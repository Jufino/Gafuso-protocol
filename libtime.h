#ifndef _LIBTIME_H
#define _LIBTIME_H
//-----------------------------------------------------------
#include <stdio.h>
#include <time.h>
#include <signal.h>
//-----------------------------------------------------------
void nsleep(const struct timespec *req, struct timespec *rem);
int msleep(unsigned long milisec);
//-----------------------------------------------------------
#endif
