/*******************************************************************************
*  FILENAME: timeout.c
*
* Discription:
* implement some interface methods to store information in the hashmap
*
*******************************************************************************/

/*-----------------------------------------------------------------------------
		include files
------------------------------------------------------------------------------*/

#include "timeout.h"

/*------------------------------------------------------------------------------
		definitions (defines, typedefs, ...)
------------------------------------------------------------------------------*/

#define    MAP_CAPACITY  10

/*------------------------------------------------------------------------------
		function prototypes
------------------------------------------------------------------------------*/

/*
* this method check the timeout of the pair to see whether the device is lost.
*
* Parameter: 
*
* pair: the pair to be checked.
*
* return value: none.
*/
void comp_timeout(Pair *pair);

/*------------------------------------------------------------------------------
		global variable declarations
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
		implementation code
------------------------------------------------------------------------------*/

int hm_init(hashMap **hashmap){
    hashMap *map = hm_new(MAP_CAPACITY);
    *hashmap = map;
    return 1;
}

int hm_destroy(hashMap *hashmap){
    hm_delete(hashmap);
    return 1;
}

int hm_add(TIME duration,  DADDRESS address){
    time_t now, timeout;
    now = time(NULL);
    timeout = now + duration;
    hm_put(hashmap, address, timeout, duration);
    return 1;
}

int hm_disconnect(DADDRESS address){
    pr_delete(hashmap, address);
    return 1;
}


int hm_update(DADDRESS address){
    time_t now, timeout;
    Pair *pair;
    pair = hm_get_fromKey(hashmap, address);
     if(pair == NULL){
         return 0;}
    now = time(NULL);
    TIME duration;
    duration = pair->duration;
    timeout = now + duration;
    pair->value = timeout;
    return 1;
}

int sleep(DADDRESS address, TIME duration){
    time_t now, timeout;
    Pair *pair;
    pair = hm_get_fromKey(hashmap, address);
     if(pair == NULL){
         return 0;}
    pair->duration = duration;
    pair->state = ASLEEP;
    now = time(NULL);
    timeout = now + duration;
    pair->value = timeout;
    return 1;
}

int check_timeout(){
   return hm_enum(hashmap, comp_timeout);
}

void comp_timeout(Pair *pair){
    time_t now;
    now = time(NULL);
    if(now > pair->value){
       //d_timeout(pair->key);
        printf("Time Out !");
    }
}





