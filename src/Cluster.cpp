#include "../include/Types.h"
#include "../include/Cluster.h"
#include <iostream>
#include <vector>

using namespace std;


Cluster::Cluster(int center, T_Curve * center_curve){
	this->center = center;
	this->center_curve = center_curve;
	this->neighbors = new Neighbors();
	this->second_best = new Second_Best();
	this->local_objective_value = 0;
}

Cluster::~Cluster(){
	if(this->center < 0){
		delete this->center_curve;
	}
}

int Cluster::Cluster_Get_Center(){
	return this->center;
}

T_Curve & Cluster::Cluster_Get_CenterCuve(){
	return (*this->center_curve);
}

void Cluster::Cluster_Insert(int neigh,int second_best_center,double x){
	(this->neighbors)->push_back(neigh);
	(this->second_best)->push_back(second_best_center);
	this->local_objective_value +=x;
}

const Neighbors  & Cluster::Cluster_Get_Neighbors(){
	return *(this->neighbors);
}

const Second_Best & Cluster::Cluster_Get_SecondBest(){
	return *(this->second_best);
}

void Cluster::Cluster_Remove_Neigh(int index_neigh){
	this->neighbors->erase(this->neighbors->begin() + index_neigh);
	this->second_best->erase(this->second_best->begin() + index_neigh);
}

double Cluster::Cluster_GetValue(){
	return this->local_objective_value;
}

void Cluster::Cluster_Update(int new_center,T_Curve * center_curve,double objective_value){
	if(this->center < 0){
		delete this->center_curve;
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

void Cluster_ClearNeigh(){
	this->neighbors->clear();
	this->second_best->clear();
}