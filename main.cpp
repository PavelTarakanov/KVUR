#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "square_solver.h" //TODO read about bash script

int main(int argc, const char* argv[])
{
    FILE* file_name = NULL;
    bool is_continue = true;
    square_equation_data equation = {.coefficient_a = NAN, .coefficient_b = NAN, .coefficient_c = NAN,
                               .root_1 = NAN, .root_2 = NAN,
                               .nRoots = UNKNOWN_NUMBER_OF_ROOTS};

        if (argc<2)
    {
        fprintf(stderr, "Using %s file_name", argv[0]);
        exit(EXIT_FAILURE);
    }
    check_file_opening(argv[1], &file_name);

    test_square_solver(file_name);

    check_file_closing(file_name);

    Poltorashkas_greeting();

    while (is_continue)
    {
        input_coefficients(&equation);

        equation_solver(&equation);

        output_roots(&equation);

        finish_program(&is_continue);
    }

    return 0;
}


void finish_program(bool* is_continue)
{
    assert (is_continue);

    int want_solve_more = 0; //TODO rename

    printf("If you want to continue input m\n"
           "If you want to finish program input s\n");

    while (1)
    {
        want_solve_more = getchar();
        clean_buffer();

        if (want_solve_more == 's')
        {
            *is_continue = false;

            break;
        }
        else if (want_solve_more == 'm')
        {
            break;
        }

        printf("If you want to continue input m\n"
               "If you want to finish programm input s\n");
    }

    return;
}

void Poltorashkas_greeting(void)
{
        printf("Meow!\nPotlorashka welcomes you in SquareSolver programm\n");
}

void check_file_opening(const char *file_name, FILE** file_ptr)
{
    if ((*file_ptr = fopen(file_name, "r")) == NULL)
    {
        fprintf(stderr, "Can't open file\" %s\"\n", file_name);
        exit(EXIT_FAILURE);
    }
}
void check_file_closing(FILE* file_name)
{
    assert (file_name);

    if (fclose(file_name) != 0)
    {
        fprintf(stderr, "Error while closing file\n");
    }
}
