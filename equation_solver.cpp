#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "square_solver.h"
/*!
Решает полученное ура
*/
void equation_solver(coefficients_data* coefficients, solutions_data* solutions)
{
    assert (coefficients);
    assert (solutions);

    assert (!isnan(coefficients->coefficient_a));
    assert (!isnan(coefficients->coefficient_b));
    assert (!isnan(coefficients->coefficient_c));

    if (check_null(coefficients->coefficient_a))
    {
        linear_solver(coefficients, solutions);
    }
    else
    {
        square_solver(coefficients, solutions);
    }
}

void square_solver(coefficients_data* coefficients, solutions_data* solutions)
{
    assert (coefficients);
    assert (solutions);

    assert (!isnan(coefficients->coefficient_a));
    assert (!isnan(coefficients->coefficient_b));
    assert (!isnan(coefficients->coefficient_c));

    double discriminant = discriminant_calculate(coefficients);

    if (discriminant < 0)
    {
        solutions->nRoots = NO_ROOTS;
    }
    else if (check_null(discriminant))
    {
        solutions->root_1 = (-coefficients->coefficient_b) / (2 * coefficients->coefficient_a);

        if (check_null(solutions->root_1))
        {
            solutions->root_1 = 0;
        }

        solutions->nRoots = ONE_ROOT;
    }
    else
    {
        double sqrt_discriminant = sqrt(discriminant);

        solutions->root_1 = (-(coefficients->coefficient_b) + sqrt_discriminant) / (2 * coefficients->coefficient_a);
        solutions->root_2 = (-(coefficients->coefficient_b) - sqrt_discriminant) / (2 *coefficients->coefficient_a);

        if (check_null(solutions->root_1))
        {
            solutions->root_1 = 0;
        }
        if (check_null(solutions->root_2))
        {
            solutions->root_2 = 0;
        }

        solutions->nRoots = TWO_ROOTS;
    }

    return;
}

void linear_solver(coefficients_data* coefficients, solutions_data* solutions)
{
    assert (coefficients);
    assert (solutions);

    assert (!isnan(coefficients->coefficient_b));
    assert (!isnan(coefficients->coefficient_c));

    if (check_null(coefficients->coefficient_b))
    {
        if (check_null(coefficients->coefficient_c))
        {
            solutions->nRoots = INF_ROOTS;
        }
        else
        {
            solutions->nRoots = NO_ROOTS;
        }
    }
    else
    {
        solutions->root_1 = -coefficients->coefficient_b / coefficients->coefficient_b;

        solutions->nRoots = ONE_ROOT;
    }

    return;
}

double discriminant_calculate(coefficients_data* coefficients)
{
    return ((coefficients->coefficient_b) * (coefficients->coefficient_b) - 4 * (coefficients->coefficient_a) * (coefficients->coefficient_c));
}

int check_null(double root)
{
    return fabs(root) < INACCURACY;
}
