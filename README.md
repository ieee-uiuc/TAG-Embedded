##TAG Embedded

###Intro to c/cpp


####Variables
Variable are boxes that hold a value in memory. You can either read to them, or write to them. Cpp is a typed language, so every box is made to store a specific representation, and once created for that it cannot be changed.
A few examples:
```cpp
int integer; // A 32-bit signed representation of a number.
short short_integer; // A shorter 16-bit signed representation.
long long_integer; // A 64-bit signed representation.
char character; // A 8-bit signed representation used to store a character.
float floating_point; // A 32-bit floating point representation used to store numbers with a certain decimal point precision.
double double_precision; // A 64-bit representation for decimals.
bool boolean; // Used to store a single bit to represent true/false
```

These are the main primitive types in cpp. There are a few other ones, but we most likely wont use them.

####Conditionals
Now that we have a place to store our data, we need some way to manipulate how the program functions.
We do this with "if", "else", and "else if"!
If statements are very simple. They decide whether or not to do something based on a certain condition.
A real life example would be "If it is not raining, I will walk the dog". In this case, the conditional is not raining, and the action is walking the dog.

```Cpp
if (notRaining) {
    walkTheDog();
}
```
While this example says what to do if it is not raining, it doesn't provide us with an option if it is raining.
What we need then is some way to specify an alternative to the if condition. We can do this using "else".
This example modified with an alternative would be "If it is not raining, I will walk the dog. Else, play board games inside."

```Cpp
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
```Cpp
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

```Cpp
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

####Operators
Operators are what allow us to manipulate the data, and are essential to every cpp program.
Lets take a look at some important ones.
These are best shown.

```Cpp
int integer1 = 13;
int integer2 = 4;
int result; // A variable for storing the result of operations

result = integer1 + integer2; // Self explanatory
result = integer1 - integer2;
result = integer1 * integer2;
result = integer1 / integer2; // Divides the 2 ints, but truncates to the nearing whole number. So result would be 3.
result = integer1 % integer2; // Stores the remainder of integer1 / integer2, and stores in result. Result would be 1


// Relational operators are very important for conditional flow of the program. Things like <, >, ==, !=, etc. return bool values which determine flow in the program.
bool result;

result = 1 < 2; // 1 is obviously less than 2, so result would store true.
result = 1 > 2; // 1 is obviously not greater than 2, so result would store false;
result = 1 >= 1; // Evaluates to true because 1 is equal to 1
result = 2 <= 3; // Evaluates to true because 2 < 3.
result = result == result; // Obviously, the value in result is the same as the value in result, so result should be true.
result = result != true; // This would store false in result because we previously stored true in result, and true != true evaluates to false
// The unary operator "!" flips the value from false to true, and true to false.
result = !result; // Result was previously false, so !false is true

bool condition1 = true, condition2 = false;

result = condition1 || condition2; // The or ("||") operator returns true if any one of its conditions returns true. So this stores true in result because condition1 is true.
result = condition1 && condition2; // The and ("&&") operator returns true only if both of its arguments are true. This would store false in result because condition2 is false;
```
Now that we have operators down, lets move onto another essential part of cpp: loops

####Loops

Loops are very simple. All they do is repeat the same thing over and over again until they are told to stop.
