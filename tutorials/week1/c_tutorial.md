# TAG Embedded

### Intro to c tutorial


#### Variables

Variable are boxes that hold a value in memory. You can either read to them, or write to them. "C" is a typed language, so every box is made to store a specific representation, and once created for that it cannot be changed.
A few examples:
```c
int integer; // A 32-bit signed representation of a number.
short short_integer; // A shorter 16-bit signed representation.
long long_integer; // A 64-bit signed representation.
char character; // A 8-bit signed representation used to store a character.
float floating_point; // A 32-bit floating point representation with a certain precision.
double double_precision; // A 64-bit representation with more decimal precision
```

These are the main primitive types in "C". There are a few other ones, but we most likely wont use them.

#### Conditionals

Now that we have a place to store our data, we need some way to manipulate how the program functions.
We do this with "if", "else", and "else if"!
If statements are very simple. They decide whether or not to do something based on a certain condition.
A real life example would be "If it is not raining, I will walk the dog". In this case, the conditional is not raining, and the action is walking the dog.

```c
if (notRaining) {
    walkTheDog();
}
```
While this example says what to do if it is not raining, it doesn't provide us with an option if it is raining.
What we need then is some way to specify an alternative to the if condition. We can do this using "else".
This example modified with an alternative would be "If it is not raining, I will walk the dog. Else, play board games inside."

```c
if (notRaining) {
    walkTheDog();
}
else {
    playBoardGames();
}
```

The way this is setup one of the two choices will **always** be selected. But is there a better and more modular way to allow more to be selected?
The answer is yes, of course!
What if we make else statement another if condition and nest them inside of each other.
```c
if (notRaining) {
    walkTheDog();
}
else {
    if (snowing) {
        goSledding()
    }
    else {
        goSwimming();
    }
}
```

In this configuration, we first check to see if it is not raining. If it is raining, however, we move to the else statement where we first check to see if it is snowing.
If it isn't snowing, then we finally default to going swimming. In this way, we have chained the conditionals together to only execute one of them, and to evaluate the conditions in order. However, there is a neater way to do this that isn't so messy. Take a look at this:

```c
if (notRaining) {
    walkTheDog();
}
else if (snowing) {
    goSledding();
}
else {
    goSwimming();
}
```

Now we can clearly see the relationship between all the conditionals. If one fails, then we move onto the next, and we break out as soon as a condition evaluates to true.

#### Operators

Operators are what allow us to manipulate the data, and are essential to every "C" program.
Lets take a look at some important ones.
These are best shown.

```c
int integer1 = 13;
int integer2 = 4;
int result; // A variable for storing the result of operations

result = integer1 + integer2; // Self explanatory
result = integer1 - integer2;
result = integer1 * integer2;
```
Divides the 2 ints, but truncates to the nearing whole number. So result would be 3.
```c
result = integer1 / integer2;
```
Stores the remainder of integer1 / integer2, and stores in result. Result would be 1
```c
result = integer1 % integer2; 
```

Relational operators are very important for conditional flow of the program. Things like <, >, ==, !=, etc. return bool values which determine flow in the program.

```c
int result // Stores a boolean

result = 1 < 2; // 1 is obviously less than 2, so result would store true.
result = 1 > 2; // 1 is obviously not greater than 2, so result would store false;
result = 1 >= 1; // Evaluates to true because 1 is equal to 1
result = 2 <= 3; // Evaluates to true because 2 < 3.
result = result == result; // Result should be true.
result = result != true; // true != true evaluates to false
// The unary operator "!" flips the value from false to true, and true to false.
result = !result; // Result was previously false, so !false is true

int condition1 = true, condition2 = false;
```
The or ("||") operator returns true if any one of its conditions returns true. So this stores true in result because condition1 is true.
```c
result = condition1 || condition2; 
```
The and ("&&") operator returns true only if both of its arguments are true. This would store false in result because condition2 is false.
```c
result = condition1 && condition2;
```

Now that we have operators down, lets move onto another essential part of cpp: loops

#### Loops

Loops are very simple. All they do is repeat the same thing over and over again until they are told to stop.
There are 3 types of loop in cpp. There's the for loop, the while loop, and the do-while loop. Each of them are slightly different.

The while loop repeats the same block of code over and over again until the condition evaluates to false. It looks like this:

Here we are simply counting down from 5 to 0. When the loop breaks out, the value of i will be 0.
```c
int i = 5;
while (i > 0) {
    i = i - 1;
}
```
Another type of loop we have is the for loop. This loop simply provides a simple abstraction from the while loop. The for loop is mainly used when a task needs to be done a certain amount of times.
```c
int i;
for (i = 5; i > 0; i = i - 1);
```
This code does the same thing as the while loop, but it is more compact and easier to understand. The i = i - 1 is the last line executed in the loop, while the condition i > 0 is checked at the beginning of each iteration.

The last type of loop is the do-while loop. It is rarely used, however, and is very subtly different from the while loop.

#### Functions

In programming functions are very useful for making sure you don't repeat yourself too much. Say that I have a program that needs to compute the absolute value of a number very frequently. I could just copy and past the same code a bunch of times, but that would be a lot of work, and we're lazy. So instead we can generalize the very simple absolute value algorithm. We can make a function that acts like a box. In this case, it is a box that takes in any number that we want to have the absolute value of, and gives back that same number's absolute value.

##### Declaration of a function
* The first number states the return type. This can be any of the primitive types we mentioned above, but it can also be many other things.
* The next word is the name of the function obviously.
* Inside the parenthesis you specify a list of parameters. These are the things that get put into the box. A function can have any number of parameters.
* These parameters are not the original variables when inside the function. Instead, they are copies of the original.

```c
int absoluteValue (int number) {
    if (number < 0) {
        return -1 * number;
    }
    else {
        return number;
    }
}
```
Say we have another function that needs to compute the absolute value. We can just call the function we made above!
When this main method executes, it will call the function "absoluteValue" on both these integers, and then add the values they return.

The first call to absoluteValue should return 30, and the second call should return 20. Once both these value have been retrieved, then the sum can be computed and stored in result.

```c
int main () {
    int num1 = 30;
    int num2 = -20;
    int result = absoluteValue(num1) + absoluteValue(num2);

    return 0;
}
```
One thing I forgot to mention...in "C", main() is a special function that is executed at the start of the program. This function returns a integer representing the status of the program when it exits. 

A returned value of 0 indicates that the program executed free of error while anything else indicates an error. However, this is just a convention.

#### Structs

Structs, put simply, are a way to organize a collection of variables together. For example, lets say that we need some way to represent a object like a rectangle. We could declare a width and a height variable separately, but then we would have no way of communicating their association very well. Plus, if we had lots of properties to a specific object, then passing it into a function would be a mess.

```c
int rectPrismVolume(int w, int h, int d) {
    return w * h * d;
}
```
Now we'd need to create 3 variables, and then pass them into the function separately. That's gross. Let's try a more organized approach.

```c
struct RectPrism{
    int w;
    int h;
    int d;    
};
```
Here we use the "struct" keyword to tell the compiler that this is how a RectPrism struct should look. Now, whenever we want to create a actual RectPrism struct the compiler knows what we are referring to.

To create a struct we simply use the "struct" keyword. Unfortunately whenever you declare or create a struct you must specify the struct keyword in front. This just tells the compiler not to try and evaluate it as a normal type. (you can get around this using typedef and other methods, but I won't talk about it here).

```c
struct RectPrism rect;
rect.w = 13;
rect.h = 15;
rect.d = 400;
```
The dot notation accesses the things declared to be inside a RectPrism struct.

Now we have represented a rectangular prism as a single word, or "object".
Lets go back to our original function example. Now we can instead pass this to the function as a single parameter of type struct RectPrism.

```c
int rectPrismVolume(struct RectPrism rect) {
    return rect.w * rect.h * rect.d;
}
```
We now have a clean way to represent a object in the form of a struct.


#### Pointers

Ah yes, pointers...these little guys scare away so many people from systems software. However, they are extremely important and powerful, and can be understood fairly quickly.

Lets say we have a struct that has 3000 int variables in it, and we want to pass it along to a function. Since a function creates a copy of the struct, it would have to copy all 3000 integers every time it was called! This takes a long time, and is very inefficient. What if there was a way to simply tell the function where this struct resides in memory? That is exactly what pointers do! Pointers hold an address to a something in memory, instead of its actual value. Lets look at some examples...

```c
int a = 32; // 2 beautiful integers. Each takes up 32 bits in some location in memory.
int b = 50;
```
If we want to find the location each of these integers are located at we can simply use the & operator.

This declares a pointer, and assigns it to NULL. NULL is a special value that indicates that pointer doesn't currently have an address assigned to it.
```c
int *pointer = NULL; 
```
Here's the tricky part. Now pointer has the address of "a" stored in it.
```c
pointer = &a;
```
The star operator, when used with pointers, indicates accessing the data at a specific address. *pointer is the exact same thing as "a" because pointer still contains the address of a. Now because we are assigning the data at pointer to "b", it stores the same data as "a".
```c
b = *pointer;
```
What does this do?
```c
pointer = &b;
*pointer = 30;
```
"b" should now be 30, right? Pointer now points to be, so assigning 30 to *pointer is now the same as assigning "b" to 30.

#### Arrays

Arrays are a type of data storage in which data is stored sequentially. It is just like a collection of variables, except it asserts that all the variables are one after another and are of the same type.

This is declaring an array of 30 integers. The number in the square brackets specifies the number of elements in the array.
```c
int numbers[30]; 
```

```c
char string[300]; // A string is just an array of characters as shown here.

char string[] = "I like pizza";
```
This will create an array with 13 elements. Why 13 and not 12? The string only has 12 characters right?

We can print a string like the one above using the printf() function, which stands for print format;
To print a character string simply call printf like this and it will display on console:
```c
printf(string);
```

Arrays are special and can be indexed unlike variables.

This accesses the first character of the string, which is "I", and assigns it to the character 'm'.
```c
string[0] = 'm';
```
This accesses the last character of the string, since "a" is the 11th index and assigns it to the character '3'.
```c
string[11] = '3';
```

In the above example what happens if we try and access "string[100]"? What will happen?

Finally we should discuss how arrays and pointers differ from each other. In truth, an array is simply a pointer to the first element of an array, and the "[]" operator is simply an abstraction from the fact that arrays **are pointers**.

```c
char *arr = "Hello world!";
char arr2[] = "Hello world!";
```
Both of these function the exact same way. They both can be accessed with [], and store the same number of characters.

What do these lines do?
```c
*arr2;
arr[3];
*arr = '3';
*(arr2 + 1); 
```
The first one should access the first element of arr2, which would be 'H'. This is because an array is just a pointer to the first element, which happens to be 'H'.
The second one should access the fourth element of arr.
The third one will set the first character of arr to be the character '3'.

The last one is a bit tricky. What happens when we increment the value of a pointer? Well it should move to the next address. So, in effect, arr2 + 1 is the address of the character 'e'. If (arr2 + 1) is the address of the character 'e', then *(arr2 + 1) accesses the value 'e' in arr2!

This means that...
```c
*(arr2 + 1) == arr2[1];
```

Or more generalized...
```c
int N; // The element we can to access.

*(arr2 + N) == arr2[N]; 
```
While both of these are technically the same we mainly use arr2[N] simply because it is easier.
