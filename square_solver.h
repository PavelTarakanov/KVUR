#ifndef SQUARE_SOLVER_H
#define SQUARE_SOLVER_H

struct SquareEquationData {double coefficient_a, coefficient_b, coefficient_c;
                           double root_1, root_2;
                           int nRoots;};

struct SquareEquationDataTests {double correct_root_1, correct_root_2;
                                int correct_nRoots;};

int check_null(double root);

int equation_solver(SquareEquationData* test);
int square_solver(SquareEquationData* test);
int linear_solver(SquareEquationData* test);

double discriminant_calculate(SquareEquationData* test);

int input_coefficients(SquareEquationData* test);
int one_scanf(double* coefficient, const char* const output);

void clean_buffer(void);
int check_buffer(void);

int finish_program(bool* more);

int double_comparison(double number_1, double number_2);

int output_roots(int root_count, SquareEquationData* test);

void test_square_solver();

void one_test_square_solver(SquareEquationData* test_coefficients,
                            SquareEquationDataTests* test_answers);

void root_sorter(SquareEquationData* test);

enum Number_of_Roots
{
    NO_ROOTS = 0,
    ONE_ROOT = 1,
    TWO_ROOTS = 2,
    INF_ROOTS = -1
};

const double INACCURACY = 0.0001;

#endif //SQUARE_SOLVER_H
