#include "problems.h"
#include <assert.h> // You can use assert.h functions to test your code
#include <stdio.h>
#include <string.h>
void testSwap () {
    int a = 5, b = 3;
    printf("Testing swap\n");
    swap(&a, &b);
    assert(a == 3);
    assert(b == 5);
    printf("swap passed!\n");
}

void testMaximumElement() {
    int arr[] = {1, 5, 8, 12, 3, 2, 9, 7, 16, 16, 4, 2};
    printf("Testing maximumElement\n");
    int max = maximumElement(arr, sizeof(arr) / sizeof(int));
    assert(max == 16);
    int arr2[] = {1, 132, 131, -313, 313, 32, 4, 32, 4343, 3132, 1, 0};
    max = maximumElement(arr2, sizeof(arr) / sizeof(int));
    assert(max == 4343);
    printf("maximumElement passed!\n");
}

void testReverseString() {
    char str1[] = "racecar";
    char str2[] = "mylittlepony";
    char str3[] = "this is a really pointless and long string";
    printf("Testing reverseString\n");
    reverseString(str1);
    assert(strcmp("racecar", str1) == 0);
    reverseString(str2);
    assert(strcmp("ynopelttilym", str2) == 0);
    reverseString(str3);
    assert(strcmp("gnirts gnol dna sseltniop yllaer a si siht", str3) == 0);
    printf("reverseString passed!\n");
}
void testEvenOddDiff() {

}
void testSeniorStudents() {

}
void testStrComp() {

}
void testHasPlayerWon() {

}
int main() {
    testSwap();
    testMaximumElement();
    testReverseString();
    // Implement these test cases.
    // Testing is fun. Err, sorta. Okay not really.
    testEvenOddDiff();
    testSeniorStudents();
    testStrComp();
    testHasPlayerWon();
    return 0;
}
