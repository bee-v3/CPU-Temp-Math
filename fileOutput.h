#ifndef FILEOUTPUT_H_INCLUDED
#define FILEOUTPUT_H_INCLUDED

#include <vector>
#include <string>

#include "parseTemps.h"

/**
 * Take the piecewise  linear interpolation and least squares approximation results
 * and output to a nicely formatted file.
 *
 * @param temperatures a vector of (pairs) containing time step and core
 * temperature readings
 * @param interp_results a vector containing _n_ vectors, one for each core, of a vector of size 4
 * @param core_count number of cpu cores to process readings for
 * @param base_name name of the file passed to the program as a parameter
 */
void fileOutput(std::vector<CoreTempReading> temperatures, std::vector<std::vector<std::vector<double>>> interp_results, 
																					int core_count, std::string base_name);

#endif