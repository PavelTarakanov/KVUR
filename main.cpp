#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "square_solver.h"

int main(void)
{
    double coefficients [3] = {NAN, NAN, NAN};
    double roots[2] = {NAN, NAN};
    bool is_continue = true;

    test_square_solver();

    while (is_continue)
    {
        input_coefficients(coefficients);

        int root_count = equation_solver(coefficients, roots);

        output_roots(root_count, roots);

        finish_program(&is_continue);
    }

    return 0;
}

void test_square_solver()
{
    double roots[2] = {NAN, NAN};

    double coefficients_1[3] = {1, -5, 6};
    one_test_square_solver(coefficients_1,  2,  3, 2, roots);
    double coefficients_2[3] = {1, -2, 1};
    one_test_square_solver(coefficients_2,  1,  0, 1, roots);
    double coefficients_3[3] = {0, 0, 1};
    one_test_square_solver(coefficients_3,  0,  0, 0, roots);
}

void one_test_square_solver(double coefficients[3],
                            double true_root_1,   double true_root_2,   int true_nRoots,
                            double roots[2])
{
    assert (!check_null(roots[0]));
    assert (!check_null(roots[1]));
    assert (!double_comparison(roots[0], roots[1]));

    int nRoots =  equation_solver(coefficients, roots);

    if (nRoots == 2)
    {
        root_sorter(roots);

        if (!(nRoots == true_nRoots && double_comparison(roots[0], true_root_1)
            && double_comparison(roots[1], true_root_2)))
        {
            printf("ERROR: square_solver(%lf, %lf, %lf, ...), nRoots == %d, root_1 = %lf, root_2 = %lf\n",
                    coefficients[0], coefficients[1],coefficients[2],
                    nRoots, roots[0], roots[1]);
            printf("Correct answer: nRoots = %d, root_1 = %lf, root_2 = %lf\n",
                    true_nRoots, true_root_1, true_root_2);
        }
    }

    if (nRoots == 1)
    {
        if (!(nRoots == true_nRoots && double_comparison(roots[0], true_root_1)))

        {
            printf("ERROR: square_solver(%lf, %lf, %lf, ...), nRoots == %d, root_1 = %lf, root_2 = %lf\n",
                    coefficients[0], coefficients[1],coefficients[2],
                    nRoots, roots[0], roots[1]);
            printf("Correct answer: nRoots = %d, root_1 = %lf, root_2 = %lf\n",
                    true_nRoots, true_root_1, true_root_2);
        }
    }
    if (nRoots == 0)
    {
        if (nRoots != true_nRoots)
        {
        printf("ERROR: square_solver(%lf, %lf, %lf, ...), nRoots == %d, root_1 = %lf, root_2 = %lf\n",
                    coefficients[0], coefficients[1],coefficients[2],
                    nRoots, roots[0], roots[1]);
        printf("Correct answer: nRoots = %d, root_1 = %lf, root_2 = %lf\n",
                    true_nRoots, true_root_1, true_root_2);
        }
    }
}

void root_sorter(double roots[2])
{
    assert (!check_null(roots[0]));
    assert (!check_null(roots[1]));
    assert (!double_comparison(roots[0], roots[1]));

    double tmp = NAN;
    if (roots[0] > roots[1])
    {
        tmp = roots[0];
        roots[0] = roots[1];
        roots[1] = tmp;
    }
}

int finish_program(bool* is_continue)
{
    assert (is_continue);

    int want_solve_more = 0;

    printf("If you want to continue input m\n");
    printf("If you want to finish program input s\n");

    while (1)
    {
        clean_buffer();

        want_solve_more = getchar();

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

int double_comparison(double number_1, double number_2)
{
    double tmp = NAN;

    if (number_1 > number_2)
    {
        tmp = number_1;
        number_1 = number_2;
        number_2 = tmp;
    }

    return (number_1 + INACCURACY > number_2);
}
