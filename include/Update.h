#ifndef _UPDATE_H_
#define _UPDATE_H_

#include "Types.h"
#include "Cluster.h"

double PAM_Improved(Clusters *clusters,long double (*distance)( T_Curve &, T_Curve &));

double Mean_Discrete_Frechet(Clusters *clusters,long double (*distance)( T_Curve &, T_Curve &));


#endif