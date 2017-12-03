#ifndef _CURVE_INFO_H_
#define _CURVE_INFO_H_


#include "Types.h"

class Curve_Info{
	T_Curve * curve;
	char * id;
	int flag;
	int LSH_Center;
	double LSH_dist;
public:
	Curve_Info(T_Curve *,char *);
	~Curve_Info();
	T_Curve & Get_Curve();
	T_Curve * Get_Curve_P();
	const char * GetId();
	const int & Get_Flag();
	void increment();
	void clear_flag();
	void LSH_Increment(int,double);
	int Get_LSH_Center();
	double Get_LSH_dist();
};

#endif