#include <stdio.h>
#include <stdint.h>
#include "timercb.h"

uint8_t var = 0;
 
/* Custom callback handler definition */
void handler_func(void)
{
    printf("Inside callback handler..\n\n");
    var++;
}

int main(void)
{
    /* Initialize timer callback context including handler */
    timercb_t timerobj;
    timerobj.sleeptime = 5000000;
    timerobj.cbhandler = handler_func;               

    printf("Test program to implement callback\n-----------------------------------\n");

    /* Register callback handler */
    register_callback(&timerobj);

    printf("Waiting in main for callback trigger..\n\n");
    while(!var);     

    printf("Inside main program again..\n");

    return 0;
}