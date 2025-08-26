#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "square_solver.h"

void test_square_solver()
{
    square_equation_data_coefficients tests_coefficients[10] =  {};
    square_equation_data_correct tests_answers[10] = {};

    FILE* fp;
    fp = fopen("tests.txt", "r");

    square_equation_data_coefficients file_input_coefficients = {
            .coefficient_a = NAN, .coefficient_b = NAN, .coefficient_c = NAN,
            .root_1 = NAN, .root_2 = NAN,
            .nRoots = UNKNOWN_NUMBER_OF_ROOTS};

    square_equation_data_correct file_input_answers = {
            .correct_root_1 = NAN, .correct_root_2 = NAN,
            .correct_nRoots = UNKNOWN_NUMBER_OF_ROOTS};

    int tests_counter = 0;

    while (fscanf(fp, "%lf %lf %lf %lf %lf %d %lf %lf %d",
                  &file_input_coefficients.coefficient_a,
                  &file_input_coefficients.coefficient_b,
                  &file_input_coefficients.coefficient_c,
                  &file_input_coefficients.root_1,
                  &file_input_coefficients.root_2,
                  &file_input_coefficients.nRoots,
                  &file_input_answers.correct_root_1,
                  &file_input_answers.correct_root_2,
                  &file_input_answers.correct_nRoots) == 9)
    {
        tests_coefficients[tests_counter] = file_input_coefficients;
        tests_answers[tests_counter] = file_input_answers;

        tests_counter++;

        if (getc(fp) = EOF)
        {
            break;
        }

    }

    fclose (fp);

    size_t size = sizeof(tests_coefficients)/sizeof(tests_coefficients[0]);

    for (size_t i = 0; i < size; i++)
    {
        one_test_square_solver(&tests_coefficients[i], &tests_answers[i]);
    }
}

void one_test_square_solver(square_equation_data_coefficients* test_coefficients,
                            square_equation_data_correct* test_answers)
{
    assert (test_coefficients);
    assert (test_answers);

    int nRoots =  equation_solver(test_coefficients);

    root_sorter(test_coefficients);

    if (!(nRoots == test_answers->correct_nRoots
        && double_equal_comparison(test_coefficients->root_1, test_answers->correct_root_1)
        && double_equal_comparison(test_coefficients->root_2, test_answers->correct_root_2)))
    {
        printf("ERROR: square_solver(%lf, %lf, %lf, ...), nRoots == %d, root_1 = %lf, root_2 = %lf\n"
               "Correct answer: nRoots = %d, root_1 = %lf, root_2 = %lf\n",
                    test_coefficients->coefficient_a, test_coefficients->coefficient_b, test_coefficients->coefficient_c,
                    nRoots, test_coefficients->root_1, test_coefficients->root_2,
                    test_answers->correct_nRoots, test_answers->correct_root_1, test_answers->correct_root_2);
    }
}

void root_sorter(square_equation_data_coefficients* test)
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


int double_equal_comparison(double number_1, double number_2)
{
    if (isnan(number_1) || isnan(number_2))
    {
        if (isnan(number_1) && isnan(number_2))
        {
            return 1;
        }
        return 0;
    }
    return abs(number_1 - number_2) < INACCURACY;
}
