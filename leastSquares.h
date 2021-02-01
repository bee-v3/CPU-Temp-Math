#ifndef LEASTSQUARES_H_INCLUDED
#define LEASTSQUARES_H_INCLUDED

#include <vector>

#include "parseTemps.h"

class LeastSquares {
private:
	/**
	 * Pair containing core number and a vector holding 2 pieces of lease squares approximation data:
	 * c_0, c_1 - values in y = c_0+c_1x 
	 */
	std::vector<CoreTempReading> c_values;
public:

	/**
 	 * Take a vector of temperature core readings and perform least squares approximation on it.
 	 *
 	 * @param temperatures a vector of (pairs) containing time step and core
 	 * temperature readings
 	 * @param cores number of cpu cores to process readings for
 	 */
	LeastSquares(std::vector<CoreTempReading> temperatures, int cores);
	
	/**
 	 * Performs reduced row echelon reduction on a 2x3 matrix.
 	 *
 	 * @param core_info a 2x3 matrix to perform reduced row echelon reduction on
	 * @return a vector containing two results of reduction
 	 */
	std::vector<double> rre_reduction(double core_info[2][3]);

	/**
	 *  Getter for c_values.
	 * @return private member c_values
	 */
	std::vector<CoreTempReading> getc_values() const {
		return c_values;
	}
};

#endif