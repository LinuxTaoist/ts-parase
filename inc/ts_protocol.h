/*
********************************************************************************
* Copyright (C) 2021, xiang <dx_65535@163.com>.
* All right reserved.
*
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
#define NIT_PID 0x0010
#define EIT_PID 0x0012

#define PROGEAM_COUNT 100

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
 * table_id's to identify table sections, S.15 in [ETS468]
 */
typedef enum  {
    PAT_SECTION              =  0x00,  /* PAT, Program Association Table */
    CAT_SECTION              =  0x01,  /* CAT, Conditional Access Table */
    PMT_SECTION              =  0x02,  /* PMT, Program Map Table */
    TSDT_SECTION             =  0x03,  /* Transport Stream Description Table */
    SCENE_SECTION_14496      =  0x04,  /* ISO_IEC_14496_scene_description_section, 13818-1 */
    OBJECT_SECTION_14496     =  0x05,  /* ISO_IEC_14496_object_description_section, 13818-1 */

    /* 0x06 - 0x09: ITU-T Rec. H.222.0 | ISO/IEC 13818-1 reserved */
    /* 0x0A - 0x0D: ISO/IEC 13818-6 */
    /* 0x0E - 0x37: ITU-T Rec. H.222.0 | ISO/IEC 13818-1 reserved */

    /* 0x38 - 0x3F: Defined in ISO/IEC 13818-6 */
    DSMCC_DL_MSG_SECTION     =  0x3B,  /* DSM-CC Download Message: DSI, DII */
    DSMCC_DL_DATA_SECTION    =  0x3C,  /* DSM-CC Download Data, DDB */
    DSMCC_DL_EVENT_SECTION   =  0x3D,  /* DSM-CC Download Event */

    /* 0x40 - 0x7F: ETSI EN 300468 */
    NIT_SECTION_A_N          =  0x40,  /* NIT, Network Information Table, actual network */
    NIT_SECTION_O_N          =  0x41,  /* NIT, Network Information Table, other network */
    SDT_SECTION_A_TS         =  0x42,  /* SDT, Service Description Table, actual TS */
    /* 0x43..0x45 reserved for future use */
    SDT_SECTION_O_TS         =  0x46,  /* SDT, Service Description Table, other TS */
    /* 0x47..0x49 reserved for future use */
    BAT_SECTION              =  0x4A,  /* BAT, Bouquet Association Table */
    /* 0x4B..0x4D reserved for future use */
    EIT_SECTION_A_TS_PF      =  0x4E,  /* EIT, Event Information Table Actual TS, p/f */
    EIT_SECTION_O_TS_PF      =  0x4F,  /* EIT, Event Information Table Other TS,  p/f */
    /* Event Information Section for actual and other TS schedule not defined yet
     * 0x50..0x5F event_information_section - actual_transport_stream, schedule
     * 0x60..0x6F event_information_section - other_transport_stream, schedule
     */
    EIT_SECTION_A_TS_SCHED   =  0x50,  /* high-nibble to mask table_id */
    EIT_SECTION_A_TS_SCHED_PF =  0x5C,  /* EIT, Actual TS, p/f, sched  */
    EIT_SECTION_O_TS_SCHED   =  0x60,  /* high-nibble to mask table_id */
    TDT_SECTION              =  0x70,  /* TDT, Time Date Table */
    RST_SECTION              =  0x71,  /* RST, Running Status Table */
    STUFFING_SECTION         =  0x72,  /* ST */
    TOT_SECTION              =  0x73,  /* TOT, Time Offset Table */
    AIT_SECTION              =  0x74,  /* AIT, added in MHP spec */
    CONTAINER_SECTION        =  0x75,  /* TS102323 */
    RELATED_CONTENT_SECTION  =  0x76,  /* TS102323 */
    CONTENT_ID_SECTION       =  0x77,  /* TS102323, content identifier section */
    MPE_FEC_SECTION          =  0x78,  /* EN301192 */

    /* 0x79..0x7D reserved to MHP for future use */
    RESOLUTION_SECTION       =  0x79,  /* TS102323, resolution notification section */
    DIT_SECTION              =  0x7E,  /* DIT, Discontinuity Information Table */
    SIT_SECTION              =  0x7F,  /* SIT, Selection Information Table */

    /* 0x80 - 0x8F: ETSI ETR 289 */
    LCN_TABLE_SECTION_MEDIASET = 0x85,
    /* 0x90 - 0xFE: private, user defined */

    FORBIDDEN                =  0xFF,  /* used for stuffing bytes, reserved */

    /* METZ user defined table_ids, table_id's are defined in tinclude.h for internal
     * processing in tables library
     */
    NIT_SECTION_SERVICE_LIST =  0xF9,   /* Nita and Nito service list*/
    NIT_SECTION_A_AND_O      =  0xFA,   /* NITa and NITo table filter, used for Homechannel search*/
    SDT_SECTION_A_AND_O_TS   =  0xFB,   /* SDTa and SDTo table filter, used for Homechannel search*/
    EIT_SECTION_SCHED_UPC    =  0xFC,   /* EIT, Actual/Other TS, p/f, sched for UPC Cablecom */
    NIT_SECTION_A_N_SCAN     =  0xFD,   /* used to identify ASTRA_SCAN_NIT_LIST */
    ASIUS_ASTRA_SDT_SECTION  =  0xFE,   /* used to identify ASIUS_ASTRA_SDT_LIST */

} TABLES_TableId_t;


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
} TABLES_PmtStreamType_t;


#endif //__TS_PROTOCOL_H__
