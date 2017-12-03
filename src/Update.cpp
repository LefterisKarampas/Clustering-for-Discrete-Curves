#include "../include/Update.h"
#include <iostream>
#include "../include/Curve_Info.h"
#include "../include/Cluster.h"
#include "../include/Distance.h"
#include <iostream>
#include <vector>


using namespace std;

extern Curve_Info ** curve_info;
extern double ** Distance_Table;


double PAM_Improved(Clusters *clusters,long double (*distance)(T_Curve &,T_Curve &)){
	double objective_value = 0;
	for(unsigned int i=0;i<clusters->size();i++){
		Neighbors neigh = (*clusters)[i].Cluster_Get_Neighbors();
		unsigned int num_neigh = neigh.size();
		double temp_dist[num_neigh];
		temp_dist[0] = 0;
		int new_center = (*clusters)[i].Cluster_Get_Center();
		double local_objective_value = (*clusters)[i].Cluster_GetValue();
		for(int j=0;j<num_neigh;j++){
			double temp =0;
			for(unsigned int k=j+1;k<num_neigh;k++){
				double dist;
				int index_b;
				int index_l;
				if(neigh[j] > neigh[k]){
					index_b = neigh[j];
					index_l = neigh[k];
				}
				else{
					index_b = neigh[k];
					index_l = neigh[j];
				}
				if(Distance_Table[index_b][index_l] != -1){
					dist = Distance_Table[index_b][index_l];
				}
				else{
					dist = (*distance)(curve_info[index_b]->Get_Curve(),curve_info[index_l]->Get_Curve());
					Distance_Table[index_b][index_l] = dist;
				}
				if(j == 0){
					temp_dist[k] = dist;
				}
				else{
					temp_dist[k] +=dist;
				}
				temp+=dist;
			}
			temp += temp_dist[j];
			if(temp < local_objective_value){
				new_center = neigh[j];
				local_objective_value = temp;
			}
		}
		(*clusters)[i].Cluster_Update(new_center,curve_info[new_center]->Get_Curve_P(),local_objective_value);
		objective_value +=local_objective_value;
	}
	return objective_value;
}



double Mean_Discrete_Frechet(Clusters *clusters,long double (*distance)(T_Curve &,T_Curve &)){
	for(unsigned int i=0;i<clusters->size();i++){
		Neighbors neigh = (*clusters)[i].Cluster_Get_Neighbors();
		unsigned int num_neigh = neigh.size();
		std::vector<T_Curve *> *Mean_Curves = new std::vector<T_Curve *>;
		int flag = 0;
		if(num_neigh == 1){
			return 0.0;
		}
		double dist;
		for(unsigned int j=0;j<num_neigh-1;j+=2){
			Mean_Curves->push_back(Mean_Frechet_Curve(curve_info[neigh[j]]->Get_Curve(),curve_info[neigh[j+1]]->Get_Curve(),&dist));
			int index_b;
			int index_l;
			if(neigh[j] > neigh[j+1]){
				index_b = neigh[j];
				index_l = neigh[j+1];
			}
			else{
				index_b = neigh[j+1];
				index_l = neigh[j];
			}
			if(Distance_Table[index_b][index_l] == -1){
				Distance_Table[index_b][index_l] = dist;
			}
		}
		
		if(num_neigh % 2 == 1){
			flag = 1;
			Mean_Curves->push_back(curve_info[neigh[num_neigh-1]]->Get_Curve_P());
		}
		int loop = 0;
		num_neigh = Mean_Curves->size();
		while(num_neigh != 1){
			std::vector<T_Curve *> *temp = new std::vector<T_Curve *>;
			for(unsigned int j=0;j<num_neigh-1;j+=2){
				temp->push_back(Mean_Frechet_Curve(*((*Mean_Curves)[j]),*((*Mean_Curves)[j+1]),&dist));
			}
			if(num_neigh % 2 == 1){
				temp->push_back((*Mean_Curves)[num_neigh-1]);
			}
			num_neigh = temp->size();
			loop++;
			delete Mean_Curves;
			Mean_Curves = temp;
		}
		(*clusters)[i].Cluster_Update(-1*(i+1),(*Mean_Curves)[0],0.0);
		delete Mean_Curves;
	}
	return 0.0;
}
