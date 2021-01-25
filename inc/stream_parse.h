/*
********************************************************************************
* Copyright (C) 2021, xiang <dx_65535@163.com>.
* All right reserved.
*
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

    /*
     * @brief: 获取终端输入的文件路径字符串
     */
    void get_path(char *file);

    /*
     * @brief: 获取实例化
     */
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


  private:
    char *buffer;
    char *path;
    FILE *ts_fp;
    unsigned long packet_lenth;
    struct PACT_DATA pact_data;
    void set_msg_status(enum MSG_STATUS status);
    MSG_STATUS get_msg_status();
};

#endif //__STREAM_PARSE_H__
