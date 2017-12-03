#ifndef _INIT_H_
#define _INIT_H_

#include "Types.h"
#include "Cluster.h"
#include <iostream>
#include <vector>

int Random_Initialization(std::vector<int> *,int,int);

int K_Means_Plusplus(std::vector<int> *,int,int,long double (*distance)( T_Curve &, T_Curve &));

#endif