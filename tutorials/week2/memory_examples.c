#include <stdio.h>
#include <stdlib.h>
#define ROWS 10
#define COLS 10
int main () {
    // What does this code do?

    // First we make an array of pointers equal to the number of rows.
    int **arr = (int **) malloc(sizeof(int*) * ROWS);

    // Then we iterate through each row, and assign the pointer to another dynamic array of COLS length
    for (int i = 0; i < ROWS; i++) {
        // arr[i] is a pointer since arr is a double pointer
        arr[i] = (int*) malloc(sizeof(int) * COLS);
    }

    // If we want to reclaim all the memory do we need to call free once, or many times?
    
}
