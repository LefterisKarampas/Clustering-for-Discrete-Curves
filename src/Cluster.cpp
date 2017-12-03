#include "../include/Types.h"
#include "../include/Cluster.h"
#include <iostream>
#include <vector>

using namespace std;


Cluster::Cluster(int center, T_Curve * center_curve){
	this->center = center;
	this->center_curve = center_curve;
	this->neighbors = new Neighbors();
	this->local_objective_value = 0;
}

Cluster::~Cluster(){
	if(this->center < 0){
		;//delete this->center_curve;
	}
	//delete this->neighbors;
}

int Cluster::Cluster_Get_Center(){
	return this->center;
}

T_Curve & Cluster::Cluster_Get_CenterCuve(){
	return (*this->center_curve);
}

T_Curve * Cluster::Cluster_Get_CenterCuve_P(){
	return this->center_curve;
}

void Cluster::Cluster_Insert(int neigh,double x){
	this->neighbors->push_back(neigh);
	this->local_objective_value +=x;
}

const Neighbors  & Cluster::Cluster_Get_Neighbors(){
	return *(this->neighbors);
}


void Cluster::Cluster_Remove_Neigh(int index_neigh){
	this->neighbors->erase(this->neighbors->begin() + index_neigh);
}

double Cluster::Cluster_GetValue(){
	return this->local_objective_value;
}

void Cluster::Cluster_Update(int new_center,T_Curve * center_curve,double objective_value){
	if(this->center < 0){
		;//delete this->center_curve;
	}
	this->center = new_center;
	this->center_curve = center_curve;
	this->local_objective_value = objective_value;
}


void Cluster::Cluster_ClearValue(){
	this->local_objective_value = 0;
}

void Cluster::Cluster_IncreaseValue(double x){
	this->local_objective_value += x;
}

void Cluster::Cluster_ClearNeigh(){
	this->neighbors->clear();
}

int Cluster::Get_num_neigh(){
	return this->neighbors->size();
}