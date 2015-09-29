#ifndef LIST_H
#define LIST_H
#include <stdlib.h>     /* qsort */
struct FileInfo{
    char type[10];
    unsigned long size;
    char* name;
};

char fileExplorerMenu();
void fileExplorer(char*);
struct FileInfo* getFileInfo(char* path, int* count);
void printFileInfos(struct FileInfo* fileInfo, int count);
int sizeComparator (const struct FileInfo* a, const struct FileInfo* b);
int nameComparator (const struct FileInfo* a, const struct FileInfo* b);
void sortBySize(struct FileInfo* pFileInfo, const int count);
void sortByName(struct FileInfo* pFileInfo, const int count);
void cleanFileInfo(struct FileInfo* fileInfo, int n);
void changeDir(char* currentDir);
void resolveUpDir(char* targetPath);

#endif // LIST_H
