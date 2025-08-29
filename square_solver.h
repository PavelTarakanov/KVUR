#ifndef SQUARE_SOLVER_H
#define SQUARE_SOLVER_H

enum Number_of_Roots
{
    INF_ROOTS               = -1,
    NO_ROOTS                =  0,
    ONE_ROOT                =  1,
    TWO_ROOTS               =  2,
    UNKNOWN_NUMBER_OF_ROOTS =  3
};

struct coefficients_data {double coefficient_a, coefficient_b, coefficient_c;};
struct solutions_data {
    double root_1, root_2;
    Number_of_Roots nRoots;
};

void Poltorashkas_greeting(void);

int check_null(double root);

void equation_solver(coefficients_data* coefficients, solutions_data* solutions);
void square_solver(coefficients_data* coefficients, solutions_data* solutions);
void linear_solver(coefficients_data* coefficients, solutions_data* solutions);

double discriminant_calculate(coefficients_data* coefficients);

void input_coefficients(coefficients_data* coefficients);
void input_coefficient(double* coefficient, const char* const output);

void clean_buffer(void);
bool check_buffer_not_clear(void);

void finish_program(bool* more);

bool double_equal_comparison(double number_1, double number_2);

void output_roots(solutions_data* solutions);

void test_square_solver(FILE* file_address);

void one_test_square_solver(coefficients_data* coefficients,
                            solutions_data* solutions,
                            solutions_data* reference_solutions,
                            bool* is_tests_correct);

void print_error_massage(coefficients_data* coefficients,
                            solutions_data* solutions,
                            solutions_data* reference_solutions);

int file_input_tests(FILE* file_name, int tests_counter, coefficients_data* tests_coefficients,
                      solutions_data* tests_reference_solutions);

void root_sorter(solutions_data* solutions);

void check_file_opening(const char *file_name, FILE** file_ptr);
void check_file_closing(FILE* file_name);

const double INACCURACY = 10e-5;
const int NUMBER_OF_FILES = 2;

#endif //SQUARE_SOLVER_H
//TODO read dynamic memory
//TODO ponyat' rasmer faila fseak ftell

