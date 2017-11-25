#include "../include/Update.h"
#include <iostream>
#include "../include/Curve_Info.h"
#include "../include/Cluster.h"
#include <iostream>
#include <vector>


using namespace std;

extern Curve_Info ** curve_info;



double PAM_Improved(Clusters *clusters,long double (*distance)(const T_Curve &,const T_Curve &)){
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
				dist = distance(curve_info[neigh[j]]->Get_Curve(),curve_info[neigh[k]]->Get_Curve());
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
		(*clusters)[i].Cluster_Update(new_center,local_objective_value);
		objective_value +=local_objective_value;
	}
	return objective_value;
}



double Mean_Discrete_Frechet(Clusters *clusters,long double (*distance)(const T_Curve &,const T_Curve &));
