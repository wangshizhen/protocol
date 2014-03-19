#ifndef TIMEOUT_H
#define TIMEOUT_H
#ifdef __cplusplus
  extern "C" {
#endif
/*******************************************************************************
*  FILENAME: timeout.h
*
* Discription:
* implement some interface methods to store infomation in the hashmap
*
*******************************************************************************/

/*-----------------------------------------------------------------------------
		include files
------------------------------------------------------------------------------*/

#include "hashmap.h"

/*------------------------------------------------------------------------------
		definitions (defines, typedefs, ...)
------------------------------------------------------------------------------*/

hashMap *hashmap;
/*------------------------------------------------------------------------------
		function prototypes
------------------------------------------------------------------------------*/


/*
* initialize the hashmap.
*
* Parameters:
*
* **hashmap: the address of the pointer pointing to a hashmap.
*
* return value: 1 if initialize successfully, 0 otherwise.
*/

int hm_init(hashMap **hashmap);

/*
* destroy the hashmap.
*
* Parameters:
*
* **hashmap: the address of the pointer pointing to a hashmap.
*
* return value: 1 if destroy successfully, 0 otherwise.
*/
int hm_destroy(hashMap *hashmap);

/*
* when the device connect, we add the related infomation to the hash map.
*
* Parameters:
* 
* duration: the time interval for the device to keep alive or the sleep duration.
*
* address: the address of the connecting device.
*
* return value: 1 if add to the map successfully, 0 otherwise.
*/

int hm_add(TIME duration,  DADDRESS address);

/*
* when the device disconnect, we set the state of the device as disconncet.
* 
* Parameter:
*
* address:the address of the disconnecting device.
* 
*return value: 1 if set the state successfully, 0 otherwise.
*/

int hm_disconnect(DADDRESS address);

/*
* when a message coming, we update the timeout value in the hashmap
*
* 
* Parameter:
*
* address:the address of the device which send the incoming message.
* 
*return value: 1 if update successfully, 0 otherwise.
*/

int hm_update(DADDRESS address);

/*
* when a device want to sleep, we update the info of the device in the map.
*
* 
* Parameter:
*
* address:the address of the device which send the incoming message.
* 
* duration: the time interval the device want to sleep.
*
*return value: 1 if update successfully, 0 otherwise.
*/

int device_sleep(DADDRESS address, TIME duration);

/*
* check whether there are timeout devices in the hashmap.
*
* 
* Parameter: none.
*
* return value: none.
*/

int check_timeout();

#ifdef __cplusplus
  }
#endif
#endif







