#include <TCanvas.h>
#include <TGraph2D.h>
#include <TMultiGraph.h>
#include <vector>
#include"../include/csvconverter.h"

void bodiesGraphic2D(){
    std::vector<std::vector<double>> data = csvReaderToDouble("./csv/output.csv",1);
    //unpacking data
    std::cout << "Number of iterations: " << data[0].size() << std::endl;
    const int n_bodies = data.size()/3;
    std::cout << "Number of bodies: " << n_bodies << std::endl; 
    std::vector<TGraph*> graphs;
    TCanvas* can = new TCanvas("total","orbits",1200,800);
    int counter = data.size() - 1;
    for (int i = n_bodies; i > 0; i--) {
        TGraph* dummy =  new TGraph(data[i].size(), data[counter-2].data(), data[counter-1].data()); 
	graphs.push_back(dummy);
        counter -= 3;
    }
    graphs[0]->SetTitle("XY plane projection of the orbits;x[m];y[m]");
    graphs[0]->Draw("AP"); //the last orbit should be the biggest
			   //so we draw it first.
    for(int i = 1; i < n_bodies; i++){
	graphs[i]->Draw("same");
    } 
}
