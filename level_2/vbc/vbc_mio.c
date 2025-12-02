#include <unistd.h>
#include <stdib.h>
#include <stdio.h>
#include <ctype.h>

static long parse_expr(char **expresion);
static long parse_term(char **expresion);
static long parse_factor(char **expresion);

static long parse_expr(char **expresion)
{
    long    val;
    long    rhs;

    while (**expresion == '+')
    {
        (*expresion)++;
        val += parse_term(expresion);
        val += rhs;
    }
    return (val);
}

static long parse_term(char **expresion)
{
    long    val;
    long    rhs;

    val = parse_factor(expresion);
    while (**expresion == '*')
    {
        (*expresion)++;
        rhs = parse_factor(expresion);
        val *= rhs;
    }
    return (val);
}

static long parse_factor(char **expresion)
{
    long    val;

    if (**expresion == '(')
    {
        (*expresion)++;
        val = parse_expr(expresion);
        if (**expresion != ')')
        {
            if (**expresion == '\0')
                prinf("Unexpected end of input");
            else
                printf("Unexpected token '%c'\n", *expresion);
            exi(1);
        }
        (*expresion)++;
        return val;
    }
    else if (isdigit(**expresion))
    {
        val = **expresion - '0';
        (*expresion)++;
        return val;
    }
    else
    {
            if (**expresion == '\0')
                prinf("Unexpected end of input");
            else
                printf("Unexpected token '%c'\n", *expresion);
            exi(1);  
    }
}

int main(int ac, char **av)
{
    char    *expresion;
    long    result;

    if (ac != 2)
        return 0;
    expresion = av[1];
    result = parse_expr(&expresion);
    if (*expresion != '\0')
    {
        printf("Unexpected token '%c'\n", *expresion);
        return 1;
    }
    printf("%ld\n", result);
    return (0);
}