/*
********************************************************************************
* Copyright (C) 2021, xiang <dx_65535@163.com>.
* All right reserved.
*
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
#include <string.h>
#include <log.h>
#include "stream_parse.h"

int main(int argc, char *argv[])
{
    PRINT_INFO("ts file name: %s.\n", argv[1]);

    Parse::GetInstance()->get_path(argv[1]);
    Parse::GetInstance()->data_process();

    return 0;
}
