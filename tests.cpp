#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "square_solver.h"

void test_square_solver(FILE* file_name)
{
    const int NUMBER_OF_TESTS = 10;

    square_equation_data tests_equation[NUMBER_OF_TESTS] =  {};
    reference_solutions_data tests_reference_solutions[NUMBER_OF_TESTS] = {};

    square_equation_data file_input_coefficients = {
            .coefficient_a = NAN, .coefficient_b = NAN, .coefficient_c = NAN,
            .root_1 = NAN, .root_2 = NAN,
            .nRoots = UNKNOWN_NUMBER_OF_ROOTS}; //TODO firs initialization - second open file and another

    reference_solutions_data file_input_answers = {
            .correct_root_1 = NAN, .correct_root_2 = NAN,
            .correct_nRoots = UNKNOWN_NUMBER_OF_ROOTS}; //TODO not copy useless

    int tests_counter = 0; //TODO func if fscanf is using more than one time, check EOF

    while (fscanf(file_name, "%lf %lf %lf %lf %lf %d %lf %lf %d",
                  &file_input_coefficients.coefficient_a,
                  &file_input_coefficients.coefficient_b,
                  &file_input_coefficients.coefficient_c,
                  &file_input_coefficients.root_1,
                  &file_input_coefficients.root_2,
          (int *) &file_input_coefficients.nRoots,
                  &file_input_answers.correct_root_1,
                  &file_input_answers.correct_root_2,
          (int *) &file_input_answers.correct_nRoots) == 9)
    {
        tests_equation[tests_counter] = file_input_coefficients;
        tests_reference_solutions[tests_counter] = file_input_answers;

        tests_counter++; //TODO while -> for

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
        printf("ERROR: square_solver(%lf, %lf, %lf, ...), nRoots == %d, root_1 = %lf, root_2 = %lf\n"
               "Correct answer: nRoots = %d, root_1 = %lf, root_2 = %lf\n",
                    test_coefficients->coefficient_a, test_coefficients->coefficient_b, test_coefficients->coefficient_c,
                    test_coefficients->nRoots, test_coefficients->root_1, test_coefficients->root_2,
                    test_answers->correct_nRoots, test_answers->correct_root_1, test_answers->correct_root_2); //TODO print_error_massage
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
