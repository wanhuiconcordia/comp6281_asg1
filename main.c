#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "log.h"
#include "fileExplorer.h"
#include "findandreplace.h"


int main(void)
{
    int loopFlag = 1;
    while(loopFlag){
        char selection = mainMenu();
        switch (selection) {
        case '1':
            fileExplorer();
            break;
        case '2':
            findAndReplace();
            break;
        case '3':
            showLog();
            break;
        case '4':
            loopFlag = 0;
            cleanLog();
            break;
        default:
            break;
        }
    }
    return 0;
}


//   int main(void)
//   {
//       FILE * fp;
//       char * line = NULL;
//       size_t len = 0;
//       ssize_t read;

//       fp = fopen("doc.txt", "r");
//       if (fp == NULL)
//           exit(EXIT_FAILURE);

//       while ((read = getline(&line, &len, fp)) != -1) {
//           printf("Retrieved line of length %zu :\n", read);
//           printf("%s", line);
//       }

//       fclose(fp);
//       if (line)
//           free(line);
//       exit(EXIT_SUCCESS);
//   }
