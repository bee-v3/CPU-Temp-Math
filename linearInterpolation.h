#ifndef LINEARINTERPOLATION_H_INCLUDED
#define LINEARINTERPOLATION_H_INCLUDED

#include <vector>
#include <utility>

#include "parseTemps.h"

class LinearInterpolation {
private:	
	/**
	 * A vector containing _n_ vectors, one for each core, with 4 pieces of interpolation data for each temperature reading:
	 * x_0, x_1 - the domain in which y_k is applicable
	 * c_0, c_1 - values in y = c_0+c_1x 
	 */
	std::vector<std::vector<std::vector<double>>> interp_collection;

public:
	
	/**
 	 * Take a vector of temperature core readings and perform piecewise linear interpolation on it.
 	 *
 	 * @param temperatures a vector of (pairs) containing time step and core
 	 * temperature readings
 	 * @param cores number of cpu cores to process readings for
 	 */
	LinearInterpolation(std::vector<CoreTempReading> temperatures, int cores);

	/**
	 * Calculate the slope between two points (rise/run)
	 * @param x1 starting point to calculate change in x
	 * @param x2 ending point to calculate change in x
	 * @param y1 starting point to calculate change in y
	 * @param y2 ending point to calculate change in y
	 * @return the slope between two points as a double
	 */
	double calc_slope(int x1, int x2, double y1, double y2);

	/**
	 * Calculate the y intercept (b in y= mx+b)
	 * @param x point in time of y
	 * @param m slope between points
	 * @param y temperature reading
	 * @return the y intercept as a double
	 */
	double calc_intercept(int x, double m, double y);

	/**
	 *  Getter for interp_collection
	 * @return private member interp_collection
	 */
	std::vector<std::vector<std::vector<double>>> get_interp_collection() const {
		return interp_collection;
	}
};

#endif