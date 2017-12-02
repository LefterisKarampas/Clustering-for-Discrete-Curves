#include "../include/Assignment.h"
#include <iostream>
#include "../include/Curve_Info.h"
#include "../include/Cluster.h"
#include <iostream>
#include <vector>


using namespace std;

extern Curve_Info ** curve_info;
extern double ** Distance_Table;

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
					T_Curve & center_curve = (*clusters)[k].Cluster_Get_CenterCuve();
					double dist;
					int index_b;
					int index_l;
					if(center == -1){
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



double LSH_RangeSearch_Assignment(Clusters *clusters,int n,LSH_Curve ** LSH,int num_HT,long double (*distance)(const T_Curve &,const T_Curve &)){
	int flag = 0;
	int num_clusters = clusters->size();
	int center;
	int t = curve_info[0]->Get_Flag();
	std::vector<int> *Closest_Neighbors = new std::vector<int>[num_clusters];
	std::vector<int> centers;
	std::vector<T_Curve> center_curves;
	double ** Dist;
	if((*clusters)[0]->Cluster_Get_Center() < 0){
		Dist = (double **)malloc(sizeof(double *)*num_clusters);
	}
	for(int i=0;i<num_clusters;i++){
		//centers.push_back((*clusters)[i]->Cluster_Get_Center());
		//center_curves.push_back((*clusters)[i]->Cluster_Get_CenterCuve());
	//}	
		int center = (*clusters)[i]->Cluster_Get_Center();
		if(center == -1){
			Dist = (double *)malloc(sizeof(double)*n);
			for(int j=0;j<n;j++){
				Dist[i][j] = -1;
			}
		}
		for(int j=0;j<num_HT;j++){
			if(center < 0){
				LSH[j]->LSH_RangeSearch(center,(*clusters)[i]->Cluster_Get_CenterCuve(),&(Closest_Neighbors[i]),&(Dist[i]));
			}
			else{
				LSH[j]->LSH_RangeSearch(center,(*clusters)[i]->Cluster_Get_CenterCuve(),&(Closest_Neighbors[i]),Distance_Table);
			}
		}
	}
	double objective_value = 0;
	double r = 10;
	for(int i=0;i<num_clusters;i++){
		int removed = 0;
		(*clusters)[i].Cluster_ClearValue();
		(*clusters)[i].Cluster_ClearNeigh();
		int center = (*clusters)[i]->Cluster_Get_Center();
		for(unsigned int j=0;j<Closest_Neighbors[i].size();j++){
			int c = Closest_Neighbors[i][j];
			if(center == curve_info[c]->Get_LSH_Center()){
				if(center < 0 && Dist[i][c] < r){
					objective_value += Dist[i][c];
					(*clusters)[i].Cluster_Insert(c,0,Dist[i][c]);
					curve_info[c]->increment();
				}
				else if(center > c && Distance_Table[center][c] < r){
					objective_value += Distance_Table[center][c];
					(*clusters)[i].Cluster_Insert(c,0, Distance_Table[center][c]);
					curve_info[c]->increment();
				}
				else if(c >= center && Distance_Table[c][center] < r){
					objective_value += Distance_Table[center][c];
					(*clusters)[i].Cluster_Insert(c,0, Distance_Table[c][center]);
					curve_info[c]->increment();
				}
			}
		}
	}
	for(int j=0;j<n;j++){
		double dist;
		int min;
		for(int i=0;i<num_clusters;i++){
			double temp_dist;
			int center = (*clusters)[i]->Cluster_Get_Center();
			if(curve_info[j]->Get_Flag() == t){
				if(center < 0){
					if(Dist[i][c] == -1){
						Dist[i][c] = (*distance)((*clusters)[i]->Cluster_Get_CenterCuve(),curve_info[j]->Get_Curve());
					}
					temp_dist = Dist[i][c];
				}
				else if(center > j){
					if(Distance_Table[center][j] == -1){
						Distance_Table[center][j] = (*distance)((*clusters)[i]->Cluster_Get_CenterCuve(),curve_info[j]->Get_Curve());
					}
					temp_dist = Distance_Table[center][j];
				}
				else if(center <= j){
					if(Distance_Table[j][center] == -1){
						Distance_Table[j][center] = (*distance)((*clusters)[i]->Cluster_Get_CenterCuve(),curve_info[j]->Get_Curve());
					}
					temp_dist = Distance_Table[j][center];
				}
			}
			else{
				continue;
			}
			if(i == 0){
				min = i;
				dist = temp_dist;
			}
			else if(temp_dist < dist){
				min = i;
				dist = temp_dist;
			}
		}
		(*clusters)[min].Cluster_Insert(j,0,dist);
		objective_value += dist;
		curve_info[c]->increment();
		curve_info[c]->increment();
	}

}