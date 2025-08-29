#include <assert.h>
#include <stdio.h>
#include "square_solver.h"

void input_coefficients(coefficients_data* coefficients)
{
    assert (coefficients);

    input_coefficient(&coefficients->coefficient_a, "Input X^2 coefficient: ");

    input_coefficient(&coefficients->coefficient_b, "Input X coefficient: ");

    input_coefficient(&coefficients->coefficient_c, "Input free coefficient: ");

    return;
}

void input_coefficient(double* coefficient, const char* const output)
{
    assert (coefficient);
    assert (output);

    printf("%s", output);

    int is_number = -1;

    while ((is_number = scanf("%lf", coefficient)) != 1 || check_buffer_not_clear())
    {
        printf("Input number!\n");
        clean_buffer();
    }

    return;
}

void clean_buffer(void)
{
    while (getchar() != '\n')
    {
        continue;
    }

    return;
}

bool check_buffer_not_clear(void)
{
    int symbol = ' ';
    while ((symbol = getchar()) != '\n')
    {
        if  (symbol != '\n' && symbol != ' ' && symbol != EOF)
        {
            return true;
        }
    }

    return false;
}
