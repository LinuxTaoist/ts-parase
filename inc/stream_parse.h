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

#ifndef __stream_PARSE_H__
#define __stream_PARSE_H__

#define PATH_LEN 30

class Parse {
public:
    Parse();
    void get_path(char *file);

    static Parse* GetInstance();

    void unpacket();

    int get_packet_lenth(char *buffer);

private:
    char *buffer;
    char *path;
    FILE *ts_fp;
    unsigned long packet_lenth;

};

#endif
