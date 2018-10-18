struct Student {
    int age;
    char name[30];
    char schoolYear[20]; // Either "Freshman", "Sophomore", "Junior", "Senior", or "Graduate"
    int creditHours;
};

void pointerSwap (int *a, int *b);

int maximumElement(int *arr, int size);

void reverseArray(char *str);

int evenOddDiff(int *arr, int size);

int seniorStudents(struct Student *students, int size);

int strComp(char *str1, char *str2);

char hasPlayerWon (char board[3][3]);
