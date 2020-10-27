#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *cmdexec(char *srcCmd) 
{
    char *buf = malloc(100);
    int i = 0;
    FILE *p = popen(srcCmd,"r");
    char *tmp;

    if (p){
        while (!feof(p) && (i < 99) )
        {
            fread(&buf[i++],1,1,p);
        }
        i--;
        buf[i] = '\0';
        pclose(p);

        return buf;


        // char ch;
        // // printf("%lu ", strlen(buf));

        // while((ch=fgetc(p)) != EOF){
        //     buf[i++] = ch;
        //     // putchar(ch);
        // }
        // i--;
        // buf[i] = '\0';

        // tmp = malloc(strlen(buf));
        // strcpy(tmp,buf);
        // // printf("%lu\n", strlen(tmp));
        // pclose(p);
        
        // return tmp;
    }
    else{
        return NULL;
    }
}

int main()
{  
    char *cmd1 = cmdexec("whoami");
    char *cmd2 = cmdexec("hostname");
    // char * cmd1 = "abcd";
    // char * cmd2 = "qwerty";

    printf("%s | %s", cmd1, cmd2);

    return 0;
}