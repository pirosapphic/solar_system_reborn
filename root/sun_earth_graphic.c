#include<TCanvas.h>
#include<TGraph2D.h>
#include<TMultiGraph.h>
#include<vector>
#include"../include/csvconverter.h"

void sun_earth_graphic(){
    std::vector<std::vector<double>> data = csvReaderToDouble("./csv/sun_earth.csv",1);
    std::vector<double> x1 = data[0];
    std::vector<double> y1 = data[1]; 
    std::vector<double> z1 = data[2]; //sun

    std::vector<double> x2 = data[3];
    std::vector<double> y2 = data[4];
    std::vector<double> z2 = data[5]; //earth

    //TCanvas* can1 = new TCanvas("body1","orbits",1200,800);
    //can1->SetFillColor(0);
    //can1->cd();
    TGraph2D* g_1 = new TGraph2D(x1.size(),x1.data(),y1.data(),z1.data());
    //g_1->SetTitle("Sun orbit;X [m]; Y [m]; Z [m]");
    g_1->SetMarkerColor(4);
    //g_1->Draw("P");


    //TCanvas* can2 = new TCanvas("body2","orbits",1200,800);
    //can2->SetFillColor(0);
    //can2->cd();
    TGraph2D* g_2 = new TGraph2D(x2.size(),x2.data(),y2.data(),z2.data());
    //g_2->SetTitle("Earth orbit;X [m]; Y [m]; Z [m]");
    //g_2->Draw("P");

    TCanvas* canTOT = new TCanvas("total","orbits:diocan",1200,800);
    canTOT->cd();
    g_2->SetTitle("Sun - Earth orbit; x[m]; y[m]; z[m]"); 
    g_2->Draw("P");     //smaller body and bigger orbit first!!
    g_1->Draw("P same");


}
