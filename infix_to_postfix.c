#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 100
typedef struct 
{
    int top;
    char items[MAX];
} Stack;
void initialize(Stack *s) 
{
    s->top = -1;
}
int isEmpty(Stack *s) 
{
    return s->top == -1;
}
int isFull(Stack *s) 
{
    return s->top == MAX - 1;
}
void push(Stack *s, char value) 
{
    if (isFull(s)) 
    {
        printf("Stack overflow\n");
        return;
    }
    s->items[++s->top] = value;
}
char pop(Stack *s) 
{
    if (isEmpty(s)) 
    {
        printf("Stack underflow\n");
        return -1;
    }
    return s->items[s->top--];
}
char peek(Stack *s) 
{
    if (isEmpty(s)) 
    {
        return -1;
    }
    return s->items[s->top];
}
int precedence(char op) 
{
    switch (op) 
    {
        case '+':
        case '-':
                  return 1;
        case '*':
        case '/':
                  return 2;
        case '^':
                  return 3;
    }
    return 0;
}
void infixToPostfix(char infix[], char postfix[]) 
{
    Stack s;
    initialize(&s);
    int i, j = 0;
    for (i = 0; infix[i] != '\0'; i++) 
    {
        if (isalnum(infix[i])) 
        {
            postfix[j++] = infix[i];
        }
        else if (infix[i] == '(') 
        {
            push(&s, infix[i]);
        }
        else if (infix[i] == ')') 
        {
            while (!isEmpty(&s) && peek(&s) != '(') 
            {
                postfix[j++] = pop(&s);
            }
            if (!isEmpty(&s) && peek(&s) != '(') 
            {
                printf("Invalid expression\n");
                return;
            } 
            else 
            {
                pop(&s);
            }
        }
        else
        {
            while (!isEmpty(&s) && precedence(infix[i]) <= precedence(peek(&s))) 
            {
                postfix[j++] = pop(&s);
            }
            push(&s, infix[i]);
        }
    }
    while (!isEmpty(&s)) 
    {
        postfix[j++] = pop(&s);
    }
    postfix[j] = '\0';
}
int main() 
{
    char infix[MAX], postfix[MAX];
    printf("Enter an infix expression: ");
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);
    return 0;
}
