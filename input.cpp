#include <assert.h>
#include <stdio.h>
#include "square_solver.h"

void input_coefficients(square_equation_data_coefficients* test)
{
    assert (test);

    one_scanf(&test->coefficient_a, "Input X^2 coefficient: ");

    one_scanf(&test->coefficient_b, "Input X coefficient: ");

    one_scanf(&test->coefficient_c, "Input free coefficient: ");

    return;
}

void one_scanf(double* coefficient, const char* const output)
{
    assert (coefficient);
    assert (output);

    printf("%s", output);

    int is_number = -1;

    while ((is_number = scanf("%lf", coefficient)) != 1 || check_buffer_not_clear() == 1)
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

int check_buffer_not_clear(void)
{
    int symbol = ' ';
    while ((symbol = getchar()) != '\n')
    {
        if  (symbol != '\n' && symbol != ' ' && symbol != EOF)
        {
            return 1;
        }
    }
    return 0;
}
