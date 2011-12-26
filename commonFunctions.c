#include <stdio.h>
#include <math.h>

#include "commonFunctions.h"



void swapTwoIntNum(int *i, int *j)
{
    if (*i == *j)
        return;
    *i = *i ^ *j;
    *j = *i ^ *j;
    *i = *i ^ *j;
}



int isTwoDoubleNumEqual(double d1, double d2)
{
    if (fabs(d1 - d2) < 1e-5)
        return 1;
    else
        return 0;
}
