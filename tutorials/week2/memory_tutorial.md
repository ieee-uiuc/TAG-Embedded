## TAG Embedded

### Memory Tutorial

In the previous tutorial we talked about arrays. Arrays are sequential data structures that have a fixed number of elements. Arrays that are allocated within functions become local to that function, and disappear when that function returns.

Take a look at this example:

```Cpp
int* returnArray() {
    int arr[] = {30, 10, 23, 41};
    // Very bad do not do this
    return arr;
}

int main() {
    int *ret = returnArray();
    for (int i = 0; i < 4; i++) {
        printf("%d ", ret[i]);
    }
```

What will happen in this code?

* The function returnArray will create an array in its local stack memory. 
* Then it will put the address to the first element in the variable "arr". 
* Then the pointer will be returned. 

However, before the array's contents reach main, the contents of the array will be deleted as part of the function returning, and the address stored in arr will no longer be valid. In other words, the kernel has taken back the memory, and it no longer belongs to your program. When main tries to access the pointer's contents, the kernel will send a signal telling your program to halt. This is a segfault, and they are bad.

Lesson: Don't touch the kernel's memory. Only touch the memory it lets you keep.

So how can we fix this? What if we want more permanent memory?

The answer is the static and dynamic allocation of memory!

#### Static Memory

Lets look at static allocation first. One of the uses of the keyword static in c is to maintain the value of a function's local variable even after the function returns. Lets return to our previous example, except this time put the static keyword in front of the array's declaration.

The static keyword allows you to create variables a part of memory that remains after function returns. It is set before any functions are called, and cannot be resized.

```c
int* returnArray() {
    static int arr[] = {30, 10, 23, 41};
    return arr;
}

int main() {
    int *ret = returnArray();
    for (int i = 0; i < 4; i++) {
        printf("%d ", ret[i]);
    }
```
The static keyword fixes this because now the compiler stores this variable in a different location. One in which it doesn't get deleted when the function returns

With just that addition of a single word we have solved the problem. Now this program no longer segfaults, and the main function can successfully traverse the array. This is because the c compiler allocates the static variables in a different part of memory than other local variables.

Static variables are a great way to solve this memory problem, but they are very, well, static. After they are made you cannot resize them. This is in contrast to the next type of memory we will talk about, which is dynamic.

#### Dynamic Memory

**Note:**
When working with pointers returned from memory functions you should **always** check to see if the pointer is null. If the system fails to allocate the memory, then it will return null. If this happens, then either try again, or exit the program gracefully with a error being printed.

This is the good stuff. Dynamically allocated memory has a special place in the program's memory called the heap. This is the place where all dynamic objects and variables are stored. Dynamic meaning that they are persistent through function returns, and their space can also be reallocated to increase their size.

There are a few very important functions to do this in "C".

Here are a few examples of them:

###### Malloc

Malloc is a "C" function that creates blocks of memory in the heap. You simply give it the number of bytes you want allocated, and it returns you a pointer to the first byte of that block.

```c
int * mallocedMem = (int*) malloc(sizeof(int) * 4);


// Always check for an error! In this case it is extremely unlikely, but still possible.
if (mallocedMem == NULL) {
    printf("Uh oh, something went wrong here");
    exit(1);
}
```
This code is saying that I want the program to create a block of memory that is sizeof(int) * 5 bytes long, and return me a pointer to the first byte. This is an int array of size 4.

###### Calloc

Another very similar memory allocating function is calloc. This function takes in 2 parameters. One parameter is the number of total elements, and the other is the size of each element.

```c
calloc(number, size) is the same as malloc(number * size);

int * callocedMem = (int*) calloc(4, sizeof(int));

if (callocedMem == NULL) {
    printf("Uh oh, something went wrong here");
    exit(1);
}
```

malloc vs. calloc is simply a matter of preference.

Earlier I stated that dynamic memory has the ability to be resized. How do we do this?
The answer is realloc!

###### Realloc

The realloc function takes in a pointer to the previous block of memory and also a size. The size parameter specifies the size of the new array. After the function returns realloc will give back a pointer to a new block of memory that is the same size as the parameter that was passed in. The key thing to node though is that our previous values in that memory still remain, unless we call realloc with a size less than the original we specified.

```c
// Declare array of 10 integers
int *mallocedMem = (int *) malloc(sizeof(int) * 10);

if (mallocedMem == NULL) {
    printf("Uh oh, something went wrong here");
    exit(1);
}

mallocedMem[9] = 300;

mallocedMem = (int *) realloc(mallocedMem, sizeof(int) * 15);
// Now our array has 15 elements, but still keeps the value 300 at index 9!
```

The function realloc can also fail and return null! Make sure to check for this.
```c
if (mallocedMem == NULL) {
    printf("Uh oh, something went wrong here");
    exit(1);
}

mallocedMem[14] = 500; // Valid statement now. Without realloc it might've segfaulted
printf("%d", mallocedMem[9]); // Should be 300
```

The only problem now is what if we allocate an array of size 100000000 and want to use that memory elsewhere? How do we tell the program we are done with it?

The answer is with the free function!

###### Free

All the free function does is simply take in an address, and recycles the memory that was allocated. Be careful though. It'll throw an error if you try and free memory you never allocated.

```c
int *mallocedMem = (int *) malloc(sizeof(int) * 30000);

if (mallocedMem == NULL) {
    printf("Uh oh, something went wrong here");
    exit(1);
}

// Do stuff with memory here

// Call free when we are done
free(mallocedMem);
```
Now if we try to access the array we might segfault because we gave away ownership of that memory

Wait a minute. How does "free" know how much memory to free? Shouldn't we need to specify a size argument to tell it how much to free? **Think about this**

**Note**
Look at all the sample code. How many of those lines were simply checking for errors? A lot of systems programming is making sure what you intend to do actually happens. Systems need lots of error checking because they need to maintain a very high reliability.

There are lots of other useful memory manipulation functions in stdio.h and stdlib.h headers. Functions like memcpy, memcmp, memset, memmove, and memchr are very useful! It's definitely worth the time to go investigate what these functions do.
