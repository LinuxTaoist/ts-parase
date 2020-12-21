/*
********************************************************************************
* @copyright 2020 Shenzhen Chuangwei-RGB Electronics Co.,Ltd.
* File Name   : stream_parse.h
* Author      :
* Version     : V1.0
* Description : Log file
* Journal     : 2020-10-19 init v1.0
* brief       :
* Others      :
********************************************************************************
*/

#ifndef __STREAM_PARSE_H__
#define __STREAM_PARSE_H__

#include <stdio.h>
#include "ts_protocol.h"

#define PATH_LEN 30

class Parse {
public:
    Parse();
    void get_path(char *file);

    static Parse* GetInstance();

    /*
     * @brief: 数据处理中心
     */
    void data_process();
 
    /*
     * @brief: 将流文件拆解为帧数据
     */
    int unpacket(struct ORIGIN_DATA *frame);

    /* 
     * @brief: 帧数据处理
     */
    int frame_process(struct ORIGIN_DATA *frame);

    /*
     * @brief: 获取数据包头
     */
    int get_packet_header(struct ORIGIN_DATA *frame);

    int get_packet_lenth(char *buffer);

private:
    char *buffer;
    char *path;
    FILE *ts_fp;
    unsigned long packet_lenth;
    struct PACT_DATA pact_data;
    void msg_set(enum MSG_STATUS status);
};

#endif
