/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 00:45:35 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/10/16 13:46:32 by acastrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Tokens
	DIGIT '0-9'
	PLUS '+'
	TIMES '*'
	PARENTHESIS '()'
*/

/*Grammar
expr   → term { '+' term }
term   → factor { '*' factor }
factor → DIGIT | '(' expr ')'
*/

/* Example
( 3 + 4 ) * 5
 
expr
 → term
   → factor * factor
     → '(' expr ')' * DIGIT
       → '(' term + term ')' * DIGIT
         → '(' factor + factor ')' * DIGIT
           → '(' DIGIT + DIGIT ')' * DIGIT

*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

static long parse_expr(char **expression);
static long parse_term(char **expression);
static long parse_factor(char **expression);

// Parses expression
// expr   → term { '+' term }
// Las priority on parse tree
static long parse_expr(char **expression)
{
    long    val;
    long    rhs;

    val = parse_term(expression); // Down call to parse term
    while (**expression == '+')
    {
        (*expression)++;
        val += parse_term(expression);
        val += rhs;
    }
    return (val);
}

// Parses term
// term   → factor { '*' factor }
static long parse_term(char **expression)
{
    long    val;
    long    rhs;

    val = parse_factor(expression); // Down call to parse factor
    while (**expression == '*')
    {
        (*expression)++;
        rhs = parse_factor(expression);
        val *= rhs;
    }
    return (val);
}

// Parses factor (down of dictionary)
// factor → DIGIT | '(' expr ')'
static long parse_factor(char **expression)
{
    long    val;

	// If there's a parenthesis, it takes over priority
    if (**expression == '(')
    {
        (*expression)++;
        val = parse_expr(expression); // Down top call to expression (change of priorities)
        if (**expression != ')') // If there's not closing ')', we throw syntax error
        {
            if (**expression == '\0')
                printf("Unexpected end of input\n");
            else
                printf("Unexpected token '%c'\n", **expression);
            exit(1);
        }
        (*expression)++;
        return (val); // Returns value of parenthesis
    }
    else if (isdigit(**expression)) // If is a digit, we reached the end of our dictionary
    {
        val = **expression - '0';
        (*expression)++;
        return (val);
    }
    else  // Factor doesn't start with DIGIT or BRACKET, syntax error
    {
        if (**expression == '\0')
            printf("Unexpected end of input\n");
        else
            printf("Unexpected token '%c'\n", **expression);
        exit(1);
    }
}

int main(int argc, char **argv)
{
	// First, a char  * to pass argv[1], and a long for result (avoid int overflow)
    char    *expresion;
    long    result;

	// Check for args and initalize variables 
    if (argc != 2)
        return 0;
    expresion = argv[1];
    result = parse_expr(&expresion); // This is where the magic happens!!!
    if (*expresion != '\0') // After reading all the lilne, if theres any symbol left is considered and syntax erro
    {
        printf("Unexpected token '%c'\n", *expresion);
        return (1);
    }
    printf("%ld\n", result); // Print a result and enjoy the rest of your day!!!
    return (0);
}
