#ifdef _CLUSTER_H_
#define _CLUSTER_H_

#include "Types.h"
#include <iostream>
#include <vector>

class Cluster{
	int center;
	std::vector<int> neighbors;
public:
	Cluster(int);
	~Cluster();
}


#endif