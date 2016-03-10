all:
	g++ -O2 -o FISHR_PARAM Wrapper/wrapper.cpp
clean:
	cp wrapper.cpp wrapper_copy.cpp_;rm -rf FISHR_PARAM ef/ gl/ binaries/ logfile/ *.bsid *.bmid *.bmatch *.log *.gz  *.cpp *.h *.hpp include/ germline8 ErrorFinder25.0 wrapper Readme.txt readme_gl.txt ;cp wrapper_copy.cpp_ wrapper.cpp;rm wrapper_copy.cpp_;