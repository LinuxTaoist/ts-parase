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
#include "log.h"

using namespace std;

static enum MSG_STATUS frame_status;
static struct ORIGIN_DATA tmp_frame;

static void show_hex(char *str, int lenth)
{
    int i = 0;

    PRINT_INFO("hex_string: ");
    for(; i<lenth; i++) {
        PRINT_INFO("%d: 0x%x ", i, str[i]);
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
    char c = 0;

    struct ORIGIN_DATA ts_frame;

    ts_fp = fopen(path, "rb+");
    if (NULL == ts_fp) {
        PRINT_ERR("File open error! \n");
        exit(0);
    }

    while(!feof(ts_fp)) {
        memset((void *)&ts_frame, 0, sizeof(ts_frame));
        unpacket(&ts_frame);
        frame_process(&ts_frame);

        PRINT_INFO("\n");
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
    if (tmp_frame.data[index] != PACKET_SYNC_BYTE) {
        index++;
        msg_set(MSG_BUSY);
    } else {
        /* 收集完一帧数据 */
        tmp_frame.lenth = index;
        index = 0;
        msg_set(MSG_COMPLETE);
        memcpy(frame, &tmp_frame, sizeof(tmp_frame));
        memset((void *)&tmp_frame, 0, sizeof(tmp_frame));
    }

    ret = 0;
}

int Parse::frame_process(struct ORIGIN_DATA *frame)
{
    int ret = 0;

    memset((void *)&pact_data, 0, sizeof(pact_data));
    get_packet_header(frame);

    if (pact_data.header.pid_13b == PAT_PID) {
        PRINT_INFO("--- Get PAT --- \n");
    }

    return ret;
}

void Parse::msg_set(enum MSG_STATUS status)
{
    frame_status = status;
}

int Parse::get_packet_header(struct ORIGIN_DATA *frame)
{
    pact_data.header.sync_indicator_8b = frame->data[0];
    pact_data.header.error_indicator_1b = frame->data[1] & 0x80;
    pact_data.header.effective_start_indicator_1b = frame->data[1] & 0x40;
    pact_data.header.priority_indicator_1b = frame->data[1] & 0x20;
    pact_data.header.pid_13b = (frame->data[1] & 0x1F) << 8 | frame->data[2];
    pact_data.header.scramble_control_2b = frame->data[3] & 0xC0;
    pact_data.header.adaptation_contorl_2b = frame->data[3] & 0x30;
    pact_data.header.continue_counter_4b = frame->data[3] & 0x0F;

    return 0;
}

int Parse::get_packet_lenth(char *buffer)
{
    
}
