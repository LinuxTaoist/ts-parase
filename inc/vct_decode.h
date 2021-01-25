/*
********************************************************************************
* Copyright (C) 2021, xiang <dx_65535@163.com>.
* All right reserved.
*
* File Name   : vct_decode.h
* Author      :
* Version     : V1.0
* Description : 
* Journal     : 2020-01-19 init v1.0
* brief       :
* Others      : Analysis of the code stream for the ATSC specification only.
********************************************************************************
*/

#ifndef __VCT_DECODE_H__
#define __VCT_DECODE_H__

#include <iostream>
#include <vector>

struct Descriptor {
    unsigned char  tag;          /*!< descriptor_tag */
    unsigned char  length;       /*!< descriptor_length */
    unsigned char* pData;        /*!< content */
    void *         pDecoded;     /*!< decoded descriptor */
};

struct VctChannel {
    unsigned char short_name[14];
    unsigned char reserved_1_4b;
    unsigned int  major_channel_number_10b;
    unsigned int  minor_channel_number_10b;
    unsigned char modulation_mode_8b;
    unsigned int  carrier_frequency_32b;
    unsigned int  channel_tsid_16b;
    unsigned int  program_number_16b;
    unsigned char etm_location_2b;
    unsigned char access_controlled_1b;
    unsigned char hidden_1b;
    unsigned char reserved_2_2b;
    unsigned char hide_guide_1b;
    unsigned char reserved_3_2b;
    unsigned char service_type_6b;
    unsigned int  source_id_16b;
    unsigned char reserved_4_6b;
    unsigned int  descriptor_length_10b;
    std::vector<Descriptor> descriptor_vector;
};

struct TsAtscVct {
    unsigned int  table_id_8b;
    unsigned char section_syntax_indicator_1b;
    unsigned char priority_indicator_1b;
    unsigned char reserved_1_2b;
    unsigned int  section_length_12b;
    unsigned int  transport_stream_id_16b;
    unsigned char reserved_2_2b;
    unsigned int  version_number_5b;
    unsigned char current_next_indicator_1b;
    unsigned char section_number_8b;
    unsigned char last_section_number_8b;
    unsigned char protocol_version_8b;
    unsigned char num_channels_in_section_8b;
    std::vector<VctChannel>channel_vector;
};

class AtscVctDecode {
  public:
    /* @brief: Single instance interface */
    static AtscVctDecode* GetInstance();

    /* @brief: Resolve the vst table data */
    bool GetVctInfo(unsigned char *data, struct TsAtscVct *pVct);
};


#endif //__VCT_DECODE_H__
