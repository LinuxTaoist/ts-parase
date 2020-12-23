/*
********************************************************************************
* @copyright 2020 Shenzhen Chuangwei-RGB Electronics Co.,Ltd.
* File Name   : pat_process.h
* Author      :
* Version     : V1.0
* Description : 
* Journal     : 2020-10-19 init v1.0
* brief       :
* Others      :
********************************************************************************
*/

#ifndef __PAT_DECODE_H__
#define __PAT_DECODE_H__

#define PAT_PREV_LENTH     6u
#define PAT_CRC_LENTH      4u
#define PAT_LENTN_POSITION 2u
#define PAT_REGULATE_LENTH 10u  //6 + CRC(4)

struct TS_PAT {
    unsigned int  table_id_8b;
    unsigned char section_syntax_indicator_1b;
    unsigned char zero_1b;
    unsigned char reserved_1_2b;
    unsigned int  section_length_12b;
    unsigned int  transport_stream_id_16b;
    unsigned char reserved_2_2b;
    unsigned char version_number_5b;
    unsigned char current_next_indicator_1b;
    unsigned int  section_number_8b;
    unsigned char last_section_number_8b;
    /* --- 节目信息 ---*/
    unsigned int CRC_32;
};

class PatDecode {
public:
    /* @brief: 实例化 */
    static PatDecode* GetInstance();

    /* @brief: 解析pat信息 */
    int get_pat_info(unsigned char *data);

    /* @brief: 获取当前帧CRC */
    unsigned int get_crc();
};

#endif
