#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD_SIZE 25
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

static char buffer[MAX_WORD_SIZE + 1][MAX_WORD_SIZE + 1];

static void display_grid(size_t rows, size_t cols){
    for (int row=0; row <= rows; ++row){
        for (int col=0; col <= cols; ++col)
            printf("%2d ",buffer[row][col]);
        printf("\n");
    }
}

static void init_grid(){
    size_t row = 0, col = 0;
    memset(buffer, 0, sizeof(buffer));
    row = 0;
    for (col=0; col <= MAX_WORD_SIZE; ++col)
        buffer[row][col] = col;
    col = 0;
    for (row=0; row <= MAX_WORD_SIZE; ++row)
        buffer[row][col] = row;
}

int wdist(const char* psz1, const char* psz2, bool verbose){
    init_grid();
    const size_t l1 = strlen(psz1);
    const size_t l2 = strlen(psz2);
    int min_value;
    for (int row= 1; row<= l1; ++row){
        const char c1 = psz1[row-1];
        for (int col= 1; col<= l2; ++col){
            const char c2 = psz2[col-1];
            const size_t upper = buffer[row-1][col];
            const size_t left = buffer[row][col-1];
            const size_t diagonal = buffer[row-1][col-1];
            if (c1 == c2)
                buffer[row][col] = diagonal;
            else {
                min_value = MIN(upper, left);
                min_value = MIN(min_value, diagonal);
                buffer[row][col] = min_value + 1;
            }
        }
    }
    if (verbose)
        display_grid(l1, l2);
    return buffer[l1][l2];
}
