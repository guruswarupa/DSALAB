#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int *items;
    int top;
    int capacity;
} Stack;

void init(Stack* stack, int capacity) {
    stack->capacity = capacity;
    stack->items = (int*)malloc(stack->capacity * sizeof(int));
    stack->top = -1;
}

void resizeStack(Stack* stack) {
    stack->capacity *= 2;
    stack->items = (int*)realloc(stack->items, stack->capacity * sizeof(int));
}

int isFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, int value) {
    if (isFull(stack)) {
        resizeStack(stack);
    }
    stack->items[++stack->top] = value;
}

int pop(Stack* stack) {
    return isEmpty(stack) ? -1 : stack->items[stack->top--];
}

int peek(Stack* stack) {
    return isEmpty(stack) ? -1 : stack->items[stack->top];
}

void display(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
    } else {
        for (int i =0; i <= stack->top; i++) {
            printf("%d ", stack->items[i]);
        }
        printf("\n");
    }
}

int main(){
    int choice,ele,max;
    printf("enter the value of max");
    scanf("%d",&max);
    Stack Mstack;
    init(&Mstack, max);
    while(1){
        printf("\nenter your choice\n");
        printf("1 for push\n2 for pop\n3 for display\n4 for exit\n");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("Enter Element to be pushed:");
                scanf("%d",&ele);
                push(&Mstack, ele);
                break;
            case 2:
                printf("deleted element is %d\n",pop(&Mstack));
                break;
            case 3:
                display(&Mstack);
                break;
            case 4:
                free(Mstack.items);
                exit(0);
            default:
                printf("invalid choice");
        }
    }
}