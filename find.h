#ifndef FINDANDREPLACE_H
#define FINDANDREPLACE_H

#include "find.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*!
 * \brief The Block struct
 * contains the pointer to a text buffer and the pointer to next Block
 */
struct Block{
    char*text;
    struct Block* next;
};

/*!
 * \brief The Paragraph struct
 * contains a list of Blocks and Paragraph index and a pointer to next Paragraph
 */
struct Paragraph{
    struct Block *block;
    unsigned index;
    struct Paragraph* next;
};

/*!
 * \brief findAndReplace
 * \param currentDir
 */
void findAndReplace(char* currentDir);

/*!
 * \brief parseParagraph
 * \return the header pointer of Paragraph list
 */
struct Paragraph* parseParagraph(char*);

/*!
 * \brief raadFile
 * \param fileName
 * \return return the pointer to a text buffer
 */
char* raadFile(char* fileName);

/*!
 * \brief printDoc
 */
void printDoc(struct Paragraph*);

/*!
 * \brief find
 * \param paragraph
 * \param key
 */
void find(struct Paragraph* paragraph, char* key);

/*!
 * \brief replace
 * \param paragraph
 * \param originWord
 * \param replaceWord
 */
void replace(struct Paragraph* paragraph, char* originWord, char* replaceWord);

/*!
 * \brief cleanDoc release the link
 * \param paragraph
 */
void cleanDoc(struct Paragraph* paragraph);

/*!
 * \brief match the first length of chars
 * \param str1
 * \param str2
 * \param length
 * \return 1 if match, otherwise return 0
 */
int match(char* str1, char* str2, int length);

#endif // FINDANDREPLACE_H
