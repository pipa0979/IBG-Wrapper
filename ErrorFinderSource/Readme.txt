Moving window average, Extend snip window
This program uses the flag -extendSNP <value> to expand the window size for snips to calculate
the moving window average.

To Compile:
--------
g++ -g -O0 ErrorFinderMain.cpp -o ErrorFinder25.0

Usuage (To run):
--------
./ErrorFinder25.0 -ped-file Beagle.Phased.Group2.1k.ped -bmatch GL.HE.Omincm3.bit20.err0.bmatch -bsid GL.HE.Omincm3.bit20.err0.bsid -bmid GL.HE.Omincm3.bit20.err0.bmid -reduced 64 3 -window 50 -empirical-ma-threshold 0.04 -gap 100 -emp-pie-threshold 0.015 -output.type finalOutput -count.gap.errors TRUE -log.file 0extendSnp100Gap -extendSNP 40 |gzip > output.gz


Instructions:
-----------
The flag -extendSNP must be used for the program to work. If the extend window feature is not needed,
then doing a -extendSNP 0 is equivalent.

 
Code Changes:
-----------
1. Additional flag added (-extendSNP).
2. Parameter handled: 
   Target files: All files and function passing -extendSNP as paramenter
3. performtrim() in consolidator.cpp files
4. important files to look at:
   parse_bmatch.cpp
  
