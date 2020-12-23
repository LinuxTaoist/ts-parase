/*
********************************************************************************
* @copyright 2020 Shenzhen Chuangwei-RGB Electronics Co.,Ltd.
* File Name   : pmt_process.h
* Author      :
* Version     : V1.0
* Description : 
* Journal     : 2020-10-19 init v1.0
* brief       :
* Others      :
********************************************************************************
*/

#include <stdio.h>
#include <string.h>
#include "pmt_decode.h"
#include "ts_protocol.h"
/* @brief: 实例化 */
PmtDecode* PmtDecode::GetInstance()
{
    static PmtDecode instance;
    return &instance;
}

/* @brief: 解析pmt信息 */
int PmtDecode::get_pmt_info(unsigned char *data, struct TS_PMT *pmt_info)
{
    unsigned char *pos;
    unsigned int crc_32 = 0, i = 0, section_length = 0, crc_start_position = 0;
    struct TS_PMT tmp_pmt_info;

    memset(&tmp_pmt_info, 0, sizeof(struct TS_PMT));

    tmp_pmt_info.table_id_8b = data[0];
    tmp_pmt_info.section_syntax_indicator_1b = data[1] >> 7; 
    tmp_pmt_info.zero_1b = (data[1] & 0x40) >> 6;
    tmp_pmt_info.reserved_1_2b = (data[1] & 0x30) >> 4;
    tmp_pmt_info.section_length_12b = (data[1]&0x0F) << 8 | data[2];
    tmp_pmt_info.program_num_16b = data[3] << 8 | data[4];
    tmp_pmt_info.reserved_2_2b =  (data[5] & 0xC0) >> 6;
    tmp_pmt_info.version_number_5b = (data[5] & 0x3E) >> 1;
    tmp_pmt_info.current_next_indicator_1b = data[5] & 0x01;
    tmp_pmt_info.section_number_8b = data[6];
    tmp_pmt_info.last_section_number_8b = data[7];
    tmp_pmt_info.reserved_3_3b = (data[8] & 0xE0) >> 5;
    tmp_pmt_info.pcr_pid_13b = (data[8] & 0x1F) << 8 | data[9];
    tmp_pmt_info.reserved_4_4b = data[10]  >> 4;
    tmp_pmt_info.program_info_length_12b = (data[10] & 0x0F) << 8 | data[11];

    crc_start_position = tmp_pmt_info.section_length_12b + 2 - PMT_CRC_LENTH;

    tmp_pmt_info.CRC_32 = data[crc_start_position] << 24 
                     | data[crc_start_position] << 16
                     | data[crc_start_position] << 8 
                     | data[crc_start_position];

    if (tmp_pmt_info.CRC_32 == pmt_info->CRC_32) {
        return 0;
    }

    pos = &data[12];  // pointer to stream_type
    section_length = crc_start_position - PROGRAM_INFO_START_POSITION;
    while (section_length > 0) {

        if(check_stream_type(pos[0])) {
            tmp_pmt_info.compent[i].stream_type_8b = pos[0];
            tmp_pmt_info.compent[i].reserved_5_3b = pos[1] >> 5;
            tmp_pmt_info.compent[i].elementary_pid_13b = 
                                            pos[1]&0x1F | pos[2];

            tmp_pmt_info.compent[i].reserved_6_4b = pos[3] >> 4;
            tmp_pmt_info.compent[i].es_info_length_12b = 
                                            (pos[3] & 0x0F)<<8 | pos[4];
        }
    }

    memcpy(pmt_info, &tmp_pmt_info, sizeof(struct TS_PMT));

    return 0;
}

bool PmtDecode::check_stream_type(unsigned char stream_type)
{
    bool bReturn = false;

    switch(stream_type) {
        case PMT_ST_MPEG1_VIDEO: /* ISO/IEC 11172-2 Video */
        case PMT_ST_MPEG2_VIDEO: /* ISO/IEC 13818-2 Video etc. */
        case PMT_ST_MPEG1_AUDIO: /* ISO/IEC 11172-3 Audio */
        case PMT_ST_MPEG2_AUDIO: /* ISO/IEC 13818-3 Audio */
        case PMT_ST_PRIVATE_SECTIONS: /* ISO/IEC 13818-1 private_sections */
        case PMT_ST_PRIVATE_PES_PACKETS: /* ISO/IEC 13818-1 PES packets containing private data */
        case PMT_ST_ATSC_AC_3: /* ATSC AC-3 and EAC-3 0x81, TS generated with VLC Player with AC3 */
        case PMT_ST_DTS: /* HDMV DTS Audio */
        case PMT_ST_MPEG2_AAC_ADTS: /* ISO/IEC 13818-7 Audio with ADTS */
        case PMT_ST_MPEG4_VISUAL: /* ISO/IEC 14496-2 Visual */
        case PMT_ST_MPEG4_AUDIO: /* ISO/IEC 14496-3 Audio */
        case PMT_ST_AVC_VIDEO: /* AVC video ITU-T Rec. H.264, 14496-10 */
        case PMT_ST_HEVC_VIDEO: /* HEVC video H.265 */
        case PMT_ST_13818_6_A:
        case PMT_ST_13818_6_B:
        case PMT_ST_13818_6_C:
        case PMT_ST_13818_6_D:
        {
            bReturn = true;
            break;
        }
    }

    return bReturn;
}



