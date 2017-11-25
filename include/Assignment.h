#ifndef _ASSIGNMENT_H_
#define _ASSIGNMENT_H_

#include "Types.h"

double Lloyd_Assignment(Clusters *,int,long double (*distance)(const T_Curve &,const T_Curve &));

#endif