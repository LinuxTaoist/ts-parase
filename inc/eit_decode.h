/*
********************************************************************************
* Copyright (C) 2021, xiang <dx_65535@163.com>.
* All right reserved.
*
* File Name   : eit_decode.h
* Author      :
* Version     : V1.0
* Description : 
* Journal     : 2020-12-29 init v1.0
* brief       :
* Others      :
********************************************************************************
*/

#ifndef __EIT_DECODE_H__
#define __EIT_DECODE_H__

class EitDecode {
  public:
    /* @brief: 实例化 */
    static EitDecode* GetInstance();

    /* @brief: 解析pat信息 */
    int get_eit_info(unsigned char *data);

};

#endif //__EIT_DECODE_H__
