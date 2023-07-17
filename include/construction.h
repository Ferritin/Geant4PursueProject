#pragma once

#include "G4VUserDetectorConstruction.hh"
#include "sensitiveDetector.h"
#include "G4SDManager.hh"
#include "G4GDMLParser.hh"

class G4GDMLParser;

class testDetector : public G4VUserDetectorConstruction
{

public:
	testDetector(const G4GDMLParser& parser);
	~testDetector();

	virtual G4VPhysicalVolume *Construct();
	virtual void ConstructSDandField();

private:

	const G4GDMLParser& fParser;

};
