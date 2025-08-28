#include <assert.h>
#include <stdio.h>
#include "square_solver.h"

void output_roots(square_equation_data* test)
{
    assert(test);

    switch(test->nRoots)
    {
        case NO_ROOTS:
            printf("Equation has no roots\n");
            break;
        case ONE_ROOT:
            printf("Answer: x = %lf\n", test->root_1);
            break;
        case TWO_ROOTS:
            printf("Answer: x1 = %lf , x2 = %lf\n", test->root_1, test->root_2);
            break;
        case INF_ROOTS:
            printf("Equation is always correct(all x are roots\n");
            break;
        case UNKNOWN_NUMBER_OF_ROOTS:
        default:
            printf("Mistake!\n");
            break;
    }
    return;
}
