# CPU Temp Math
======
Accepts a file containing the timed temperature readings of a 4-core processor, performs least squares approximation and piecewise linear interpolation on the data, and outputs the results for each core to a separate file.
This program comes with sample readings.


## Running
======
Linux:
```./parseTemps [filename]```

Windows:
```parseTemps.exe [filename]```

## Output
======
The processed data will be written to a file named [filename]-core-[#].txt, where # is the core number the file's data corresponds to.
