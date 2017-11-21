#ifndef _CURVE_INFO_H_
#define _CURVE_INFO_H_


#include "Types.h"

class Curve_Info{
	T_Curve * curve;
	char * id;
	int flag;
public:
	Curve_Info(T_Curve *,char *);
	~Curve_Info();
	const T_Curve & Get_Curve();
	const char * GetId();
};

#endif