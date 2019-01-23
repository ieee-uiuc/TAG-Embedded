#include "problems.h"
#include <stdio.h>
#include <stdlib.h>
/*
    These are a bunch of functions to practice writing
    c code to practice memory and file io concepts. They range from easy to challenging.
*/


/*
 * Create a function that takes in a file name, and sums up all the integers in 
 * the file and returns the sum. The integers are all newline seperated, so no 
 * parsing should be necessary
 * @param char * filename
 * @return int sum: the sume of all the integers in the file.
 * Note: No integer will exceed the maximum 32-bit integer bounds
 *
*/
long sumIntegers(char * filename) {
    return 0;
}

/*
 * Given an array of integers, return the array as two seperate halves.
 * These can be in any way you like as long as array "A" contains integers
 * 0 to N/2 - 1 and array "B" contains integers N/2 to N - 1.
 * Note: There is a very easy way to do this. See if you can find it.
 * @param int * orig_arr: Original array of integers to split
 * @param int size: Size of the original array to help you split it
 * @param int ** A: First half of the array
 * @param int ** B: Second half of the array
 * @return void
 *
*/
void splitArr(int * orig_arr, int size, int ** A, int ** B) {
}

/*
 * Given an array of words return a new array will all the words removed that 
 * begin with a given letter. For example, if the array had
 * ["Child", "Fun", "Stuff"] and you were given "S", then you would return
 * an array of length two with ["Child", "Fun"]. Say for the purposes of this
 * exercise that there everything is case insensitive.
 * @param char ** words
 * @param int * size
 * @param char ** new_words
 * @param char letter
 * @return void
 * Note: In this problem you are given 2 double pointers and a single pointer. 
 * Since you will be creating an array within the function you will need to use
 * heap memory. After creating the new array, then simply copy a word over to
 * your new array if it meets the criteria (check first letter). After copying
 * all the words make sure to set the size pointer to the new size of the array.
*/
void removeWords(char ** words, int * size, char ** new_words, char letter) {
}

/*
 * Given the names of two files that have lexographically sorted words
 * seperated by newlines return the name of a new file where all the words
 * of both files have been merged in lexographical order.
 *
 * @param char * filename1: First file to merge
 * @param char * filename2: Second file to merge
 * @param char * new_filename: Name of the new file to put the output in.
 * @return void
 *
*/
void mergeFiles(char * filename1, char * filename2, char * newfilename) {
}



