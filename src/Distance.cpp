#include <iostream>
#include "../include/Distance.h"
#include "../include/Types.h"
#include <vector>
#include <algorithm>    // std::reverse
#include <math.h>

using namespace std;



template <typename T>
T my_max(T x, T y){
	return (x>y?x:y);
}

template <typename T>
T my_min(T x, T y){
	return (x>y?y:x);
}


template <typename T>
long double Euclidean_Distance(const T & v1,const T &v2){
 	long double sum = 0;
 	for(unsigned int i = 0;i<v1.size();i++){
 		sum += pow((v1[i] - v2[i]),2);
 	}
 	return sqrt(sum);
 };


long double DFT(T_Curve & v1,T_Curve &v2){
	unsigned int n = v1.size();
	unsigned int m = v2.size();
	long double C[n][m];
	for(unsigned int i=0;i<n;i++){
		for(unsigned int j=0;j<m;j++){
			if(i == 0 && j == 0){
				C[0][0] = Euclidean_Distance(v1[0],v2[0]);
			}
			else if(i == 0 && j>0){
				C[i][j] = my_max(C[i][j-1],Euclidean_Distance(v1[i],v2[j]));
			}
			else if(j == 0){
				C[i][j] = my_max(C[i-1][j],Euclidean_Distance(v1[i],v2[j]));
			}
			else{
				C[i][j] = my_max(my_min(my_min(C[i-1][j],C[i-1][j-1]),C[i][j-1]),
					Euclidean_Distance(v1[i],v2[j])); 
			}
		}
	}
	return C[n-1][m-1];
}

long double DTW(T_Curve &v1,T_Curve &v2){
	unsigned int n = v1.size();
	unsigned int m = v2.size();
	long double C[n][m];
	for(unsigned int i=0;i<n;i++){
		for(unsigned int j=0;j<m;j++){
			if(i == 0 && j == 0){
				C[0][0] = Euclidean_Distance(v1[0],v2[0]);
			}
			else if(i == 0 && j>0){
				C[i][j] = C[i][j-1] + Euclidean_Distance(v1[i],v2[j]);
			}
			else if(j == 0){
				C[i][j] = C[i-1][j] + Euclidean_Distance(v1[i],v2[j]);
			}
			else{
				C[i][j] = my_min(my_min(C[i-1][j],C[i-1][j-1]),C[i][j-1])+Euclidean_Distance(v1[i],v2[j]); 
			}
		}
	}
	return C[n-1][m-1];
}


int min_index(double x1,double x2,double x3){
	if(x1<x2){
		if(x1 <x3){
			return 0;
		}
		else{
			return 2;
		}
	}
	else{
		if(x2<x3){
			return 1;
		}
		else{
			return 2;
		}
	}
}

void Mean(Point x1,Point x2,Point *p){
	for(unsigned int i=0;i<x1.size();i++){
		double mid;
		mid = (x2[i] + x1[i]) /2.0; 
		p->push_back(mid);
	}
}

int find_min(double x1,double x2,double x3){
	if(x1<x2){
		if(x1<x3){
			return 0;
		}
		else{
			return 2;
		}
	}
	else if(x2<x3){
		return 1;
	}
	return 2;
}

T_Curve * Mean_Frechet_Curve(T_Curve & v1, T_Curve &v2,double *dist){
	unsigned int n = v1.size();
	unsigned int m = v2.size();
	long double C[n][m];
	for(unsigned int i=0;i<n;i++){
		for(unsigned int j=0;j<m;j++){
			if(i == 0 && j == 0){
				C[0][0] = Euclidean_Distance(v1[0],v2[0]);
			}
			else if(i == 0 && j>0){
				C[i][j] = my_max(C[i][j-1],Euclidean_Distance(v1[i],v2[j]));
			}
			else if(j == 0){
				C[i][j] = my_max(C[i-1][j],Euclidean_Distance(v1[i],v2[j]));
			}
			else{
				C[i][j] = my_max(my_min(my_min(C[i-1][j],C[i-1][j-1]),C[i][j-1]),
					Euclidean_Distance(v1[i],v2[j])); 
			}
		}
	}
	*dist = C[n-1][m-1];
	unsigned int i = n-1;
	unsigned int j = m-1;
	T_Curve * traversal = new T_Curve;
	while(i != 0 && j != 0){
		Point p ;
		Mean(v1[i],v2[j],&p);
		traversal->push_back(p);
		int min_index;
		min_index = find_min(C[i-1][j],C[i][j-1],C[i-1][j-1]);
		if(min_index == 0){
			i--;
		}
		else if(min_index == 1){
			j--;
		}
		else{
			i--;
			j--;
		}
	}
	if(i != 0){
		while(i > 0){
			Point p;
			Mean(v1[i],v2[j],&p);
			traversal->push_back(p);
			i--;
		}
	}
	else{
		while(j > 0){
			Point p;
			Mean(v1[i],v2[j],&p);
			traversal->push_back(p);
			j--;
		}
	}
	Point p;
	Mean(v1[0],v2[0],&p);
	traversal->push_back(p);
  	std::reverse(traversal->begin(),traversal->end());
	return traversal;
}


