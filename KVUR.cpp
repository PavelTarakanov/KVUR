#include <stdio.h>
#include <math.h>
#include <assert.h>

int check_null(double root);

int equation_solver(double coefficient_a, double coefficient_b, double coefficient_c,
                    double* root_1,       double* root_2);
int square_solver(double coefficient_a, double coefficient_b, double coefficient_c,
                  double* root_1,       double* root_2);

int linear_solver(double coefficient_b, double coefficient_c, double* root_1);

double diskr_calculate(double coefficient_a, double coefficient_b, double coefficient_c);

int input_coefficients(double* coefficient_a, double* coefficient_b, double* coefficient_c);
double scanf_check(double* coefficient_a);
void cleaner(void);

int finish(bool* more);

int output_roots(int root_count,double root_1,double root_2);

void test_square_solver();

void one_test_square_solver(
    double coefficient_a, double coefficient_b, double coefficient_c,
    double true_root_1,   double true_root_2,   int true_nRoots,
    double* root_1,       double* root_2);

void root_changer(double* root_1, double* root_2);

enum Number_of_Roots
{
NO_ROOTS = 0,
ONE_ROOT = 1,
TWO_ROOTS = 2,
INF_ROOTS = -1
};
const double INACCURACY = 0.0001;
int main(void)
{
    double coefficient_a = NAN, coefficient_b = NAN, coefficient_c = NAN;
    double root_1 = NAN, root_2 = NAN;
    bool is_continue = true;

    test_square_solver();

    while (is_continue)
    {
        input_coefficients(&coefficient_a, &coefficient_b, &coefficient_c);

        int root_count = equation_solver(coefficient_a, coefficient_b, coefficient_c, &root_1, &root_2);

        output_roots(root_count, root_1, root_2);

        finish(&is_continue);
    }
    return 0;

}

int input_coefficients(double* coefficient_a, double* coefficient_b, double* coefficient_c)
{
    assert (coefficient_a);
    assert (coefficient_b);
    assert (coefficient_c);

    assert (coefficient_a != coefficient_b);
    assert (coefficient_b != coefficient_c);
    assert (coefficient_a != coefficient_c);

    printf("Input X^2 coefficient: ");
    scanf_check(coefficient_a);

    printf("Input X coefficient: ");
    scanf_check(coefficient_b);

    printf("Input free coefficient: ");
    scanf_check(coefficient_c);

    return 0;
}

double scanf_check(double* coefficient_a)
 {
    assert (coefficient_a);

    int is_number = -1;

    while ((is_number = scanf("%lf", coefficient_a)) != 1)
    {
        printf("Input number!\n");

        cleaner();
    }
    return 0;
}

void cleaner(void)
{
    while (getchar() != '\n')
        {
            continue;
        }
}
int equation_solver(double coefficient_a, double coefficient_b, double coefficient_c,
                     double* root_1,       double* root_2)
{
    if (check_null(coefficient_a))
    {
        return linear_solver(coefficient_b, coefficient_c, root_1);
    }
    else
    {
        return square_solver(coefficient_a, coefficient_b, coefficient_c,
                             root_1, root_2);
    }
}
int square_solver(double  coefficient_a,  double  coefficient_b, double coefficient_c,
                  double* root_1, double* root_2)

{
    assert (root_1);
    assert (root_2);
    assert (root_1 != root_2);


    double diskr = diskr_calculate(coefficient_a, coefficient_b, coefficient_c);

    if (diskr < 0)
    {
        return NO_ROOTS;
    }
    else if (check_null(diskr))
    {
        *root_1 = -coefficient_b/(2*coefficient_a);

        if (check_null(*root_1))
        {
            *root_1 = 0;
        }

        return ONE_ROOT;
    }
    else
    {
        double sqrt_diskr = sqrt(diskr);

        *root_1 = (-coefficient_b+sqrt_diskr)/(2*coefficient_a);
        *root_2 = (-coefficient_b-sqrt_diskr)/(2*coefficient_a);

        if (check_null(*root_1))
        {
            *root_1 = 0;
        }
        if (check_null(*root_2))
        {
            *root_2 = 0;
        }
        return TWO_ROOTS;
    }

}

void test_square_solver()
{
    double root_1 = NAN, root_2 = NAN;

    one_test_square_solver(1, -5,  6,  2,  3, 2, &root_1, &root_2 );
    one_test_square_solver(1, -2,  1,  1,  0, 1, &root_1, &root_2 );
    one_test_square_solver(0,  0,  1,  0,  0, 0, &root_1, &root_2 );
}

void one_test_square_solver(double coefficient_a, double coefficient_b, double coefficient_c,
                            double true_root_1,   double true_root_2,   int true_nRoots,
                            double* root_1,       double* root_2)
{
    assert (root_1);
    assert (root_2);
    assert (root_1 != root_2);

    int nRoots =  equation_solver(coefficient_a, coefficient_b, coefficient_c, root_1, root_2);

    if (nRoots == 2)
    {

        root_changer(root_1, root_2);

        if (!(nRoots == true_nRoots && *root_1 == true_root_1 && *root_2 == true_root_2))
        {
            printf("ERROR: square_solver(%lf, %lf, %lf, ...), nRoots == %d, root_1 = %lf, root_2 = %lf\n",
                    coefficient_a, coefficient_b, coefficient_c, nRoots, *root_1, *root_2);
            printf("Correct answer: nRoots = %d, root_1 = %lf, root_2 = %lf\n",
                    true_nRoots, true_root_1, true_root_2);
        }
    }

    if (nRoots == 1)
    {
        if (!(nRoots == true_nRoots && *root_1 == true_root_1))
        {
            printf("ERROR: square_solver(%lf, %lf, %lf, ...), nRoots = %d, root_1 = %lf\n",
                    coefficient_a, coefficient_b, coefficient_c, nRoots, *root_1);
            printf("Correct answer: nRoots = %d, root = %lf\n",
                    true_nRoots, true_root_1);
        }
    }
    if (nRoots == 0)
    {
        if (nRoots != true_nRoots)
        {
        printf("ERROR: square_solver(%lf, %lf, %lf, ...), nRoots = %d\n",
                    coefficient_a, coefficient_b, coefficient_c, nRoots);
        printf("Correct answer: nRoots = %d\n",
                    true_nRoots);
        }
    }
}

void root_changer(double *root_1, double *root_2)
{
    assert (root_1);
    assert (root_2);
    assert (root_1 != root_2);

    double tmp = NAN;
    if (root_1 > root_2)
    {
        tmp = *root_1;
        *root_1 = *root_2;
        *root_2 = tmp;
    }
}

int check_null(double root)
{
    return fabs(root) < INACCURACY;
}

int linear_solver(double coefficient_b, double coefficient_c,
                  double* root_1)
{
    assert (root_1);

    if (check_null(coefficient_b))
    {
        if (check_null(coefficient_c))
        {
            return INF_ROOTS;
        }
        else
        {
            return NO_ROOTS;
        }
    }
    else
    {
        *root_1 = -coefficient_c/coefficient_b;

        return ONE_ROOT;
    }
}

double diskr_calculate(double coefficient_a, double coefficient_b, double coefficient_c)
{
    return (coefficient_b*coefficient_b-4*coefficient_a*coefficient_c);
}

int output_roots(int root_count, double root_1, double root_2)
{
    switch(root_count)
    {
        case NO_ROOTS: printf("Equation has no roots\n");
                        break;
        case ONE_ROOT: printf("Answer: x = %lf\n", root_1);
                        break;
        case TWO_ROOTS: printf("Answer: x1 = %lf , x2 = %lf\n", root_1, root_2);
                        break;
        case INF_ROOTS: printf("Equation is always correct(all x are roots\n");
                break;
        default: printf("Mistake!");
                break;
    }

    return 0;
}

int finish(bool* is_continue)
{
    assert (is_continue);

    int m_or_s = 0;

    printf("If you want to continue input m\n");
    printf("If you want to finish programm input s\n");

    while (1)
    {
        cleaner();

        m_or_s = getchar();

        if (m_or_s == 's')
        {
            *is_continue = false;

            break;
        }
        else if (m_or_s == 'm')
        {
            break;
        }
        else
        {
            printf("If you want to continue input m\n");
            printf("If you want to finish programm input s\n");

            continue;
        }
    }
    return 0;
}
