#include <stdio.h>
#include <stdint.h>
#include "callback.h"

uint8_t var = 0;
 
/* callback function definition goes here */
void my_callback(void)
{
    printf("Inside callback handler..\n");
    var++;
}

int main(void)
{
    /* initialize function pointer to my_callback */
    callback_t ptr_my_callback = my_callback;               

    printf("Test program to implement callback\n\n");

    /* register our callback function */
    register_callback(ptr_my_callback);

    printf("Waiting for callback trigger..\n");
    while(!var);     

    printf("Inside main program\n");

    return 0;
}