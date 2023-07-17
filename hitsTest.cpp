#include <iostream>
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4GDMLParser.hh"
#include "G4Types.hh"
#include "construction.h"
#include "particleGun.h"
#include "physics.h"
#include "stackingAction.h"
#include "userAction.h"

void print_aux(const G4GDMLAuxListType* auxInfoList, G4String prepend="|")
{
  for(std::vector<G4GDMLAuxStructType>::const_iterator
      iaux = auxInfoList->begin(); iaux != auxInfoList->end(); iaux++ )
    {
      G4String str=iaux->type;
      G4String val=iaux->value;
      G4String unit=iaux->unit;

      G4cout << prepend << str << " : " << val  << " " << unit << G4endl;

      if (iaux->auxList) print_aux(iaux->auxList, prepend + "|");
    }
  return;
}


int main(int argc, char **argv)
{
	//Loads gdml file into parser
	G4cout << G4endl;
	G4cout << "Usage: load_gdml <intput_gdml_file:mandatory>"
				 << " <output_gdml_file:optional>" << G4endl;
	G4cout << G4endl;

	if (argc<2)
	{
		 G4cout << "Error! Mandatory input file is not specified!" << G4endl;
		 G4cout << G4endl;
		 return -1;
	}

	G4GDMLParser parser;

	parser.SetOverlapCheck(true);
	parser.Read(argv[1]);

	if (argc>4)
	{
		 G4cout << "Error! Too many arguments!" << G4endl;
		 G4cout << G4endl;
		 return -1;
	}

	//Starts a G4 run manager, it runs everything
	G4RunManager *runManager = new G4RunManager();

	//Detector construction
	runManager -> SetUserInitialization(new testDetector(parser));

	//Physics List
	runManager -> SetUserInitialization(new TestPhysicsList());

  //Sets userAction
  runManager -> SetUserInitialization(new userActionInitialization());

  //Sets primary generator action
	runManager -> SetUserAction(new ParticleGeneratorAction());

  //Sets stacking action
  runManager -> SetUserAction(new stackingAction());

	//Initiates the UI and vis managers
	G4UIExecutive *ui = new G4UIExecutive(argc, argv);
	G4VisManager *visManager = new G4VisExecutive();
	visManager -> Initialize();

	G4UImanager *UImanager = G4UImanager::GetUIpointer();

	//Initiates basic visualization, and
	//Sets particle filters
	//UImanager -> ApplyCommand("/control/execute photon_ConfigWithVis.mac");
  UImanager -> ApplyCommand("/control/execute photon_Config.mac");



	ui -> SessionStart();

	return 0;

}
