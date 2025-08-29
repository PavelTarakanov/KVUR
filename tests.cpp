#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "square_solver.h"

void test_square_solver(FILE* file_address)
{
    const int NUMBER_OF_TESTS = 10;

    coefficients_data tests_coefficients[NUMBER_OF_TESTS] =  {};
    solutions_data tests_solutions[NUMBER_OF_TESTS] =  {};
    solutions_data tests_reference_solutions[NUMBER_OF_TESTS] = {};

    for (int tests_counter = 0; tests_counter < NUMBER_OF_TESTS; tests_counter++)
    {
        file_input_tests(file_address, tests_counter, tests_coefficients, tests_reference_solutions);

        int symbol = 0;

        if ((symbol = getc(file_address)) == EOF)
        {
            break;
        }
    }

    size_t real_number_of_tests = sizeof(tests_coefficients)/sizeof(tests_coefficients[0]);

    bool is_tests_correct = true;

    for (size_t i = 0; i < real_number_of_tests; i++)
    {
        one_test_square_solver(&tests_coefficients[i], &tests_solutions[i], &tests_reference_solutions[i],
                               &is_tests_correct);
    }

    if (is_tests_correct)
    {
        printf("All tests passed successfully\n");
    }
}

void one_test_square_solver(coefficients_data* test_coefficients, solutions_data* tests_solutions,
                            solutions_data* tests_reference_solutions,
                            bool* is_tests_correct)
{
    assert (test_coefficients);
    assert (tests_solutions);
    assert (tests_reference_solutions);

    equation_solver(test_coefficients, tests_solutions);

    root_sorter(tests_solutions); //TODO colorful text with "escape - sequences"

    if (!(tests_solutions->nRoots == tests_reference_solutions->nRoots
        && double_equal_comparison(tests_reference_solutions->root_1, tests_reference_solutions->root_1)
        && double_equal_comparison(tests_reference_solutions->root_2, tests_reference_solutions->root_2)))
    {
        print_error_massage(test_coefficients, tests_solutions, tests_reference_solutions);
        *is_tests_correct = false;
    } //TODO good_message
}

void root_sorter(solutions_data* solutions)
{
    assert (solutions);

    double tmp = NAN;
    if (solutions->root_1 > solutions->root_2)
    {
        tmp = solutions->root_1;
        solutions->root_1 = solutions->root_2;
        solutions->root_2 = tmp;
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

void print_error_massage(coefficients_data* coefficients,
                            solutions_data* solutions,
                            solutions_data* reference_solutions)
{
    printf("ERROR: square_solver(%lf, %lf, %lf, ...), nRoots == %d, root_1 = %lf, root_2 = %lf\n"
           "Correct answer: nRoots = %d, root_1 = %lf, root_2 = %lf\n",
           coefficients->coefficient_a, coefficients->coefficient_b, coefficients->coefficient_c,
           solutions->nRoots, solutions->root_1, solutions->root_2,
           reference_solutions->nRoots, reference_solutions->root_1, reference_solutions->root_2);
    return;
}

void file_input_tests(FILE* file_address, int tests_counter, coefficients_data* tests_coefficients,
                      solutions_data* tests_reference_solutions) //TODO return return value of scanf and check to EOF and num of scanf value
{
    fscanf(file_address, "%lf %lf %lf %lf %lf %d",
           &tests_coefficients[tests_counter].coefficient_a,
           &tests_coefficients[tests_counter].coefficient_b,
           &tests_coefficients[tests_counter].coefficient_c,
           &tests_reference_solutions[tests_counter].root_1,
           &tests_reference_solutions[tests_counter].root_2,
   (int *) &tests_reference_solutions[tests_counter].nRoots);

   return;
}
