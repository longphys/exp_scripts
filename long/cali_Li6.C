#define _15C 28
#define NUM 100

#include "TChain.h"
#include "TCanvas.h"
#include "TGraph.h"
#include <iostream>
#include <fstream>
#include <sstream>

void cali_Li6()
{
    Int_t stripnum = 0;
    int start = 16;
    int stop = 18;
    TChain *fch;
    fch = new TChain("tree", "tree");
    for (int i= start; i<=stop; i++){
        TString fileName = TString::Format("/home/long/data/25e04/10Be/hit/run%02d_hit.root" , i);
        fch->AddFile(fileName.Data());
    }
    // fch->Print();

    TCanvas *c1=new TCanvas("c1","c1");

    //! Add material
    // Double_t silicon_thickness = 300.; // Microns
    // Double_t CsI_thickness = 100000.; // Microns
    Double_t silicon_thickness = 300.; // Microns
    Double_t CsI_thickness = 100000.; // Microns
    std::vector<Double_t> thickness;
    thickness.push_back(silicon_thickness); // 1. Si
    thickness.push_back(CsI_thickness); // 2. CsI
    // std::cout << "Number of layers: " << thickness.size() << "\n";

    const int n_layers = 2;
    //!


    std::string ss;
    Double_t aa, bbb, e, dedx;
    // i=0;
    Double_t E0=0.,Etem=0.,Esmall=0.,E2=0.,E=0.,dE=0.,x=0.,dx=0.25;
    // E0 is the total energy value, E is the real-time recorded energy value, 
    // E1 is the energy when penetrating the first piece of silicon
    // E2 is the energy when penetrating the second piece.

    Double_t sep[16][n_layers][NUM];
    
    TString  str_f_d;
    str_f_d = TString::Format("/home/long/scripts/exp_scripts/lise/6Li_Si.txt");

    TGraph *g_1 = new TGraph();

    std::ifstream in_1(str_f_d.Data());

    if(in_1.is_open())
    {
        //    getline(in,ss);
        Int_t i = 0; 
        // while(in_1>>aa>>bbb>>/*3*/e>>/*4*/dedx>>aa>>bbb>>aa>>bbb>>aa>>bbb>>aa>>bbb>>aa>>bbb)
        while(in_1>>aa>>bbb>>/*3*/e>>/*4*/dedx>>aa>>bbb>>aa>>bbb>>aa>>bbb>>aa>>bbb>>aa>>bbb)
        {
            // Extract the data in columns 3 and 4.
            std::cout << "e:" << e << "\n";
            std::cout << "dedx:" << dedx << "\n";
            g_1->SetPoint(i++, e*6, dedx);// Energy units are MeV/u. For 6Li, multiply by 6    
        }
    }
    in_1.close();

    c1->cd();
    g_1->Draw();
    c1->Draw();

    // Double_t x_start[n_layers];
    // Double_t x_end[n_layers];
    // Int_t num_CsI=0;
    // int i;

    // // for(num_CsI=0; num_CsI < stripnum; num_CsI++)
    // for(num_CsI=stripnum; num_CsI < stripnum+1; num_CsI++)
    // {       
    //     std::cout<<"num_CsI="<<num_CsI<<'\n';

    //     for(i=0; i < n_layers; i++)
    //     {
    //         if(i==0)
    //         // If layer == 0 (the first layer), then x_start = 0
    //         {
    //             x_start[i] = 0;
    //             x_end[i]   = thickness[i];
    //         }
    //         else 
    //         {
    //             x_start[i] = x_end[i-1]; // Start of this layer is the end of the previous layer
    //             x_end[i]   = x_start[i] + thickness[i];
    //         }
    //     }

    //     for(i=0; i<NUM; i++)   // Start simulation based on NUM events
    //     {
    //         // if(i%20==0)
    //         {
    //             std::cout<< "############ Event: " << i <<"/"<<NUM<<'\n';
    //         }
            
    //         x=0.; // Reset the depth position of the particle

    //         // Reset the energy loss in each layer
    //         for(Int_t j=0; j < n_layers; j++)
    //         {
    //             sep[num_CsI][j][i]=0;
    //         }

    //         // E0=E=i*80./(Double_t)(NUM);
    //         if(i<NUM/2)E0=E=i*40./(Double_t)(NUM);
    //         // Second half of events NUM, energy from 20 to 320 MeV
    //         else E0=E=20.+(i-(Double_t)(NUM)/2)*300./(Double_t)(NUM);
            
    //         Etem=E0; // Reset the temporary energy value (to the initial energy value)

    //         while (E > 0 && x < x_end[n_layers-1]) 
    //         {
    //             for (Int_t layer = 0; layer < n_layers; layer++)
    //             {
    //                 if (x >= x_start[layer] && x < x_end[layer]) 
    //                 {
    //                     Double_t dist_to_boundary = x_end[layer] - x;
    //                     Double_t dx_step = std::min(dx, dist_to_boundary);

    //                     // dE/dx from stopping power curve
    //                     Double_t dEdx = g_1->Eval(E);
    //                     Double_t dE_dep = dEdx * dx_step;

    //                     if (dE_dep >= E) { // particle stops inside this step
    //                         sep[num_CsI][layer][i] += E;
    //                         E = 0;
    //                         break; // stop everything
    //                     }

    //                     // deposit this step
    //                     sep[num_CsI][layer][i] += dE_dep;
    //                     E -= dE_dep;
    //                     x += dx_step;

    //                     break; // recheck x in case we move to next layer
    //                 }
    //             }
    //         }

            
    //         for (Int_t layer = 0; layer < n_layers; layer++)
    //         {
    //             std::cout << "Final energy lost in layer: " << layer << " = " << sep[num_CsI][layer][i] << " MeV\n";
    //         }

    //     }
    // }

    // TGraph* g_dEE = new TGraph();

    // for (Int_t i = 0; i < NUM; i++) 
    // {
    //     double dE = sep[0][0][i];  // layer 0 (Si)
    //     double E  = sep[0][1][i];  // layer 1 (CsI)

    //     g_dEE->AddPoint(E, dE);    // x = E (CsI), y = ΔE (Si)
    // }

    // c1->Clear();
    // c1->cd();
    // g_dEE->SetTitle("dE-E plot;E_{CsI} [MeV];dE_{Si} [MeV]");
    // g_dEE->SetMarkerStyle(20);
    // g_dEE->Draw("AP");

    // c1->Draw();

}