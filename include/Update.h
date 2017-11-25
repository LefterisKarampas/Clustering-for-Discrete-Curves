#ifndef _UPDATE_H_
#define _UPDATE_H_

#include "Types.h"
#include "Cluster.h"

double PAM_Improved(Clusters *clusters,long double (*distance)(const T_Curve &,const T_Curve &));

double Mean_Discrete_Frechet(Clusters *clusters,long double (*distance)(const T_Curve &,const T_Curve &));


#endif