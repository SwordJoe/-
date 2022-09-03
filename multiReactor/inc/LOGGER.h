#pragma once

#include<stdio.h>

#define LOG(fmt,...)\
do{\
    char buf[1024]={0};\
    int ret = snprintf(buf, 1024, fmt, ##__VA_ARGS__);\
    printf("%s-%s-%d:%s\n",__FILE__, __FUNCTION__, __LINE__, buf);\
} while (0);
