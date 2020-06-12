#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
   // Allocation shows up in valgrind
   char *p1, *p2;

   p1 = (char *)malloc(0);
   printf("p1 = %p\n", p1);

   p2 = (char *)malloc(0);
   printf("p2 = %p\n", p2);

   free(p1);
   free(p2);

// Heap overflow
// while(1)
// {
//     malloc(0);
// }

   return 0;
}