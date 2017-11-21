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


const T_Curve & Curve_Info::Get_Curve(){
	return *(this->curve);
}



const char * Curve_Info::GetId(){
	return this->id;
}