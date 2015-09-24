#ifndef LOG_H
#define LOG_H
#include <stdlib.h>

static int capacity = 0;
static int size = 0;
static char * data;

void depositLog(char *str);
void showLog();
void cleanLog();
void getTimeStr(char* buffer, int size);

#endif // LOG_H
