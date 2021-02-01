#include <vector>
#include <fstream>
#include <iomanip>
#include <string>

#include "parseTemps.h"

void fileOutput(std::vector<CoreTempReading> temperatures, std::vector<std::vector<std::vector<double>>> interp_results, 
																					int core_count, std::string base_name){
    for(int i = 0; i < core_count; i++){
        std::ofstream output;        
        std::string filename = base_name.substr(0,base_name.find_last_of(".")) + "-core-" + std::to_string(i) + ".txt";
        output.open(filename, std::ios::trunc);

        if(output.is_open()){
            // Write least squares approximation data to file
            output << std::setfill('-') << std::setw(83) <<  " " << std::endl;
            output << std::setfill(' ') << base_name << std::endl;
            output << std::setfill('-') << std::setw(83) << " " << std::endl;
            output << std::setfill(' ') << std::right << std::setw(8) << '0' << std::setw(7) << "<= x <" <<
            std::setw(8)<< temperatures[i].second[2] << std::setw(0) << "; y " <<
            std::setw(8)<< "=" << std::setw(12) << temperatures[i].second[0] <<
            std::setw(0) << " + " << std::setw(8) << temperatures[i].second[1] << "x; least-squares" << std::endl;
            output << std::setfill('-') << std::setw(83) <<  " " << std::setfill(' ') << std::endl;

            // Write piecewise linear interpolation data to file
            for(unsigned int j = 0; j < interp_results[i].size(); j++){
                output << std::right << std::setw(8) << (int)interp_results[i][j][0] << std::setw(7) << "<= x <" <<
                std::setw(8)<< (int)interp_results[i][j][1] << std::setw(0) << "; y_" << std::left;
                if(j < 10){
                    output << "0" << std::setw(3);
                } else{
                    output << std::setw(4);
                }
                output << std::to_string(j) << std::right << std::setfill(' ') << std::setw(4)<< "=" << 
                std::setw(8) << std::fixed << std::setprecision(4) << (int)interp_results[i][j][2] << std::setw(0) << ".0000" << " + " << 
                std::setw(8) <<  interp_results[i][j][3] << "x; linear interpolation" << std::endl;
            }
        }

        output.close();
    }
}