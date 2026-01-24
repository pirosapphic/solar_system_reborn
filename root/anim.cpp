#include <TCanvas.h>
#include <TGraph2D.h>
#include <TMultiGraph.h>
#include <TEllipse.h>
#include <algorithm>
#include <vector>
#include"../include/csvconverter.h"

void bodiesGraphic2D(){
    std::vector<std::vector<double>> data = csvReaderToDouble("./csv/output.csv",1);
    //unpacking data
    int steps = data[0].size();
    std::cout << "Number of iterations: " << steps << std::endl;
    const int n_bodies = data.size()/3;
    std::cout << "Number of bodies: " << n_bodies << std::endl; 
    std::vector<TGraph*> graphs;
    int counter = data.size() - 1;
    /*
    TCanvas* can = new TCanvas("total","orbits",1200,800);
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
    }*/

    TCanvas* can = new TCanvas("can", "can", 1200, 800);
    //data[nbodies] is the x array of the biggest orbit
    //data[nbodies+1] is the y array of the biggest orbit
    //we find the max and min of these to convert the coords in canvas coords
    double max_x = *std::max_element(data[nbodies].begin(),data[nbodies].end());
    double max_y = *std::max_element(data[nbodies+1].begin(),data[nbodies+1].end());
    double min_x = *std::min_element(data[nbodies].begin(),data[nbodies].end());
    double min_y = *std::min_element(data[nbodies+1].begin(),data[nbodies+1].end());
    //I want the point (x_min,y_min) to become (0,0) and (x_max,y_max) to become (1,1)
    //so x_new = (x_old-x_min)/(x_max-x_min)

    counter = 0;
    std::vector<std::vector<double>> new_data(3*n_bodies, std::vector<double>(steps));
    for(int j = 0; j < n_bodies; j++){
	for (int i = 0; i < steps; i++){
	    new_data[counter+j][i] = (data[counter+j][i] - min_x) / (max_x - min_x);
	    new_data[counter+j+1][i] = (data[counter+j+1][i] - min_y) / (max_y - min_y);
	}
	counter+=3;
    }
    // new_data are normalized coords

    //animation
    std::vector<TEllipse*> circles(n_bodies);
    for (int i = 0; i < n_bodies; i++){
	TEllipse* dummy = new TEllipse(0,0,0.01,0.01); //coords, semiaxes
	dummy->SetFillColor(kBlack);
	circles[i] = dummy;
    }
    for(int i = 0; i<steps; i++) {
	for(int j = 0; j < circles.size(); j += 2) {
	    circles[j]->SetX(new_data[j][i]);
	    circles[j]->SetY(new_data[j+1][i]);
	    circles[j]->Draw();
	    can->update();
	}
	

}
