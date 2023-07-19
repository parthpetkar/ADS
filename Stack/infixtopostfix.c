#include <stdio.h>
#include <ctype.h>

char stack[100];
int top = -1;

void push(char item)
{
    if (top == (MAX_EXPR_SIZE - 1))
        printf("Stack is Full\n");
    else
    {
        top = top + 1;
        stk[top] = item;
    }
}
void pop()
{
    if (top == -1)
    {
        printf("Stack is Empty\n");
    }
    else
    {
        top = top - 1;
    }
}

int priority(char x)
{
    if (x == '(')
        return 0;
    if (x == '+' || x == '-')
        return 1;
    if (x == '*' || x == '/')
        return 2;
    return 0;
}

int main()
{
    char exp[100];
    char *e, x;
    printf("Enter the expression : ");
    scanf("%s", exp);
    printf("\n");
    e = exp;

    while (*e != '\0')
    {
        if (isalnum(*e))
            printf("%c ", *e);
        else if (*e == '(')
            push(*e);
        else if (*e == ')')
        {
            while ((x = pop()) != '(')
                printf("%c ", x);
        }
        else
        {
            while (priority(stack[top]) >= priority(*e))
                printf("%c ", pop());
            push(*e);
        }
        e++;
    }

    while (top != -1)
    {
        printf("%c ", pop());
    }
    return 0;
}
