/*
********************************************************************************
* Copyright (C) 2021, xiang <dx_65535@163.com>.
* All right reserved.
*
* File Name   : sky_test_log.h
* Author      :
* Version     : V1.0
* Description : Log file
* Journal     : 2020-10-19 init v1.0
* brief       :
* Others      :
********************************************************************************
*/

#ifndef __SKY_TEST_LOG_H__
#define __SKY_TEST_LOG_H__

#include <string.h>

#ifdef  green
#undef  green
#endif
#define green  "\033[1;49;32m"

#ifdef  red
#undef  red
#endif
#define red    "\033[1;49;31m"

#ifdef  yellow
#undef  yellow
#endif
#define yellow "\033[1;49;33m"

#ifdef  normal
#undef  normal
#endif
#define normal "\033[0m"

#ifdef  DEBUG_LOG_SUPPORT
#undef  DEBUG_LOG_SUPPORT
#endif
#define DEBUG_LOG_SUPPORT

#define filename(x) strrchr(x,'/')?strrchr(x,'/')+1:x

#define PRINT_ERR(format,x...)    \
do{     printf( "[%sERROR%s] [%s:%d] [%s] info: " format, red, normal,    \
                              __FILE__, __LINE__, __func__, ## x); }while(0)

#define PRINT_WARN(format,x...)    \
do{     printf( "[%sWARN%s] [%s:%d] [%s] info: " format, yellow, normal,   \
                     filename(__FILE__), __LINE__, __func__, ## x); }while(0)

#define PRINT_INFO(format,x...)   \
do{     printf(format, ## x); }while(0)

#ifdef  DEBUG_LOG_SUPPORT
#define PRINT_DEBUG(format,x...)  \
do{     printf("[%sDEBUG%s] [%s:%d] [%s] info: " format, green, normal,    \
                     filename(__FILE__), __LINE__, __func__, ## x); }while(0)
#else
#define PRINT_DEBUG(format,x...)
#endif

#endif //__SKY_TEST_LOG_H__


