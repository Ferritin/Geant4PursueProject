#include "utilityFunctions.h"

namespace utilityFunctions
{

  /*

  Method originally written by Hans Wenzel,
  https://github.com/hanswenzel/LArProperties/blob/main/scripts/Cerenkov.C

  Modified so that energy input is MeV instead of eV
  */
  G4double evToLambda(G4double MeV)
  {
    G4double h = 4.13566743E-15;
    G4double c = 299792458.;

    //Converts MeV to eV
    G4double eV = MeV * (1.e+6);

    double lambda = (h*c)/(eV * 1.e-9);
    return lambda;
  }

  G4double getCerenkovAngleOfEmission(G4double refractiveIndex, G4double v)
  {
    G4double c = 299792458.;
    G4double pi = 3.14;
    G4cout <<"v: " << v << G4endl;

    //Geant4 returns velocity in Mm/s, converting it back into m/s
    G4double actualV = v * (1000000.);

    G4cout <<"actuaV: "<< actualV << G4endl;

    G4double beta = actualV / c;

    G4cout <<"beta: "<< beta << G4endl;

    G4double cosTheta = (1.)/(beta * refractiveIndex);

    G4cout <<"cosTheta: " << cosTheta << G4endl;


    G4double thetaRadians = std::acos(cosTheta);
    G4double thetaDegrees = (thetaRadians * 180.) / pi;

    return thetaDegrees;
  }


}
