#include<TCanvas.h>
#include<TGraph2D.h>
#include<TMultiGraph.h>
#include<vector>
#include"../include/csvconverter.h"

void earth_moon_graphic(){
    std::vector<std::vector<double>> data = csvReaderToDouble("./csv/earth_moon.csv",1);
    std::vector<double> x1 = data[0];
    std::vector<double> y1 = data[1]; 
    std::vector<double> z1 = data[2]; //earth

    std::vector<double> x2 = data[3];
    std::vector<double> y2 = data[4];
    std::vector<double> z2 = data[5]; //moon

    //TCanvas* canE = new TCanvas("earth","orbits",1200,800);
    //canE->SetFillColor(0);
    //canE->SetGrid();
    TGraph2D* g_earth = new TGraph2D(x1.size(),x1.data(),y1.data(),z1.data());
    //g_earth->SetTitle("earth");
    //g_earth->Draw("P");
    //g_earth->GetXaxis()->SetTitle("x");


    //TCanvas* canM = new TCanvas("moon","orbits",1200,800);
    //canM->SetFillColor(0);
    //canM->SetGrid();
    //canM->cd();
    TGraph2D* g_moon = new TGraph2D(x2.size(),x2.data(),y2.data(),z2.data());
    //g_moon->Draw("P");

    TCanvas* canTOT = new TCanvas("total","orbits",1200,800);
    canTOT->cd();
    g_moon->SetTitle("Earth-Moon system;x[m];y[m];z[m]");
    g_moon->Draw("P");
    g_earth->Draw("P same");
}
