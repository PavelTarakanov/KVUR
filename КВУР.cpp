#include <stdio.h>
#include <TXLib.h>
#include <math.h>

int square_solver(double a, double b, double c, double* x1, double* x2);
int if_nol(double x);
int lin_solver(double b, double c, double* x1);
double diskr_counter(double a, double b, double c);
double scanf_check(double* a);
int finish(int* more);
int input(double* a, double* b, double* c);
int output(int root_count,double x1,double x2);

int main(void)
{
    double a = NAN;
    double b = NAN;
    double c = NAN;
    double x1 = NAN;
    double x2 = NAN;
    int more = 1;
    while (more)
    {
    // Ввод
    input(&a, &b, &c);

    int root_count = square_solver(a, b, c, &x1, &x2);

    //Вывод
    output(root_count, x1, x2);


    finish(&more);
    }
    return 0;

}
int square_solver(double a, double b, double c,
                    double* x1, double* x2)
{
    assert(x1);
    assert(x2);

    if (if_nol(a))
    {
        int col = lin_solver(b, c, x1);
        return col;
    }
    else
    {
        double diskr = diskr_counter(a, b, c);
        if (diskr < 0)
            return 0;
        else if (if_nol(diskr))
        {
            *x1 = -b/(2*a);
            if (if_nol(*x1))
                *x1 = 0;
            return 1;
        }
        else
        {
            double sqrt_diskr = sqrt(diskr);
            *x1 = (-b+sqrt_diskr)/(2*a);
            *x2 = (-b-sqrt_diskr)/(2*a);
            return 2;
        }

    }
}

int if_nol(double x)//функция проверки не ноль ли
{
    if (x < 0.0001 && x > -0.0001)
    return 1;
    else
    return 0;
}

int lin_solver(double b, double c,
                    double* x1)
{
    assert (x1);
    if (if_nol(b))
    {
        if (if_nol(c))
            return -1;
        else
            return 0;
    }
    else
    {
        *x1 = -c/b;
        return 1;
    }
}
double diskr_counter(double a, double b, double c)
{
    return (b*b-4*a*c);
}
double scanf_check(double* a)
 {
    assert (a);
    int status = scanf("%lf", a);
    while (status != 1)
    {
        printf("Введите число!\n");
        while (getchar() != '\n')
            continue;
        status = scanf("%lf", a);
    }
    return 0;
}
int finish(int* more)
{
    assert (more);
    int m_or_s = 0;
    while (1)
    {
        m_or_s = getchar();
        if (m_or_s == 's')
        {
            *more = 0;
            break;
        }
        else if (m_or_s == 'm') {
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

int output(int root_count,double x1,double x2)
{
    switch(root_count)
    {
        case 0: printf("Нет действительных корней\n");
                break;
        case 1: printf("Ответ: х = %lf\n", x1);
                break;
        case 2: printf("Ответ: х1 = %lf , х2 = %lf\n", x1, x2);
                break;
        case -1: printf("Уравнение верно при любых х\n");
                    break;
        default: printf("Ошибка!");
                    break;
    }
    return 0;
}

int input(double* a, double* b, double* c)
{
    assert (a);
    assert (b);
    assert (c);
    printf("Введите коэффицент при X^2: ");
    scanf_check(a);
    printf("Введите коэффицент при Х: ");
    scanf_check(b);
    printf("Введите свободный член: ");
    scanf_check(c);
    return 0;
}
