#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define True 1   // Return Value 
#define False -1 // Return Value

int n;
FILE * fp = fopen("../ironman.jpg", "wb+");
if (fp  == NULL){
    printf("reading file error\n");
    exit(1);
}
fseek(fp, 0, SEEK_END);
long filesize = ftell(fp);
fclose (fp);
printf ("Size of my file: %ld bytes.\n",filesize);