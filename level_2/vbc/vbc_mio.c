/* vbc.c – Rubén 02/94 → Arquitecto Senior approved */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

static char    *g_pos;

static void syntax_error(char c)
{
    if (c == '\0')
        printf("Unexpected end of input\n");
    else
        printf("Unexpected token '%c'\n", c);
    exit(1);
}

static long factor(void)
{
    long    v;

    if (*g_pos == '(') {
        g_pos++;
        v = parse_expr();
        if (*g_pos != ')')
            syntax_error(*g_pos ? *g_pos : '\0');
        g_pos++;
        return v;
    }
    if (!isdigit(*g_pos))
        syntax_error(*g_pos ? *g_pos : '\0');
    v = *g_pos++ - '0';
    return v;
}

static long term(void)
{
    long v = factor();

    while (*g_pos == '*')
        v *= factor(), g_pos++;
    return v;
}

static long parse_expr(void)
{
    long v = term();

    while (*g_pos == '+')
        v += term(), g_pos++;
    return v;
}

int main(int ac, char **av)
{
    long    res;

    if (ac != 2) return 0;
    g_pos = av[1];
    res = parse_expr();
    if (*g_pos) syntax_error(*g_pos);
    printf("%ld\n", res);
    return 0;
}