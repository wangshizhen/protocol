/*******************************************************************************
*  FILENAME: hashmap.c
*
* Discription:
* implement hash_map. provide basic functions.
*
*******************************************************************************/

/*-----------------------------------------------------------------------------
		include files
------------------------------------------------------------------------------*/
#include "hashmap.h"

/*------------------------------------------------------------------------------
		definitions (defines, typedefs, ...)
------------------------------------------------------------------------------*/




/*------------------------------------------------------------------------------
		function prototypes
------------------------------------------------------------------------------*/

static Pair * get_pair(Bucket *bucket, DADDRESS key);
static unsigned long hash(DADDRESS  key);

/*------------------------------------------------------------------------------
		global variable declarations
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
		implementation code
------------------------------------------------------------------------------*/

hashMap * hm_new(unsigned int capacity)
{
	hashMap *map;
	
	map = malloc(sizeof(hashMap));
	if (map == NULL) {
		return NULL;
	}
	map->count = capacity;
	map->buckets = malloc(map->count * sizeof(Bucket));
	if (map->buckets == NULL) {
		free(map);
		return NULL;
	}
	memset(map->buckets, 0, map->count * sizeof(Bucket));
	return map;
}

void hm_delete(hashMap *map)
{
	unsigned int i, j, n, m;
	Bucket *bucket;
	Pair *pair;

	if (map == NULL) {
		return;
	}
	n = map->count;
	bucket = map->buckets;
	i = 0;
	while (i < n) {
		m = bucket->count;
		pair = bucket->pairs;
		j = 0;
		while(j < m) {
			free(pair);
			pair++;
			j++;
		}
		free(bucket->pairs);
		bucket++;
		i++;
	}
	free(map->buckets);
	free(map);
}

Pair  * hm_get_fromKey(const hashMap *map, DADDRESS key)
{
	unsigned int index;
	Bucket *bucket;
	Pair *pair;

	if (map == NULL) {
		return 0;
	}

	index = hash(key) % map->count;
	bucket = &(map->buckets[index]);
	pair = get_pair(bucket, key);
	if (pair == NULL) {
		return 0;
	}

	return pair;
}

Pair  * hm_get_fromState(const hashMap *map, State state)
{
	unsigned int i, j, n, m;
	Bucket *bucket;
	Pair *pair;

	if (map == NULL) {
		return NULL;
	}
	bucket = map->buckets;
	n = map->count;
	i = 0;
	while (i < n) {
		pair = bucket->pairs;
		m = bucket->count;
		j = 0;
		while (j < m) {
			if(pair->state == state){
                        return pair;}
			pair++;
			j++;
		}
		bucket++;
		i++;
	}
	return NULL;
}

State hm_state(const hashMap *map, DADDRESS key)  // maybe this method should be replaced by sql.
{
	unsigned int index;
	Bucket *bucket;
	Pair *pair;

	if (map == NULL) {
		return 0;
	}
	index = hash(key) % map->count;
	bucket = &(map->buckets[index]);
	pair = get_pair(bucket, key);
	if (pair == NULL) {
        return NOTCONNECTED;
	}
        else {return pair->state;}
}

int pr_delete(hashMap *map, DADDRESS key)
{
        unsigned int index;
	Bucket *bucket;
	Pair *pair;

	if (map == NULL) {
		return 0;
	}
	index = hash(key) % map->count;
	bucket = &(map->buckets[index]);
	pair = get_pair(bucket, key);
	if (pair == NULL) {
		return 0;
	}
        pair->state = NOTCONNECTED;
	return 1;
}

int hm_put(hashMap *map, DADDRESS key, time_t value, TIME duration)
{
	unsigned int index;
	Bucket *bucket;
	Pair *tmp_pairs, *pair;

	if (map == NULL) {
		return 0;
	}

	/* Get a pointer to the bucket the key string hashes to */
	index = hash(key) % map->count;
	bucket = &(map->buckets[index]);
	/* Check if we can handle insertion by simply replacing
	 * an existing value in a key-value pair in the bucket.
	 */
        pair = get_pair(bucket, key);
	if (pair != NULL) {
                if(pair->state == NOTCONNECTED){
                 pair->state = ACTIVE;
                 pair->value = value;
                 pair->duration = duration;
                 return 1; 
                 }
	        return 0;
	}
        pair = hm_get_fromState(map, NOTCONNECTED);
        if(pair != NULL){
            pair->key = key;
            pair->value = value;
            pair->state = ACTIVE;
            pair->duration = duration;
            return 1;}
	
	/* Create a key-value pair */
	if (bucket->count == 0) {
		/* The bucket is empty, lazily allocate space for a single
		 * key-value pair.
		 */
		bucket->pairs = malloc(sizeof(Pair));
		if (bucket->pairs == NULL) {
			return 0;
		}
		bucket->count = 1;
	}
	else {
		/* The bucket wasn't empty but no pair existed that matches the provided
		 * key, so create a new key-value pair.
		 */
		tmp_pairs = realloc(bucket->pairs, (bucket->count + 1) * sizeof(Pair));
		if (tmp_pairs == NULL) {
			return 0;
		}
		bucket->pairs = tmp_pairs;
		bucket->count++;
	}
	/* Get the last pair in the chain for the bucket */
	pair = &(bucket->pairs[bucket->count - 1]);
	pair->key = key;
	pair->value = value;
        pair->state = ACTIVE;
        pair->duration = duration;
	return 1;
}

int hm_get_count(const hashMap *map)
{
	unsigned int i, j, n, m;
	unsigned int count;
	Bucket *bucket;
	Pair *pair;

	if (map == NULL) {
		return 0;
	}
	bucket = map->buckets;
	n = map->count;
	i = 0;
	count = 0;
	while (i < n) {
		pair = bucket->pairs;
		m = bucket->count;
		j = 0;
		while (j < m) {
			count++;
			pair++;
			j++;
		}
		bucket++;
		i++;
	}
	return count;
}

int hm_enum(const hashMap *map, hm_enum_func enum_func)
{
	unsigned int i, j, n, m;
	Bucket *bucket;
	Pair *pair;

	if (map == NULL) {
		return 0;
	}
	if (enum_func == NULL) {
		return 0;
	}
	bucket = map->buckets;
	n = map->count;
	i = 0;
	while (i < n) {
		pair = bucket->pairs;
		m = bucket->count;
		j = 0;
		while (j < m) {
            enum_func(pair);
			pair++;
			j++;
		}
		bucket++;
		i++;
	}
	return 1;
}

/*
 * Returns a pair from the bucket that matches the provided key,
 * or null if no such pair exist.
 */

static Pair * get_pair(Bucket *bucket, DADDRESS key)
{
	unsigned int i, n;
	Pair *pair;

	n = bucket->count;
	if (n == 0) {
		return NULL;
	}
	pair = bucket->pairs;
	i = 0;
	while (i < n) {
		if (pair->key == key) {
				return pair;
		}
		pair++;
		i++;
	}
	return NULL;
}

/*
 * Returns a hash code for the address.
 */
static DADDRESS hash(DADDRESS key)
{
	DADDRESS hash = key;

	return hash;
}

