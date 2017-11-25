#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "../include/Initialization.h"
#include "../include/Curve_Info.h"

using namespace std;

extern Curve_Info** curve_info;

int Random_Initialization(std::vector<Cluster> *Clusters,int num_clusters,int num_curves){
	std::vector<int> centers;
	int new_center;
	int flag = 0;
	for(int i=0;i<num_clusters;i++){
		flag = 0;
		while(!flag){
			new_center = rand() % num_curves;
			for(unsigned int j=0;j<centers.size();j++){
				if(centers[j] == new_center){
					break;
				}
			}
			Cluster temp(new_center);
			Clusters->push_back(temp);
			centers.push_back(new_center);
			flag = 1;
		}

	}
	return 0;
}

int K_Means_Plusplus(std::vector<Cluster> *Clusters,int num_clusters,int num_curves,long double (*distance)(const T_Curve &,const T_Curve &)){
	std::vector<int> centers;
	std::vector<double> min_distance;
	int new_center;
	for(int i=0;i<num_clusters;i++){
		std::vector<float> P;
		if(i == 0){
			new_center = rand() % num_curves;
		}
		Cluster temp(new_center);
		Clusters->push_back(temp);
		centers.push_back(new_center);
		double max_dist; 
		for(int j=0;j<num_curves;j++){
			int flag = 0;
			for(unsigned int k=0;k<centers.size();k++){
				if(j == centers[k]){
					flag = 1;
					break;
				}
			}
			if(flag == 1){
				min_distance.push_back(0.0);
				continue;
			}
			double dist = (*distance)(curve_info[j]->Get_Curve(),curve_info[new_center]->Get_Curve());
			if (j == 0){
				max_dist = dist;
			}
			else if(max_dist < dist){
				max_dist = dist;
			}
			if(i == 0){
				min_distance.push_back(dist);
			}
			else if(min_distance[j] > dist){
				min_distance[j] = dist;
			}
		}
		for(int j=0;j<num_curves;j++){
			if(j == 0){
				P.push_back(min_distance[j]/max_dist * min_distance[j]/max_dist);
			}
			else{
				P.push_back(P[j-1]+min_distance[j]/max_dist * min_distance[j]/max_dist);
			}
		}
		if(i < num_clusters-1){
			int flag = 0;
			float x;
			int upper = P.size();
			int lower = 0;
			int mid = (upper+lower)/2;
			x = rand()/((float)RAND_MAX) * P[num_curves-1];
			while(1){
				if(P[mid] > x){
					if(P[mid] == x || P[mid-1] < x){
						while(mid > 0 && P[mid] == P[mid-1]){
							mid--;
						}
						new_center = mid;
						break;
					}
					else{
						upper = mid;
						mid = (upper+lower)/2;
					}
				}
				else if(P[mid] == x){
					while(mid > 0 && P[mid] == P[mid-1]){
						mid--;
					}
					new_center = mid;
					break;
				}
				else{
					lower = mid;
					mid = (upper+lower)/2;
				}
			}
		}
	}

	return 0;
}