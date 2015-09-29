#ifndef FINDANDREPLACE_H
#define FINDANDREPLACE_H

#include "find.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct Block{
    char*text;
    struct Block* next;
};

struct Paragraph{
    struct Block *block;
    unsigned index;
    struct Paragraph* next;
};


void findAndReplace(char* currentDir);
struct Paragraph* parseParagraph(char*);
char* raadFile(char* fileName);
void printDoc(struct Paragraph*);
void find(struct Paragraph* paragraph, char* key);
void replace(struct Paragraph* paragraph, char* originWord, char* replaceWord);
void cleanDoc(struct Paragraph* paragraph);
int match(char* str1, char* str2, int length);

#endif // FINDANDREPLACE_H
