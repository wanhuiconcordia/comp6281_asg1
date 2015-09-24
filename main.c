#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "log.h"
#include "fileExplorer.h"
#include "findandreplace.h"


int main(void)
{
    int loopFlag = 1;
    while(loopFlag){
        char selection = mainMenu();
        switch (selection) {
        case '1':
            fileExplorer();
            break;
        case '2':
            findAndReplace();
            break;
        case '3':
            showLog();
            break;
        case '4':
            loopFlag = 0;
            cleanLog();
            printf("\r\n");
            break;
        default:
            break;
        }
    }
    return 0;
}
