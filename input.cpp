#include <assert.h>
#include <stdio.h>
#include "square_solver.h"

int input_coefficients(double* coefficients)
{
    assert (!check_null(coefficients[0]));
    assert (!check_null(coefficients[1]));
    assert (!check_null(coefficients[2]));

    assert (!double_comparison(coefficients[0], coefficients[1]));
    assert (!double_comparison(coefficients[1], coefficients[2]));
    assert (!double_comparison(coefficients[0], coefficients[2]));

    one_scanf(&coefficients[0], "Input X^2 coefficient: ");

    one_scanf(&coefficients[1], "Input X coefficient: ");

    one_scanf(&coefficients[2], "Input free coefficient: ");

    return 0;
}

double one_scanf(double* coefficients, const char* const output)
 {
    assert (!check_null(coefficients[0]));

    printf("%s", output);

    int is_number = -1;

    while ((is_number = scanf("%lf", &coefficients[0])) != 1)
    {
        printf("Input number!\n");

        clean_buffer();
    }
    return 0;
}

void clean_buffer(void)
{
    while (getchar() != '\n')
        {
            continue;
        }
}
