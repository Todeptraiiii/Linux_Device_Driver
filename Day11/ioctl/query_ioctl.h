// SPDX-License-Identifier: GPL-2.0
#ifndef QUERY_IOCTL_H
#define QUERY_IOCTL_H
#include <linux/ioctl.h>

typedef struct 
{
    int day, month, year;
}birthday;

#define magic_number 'o'
#define QUERY_GET_VARIABLES _IOR(magic_number,1,struct*)
#define QUERY_CLR_VARIABLES _IO(magic_number,2)
#define QUERY_SET_VARIABLES _IOW(magic_number,3,struct*)


#endif