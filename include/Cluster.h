#ifndef _CLUSTER_H_
#define _CLUSTER_H_

#include "Types.h"
#include <iostream>
#include <vector>


typedef std::vector<int> Neighbors;
typedef std::vector<int> Second_Best;

class Cluster{
	int center;
	T_Curve *center_curve;
	Neighbors *neighbors;
	Second_Best *second_best;
	double local_objective_value;
public:
	Cluster(int,T_Curve *);
	~Cluster();
	int Cluster_Get_Center();
	T_Curve & Cluster_Get_CenterCuve();
	void Cluster_Insert(int,int,double);
	const Neighbors & Cluster_Get_Neighbors();
	const Second_Best & Cluster_Get_SecondBest();
	void Cluster_Remove_Neigh(int);
	void Cluster_Objective_Function(double);
	double Cluster_GetValue();
	void Cluster_Update(int,T_Curve *,double );
	void Cluster_ClearValue();
	void Cluster_IncreaseValue(double);
	void Cluster_ClearNeigh();
};


#endif