#include <assert.h>
#include <stdio.h>
#include "square_solver.h"

int input_coefficients(SquareEquationData* test)
{
    assert (test);

    one_scanf(&test->coefficient_a, "Input X^2 coefficient: ");

    one_scanf(&test->coefficient_b, "Input X coefficient: ");

    one_scanf(&test->coefficient_c, "Input free coefficient: ");

    return 0;
}

int one_scanf(double* coefficient, const char* const output)
 {
    assert (coefficient);
    assert (output);

    printf("%s", output);

    int is_number = -1;

    while ((is_number = scanf("%lf", coefficient)) != 1 || check_buffer() == 1)
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

int check_buffer(void)
{
    int ch = ' ';
    while ((ch = getchar()) != '\n')
    {
        if  (ch != '\n' && ch != ' ')
        {
            return 1;
        }
    }
    return 0;
}
