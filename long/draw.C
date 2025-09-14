#include <TChain.h>
#include <TCanvas.h>
#include <TGraph2D.h>
#include <TGraph.h>
#include <TF1.h>
#include <TFitResultPtr.h>

void draw(){
    int start = 16;
    int stop = 20;
    TChain *fch;
    fch = new TChain("tree", "tree");
    for (int i= start; i<=stop; i++)
    {
        TString fileName = TString::Format("/home/long/data/25e04/10Be/hit/run%02d_hit.root" , i);
        fch->AddFile(fileName.Data());
    }

    double a = 20.;
    double b = -0.0107;

    double min = 180.;
    double max = 220.;
    double avg = (min+max)/2.;
    double avg_diff = avg-min;

    // TString name = TString::Format("(TMath::Sqrt(Rxc[0]*Rea[0]+%f*Rxc[0]*Rxc[0])+%f*Rea[0]):Rea[0]>>(1000,0,8000,1000,0.,400.)",a,b);
    // TString name = TString::Format("(TMath::Sqrt(Rxc[0]*Rea[0]+%f*Rxc[0]*Rxc[0])+%f*Rea[0])>>(500,%f,%f)",a,b,min,max);
    TString name = "Rxc[0]:Rea[0]:Rxc[0]>>(1000,0,8000,1000,0.,70.)";
    // TString name = "Rxc[0]:Rea[0]>>(1000,0,8000,1000,0.,70.)";

    min = 185.;
    max = 194.;
    avg = (min+max)/2.;
    avg_diff = avg-min;

    TString draw_condition = "Rxa_n[0]>=0 && Rxa_n[0]<=3 && Rya_n[0]>=12 && Rya_n[0]<=15";

    draw_condition = draw_condition + Form("&& TMath::Abs(TMath::Sqrt(Rxc[0]*Rea[0]+(%f)*Rxc[0]*Rxc[0])+(%.5f)*Rea[0] - %f) < %f", a, b, avg, avg_diff);
    draw_condition = draw_condition + "&& af3>1500. && af3<3000. && ToF>170. && ToF<220.";
    draw_condition = draw_condition + "&& xbt*xbt+ybt*ybt<100.";
    // draw_condition = draw_condition + "&& Rea[0]==0";
    // std::cout << "c_number: " << c_number << "\n";
    
    TCanvas* c1 = new TCanvas("c1","c1");
    c1->cd();
    // fch->Draw(name.Data(),draw_condition.Data(),"colz");
    Int_t num1=fch->Draw(name.Data(),draw_condition.Data());
    c1->Draw();
    if(num1==0) return;

}