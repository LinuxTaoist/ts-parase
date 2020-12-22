/*
********************************************************************************
* @copyright 2020 Shenzhen Chuangwei-RGB Electronics Co.,Ltd.
* File Name   : stream_parse.cpp
* Author      :
* Version     : V1.0
* Description : 
* Journal     : 2020-12-18 init v1.0
* brief       :
* Others      :
********************************************************************************
*/

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "stream_parse.h"
#include "pat_decode.h"
#include "log.h"

using namespace std;

static enum MSG_STATUS process_status = MSG_DEFAULT;
static struct ORIGIN_DATA tmp_frame;

static unsigned int packet_position = 0;

#define PRINT_HEADER() \
{                      \
    PRINT_INFO("packet_position: %u\n\
    sync_indicator_8b:            0x%x \n\
    error_indicator_1b:           0x%x \n\
    effective_start_indicator_1b: 0x%x \n\
    priority_indicator_1b:        0x%x \n\
    pid_13b:                      0x%x \n\
    scramble_control_2b:          0x%x \n\
    adaptation_contorl_2b:        0x%x \n\
    continue_counter_4b:          0x%x \n",\
    packet_position,                               \
    pact_data.header.sync_indicator_8b,            \
    pact_data.header.error_indicator_1b,           \
    pact_data.header.effective_start_indicator_1b, \
    pact_data.header.priority_indicator_1b,        \
    pact_data.header.pid_13b,                      \
    pact_data.header.scramble_control_2b,          \
    pact_data.header.adaptation_contorl_2b,        \
    pact_data.header.continue_counter_4b);         \
}

static void show_hex(unsigned char *str, unsigned int lenth)
{
    int i = 0;

    PRINT_INFO("hex_string: ");
    for(; i<lenth; i++) {
        PRINT_INFO(" 0x%x", str[i]);
    }
}

Parse::Parse()
{
    PRINT_INFO("Class Parse\n");
}

Parse* Parse::GetInstance()
{
    static Parse instance;
    return &instance;
}

void Parse::get_path(char *file)
{
    path = file;
    PRINT_INFO("path: %s\n", path);
}

void Parse::data_process()
{
    struct ORIGIN_DATA ts_frame;

    ts_fp = fopen(path, "rb+");
    if (NULL == ts_fp) {
        PRINT_ERR("File open error! \n");
        exit(0);
    }

    while(!feof(ts_fp)) {
        packet_position++;
        memset((void *)&ts_frame, 0, sizeof(ts_frame));
        unpacket(&ts_frame);
        
        if (get_msg_status() == MSG_COMPLETE) {
            frame_process(&ts_frame);
            //PRINT_HEADER();
            //PRINT_INFO("\n");
        }

       // PRINT_INFO("0x%x ", ts_frame.data[c++]);
    }

    if(ts_fp) {
        fclose(ts_fp);
    }
}

int Parse::unpacket(struct ORIGIN_DATA *frame)
{
    int ret = 0;
    static int index =0;

    /* 收集一帧数据后，发出处理消息 */
    tmp_frame.data[index] = fgetc(ts_fp);
    if (tmp_frame.data[index] != PACKET_SYNC_BYTE
        || get_msg_status() == MSG_DEFAULT) {
        //PRINT_DEBUG("busy! \r\n");
        index++;
        set_msg_status(MSG_BUSY);
    } else if (tmp_frame.data[index] == PACKET_SYNC_BYTE
               && get_msg_status() != MSG_DEFAULT) {
        /* 收集完一帧数据，发出完成消息 */
        //PRINT_DEBUG("complate! \r\n");
        tmp_frame.lenth = index;
        index = 0;
        tmp_frame.data[index++] = PACKET_SYNC_BYTE; //补充丢失包头同步字节
        set_msg_status(MSG_COMPLETE);
        memcpy(frame, &tmp_frame, sizeof(tmp_frame));
        memset((void *)&tmp_frame, 0, sizeof(tmp_frame));
        //show_hex(frame->data, frame->lenth);
        //PRINT_INFO("\n");
    } 

    ret = 0;
}

int Parse::frame_process(struct ORIGIN_DATA *frame)
{
    int ret = 0;
    static int debug = 0;
    memset((void *)&pact_data, 0, sizeof(pact_data));
    get_packet_header(frame);

    /* 获取PAT表信息 */
    if (pact_data.header.pid_13b == PAT_PID) {
            PatDecode::GetInstance()->get_pat_info(
                pact_data.buffer);
#if 0
        if(debug == 0) {
            debug =1;
            PRINT_HEADER();
            show_hex(&pact_data.buffer[EFFECTIVE_START_POSITION 
                         + pact_data.header.effective_start_indicator_1b],30);

        }
#endif
    }

    return ret;
}

void Parse::set_msg_status(enum MSG_STATUS status)
{
    process_status = status;
}

MSG_STATUS Parse::get_msg_status()
{
    return process_status;
}

int Parse::get_packet_header(struct ORIGIN_DATA *frame)
{
    pact_data.header.sync_indicator_8b = frame->data[0];
    pact_data.header.error_indicator_1b = (frame->data[1] & 0x80) >> 7;
    pact_data.header.effective_start_indicator_1b = (frame->data[1] & 0x40) >> 6;
    pact_data.header.priority_indicator_1b = (frame->data[1] & 0x20) >>5;
    pact_data.header.pid_13b = (frame->data[1] & 0x1F) << 8 | frame->data[2];
    pact_data.header.scramble_control_2b = (frame->data[3] & 0xC0) >> 6;
    pact_data.header.adaptation_contorl_2b = (frame->data[3] & 0x30) >> 4;
    pact_data.header.continue_counter_4b = frame->data[3] & 0x0F;

    memcpy(pact_data.buffer, frame->data+PACKET_HEADER_LENTH
           + pact_data.header.effective_start_indicator_1b, 
           PACKET_LENTH_188-PACKET_HEADER_LENTH);

    return 0;
}

int Parse::get_packet_lenth(char *buffer)
{
    
}
