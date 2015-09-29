#ifndef LOG_H
#define LOG_H
#include <stdlib.h>

static int capacity = 0;
static int size = 0;
static char * data;

/*!
 * \brief depositLog to a text buffer
 * \param str
 */
void depositLog(char *str);

/*!
 * \brief showLog
 */
void showLog();

/*!
 * \brief cleanLog
 * release alloced memory
 */
void cleanLog();

/*!
 * \brief getTimeStr
 * \param buffer
 * \param size
 */
void getTimeStr(char* buffer, int size);

#endif // LOG_H
