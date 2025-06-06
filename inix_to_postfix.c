#include<stdio.h>
#include<string.h>
#define SIZE 30

char array1[SIZE]; // Postfix output
char array2[SIZE]; // Operator stack

void infix_to_postfix(char str[], int len, int* top1, int* top2) {
    for (int i = 0; i < len; i++) {
        if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) {
            *top1 = *top1 + 1;
            array1[*top1] = str[i];
        }
        else if (str[i] == '(') {
            *top2 = *top2 + 1;
            array2[*top2] = str[i];
        }
        else if (str[i] == ')') {
            while (*top2 >= 0 && array2[*top2] != '(') {
                *top1 = *top1 + 1;
                array1[*top1] = array2[*top2];
                *top2 = *top2 - 1;
            }
            if (*top2 >= 0 && array2[*top2] == '(') {
                *top2 = *top2 - 1; // Pop the '('
            }
        }
        else if (str[i] == '^') {
            *top2 = *top2 + 1;
            array2[*top2] = str[i];
        }
        else if (str[i] == '*' || str[i] == '/') {
            while (*top2 >= 0 && array2[*top2] == '^') {
                *top1 = *top1 + 1;
                array1[*top1] = array2[*top2];
                *top2 = *top2 - 1;
            }
            *top2 = *top2 + 1;
            array2[*top2] = str[i];
        }
        else if (str[i] == '+' || str[i] == '-') {
            while (*top2 >= 0 && 
                  (array2[*top2] == '^' || array2[*top2] == '/' || array2[*top2] == '*')) {
                *top1 = *top1 + 1;
                array1[*top1] = array2[*top2];
                *top2 = *top2 - 1;
            }
            *top2 = *top2 + 1;
            array2[*top2] = str[i];
        }
    }

    // Pop any remaining operators
    while (*top2 >= 0) {
        *top1 = *top1 + 1;
        array1[*top1] = array2[*top2];
        *top2 = *top2 - 1;
    }

    // Null-terminate and print postfix expression
    array1[*top1 + 1] = '\0';
    printf("Postfix expression: %s\n", array1);
}

int main() {
    char str[SIZE] = "A+B*(C^D-E)^(F+G*H)-I";
    int len = strlen(str);
    int top1 = -1;
    int top2 = -1;
    infix_to_postfix(str, len, &top1, &top2);
    return 0;
}
