/*
********************************************************************************
* @copyright 2020 Shenzhen Chuangwei-RGB Electronics Co.,Ltd.
* File Name   : ts_protocol.h
* Author      :
* Version     : V1.0
* Description : Log file
* Journal     : 2020-10-19 init v1.0
* brief       :
* Others      :
********************************************************************************
*/

#ifndef __TS_PROTOCOL_H__
#define __TS_PROTOCOL_H__

#define PACKET_SYNC_BYTE 0x47
#define PACKET_LENTH_188 188
#define PACKET_LENTH_204 204
#define PACKET_HEADER_LENTH 4

#define EFFECTIVE_START_POSITION 4

#define PAT_PID 0x0000  //13b: 5+8 


struct ORIGIN_DATA {
    unsigned char data[PACKET_LENTH_204];
    unsigned char lenth;
};

struct PACKET_HEADER {
    unsigned char sync_indicator_8b;
    unsigned char error_indicator_1b;
    unsigned char effective_start_indicator_1b;
    unsigned char priority_indicator_1b;
    unsigned int  pid_13b;
    unsigned char scramble_control_2b;
    unsigned char adaptation_contorl_2b;
    unsigned char continue_counter_4b;
}; 

struct PACT_DATA {
    struct PACKET_HEADER header;
    unsigned char buffer[PACKET_LENTH_204-PACKET_HEADER_LENTH];
    unsigned int lenth;
};

enum MSG_STATUS {
    MSG_DEFAULT = 0,
    MSG_BUSY = 1,
    MSG_COMPLETE = 2,
    MSG_STATUS_MAX
};


#endif
