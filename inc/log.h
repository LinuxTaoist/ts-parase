/*
********************************************************************************
* @copyright 2020 Shenzhen Chuangwei-RGB Electronics Co.,Ltd.
* File Name   : log.h
* Author      :
* Version     : V1.0
* Description : Log file
* Journal     : 2020-10-19 init v1.0
* brief       :
* Others      :
********************************************************************************
*/

#ifndef __LOG_H__
#define __LOG_H__

#include <string.h>

static char green[]  = "\033[1;49;32m";
static char red[]    = "\033[1;49;31m";
static char normal[] = "\033[0m";

#define DEBUG_LOG_SUPPORT

#define filename(x) strrchr(x,'/')?strrchr(x,'/')+1:x

#define PRINT_ERR(format,x...)    \
do{ printf( "[%sERROR%s] [%s:%d] [%s] info: " format, red, normal,    \
                                 __FILE__, __LINE__, __func__, ## x); }while(0)

#define PRINT_INFO(format,x...)   \
do{ printf(format, ## x); }while(0)

#ifdef DEBUG_LOG_SUPPORT
#define PRINT_DEBUG(format,x...)  \
do{ printf("[%sDEBUG%s] [%s:%d] [%s] info: " format, green, normal,   \
                     filename(__FILE__), __LINE__, __func__, ## x); }while(0)
#else
#define PRINT_DEBUG(format,x...)
#endif


#endif


