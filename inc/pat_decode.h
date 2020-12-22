/*
********************************************************************************
* @copyright 2020 Shenzhen Chuangwei-RGB Electronics Co.,Ltd.
* File Name   : pat_process.h
* Author      :
* Version     : V1.0
* Description : Log file
* Journal     : 2020-10-19 init v1.0
* brief       :
* Others      :
********************************************************************************
*/

#ifndef __PAT_DECODE_H__
#define __PAT_DECODE_H__

#include "ts_protocol.h"

#define PAT_REGULATE_LENTH 10u  //6 + CRC(4)
#define PROGEAM_COUNT 0X3FFF

struct TS_PAT {
    unsigned int table_id_8b;
    unsigned char section_syntax_indicator_1b;
    unsigned char zero_1b;
    unsigned char reserved_1_2b;
    unsigned int section_length_12b;
    unsigned int transport_stream_id_16b;
    unsigned char reserved_2_2b;
    unsigned char version_number_5b;
    unsigned char current_next_indicator_1b;
    unsigned int section_number_8b;
    unsigned char last_section_number_8b;
    /* 节目信息 */
    unsigned int CRC_32;
};

struct PROGRAM_INFO {
    unsigned int num_16b;
    unsigned int pmt_13b;
    unsigned int count;
};

class PatDecode {
public:
    static PatDecode* GetInstance();

    int get_pat_info(unsigned char *data);
};

#endif
