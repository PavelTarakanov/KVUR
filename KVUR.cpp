#include <stdio.h>
#include <TXLib.h>
#include <math.h>

int ckeck_null(double root);

int square_solver(double coefficient_a, double coefficient_b, double coefficient_c,
                  double* root_1,       double* root_2);

int linear_solver(double coefficient_b, double coefficient_c, double* root_1);

double diskr_calculate(double coefficient_a, double coefficient_b, double coefficient_c);

int input(double* coefficient_a, double* coefficient_b, double* coefficient_c);
double scanf_check(double* coefficient_a);
void cleaner(void);

int finish(bool* more);

int output(int root_count,double root_1,double root_2);

void test_square_solver();

void one_test_square_solver(
    double coefficient_a, double coefficient_b, double coefficient_c,
    double true_root_1,   double true_root_2,   int true_nRoots,
    double* root_1,       double* root_2);

void root_changer(double* root_1, double* root_2);

int main(void)
{
    double coefficient_a = NAN, coefficient_b = NAN, coefficient_c = NAN;
    double root_1 = NAN, root_2 = NAN;
    bool is_continue = true;

    test_square_solver();

    while (is_continue)
    {
        input(&coefficient_a, &coefficient_b, &coefficient_c);

        int root_count = square_solver(coefficient_a, coefficient_b, coefficient_c, &root_1, &root_2);

        output(root_count, root_1, root_2);

        finish(&is_continue);
    }
    return 0;

}

int input(double* coefficient_a, double* coefficient_b, double* coefficient_c)
{
    assert (coefficient_a);
    assert (coefficient_b);
    assert (coefficient_c);

    assert (coefficient_a != coefficient_b);
    assert (coefficient_b != coefficient_c);
    assert (coefficient_a != coefficient_c);

    printf("Введите коэффицент при X^2: ");
    scanf_check(coefficient_a);

    printf("Введите коэффицент при Х: ");
    scanf_check(coefficient_b);

    printf("Введите свободный член: ");
    scanf_check(coefficient_c);

    return 0;
}

double scanf_check(double* coefficient_a)
 {
    assert (coefficient_a);

    int is_number = NAN;

    while ((is_number = scanf("%lf", coefficient_a)) != 1)
    {
        printf("Введите число!\n");

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
int square_solver(double  coefficient_a,  double  coefficient_b, double coefficient_c,
                  double* root_1, double* root_2)

{
    assert(root_1);
    assert(root_2);
    assert(root_1 != root_2);

    if (ckeck_null(coefficient_a))
    {
        return linear_solver(coefficient_b, coefficient_c, root_1);
    }
    else
    {
        double diskr = diskr_calculate(coefficient_a, coefficient_b, coefficient_c);

        if (diskr < 0)
        {
            return 0;
        }
        else if (ckeck_null(diskr))
        {
            *root_1 = -coefficient_b/(2*coefficient_a);

            if (ckeck_null(*root_1))
            {
                *root_1 = 0;
            }

            return 1;
        }
        else
        {
            double sqrt_diskr = sqrt(diskr);

            *root_1 = (-coefficient_b+sqrt_diskr)/(2*coefficient_a);
            *root_2 = (-coefficient_b-sqrt_diskr)/(2*coefficient_a);

            if (ckeck_null(*root_1))
            {
                *root_1 = 0;
            }
            if (ckeck_null(*root_2))
            {
                *root_2 = 0;
            }
            return 2;
        }

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

    int nRoots =  square_solver(coefficient_a, coefficient_b, coefficient_c, root_1, root_2);

    if (nRoots == 2)
    {

        root_changer(root_1, root_2);

        if (!(nRoots == true_nRoots && *root_1 == true_root_1 && *root_2 == true_root_2))
        {
            printf("Произошла ошибка: square_solver(%lf, %lf, %lf, ...), nRoots == %d, root_1 = %lf, root_2 = %lf\n",
                    coefficient_a, coefficient_b, coefficient_c, nRoots, *root_1, *root_2);
            printf("Правильный ответ: nRoots = %d, root_1 = %lf, root_2 = %lf\n",
                    true_nRoots, true_root_1, true_root_2);
        }
    }

    if (nRoots == 1)
    {
        if (!(nRoots == true_nRoots && *root_1 == true_root_1))
        {
            printf("Произошла ошибка: square_solver(%lf, %lf, %lf, ...), nRoots = %d, root_1 = %lf\n",
                    coefficient_a, coefficient_b, coefficient_c, nRoots, *root_1);
            printf("Правильный ответ: nRoots = %d, root = %lf\n",
                    true_nRoots, true_root_1);
        }
    }
    if (nRoots == 0)
    {
        if (nRoots != true_nRoots)
        {
        printf("Произошла ошибка: square_solver(%lf, %lf, %lf, ...), nRoots = %d\n",
                    coefficient_a, coefficient_b, coefficient_c, nRoots);
        printf("Правильный ответ: nRoots = %d\n",
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

int ckeck_null(double root)
{
    return fabs(root) < 0.0001;
}

int linear_solver(double coefficient_b, double coefficient_c,
                  double* root_1)
{
    assert (root_1);

    if (ckeck_null(coefficient_b))
    {
        if (ckeck_null(coefficient_c))
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        *root_1 = -coefficient_c/coefficient_b;

        return 1;
    }
}

double diskr_calculate(double coefficient_a, double coefficient_b, double coefficient_c)
{
    return (coefficient_b*coefficient_b-4*coefficient_a*coefficient_c);
}

int output(int root_count, double root_1, double root_2)
{
    switch(root_count)
    {
        case 0: printf("Нет действительных корней\n");
                break;
        case 1: printf("Ответ: х = %lf\n", root_1);
                break;
        case 2: printf("Ответ: х1 = %lf , х2 = %lf\n", root_1, root_2);
                break;
        case -1: printf("Уравнение верно при любых х\n");
                break;
        default: printf("Ошибка!");
                break;
    }

    return 0;
}

int finish(bool* is_continue)
{
    assert (is_continue);

    int m_or_s = 0;

    while (1)
    {
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
            printf("Для продолжения работы введите m\n");
            printf("Для завершения работы введите s\n");

            continue;
        }
    }
    return 0;
}
