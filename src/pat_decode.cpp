/*
********************************************************************************
* Copyright (C) 2021, xiang <dx_65535@163.com>.
* All right reserved.
*
* File Name   : pat_process.cpp
* Author      :
* Version     : V1.0
* Description : 
* Journal     : 2020-12-21 init v1.0
* brief       :
* Others      :
********************************************************************************
*/

#include <stdio.h>
#include "ts_protocol.h"
#include "pat_decode.h"
#include "log.h"

struct TS_PAT pat_info;

struct PMT_PID pmt_pid_collection;

PatDecode* PatDecode::GetInstance()
{
    static PatDecode instance;
    return &instance;
}

int PatDecode::get_pat_info(unsigned char *data)
{
    int ret = 0;
    unsigned int i = 0;
    static int status_default = 0;

    /* 只解析一次PAT表 */
    if (status_default == 1) {
        return ret;    
    } else {
        status_default = 1;    
    }

    pat_info.table_id_8b = data[0];
    pat_info.section_syntax_indicator_1b = data[1] >> 7;
    pat_info.zero_1b = (data[1] &0x40) >> 6;
    pat_info.reserved_1_2b = (data[1] & 0x30) >> 4;
    pat_info.section_length_12b = (data[1] & 0x0F) << 8 | data[2];
    pat_info.transport_stream_id_16b = data[3] << 8 | data[4];
    pat_info.reserved_2_2b = data[5] >> 6;
    pat_info.version_number_5b = (data[5] & 0x3e) >> 1;
    pat_info.current_next_indicator_1b = data[5] & 0x01;
    pat_info.section_number_8b = data[6];
    pat_info.last_section_number_8b = data[7];

    /* 获取所有节目PMT */
    for(i = 0; i < pat_info.section_length_12b-PAT_REGULATE_LENTH+1; i=i+4) {
        pmt_pid_collection.info[i/4].num_16b = (data[8+i]&0x1F) << 8 | data[9+i];
        pmt_pid_collection.info[i/4].pmt_13b = (data[10+i]&0x1F) << 8 | data[11+i];
        pmt_pid_collection.count++;

        PRINT_DEBUG("%d: num: %d pmt: 0x%x count: %u\n", i/4, 
                         pmt_pid_collection.info[i/4].num_16b, 
                         pmt_pid_collection.info[i/4].pmt_13b, pmt_pid_collection.count);
    } 

    pat_info.CRC_32 = data[pat_info.section_length_12b + PAT_LENTN_POSITION] 
                    | data[pat_info.section_length_12b+PAT_LENTN_POSITION-1]<<8
                    | data[pat_info.section_length_12b+PAT_LENTN_POSITION-2]<<16
                    | data[pat_info.section_length_12b+PAT_LENTN_POSITION-3]<<24;

    return ret;
}

unsigned int PatDecode::get_crc()
{
    return pat_info.CRC_32;
}


