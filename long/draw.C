#include <TChain.h>
#include <TCanvas.h>
#include <TGraph2D.h>
#include <TGraph.h>
#include <TF1.h>
#include <TFitResultPtr.h>

void draw(){
    int start = 16;
    int stop = 24;
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

    TGraph2D *e1=new TGraph2D(num1,fch->GetV3(),fch->GetV2(),fch->GetV1());
    Int_t npoints1=e1->GetN();

    TGraph *tempresult[3][10];
    for(Int_t I=0;I<3;I++){ for(Int_t J=0;J<10;J++)tempresult[I][J]= new TGraph;}
    TGraph *evalcheck=new TGraph();
    TGraph *result[3];
    for(Int_t I=0;I<3;I++) result[I]= new TGraph();
    TGraph *indeedpid[3];
    for(Int_t I=0;I<3;I++) indeedpid[I]= new TGraph();
    Double_t kk[3][10],bb[3][10];
    Double_t *gex=e1->GetY();
    Double_t *gey=e1->GetZ();

    Int_t J=0;
    for(Int_t i=0;i<npoints1;i++)
    {
        //if(ey[I]>20&&ex[I]>=800&&ex[I]<2000){tempresult[1]->SetPoint(J,ex[I],pid->Eval(ey[I]));J++;}
        if(gey[i]>0.3&&gex[i]>=500&&gex[i]<30000){tempresult[0][1]->SetPoint(J,calpid13_p[0]->Eval(gey[i]),gex[i]);J++;}
        //tempresult[1]->SetPoint(J,pid->Eval(gey[i]),gex[i]);J++;
    }

    tempresult[0][1]->Draw("ap");
    c1->Draw();
    TF1 *f3 = new TF1("f3","[1]*x+[0]",1,100);
    f3->SetParameter(0,200);
    f3->SetParameter(1,0);
    f3->SetParLimits(1,50,500);
    TFitResultPtr r1 = tempresult[0][1]->Fit("f3","QS+rob=0.9");
    kk[0][1]=r1->Value(1);
    bb[0][1]=r1->Value(0);
    std::cout<<"N="<<npoints1<<'\n';
    std::cout<<"i="<<J<<" kp="<<kk[0][1]<<" bp="<<bb[0][1]<<'\n'; 
}