#ifndef FINDANDREPLACE_H
#define FINDANDREPLACE_H


#include <string.h>
#include "findandreplace.h"
#include <stdio.h>
#include <stdlib.h>

struct Paragraph{
    char *text;
    unsigned index;
    struct Paragraph* next;
};

void findAndReplace();
struct Paragraph* parseParagraph(char*);
char* raadFile(char* fileName);
void printDoc(struct Paragraph*);
void find(struct Paragraph* firstParagraph, char* key);
void cleanDoc(struct Paragraph* header);
int match(char* str1, char* str2, int length);

#endif // FINDANDREPLACE_H
