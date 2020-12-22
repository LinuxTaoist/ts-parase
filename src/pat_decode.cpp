/*
********************************************************************************
* @copyright 2020 Shenzhen Chuangwei-RGB Electronics Co.,Ltd.
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
#include "pat_decode.h"
#include "log.h"

struct TS_PAT pat_info;

struct PROGRAM_INFO program_info[PROGEAM_COUNT] = {0, 0, 0};

#define PRINT_PAT_INFO() \
{                      \
    PRINT_INFO("\n\
    table_id_8b:                           0x%x \n\
    section_syntax_indicator_1b:           0x%x \n\
    zero_1b:                               0x%x \n\
    reserved_1_2b:                         0x%x \n\
    section_length_12b:                    0x%x \n\
    transport_stream_id_16b:               0x%x \n\
    reserved_2_2b:                         0x%x \n\
    version_number_5b:                     0x%x \n\
    current_next_indicator_1b:             0x%x \n\
    section_number_8b:                     0x%x \n\
    last_section_number_8b:                0x%x \n",\
    pat_info.table_id_8b,                          \
    pat_info.section_syntax_indicator_1b,          \
    pat_info.zero_1b,                              \
    pat_info.reserved_1_2b,                        \
    pat_info.section_length_12b,                   \
    pat_info.transport_stream_id_16b,              \
    pat_info.reserved_2_2b,                        \
    pat_info.version_number_5b,                    \
    pat_info.current_next_indicator_1b,            \
    pat_info.section_number_8b,                    \
    pat_info.last_section_number_8b                \
);                                                 \
}

static void show_hex(char *str, int lenth)
{
    int i = 0;

    PRINT_INFO("hex_string: ");
    for(; i<lenth; i++) {
        PRINT_INFO("%d: 0x%x ", i, str[i]);
    }
}

PatDecode* PatDecode::GetInstance()
{
    static PatDecode instance;
    return &instance;
}

int PatDecode::get_pat_info(unsigned char *data)
{
    int ret = 0, i = 0;
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
    for(i = 0; i < pat_info.section_length_12b - PAT_REGULATE_LENTH + 1; i=i+4) {
        program_info[i/4].num_16b = (data[8+i]&0x1F) << 8 | data[9+i];
        program_info[i/4].pmt_13b = (data[10+i]&0x1F) << 8 | data[11+i];
        program_info[i/4].count++;

        PRINT_DEBUG("%d: num: %d pmt: 0x%x\n", i/4, 
                          program_info[i/4].num_16b, program_info[i/4].pmt_13b);
    } 

    return ret;
}




