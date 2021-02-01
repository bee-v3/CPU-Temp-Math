#include <vector>
#include <utility>

#include "parseTemps.h"
#include "linearInterpolation.h"

LinearInterpolation::LinearInterpolation(std::vector<CoreTempReading> temperatures, int cores){
	for(int i = 0; i < cores; i++){
		std::vector<std::vector<double>> interp_values;	 // Stores all result vectors for a core

		for(unsigned int j = 0; j < temperatures.size() - 1; j++){
			int x1 = temperatures[j].first;
			int x2 = temperatures[j+1].first;
			double y1 = temperatures[j].second[i];
			double y2 = temperatures[j+1].second[i];
			double slope = calc_slope(x1, x2, y1, y2);
			double intercept = calc_intercept(x1, slope, y1);
			
			std::vector<double> results = {(double)x1, (double)x2, intercept, slope};
			
			interp_values.push_back(results);
		}
		interp_collection.push_back(interp_values);	
	}
}

double LinearInterpolation::calc_slope(int x1, int x2, double y1, double y2){
	return (y2 - y1) / (x2 - x1);
}


double LinearInterpolation::calc_intercept(int x, double m, double y){
	return y - (m * x);
}