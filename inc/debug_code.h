/*
********************************************************************************
* Copyright (C) 2021, xiang <dx_65535@163.com>.
* All right reserved.
*
* File Name   : debug_code.h
* Author      :
* Version     : V1.0
* Description : Log file
* Journal     : 2020-10-19 init v1.0
* brief       :
* Others      :
********************************************************************************
*/

#ifndef __DEBUG_CODE_H__
#define __DEBUG_CODE_H__

#include <stdio.h>
#include "pmt_decode.h"
#include "log.h"


#define PRINT_PMT_INFO() \
{                                                    \
    int j = 0;                                       \
    for (; j < 4; j++) {                         \
        PRINT_DEBUG("packet_position: %d\n\
        pmt_id:                  0x%x \n\
        table_id_8b:             0x%x \n\
        program_num_16b:         0x%x \n\
        elementary_pid_13b:      0x%x \n\
        pcr_pid_13b:             0x%x \n\
        stream_type_8b:          0x%x \n\
        descriptor_tag:          0x%x \n,\
        language_code:           0x%x \n", \
        j,                                  \
        pmt_info[j].pmt_id,     \
        pmt_info[j].table_id_8b ,                               \
        pmt_info[j].program_num_16b,            \
        pmt_info[j].pcr_pid_13b,           \
        pmt_info[j].compent[1].elementary_pid_13b , \
        pmt_info[j].compent[1].stream_type_8b , \
        pmt_info[j].compent[1].es_descriptor.descriptor_tag,   \
        pmt_info[j].compent[1].es_descriptor.descriptor_data.language_code ); \
    } \
}

#define PRINT_HEADER() \
{                      \
    PRINT_DEBUG("packet_position: %u\n\
    sync_indicator_8b:            0x%x \n\
    error_indicator_1b:           0x%x \n\
    effective_start_indicator_1b: 0x%x \n\
    priority_indicator_1b:        0x%x \n\
    pid_13b:                      0x%x \n\
    scramble_control_2b:          0x%x \n\
    adaptation_contorl_2b:        0x%x \n\
    continue_counter_4b:          0x%x \n",\
    packet_position,                               \
    pact_data.header.sync_indicator_8b,            \
    pact_data.header.error_indicator_1b,           \
    pact_data.header.effective_start_indicator_1b, \
    pact_data.header.priority_indicator_1b,        \
    pact_data.header.pid_13b,                      \
    pact_data.header.scramble_control_2b,          \
    pact_data.header.adaptation_contorl_2b,        \
    pact_data.header.continue_counter_4b);         \
}


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
    last_section_number_8b:                0x%x \n\
    CRC:                                   0x%x \n",\
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
    pat_info.last_section_number_8b,               \
    pat_info.CRC_32                                \
);                                                 \
}

inline void show_hex(unsigned char *str, int lenth)
{
    int i = 0;

    PRINT_INFO("hex_string: ");
    for(; i<lenth; i++) {
        PRINT_INFO("%d: 0x%x ", i, str[i]);
    }
}

#endif //__DEBUG_CODE_H__

