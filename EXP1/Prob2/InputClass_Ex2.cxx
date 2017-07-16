/*************************************************/
//              DESCRIPTION
// Simple PWR UOX Scenario from Exo 1 FCCI
//
//@author Nico
/*************************************************/
#include "CLASSHeaders.hxx"
#include <sstream>
#include <iomanip>
#include <math.h>
#include <string>

#include "XS/XSM_MLP.hxx"			
#include "Irradiation/IM_RK4.hxx"
#include "EquivalenceModel.hxx"

using namespace std;

string dtoa(double num)
{
        ostringstream os(ostringstream::out);
        os<<setprecision(6)<<num;
        return os.str();
}
string itoa(int num)
{
        ostringstream os(ostringstream::out);
        os<<num;
        return os.str();
}

int main(int argc, char** argv)
{

	cSecond year = 3600*24.*365.25; 

	//##########################################################################################
	//####### USE ##############################################################################
	//##########################################################################################

	if (argc != 13)
	{
		cout<<"#############################################"<<endl;
		cout<<"#############################################"<<endl<<endl;
		cout<<"USE : "<<endl<<endl;
		cout<<"CLASS_Exec UOXEnr BU PSpec Mass Batch LF"<<endl<<endl;
		cout<<"EXAMPLE : "<<endl<<endl;
		cout<<"CLASS_Exec 4 40 30 90 3 1 4 40 30 90 3 1"<<endl<<endl;;
		cout<<"#############################################"<<endl<<endl;;
		cout<<"#############################################"<<endl;
		exit(1);
	}

	//##########################################################################################
	//####### PARAMETERS #######################################################################
	//##########################################################################################

	double UOXEnr		= atof(argv[1]);	// %w
	double BurnUp 		= atof(argv[2]);	// GWd/t 
	double SpecPower	= atof(argv[3]);	// W/g
	double HMMass		= atof(argv[4]);	// t
	int BatchNumber 	= atoi(argv[5]); 	// 

	double LoadFactor 	= atof(argv[6]);	// 1
	double Power 		= SpecPower * HMMass * 1e6 * LoadFactor;
	double CycleTime 	= BurnUp * HMMass / (Power/1.e9) / (1/(3600.*24.));

    cSecond LifeTime     = 100*year;
    cSecond StartingTime =  0;

	double UOXEnr2		= atof(argv[7]);	// %w
	double BurnUp2 		= atof(argv[8]);	// GWd/t 
	double SpecPower2	= atof(argv[9]);	// W/g
	double HMMass2		= atof(argv[10]);	// t
	int BatchNumber2 	= atoi(argv[11]); 	// 

	double LoadFactor2 	= atof(argv[12]);	// 1
	double Power2 		= SpecPower2 * HMMass2 * 1e6 * LoadFactor2;
	double CycleTime2 	= BurnUp2 * HMMass2 / (Power2/1.e9) / (1/(3600.*24.));

    cSecond LifeTime2     = 100*year;
    cSecond StartingTime2 =  0;

	cout<<"#############################################"<<endl;
	cout<<"#############################################"<<endl<<endl;
	cout<<"REACTOR 1 : "<<endl<<endl;
    cout<<"Enrichment  "<<UOXEnr  <<""<<endl;
    cout<<"LoadFactor  "<<LoadFactor  <<""<<endl;
	cout<<"SpecPower   "<<SpecPower   <<" W/g"<<endl;
	cout<<"HMMass      "<<HMMass      <<" t"<<endl;
	cout<<"BurnUp      "<<BurnUp      <<" GWd/t"<<endl;
	cout<<"CycleTime   "<<CycleTime / 365.25 / 24. / 3600.   <<" y"<<endl;
	cout<<"BatchNumber "<<BatchNumber <<""<<endl;
	cout<<"LifeTime    "<<LifeTime / 365.25 / 24. / 3600.    <<" y"<<endl;
	cout<<"Power       "<<Power/1e9   <<" GW"<<endl;
	cout<<"REACTOR 2 : "<<endl<<endl;
    cout<<"Enrichment  "<<UOXEnr2  <<""<<endl;
	cout<<"LoadFactor  "<<LoadFactor2  <<""<<endl;
	cout<<"SpecPower   "<<SpecPower2   <<" W/g"<<endl;
	cout<<"HMMass      "<<HMMass2      <<" t"<<endl;
	cout<<"BurnUp      "<<BurnUp2      <<" GWd/t"<<endl;
	cout<<"CycleTime   "<<CycleTime2 / 365.25 / 24. / 3600.   <<" y"<<endl;
	cout<<"BatchNumber "<<BatchNumber2 <<""<<endl;
	cout<<"LifeTime    "<<LifeTime / 365.25 / 24. / 3600.    <<" y"<<endl;
	cout<<"Power       "<<Power2/1e9   <<" GW"<<endl;
	cout<<"#############################################"<<endl<<endl;;
	cout<<"#############################################"<<endl;

	//##########################################################################################
	//####### SCENARIO DATA ####################################################################
	//##########################################################################################

	cSecond d_TimeStep 		= year / 12.;//atof(s_TimeStep.c_str()); 		// arg should be in seconds
	cSecond d_TimeScenario	= 100*year  ;//atof(s_TimeScenario.c_str()); 	// arg should be in seconds
	string s_DirFileName 		= string("OUT")
                                + string("_") + argv[1] + string("_") + argv[2] + string("_") + argv[3] + string("_") + argv[4] + string("_") + argv[5] + string("_") + argv[6]
								+ string("_") + argv[7] + string("_") + argv[8] + string("_") + argv[9] + string("_") + argv[10] + string("_") + argv[11] + string("_") + argv[12];
	string s_CMD = 	string("mkdir ") + s_DirFileName;					
	system(s_CMD.c_str());
	string s_FileName 		= s_DirFileName + string("/OUT.root");

	//##########################################################################################
	//####### LOG MANAGEMENT ###################################################################
	//##########################################################################################

	int Std_output_level 	= 0;
	int File_output_level 	= 0;
	CLASSLogger *Logger 	= new CLASSLogger("CLASS_OUTPUT.log",Std_output_level,File_output_level);

	//##########################################################################################
	//####### SCENARIO #########################################################################
	//##########################################################################################

	Scenario *gCLASS=new Scenario(0*year,Logger);
	gCLASS->SetStockManagement(true);
	gCLASS->SetTimeStep((double)d_TimeStep);
	gCLASS->SetOutputFileName(s_FileName);
	gCLASS->SetSoberTerminalOutput();
	gCLASS->SetZAIThreshold(82);

	//##########################################################################################
	//####### DATABASE #########################################################################
	//##########################################################################################

    string CLASS_PATH = getenv("CLASS_PATH");
    string PATH_TO_DATA = CLASS_PATH + "/DATA_BASES/";

   	// DECAY
	DecayDataBank* DecayDB = new DecayDataBank(gCLASS->GetLog(), PATH_TO_DATA + "DECAY/ALL/Decay.idx");
	gCLASS->SetDecayDataBase(DecayDB);

	// Bateman Solver
	IM_RK4*			IMRK4 		= new IM_RK4(gCLASS->GetLog());

	// REP UOX
	XSM_MLP* 		XSMUOX 			= new XSM_MLP(gCLASS->GetLog(), PATH_TO_DATA + "PWR/UOX/XSModel/30Wg_FullUOX");
/*	
	EquivalenceModel*	EQMPWRUOX 	= new EquivalenceModel(gCLASS->GetLog(), PATH_TO_DATA + "PWR/UOX/EQModel/XML/PWR_UOX.xml", PATH_TO_DATA + "PWR/UOX/EQModel/NFO/PWR_UOX.nfo");
	EQMPWRUOX->SetModelParameter("kThreshold",KseuilUOx);
	EQMPWRUOX->SetModelParameter("NumberOfBatch",NumberOfBatchesUOx);
*/
	EquivalenceModel*	EQMPWRUOX 	= new EquivalenceModel(gCLASS->GetLog(), PATH_TO_DATA + "PWR/UOX/EQModel/NFO/PWR_UOX.nfo");
	PhysicsModels*		PMUOX		= new PhysicsModels(XSMUOX, EQMPWRUOX, IMRK4);
/*
	// REP MOx 
	XSM_MLP* 			XSMMOX 		= new XSM_MLP(gCLASS->GetLog(), PATH_TO_DATA + "PWR/MOX/XSModel/30Wg_FullMOX");
	EquivalenceModel* 	EQMPWRMOX 	= new EquivalenceModel(gCLASS->GetLog(), PATH_TO_DATA + "PWR/MOX/EQModel/XML/PWR_MOX.xml", PATH_TO_DATA + "PWR/MOX/EQModel/NFO/PWR_MOX.nfo");
	EQMPWRMOX->SetModelParameter("kThreshold",KseuilMOx);
	EQMPWRMOX->SetModelParameter("NumberOfBatch",NumberOfBatchesMOx);
	PhysicsModels*		PMMOX		= new PhysicsModels(XSMMOX, EQMPWRMOX, IMRK4);
*/
	//##########################################################################################
	//####### IV ###############################################################################
	//##########################################################################################

	//##########################################################################################
	//####### STORAGE ##########################################################################
	//##########################################################################################
 
	Storage *StockUOx = new Storage(gCLASS->GetLog());
	StockUOx->SetName("StockUOx");
	gCLASS->Add(StockUOx);

	//##########################################################################################
	//####### SEPARATION PLANT #################################################################
	//##########################################################################################

	//##########################################################################################
	//####### POOL #############################################################################
	//##########################################################################################

	//##########################################################################################
	//####### FABRICATION PLANT #################################################################
	//##########################################################################################

	FabricationPlant *FP_UOX = new FabricationPlant(gCLASS->GetLog(), 0*year);
	FP_UOX->SetName("Fab_UOX");
	//FP_UOX->AddInfiniteStorage("Fissile",0.02,0.06,1);
	FP_UOX->AddInfiniteStorage("Fissile",UOXEnr/100.,1);
	FP_UOX->AddFuelBuffer("Fertile");
	gCLASS->AddFabricationPlant(FP_UOX);

    FabricationPlant *FP_UOX2 = new FabricationPlant(gCLASS->GetLog(), 0*year);
    FP_UOX2->SetName("Fab_UOX2");
    //FP_UOX->AddInfiniteStorage("Fissile",0.02,0.06,1);
    FP_UOX2->AddInfiniteStorage("Fissile",UOXEnr2/100.,1);
    FP_UOX2->AddFuelBuffer("Fertile");
    gCLASS->AddFabricationPlant(FP_UOX2);

/*
	FabricationPlant *FP_MOX = new FabricationPlant(gCLASS->GetLog(), 2.*year);
	FP_MOX->SetName("FP_MOX");
	FP_MOX->SetSeparationManagement(true);
	FP_MOX->SetStorageManagement(SM);
	FP_MOX->AddStorage("Fissile", StockUOx, 0.04, 0.16,1);
	FP_MOX->AddFuelBuffer("Fertile");
	gCLASS->AddFabricationPlant(FP_MOX);
*/
	//##########################################################################################
	//####### REACTOR ##########################################################################
	//##########################################################################################
	
	//##########################################################################################
	//####### REP UOX ##########################################################################
	//##########################################################################################
	
	Reactor* PWR_UOX = new Reactor(gCLASS->GetLog(),PMUOX,FP_UOX,StockUOx,StartingTime,LifeTime,Power,HMMass,BurnUp,LoadFactor);
	PWR_UOX->SetName("PWR_UOx");
	gCLASS->AddReactor(PWR_UOX);

	Reactor* PWR_UOX2 = new Reactor(gCLASS->GetLog(),PMUOX,FP_UOX2,StockUOx,StartingTime2,LifeTime2,Power2,HMMass2,BurnUp2,LoadFactor2);
	PWR_UOX2->SetName("PWR_UOx2");
	gCLASS->AddReactor(PWR_UOX2);

	//##########################################################################################
	//####### REP MOX ##########################################################################
	//##########################################################################################
/*
	HMMass 		= HMMassMOx;
	Power 		= PowerMOx;
	BurnUp 		= BU_MOX;
	LoadFactor 	= LoadFactorMOx;

	StartingTime =  TimeStartMox;
	LifeTime     =  LifeTimeMOx;
	
	Reactor* PWR_MOX = new Reactor(gCLASS->GetLog(),PMMOX,FP_MOX,PoolMOx,StartingTime,LifeTime,Power,HMMass,BurnUp,LoadFactor);

	PWR_MOX->SetName("PWR_MOX");
	gCLASS->AddReactor(PWR_MOX);
*/

	//##########################################################################################
	//####### EVOLUTION ########################################################################
	//##########################################################################################

	gCLASS->Evolution((double)d_TimeScenario);

	delete gCLASS;
}

//==========================================================================================
// Compilation
//==========================================================================================
/*
 
g++ -o CLASS_Exec InputClass.cxx -I $CLASS_include -L $CLASS_lib -lCLASSpkg `root-config --cflags` `root-config --libs` -fopenmp -lgomp
 
 
 */
