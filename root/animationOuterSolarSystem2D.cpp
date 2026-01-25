#include <TCanvas.h>
#include <TGraph2D.h>
#include <TMultiGraph.h>
#include <TEllipse.h>
#include <algorithm>
#include <vector>
#include"../include/csvconverter.h"

//this is an animator for the outer solar system: it animates 2D orbits simulated with
//the preset "Outer solar System" of /bin/main and puts the resulting animation in
// ./root/media/animationOuterSolarSystem.gif
//These gifs can be converted to videos by using ffmpeg -i /path/to/yourgif.gif /path/to/yourvideo.mp4

void animationOuterSolarSystem2D(){
    std::vector<std::vector<double>> data = csvReaderToDouble("./csv/output.csv",1);
    //unpacking data
    int steps = data[0].size();
    std::cout << "Number of iterations: " << steps << std::endl;
    const int n_bodies = data.size()/3;
    std::cout << "Number of bodies: " << n_bodies << std::endl; 

    TCanvas* can = new TCanvas("can", "can", 2400, 2400);
    can->SetFillColor(kBlack);
    //here we are sure that Neptune's orbit is the biggest, so we use
    //the general purpose animator way to determine max and min
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
    std::vector<TEllipse*> circles;
    
    TEllipse* sun = new TEllipse(0,0,0.01,0.01);
    sun->SetFillColor(kYellow);
    circles.push_back(sun);
    
    TEllipse* jupiter = new TEllipse(0,0,0.003,0.003);
    jupiter->SetFillColor(kOrange - 9);
    circles.push_back(jupiter);
    
    TEllipse* saturn = new TEllipse(0,0,0.003,0.003);
    saturn->SetFillColor(kOrange - 6);
    circles.push_back(saturn);
    
    TEllipse* uranus = new TEllipse(0,0,0.003,0.003);
    uranus->SetFillColor(kCyan - 10);
    circles.push_back(uranus);
    
    TEllipse* nepture = new TEllipse(0,0,0.003,0.003);
    neptune->SetFillColor(kBlue - 1);
    circles.push_back(neptune);
    
    for(int i = 0; i < steps; i += steps/240) {
	counter = 0;
	for(int j = 0; j < 2*n_bodies; j += 2) {
	    circles[counter]->SetX1(new_data[j][i]);
	    circles[counter]->SetY1(new_data[j+1][i]);
	    circles[counter]->Draw();
	    counter += 1;
	}
	can->Update();
	can->Print("./root/media/animationOuterSolarSystem.gif+");
    }
	

}
