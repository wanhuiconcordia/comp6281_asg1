#include "fileexplorer.h"
#include "log.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>


char fileExplorerMenu(){
    system("stty raw");
    char selection;
    Selection:
    while(1){
        system("clear");
        printf("\n\r+++++++++++++++++++++++\n\r");
        printf("File Explorer\n\r");
        printf("  1. File List (sorted by name)\n\r");
        printf("  2. File List (sorted by size)\n\r");
        printf("  3. Change Directory\n\r");
        printf("  4. Main Menu\n\r");
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

void fileExplorer(char* currentDir){
    int loopFlag = 1;

    int n = 0;
    struct FileInfo* pFileInfo = NULL;
    while(loopFlag){
        char selection = fileExplorerMenu();
        switch (selection) {
        case '1':
            pFileInfo = getFileInfo(currentDir, &n);
            sortBySize(pFileInfo, n);
            printFileInfos(pFileInfo, n);
            cleanFileInfo(pFileInfo, n);
            depositLog("performed sort file by size.\n");
            system("stty raw");
            printf("Press any key to continue...");
            getchar();
            system("stty cooked");
            break;
        case '2':
            pFileInfo = getFileInfo(currentDir, &n);
            sortByName(pFileInfo, n);
            printFileInfos(pFileInfo, n);
            cleanFileInfo(pFileInfo, n);
            depositLog("performed sort file by name.\n");
            system("stty raw");
            printf("Press any key to continue...");
            getchar();
            system("stty cooked");
            break;
        case '3':
            changeDir(currentDir);
            break;
        case '4':
            loopFlag = 0;
            break;
        default:
            break;
        }
    }
}

void changeDir(char* currentDir){
    char targetPath[1000];
    strcpy(targetPath, currentDir);
    char inputPath[1000];
    printf("\r\nInput Directory:");
    scanf("%s", inputPath);

    if(strcmp(inputPath, ".") == 0){
        return;
    }else if(strcmp(inputPath, "..") == 0){
        resolveUpDir(targetPath);
        chdir(targetPath);
    }else if(strcmp(inputPath, "../") == 0){
        resolveUpDir(targetPath);
        chdir(targetPath);
    }else if(inputPath[0] == '/'){
        strcpy(targetPath, inputPath);
    }else{
        strcat(targetPath, "/");
        strcat(targetPath, inputPath);
    }

    DIR *dir;

    if ((dir = opendir (targetPath)) != NULL) {
        strcpy(currentDir, targetPath);
        depositLog("change dir to:");
        depositLog(targetPath);
        depositLog("\n");
        printf("dir changed to: %s\r\n", targetPath);
        closedir (dir);
    }else{
        printf("%s cannot be accessed.\r\n", targetPath);
        depositLog(targetPath);
        depositLog("cannot be accessed\n");
    }



    system("stty raw");
    printf("Press any key to continue...");
    getchar();
    getchar();
    system("stty cooked");
}

void resolveUpDir(char* targetPath){
    char * p = targetPath + strlen(targetPath) - 1;
    while(p > targetPath){
        if(*p == '/'){
            *p = 0;
            break;
        }
        p--;
    }
}

void cleanFileInfo(struct FileInfo* pFileInfo, int n){
    for(int i = 0; i < n; i++){
        free(pFileInfo[i].name);
    }
    free(pFileInfo);
}

struct FileInfo* getFileInfo(char* path, int* count){
    printf("\r\ncurrent dir:%s\r\n", path);
    *count = 0;
    DIR *dir;
    struct dirent *ent;
    int fileCount = 0;
    if ((dir = opendir (path)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            fileCount++;
        }
        closedir (dir);
    }

    if (fileCount > 0
            && (dir = opendir (path)) != NULL) {
        struct FileInfo* pFileInfo = malloc(fileCount * sizeof(struct FileInfo));
        int i = 0;
        while ((ent = readdir (dir)) != NULL) {
            struct stat st;
            stat(ent->d_name, &st);
            pFileInfo[i].name = malloc(strlen(ent->d_name));
            strcpy(pFileInfo[i].name, ent->d_name);
            if(ent->d_type == 4){
                strcpy(pFileInfo[i].type, "Directory");
            }else if(ent->d_type == 8){
                strcpy(pFileInfo[i].type, "Regular");
            }else if(ent->d_type == 10){
                strcpy(pFileInfo[i].type, "Symlink");
            }else{
                strcpy(pFileInfo[i].type, "Unknown");
            }
            pFileInfo[i].size = st.st_size % 1024;
//            pFileInfo[i].size = st.st_size;
            i++;
        }

        closedir (dir);
        *count = fileCount;
        return pFileInfo;
    } else {
        /* could not open directory */
        perror ("");
        return NULL;
    }
}

void printFileInfos(struct FileInfo* pFileInfo, int count){
    printf ("%-20s%-20s%s\n", "File_Type", "Size (Kb)", "File_Name");
    for(int i = 0; i < count; i++){
        printf ("%-20s%-20d%s\n", pFileInfo[i].type, pFileInfo[i].size, pFileInfo[i].name);
    }
}


int sizeComparator (const struct FileInfo* a, const struct FileInfo* b)
{
  return (a->size - b->size);
}

int nameComparator (const struct FileInfo* a, const struct FileInfo* b){
    return strcmp(a->name, b->name);
}


void sortBySize(struct FileInfo* pFileInfo, const int count){
    qsort(pFileInfo, count, sizeof(struct FileInfo), sizeComparator);
}

void sortByName(struct FileInfo* pFileInfo, const int count){
    qsort(pFileInfo, count, sizeof(struct FileInfo), nameComparator);
}

