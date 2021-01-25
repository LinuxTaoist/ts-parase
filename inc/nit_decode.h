/*
********************************************************************************
* Copyright (C) 2021, xiang <dx_65535@163.com>.
* All right reserved.
*
* File Name   : nit_decode.h
* Author      :
* Version     : V1.0
* Description : 
* Journal     : 2020-12-29 init v1.0
* brief       :
* Others      :
********************************************************************************
*/

#ifndef __NIT_DECODE_H__
#define __NIT_DECODE_H__

struct TS_NIT {
    unsigned int  table_id_8b;
    unsigned char section_syntax_indicator_1b;
    unsigned char zero_1b;
    unsigned char reserved_1_2b;
    unsigned int  section_length_12b;
    unsigned int  Network_id_16b;
    unsigned char reserved_2_2b;
    unsigned char version_number_5b;
    unsigned char current_next_indicator_1b;
    unsigned int  section_number_8b;
    unsigned char last_section_number_8b;
    unsigned char reserved_3_4b;
    unsigned char Network_descriptors_length_12b;
    /*--- loop: descriptor ---*/
    unsigned char reserved_4_4b;
    unsigned int  transport_stream_loop_length_12b;
    /*--- loop: descriptor ---*/
    unsigned int CRC_32;
};

class NitDecode {
  public:
    /* @brief: 实例化 */
    static NitDecode* GetInstance();

    /* @brief: 解析pat信息 */
    int get_nit_info(unsigned char *data, struct TS_NIT *nit_info);

};

#endif //__NIT_DECODE_H__
