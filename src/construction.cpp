#include "construction.h"


testDetector::~testDetector()
{}

//Reads GDML geometry
testDetector::testDetector(const G4GDMLParser& parser) : G4VUserDetectorConstruction(), fParser(parser)
{}

//Constructs geometry read from GDML parser
G4VPhysicalVolume* testDetector::Construct()
{
  return fParser.GetWorldVolume();
}

void testDetector::ConstructSDandField()
{
  //------------------------------------------------
  // Sensitive detectors
  //------------------------------------------------

  G4SDManager* SDman = G4SDManager::GetSDMpointer();

  G4String photonSDname = "PhotonDetector";
  sensitiveDetector* photonSD =
    new sensitiveDetector(photonSDname);
  SDman->AddNewDetector( photonSD );


  //Retrieves auxiliary information for the sensitive detector

  const G4GDMLAuxMapType* auxmap = fParser.GetAuxMap();
  G4cout << "Found " << auxmap->size()
            << " volume(s) with auxiliary information."
            << G4endl << G4endl;
  for(G4GDMLAuxMapType::const_iterator iter=auxmap->begin();
      iter!=auxmap->end(); iter++)
  {
    G4cout << "Volume " << ((*iter).first)->GetName()
           << " has the following list of auxiliary information: "
           << G4endl << G4endl;
    for (G4GDMLAuxListType::const_iterator vit=(*iter).second.begin();
         vit!=(*iter).second.end(); vit++)
    {
      G4cout << "--> Type: " << (*vit).type
                << " Value: " << (*vit).value << G4endl;
    }
  }
  G4cout << G4endl;

  //Sets the sensitive detectors for the volumes

  for(G4GDMLAuxMapType::const_iterator iter=auxmap->begin();
      iter!=auxmap->end(); iter++)
  {
    G4cout << "Volume " << ((*iter).first)->GetName()
           << " has the following list of auxiliary information: "
           << G4endl << G4endl;
    for (G4GDMLAuxListType::const_iterator vit=(*iter).second.begin();
         vit!=(*iter).second.end();vit++)
    {
      if ((*vit).type=="SensDet")
      {
        G4cout << "Attaching sensitive detector " << (*vit).value
               << " to volume " << ((*iter).first)->GetName()
               <<  G4endl << G4endl;

        G4VSensitiveDetector* mydet =
          SDman->FindSensitiveDetector((*vit).value);
        if(mydet)
        {
          G4LogicalVolume* myvol = (*iter).first;
          myvol->SetSensitiveDetector(mydet);
        }
        else
        {
          G4cout << (*vit).value << " detector not found" << G4endl;
        }
      }
    }
  }
}
