#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "wdist.h"

#define FILENAME "/home/john/samples/spellcheck/words-distances.csv"
#define BUFFER_LENGTH 255
#define MAX_LINES_TO_PROCESS 500000

void process_file(){
    int lines_read=0, correct=0, wrong=0;
    FILE* input;
    char buffer[BUFFER_LENGTH]; 
    input = fopen(FILENAME, "r");
    const char* psz1 = buffer;
    char* psz2 = NULL;
    char* psz3 = NULL;
    char* c = (char*)psz1;
    clock_t start, end;
    start = clock();
    while(fgets(buffer, BUFFER_LENGTH, input)) {
        psz2 = psz3 = NULL;
        c = (char*)psz1;
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
        const int retrieved = word_distance(psz1, psz2);

        if (retrieved == diff) 
            correct +=1;
        else 
            wrong +=1;

        if (retrieved != diff){
            //printf(" wrong: %s %s %d %d\n", psz1, psz2, diff, retrieved);
        }

        lines_read +=1;
        if (lines_read > MAX_LINES_TO_PROCESS) 
            break;
    }
    end = clock();
    double duration = ((double) (end - start)) / CLOCKS_PER_SEC;
    fclose(input);

    printf("Timing improved algorithm as implemented in plain ANSI C.\n");
    printf("Total lines processed .: %d\n", lines_read);
    printf("Correct ...............: %d\n",correct);
    printf("Wrong  ................: %d\n",wrong);
    printf("Duration: %f seconds\n", duration);
}

int main(){
    process_file();
}

int main2(int argc, char** argv) {
    const int d = word_distance("HONDA", "HYUNDAI");
    printf("Dist: %d\n", d);
    //cout << " this is a test" << d << endl;
    return 0;
}