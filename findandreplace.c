#include "findandreplace.h"
#include "tools.h"


void findAndReplace(){
    printf("\n\rFile Name:");
    char fileName[200];
    scanf("%s", fileName);

    printf("Enter text to find:");
    char originWord[200];
    scanf("%s", originWord);

    printf("Replace text with:");
    char replaceWord[200];
    scanf("%s", replaceWord);

    char* docText = raadFile(fileName);
    if(docText){
        struct Paragraph* header = parseParagraph(docText);
        free(docText);
//        printDoc(header);
        find(header->next, originWord);
//        replace(header->next, originWord, replaceWord);
        cleanDoc(header);
    }

    system("stty raw");
    printf("\r\nPress any key to continue...");
    getchar();
    getchar();
    system("stty cooked");
    printf("\n\n return from findAndReplace.\n");
}

struct Paragraph* parseParagraph(char* docText){
    struct Paragraph* header = calloc(1, sizeof(struct Paragraph));
    struct Paragraph* paragraph = header;
    if(strlen(docText) > 0){
        int paraIndex = 1;
        char* paraStart, * paraEnd;
        paraStart = paraEnd = docText;
        while(*paraEnd){
            if(*paraEnd == '\n'){
                paragraph->next = calloc(1, sizeof(struct Paragraph));
                paragraph = paragraph->next;
                paragraph->index = paraIndex;
                paragraph->next = NULL;
                paragraph->block = calloc(1, sizeof(struct Block));
                paragraph->block->text = calloc((paraEnd - paraStart) + 2, sizeof(char));
                memcpy(paragraph->block->text, paraStart, paraEnd - paraStart + 1);
                paraStart = paraEnd + 1;
                paraIndex++;
            }
            ++paraEnd;
        }
    }
    return header;
}

char* raadFile(char* fileName){
    char* buffer = NULL;
    FILE * pFile = fopen (fileName , "r" );

    if (pFile == NULL) {
        perror ("");
    }else{
        // obtain file size:
        fseek (pFile , 0 , SEEK_END);
        size_t lSize = ftell (pFile);
        rewind (pFile);
        // allocate memory to contain the whole file:
        buffer = (char*) calloc (lSize + 1, sizeof(char));
        if (buffer == NULL) {
            perror ("");
        }else{
            // copy the file into the buffer:
            size_t result = fread (buffer, 1, lSize, pFile);

            if (result != lSize) {
                free (buffer);
                buffer = NULL;
                perror ("");
            }
            buffer[lSize] = 0;
            /*else the whole file is now loaded in the memory buffer. */
        }
        fclose (pFile);
    }
    return buffer;
}

void printDoc(struct Paragraph* paragraph){
    while(paragraph){
        if(paragraph->block && paragraph->block->text){
            printf("%s", paragraph->block->text);
        }
        paragraph = paragraph->next;
    }
}

void find(struct Paragraph* paragraph, char * originWord){
    struct Paragraph* currentParagraph = paragraph;
    printf("OLD  FILE:\n");
    while(currentParagraph){
        if(paragraph->block && paragraph->block->text){
            int offset = strlen(currentParagraph->block->text) - strlen(originWord);
            if(offset > 0){
                for(unsigned i = 0; i <= offset; i++){
                    if(match(currentParagraph->block->text + i, originWord, strlen(originWord))){
                        printf("line[%d]\t%s\n", currentParagraph->index, currentParagraph->block->text);
                        break;
                    }
                }
            }
        }
        currentParagraph = currentParagraph->next;
    }
}


void replace(struct Paragraph* firstParagraph, char* originWord, char* replaceWord){
    struct Paragraph* currentParagraph = paragraph;
    printf("OLD  FILE:\n");
    while(currentParagraph){
        if(paragraph->block && paragraph->block->text){
            int offset = strlen(currentParagraph->block->text) - strlen(originWord);
            if(offset > 0){
                for(unsigned i = 0; i <= offset; i++){
                    if(match(currentParagraph->block->text + i, originWord, strlen(originWord))){
                        printf("line[%d]\t%s\n", currentParagraph->index, currentParagraph->block->text);
                        break;
                    }
                }
            }
        }
        currentParagraph = currentParagraph->next;
    }
}

int match(char* str1, char* str2, int length){
    for(int i = 0; i < length; i++){
        if((*(str1 + i)) ^ (*(str2 + i))){
            return 0;
        }
    }
    return 1;
}

//clean up all the malloced memory
void cleanDoc(struct Paragraph* paragraph){
    struct Paragraph* currentParagraph = paragraph;
    while(currentParagraph){
        if(currentParagraph->block){
            if(currentParagraph->block->text){
                free(currentParagraph->block->text);
                currentParagraph->block->text = NULL;
            }
            free(currentParagraph->block);
            currentParagraph->block = NULL;
        }
        currentParagraph = currentParagraph->next;
        free(paragraph);
        paragraph = currentParagraph;
    }
}


