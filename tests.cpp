#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "square_solver.h"

void test_square_solver(FILE* file_name)
{
    const int NUMBER_OF_TESTS = 10;

    square_equation_data tests_equation[NUMBER_OF_TESTS] =  {};
    reference_solutions_data tests_reference_solutions[NUMBER_OF_TESTS] = {};

    for (int tests_counter = 0; tests_counter < NUMBER_OF_TESTS; tests_counter++)
    {
        file_input_tests(file_name, tests_counter, tests_equation, tests_reference_solutions);

        int symbol = 0;

        if ((symbol = getc(file_name)) == EOF)
        {
            break;
        }
    }

    size_t size = sizeof(tests_equation)/sizeof(tests_equation[0]);

    for (size_t i = 0; i < size; i++)
    {
        one_test_square_solver(&tests_equation[i], &tests_reference_solutions[i]);
    }
}

void one_test_square_solver(square_equation_data* test_coefficients,
                            reference_solutions_data* test_answers)
{
    assert (test_coefficients);
    assert (test_answers);

    equation_solver(test_coefficients);

    root_sorter(test_coefficients); //TODO colorful text with "escape - sequences"

    if (!(test_coefficients->nRoots == test_answers->correct_nRoots
        && double_equal_comparison(test_coefficients->root_1, test_answers->correct_root_1)
        && double_equal_comparison(test_coefficients->root_2, test_answers->correct_root_2)))
    {
        print_error_massage(test_coefficients, test_answers);
    }
}

void root_sorter(square_equation_data* test)
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


bool double_equal_comparison(double number_1, double number_2)
{
    if (isnan(number_1) || isnan(number_2))
    {
        if (isnan(number_1) && isnan(number_2))
        {
            return true;
        }

        return false;
    }

    return abs(number_1 - number_2) < INACCURACY;
}

void print_error_massage(square_equation_data* test_coefficients,
                         reference_solutions_data* test_answers)
{
    printf("ERROR: square_solver(%lf, %lf, %lf, ...), nRoots == %d, root_1 = %lf, root_2 = %lf\n"
           "Correct answer: nRoots = %d, root_1 = %lf, root_2 = %lf\n",
           test_coefficients->coefficient_a, test_coefficients->coefficient_b, test_coefficients->coefficient_c,
           test_coefficients->nRoots, test_coefficients->root_1, test_coefficients->root_2,
           test_answers->correct_nRoots, test_answers->correct_root_1, test_answers->correct_root_2);
    return;
}

void file_input_tests(FILE* file_name, int tests_counter, square_equation_data* tests_equation,
                      reference_solutions_data* tests_reference_solutions)
{
    fscanf(file_name, "%lf %lf %lf %lf %lf %d %lf %lf %d",
           &tests_equation[tests_counter].coefficient_a,
           &tests_equation[tests_counter].coefficient_b,
           &tests_equation[tests_counter].coefficient_c,
           &tests_equation[tests_counter].root_1,
           &tests_equation[tests_counter].root_2,
   (int *) &tests_equation[tests_counter].nRoots,
           &tests_reference_solutions[tests_counter].correct_root_1,
           &tests_reference_solutions[tests_counter].correct_root_2,
   (int *) &tests_reference_solutions[tests_counter].correct_nRoots);
}
