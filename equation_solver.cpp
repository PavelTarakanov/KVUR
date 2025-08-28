#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "square_solver.h"

void equation_solver(square_equation_data* test)
{
    assert (test);

    assert (!isnan(test->coefficient_a));
    assert (!isnan(test->coefficient_b));
    assert (!isnan(test->coefficient_c));

    if (check_null(test->coefficient_a))
    {
        linear_solver(test);
    }
    else
    {
        square_solver(test);
    }
}

void square_solver(square_equation_data* test)
{
    assert (test);

    assert (!isnan(test->coefficient_a));
    assert (!isnan(test->coefficient_b));
    assert (!isnan(test->coefficient_c));

    double discriminant = discriminant_calculate(test);

    if (discriminant < 0)
    {
        test->nRoots = NO_ROOTS;
    }
    else if (check_null(discriminant))
    {
        test->root_1 = (-test->coefficient_b) / (2 * test->coefficient_a);

        if (check_null(test->root_1))
        {
            test->root_1 = 0;
        }

        test->nRoots = ONE_ROOT;
    }
    else
    {
        double sqrt_discriminant = sqrt(discriminant);

        test->root_1 = (-(test->coefficient_b) + sqrt_discriminant) / (2 * test->coefficient_a);
        test->root_2 = (-(test->coefficient_b) - sqrt_discriminant) / (2 *test->coefficient_a);

        if (check_null(test->root_1))
        {
            test->root_1 = 0;
        }
        if (check_null(test->root_2))
        {
            test->root_2 = 0;
        }

        test->nRoots = TWO_ROOTS;
    }

    return;
}

void linear_solver(square_equation_data* test)
{
    assert (test);

    assert (!isnan(test->coefficient_b));
    assert (!isnan(test->coefficient_c));

    if (check_null(test->coefficient_b))
    {
        if (check_null(test->coefficient_c))
        {
            test->nRoots = INF_ROOTS;
        }
        else
        {
            test->nRoots = NO_ROOTS;
        }
    }
    else
    {
        test->root_1 = -test->coefficient_b / test->coefficient_b;

        test->nRoots = ONE_ROOT;
    }

    return;
}

double discriminant_calculate(square_equation_data* test)
{
    return ((test->coefficient_b) * (test->coefficient_b) - 4 * (test->coefficient_a) * (test->coefficient_c));
}

int check_null(double root)
{
    return fabs(root) < INACCURACY;
}
