#include <assert.h>
#include <stdio.h>
#include "square_solver.h"

int output_roots(int root_count, double *roots)
{
    switch(root_count)
    {
        case NO_ROOTS: printf("Equation has no roots\n");
                        break;
        case ONE_ROOT: printf("Answer: x = %lf\n", roots[0]);
                        break;
        case TWO_ROOTS: printf("Answer: x1 = %lf , x2 = %lf\n", roots[0], roots[1]);
                        break;
        case INF_ROOTS: printf("Equation is always correct(all x are roots\n");
                break;
        default: printf("Mistake!");
                break;
    }

    return 0;
}
