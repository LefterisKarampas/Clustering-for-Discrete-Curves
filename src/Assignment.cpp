#include "../include/Assignment.h"
#include <iostream>
#include "../include/Curve_Info.h"
#include "../include/Cluster.h"
#include <iostream>
#include <vector>


using namespace std;

extern Curve_Info ** curve_info;

double Lloyd_Assignment(Clusters *clusters,int n,long double (*distance)(const T_Curve &,const T_Curve &)){
	if(n <= 0){
		cerr << "We don't have any curve\n" << endl;
	}
	double objective_value = 0;
	//First assignment
	if(curve_info[0]->Get_Flag() == 0){
		for(int i=0;i<n;i++){
			int min;
			double min_dist;
			int second_min;
			double second_min_dist;
			for(unsigned int j=0;j<clusters->size();j++){
				int center = (*clusters)[j].Cluster_Get_Center();
				double dist = (*distance)(curve_info[i]->Get_Curve(),curve_info[center]->Get_Curve());
				if(j==0){
					min = j;
					min_dist = dist;
				}
				else if(min_dist > dist){
					second_min_dist = min_dist;
					second_min = min;
					min_dist = dist;
					min = j;
				}
				else if(j == 1 || second_min > dist){
					second_min_dist = dist;
					second_min = j;
				}
			}
			(*clusters)[min].Cluster_Insert(i,second_min,min_dist);
			objective_value += min_dist;
			curve_info[i]->increment();
		}
	}
	else{
		int flag = curve_info[0]->Get_Flag();
		for(unsigned int i=0;i<clusters->size();i++){
			int removed = 0;
			(*clusters)[i].Cluster_ClearValue();
			std::vector<int>  neigh = (*clusters)[i].Cluster_Get_Neighbors();
			for(unsigned int j=0;j<neigh.size();j++){
				if(curve_info[neigh[j]]->Get_Flag() > flag){
					continue;
				}
				int min;
				double min_dist;
				int second_min;
				double second_min_dist;
				for(unsigned int k=0;k<clusters->size();k++){
					int center = (*clusters)[k].Cluster_Get_Center();
					double dist = (*distance)(curve_info[neigh[j]]->Get_Curve(),curve_info[center]->Get_Curve());
					if(k==0){
						min = k;
						min_dist = dist;
					}
					else if(min_dist > dist){
						second_min_dist = min_dist;
						second_min = min;
						min_dist = dist;
						min = k;
					}
					else if(k == 1 || second_min > dist){
						second_min_dist = dist;
						second_min = k;
					}
				}
				if(min != i){
					(*clusters)[min].Cluster_Insert(neigh[j],second_min,min_dist);
					(*clusters)[i].Cluster_Remove_Neigh(j-removed);
					removed++;
				}
				else{
					(*clusters)[i].Cluster_IncreaseValue(min_dist);
				}
				objective_value += min_dist;
				curve_info[neigh[j]]->increment();
			}
		}
	}
	return objective_value;
}