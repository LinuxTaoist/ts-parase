/*
********************************************************************************
* Copyright (C) 2021, xiang <dx_65535@163.com>.
* All right reserved.
*
* File Name   : show.h
* Author      :
* Version     : V1.0
* Description : 
* Journal     : 2020-12-28 init v1.0
* brief       :
* Others      :
********************************************************************************
*/

#ifndef __SHOW_H__
#define __SHOW_H__

#include "pmt_decode.h"

class Show {
  public:

    /*
     * @brief: 获取实例化
     */
    static Show* GetInstance();

    /*
     * @brief: 输出pmt表信息
     */
    void pmt_show(struct TS_PMT *pmt_info);
};


#endif //__SHOW_H__
