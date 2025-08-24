#include <assert.h>
#include <math.h>
#include "square_solver.h"

int equation_solver(double *coefficients, double* roots)
{
    assert (!check_null(roots[0]));
    assert (!check_null(roots[1]));
    assert (!double_comparison(roots[0], roots[1]));

    assert (!isnan(coefficients[0]));
    assert (!isnan(coefficients[1]));
    assert (!isnan(coefficients[2]));


    if (check_null(coefficients[0]))
    {
        return linear_solver(coefficients, roots);
    }
    else
    {
        return square_solver(coefficients, roots);
    }
}

int square_solver(double *coefficients, double* roots)

{
    assert (!check_null(roots[0]));
    assert (!check_null(roots[1]));
    assert (!double_comparison(roots[0], roots[1]));

    assert (!isnan(coefficients[0]));
    assert (!isnan(coefficients[1]));
    assert (!isnan(coefficients[2]));

    double discriminant = discriminant_calculate(coefficients);

    if (discriminant < 0)
    {
        return NO_ROOTS;
    }
    else if (check_null(discriminant))
    {
        roots[0] = -coefficients[1]/(2*coefficients[0]);

        if (check_null(roots[0]))
        {
            roots[0] = 0;
        }

        return ONE_ROOT;
    }
    else
    {
        double sqrt_discriminant = sqrt(discriminant);

        roots[0] = (-coefficients[1]+sqrt_discriminant)/(2*coefficients[0]);
        roots[1] = (-coefficients[1]-sqrt_discriminant)/(2*coefficients[0]);

        if (check_null(roots[0]))
        {
            roots[0] = 0;
        }
        if (check_null(roots[1]))
        {
            roots[1] = 0;
        }
        return TWO_ROOTS;
    }

}
int check_null(double root)
{
    return fabs(root) < INACCURACY;
}

int linear_solver(double* coefficients, double* roots)
{
    assert (!check_null(roots[0]));

    assert (!isnan(coefficients[1]));
    assert (!isnan(coefficients[2]));

    if (check_null(coefficients[1]))
    {
        if (check_null(coefficients[2]))
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
        roots[0] = -coefficients[2]/coefficients[1];

        return ONE_ROOT;
    }
}

double discriminant_calculate(double *coefficients)
{
    return (coefficients[1]*coefficients[1]-4*coefficients[0]*coefficients[2]);
}
