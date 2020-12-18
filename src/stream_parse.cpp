/*
********************************************************************************
* @copyright 2020 Shenzhen Chuangwei-RGB Electronics Co.,Ltd.
* File Name   : main.cpp
* Author      :
* Version     : V1.0
* Description : Entrance of the main program
* Journal     : 2020-12-18 init v1.0
* brief       :
* Others      :
********************************************************************************
*/

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "stream_parse.h"
#include "ts_protocol.h"
#include "log.h"

using namespace std;

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

void Parse::unpacket()
{
    ts_fp = fopen(path, "rb+");
    if (NULL == ts_fp) {
        PRINT_ERR("file open error! \n");    
    }

    while(!feof(ts_fp)) {
        
    }

    if(ts_fp) {
        fclose(ts_fp);
    }
}

int Parse::get_packet_lenth(char *buffer)
{

}
