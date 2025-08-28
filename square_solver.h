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

struct square_equation_data {double coefficient_a, coefficient_b, coefficient_c;
                            double root_1, root_2;
                            Number_of_Roots nRoots;};

struct reference_solutions_data {
    double correct_root_1, correct_root_2;
    Number_of_Roots correct_nRoots;
};//TODO use struct for solutions and for coeff

void Poltorashkas_greeting(void);

int check_null(double root);

void equation_solver(square_equation_data* test);
void square_solver(square_equation_data* test);
void linear_solver(square_equation_data* test);

double discriminant_calculate(square_equation_data* test);

void input_coefficients(square_equation_data* test);
void input_coefficient(double* coefficient, const char* const output);

void clean_buffer(void);
bool check_buffer_not_clear(void);

void finish_program(bool* more);

bool double_equal_comparison(double number_1, double number_2);

void output_roots(square_equation_data* test);

void test_square_solver(FILE* file_name);

void one_test_square_solver(square_equation_data* test_coefficients,
                            reference_solutions_data* test_answers);

void root_sorter(square_equation_data* test);

void check_file_opening(const char *file_name, FILE** file_ptr);
void check_file_closing(FILE* file_name);

const double INACCURACY = 10e-5;

#endif //SQUARE_SOLVER_H
