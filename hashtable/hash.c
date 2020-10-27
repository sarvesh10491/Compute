#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define HASHTAB_CAP 50000      // Size of the Hash Table


unsigned long hash_function(char* str) 
{
    unsigned long i = 0;

    for (int j=0; str[j]; j++)
        i += str[j];

    return i % HASHTAB_CAP;
}


int main()
{
    printf("%lu\n",hash_function("HelloWorld"));

    return 0;
}