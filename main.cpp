#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "square_solver.h"

int main()
{
    bool is_continue = true;
    square_equation_data_coefficients test = {.coefficient_a = NAN, .coefficient_b = NAN, .coefficient_c = NAN,
                               .root_1 = NAN, .root_2 = NAN,
                               .nRoots = UNKNOWN_NUMBER_OF_ROOTS};

    test_square_solver();

    printf("Meow!\nPotlorashka welcomes you in SquareSolver programm\n");

    while (is_continue)
    {
        input_coefficients(&test);

        int root_count = equation_solver(&test);

        output_roots(root_count, &test);

        finish_program(&is_continue);
    }
    return 0;
}


void finish_program(bool* is_continue)
{
    assert (is_continue);

    int want_solve_more = 0;

    printf("If you want to continue input m\n"
           "If you want to finish program input s\n");

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
    return;
}
