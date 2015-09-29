#ifndef LIST_H
#define LIST_H
#include <stdlib.h>

/*!
 * \brief The FileInfo struct
 * contains a basic file infomation: type, size and name
 */
struct FileInfo{
    char type[10];
    unsigned long size;
    char* name;
};

/*!
 * \brief fileExplorerMenu
 * \return a input charactor
 */
char fileExplorerMenu();

/*!
 * \brief fileExplorer
 * The entry of this functionality
 */
void fileExplorer(char*);

/*!
 * \brief getFileInfo
 * \param path
 * \param count
 * \return the header of FileInfo list
 */
struct FileInfo* getFileInfo(char* path, int* count);

/*!
 * \brief printFileInfos
 * \param fileInfo
 * \param count
 */
void printFileInfos(struct FileInfo* fileInfo, int count);

/*!
 * \brief sizeComparator
 * \param a
 * \param b
 * \return 0, negitive or positive number
 */
int sizeComparator (const struct FileInfo* a, const struct FileInfo* b);

/*!
 * \brief nameComparator
 * \param a
 * \param b
 * \return 0, negitive or positive number
 */
int nameComparator (const struct FileInfo* a, const struct FileInfo* b);

/*!
 * \brief sortBySize
 * \param pFileInfo
 * \param count
 */
void sortBySize(struct FileInfo* pFileInfo, const int count);

/*!
 * \brief sortByName
 * \param pFileInfo
 * \param count
 */
void sortByName(struct FileInfo* pFileInfo, const int count);

/*!
 * \brief cleanFileInfo release the list
 * \param fileInfo
 * \param n
 */
void cleanFileInfo(struct FileInfo* fileInfo, int n);

/*!
 * \brief changeDir
 * \param currentDir
 */
void changeDir(char* currentDir);

/*!
 * \brief resolveUpDir
 * \param targetPath
 */
void resolveUpDir(char* targetPath);

#endif // LIST_H
