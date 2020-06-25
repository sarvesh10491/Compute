#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define sleeptime 2000        // Main program runtime in ms

int main()
{
    struct timespec tsobj;

    for(int i=0; i<5; i++)
    {
        clock_gettime(CLOCK_MONOTONIC,&tsobj);

        tsobj.tv_sec += sleeptime/1000;                 // adds time to sleep
        tsobj.tv_nsec += sleeptime*1000000ul;
        if(tsobj.tv_nsec > 1000000000ul)
        {
            tsobj.tv_nsec = 0;
            tsobj.tv_sec++;
        }

        printf("\nSleeping for set time, Iteration : %d",i+1);
        clock_nanosleep(CLOCK_MONOTONIC,TIMER_ABSTIME,&tsobj,0);  // sleeps for set period
        printf(" ...Done\n");
    }

    return 0;
}