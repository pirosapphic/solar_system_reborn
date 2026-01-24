#include <TCanvas.h>
#include <TGraph2D.h>
#include <TMultiGraph.h>
#include <vector>
#include"../include/csvconverter.h"

void bodiesGraphic3D(){
    std::vector<std::vector<double>> data = csvReaderToDouble("./csv/output.csv",1);
    //unpacking data
    std::cout << "Number of iterations: " << data[0].size() << std::endl;
    const int n_bodies = data.size()/3;
    std::cout << "Number of Bodies: " << n_bodies << std::endl; 
    std::vector<TGraph2D*> graphs;
    TCanvas* can = new TCanvas("3D visualizer","3D orbits",1200,800);
    int counter = data.size() - 1;
    for (int i = n_bodies; i > 0; i--) {
        TGraph2D* dummy =  new TGraph2D(data[i].size(), data[counter-2].data(), data[counter-1].data(), data[counter].data()); 
	graphs.push_back(dummy);
        counter -= 3;
    }
    graphs[0]->Draw("P");
    graphs[0]->SetTitle("3D orbits visualizer;x[m];y[m];z[m]");
    for(int i = 1; i < n_bodies; i++){
        graphs[i]->Draw("P same");
    } 
}
