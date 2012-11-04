//-----------------------------------------------------------
#include "libtime.h"
//-----------------------------------------------------------
void nsleep(const struct timespec *req, struct timespec *rem)
{
    struct timespec temp_rem;
    if(nanosleep(req,rem)==-1)	nsleep(rem,&temp_rem);
}
//-----------------------------------------------------------
int msleep(unsigned long milisec)
{
    struct timespec req={0},rem={0};
    time_t sec=(int)(milisec/1000);
    milisec=milisec-(sec*1000);
    req.tv_sec=sec;
    req.tv_nsec=milisec*1000000L;
    nsleep(&req,&rem);
    return 1;
}
//-----------------------------------------------------------
