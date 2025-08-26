#ifndef SQUARE_SOLVER_H
#define SQUARE_SOLVER_H

enum Number_of_Roots
{
    NO_ROOTS = 0,
    ONE_ROOT = 1,
    TWO_ROOTS = 2,
    INF_ROOTS = -1,
    UNKNOWN_NUMBER_OF_ROOTS = 3
};

struct square_equation_data_coefficients {double coefficient_a, coefficient_b, coefficient_c;
                            double root_1, root_2;
                            Number_of_Roots nRoots;};

struct square_equation_data_correct {double correct_root_1, correct_root_2;
                                   Number_of_Roots correct_nRoots;};

int check_null(double root);

int equation_solver(square_equation_data_coefficients* test);
int square_solver(square_equation_data_coefficients* test);
int linear_solver(square_equation_data_coefficients* test);

double discriminant_calculate(square_equation_data_coefficients* test);

void input_coefficients(square_equation_data_coefficients* test);
void one_scanf(double* coefficient, const char* const output);

void clean_buffer(void);
int check_buffer_not_clear(void);

void finish_program(bool* more);

int double_equal_comparison(double number_1, double number_2);

void output_roots(int root_count, square_equation_data_coefficients* test);

void test_square_solver();

void one_test_square_solver(square_equation_data_coefficients* test_coefficients,
                            square_equation_data_correct* test_answers);

void root_sorter(square_equation_data_coefficients* test);

const double INACCURACY = 0.0001;

#endif //SQUARE_SOLVER_H
