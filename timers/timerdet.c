#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main()
{
    struct timespec ts;

    // The clock_getres function returns the clock resolution.
    clock_getres(CLOCK_REALTIME, &ts);

    printf("\nClock resolution is : %ld seconds | %ld nanoseconds \n", ts.tv_sec, ts.tv_nsec);

    // Both the time and clock_gettime functions return the value of the systemwide clock as the number of elapsed seconds since the Epoch.
    printf("\ntime() returns : %ld seconds\n", time(NULL));
    
    clock_gettime(CLOCK_REALTIME, &ts);
    printf("\nclock_gettime() returns : %ld seconds and %ld nanoseconds\n", ts.tv_sec, ts.tv_nsec);

    return 0;
}