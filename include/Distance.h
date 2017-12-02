#ifndef DISTANCE_H_
#define DISTANCE_H_

#include <vector>
#include "Types.h"

long double DFT(const T_Curve &,const T_Curve &);
long double DTW(const T_Curve &,const T_Curve &);
T_Curve * Mean_Frechet_Curve(T_Curve &, T_Curve &,double *);

#endif