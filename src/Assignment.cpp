#include "../include/Assignment.h"
#include <iostream>
#include "../include/Curve_Info.h"
#include "../include/Cluster.h"
#include "../include/LSH_Curve.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <cstdlib>


using namespace std;

extern Curve_Info ** curve_info;
extern double ** Distance_Table;

double Lloyd_Assignment(Clusters *clusters,int n,long double (*distance)(T_Curve &,T_Curve &)){
	if(n <= 0){
		cerr << "We don't have any curve\n" << endl;
	}
	double objective_value = 0;
	//First assignment
	if(curve_info[0]->Get_Flag() == 0){
		for(int i=0;i<n;i++){
			int min;
			double min_dist;
			for(unsigned int j=0;j<clusters->size();j++){
				int center = (*clusters)[j].Cluster_Get_Center();
				T_Curve center_curve = (*clusters)[j].Cluster_Get_CenterCuve();
				double dist;
				int index_b;
				int index_l;
				//Mean Frechet Distance
				if(center < 0){
					dist = (*distance)(curve_info[i]->Get_Curve(),center_curve);
				}
				else{
					if(i > center){
						index_b = i ;
						index_l = center;
					}
					else{
						index_b = center;
						index_l = i;
					}
					if(Distance_Table[index_b][index_l] != -1){
						dist = Distance_Table[index_b][index_l];
					}
					else{
						dist = (*distance)(curve_info[index_b]->Get_Curve(),curve_info[index_l]->Get_Curve());
						Distance_Table[index_b][index_l] = dist;
					}
				}
				if(j==0){
					min = j;
					min_dist = dist;
				}
				else if(min_dist > dist){
					min_dist = dist;
					min = j;
				}
			}
			(*clusters)[min].Cluster_Insert(i,min_dist);
			objective_value += min_dist;
			curve_info[i]->increment();
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
				for(unsigned int k=0;k<clusters->size();k++){
					int center = (*clusters)[k].Cluster_Get_Center();
					T_Curve & center_curve = (*clusters)[k].Cluster_Get_CenterCuve();
					double dist;
					int index_b;
					int index_l;
					if(center < 0){
						dist = (*distance)(curve_info[neigh[j]]->Get_Curve(),center_curve);
					}
					else{
						if(neigh[j] > center){
							index_b = neigh[j] ;
							index_l = center;
						}
						else{
							index_b = center;
							index_l = neigh[j];
						}
						if(Distance_Table[index_b][index_l] != -1){
							dist = Distance_Table[index_b][index_l];
						}
						else{
							dist = (*distance)(curve_info[index_b]->Get_Curve(),curve_info[index_l]->Get_Curve());
							Distance_Table[index_b][index_l] = dist;
						}
					}
					if(k==0){
						min = k;
						min_dist = dist;
					}
					else if(min_dist > dist){
						min_dist = dist;
						min = k;
					}
				}
				if(min != i){
					(*clusters)[min].Cluster_Insert(neigh[j],min_dist);
					(*clusters)[i].Cluster_Remove_Neigh(j-removed);
					removed++;
				}
				else{
					(*clusters)[i].Cluster_IncreaseValue(min_dist);
				}
				objective_value += min_dist;
				curve_info[neigh[j]]->increment();
				//curve_info[i]->increment();
			}
		}
	}
	return objective_value;
}



double LSH_RangeSearch_Assignment(Clusters *clusters,int n,LSH_Curve ** LSH,int num_HT,long double (*distance)(T_Curve &,T_Curve &)){
	int flag = 0;
	int num_clusters = clusters->size();
	int center;
	int t = curve_info[0]->Get_Flag();

	std::vector<int> *Closest_Neighbors = new std::vector<int>[num_clusters];
	std::vector<double> *Dist;
	if((*clusters)[0].Cluster_Get_Center() < 0){
		Dist =  new std::vector<double>[num_clusters];
	}
	//For each cluster, find the LSH Neighbors
	for(int i=0;i<num_clusters;i++){
		(*clusters)[i].Cluster_ClearValue();
		(*clusters)[i].Cluster_ClearNeigh();
		int center = (*clusters)[i].Cluster_Get_Center();
		for(int j=0;j<num_HT;j++){
			if(center < 0){
				LSH[j]->LSH_RangeSearch(center,(*clusters)[i].Cluster_Get_CenterCuve(),&(Closest_Neighbors[i]),&(Dist[i]),distance);
			}
			else{
				LSH[j]->LSH_RangeSearch(center,(*clusters)[i].Cluster_Get_CenterCuve(),&(Closest_Neighbors[i]),distance);
			}
		}
	}
	//Assignment the LSH range neighbors
	double objective_value = 0;
	double r = 0.005;
	int loop = 0;
	int max_assign = 0;
	do{
		r *=2;
		flag = 0;	
		for(int i=0;i<num_clusters;i++){
			if(loop == 0){
				sort( Closest_Neighbors[i].begin(), Closest_Neighbors[i].end() );
				Closest_Neighbors[i].erase( unique( Closest_Neighbors[i].begin(), 
					Closest_Neighbors[i].end() ), Closest_Neighbors[i].end() );
			}
			int center = (*clusters)[i].Cluster_Get_Center();
			int counter = Closest_Neighbors[i].size();
			int j = 0;
			int k = counter -1;
			while(j < counter){
				int neigh = Closest_Neighbors[i][k];
				if(curve_info[neigh]->Get_LSH_Center() == center){
					double dist = curve_info[neigh]->Get_LSH_dist();
					if((r > dist) && ((curve_info[neigh]->Get_Flag() % 2) == 1)){
						curve_info[neigh]->increment();
						flag =1;
						objective_value += dist;
						(*clusters)[i].Cluster_Insert(neigh,dist);
						Closest_Neighbors[i].erase( Closest_Neighbors[i].begin() + k);
						max_assign++;

					}
				}
				else{
					Closest_Neighbors[i].erase( Closest_Neighbors[i].begin() + k);
				}
				k--;
				j++;
			}
		}
		loop++;
	}while(flag && r<10);


	//Assignment all the curves which have not already assigned
	for(int j=0;j<n;j++){
		double dist = -1;
		int min;
		for(int i=0;i<num_clusters;i++){
			double temp_dist;
			int center = (*clusters)[i].Cluster_Get_Center();
			if(curve_info[j]->Get_Flag() < t+2){
				if(center < 0){
					temp_dist = (*distance)((*clusters)[i].Cluster_Get_CenterCuve(),curve_info[j]->Get_Curve());
				}
				else if(center > j){
					if(Distance_Table[center][j] == -1){
						Distance_Table[center][j] = (*distance)((*clusters)[i].Cluster_Get_CenterCuve(),curve_info[j]->Get_Curve());
					}
					temp_dist = Distance_Table[center][j];
				}
				else if(center < j){
					if(Distance_Table[j][center] == -1){
						Distance_Table[j][center] = (*distance)((*clusters)[i].Cluster_Get_CenterCuve(),curve_info[j]->Get_Curve());
					}
					temp_dist = Distance_Table[j][center];
				}
			}
			else{
				continue;
			}
			if(dist == -1){
				min = i;
				dist = temp_dist;
			}
			else if(temp_dist < dist){
				min = i;
				dist = temp_dist;
			}
		}
		if(dist != -1){
			max_assign++;
			(*clusters)[min].Cluster_Insert(j,dist);
			objective_value += dist;
			if(curve_info[j]->Get_Flag() % 2 == 0){
				curve_info[j]->increment();
			}
			curve_info[j]->increment();
		}
	}
	delete[] Closest_Neighbors;
	if((*clusters)[0].Cluster_Get_Center() < 0){
		delete[] Dist;
	}
	return objective_value;
}