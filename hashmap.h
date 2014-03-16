/*******************************************************************************
*  FILENAME: hashmap.h
*
* Discription:
* implement hash_map to store the address and timeout time as well as the state of certain device. provide basic functions.
*
*******************************************************************************/

#ifndef HASHMAP_H
#define HASHMAP_H
#ifdef __cplusplus
extern "C"
{
#endif
/*-----------------------------------------------------------------------------
		include files
------------------------------------------------------------------------------*/

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "our_protocol.h"
//#include "timeout.h"
/*------------------------------------------------------------------------------
		definitions (defines, typedefs, ...)
------------------------------------------------------------------------------*/


typedef struct Pair Pair;

typedef struct Bucket Bucket;
enum State {ACTIVE, ASLEEP, NOTCONNECTED};
typedef enum State State;
struct Pair {
    DADDRESS  key;
    time_t    value;
        TIME      duration;
        State     state;
};

struct Bucket {
    unsigned int count;
    Pair *pairs;
};

struct HashMap {
    unsigned int count;
    Bucket *buckets;
};
typedef struct HashMap hashMap;



/*------------------------------------------------------------------------------
		function prototypes
------------------------------------------------------------------------------*/

/*
 * This callback function is called once per pair when iterating over
 * all keys associated to values.
 *
 * Parameters:
 *
 * key: An integer contain the value of the address of sensor device.
 *
 * pair: the basic element in the map.
 *
 * Return value: None.
 */

typedef void(*hm_enum_func)(Pair *pair);

/*
 * Creates a hashmap.
 *
 * Parameters:
 *
 * capacity: The number of top-level slots this hash map
 * should allocate. This parameter must be > 0.
 *
 * Return value: A pointer to a hashmap object, 
 * or null if a new hashmap could not be allocated.
 */
hashMap * hm_new(unsigned int capacity);

/*
 * Releases all memory held by a hashmap object.
 *
 * Parameters:
 *
 * map: A pointer to a string map. This parameter cannot be null.
 * If the supplied hashmap has been previously released, the
 * behaviour of this function is undefined.
 *
 * Return value: None.
 */
void hm_delete(hashMap *map);

/*
 * Returns the pointer associated with the supplied key.
 *
 * Parameters:
 *
 * map: A pointer to a hashmap. This parameter cannot be null.
 *
 * key: An integer contain the value of the address of sensor device.
 *
 * Return value: if find the pair, return the pointer to the pair. otherwise 
 * return null.
 */

Pair * hm_get_fromKey(const hashMap *map, DADDRESS key);

/*
 * Returns the pointer associated with the first pair with the specified state.
 *
 * Parameters:
 *

 * map: A pointer to a hashmap. This parameter cannot be null.
 *
 * state: the state of the sensor device.It could be active/asleep/disconnect.
 *

 * Return value: if find the pair, return the pointer to the pair. otherwise 
 * return null.
 */

Pair  * hm_get_fromState(const hashMap *map, State state);

/*
 * Queries the state of the device with certain key.
 *
 * Parameters:
 *
 * map: A pointer to a hashmap. This parameter cannot be null.
 *
 * key: An integer contain the value of the address of sensor device.
 *
 * Return value: the state of the device with the key.
 */
State hm_state(const hashMap *map, DADDRESS key);

/*
 * set the state of the device as disconnect. as if we delete the element.
 *
 * Parameters:
 *
 * map: A pointer to a hashmap. This parameter cannot be null.
 *
 * key: An integer contain the value of the address of sensor device.
 *
 * Return value: 1 if the deletion succeeded, 0 otherwise.
 */
int pr_delete(hashMap *map, DADDRESS key);

/*
 * Associates a value with the supplied key. 
 *
 * Parameters:
 *
 * map: A pointer to a hashmap. This parameter cannot be null.
 *
 * key: An integer contain the value of the address of sensor device.
 *
 * value: the timeout time of the device.
 *
 * duration: the time interval for the device to keep alive or the sleep duration.
 *
 * Return value: 1 if the association succeeded, 0 otherwise.
 */
int hm_put(hashMap *map, DADDRESS key,time_t value, TIME duration);

/*
 * Returns the number of associations between keys and values.
 *
 * Parameters:
 *
 * map: A pointer to a hashmap. This parameter cannot be null.
 *
 * Return value: The number of associations between keys and values.
 */
int hm_get_count(const hashMap *map);

/*
 * An enumerator over all associations between keys and values.
 *
 * Parameters:
 *
 * map: A pointer to a hashmap. This parameter cannot be null.
 *
 * enum_func: A pointer to a callback function that will be
 * called by this procedure once for every key associated
 * with a value. This parameter cannot be null.
 *
 *
 * Return value: 1 if enumeration completed, 0 otherwise.
 */
int hm_enum(const hashMap *map, hm_enum_func enum_func);
#ifdef __cplusplus
}
#endif
#endif


