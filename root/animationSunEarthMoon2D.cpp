#include <TCanvas.h>
#include <TGraph2D.h>
#include <TMultiGraph.h>
#include <TEllipse.h>
#include <algorithm>
#include <vector>
#include"../include/csvconverter.h"

//this is an animator for the sun-earth-moon system: it animates 2D orbits simulated with
//the preset "sun earth moon" of /bin/main and puts the resulting animation in
// ./root/media/animationSunEarthMoon.gif
//These gifs can be converted by using ffmpeg -i /path/to/yourgif.gif /path/to/yourvideo.mp4

void animationSunEarthMoon2D(){
    std::vector<std::vector<double>> data = csvReaderToDouble("./csv/output.csv",1);
    //unpacking data
    int steps = data[0].size();
    std::cout << "Number of iterations: " << steps << std::endl;
    const int n_bodies = data.size()/3;
    std::cout << "Number of bodies: " << n_bodies << std::endl; 

    TCanvas* can = new TCanvas("can", "can", 2400, 2400);
    can->SetFillColor(kBlack);
    //as this is NOT the general animator, we use the max and min we can see by graphing the orbit.

    double max_x = 155e9; 
    double max_y = 150e9;
    double min_x = -150e9;
    double min_y = -155e9;
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
    
    TEllipse* sun = new TEllipse(0,0,0.01,0.01);
    sun->SetFillColor(kYellow);
    circles[0] = sun;
    
    TEllipse* earth = new TEllipse(0,0,0.003,0.003);
    earth->SetFillColor(kBlue);
    circles[1] = earth;
    
    TEllipse* moon = new TEllipse(0,0,0.002,0.002);
    moon->SetFillColor(kWhite);
    circles[2] = moon;
    
    for(int i = 0; i < steps; i += steps/240) {
	counter = 0;
	for(int j = 0; j < 2*n_bodies; j += 2) {
	    circles[counter]->SetX1(new_data[j][i]);
	    circles[counter]->SetY1(new_data[j+1][i]);
	    circles[counter]->Draw();
	    counter += 1;
	}
	can->Update();
	can->Print("./root/media/animationSunEarthMoon.gif+");
    }
	

}
