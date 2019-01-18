## Memory Errors and Leaks

### In the previous tutorial we...
* Talked about local, static, and dynamic memory
* The stack and heap sections of memory and their uses
* How to allocate memory with malloc or calloc in c
* How to reallocate more memory with realloc
* How to give memory back to the system with free

### Memory Errors
Memory errors happen when you do something the Linux kernel doesn't like. This could be:
* Accessing an invalid address like NULL
* Accessing a functions local variables after it returned
* Accessing a region beyond the amount of memory that you allocated
* Accessing memory you recently freed
* Accessing memory you don't own (i.e from another process)

### Memory Leaks
* Only caused when you malloc or calloc memory, and then don't free it. You never need to free local or static variables

So what do these look like? See if you can spot if there are memory errors in these examples, and if so, which types.

'''cpp
    int * getArr() {
        int arr[] = {1, 2, 3, 4};
        return arr;
    }
    int main() {
        int * ptr = getArr();
        printf("%d", ptr[2]);
        return 0;
    }
'''

Lets try another one. Recall how simple pointer arithmetic works.

'''cpp
    int computeSum(int * arr) {
        int sum = 0;
        while (arr != NULL) {
            sum += *arr;
            arr += 1;
        }
        return sum;
    }
    int main() {
        int arr[] = {1, 2, 3, 4, 4, 5, 5, 6};
        int sum = computeSum(arr);
        printf("%d", sum);
        return 0;
    }
'''

Lets be more subtle. What's wrong with this program?

'''cpp
    char * repeatChars(char c, int times) {
        char * arr = (char*) malloc(times * sizeof(char));
        for (int i = 0; i < times; i++) {
            arr[i] = c;
        }
        return arr;
    }
    int main() {
        char * c = repeatChars('b', 36);
        printf("%s", c);
        return 0;
    }
'''

Is there something wrong with this one?

'''cpp
    #define NUM_ROWS 15
    #define NUM_COLS 15
    int main() {
        int ** mem = (int ** ) malloc(sizeof(int*) * NUM_ROWS);
        for (int i = 0; i < NUM_COLS; i++) {
            mem[i] = (int * ) malloc(sizeof(int) * NUM_COLS);
        }

        // Do stuff with the 2d array

        // free the mem
        free(mem);
        return 0;
    }
'''

Last one! This is some code for a stack. It is a LIFO data structure, so the first thing to go in is the last one out.
* push adds an element to the top of the data structure
* pop removes an element from the top of the data structure and returns it back
* isEmpty simply checks to see if there are any elements left
* initStack creates the memory to use for the stack

** There is a subtle memory error in this code. See if you can find it. **
This is not easy! Question everything in here, and see if you can spot the hidden error. The syntax is fine, and so is the logic.
There is only memory errors and leaks.

'''cpp
    #define INITIAL_NUM_ELEMS 30

    struct Stack {
        int currIdx; // Points to next free spot
        int maxSize; // Current size of array
        int * arr;
    };

    int isEmpty(struct Stack * stack) {
        if (stack == NULL) return -1;
        return stack->currIdx == 0;
    }

    void push(struct Stack * stack, int elem) {
        if (stack == NULL) return;
        if (stack->currIdx >= stack->maxSize) {
            if (!realloc(stack->arr, 2 * stack->maxSize * sizeof(int))) {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
            stack->maxSize *= 2;
        }
        stack->arr[stack->currIdx++] = elem;
    }

    int pop(struct Stack * stack) {
        if (stack == NULL) return -1;
        if (stack->currIdx == 0) return -1; // Stack is empty!
        else {
            return stack->arr[--stack->currIdx];
        }
    }

    struct Stack * initStack() {
        struct Stack * s = (struct Stack *) malloc(sizeof(struct Stack));
        if (!s) {
            perror("malloc struct");
            exit(EXIT_FAILURE);
        }
        s->arr = (int *) malloc(sizeof(int) * INITIAL_NUM_ELEMS);
        if (!s->arr) {
            perror("malloc arr");
            exit(EXIT_FAILURE);
        }
        s->currIdx = 0;
        s->maxSize = INITIAL_NUM_ELEMS;
        return s;
    }

    void freeStack(struct Stack * s) {
        if(s) free(s);
    }

    int main() {
        struct Stack * s = initStack();
        push(s, 1);
        push(s, 2);
        push(s, 3);
        push(s, 4);
        push(s, 5);
        printf("%d %d %d %d %d\n", pop(s), pop(s), pop(s), pop(s), pop(s));
        free(s);
        return 0;
    }
'''
