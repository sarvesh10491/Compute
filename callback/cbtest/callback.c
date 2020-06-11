#include <stdio.h>
 #include <unistd.h>
#include "callback.h"
 
/* registration goes here */
void register_callback(callback_t ptr_reg_callback)
{
    printf("Callback registered..\n");

    usleep(5000000);

    /* calling our callback function my_callback */
    (*ptr_reg_callback)();                                  
}