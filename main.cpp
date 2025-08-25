#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "square_solver.h"

int main(void)
{
    bool is_continue = true;
    SquareEquationData test = {.coefficient_a = NAN, .coefficient_b = NAN, .coefficient_c = NAN,
                     .root_1 = NAN, .root_2 = NAN,
                     .nRoots = 3};

    test_square_solver();

    while (is_continue)
    {
        input_coefficients(&test);

        int root_count = equation_solver(&test);

        output_roots(root_count, &test);

        finish_program(&is_continue);
    }

    return 0;
}


int finish_program(bool* is_continue)
{
    assert (is_continue);

    int want_solve_more = 0;

    printf("If you want to continue input m\n");
    printf("If you want to finish program input s\n");

    while (1)
    {
        want_solve_more = getchar();
        clean_buffer();

        if (want_solve_more == 's')
        {
            *is_continue = false;

            break;
        }
        else if (want_solve_more == 'm')
        {
            break;
        }
        else
        {
            printf("If you want to continue input m\n");
            printf("If you want to finish programm input s\n");

            continue;
        }
    }

    return 0;
}
