/*
********************************************************************************
* Copyright (C) 2021, xiang <dx_65535@163.com>.
* All right reserved.
*
* File Name   : eit_decode.cpp
* Author      :
* Version     : V1.0
* Description : 
* Journal     : 2020-12-29 iEit v1.0
* brief       :
* Others      :
********************************************************************************
*/
#include <stdio.h>
#include "ts_protocol.h"
#include "eit_decode.h"
#include "debug_code.h"
#include "log.h"


EitDecode* EitDecode::GetInstance()
{
    static EitDecode instance;
    return &instance;
}

int EitDecode::get_eit_info(unsigned char *data)
{
    //struct TS_Eit tmp_Eit_info;

    //memset(&tmp_Eit_info, 0, sizeof(struct TS_Eit));
#if 1
    static int i = 0;
    if (data[0] == 0x4e) {
        PRINT_INFO("----------Eit Table: %d\n", i++);
        show_hex(data, 188);
        PRINT_INFO("---------------------------------------\n");
    }
#endif
    return 0;
}
