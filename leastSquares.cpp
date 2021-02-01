#include <vector>

#include "leastSquares.h"

LeastSquares::LeastSquares(std::vector<CoreTempReading> temperatures, int cores){
        double x0_x0 = temperatures.size();     //SUM number of readings

    for(int i = 0; i < cores; i++){
        double temp_matrix[2][3];   //A 2x3 matrix to store values from core used to find c0 and c1
        double x1_x0 = 0;   //SUM x (seconds)
        double x1_x1 = 0;   //SUM x^2 from 0 to n (seconds)
        double x0_xf = 0;   //SUM f(x) (temperature)
        double x1_xf = 0;   //SUM x*f(x) from 0 to n (seconds)(temperature)

        for(unsigned int j = 0; j < temperatures.size(); j++){      
            x1_x0 += temperatures[j].first;
            x1_x1 += temperatures[j].first * temperatures[j].first;
            x0_xf += temperatures[j].second[i];
            x1_xf += temperatures[j].first * temperatures[j].second[i];
        }

        // Assign values to 2x3 matrix
        temp_matrix[0][0] = x0_x0;
        temp_matrix[0][1] = x1_x0;
        temp_matrix[0][2] = x0_xf;
        temp_matrix[1][0] = x1_x0;
        temp_matrix[1][1] = x1_x1;
        temp_matrix[1][2] = x1_xf;

        std::vector<double> c_result = rre_reduction(temp_matrix);
        c_result.push_back(temperatures[x0_x0-1].first);
        c_values.emplace_back(i, c_result);
    }

}

std::vector<double> LeastSquares::rre_reduction(double core_info[2][3]){
    const int num_of_rows = 2;
    
    for(int i=0; i < num_of_rows; i++){
        
        for(int j = 0; j < num_of_rows; j++){
            double divisor = core_info[i][i];   
            double factor = core_info[j][i] / core_info[i][i];

            for(int k = 0; k < num_of_rows + 1; k++){
                // If place in matrix is pivot, divide to make 1, eliminate otherwise
                core_info[j][k] = (j == i) ? core_info[j][k] / divisor : core_info[j][k] - (core_info[i][k] * factor);
            }
        }

    }
    // Place results in vector and return
    std::vector<double> c = {core_info[0][2], core_info[1][2]};
    return c;
}
