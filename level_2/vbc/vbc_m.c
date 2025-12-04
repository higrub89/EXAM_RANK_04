#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

static long parse_expr(char **expression);
static long parse_term(char **expression);
static long parse_factor(char **expression);

static long parse_expr(char **expression)
{
    long    val = parse_term(expression);
    while (**expression == '+')
    {
        (*expression)++;
        val += parse_term(expression);
    }
    return val;
}

static long parse_term(char **expression)
{
    long    val = parse_factor(expression);
    while (**expression == '*')
    {
        (*expression)++;
        val *= parse_factor(expression);
    }
    return val;
}

static long parse_factor(char **expression)
{
    long    val;
    if (**expression == '(')
    {
        (*expression)++;
        val = parse_expr(expression);
        if (**expression != ')')
        {
            if (**expression == '\0')
                printf("Unexpected end of input\n");
            else
                printf("Unexpected token '%c'\n", **expression);
            exit(1);
        }
        (*expression)++;
        return val;
    }
    else if (isdigit(**expression))
    {
        val = **expression - '0';
        (*expression)++;
        return val;
    }
    else
    {
        if (**expression == '\0')
            printf("Unexpected end of input\n");
        else
            printf("Unexpected token '%c'\n", **expression);
        exit(1);
    }
}

int main(int ac, char **av)
{
    char    *expression;
    long    result;

    if (ac != 2)
        return 0;
    expression = av[1];
    result = parse_expr(&expression);
    
    if (*expression != '\0')
    {
        printf("Unexpected token '%c'\n", *expression);
        return 1;
    }
    printf("%ld\n", result);
    return 0;
}