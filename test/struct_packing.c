#include <stdio.h>
#include <stddef.h>

typedef struct
{
    char gender;    // 1 byte + 7 bytes padding
    double sal;     // 8 bytes
    int day;        // 4 bytes
    int month;      // 4 bytes
    int year;       // 4 bytes + 4 bytes padding
}struct1;

typedef struct
{
    int day;        // 4 bytes
    int month;      // 4 bytes
    int year;       // 4 bytes
    char gender;    // 1 byte + 3 bytes padding
    double sal;     // 8 bytes
}struct2;

typedef struct __attribute((packed))__
{
    char gender;    // 1 byte
    double sal;     // 8 bytes
    int day;        // 4 bytes
    int month;      // 4 bytes
    int year;       // 4 bytes
}struct3;

typedef struct
{
    int day:5;      // 5 bits
    int month:4;    // 4 bits
    int year:12;    // 12 bits
    char gender;    // 1 byte + 4 bytes padding
    double sal;     // 8 bytes
}struct4;


// void get_offset(void *stptr,int num)
// {
//     if(num==1){struct1 * tptr = stptr;}
//     else if(num==2){struct2 * tptr = stptr;}
//     else if(num==3){struct3 * tptr = stptr;}
//     else if(num==4){struct4 * tptr = stptr;}

//     printf("gender offset = %lu byte in struct.\n", offsetof(*tptr, gender));
//     printf("sal offset = %lu byte in struct.\n", offsetof(*tptr, sal));
//     printf("day offset = %lu byte in struct.\n", offsetof(*tptr, day));
//     printf("month offset = %lu byte in struct.\n", offsetof(*tptr, month));
//     printf("year offset = %lu byte in struct.\n", offsetof(*tptr, year));
// }


int main()
{
    struct1 obj1;
    printf("\nstruct1 obj size : %lu\n\n",sizeof(obj1));
    // get_offset(&obj1,1);
    printf("gender offset = %lu byte in struct.\n", offsetof(struct1, gender));
    printf("sal offset = %lu byte in struct.\n", offsetof(struct1, sal));
    printf("day offset = %lu byte in struct.\n", offsetof(struct1, day));
    printf("month offset = %lu byte in struct.\n", offsetof(struct1, month));
    printf("year offset = %lu byte in struct.\n", offsetof(struct1, year));
    printf("-----------\n");
    
    struct2 obj2;
    printf("\nstruct2 obj size : %lu\n\n",sizeof(obj2));
    // get_offset(&obj2,2);
    printf("day offset = %lu byte in struct.\n", offsetof(struct2, day));
    printf("month offset = %lu byte in struct.\n", offsetof(struct2, month));
    printf("year offset = %lu byte in struct.\n", offsetof(struct2, year));
    printf("gender offset = %lu byte in struct.\n", offsetof(struct2, gender));
    printf("sal offset = %lu byte in struct.\n", offsetof(struct2, sal));
    printf("-----------\n");
    
    struct3 obj3;
    printf("\nstruct3 obj size : %lu\n\n",sizeof(obj3));
    // get_offset(&obj3,3);
    printf("gender offset = %lu byte in struct.\n", offsetof(struct3, gender));
    printf("sal offset = %lu byte in struct.\n", offsetof(struct3, sal));
    printf("day offset = %lu byte in struct.\n", offsetof(struct3, day));
    printf("month offset = %lu byte in struct.\n", offsetof(struct3, month));
    printf("year offset = %lu byte in struct.\n", offsetof(struct3, year));
    printf("-----------\n");
    
    struct4 obj4;
    printf("\nstruct4 obj size : %lu\n\n",sizeof(obj4));
    // get_offset(&obj4,3);
    // printf("day offset = %lu byte in struct.\n", offsetof(struct4, day));
    // printf("month offset = %lu byte in struct.\n", offsetof(struct4, month));
    // printf("year offset = %lu byte in struct.\n", offsetof(struct4, year));
    printf("gender offset = %lu byte in struct.\n", offsetof(struct4, gender));
    printf("sal offset = %lu byte in struct.\n", offsetof(struct4, sal));
    printf("-----------\n");

    return 0;
}
