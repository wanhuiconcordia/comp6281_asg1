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


void findAndReplace();

struct WordInfo* parseWordInfo(char* buffer, char *docEnd);

void cleanDoc(struct WordInfo* header);

#endif // FINDANDREPLACE_H
