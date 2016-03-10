#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string.h> 
#include <boost/algorithm/string.hpp>

using namespace boost::algorithm;
using namespace std; 


bool openFile(string);
string SplitFilenamefirst(const string&);
string SplitFilenamesecond(const string&);

string binaries="binaries";
string germlineSourceFolder="GermlineSource/";
string germlineSource = "germline_source_IBG.tar"; 
string germlineSourceExtractTar="tar -xf ";//no vervose
string germlineCompilation="g++ -O2 -o ./binaries/germline8_param -I ./GermlineSource/include ./GermlineSource/GERMLINE_0001.cpp "
"./GermlineSource/GERMLINE.cpp ./GermlineSource/Share.cpp ./GermlineSource/Chromosome.cpp ./GermlineSource/ChromosomePair.cpp ./GermlineSource/HMIndividualsExtractor.cpp "
"./GermlineSource/MarkerSet.cpp ./GermlineSource/Individual.cpp ./GermlineSource/Individuals.cpp ./GermlineSource/InputManager.cpp ./GermlineSource/MatchFactory.cpp "
"./GermlineSource/MatchesBuilder.cpp ./GermlineSource/NucleotideMap.cpp ./GermlineSource/PEDIndividualsExtractor.cpp ./GermlineSource/Match.cpp "
"./GermlineSource/PolymorphicIndividualsExtractor.cpp ./GermlineSource/SNP.cpp ./GermlineSource/SNPPositionMap.cpp ./GermlineSource/SNPs.cpp" ;
string germlineOutputDirn="-germline output directory";
string germlineOutputDir="./";//	./
string errorFinderSourceFolder="ErrorFinderSource/";
string errorFinderSource = "ErrorFinder25.0_source.tar";
string errorFinderSourceExtractTar="tar -xf ";
string errorFinderCompilation="g++ -O2 -o ./binaries/Fishr25.0_param ./ErrorFinderSource/ErrorFinderMain.cpp";
string errorFinderOutputDirn="-fishr output directory";
string errorFinderOutputDir="./";


string parameterFileName = "parameters.txt";

string defpedmapfileFolder="Default_PED_MAP/";
string pedmap="ped_map.tar";
string pedmapExtractTar="tar -xf ";
string defaultMapFile="./Default_PED_MAP/Beagle.Phased.Group2.1k.map";
string defaultPedFile="./Default_PED_MAP/Beagle.Phased.Group2.1k.ped";

string pedfile_loc="";
string pedfile_loc_n="-pedfile";


string mapfile_loc="";
string mapfile_loc_n="-mapfile";



string germline8="./germline8_param";
string delim=":";
string deflt="default";
string hash="#";

string logfilen="-log.file";
string logfileOutputDirectory="./";
string logfilename="default.log";
string logfile="logs";

string heading0="(USER PREFERENCE FISHR)";
string heading1="(FILE LOCATIONS)";
string heading2="(GERMLINE)";
string heading2_2="(OPTIONAL GERMLINE PARAMETER)";
string heading3="(ERRORFINDER)";
string heading3_3="(OPTIONAL ERRORFINDER PARAMETER)";
string heading4="(OPTIONAL ERRORFINDER PARAMETER)";
string pedfile= "-pedfile";
string mapfile= "-mapfile";


string outfile="";
string outfile_n="-germline.outfile.prefix";
string fisheroutfile_n="-fishr.outfile.prefix";

string bmatch="\"-outfile\".bmatch";
string bmatch_n="-bmatch";

string bsid="\"-outfile\".bsid";
string bsid_n="-bsid";

string bmid="\"-outfile\".bmid";
string bmid_n="-bmid";

string ErrorFinder25_0="./Fishr25.0_param";
string pedfile_n="-ped-file";


string outputname="default.gz";
bool f_run_compile=false;

string binary_output_directory_n="-binary-output-directory";
string binary_output_directory="";
string makebinaries_n="-MAKEBINARIES";
string makebinaries="";/*YES/NO*/

//string logfile="logs";//logs
//string logfile_n=
//string outputnamen="-outputname";
//string outputDirectory="./";



int main (int argc,char *argv[])
{
/*CHECK USER PREFERENCE*/
/*READ PARAMETERS.TXT FOR PEDMEDFILE*/
	if (argc<2)
	{
		cout<<"parameters.txt file path not given... program is exiting"<<endl;
		exit(0);
	}
	else
	{
		parameterFileName=argv[argc-1];
	}
cout<<"parameterFileName = "<<parameterFileName<<endl;


ifstream file(parameterFileName.c_str());

if (!file.is_open())
{
	cout<<"parameters.txt file couldn't open"<<endl;
	exit(0);
}
//cout<<"***Reading Pedfile and Mapfile"<<parameterFileName<<"***\n"<<endl;
string beg,end,each,cmnt;




while(getline(file,each))
	{

		if(!strcmp(each.c_str(),heading0.c_str()) || (each.length()==0) )
		{			
			continue;
		}

		if(!strcmp(each.c_str(), heading1.c_str()))
		{
			
			break;
		}
		if(each[0]=='#')
		{
			continue;
		}
		beg=each.substr(0,each.find(delim));
		trim(beg);
		end=each.substr(each.find(':')+1,each.find('#') - each.find(':')-1);
		trim(end);
		cmnt=each.substr(each.find(hash)+1,each.length()- each.find(hash)-1);
		trim(cmnt);
		if(!strcmp(beg.c_str(),makebinaries_n.c_str()))
		{			
			if(end.length()!=0)
				{
					if(!strcmp(end.c_str(),"YES"))
					{
						cout<<"Process creating binaries started..."<<endl;
						makebinaries="YES";

					}
					else if (!strcmp(end.c_str(),"NO"))
					{
						cout<<"Process creating binaries bypassed... Running Program sequence"<<endl;
						makebinaries="NO";
					}

				}
			else
				{
					cout<<" Program is exiting. No value entered."<<endl;
					exit(0);
					
				}
		}

	}


system(("mkdir -p "+binaries).c_str()); // binaries folder made
cout<<"---Wrapper program called---\n"<<endl;
/*CHECK TO SEE IF 1. GERMLINE SOURCE 2.ERRORFINDER SPURCE 3. PARAMETER.TXT FILE EXIST */


if (!strcmp(makebinaries.c_str(),"YES"))
	{

		cout<<"---Checking if Germline source exists---"<<endl;
		if(openFile(germlineSourceFolder+germlineSource))
			{
				cout<<germlineSource<<" file opened successfully\n"<<endl;		
			}

		else
			{
				cout<<germlineSource<<" couldn't open.\n Please check if the file "<<germlineSource;
				cout<<" exists....\n Exiting program"<<endl;
				exit(0);
			}
	}


if (!strcmp(makebinaries.c_str(),"YES"))
	{

		cout<<"---Checking if ErrorFinder source exists---"<<endl;
		if(openFile(errorFinderSourceFolder+errorFinderSource))
			{
				cout<<errorFinderSource<<" file opened successfully\n"<<endl;
			}

		else
			{
				cout<<errorFinderSource<<" couldn't open.\n Please check if the file "<<errorFinderSource;
				cout<<" exists....\n Exiting program"<<endl;
				exit(0);

			}
	}


cout<<"---Checking if parameters.txt file exists---"<<endl;

if (openFile(parameterFileName))
	{
		cout<<parameterFileName<<" file opened successfully\n"<<endl;
	}
else
	{
		cout<<parameterFileName<<" couldn't open.\n Please check if the file "<<parameterFileName;
		cout<<" exists....\n Exiting program"<<endl;
		exit(0); 
	}

/*
if (!strcmp(makebinaries.c_str(),"NO"))
	{
	
		cout<<"---Checking if default ped and map file exists---"<<endl;
		if (openFile(defpedmapfileFolder+pedmap))
			{
				cout<<pedmap<<" file opened successfully\n"<<endl;
			}
		else
			{
				cout<<pedmap<<" couldn't open default ped and map file.\n Must pass ped and map file explicitly "<<pedmap;
				cout<<" exists....\n Exiting program"<<endl;
				exit(0); 
			}
	}
*/
/***************************************************************************************/





if (!strcmp(makebinaries.c_str(),"YES"))
	{
		cout<<"***Compiling Germline source***\n"<<endl;
		system((germlineSourceExtractTar+" "+germlineSourceFolder+germlineSource+" -C "+"./"+germlineSourceFolder).c_str());
		system(germlineCompilation.c_str());
	}
else
{

}

if (!strcmp(makebinaries.c_str(),"YES"))
	{
		/* EXTRACT AND COMPILE ERRORFINDER*/
		cout<<"***Compiling ErrorFinder source***\n"<<endl;

		system((errorFinderSourceExtractTar+" "+errorFinderSourceFolder+errorFinderSource+" -C "+"./"+errorFinderSourceFolder).c_str());
		//cout<<(errorFinderSourceExtractTar+" "+errorFinderSourceFolder+errorFinderSource+" -C "+"./"+errorFinderSourceFolder);
		system(errorFinderCompilation.c_str());
		//cout<<"ErrorFinder source compilation completed successfully\n"<<endl;
	}
else
	{

	}


/*
if (!strcmp(makebinaries.c_str(),"NO"))
	{
		//Extract default ped map file
		cout<<"***Checking .ped and .map file ***\n"<<endl;
		system((pedmapExtractTar+ " "+defpedmapfileFolder+pedmap+" "+" -C "+ "./"+defpedmapfileFolder).c_str());
	}



*/
//cout<<(pedmapExtractTar+ " "+pedmap+" "+" -C "+ "./"+defpedmapfileFolder)<<endl;
//cout<<"Extracting default .map and .ped file completed successfully\n"<<endl;
/***************************************************************************************/
while(getline(file,each))
	{
		if(!strcmp(each.c_str(),heading1.c_str()) || (each.length()==0) )
		{			
			continue;
		}

		if(!strcmp(each.c_str(), heading2.c_str()))
		{
			
			break;
		}
		if(each[0]=='#')
		{
			continue;
		}
		beg=each.substr(0,each.find(delim));
		trim(beg);
		end=each.substr(each.find(':')+1,each.find('#') - each.find(':')-1);
		trim(end);
		cmnt=each.substr(each.find(hash)+1,each.length()- each.find(hash)-1);
		trim(cmnt);

		if (!strcmp(makebinaries.c_str(),"YES"))
			{
					if(!strcmp(beg.c_str(),binary_output_directory_n.c_str()))
						{							
							if(end.length()!=0)
								{
									
									system(("sudo mkdir -p "+end).c_str()); /*-p very very impoertant*/
									
									/* Move GL and Fishr binaries into binary-output-directory*/
									system(("sudo mv ./"+binaries+"/./Fishr25.0_param "+ "./"+binaries+"/./germline8_param " +end).c_str());
								}
							else
								{
									cout<<"Location of binaries not specified... Program is exiting."<<endl;
									exit(0);								
								}								
						}
			}


		if (!strcmp(makebinaries.c_str(),"NO"))
			{
					if(!strcmp(beg.c_str(),binary_output_directory_n.c_str()))
						{
							
							if(end.length()!=0)
								{
									binary_output_directory=end;								
									
								}
							else
								{
									cout<<"Location of binaries not specified... Program is exiting."<<endl;
									exit(0);								
								}								
						}
			}






		/*If make binaries is YES, don't run fishr and gl i.e. just exit out*/
	if (!strcmp(makebinaries.c_str(),"YES"))
		{
			cout<<"Process creating binaries finished."<<endl;
			exit(0);
		}






		if(!strncmp(beg.c_str(),pedfile.c_str(),beg.length()))// && 
			{
				if( end.length()==0) 
				{
					cout<<"No .ped file provided... Program is exiting"<<endl;
					exit(0);
				}
				else
				{			
					cout<<"Checking .ped file"<<endl;		
					defaultPedFile=end;
					cout<<"defaultPedFile = "<<defaultPedFile<<endl;
					if (openFile(defaultPedFile))
						{

						}
					else
						{
							cout<<"Can't open the file "<<defaultPedFile<<" please check again"<<endl;
							exit(0);
						}
				}
			}



		if(!strncmp(beg.c_str(),mapfile.c_str(),beg.length()))// && !strcmp(end.c_str(),deflt.c_str()))
		{
			if(end.length()==0)
				{
					cout<<"No .ped file provided... Program is exiting"<<endl;
					exit(0);
				}
			else
				{
					cout<<"Checking .map file"<<endl;
					defaultMapFile=end;

					if (openFile(defaultMapFile))
						{

						}
					else
						{
							cout<<"Can't open the file "<<defaultMapFile<<" please check again"<<endl;
							exit(0);
						}
				}
		}


		if(!strcmp(beg.c_str(), germlineOutputDirn.c_str()))
			{
				if(!strcmp(end.c_str(), deflt.c_str()))
					{
						cout<<"default directory (current)  will be used"<<endl;
					}
				else
					{
						cout<<"user  defined directory is used"<<endl;
						germlineOutputDir=end;
						system(("mkdir -p "+germlineOutputDir).c_str());
					}

			}

			
		if(!strcmp(beg.c_str(),errorFinderOutputDirn.c_str()))
			{
				if(!strcmp(end.c_str(),deflt.c_str()))
					{
						cout<<"default directory (current) will be used"<<endl;
					}
				else
					{
						cout<<"user defined directory is used"<<endl;
						//cout<<"LOOKO-->"<<end<<endl;
						errorFinderOutputDir=SplitFilenamefirst(end);
						outputname=SplitFilenamesecond(end);
						system(("mkdir -p " + errorFinderOutputDir).c_str());
						//cout<<"MEELO-->"<<errorFinderOutputDir<<endl;
						//cout<<"BANKAI-->"<<outputname<<endl;
					}
			}

		if(!strcmp(beg.c_str(),logfilen.c_str()))
			{
				if(!strcmp(end.c_str(), deflt.c_str()))
				{
					cout<<"Default directory (currrent) directory will be used "<<endl;
				}
				else
				{
					logfileOutputDirectory=end;
					system(("mkdir -p "+ logfileOutputDirectory).c_str() );
					logfilename=logfile;
				}
				/*
				cout<<"beg= "<<beg<<endl;
				cout<<"end= "<<end<<endl;
				cout<<"logfileOutputDirectory= "<<logfileOutputDirectory<<endl;
				exit(0);
				*/
			}



		if(!strcmp(beg.c_str(),outfile_n.c_str()))
			{
				//outfile=end;
				if(end.length()==0)
				{
					outfile=deflt;
					outfile_n="-outfile";
				}
				else
				{
					outfile=end;
					outfile_n="-outfile";
				}
			}

		if(!strcmp(beg.c_str(),fisheroutfile_n.c_str()))
			{

				if(end.length()==0)
				{
					outputname=deflt;
					
				}
				else
				{
					outputname=end;
					
				}
			}
	}


/***********************GERMLINE***********************/
//make the binary folder

//germline8=binary_output_directory+"/"+germline8;//binaries
germline8=binary_output_directory+germline8;
germline8+=" "+mapfile+" "+defaultMapFile+" "+ pedfile + " "+defaultPedFile +" "+outfile_n+" "+outfile;
germline8+=" ";

cout<<"READING GERMLINE PARAMS"<<endl;
/*germline inputs*/
	int methodFlagGL=0; //if flag is more than one than throw error as only one flag needs to be selected
	while(getline(file,each))
	{

		if(!strcmp(each.c_str(),heading2_2.c_str()))
		{
			break;
		}
		

		if(!strcmp(each.c_str(),heading2.c_str())  || each.length()==0)
		{

			continue;
		}

		if(each[0]=='#')
		{
			continue;
		}
		string tstring="";
		//int index=0;
		tstring=each;
		if(tstring.find(':')<0 || tstring.find(':')==-1)
		{
			beg=each.substr(0,each.find('#'));
			trim(beg);
			germline8+=beg+" ";
			continue;
		}
		
		beg=each.substr(0,each.find(delim));
		trim(beg);
		end=each.substr(each.find(':')+1,each.find('#') - each.find(':')-1);
		trim(end);
		cmnt=each.substr(each.find(hash)+1,each.length()- each.find(hash)-1);
		trim(cmnt);
		if(!strcmp(beg.c_str(),"a") ||!strcmp(beg.c_str(),"b")||!strcmp(beg.c_str(),"c") )
		{
			if(++methodFlagGL >1)
			{
				cerr<<"ERROR: multiple options selected in (GERMLINE) "<<endl;
				exit(0);
			}
			germline8+=" "+ end+" ";
			continue;
		}

		if(end.length()==0)
		{
			cerr<<"ERROR: attribute value missing in \""<<beg<<"\""<<endl;
			exit(0);
		}

		germline8+=beg + " "+end;
		germline8+=" ";		
	}
if(methodFlagGL==0)
{
	cerr<<"ERROR: no methods selected in (GERMLINE) "<<endl;
	exit(0);

}
//cout<<"germline8 parameters = "<<germline8<<endl;
cout<<"READING OPTIONAL GERMLINE PARAMS"<<endl;

while (getline(file,each))
{
	if(!strcmp(each.c_str(),heading3.c_str()))
		{
			break;
		}
		

	if(!strcmp(each.c_str(),heading2_2.c_str())  || each.length()==0)
		{

			continue;
		}
	
	if(each[0]=='#')
		{
			continue;
		}
	string tstring="";
	//int index=0;
	tstring=each;
	if(tstring.find(':')<0 || tstring.find(':')==-1)
	{
		beg=each.substr(0,each.find('#'));
		trim(beg);
		germline8+=beg+" ";
		continue;
	}
	beg=each.substr(0,each.find(delim));
	trim(beg);
	end=each.substr(each.find(':')+1,each.find('#') - each.find(':')-1);
	trim(end);
	cmnt=each.substr(each.find(hash)+1,each.length()- each.find(hash)-1);
	trim(cmnt);	
	if(end.length()==0)
		{
			cerr<<"ERROR: attribute value missing in \""<<beg<<"\""<<endl;
			exit(0);
		}

	germline8+=beg + " "+end;
	germline8+=" ";		
} 
cout<<"\n\ngermline8= "<<germline8<<endl;
cout<<"***Running germline***"<<endl;
//exit(0);
system(germline8.c_str());





//-------------------------------------------------------------------------------------------------------------------------------------------------//


/*****************************************Run-ErrorFinder25.0*************************/
//ErrorFinder25_0=  binary_output_directory+"/"+ErrorFinder25_0;	//binaries
ErrorFinder25_0=  binary_output_directory+ErrorFinder25_0;
ErrorFinder25_0 += " "+ pedfile_n+" "+ defaultPedFile+" ";
ErrorFinder25_0 += " " + bmatch_n + " " + outfile + ".bmatch";
ErrorFinder25_0 += " " + bsid_n + " " + outfile + ".bsid";
ErrorFinder25_0 += " " + bmid_n + " " + outfile + ".bmid ";
//cout<<"ErrorFinder25_0= "<<ErrorFinder25_0<<endl;
//cout<<"outfile="<<outfile<<endl;
int reducedFlag=0;
int methodFlagEF[3]={0};
string reducedParam="";
while(getline(file,each))
{
	if(!strcmp(each.c_str(),heading3.c_str()) || each.length()==0)
		{
			continue;
		}

	if(!strcmp(each.c_str(), heading3_3.c_str()))
		{
			break;
		}
	if(each[0]=='#')
		{
			continue;
		}

	string tstring="";
	//int index=0;
	tstring=each;
	if(tstring.find(':')<0 || tstring.find(':')==-1)
	{
		beg=each.substr(0,each.find('#'));
		trim(beg);
		ErrorFinder25_0+=beg+" ";
		continue;
	}

	beg=each.substr(0,each.find(delim));
	trim(beg);
	end=each.substr(each.find(':')+1,each.find('#') - each.find(':')-1);
	trim(end);
	cmnt=each.substr(each.find(hash)+1,each.length()- each.find(hash)-1);
	trim(cmnt);

	if(!strcmp(beg.c_str(),"a") ||!strcmp(beg.c_str(),"b"))
		{

			if(++methodFlagEF[0] >1)
			{
				cerr<<"ERROR: multiple options selected in (ERRORFINDER) "<<endl;
				exit(0);
			}
			beg=end.substr(0,end.find(delim));
			trim(beg);
			end=end.substr(end.find(delim)+1);
			trim(end);
			ErrorFinder25_0+=" "+ beg+ " "+ end+" ";
			continue;
		}
	if(!strcmp(beg.c_str(),"c") ||!strcmp(beg.c_str(),"d"))
		{
			if(++methodFlagEF[1] >1)
			{
				cerr<<"ERROR: multiple options selected in (ERRORFINDER) "<<endl;
				exit(0);
			}
			beg=end.substr(0,end.find(delim));
			trim(beg);
			end=end.substr(end.find(delim)+1);
			trim(end);
			ErrorFinder25_0+=" "+ beg+ " "+ end+" ";
			continue;
		}

	if(end.length()==0)
		{
			cerr<<"ERROR: attribute value missing in \""<<beg<<"\""<<endl;
			exit(0);
		}
	if(!strcmp(beg.c_str(),"-min_snp")  || !strcmp(beg.c_str(),"-min_cm")  )
	{
		if(reducedFlag==0)
		{
			ErrorFinder25_0+= " -reduced "+ end+" ";
			++reducedFlag;
			continue;
		}
		ErrorFinder25_0+=" "+end +" ";
		++reducedFlag;
		continue;
	}

	ErrorFinder25_0+=beg + " "+end;
	ErrorFinder25_0+=" ";	
}

if(reducedFlag%2!=0)
{
	cerr<<"ERROR: -min_snp and -min_cm flags need to be used togther"<<endl;
	exit(0);
}
if(methodFlagEF[0]%2 ==0)
{
	cerr<<"ERROR: only one option MUST be selected in (ERRORFINDER) "<<endl;
	exit(0);

}
if(methodFlagEF[1]%2 ==0)
{
	cerr<<"ERROR: only one option MUST be selected in (ERRORFINDER) "<<endl;
	exit(0);

}

//cout<<"ErrorFinder25_0 = "<<ErrorFinder25_0<<endl;
//exit(0);


while (getline(file,each))
{
	//cout<<"\n\n\n"<<each<<endl;
	if(!strcmp(each.c_str(),heading4.c_str()) || each.length()==0)
		{
			continue;
		}
	if(each[0]=='#')
		{
			continue;
		}
	string tstring="";
	//int index=0;
	tstring=each;
	if(tstring.find(':')<0 || tstring.find(':')==-1)
		{
			beg=each.substr(0,each.find('#'));
			trim(beg);
			ErrorFinder25_0+=beg+" ";
			continue;
		}
	beg=each.substr(0,each.find(delim));
	trim(beg);
	end=each.substr(each.find(':')+1,each.find('#') - each.find(':')-1);
	trim(end);
	cmnt=each.substr(each.find(hash)+1,each.length()- each.find(hash)-1);
	trim(cmnt);
	

	ErrorFinder25_0+=beg + " "+end;
	ErrorFinder25_0+=" ";

}


ErrorFinder25_0+=" "+logfilen+" "+logfilename+" ";
ErrorFinder25_0+= "|gzip >";
ErrorFinder25_0+=" "+outputname+".gz";

cout<<"\n\nErrorFinder25_0= "<<ErrorFinder25_0<<endl;
//cout<<ErrorFinder25_0<<endl;
system(ErrorFinder25_0.c_str());
file.close();

/*
cout<<"\n\n\n";
cout<<"pedfile directory "<<defaultPedFile<<endl;
cout<<"mapfile directory "<<defaultMapFile<<endl;
cout<<"germlineOutputDir "<<germlineOutputDir<<endl;
cout<<"errorfinder output directory "<< errorFinderOutputDir<<endl;
cout<<"log file outout directory "<<logfileOutputDirectory<<endl;
cout<<"outputname ="<<outputname<<endl;
*/
//string removee=" rm -rf *.cpp *.h *.hpp include/ germline8 ErrorFinder25.0 wrapper; ";
//system(removee.c_str());

string adjunctTemp="*.log";
system(("mv "+outfile+".bmatch"+" "+germlineOutputDir+"/").c_str());
system(("mv "+outfile+".bsid"+" "+germlineOutputDir+"/").c_str());
system(("mv "+outfile+".bmid"+" "+germlineOutputDir+"/").c_str());
system(("mv "+outputname+".gz"+" "+errorFinderOutputDir+"/" ).c_str());
system(("mv "+outfile+".log "+logfileOutputDirectory).c_str());
system(("mv "+logfilename+".log "+ logfileOutputDirectory+"/").c_str());

return 0;
}

bool openFile(string filename)
{
	//cout<<"filename= "<<filename<<endl;
	ifstream file_(filename.c_str());
	bool temp=file_.is_open();
	file_.close();
	return temp;

}

string SplitFilenamefirst (const std::string& str)
{
 
  int found = str.find_last_of("/");
  return str.substr(0,found);
}

string SplitFilenamesecond (const std::string& str)
{
 
  int found = str.find_last_of("/");
  return  str.substr(found+1) ;
}