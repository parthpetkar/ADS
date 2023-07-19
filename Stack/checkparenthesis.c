#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_EXPR_SIZE 1000
struct stack
{
    int top;
    char stk[MAX_EXPR_SIZE];
};

struct stack s;
void push(char item)
{
    if (s.top == (MAX_EXPR_SIZE - 1))
        printf("Stack is Full\n");
    else
    {
        s.top = s.top + 1;
        s.stk[s.top] = item;
    }
}
void pop()
{
    if (s.top == -1)
    {
        printf("Stack is Empty\n");
    }
    else
    {
        s.top = s.top - 1;
    }
}
char *checkparenthesis(char *exp)
{
    int len = strlen(exp);
    int i = 0;
    s.top = -1;
    for (i = 0; i < len; i++)
    {
        if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{')
        {
            push(exp[i]); 
            continue;
        }
        else if (exp[i] == ')' || exp[i] == ']' || exp[i] == '}') 
        {
            if (exp[i] == ')')
            {
                if (s.stk[s.top] == '(')
                {
                    pop(); 
                }
                else
                {
                    printf("\nUNBALANCED EXPRESSION\n");
                    break;
                }
            }
            if (exp[i] == ']')
            {
                if (s.stk[s.top] == '[')
                {
                    pop(); 
                }
                else
                {
                    printf("\nUNBALANCED EXPRESSION\n");
                    break;
                }
            }
            if (exp[i] == '}')
            {
                if (s.stk[s.top] == '{')
                {
                    pop(); 
                }
                else
                {
                    printf("\nUNBALANCED EXPRESSION\n");
                    break;
                }
            }
        }
    }
    if (s.top == -1)
    {
        printf("\nBALANCED EXPRESSION\n"); 
    }
}

int main()
{
    char *exp;
    exp =(char *)malloc(MAX_EXPR_SIZE);
    printf("Enter a Expression:");
    fgets(exp, MAX_EXPR_SIZE, stdin);
    checkparenthesis(exp);
    free(exp);
    return 0;
}
