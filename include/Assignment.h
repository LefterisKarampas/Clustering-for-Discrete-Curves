#ifndef _ASSIGNMENT_H_
#define _ASSIGNMENT_H_

#include "Types.h"
#include "../include/LSH_Curve.h"

double Lloyd_Assignment(Clusters *,int,long double (*distance)(T_Curve &,T_Curve &));


double LSH_RangeSearch_Assignment(Clusters *,int ,LSH_Curve ** ,int ,long double (*distance)(T_Curve &,T_Curve &));

#endif