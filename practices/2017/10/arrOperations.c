#include <stdlib.h>
#include <stdio.h>
#include <math.h>

enum Operation
{
    PLUS,
    MINUS,
    DIVIDE,
    MULT
};

int getArrayLengthUserInput();
void fillArrayUserInput(double a[], int length);
enum Operation getUserOperationInput();
void applyOperation(
    double a[],
    double b[],
    double c[],
    int length,
    enum Operation operation);
void printArr(double a[], int length);

void cleanBuffer() {
    char c = 0;
    while(c != '\n') {
        c = getchar();
    }
}

int main(void)
{
    int N = getArrayLengthUserInput();
    double a[N];
    fillArrayUserInput(a, N);
    printArr(a, N);
    double b[N];
    fillArrayUserInput(b, N);
    printArr(b, N);
    double c[N];
    enum Operation op = getUserOperationInput();
    applyOperation(a, b, c, N, op);
    printArr(c, N);
    return 0;
}

double valueOperation(double a, double b, enum Operation op);

void applyOperation(
    double a[],
    double b[],
    double c[],
    int length,
    enum Operation operation) {
    for (int i = 0; i < length; i++) {
        c[i] = valueOperation(a[i], b[i], operation);
    }
}

double valueOperation(double a, double b, enum Operation op) {
    switch (op) {
        case PLUS: return a + b;
        case MINUS: return a - b;
        case DIVIDE: {
            if (fabs(b) < 0.000001) {
                return NAN;
            }
            return a / b;
        }
        case MULT: return a * b;
        default: return NAN;
    }
}

enum Operation getUserOperationInput()
{
    char c = 0;
    while(1)
    {
        puts("Enter operation (+,-,/,*):");
        cleanBuffer();
        scanf("%c", &c);
        printf("operation: %c\n", c);
        cleanBuffer();
        switch (c)
        {
        case '+':
            return PLUS;
        case '-':
            return MINUS;
        case '/':
            return DIVIDE;
        case '*':
            return MULT;
        default:
            puts("Invalid operation.");
            break;
        }
    }
}

void printArr(double a[], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%.2f, ", a[i]);
    }
    puts("");
}

void fillArrayUserInput(double a[], int length)
{
    double value;
    for (int i = 0; i < length; i++)
    {
        printf("[%i] = ", i);
        scanf("%lf", &value);
        a[i] = value;
    }
}

int getArrayLengthUserInput()
{
    int length;
    do
    {
        puts("Enter arrays length:");
        scanf("%i", &length);
        if (length <= 0)
        {
            puts("Invalid array length.");
        }
    } while (length <= 0);
    return length;
}