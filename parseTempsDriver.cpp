#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>
#include <memory>
#include <iterator>
#include <algorithm>
#include <utility>

#include "leastSquares.h"
#include "linearInterpolation.h"
#include "fileOutput.h"
#include "parseTemps.h"

using namespace std;

//------------------------------------------------------------------------------
int main(int argc, char** argv)
{
    // Input validation
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " input_file_name" << "\n";
        return 1;
    }

    ifstream input_temps(argv[1]);
    if (!input_temps) {
        cout << "ERROR: " << argv[1] << " could not be opened" << "\n";
        return 2;
    }
    // End Input Validation

    vector<CoreTempReading> readings = parse_raw_temps(input_temps);

    int core_count = readings[0].second.size();

    // Solve least squares approximation for cpu readings and return results
    LeastSquares least_squares(readings, core_count);
    std::vector<CoreTempReading> least_sq_results = least_squares.getc_values();
    
    // Solve piecewise linear approximation for cpu readings and return results
    LinearInterpolation linear_interp(readings,core_count);
    std::vector<std::vector<std::vector<double>>> interp_results = linear_interp.get_interp_collection();

    // Output results to file
    fileOutput(least_sq_results, interp_results, core_count, argv[1]);

    return 0;
}
