#include "findandreplace.h"

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
//        find(header->next, originWord);
        replace(header->next, originWord, replaceWord);
        printDoc(header);
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
        struct Block* currentBlock = paragraph->block;
        while(currentBlock){
            if(currentBlock->text){
                printf("%s", currentBlock->text);
            }
            currentBlock = currentBlock->next;
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


void replace(struct Paragraph* paragraph, char* originWord, char* replaceWord){
    struct Paragraph* currentParagraph = paragraph;

    while(currentParagraph){
        struct Block* currentBlock = currentParagraph->block;
        while(currentBlock){
            if(currentBlock->text){
                int offset = strlen(currentBlock->text) - strlen(originWord);
                if(offset > 0){
                    for(unsigned i = 0; i <= offset; i++){
                        if(match(currentBlock->text + i, originWord, strlen(originWord))){
                            struct Block* newBlock1 = calloc(1, sizeof(struct Block));
                            if(i == 0){
                                newBlock1->text = calloc(strlen(currentBlock->text) - strlen(originWord) + 1, sizeof(char));
                                strcpy(newBlock1->text, currentBlock->text + strlen(originWord));
                                strcpy(currentBlock->text, replaceWord);
                                newBlock1->next = currentBlock->next;
                                currentBlock->next = newBlock1;
                            }else{
                                newBlock1->text = calloc(strlen(replaceWord) + 1, sizeof(char));
                                strcpy(newBlock1->text, replaceWord);
                                if(i == offset){
                                    currentBlock->text[offset] = 0;
                                    newBlock1->next = currentBlock->next;
                                    currentBlock->next = newBlock1;
                                }else{
                                    struct Block* newBlock2  = calloc(1, sizeof(struct Block));
                                    newBlock2->text = calloc(strlen(currentBlock->text) - strlen(originWord) - i + 1, sizeof(char));
                                    strcpy(newBlock2->text, currentBlock->text + i + strlen(originWord));
                                    newBlock2->next = currentBlock->next;
                                    newBlock1->next = newBlock2;
                                    currentBlock->text[i] = 0;
                                    currentBlock->next = newBlock1;
                                    currentBlock = currentBlock->next;
                                }
                            }
                            break;
                        }
                    }
                }
            }
            currentBlock = currentBlock->next;
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
        struct Block* currentBlock = currentParagraph->block;
        struct Block* block = currentBlock;
        while(currentBlock){
            if(currentBlock->text){
                free(currentBlock->text);
            }
            currentBlock = currentBlock->next;
            free(block);
            block = currentBlock;
        }
        currentParagraph = currentParagraph->next;
        free(paragraph);
        paragraph = currentParagraph;
    }
}


