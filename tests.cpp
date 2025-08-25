#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "square_solver.h"

void test_square_solver()
{
    SquareEquationData tests_coefficients[] =  {
                        {.coefficient_a = 1, .coefficient_b = -5, .coefficient_c = 6,
                         .root_1 = NAN, .root_2 = NAN, .nRoots = 2},
                        {.coefficient_a = 1, .coefficient_b = -2, .coefficient_c = 1,
                         .root_1 = NAN, .root_2 = NAN, .nRoots = 2}
                        };
    SquareEquationDataTests tests_answers[] = {
                        {.correct_root_1 = 2, .correct_root_2 = 3,
                         .correct_nRoots = 2},
                        {.correct_root_1 = 1, .correct_root_2 = NAN,
                         .correct_nRoots = 1}
                        };



    size_t size = sizeof(tests_coefficients)/sizeof(tests_coefficients[0]);

    for (size_t i = 0; i < size; i++)
    {
        one_test_square_solver(&tests_coefficients[i], &tests_answers[i]);
    }
}

void one_test_square_solver(SquareEquationData* test_coefficients,
                            SquareEquationDataTests* test_answers)
{
    assert (test_coefficients);
    assert (test_answers);

    int nRoots =  equation_solver(test_coefficients);

    root_sorter(test_coefficients);

    if (!(nRoots == test_answers->correct_nRoots
        && double_comparison(test_coefficients->root_1, test_answers->correct_root_1)
        && double_comparison(test_coefficients->root_2, test_answers->correct_root_2)))
    {
        printf("ERROR: square_solver(%lf, %lf, %lf, ...), nRoots == %d, root_1 = %lf, root_2 = %lf\n"
               "Correct answer: nRoots = %d, root_1 = %lf, root_2 = %lf\n",
                    test_coefficients->coefficient_a, test_coefficients->coefficient_b, test_coefficients->coefficient_c,
                    nRoots, test_coefficients->root_1, test_coefficients->root_2,
                    test_answers->correct_nRoots, test_answers->correct_root_1, test_answers->correct_root_2);
    }
}

void root_sorter(SquareEquationData* test)
{
    assert (test);


    double tmp = NAN;
    if (test->root_1 > test->root_2)
    {
        tmp = test->root_1;
        test->root_1 = test->root_2;
        test->root_2 = tmp;
    }
}


int double_comparison(double number_1, double number_2)
{
    double tmp = NAN;

    if (isnan(number_1))
    {
        if (isnan(number_2))
        {
            return 1;
        }
        return 0;
    }

    if (number_1 > number_2)
    {
        tmp = number_1;
        number_1 = number_2;
        number_2 = tmp;
    }
    return (number_1 + INACCURACY > number_2);
}
