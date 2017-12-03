#ifndef _CLUSTER_H_
#define _CLUSTER_H_

#include "Types.h"
#include <iostream>
#include <vector>


typedef std::vector<int> Neighbors;


class Cluster{
	int center;
	T_Curve *center_curve;
	Neighbors *neighbors;
	double local_objective_value;
public:
	Cluster(int,T_Curve *);
	~Cluster();
	int Cluster_Get_Center();
	T_Curve & Cluster_Get_CenterCuve();
	T_Curve * Cluster_Get_CenterCuve_P();
	void Cluster_Insert(int,double);
	const Neighbors & Cluster_Get_Neighbors();
	void Cluster_Remove_Neigh(int);
	void Cluster_Objective_Function(double);
	double Cluster_GetValue();
	void Cluster_Update(int,T_Curve *,double );
	void Cluster_ClearValue();
	void Cluster_IncreaseValue(double);
	void Cluster_ClearNeigh();
	int Get_num_neigh();
};


#endif