#define _15C 28
#define NUM 100
#define _N 6

#include "TChain.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TGraph2D.h"
#include "TF1.h"
#include "TCutG.h"
#include <iostream>
#include <sstream>
#include <fstream>

void cali_Li6()
{
    Int_t stripnum=1;
    int start = 16;
    int stop = 24;
    TChain *fch;
    fch = new TChain("tree", "tree");
    for (int i= start; i<=stop; i++){
    TString fileName = TString::Format("/home/long/data/25e04/10Be/hit/run%02d_hit.root" , i);
    fch->AddFile(fileName.Data());
    }
    // fch->Print();
    
    TCanvas *c1=new TCanvas("c1","c1");
    Double_t silicon_thickness = 284.; // Microns
    std::string ss;
    Double_t aa, bbb, e, dedx;
    // i=0;
    // Double_t E0=0.,Etem=0.,Esmall=0.,E2=0.,E=0.,dE=0.,x=0.,dx=0.25;
    Double_t E0=0.,Etem=0.,Esmall=0.,E2=0.,E=0.,dE=0.,x=0.,dx=0.5;
    Double_t sep[16][_N][NUM];

    TString  lise_cal;
lise_cal = TString::Format("/home/long/scripts/exp_scripts/lise/6Li_Si.txt");

TGraph *g_1;

std::ifstream in_1(lise_cal.Data());

g_1 = new TGraph;

if(in_1.is_open())
{
    Int_t i = 0; 
    while(!in_1.eof())
    {
        in_1>>aa>>bbb>>e>>dedx>>aa>>bbb>>aa>>bbb>>aa>>bbb>>aa>>bbb>>aa>>bbb;
        
        g_1->SetPoint(i++, e*6,dedx);//6Li.    
    }
}
in_1.close();

c1->cd();
g_1->Draw();
c1->Draw();

Double_t d[_N-1];
Int_t k; //kind  0:Si 1:Al 2:Mylar
Int_t num_ad3=0;
int i;

for(num_ad3=stripnum;num_ad3<stripnum+1;num_ad3++){
    
    std::cout<<"num_ad3="<<num_ad3<<'\n';
            
    d[0]=0.;
    d[1]=0.;
    d[2]=0.;
    d[3]=silicon_thickness;
    d[4]=100000.;
    
    for(i=1;i<(_N-1);i++)
        {
            d[i]=d[i]+d[i-1];
            std::cout << "d[" << i << "]=" << d[i] << "\n";
        }
    for(i=0;i<NUM;i++)   // Start simulation based on NUM events
    {
        if(i%30==0)std::cout<<i<<":"<<NUM<<'\n';
        x=0;

        // First half of events NUM, energy from 0 to 40 MeV
        if(i<=NUM)E0=E=i*200./(Double_t)(NUM);

        for(Int_t j=0;j<_N;j++)sep[num_ad3][j][i]=0;
        sep[num_ad3][_N-1][i]=E0;
        Etem=E0;
        k=0;
        //cout<<" Y1"<<'\n';
        x=0.;
        while(1)
        {
            if((fabs(x-d[0])<=(dx/40.)||(x>=0&&x<d[0]))&&E<=0){sep[num_ad3][0][i]=Etem;Etem=0;break;}
            else if(fabs(x-d[0])<=(dx/40.)&&E>0){if(k!=0){sep[num_ad3][0][i]=E0-E;Etem=E;}k=0;}

            else if((fabs(x-d[1])<=(dx/2.)||(x>d[0]&&x<d[1]))&&E<=0){sep[num_ad3][1][i]=Etem;Etem=0;break;}
            else if(fabs(x-d[1])<=(dx/2.)&&E>0){if(k!=1){sep[num_ad3][1][i]=Etem-E;Etem=E;}k=1;}

            else if((fabs(x-d[2])<=(dx/2.)||(x>d[1]&&x<d[2]))&&E<=0){sep[num_ad3][2][i]=Etem;Etem=0;break;}
            else if(fabs(x-d[2])<=(dx/2.)&&E>0){if(k!=3){sep[num_ad3][2][i]=Etem-E;Etem=E;}k=3;}
            
            else if((fabs(x-d[3])<=(dx/2.)||(x>d[2]&&x<d[3]))&&E<=0){sep[num_ad3][3][i]=Etem;Etem=0;break;}
            else if(fabs(x-d[3])<=(dx/2.)&&E>0){if(k!=2){sep[num_ad3][3][i]=Etem-E;Etem=E;}k=2;}

            else if(((fabs(x-d[4])>(dx/40.)&&x>d[4])&&E<=0)){sep[num_ad3][4][i]=Etem;Etem=0;break;}
            else if(((fabs(x-d[4])>(dx/40.)&&x>d[4])&&E>0)){sep[num_ad3][4][i]=Etem-E;Etem=0;break;}
            else if(fabs(x-d[4])<=(dx/40.)&&E>0){if(k!=0){sep[num_ad3][4][i]=Etem-E;Etem=E;}k=0;}
            
            dE=g_1->Eval(E);
            E=E-dE*dx;
            x=x+dx;
        }
        //     cout<<"Num="<<i<<'\t'<<"E="<<E<<'\t'<<"dE_Si="<<sep[num_ad3][1][i]<<'\t'<<"dE_Mylar="<<sep[num_ad3][3][i]<<'\t'<<"dE_CsI="<<sep[num_ad3][4][i]<<'\n';
    } 

}

TGraph *calpid13_p[16];
for(Int_t i=0;i<16;i++){
        calpid13_p[i]=new TGraph();
        //pid31_2[i][j]=new TGraph();
        //cout<<"i="<<i<<" j="<<j<<'\n';
}

Int_t keypid=1;
Int_t ip=0,i03=0,i23=0,i43=0;
for(Int_t j0=stripnum;j0<stripnum+1;j0++){
    std::cout<<"******************j="<<j0<<"*****************"<<'\n';
        for(Int_t i0=0;i0<NUM;){
            // if(keypid==1&&sep[j0][4][i0]>0)calpid13_p[0]->SetPoint(ip++, sep[j0][3][i0],sep[j0][4][i0]);  
            if(keypid==1&&sep[j0][4][i0]>0)calpid13_p[0]->SetPoint(ip++, sep[j0][4][i0],sep[j0][3][i0]);       
            i0++;
    }
    ip=0;
    i03=0;
    i23=0;
    i43=0;
    keypid=0;
}
c1->Clear();
calpid13_p[0]->SetMarkerStyle(3);
calpid13_p[0]->Draw("ap");
c1->Draw();

gROOT->Macro("/home/long/data/25e04/10Be/hit/test_cut.C");
TCutG *test_cut = (TCutG *)gROOT->GetListOfSpecials()->FindObject("test_cut");

    // c1->Clear();

double a = 20.;
double b = -0.0107;

double min_fit = 180.;
double max_fit = 220.;
double avg = (min_fit+max_fit)/2.;
double avg_diff = avg-min_fit;

// TString name = TString::Format("(TMath::Sqrt(Rxc[0]*Rea[0]+%f*Rxc[0]*Rxc[0])+%f*Rea[0]):Rea[0]>>(1000,0,8000,1000,0.,400.)",a,b);
// TString name = TString::Format("(TMath::Sqrt(Rxc[0]*Rea[0]+%f*Rxc[0]*Rxc[0])+%f*Rea[0])>>(500,%f,%f)",a,b,min_fit,max_fit);
TString name = "Rxc[0]:Rea[0]:Rxc[0]>>(1000,0,8000,1000,0.,70.)";
// TString name = "Rxc[0]:Rea[0]>>(1000,0,8000,1000,0.,70.)";

min_fit = 183.;
max_fit = 193.;
avg = (min_fit+max_fit)/2.;
avg_diff = avg-min_fit;

TString draw_condition = "Rxa_n[0]>=0 && Rxa_n[0]<=3 && Rya_n[0]>=12 && Rya_n[0]<=15";

draw_condition = draw_condition + Form("&& TMath::Abs(TMath::Sqrt(Rxc[0]*Rea[0]+(%f)*Rxc[0]*Rxc[0])+(%.5f)*Rea[0] - %f) < %f", a, b, avg, avg_diff);
draw_condition = draw_condition + "&& af3>1500. && af3<3000. && ToF>170. && ToF<220.";
draw_condition = draw_condition + "&& xbt*xbt+ybt*ybt<100.";
draw_condition = draw_condition + "&& Rea_n[0]==0";
// std::cout << "c_number: " << c_number << "\n";

// fch->Draw(name.Data(),draw_condition.Data(),"colz");
Int_t num1=fch->Draw(name.Data(),draw_condition.Data());
c1->Draw();
if(num1==0) return;

TGraph2D *e1=new TGraph2D(num1,fch->GetV3(),fch->GetV2(),fch->GetV1());
Int_t npoints1=e1->GetN();

name = "Rxc[0]:Rea[0]>>(1000,0,8000,1000,0.,70.)";

draw_condition = "Rxa_n[0]>=0 && Rxa_n[0]<=3 && Rya_n[0]>=12 && Rya_n[0]<=15";
// draw_condition = draw_condition + Form("&& TMath::Abs(TMath::Sqrt(Rxc[0]*Rea[0]+(%f)*Rxc[0]*Rxc[0])+(%.5f)*Rea[0] - %f) < %f", a, b, avg, avg_diff);
draw_condition = draw_condition + "&& TMath::Abs(TMath::Sqrt(Rxc[0]*Rea[0]+(20.)*Rxc[0]*Rxc[0])+(-0.0107)*Rea[0] - 188) < 5";
draw_condition = draw_condition + "&& af3>1500. && af3<3000. && ToF>170. && ToF<220.";
draw_condition = draw_condition + "&& xbt*xbt+ybt*ybt<100.";
draw_condition = draw_condition + "&& test_cut";

num1=fch->Draw(name.Data(),draw_condition.Data(), "colz");
c1->Draw();
}