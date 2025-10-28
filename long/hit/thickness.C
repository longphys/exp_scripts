void thickness()
{
    // TFile* f = new TFile("/home/long/data/25e04/12Be/hit/12Be09.root", "read");
    // TTree* t = (TTree*)f->Get("tree");
    
    TChain* ch_1 = new TChain("tree");

    ch_1->AddFile("/home/long/data/25e04/12Be/hit/12Be09.root");
    ch_1->AddFile("/home/long/data/25e04/12Be/hit/12Be10.root");

    Int_t n_run = 0;
    Int_t n_event = 0;

    Double_t Rxa[5];      // Raw Amplitude (Top 5)
    Double_t Rxc[5];     // Calibrated energy（Top 5）
    Int_t Rxa_n[5];        // Corresponding strip number (channel number)
    Int_t Rxa_hits;           // Actual effective hit number

    // Right y_strip silicon
    Double_t Rya[5];    
    Double_t Ryc[5];   
    Int_t Rya_n[5];     
    Int_t Rya_hits;        

    // Left x_strip silicon
    Double_t Lxa[5];    
    Double_t Lxc[5];    
    Int_t Lxa_n[5];     
    Int_t Lxa_hits;        

    // Left y_strip silicon
    Double_t Lya[5];
    Double_t Lyc[5];  
    Int_t Lya_n[5];    
    Int_t Lya_hits;       

    // Right scintillator crystals
    Double_t Rea[5];   
    Int_t Rea_n[5];      
    Int_t Rea_hits;

    // Left scintillator crystals
    Double_t Lea[5];
    Int_t Lea_n[5]; 
    Int_t Lea_hits;           

    // TOF
    Double_t ToF;
    Double_t af3;
    Double_t af5;

    // Beam profile
    Double_t xbt;
    Double_t ybt;
    Double_t xbd;
    Double_t ybd;

    ch_1->SetBranchAddress("n_run", &n_run);
    ch_1->SetBranchAddress("Rxa", Rxa);
    ch_1->SetBranchAddress("Rxc", Rxc);
    ch_1->SetBranchAddress("Rxa_n", Rxa_n);
    ch_1->SetBranchAddress("Rxa_hits", &Rxa_hits);
    ch_1->SetBranchAddress("Rya", Rya);
    ch_1->SetBranchAddress("Ryc", Ryc);
    ch_1->SetBranchAddress("Rya_n", Rya_n);
    ch_1->SetBranchAddress("Rya_hits", &Rya_hits);
    ch_1->SetBranchAddress("Lxa", Lxa);
    ch_1->SetBranchAddress("Lxc", Lxc);
    ch_1->SetBranchAddress("Lxa_n", Lxa_n);
    ch_1->SetBranchAddress("Lxa_hits", &Lxa_hits);
    ch_1->SetBranchAddress("Lya", Lya);
    ch_1->SetBranchAddress("Lyc", Lyc);
    ch_1->SetBranchAddress("Lya_n", Lya_n);
    ch_1->SetBranchAddress("Lya_hits", &Lya_hits);
    ch_1->SetBranchAddress("Rea", Rea);
    ch_1->SetBranchAddress("Rea_n", Rea_n);
    ch_1->SetBranchAddress("Rea_hits", &Rea_hits);
    ch_1->SetBranchAddress("Lea", Lea);
    ch_1->SetBranchAddress("Lea_n", Lea_n);
    ch_1->SetBranchAddress("Lea_hits", &Lea_hits);
    ch_1->SetBranchAddress("ToF", &ToF);
    ch_1->SetBranchAddress("af3", &af3);
    ch_1->SetBranchAddress("af5", &af5);

    gROOT->Macro("~/scripts/exp_scripts/long/hit/12Be_8.C");
    gROOT->Macro("~/scripts/exp_scripts/long/hit/12Be_4.C");

    TH1D* h_1 = new TH1D("h_1", "h_1", 200,-5,5);
    TH1D* h_2 = new TH1D("h_2", "h_2", 200,-5,5);
    h_1->SetTitle("Difference of energy deposit between calculation and measured;E_cal - E_mea(MeV);Counts");
    h_2->SetTitle("Difference of energy deposit between calculation and measured;E_cal - E_mea(MeV);Counts");
    // t->Draw("Rxc[0]:Rea[0]>>(1000,0,7500,1000,1000,0,50)","ToF>150 && ToF<170 && af5>1000 && af5<2000 && Rxa_n[0]>=0 && Rxa_n[0]<=3 && Rya_n[0]>=4 && Rya_n[0]<=7 && Rea_n[0]==8 && xbt*xbt+ybt*ybt<80","colz");
    // TCanvas* c_1 = new TCanvas("c_1", "c_1", 1200,800);
    // ch_1->Draw("tBeamC-tBeamS[5]-Rxc[0]>>h_1","ToF>150 && ToF<170 && af5>1000 && af5<2000 && Rxa_n[0]>=0 && Rxa_n[0]<=3 && Rya_n[0]>=4 && Rya_n[0]<=7 && xbt*xbt+ybt*ybt<80 12Be_8","colz");
    // t->Draw("Rxc[0]:Rea[0]>>(1000,0,7500,1000,0,50)","ToF>150 && ToF<170 && af5>1000 && af5<2000 && Rxa_n[0]>=0 && Rxa_n[0]<=3 && Rya_n[0]>=4 && Rya_n[0]<=7 && Rea_n[0]==8 && xbt*xbt+ybt*ybt<80 && tBeamC-tBeamS[5]-Rxc[0]<-1 && 12Be_8","colz");

    TCanvas* c_2 = new TCanvas("c_1", "c_1", 1700,800);
    c_2->Divide(2,1);
    // ch_1->Draw("Rxc[0]:Rea[0]>>(1000,0,7500,1000,1000,0,50)","ToF>150 && ToF<170 && af5>1000 && af5<2000 && Rxa_n[0]>=0 && Rxa_n[0]<=3 && Rya_n[0]>=8 && Rya_n[0]<=11 && xbt*xbt+ybt*ybt<80","colz");
    
    c_2->cd(1);
    ch_1->Draw("tBeamC-tBeamS[5]-Rxc[0]>>h_2","ToF>150 && ToF<170 && af5>1000 && af5<2000 && Rxa_n[0]>=0 && Rxa_n[0]<=3 && Rya_n[0]>=8 && Rya_n[0]<=11 && 12Be_4 && xbt*xbt+ybt*ybt<80","colz");
    h_2->SetStats(0);
    c_2->cd(2);
    ch_1->Draw("tBeamC-tBeamS[4]-Rxc[0]>>h_1","ToF>150 && ToF<170 && af5>1000 && af5<2000 && Rxa_n[0]>=0 && Rxa_n[0]<=3 && Rya_n[0]>=4 && Rya_n[0]<=7 && xbt*xbt+ybt*ybt<80 && 12Be_8","colz");
    h_1->SetStats(0);
}