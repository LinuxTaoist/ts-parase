/*
********************************************************************************
* Copyright (C) 2021, xiang <dx_65535@163.com>.
* All right reserved.
*
* File Name   : vct_decode.cpp
* Author      :
* Version     : V1.0
* Description : 
* Journal     : 2020-01-19 init v1.0
* brief       :
* Others      : Analysis of the code stream for the ATSC specification only.
********************************************************************************
*/

#include <stdio.h>
#include "ts_protocol.h"
#include "vct_decode.h"
#include "debug_code.h"
#include "log.h"

AtscVctDecode* AtscVctDecode::GetInstance()
{
    static AtscVctDecode instance;
    return &instance;
}

bool AtscVctDecode::GetVctInfo(unsigned char *data, struct TsAtscVct *pVct)
{
    bool ret = true;

    pVct->table_id_8b = data[0];

    return ret;
}
