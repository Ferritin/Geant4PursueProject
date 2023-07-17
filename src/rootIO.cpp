#include "rootIO.h"

rootIO::rootIO()
{ }

~rootIO::rootIO()
{ }

void rootIO::draw1DGraph(std::vector<double> &xValues, std::vector<double> &yValues)
{
  TCanvas *canvas = new TCanvas("canvas", "Graph", 1);

  double xArray[x.size()];
  double yArray[y.size()];

  for(int i = 0; i < x.size(); i++)
  {
    xArray[i] = xValues[i];
  
  }


  TGraph *graph = new TGraph(x.size(), xArray, yArray);
}
