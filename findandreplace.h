#ifndef FINDANDREPLACE_H
#define FINDANDREPLACE_H


#include <string.h>
#include "findandreplace.h"
#include <stdio.h>
#include <stdlib.h>

struct WordInfo{
    char* word;
    char* replacedWord;
    unsigned lineIndex;
    struct WordInfo* next;
};

struct Paragraph{
    char *text;
    unsigned paragraphIndex;
    struct Paragraph* next;
};

void findAndReplace();

void find(struct Paragraph* firstParagraph, char* key);

void displayParagraph(struct Paragraph* firstParagraph);

int match(char* str1, char* str2, int length);
void findAndReplace_backup();

struct WordInfo* parseWordInfo(char* buffer, char *docEnd);

void cleanDoc(struct WordInfo* header);



#endif // FINDANDREPLACE_H
