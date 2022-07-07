#include "spellcheck.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>

#define FILENAME "/home/john/samples/spellcheck/words-distances.csv"
#define BUFFER_LENGTH 255
#define MAX_LINES_TO_PROCESS 500000
#define LONG_DICT "/home/john/repos/spellcheck/spellcheck/static/english.txt"
#define SHORT_DICT "/home/john/repos/spellcheck/spellcheck/static/shortdict.txt"

using namespace std;

void process_file() {
    int lines_read = 0, correct = 0, wrong = 0;
    FILE* input;
    char buffer[BUFFER_LENGTH];
    input = fopen(FILENAME, "r");
    const char* psz1 = buffer;
    char* psz2 = NULL;
    char* psz3 = NULL;
    char* c = (char*) psz1;
    clock_t start, end;
    start = clock();
    while (fgets(buffer, BUFFER_LENGTH, input)) {
        psz2 = psz3 = NULL;
        c = (char*) psz1;
        while (*c != '\n') {
            if (*c == ',') {
                if (psz2 == NULL) {
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
            correct += 1;
        else
            wrong += 1;

        if (retrieved != diff) {
            //printf(" wrong: %s %s %d %d\n", psz1, psz2, diff, retrieved);
        }

        lines_read += 1;
        if (lines_read > MAX_LINES_TO_PROCESS)
            break;
    }
    end = clock();
    double duration = ((double) (end - start)) / CLOCKS_PER_SEC;
    fclose(input);

    printf("Timing improved algorithm as implemented in plain ANSI C.\n");
    printf("Total lines processed .: %d\n", lines_read);
    printf("Correct ...............: %d\n", correct);
    printf("Wrong  ................: %d\n", wrong);
    printf("Duration: %f seconds\n", duration);
}

int main() {
    int ret_code = 0;

    if (ret_code) {
        printf("error %d\n", ret_code);
        exit(ret_code);
    }

    clock_t start, end;
    start = clock();
    ret_code = set_dict(LONG_DICT);
    //ret_code = set_dict(SHORT_DICT);
    if (ret_code <= 0) {
        printf("error %d\n", ret_code);
        exit(ret_code);
    }
    end = clock();
    double duration = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Duration: %f seconds\n", duration);

    char matches[MAX_MATCHES][MAX_WORD_LENGTH];

    for (int i = 0; i < 1000; ++i) {
        int counter = find_matches("consioys", matches);
        for (int i = 0; i < counter; ++i){
            //cout << matches[i] << endl;
	}
	if (i % 100 == 0) cout << i << endl;
    }
}

int main1() {
    process_file();
    char matches[MAX_MATCHES][MAX_WORD_LENGTH];
    int i = find_matches("junk", matches);
    printf("matches: %d \n", i);
    set_dict("/home/john/repos/spellcheck/spellcheck/static/english.txt");
}

int main2(int argc, char** argv) {
    const int d = word_distance("HONDA", "HYUNDAI");
    printf("Dist: %d\n", d);
    //cout << " this is a test" << d << endl;
    return 0;
}