#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "square_solver.h"

int equation_solver(SquareEquationData* test)
{
    assert (test);

    assert (!isnan(test->coefficient_a));
    assert (!isnan(test->coefficient_b));
    assert (!isnan(test->coefficient_c));


    if (check_null(test->coefficient_a))
    {
        return linear_solver(test);
    }
    else
    {
        return square_solver(test);
    }
}

int square_solver(SquareEquationData* test)

{
    assert (test);

    assert (!isnan(test->coefficient_a));
    assert (!isnan(test->coefficient_b));
    assert (!isnan(test->coefficient_c));

    double discriminant = discriminant_calculate(test);


    if (discriminant < 0)
    {
        return NO_ROOTS;
    }
    else if (check_null(discriminant))
    {
        test->root_1 = (-test->coefficient_b)/(2*test->coefficient_a);

        if (check_null(test->root_1))
        {
            test->root_1 = 0;
        }

        return ONE_ROOT;
    }
    else
    {
        double sqrt_discriminant = sqrt(discriminant);

        test->root_1 = (-(test->coefficient_b)+sqrt_discriminant)/(2*test->coefficient_a);
        test->root_2 = (-(test->coefficient_b)-sqrt_discriminant)/(2*test->coefficient_a);

        if (check_null(test->root_1))
        {
            test->root_1 = 0;
        }
        if (check_null(test->root_2))
        {
            test->root_2 = 0;
        }
        return TWO_ROOTS;
    }

}
int check_null(double root)
{
    return fabs(root) < INACCURACY;
}

int linear_solver(SquareEquationData* test)
{
    assert (test);

    assert (!isnan(test->coefficient_b));
    assert (!isnan(test->coefficient_c));

    if (check_null(test->coefficient_b))
    {
        if (check_null(test->coefficient_c))
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
        test->root_1 = -test->coefficient_b/test->coefficient_b;

        return ONE_ROOT;
    }
}

double discriminant_calculate(SquareEquationData* test)
{
    return ((test->coefficient_b)*(test->coefficient_b)-4*(test->coefficient_a)*(test->coefficient_c));
}
