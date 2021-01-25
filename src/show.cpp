/*
********************************************************************************
* Copyright (C) 2021, xiang <dx_65535@163.com>.
* All right reserved.
*
* File Name   : show.cpp
* Author      :
* Version     : V1.0
* Description : 
* Journal     : 2020-12-28 init v1.0
* brief       :
* Others      :
********************************************************************************
*/

#include <iostream>
#include <stdio.h>
#include "show.h"
#include "pmt_decode.h"
#include "log.h"

Show* Show::GetInstance()
{
    static Show instance;
    return &instance;
}

void Show::pmt_show(struct TS_PMT *pmt_info) 
{
    int i, j;

    for (i = 0; pmt_info[i].pmt_id != 0; i++) {
        PRINT_INFO("├── Program: 0x%x  ==> pmt_id: 0x%x\n", pmt_info[i].program_num_16b, pmt_info[i].pmt_id);
        PRINT_INFO("│    ├── table_id: 0x%x\n", pmt_info[i].table_id_8b);
        PRINT_INFO("│    ├── section_length: 0x%x\n", pmt_info[i].section_length_12b);
        PRINT_INFO("│    ├── program_num: 0x%x\n", pmt_info[i].program_num_16b);
        PRINT_INFO("│    ├── version_num: 0x%x\n", pmt_info[i].version_number_5b);
        PRINT_INFO("│    ├── current_next_indicator: 0x%x\n", pmt_info[i].current_next_indicator_1b);
        PRINT_INFO("│    ├── section_num: 0x%x\n", pmt_info[i].section_number_8b);
        PRINT_INFO("│    ├── last_section_number: 0x%x\n", pmt_info[i].last_section_number_8b);
        PRINT_INFO("│    ├── pcr_pid: 0x%x\n", pmt_info[i].pcr_pid_13b);
        PRINT_INFO("│    ├── program_info_length: 0x%x\n", pmt_info[i].program_info_length_12b);

        for (j = 0; pmt_info[i].compent[j].stream_type_8b !=0; j++) {
            PRINT_INFO("│    │     ├── stream_type: 0x%x\n", pmt_info[i].compent[j].stream_type_8b);
            PRINT_INFO("│    │     │      ├── elementary_pid: 0x%x\n", pmt_info[i].compent[j].elementary_pid_13b);
            PRINT_INFO("│    │     │      └── es_info_length: 0x%x\n", pmt_info[i].compent[j].es_info_length_12b);
            if (pmt_info[i].compent[j].es_info_length_12b != 0) {
                PRINT_INFO("│    │     │      └── es_descriptor \n");
                PRINT_INFO("│    │     │           ├── descriptor_tag: 0x%x\n", pmt_info[i].compent[j].es_descriptor.descriptor_tag);
                PRINT_INFO("│    │     │           ├── descriptor_length: 0x%x\n", pmt_info[i].compent[j].es_descriptor.descriptor_length);
                PRINT_INFO("│    │     │           ├── descriptor_data\n");
                PRINT_INFO("│    │     │           ├── language_code: 0x%x\n", pmt_info[i].compent[j].es_descriptor.descriptor_data.language_code);
                PRINT_INFO("│    │     │           └── audio_type: 0x%x\n", pmt_info[i].compent[j].es_descriptor.descriptor_data.audio_type);
            }
        }
        PRINT_INFO("│    └── crc_32: 0x%x \n", pmt_info[i].CRC_32);
    }
}
