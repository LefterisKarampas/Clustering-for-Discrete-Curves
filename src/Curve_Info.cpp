#include "../include/Curve_Info.h"


template <typename T_Curve>
Curve_Info<T_Curve>::Curve_Info(T_Curve *curve,char *id){
	this->curve = curve;
	this->id = id;
	this->flag = 0;
}

template <typename T_Curve>
Curve_Info<T_Curve>::~Curve_Info(){
	delete this->curve;
	free(this->id);
}

template <typename T_Curve>
const T_Curve & Curve_Info<T_Curve>::Get_Curve(){
	return *(this->curve);
}


template <typename T_Curve>
const char * Curve_Info<T_Curve>::GetId(){
	return this->id;
}