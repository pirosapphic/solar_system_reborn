#include<TCanvas.h>
#include<TGraph2D.h>
#include<TMultiGraph.h>
#include<vector>
#include"../include/csvconverter.h"

void threeBodiesGraphic(){
    std::vector<std::vector<double>> data = csvReaderToDouble("./csv/output.csv",1);
    //unpacking data
    std::vector<double> x1 = data[0];
    std::vector<double> y1 = data[1]; 
    std::vector<double> z1 = data[2]; //body1

    std::vector<double> x2 = data[3];
    std::vector<double> y2 = data[4];
    std::vector<double> z2 = data[5]; //body2

    std::vector<double> x3 = data[6];
    std::vector<double> y3 = data[7]; 
    std::vector<double> z3 = data[8]; //body3
    /*TGraph2D* g_p1= new TGraph2D(x1.size(),x1.data(),y1.data(),z1.data());

    TGraph2D* g_p2 = new TGraph2D(x2.size(),x2.data(),y2.data(),z2.data());

    TGraph2D* g_p3= new TGraph2D(x3.size(),x3.data(),y3.data(),z3.data());
    */
    TGraph* g_p1= new TGraph(x1.size(),x1.data(),y1.data());

    TGraph* g_p2 = new TGraph(x2.size(),x2.data(),y2.data());

    TGraph* g_p3= new TGraph(x3.size(),x3.data(),y3.data());
    TCanvas* canTOT = new TCanvas("total","orbits",1200,800);
    canTOT->cd();
    g_p3->SetTitle("Two Bodies system;x[m];y[m]");
    g_p3->Draw("AP");		//draw the bigger orbit first! need to find a way to do this automatically...
    g_p2->Draw("same");
    g_p1->Draw("same");
}
