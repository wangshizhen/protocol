#ifndef OUR_PROTOCOL_H
#define OUR_PROTOCOL_H



#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>


#define SUBSCRIBE            (0x00)
#define UNSUBSCRIBE          (0x01)
#define PINGREQ              (0x02)
#define REGISTER             (0x03)
#define WILLTOPICUPD         (0x04)
#define WILLMESSAGEUPD       (0x05)
#define PUBLISH              (0x06)
#define DISCONNECT           (0x07)

#define CONNECT              (0x08)
#define SEARCHGW             (0x09)
#define WILLTOPIC            (0x0a)
#define WILLMESSAGE          (0x0b)
#define GWINFO               (0x0c)
#define ADVERTISE            (0x0d)
#define SUBACK               (0x0e)
#define UNSUBACK             (0x0f)
#define PINGACK              (0x10)
#define REGACK               (0x11)
#define WILLTOPICRESP        (0x12)
#define WILLMESSAGERESP      (0x13)
#define PUBACK               (0x14)



#define   _gwID          (0x11)
#define   _gwAddress      (0x11111111)

#define   adDuration     (0x78)



enum return_code{ACCEPT,REJECT};


typedef      uint64_t           DADDRESS;
typedef      uint32_t           GWDADDRESS;
typedef      uint8_t            GW_ID;
typedef      uint8_t            PROTOCOL_ID;
typedef      uint8_t            TIME;
typedef      uint8_t            LENGTH;
typedef      uint8_t            TYPE;
typedef      char               TOPIC_NAME;
typedef      uint8_t            TOPIC_ID;
typedef      uint16_t           CLIENT_ID;
typedef      uint8_t            RETURN_CODE;
typedef      uint8_t            FLAG;
typedef      uint16_t           MESSAGE_ID;
typedef      char               DATA; //need to find out what exactly the data type is
 



typedef struct{
   DADDRESS    device_address;
   DATA       *data;
}message_info;

typedef struct{
   DADDRESS    device_address;
   LENGTH      length_of_real_data;
   DATA        *real_data;
}data_info;

typedef struct{
   DADDRESS    device_address;
   TIME        duration;
}thread_para;

typedef struct {
  LENGTH       length;
  TYPE         type;
  GW_ID        gwID;
  TIME         duration;
} advertise_packet;

typedef struct {
  LENGTH       length;
  TYPE         type;
  GW_ID        gwID;
  GWDADDRESS   gwAddress;
} gwinfo_packet;

typedef struct {
  LENGTH       length;
  TYPE         type;
  TOPIC_ID     topic_id;
  MESSAGE_ID   message_id;
  TOPIC_NAME  *topic_name;
} register_packet;	


typedef struct {
  LENGTH       length;
  TYPE         type;
  TOPIC_ID     topic_id;
  MESSAGE_ID   message_id;
  RETURN_CODE  return_code;
} regack_packet;


typedef struct {
  LENGTH       length;
  TYPE         type;
  FLAG         flags;
  TOPIC_ID     topic_id;
  MESSAGE_ID   message_id;
  DATA         *data;
} publish_packet;

typedef struct {
  LENGTH       length;
  TYPE         type;
  TOPIC_ID     topic_id;
  MESSAGE_ID    message_id;
  RETURN_CODE  return_code;
} puback_packet;

typedef struct {
  LENGTH       length;
  TYPE         type;
  FLAG         flags;
  PROTOCOL_ID  protocol_id;
  TIME         duration;
  CLIENT_ID    client_id;
} connect_packet;

typedef struct {
  LENGTH       length;
  TYPE         type;
  RETURN_CODE  return_code;
} connack_packet;

typedef struct {
  LENGTH       length;
  TYPE         type;
} willtopicreq_packet;

typedef struct {
  LENGTH       length;
  TYPE         type;
  FLAG         flags;
  TOPIC_ID     topic_id;
} willtopic_packet;

typedef struct {
  LENGTH       length;
  TYPE         type;
  DATA         *will_message;
} willmessage_packet;

typedef struct {
  LENGTH       length;
  TYPE         type;
  CLIENT_ID    client_id;
} pingreq_packet;

typedef struct {
  LENGTH       length;
  TYPE         type;
} pingresp_packet;

typedef struct {
  LENGTH length;
  TYPE type;
  FLAG flags;
  MESSAGE_ID message_id;
  union {
      TOPIC_NAME *topic_name;
      TOPIC_ID topic_id;
  };
} subscribe_packet;

typedef struct {
  LENGTH length;
  TYPE type;
  FLAG flags;
  TOPIC_ID topic_id;
  MESSAGE_ID message_id;
  RETURN_CODE return_code;
} suback_packet;

typedef struct {
  LENGTH length;
  TYPE type;
  MESSAGE_ID message_id;
} unsuback_packet;

#endif
