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
#include "debug_code.h"

/* @brief: 实例化 */
PmtDecode* PmtDecode::GetInstance()
{
    static PmtDecode instance;
    return &instance;
}

/* @brief: 解析pmt信息 */
bool PmtDecode::get_pmt_info(unsigned char *data, struct TS_PMT *pmt_info, unsigned int *index)
{
    unsigned char *pos, *pDesc;
    unsigned int crc_32 = 0, i = 0, crc_start_position = 0;
    int program_info_length = 0, section_length = 0, es_info_length = 0, descriptor_length = 0;
    struct TS_PMT tmp_pmt_info;

    memset(&tmp_pmt_info, 0, sizeof(struct TS_PMT));
    tmp_pmt_info.table_id_8b = data[0];
    if (tmp_pmt_info.table_id_8b != PMT_SECTION) {
        return false;
    }

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

    if (tmp_pmt_info.CRC_32 == pmt_info->CRC_32 && pmt_info->CRC_32 != 0) {
        return false;
    }

    /* The length between first stream_type and crc  */
    section_length = tmp_pmt_info.section_length_12b - 13 - program_info_length;

    pos = &data[10];                 //pos pointer to program_info_length
    program_info_length = tmp_pmt_info.program_info_length_12b;

    /* loop: look for program descriptor */
    for(;program_info_length > 0;) {
        PRINT_DEBUG("program_info_length: 0x%x", program_info_length);
    }

    pos += 2 + program_info_length;  // pos pointer to stream_type

    /* loop: look for program audio and video pid */
    for (i = 0; section_length > 0;) {

        /* 检测stream_type类型是否存在 */
        if(check_stream_type(pos[0])) {
            //PRINT_DEBUG("dx_debug: Pos : \n");
            //show_hex(pos, 10);
            tmp_pmt_info.compent[i].stream_type_8b = pos[0];
            tmp_pmt_info.compent[i].reserved_5_3b = pos[1] >> 5;
            tmp_pmt_info.compent[i].elementary_pid_13b = 
                                            pos[1]&0x1F | pos[2];

            tmp_pmt_info.compent[i].reserved_6_4b = pos[3] >> 4;
            tmp_pmt_info.compent[i].es_info_length_12b = 
                                            (pos[3] & 0x0F)<<8 | pos[4];

            es_info_length = tmp_pmt_info.compent[i].es_info_length_12b;

            /* loop: es_info_length 
             * pDesc pointer to descriptor_tag
             */
            for (pDesc = &(pos[5]); es_info_length > 0; ) {
                //PRINT_DEBUG("es_descriptor.descriptor_tag: 0x%x \n", pDesc[0]);
                tmp_pmt_info.compent[i].es_descriptor.descriptor_tag = pDesc[0];
                tmp_pmt_info.compent[i].es_descriptor.descriptor_length = pDesc[1];
                descriptor_length = pDesc[1];

                if (descriptor_length > 0) {
                    tmp_pmt_info.compent[i].es_descriptor.descriptor_data.language_code 
                            = pDesc[2] << 16 | pDesc[3] << 8 | pDesc[4];
                    tmp_pmt_info.compent[i].es_descriptor.descriptor_data.audio_type = pDesc[5];
                }

                es_info_length -= 2 + descriptor_length;
                pDesc += 2 + descriptor_length;
                //PRINT_DEBUG("****** es_info_length: %d \n", es_info_length);
            }
            i++;
            //PRINT_DEBUG("!!!dx_debug: compent index :%d \n", i);
        }

        /* skip the next stream_type */
        section_length -=  5 + ((pos[3] & 0x0F) << 8) + pos[4];
        pos = pos + 5 + ((pos[3] & 0x0F) << 8) + pos[4];
    }

    *index = *index + 1;
    memcpy(pmt_info, &tmp_pmt_info, sizeof(struct TS_PMT));
    //PRINT_DEBUG("tmp_pmt_info: %d\n", *index);
    //show_hex((unsigned char *)&tmp_pmt_info, sizeof(struct TS_PMT));
    return true;
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



