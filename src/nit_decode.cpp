/*
********************************************************************************
* Copyright (C) 2021, xiang <dx_65535@163.com>.
* All right reserved.
*
* File Name   : nit_decode.cpp
* Author      :
* Version     : V1.0
* Description : 
* Journal     : 2020-12-29 init v1.0
* brief       :
* Others      :
********************************************************************************
*/

#include <stdio.h>
#include "ts_protocol.h"
#include "nit_decode.h"
#include "debug_code.h"
#include "log.h"

NitDecode* NitDecode::GetInstance()
{
    static NitDecode instance;
    return &instance;
}

int NitDecode::get_nit_info(unsigned char *data, struct TS_NIT *nit_info)
{
    struct TS_NIT tmp_nit_info;

    memset(&tmp_nit_info, 0, sizeof(struct TS_NIT));
#if 0
    static int i = 0;
    if (data[0] == 0x40) {
        PRINT_INFO("----------NIT Table: %d\n", i++);
        show_hex(data, 30);
        PRINT_INFO("---------------------------------------\n");
    }
#endif
    return 0;
}



