#include "../include/Curve_Info.h"
#include <stdlib.h>

Curve_Info::Curve_Info(T_Curve *curve,char * id){
	this->curve = curve;
	this->id = id;
	this->flag = 0;
}

Curve_Info::~Curve_Info(){
	delete this->curve;
	free(this->id);
}


T_Curve & Curve_Info::Get_Curve(){
	return *(this->curve);
}

T_Curve * Curve_Info::Get_Curve_P(){
	return this->curve;
}


const char * Curve_Info::GetId(){
	return this->id;
}

const int & Curve_Info::Get_Flag(){
	return this->flag;
};

void Curve_Info::increment(){
	this->flag++;
}


void Curve_Info::clear_flag(){
	this->flag = 0;
}

void Curve_Info::LSH_Increment(int center,double dist){
	if(this->flag % 2 == 0){
		(this->flag)++;
		this->LSH_Center = center;
		this->LSH_dist = dist;
	}
	else if(this->LSH_dist >= dist){
		this->LSH_Center = center;
		this->LSH_dist = dist;
	}
}

int Curve_Info::Get_LSH_Center(){
	if(this->flag % 2 == 0){
		return -1;
	}
	else{
		return this->LSH_Center;
	}
}

double Curve_Info::Get_LSH_dist(){
	return this->LSH_dist;
}