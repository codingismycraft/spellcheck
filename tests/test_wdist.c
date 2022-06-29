#include <stdio.h>
#include <stdlib.h>
#include <time.h>




#include "wdist.h"

#define FILENAME "/home/john/samples/spellcheck/words-distances.csv"
void process_file(){
    int lines_read=0, correct=0, wrong=0;

    FILE* filePointer;
    int bufferLength = 255;
    char buffer[bufferLength]; /* not ISO 90 compatible */

    filePointer = fopen(FILENAME, "r");

    const char* psz1 = buffer;
    char* psz2 = NULL;
    char* psz3 = NULL;
    char* c = psz1;

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    
    while(fgets(buffer, bufferLength, filePointer)) {
        psz2 = NULL;
        psz3 = NULL;
        c = psz1;
        while(*c != '\n'){
            if (*c == ',') {
                if (psz2 == NULL){
                    *c++ = '\0';
                    psz2 = c;
                } else {
                    *c++ = '\0';
                    psz3 = c;
                }
            }
            ++c;
        }

        const int diff = atoi(psz3);
        const int retrieved = wdist(psz1, psz2, false);

        if (retrieved == diff) correct +=1;
        else wrong +=1;

        if (retrieved != diff){
            //printf(" wrong: %s %s %d %d\n", psz1, psz2, diff, retrieved);
        }

        lines_read +=1;
        if (lines_read >500000) break;
    }

    end = clock();
    
    double duration = ((double) (end - start)) / CLOCKS_PER_SEC;
    //printf("Total lines read: %d  correct: %d wrong %d  \n",lines_read, correct, wrong);

    //printf("fun() took %f seconds to execute \n", duration);
    fclose(filePointer);


    printf("Timing improved algorithm as implemented in plain ANSI C.\n");
    printf("Total lines processed: %d\n", lines_read);
    printf("Duration: %f seconds\n", duration);
    
}

int main(){
    //int x = wdist("HONDA", "HYUNDAI", true);
    //printf("this is a test %d\n", x);
    process_file();
}
