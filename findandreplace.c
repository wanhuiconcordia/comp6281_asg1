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

    FILE * pFile = fopen (fileName , "r" );

    if (pFile == NULL) {
        perror ("");
    }else{
        char * line = NULL;
        size_t len = 0;
        ssize_t read;
        unsigned paragraphIndex = 1;
        struct Paragraph* header = malloc(sizeof(struct Paragraph));
        struct Paragraph* paragraph = header;
        while ((read = getline(&line, &len, pFile)) != -1) {
            paragraph->next = malloc(sizeof(struct Paragraph));
            paragraph = paragraph->next;
            paragraph->text = line;
            paragraph->paragraphIndex = paragraphIndex++;
        }
        paragraph->next = NULL;
        displayParagraph(header->next);
        //find(header->next, originWord);
        fclose (pFile);


    }
    system("stty raw");
    printf("\r\nPress any key to continue...");
    getchar();
    getchar();
    system("stty cooked");
    printf("\n\n return from findAndReplace.\n");
}

void displayParagraph(struct Paragraph* firstParagraph){
    struct Paragraph* currentParagraph = firstParagraph;
    while(currentParagraph){
        printf("%s", currentParagraph->text);

        currentParagraph = currentParagraph->next;

    }
}

void find(struct Paragraph* firstParagraph, char * key){
    struct Paragraph* currentParagraph = firstParagraph;
    printf("OLD  FILE:");
    while(currentParagraph){
        printf("Try to find [%s] from :%s\n", key, currentParagraph->text);
        for(int i = 0; i < strlen(currentParagraph->text) - strlen(key); i++){
            if(match(currentParagraph->text + i, key, strlen(key))){
                printf("%s\n", currentParagraph->text);
                break;
            }
        }
        printf("before paragraph = paragraph->next;\n");
        currentParagraph = currentParagraph->next;
        printf("after paragraph = paragraph->next;\n");
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

void findAndReplace_backup(){
    printf("\n\rFile Name:");
    char fileName[200];
    scanf("%s", fileName);

    printf("Enter text to find:");
    char originWord[200];
    scanf("%s", originWord);

    printf("Replace text with:");
    char replaceWord[200];
    scanf("%s", replaceWord);

    FILE * pFile = fopen (fileName , "r" );

    if (pFile == NULL) {
        perror ("");
    }else{
        // obtain file size:
        fseek (pFile , 0 , SEEK_END);
        long lSize = ftell (pFile);
        rewind (pFile);

        // allocate memory to contain the whole file:
        char* buffer = (char*) malloc (sizeof(char)*lSize);
        if (buffer == NULL) {
            perror ("");
            fclose (pFile);
        }else{
            // copy the file into the buffer:
            size_t result = fread (buffer, 1, lSize, pFile);

            if (result == lSize) {
                for(int i = 0; i < result; i++){
                    printf("%4d", buffer[i]);
                    if(buffer[i] == 10){
                        printf("\n---10---\n");
                    }else if(buffer[i] == 13){
                        printf("\n---13---\n");
                    }
                }
                /* the whole file is now loaded in the memory buffer. */
                struct WordInfo* wordInfo = parseWordInfo(buffer, buffer + lSize - 1);


                cleanDoc(wordInfo);

            }else{
                //fputs ("Reading error", stderr);
                fclose (pFile);
                free (buffer);
                perror ("");
            }
        }
    }
    system("stty raw");
    printf("\r\nPress any key to continue...");
    getchar();
    getchar();
    system("stty cooked");
}


struct WordInfo* parseWordInfo(char* buffer, char *docEnd){
    struct WordInfo* newWordInfo = malloc(sizeof(struct WordInfo));
    struct WordInfo* header = newWordInfo;
    int status = WORD_STATUS;
    char *cursor = buffer, *keyStart = buffer;
    int isWordFinished = 0;
    int lineIndex = 1;
    newWordInfo->lineIndex = lineIndex;
    while(cursor != docEnd){
        if(*cursor == 10){
            status = WORD_STATUS;
            isWordFinished = 1;
            lineIndex++;
        }else if(*cursor == '\t'
                 || *cursor == ' '){
            if(status == WORD_STATUS){
                status = SPLITTER_STATUS;
                isWordFinished = 1;
            }
        }else{
            if(status == SPLITTER_STATUS){
                status = WORD_STATUS;
                isWordFinished = 1;
            }
        }

        if(isWordFinished){
            //record the word
            if(cursor > keyStart){
                //record the word and add to struct
                int size = cursor - keyStart;
                newWordInfo->word = malloc(size + 1);
                memcpy(newWordInfo->word, keyStart, size);
                newWordInfo->word[size] = 0;

                newWordInfo->next = malloc(sizeof(struct WordInfo));
                newWordInfo = newWordInfo->next;
                newWordInfo->lineIndex = lineIndex;
            }
            keyStart = cursor;
            isWordFinished = 0;
        }
        cursor++;
    }
    if(cursor > keyStart){
        //record the word and add to struct
        int size = cursor - keyStart;
        newWordInfo->word = malloc(size + 1);
        memcpy(newWordInfo->word, keyStart, size);
        newWordInfo->word[size] = 0;
        newWordInfo->next = NULL;
    }
    return header;
}

//clean up all the malloced memory
void cleanDoc(struct WordInfo* wordInfo){
    struct WordInfo* currentWordInfo = wordInfo;
    while(currentWordInfo){
        if(currentWordInfo->word){
            printf("(line:%d[%d])%s", currentWordInfo->lineIndex, currentWordInfo->word[0], currentWordInfo->word);
            free(currentWordInfo->word);
        }
        if(currentWordInfo->replacedWord){
            free(currentWordInfo->replacedWord);
        }
        wordInfo = wordInfo->next;
        free(currentWordInfo);
        currentWordInfo = wordInfo;
    }
}
