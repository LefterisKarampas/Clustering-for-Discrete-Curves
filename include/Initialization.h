#ifndef _INIT_H_
#define _INIT_H_

#include "Types.h"
#include "Cluster.h"
#include <iostream>
#include <vector>

int Random_Initialization(Clusters *,int,int);

int K_Means_Plusplus(Clusters *,int,int,long double (*distance)(const T_Curve &,const T_Curve &));

#endif