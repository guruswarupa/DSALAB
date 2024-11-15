#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  // For isdigit() and isalpha()
#include <string.h> // For strtok()

// Stack structure for char type (used in infix-to-postfix conversion)
typedef struct {
    char *items;
    int top;
    int capacity;
} CharStack;

void initCharStack(CharStack *stack, int capacity) {
    stack->capacity = capacity;
    stack->items = (char *)malloc(stack->capacity * sizeof(char));
    stack->top = -1;
}

void resizeCharStack(CharStack *stack) {
    stack->capacity *= 2;
    stack->items = (char *)realloc(stack->items, stack->capacity * sizeof(char));
}

int isCharStackEmpty(CharStack *stack) {
    return stack->top == -1;
}

void pushChar(CharStack *stack, char value) {
    if (stack->top == stack->capacity - 1) {
        resizeCharStack(stack);
    }
    stack->items[++stack->top] = value;
}

char popChar(CharStack *stack) {
    return isCharStackEmpty(stack) ? -1 : stack->items[stack->top--];
}

char peekChar(CharStack *stack) {
    return isCharStackEmpty(stack) ? -1 : stack->items[stack->top];
}

// Stack structure for integer type (used in postfix evaluation)
typedef struct {
    int *items;
    int top;
    int capacity;
} IntStack;

void initIntStack(IntStack *stack, int capacity) {
    stack->capacity = capacity;
    stack->items = (int *)malloc(stack->capacity * sizeof(int));
    stack->top = -1;
}

void resizeIntStack(IntStack *stack) {
    stack->capacity *= 2;
    stack->items = (int *)realloc(stack->items, stack->capacity * sizeof(int));
}

int isIntStackEmpty(IntStack *stack) {
    return stack->top == -1;
}

void pushInt(IntStack *stack, int value) {
    if (stack->top == stack->capacity - 1) {
        resizeIntStack(stack);
    }
    stack->items[++stack->top] = value;
}

int popInt(IntStack *stack) {
    return isIntStackEmpty(stack) ? -1 : stack->items[stack->top--];
}

int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    if (op == '^') {
        return 3;
    }
    return 0;
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Function to convert infix to postfix
void infixToPostfix(char *infix, char *postfix) {
    CharStack operatorStack;
    initCharStack(&operatorStack, 10);
    int k = 0;  // Index for postfix expression

    for (int i = 0; infix[i] != '\0'; i++) {
        char current = infix[i];

        if (isdigit(current)) {  // If digit, extract the full number
            while (isdigit(infix[i])) {
                postfix[k++] = infix[i++];
            }
            postfix[k++] = ' ';  // Add space as a separator
            i--; // Step back to correct the outer loop index
        } else if (current == '(') {  // Opening parenthesis
            pushChar(&operatorStack, current);
        } else if (current == ')') {  // Closing parenthesis
            while (!isCharStackEmpty(&operatorStack) && peekChar(&operatorStack) != '(') {
                postfix[k++] = popChar(&operatorStack);
                postfix[k++] = ' ';  // Add space
            }
            popChar(&operatorStack);  // Remove '('
        } else if (isOperator(current)) {  // Operator
            while (!isCharStackEmpty(&operatorStack) && precedence(current) <= precedence(peekChar(&operatorStack))) {
                postfix[k++] = popChar(&operatorStack);
                postfix[k++] = ' ';  // Add space
            }
            pushChar(&operatorStack, current);
        }
    }

    // Pop remaining operators
    while (!isCharStackEmpty(&operatorStack)) {
        postfix[k++] = popChar(&operatorStack);
        postfix[k++] = ' ';  // Add space
    }

    postfix[k - 1] = '\0';  // Replace last space with null terminator
    free(operatorStack.items);  // Free memory
}

// Function to evaluate postfix expression
int evaluatePostfix(char *postfix) {
    IntStack stack;
    initIntStack(&stack, 10);
    char *token = strtok(postfix, " ");

    while (token != NULL) {
        if (isdigit(token[0])) {  // Operand
            pushInt(&stack, atoi(token));
        } else if (isOperator(token[0])) {  // Operator
            int operand2 = popInt(&stack);
            int operand1 = popInt(&stack);

            switch (token[0]) {
                case '+': pushInt(&stack, operand1 + operand2); break;
                case '-': pushInt(&stack, operand1 - operand2); break;
                case '*': pushInt(&stack, operand1 * operand2); break;
                case '/': pushInt(&stack, operand1 / operand2); break;
                case '^': {
                    int result = 1;
                    for (int i = 0; i < operand2; i++) {
                        result *= operand1;
                    }
                    pushInt(&stack, result);
                    break;
                }
            }
        }
        token = strtok(NULL, " ");
    }

    int result = popInt(&stack);
    free(stack.items);  // Free memory
    return result;
}

int main() {
    char infix[100], postfix[200];

    printf("Enter an infix expression: ");
    scanf("%[^\n]%*c", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix Expression: %s\n", postfix);

    int result = evaluatePostfix(postfix);
    printf("Result of Evaluation: %d\n", result);

    return 0;
}
