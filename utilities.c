#include <stdio.h>
#include <stdlib.h>
#include "log.h"
#include "fileexplorer.h"
#include "find.h"


char mainMenu(){
    system("stty raw");
    char selection;

    while(1){
        system("clear");
        printf("\n\r+++++++++++++++++++++++\n\r");
        printf("Sys Admin Utility\n\r");
        printf("  1. File Explorer\n\r");
        printf("  2. Find and Replace\n\r");
        printf("  3. Show the Log\n\r");
        printf("  4. Exit\n\r");
        printf("+++++++++++++++++++++++\n\r");
        printf("Selection:");
        selection = getchar();
        if(selection >= '1' && selection <= '4'){
            break;
        }
    }
    system("stty cooked");
    return selection;
}

int main(void)
{
    char currentDir[1000];
    realpath(".", currentDir);

    int loopFlag = 1;
    while(loopFlag){
        char selection = mainMenu();
        switch (selection) {
        case '1':
            fileExplorer(currentDir);
            break;
        case '2':
            findAndReplace(currentDir);
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
