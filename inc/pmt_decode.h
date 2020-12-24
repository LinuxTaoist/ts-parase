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

#ifndef __PMT_DECODE_H__
#define __PMT_DECODE_H__

#define PMT_STREAM_MAX 20
#define PMT_ES_DESCRIPTORS_MAX 10

#define PROGRAM_INFO_START_POSITION 10
#define PMT_CRC_LENTH  4

struct DESCRIPTOR_DATA {
    unsigned int language_code;
    unsigned char audio_type;
};

struct ES_DESCRIPTORS {
    unsigned char descriptor_tag;
    unsigned int  descriptor_length;
    struct DESCRIPTOR_DATA descriptor_data;
};

struct PMT_STREAM {
    unsigned int  stream_type_8b;
    unsigned char reserved_5_3b;
    unsigned int  elementary_pid_13b;
    unsigned char reserved_6_4b;
    unsigned int  es_info_length_12b;
    struct ES_DESCRIPTORS es_descriptor;
};

struct TS_PMT {
    unsigned int  table_id_8b;
    unsigned char section_syntax_indicator_1b;
    unsigned char zero_1b;
    unsigned char reserved_1_2b;
    unsigned int  section_length_12b;
    unsigned int  program_num_16b;
    unsigned char reserved_2_2b;
    unsigned char version_number_5b;
    unsigned char current_next_indicator_1b;
    unsigned int  section_number_8b;
    unsigned char last_section_number_8b;
    unsigned char reserved_3_3b;
    unsigned int  pcr_pid_13b;
    unsigned char reserved_4_4b;
    unsigned int  program_info_length_12b;
    struct PMT_STREAM compent[PMT_STREAM_MAX];

    unsigned int  CRC_32;
};

class PmtDecode {
public:
    /* @brief: 实例化 */
    static PmtDecode* GetInstance();

    /* @brief: 解析pmt信息 */
    bool get_pmt_info(unsigned char *data, struct TS_PMT *pmt_info, unsigned int *index);

private:
    bool check_stream_type(unsigned char stream_type);
};

#endif
