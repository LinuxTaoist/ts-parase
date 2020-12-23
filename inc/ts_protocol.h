/*
********************************************************************************
* @copyright 2020 Shenzhen Chuangwei-RGB Electronics Co.,Ltd.
* File Name   : ts_protocol.h
* Author      :
* Version     : V1.0
* Description : Log file
* Journal     : 2020-10-19 init v1.0
* brief       :
* Others      :
********************************************************************************
*/

#ifndef __TS_PROTOCOL_H__
#define __TS_PROTOCOL_H__

#define PACKET_SYNC_BYTE 0x47
#define PACKET_LENTH_188 188
#define PACKET_LENTH_204 204
#define PACKET_HEADER_LENTH 4

#define EFFECTIVE_START_POSITION 4

#define PAT_PID 0x0000  //13b: 5+8 

#define PROGEAM_COUNT 0X3FFF

struct ORIGIN_DATA {
    unsigned char data[PACKET_LENTH_204];
    unsigned char lenth;
};

struct PACKET_HEADER {
    unsigned char sync_indicator_8b;
    unsigned char error_indicator_1b;
    unsigned char effective_start_indicator_1b;
    unsigned char priority_indicator_1b;
    unsigned int  pid_13b;
    unsigned char scramble_control_2b;
    unsigned char adaptation_contorl_2b;
    unsigned char continue_counter_4b;
}; 

struct PACT_DATA {
    struct PACKET_HEADER header;
    unsigned char buffer[PACKET_LENTH_204-PACKET_HEADER_LENTH];
    unsigned int lenth;
};

enum MSG_STATUS {
    MSG_DEFAULT = 0,
    MSG_BUSY = 1,
    MSG_COMPLETE = 2,
    MSG_STATUS_MAX
};

/* 
 * @brief: PMT_PID 
 * @member-num_16b: 节目号
 * @member-pmt_13b: pmt pid
 */
struct PMT_PID_INFO {
    unsigned int num_16b;
    unsigned int pmt_13b;
};

struct PMT_PID {
    unsigned int count;
    struct PMT_PID_INFO info[PROGEAM_COUNT];

};

extern struct PMT_PID pmt_pid_collection;

/*
 * stream_type coding in PMT, S.45, Table 2-29, [ISO 13818]
 */
typedef enum  {
    PMT_ST_RESERVED             = 0x00,  /* 0x00 ITU-T | ISO/IEC reserved */
    PMT_ST_MPEG1_VIDEO,                  /* 0x01 ISO/IEC 11172-2 Video */
    PMT_ST_MPEG2_VIDEO,                  /* 0x02 ISO/IEC 13818-2 Video etc. */
    PMT_ST_MPEG1_AUDIO,                  /* 0x03 ISO/IEC 11172-3 Audio */
    PMT_ST_MPEG2_AUDIO,                  /* 0x04 ISO/IEC 13818-3 Audio */
    PMT_ST_PRIVATE_SECTIONS,             /* 0x05 ISO/IEC 13818-1 private_sections */
    PMT_ST_PRIVATE_PES_PACKETS,          /* 0x06 ISO/IEC 13818-1 PES packets containing private data */
    PMT_ST_MHEG,                         /* 0x07 */
    PMT_ST_DSM_CC,                       /* 0x08 */
    PMT_ST_H222_1,                       /* 0x09 */
    PMT_ST_13818_6_A,                    /* 0x0A */
    PMT_ST_13818_6_B,                    /* 0x0B */
    PMT_ST_13818_6_C,                    /* 0x0C */
    PMT_ST_13818_6_D,                    /* 0x0D */
    PMT_ST_AUXILIARY,                    /* 0x0E ISO/IEC 13818-1 auxiliary */
    PMT_ST_MPEG2_AAC_ADTS,               /* 0x0F ISO/IEC 13818-7 Audio with ADTS (audio data TS) */
    PMT_ST_MPEG4_VISUAL,                 /* 0x10 ISO/IEC 14496-2 Visual */
    PMT_ST_MPEG4_AUDIO,                  /* 0x11 ISO/IEC 14496-3 Audio */
    PMT_ST_MPEG4_SYS_PES,                /* 0x12 ISO/IEC 14496-1 SL stream or FlexMux carried in PES packets */
    PMT_ST_MPEG4_SYS_14496,              /* 0x13 ISO/IEC 14496-1 SL stream or FlexMux carried in 14496 secs */
    PMT_ST_13818_6_SDP,                  /* 0x14 ISO/IEC 13818-6 Synchronized Download Protocol */
    PMT_ST_META_PES,                     /* 0x15 Metadata carried in PES packets */
    PMT_ST_META_SEC,                     /* 0x16 Metadata carried in metadata_sections */
    PMT_ST_META_DATA_CAROUSEL,           /* 0x17 Metadata carried in 13818-6 data carousel */
    PMT_ST_META_OBJECT_CAROUSEL,         /* 0x18 Metadata carried in 13818-6 object carousel */
    PMT_ST_META_SDP,                     /* 0x19 Metadata carried in 13818-6 synchronized download protocol */
    PMT_ST_MPEG2_IPMP,                   /* 0x1A MPEG-2 IPMP, 13818-11 */
    PMT_ST_AVC_VIDEO,                    /* 0x1B AVC video ITU-T Rec. H.264, 14496-10 Video */
    /* reserved                             0x1C..0x23 */
    PMT_ST_HEVC_VIDEO           = 0x24,  /* 0x24 HEVC (H.265) */
    /* reserved                             0x25..0x7E */
    PMT_ST_IPMP                 = 0x7F,  /* 0x7F  IPMP stream */
    /* user private                         0x80..0xFF */
                                         /* Metz mapped values: */
    PMT_ST_EBU_TELETEXT         = 0x80,  /* Metz: EBU teletext container, PMT_ST_PRIVATE_PES_PACKETS */
    PMT_ST_ATSC_AC_3            = 0x81,  /* AC3 in VLC Player generated TS uses stream_type=0x81 */
    PMT_ST_AC_3 = PMT_ST_ATSC_AC_3,      /* Metz: AC-3 container, PMT_ST_PRIVATE_PES_PACKETS */
    PMT_ST_DTS                  = 0x82,  /* HDMV DTS Audio */
    PMT_ST_SUBTITLES,                    /* Metz: DVB Subtitles, PMT_ST_PRIVATE_PES_PACKETS */
    PMT_ST_E_AC_3,                       /* Metz: E-AC-3 container, PMT_ST_PRIVATE_PES_PACKETS */
    PMT_ST_AAC,
    PMT_ST_HE_AAC,
    PMT_ST_NOT_DEFINED                   /* Metz: init status */
} MZTABLES_PmtStreamType_t;


#endif
