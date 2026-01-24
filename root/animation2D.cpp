#include <TCanvas.h>
#include <TGraph2D.h>
#include <TMultiGraph.h>
#include <TEllipse.h>
#include <algorithm>
#include <vector>
#include"../include/csvconverter.h"

void animation2D(){
    std::vector<std::vector<double>> data = csvReaderToDouble("./csv/output.csv",1);
    //unpacking data
    int steps = data[0].size();
    std::cout << "Number of iterations: " << steps << std::endl;
    const int n_bodies = data.size()/3;
    std::cout << "Number of bodies: " << n_bodies << std::endl; 
    //std::vector<TGraph*> graphs;
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

    TCanvas* can = new TCanvas("can", "can", 2400, 2400);
    can->SetFillColor(kBlack);
    //data[3*n_bodies-3] is the x array of the biggest orbit
    //data[3*n_bodies-2] is the y array of the biggest orbit
    //we find the max and min of these to convert the coords in canvas coords
    double max_x = *std::max_element(data[3*n_bodies-3].begin(),data[3*n_bodies-3].end());
    double max_y = *std::max_element(data[3*n_bodies-2].begin(),data[3*n_bodies-2].end());
    double min_x = *std::min_element(data[3*n_bodies-3].begin(),data[3*n_bodies-3].end());
    double min_y = *std::min_element(data[3*n_bodies-2].begin(),data[3*n_bodies-2].end());
    //I want the point (x_min,y_min) to become (0,0) and (x_max,y_max) to become (1,1)
    //so x_new = (x_old-x_min)/(x_max-x_min)
    //so y_new = (y_old-y_min)/(y_max-y_min)
    std::vector<std::vector<double>> new_data(2*n_bodies, std::vector<double>(steps));
    int counter = 0;
    for(int i = 0; i < 3*n_bodies; i += 3){
	for(int j = 0; j < steps; j++){
	    new_data[counter][j] = (data[i][j] - min_x) / (max_x - min_x); 	//x coords
	    new_data[counter+1][j] = (data[i+1][j] - min_y) / (max_y - min_y); 	//y coords
	}
	counter += 2;
    }

    // new_data are normalized coords

    //animation
    std::vector<TEllipse*> circles(n_bodies);
    for (int i = 0; i < n_bodies; i++){
	TEllipse* dummy = new TEllipse(0,0,0.005,0.005); //coords, semiaxes
	dummy->SetFillColor(kWhite);
	circles[i] = dummy;
    }
    std::cout<<"Circles created\n";
    for(int i = 0; i < steps; i += steps/120) {
	counter = 0;
	for(int j = 0; j < 2*n_bodies; j += 2) {
	    circles[counter]->SetX1(new_data[j][i]);
	    circles[counter]->SetY1(new_data[j+1][i]);
	    circles[counter]->Draw();
	    counter += 1;
	}
	can->Update();
	can->Print("diofa.gif+");
    }
	

}
