#include "problems.h"
#include <stdio.h>
#include <stdlib.h>
/*
    These are a bunch of functions to practice writing
    c code. They range from easy to challenging.
*/



/*
    Write a function that takes in 2 integer pointers, and swaps them.
    a and b are passed in, and a should point to b and b should point to a.

    @param a an integer pointer
    @param b an integer pointer
    @return void
*/
void swap (int *a, int *b) {

}

/*
    Write a function that takes in a pointer to an array, and
    the size of the array, and returns the array's maximum element.

    @param arr the integer array
    @param size the size of the array
    @return the maximum element
*/
int maximumElement(int *arr, int size) {
    return 0;
}

/*
    Write a function that reverses a c style string.

    @param arr the string array to be reversed
    @return void
    ** HINT **
    Think about swapping the elements to reverse the array.
    You are only given a pointer, so you can't make a new array.

    You are not given a size of the array here, so you need to find that out first.
    Think how char arrays are structured. How would you find the size? Do you need to?
*/
void reverseString(char *str) {

}

/*
    Write a function that finds the absolute difference between all
    the odd numbers summed, and all the even numbers summed.

    @param arr the integer array containing no negative numbers
    @param size the size of the array
    @return the absolute difference between the even numbers summed
    and the odd numbers summed
*/
int evenOddDiff(int *arr, int size) {
    return 0;
}

/*
    Given an array of struct student pointers with declarations like this:
    struct Student {
        int age;
        char name[30];
        char schoolYear[20]; // Either "Freshman", "Sophomore", "Junior", "Senior", or "Graduate"
        int creditHours;
    };
    Determine the number of students who are Seniors over the age of 21 and have greater
    than 100 credit hours.

    @param student struct array
    @param size size of the array
    @return number of students that fit the criteria
*/
int seniorStudents(struct Student *students, int size) {
    return 0;
}

/*
    Given 2 character arrays determine which one comes lexicographically before the other.
    Return 1 if str1 is lexicographically before str2, return -1 if str2 comes before str1, and
    return 0 if they are both exactly equal.
    For example, aaaa comes before aaab. In this case the function would return 1.
    The strings must be the same length to return 0

    @param str1 string one
    @param str2 string two
    @return 1, 0, or -1
*/
int strComp(char *str1, char *str2) {
    return 0;
}

/*
    Given an string return its integer representation.
    If the string has a negtive sign at the front, then make the integer
    negative. The string given will always be within integer range.
    "-5000" gives -5000 in integer form
    @param string given as a char array
    @return the integer representation.

    ** HINT ** How could you construct the integer using * and +
    operators?
*/
int stoi(char * str) {
    return 0;
}
/*
    Given a tic-tac-toe board, determine if anyone has won. If X's have won, then return 'X'.
    If O's have won, then return 'O'. If more than one player has won, or nobody has won, return 'C'.
    Blank spaces are represented with a ' ' space character.
    @param the board given as a 3x3 char array
    @return the char representing the outcome.
*/

char hasPlayerWon (char board[3][3]) {
    return 'C';
}
