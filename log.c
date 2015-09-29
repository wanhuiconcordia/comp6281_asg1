#include "log.h"
#include <string.h>
#include <time.h>

void depositLog(char *str){
    char timeBuffer[80];
    getTimeStr(timeBuffer, sizeof(timeBuffer));
    int requiredCapacity = strlen(timeBuffer) + strlen(str) + size;
    if(requiredCapacity >= capacity){
        while(requiredCapacity >= capacity){
            capacity *= 2;
            capacity++;
        }
        char * newData = malloc(capacity);
        if(size > 0){
            strcpy(newData, data);
            free(data);
        }
        data = newData;
    }
    strcpy(data + size, timeBuffer);
    size += strlen(timeBuffer);
    strcpy(data + size, str);
    size += strlen(str);
}

void showLog(){
    if(size > 0){
        printf("\r\n%s\r\n", data);
    }
    system("stty raw");
    printf("Press any key to continue...");
    getchar();
    system("stty cooked");
}

void cleanLog(){
    free(data);
    size = 0;
    capacity = 0;
}

void getTimeStr(char* buffer, int size)
{
    time_t     now = time(0);
    struct tm  tstruct;
    tstruct = *localtime(&now);
    strftime(buffer, size, "%F %T\t", &tstruct);
}
