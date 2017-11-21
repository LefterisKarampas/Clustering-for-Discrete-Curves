#ifndef CURVE_H_
#define CURVE_H_

#include <vector>
#include <iostream>

typedef std::vector<double> Point;
typedef std::vector< Point > T_Curve;

class Curve{
	T_Curve * curve;
	Point *grid_curve;
	char * id;
public:
	Curve(T_Curve *, Point *,char *);
	~Curve();
	const Point & Get_GridCurve();
	bool Compare_GridCurve(Curve *);
	char * GetId();
	T_Curve & GetCurve();
	void Clear_up();
};




#endif