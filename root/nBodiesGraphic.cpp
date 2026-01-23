#include <TCanvas.h>
#include <TGraph2D.h>
#include <TMultiGraph.h>
#include <vector>
#include"../include/csvconverter.h"

void nBodiesGraphic(){
    std::vector<std::vector<double>> data = csvReaderToDouble("./csv/output.csv",1);
    //unpacking data
    std::cout << "Data size: " << data.size() << std::endl;
    const int n_bodies = data.size()/3;
    std::cout << "nbodies: " << n_bodies << std::endl; 
    std::vector<TGraph2D*> graphs;
    TCanvas* can = new TCanvas("total","orbits",1200,800);
    int counter = data.size() - 1;
    for (int i = n_bodies; i > 0; i--) {
        TGraph2D* dummy =  new TGraph2D(data[i].size(), data[counter-2].data(), data[counter-1].data(), data[counter].data()); 
	graphs.push_back(dummy);
        counter -= 3;
    }
    for(int i = 0; i < n_bodies; i++){
        if(i == 0) graphs[i]->Draw("P");
        else graphs[i]->Draw("P same");
    } 
}
