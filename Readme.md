Usage:





CREATE BINARIES:
The program needs to be compiled to create the binaries.

Step-1:	Navigate into the root folder, there will be a parameters.txt file.

Step-2: Use "-MAKEBINARIES: YES" as the value in the USER PREFERENCE FISHR. This means user is interested in compiling the program and creating the binaries. Now where do we store the binary?

Step-3:	Use "-binary-output-directory: /some/location/ " This is the dicrectory where the binary program of germline and fishr will be saved at.

Step-4: Done. Binaries have been created.



RUN:
After creating binaries, there will be a Executable binary named FISHR_PARAM created in the root directory. Make sure to use "-MAKEBINARIES: NO" as the value in the USER PREFERENCE FISHR in parameters.txt file. "NO" suggests the user has done compiling and created the binaries and now is interested in running the program..Then execute the following code.

FISHR_PARAM /path/to/parameters.txt




Add FISHR_PARAM to the directory path to seamlessly access the program the prompt.




-pedfile: /path/to/file.ped
-mapfile: /path/to/file.map
-germline output directory: /germline/output/savedhere/
-fishr output directory: /fishr/output/savedhere/
-log.file:	/logfiles/saved/here/
-germline.outfile.prefix: output_name_of_germline
-fishr.outfile.prefix:output_name_of_fishr


 
