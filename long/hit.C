#include "TChain.h"
#include "TFile.h"
#include <algorithm>
#include <iostream>

using std::min;
using std::swap;

void hit()
{
    
// Variables to be read from the input tree
// Variables that will be changed/refilled in the loop will have "NeEvent_" prefix)

UShort_t  iSa[16];
UShort_t  iSt[16];
UShort_t  iRa[16];
UShort_t  iRt[16];
UShort_t  iS2a[16];
UShort_t  iS2t[16];
UShort_t  iVa[16];
UShort_t  iVt[16];

// Right silicon
    // amplitude and time branches
UShort_t  NeEvent_Rxa[16];
UShort_t  NeEvent_Rxt[16];
UShort_t  NeEvent_Rya[16];
UShort_t  NeEvent_Ryt[16];
    // energy calibrated branches
Double_t  NeEvent_Rxc[16];
Double_t  NeEvent_Ryc[16];

// Left silicon
UShort_t  NeEvent_Lxa[32];
UShort_t  NeEvent_Lxt[32];
UShort_t  NeEvent_Lya[32];
UShort_t  NeEvent_Lyt[32];
Double_t  NeEvent_Lxc[32];
Double_t  NeEvent_Lyc[32];

// Center telescope
UShort_t  iCxa[16];
UShort_t  iCxt[16];
UShort_t  iCya[16];
UShort_t  iCyt[16];

// Left scintillator: amplitude and time
UShort_t  NeEvent_Lea[16];
UShort_t  NeEvent_Let[16];

// Right scintillator
UShort_t  NeEvent_Rea[16];
UShort_t  NeEvent_Ret[16];

// Focal plane scintillators and MWPC
UShort_t  iFocus3[4];
UShort_t  itF3[4];
UShort_t  iF5[4];
UShort_t  itF5[4];
UShort_t  iF6[4];
UShort_t  itF6[4];
UShort_t  itMWPC[4];
UInt_t    scaler[16];

// ?
UShort_t  nx1;
UShort_t  ny1;
UShort_t  nx2;
UShort_t  ny2;
UShort_t  ix1[32];
UShort_t  iy1[32];
UShort_t  ix2[32];
UShort_t  iy2[32];

// ToF, dE at ToF plastics, and MWPC variables
Double_t  af3;
Double_t  af5;
Double_t  af6;
Double_t  ToF;
Double_t  xbt;
Double_t  ybt;
Double_t  xbd;
Double_t  ybd;

// Variables for MWPC position calculation
Double_t mwx1,mwy1;
Double_t mwx2,mwy2;

// Unused calibrated variables
Double_t  Sc[16];
Double_t  Rc[16];
Double_t  S2c[16];
Double_t  Vc[16];
Double_t  Cxc[16];
Double_t  Cyc[16];
Double_t  Rec[16];
Double_t  Lec[16];

// Event number and trigger number
UInt_t  nevent;
UInt_t  trigger;

TChain *fch = new TChain("AnalysisxTree");

Int_t n_run = 18;
int start = 0;
int stop = 2;
for (int i= start; i<=stop; i++){
    // TString fileName = TString::Format("~/data/25e04/10Be/rawdata/run25_%02d.root" , i);
    TString fileName = TString::Format("~/data/25e04/10Be/rawdata/run%02d.root" , n_run);
    fch->AddFile(fileName.Data());
}

// fch->AddFile("~/data/25e04/run25_00.root");

fch->SetMakeClass(1);
// Set branch addresses for input tree
// Variables that will be changed/refilled in the loop will have "NeEvent_" prefix.
// Variables that remains the same in the loop will not have prefix.
// Unused variables (for now) will have "i" prefix.

fch->SetBranchAddress("NeEvent.Sa[16]",   iSa);
fch->SetBranchAddress("NeEvent.St[16]",   iSt);
fch->SetBranchAddress("NeEvent.Ra[16]",   iRa);
fch->SetBranchAddress("NeEvent.Rt[16]",   iRt);
fch->SetBranchAddress("NeEvent.S2a[16]",  iS2a);
fch->SetBranchAddress("NeEvent.S2t[16]",  iS2t);
fch->SetBranchAddress("NeEvent.Va[16]",   iVa);
fch->SetBranchAddress("NeEvent.Vt[16]",   iVt);

// Right silicon
    // amplitude and time branches
fch->SetBranchAddress("NeEvent.Rxa[16]",  NeEvent_Rxa);
fch->SetBranchAddress("NeEvent.Rxt[16]",  NeEvent_Rxt);
fch->SetBranchAddress("NeEvent.Rya[16]",  NeEvent_Rya);
fch->SetBranchAddress("NeEvent.Ryt[16]",  NeEvent_Ryt);
    // energy calibrated branches
fch->SetBranchAddress("NeEvent.Rxc[16]",  NeEvent_Rxc);
fch->SetBranchAddress("NeEvent.Ryc[16]",  NeEvent_Ryc);

// Left silicon
fch->SetBranchAddress("NeEvent.Lxa[32]",  NeEvent_Lxa);
fch->SetBranchAddress("NeEvent.Lxt[32]",  NeEvent_Lxt);
fch->SetBranchAddress("NeEvent.Lya[32]",  NeEvent_Lya);
fch->SetBranchAddress("NeEvent.Lyt[32]",  NeEvent_Lyt);
fch->SetBranchAddress("NeEvent.Lxc[32]",  NeEvent_Lxc);
fch->SetBranchAddress("NeEvent.Lyc[32]",  NeEvent_Lyc);

// Center telescope
fch->SetBranchAddress("NeEvent.Cxa[16]",  iCxa);
fch->SetBranchAddress("NeEvent.Cxt[16]",  iCxt);
fch->SetBranchAddress("NeEvent.Cya[16]",  iCya);
fch->SetBranchAddress("NeEvent.Cyt[16]",  iCyt);

// Left scintillator: amplitude and time
fch->SetBranchAddress("NeEvent.Lea[16]",  NeEvent_Lea);
fch->SetBranchAddress("NeEvent.Let[16]",  NeEvent_Let);

// Right scintillator
fch->SetBranchAddress("NeEvent.Rea[16]",  NeEvent_Rea);
fch->SetBranchAddress("NeEvent.Ret[16]",  NeEvent_Ret);

// Focal plane scintillators and MWPC
fch->SetBranchAddress("NeEvent.Focus3[4]",    iFocus3);
fch->SetBranchAddress("NeEvent.tF3[4]",   itF3);
fch->SetBranchAddress("NeEvent.F5[4]",    iF5);
fch->SetBranchAddress("NeEvent.tF5[4]",   itF5);
fch->SetBranchAddress("NeEvent.F6[4]",    iF6);
fch->SetBranchAddress("NeEvent.tF6[4]",   itF6);
fch->SetBranchAddress("NeEvent.tMWPC[4]",   itMWPC);
fch->SetBranchAddress("NeEvent.scaler[16]", scaler);

// ?
fch->SetBranchAddress("NeEvent.nx1",  &nx1);
fch->SetBranchAddress("NeEvent.ny1",  &ny1);
fch->SetBranchAddress("NeEvent.nx2",  &nx2);
fch->SetBranchAddress("NeEvent.ny2",  &ny2);
fch->SetBranchAddress("NeEvent.x1[32]",  ix1);
fch->SetBranchAddress("NeEvent.y1[32]",  iy1);
fch->SetBranchAddress("NeEvent.x2[32]",  ix2);
fch->SetBranchAddress("NeEvent.y2[32]",  iy2);

// ToF, dE at ToF plastics, and MWPC variables
fch->SetBranchAddress("NeEvent.af3",  &af3);
fch->SetBranchAddress("NeEvent.af5",  &af5);
fch->SetBranchAddress("NeEvent.af6",  &af6);
fch->SetBranchAddress("NeEvent.ToF",  &ToF);
fch->SetBranchAddress("NeEvent.xbt",  &xbt);
fch->SetBranchAddress("NeEvent.ybt",  &ybt);
fch->SetBranchAddress("NeEvent.xbd",  &xbd);
fch->SetBranchAddress("NeEvent.ybd",  &ybd);

// Calibrated variables
fch->SetBranchAddress("NeEvent.Sc[16]",  Sc);
fch->SetBranchAddress("NeEvent.Rc[16]",  Rc);
fch->SetBranchAddress("NeEvent.S2c[16]",  S2c);
fch->SetBranchAddress("NeEvent.Vc[16]",  Vc);
fch->SetBranchAddress("NeEvent.Cxc[16]",  Cxc);
fch->SetBranchAddress("NeEvent.Cyc[16]",  Cyc);
fch->SetBranchAddress("NeEvent.Rec[16]",  Rec);
fch->SetBranchAddress("NeEvent.Lec[16]",  Lec);

// Event number and trigger number
fch->SetBranchAddress("NeEvent.nevent",  &nevent);
fch->SetBranchAddress("NeEvent.trigger",   &trigger);
// Create a new ROOT file
TString outFileName = TString::Format("~/data/25e04/10Be/hit/run%02d_hit.root", n_run);
TFile *outFile = new TFile(outFileName, "recreate");
TTree *hitTree = new TTree("tree", "tree");

// Define hit structure variables
// Right x_strip silicon
Double_t Rxa[5] = {0.};      // Raw Amplitude (Top 5)
Double_t Rxc[5] = {0.};     // Calibrated energy（Top 5）
Double_t Rxt[5] = {0.};     // Time（Sorted by descending energy）
Int_t Rxa_n[5]  = {-1};        // Corresponding strip number (channel number)
Int_t Rxa_hits = 0;           // Actual effective hit number

// Right y_strip silicon
Double_t Rya[5] = {0.};      
Double_t Ryc[5] = {0.};    
Double_t Ryt[5] = {0.};   
Int_t Rya_n[5]  = {-1};     
Int_t Rya_hits = 0;        

// Left x_strip silicon
Double_t Lxa[5] = {0.};    
Double_t Lxc[5] = {0.};   
Double_t Lxt[5] = {0.};   
Int_t Lxa_n[5]  = {-1};     
Int_t Lxa_hits = 0;        

// Left y_strip silicon
Double_t Lya[5] = {0.};   
Double_t Lyc[5] = {0.};  
Double_t Lyt[5] = {0.};    
Int_t Lya_n[5]  = {-1};     
Int_t Lya_hits = 0;        

// Right scintillator crystals
Double_t Rea[5] = {0};    
Double_t Ret[5] = {0};    
Int_t Rea_n[5] = {-1};    
Int_t Rea_hits = 0;         

// Left scintillator crystals
Double_t Lea[5] = {0};   
Double_t Let[5] = {0};  
Int_t Lea_n[5] = {-1};  
Int_t Lea_hits = 0;        

// ToF
hitTree->Branch("ToF",        &ToF,         "ToF/D");
hitTree->Branch("af3",        &af3,         "af3/D");
hitTree->Branch("af5",        &af5,         "af5/D");
hitTree->Branch("af6",        &af6,         "af6/D");

// Beam profile
hitTree->Branch("xbt",        &xbt,         "xbt/D");
hitTree->Branch("ybt",        &ybt,         "ybt/D");
hitTree->Branch("xbd",        &xbd,         "xbd/D");
hitTree->Branch("ybd",        &ybd,         "ybd/D");

// Create branches for output tree
hitTree->Branch("nevent",     &nevent,      "nevent/I");
hitTree->Branch("n_run",      &n_run,       "n_run/I");
hitTree->Branch("trigger",    &trigger,     "trigger/I");

// Right x_strip silicon
hitTree->Branch("Rxa",        Rxa,          "Rxa[5]/D");
hitTree->Branch("Rxc",        Rxc,          "Rxc[5]/D");
hitTree->Branch("Rxt",        Rxt,          "Rxt[5]/D");
hitTree->Branch("Rxa_n",      Rxa_n,        "Rxa_n[5]/I");
hitTree->Branch("Rxa_hits",   &Rxa_hits,    "Rxa_hits/I");

// Right y_strip silicon
hitTree->Branch("Rya",        Rya,          "Rya[5]/D");
hitTree->Branch("Ryc",        Ryc,          "Ryc[5]/D");
hitTree->Branch("Ryt",        Ryt,          "Ryt[5]/D");
hitTree->Branch("Rya_n",      Rya_n,        "Rya_n[5]/I");
hitTree->Branch("Rya_hits",   &Rya_hits,    "Rya_hits/I");

// Left x_strip silicon
hitTree->Branch("Lxa",        Lxa,          "Lxa[5]/D");
hitTree->Branch("Lxc",        Lxc,          "Lxc[5]/D");
hitTree->Branch("Lxt",        Lxt,          "Lxt[5]/D");
hitTree->Branch("Lxa_n",      Lxa_n,        "Lxa_n[5]/I");
hitTree->Branch("Lxa_hits",   &Lxa_hits,    "Lxa_hits/I");

// Left y_strip silicon
hitTree->Branch("Lya",        Lya,          "Lya[5]/D");
hitTree->Branch("Lyc",        Lyc,          "Lyc[5]/D");
hitTree->Branch("Lyt",        Lyt,          "Lyt[5]/D");
hitTree->Branch("Lya_n",      Lya_n,        "Lya_n[5]/I");
hitTree->Branch("Lya_hits",   &Lya_hits,    "Lya_hits/I");

// Right scintillator crystals
hitTree->Branch("Rea",        Rea,          "Rea[5]/D");
hitTree->Branch("Ret",        Ret,          "Ret[5]/D");
hitTree->Branch("Rea_n",      Rea_n,        "Rea_n[5]/I");
hitTree->Branch("Rea_hits",   &Rea_hits,    "Rea_hits/I");

// Left scintillator crystals
hitTree->Branch("Lea",        Lea,          "Lea[5]/D");
hitTree->Branch("Let",        Let,          "Let[5]/D");
hitTree->Branch("Lea_n",      Lea_n,        "Lea_n[5]/I");
hitTree->Branch("Lea_hits",   &Lea_hits,    "Lea_hits/I");

Long64_t entries = fch->GetEntries();
// Long64_t entries = 100000;
std::cout << "number of entries: " << entries << "\n";

for (Long64_t entry=0; entry<entries; entry++)
{
    fch->GetEntry(entry);

    if(entry%100000==0)
    {
        std::cout<< "Entry: " << entry <<"\n";            
    }
    
    // Reset all variables for the new event
    for (int i = 0; i < 5; i++)
    {
        Rxa[i]   = 0.;
        Rxc[i]   = 0.;
        Rxt[i]   = 0.;
        Rxa_n[i] = -1;
        
        Rya[i]   = 0.;
        Ryc[i]   = 0.;
        Ryt[i]   = 0.;
        Rya_n[i] = -1;
        
        Lxa[i]   = 0.;
        Lxc[i]   = 0.;
        Lxt[i]   = 0.;
        Lxa_n[i] = -1;
        
        Lya[i]   = 0.;
        Lyc[i]   = 0.;
        Lyt[i]   = 0.;
        Lya_n[i] = -1;
    
        Rea[i]   = 0.;
        Ret[i]   = 0.;
        Rea_n[i] = -1;
        
        Lea[i]   = 0.;
        Let[i]   = 0.;
        Lea_n[i] = -1;
    }
        
        Rxa_hits = 0;
        Rya_hits = 0;
        Lxa_hits = 0;
        Lya_hits = 0;
        Rea_hits = 0;
        Lea_hits = 0;

    // Reset the temporary variables

    Double_t tmp_Rxa[16] = {0.};      
    Double_t tmp_Rxc[16] = {0.};   
    Double_t tmp_Rxt[16] = {0.};   
    Int_t tmp_Rxa_n[16]  = {-1};      
    Int_t tmp_Rxa_hits = 0; 

    Double_t tmp_Rya[16] = {0.};   
    Double_t tmp_Ryc[16] = {0.};    
    Double_t tmp_Ryt[16] = {0.};   
    Int_t tmp_Rya_n[16]  = {-1};      
    Int_t tmp_Rya_hits = 0; 

    Double_t tmp_Lxa[32] = {0.};     
    Double_t tmp_Lxc[32] = {0.};   
    Double_t tmp_Lxt[32] = {0.};   
    Int_t tmp_Lxa_n[32]  = {-1};    
    Int_t tmp_Lxa_hits = 0;

    Double_t tmp_Lya[32] = {0.};   
    Double_t tmp_Lyc[32] = {0.};    
    Double_t tmp_Lyt[32] = {0.};   
    Int_t tmp_Lya_n[32]  = {-1};      
    Int_t tmp_Lya_hits = 0; 
    
    Double_t tmp_Rea[16] = {0.};   
    Double_t tmp_Ret[16] = {0.};   
    Int_t tmp_Rea_n[16]  = {-1};    
    Int_t tmp_Rea_hits = 0; 

    Double_t tmp_Lea[16] = {0.};   
    Double_t tmp_Let[16] = {0.}; 
    Int_t tmp_Lea_n[16]  = {-1};    
    Int_t tmp_Lea_hits = 0;
    
    for (int ch = 0; ch < 16; ch++) 
    {
        // if (chdata2[ch] > pedel[ch]) 
        if (NeEvent_Rxa[ch] > 100.) 
        {
            tmp_Rxa[tmp_Rxa_hits] = NeEvent_Rxa[ch];
            tmp_Rxc[tmp_Rxa_hits] = NeEvent_Rxc[ch];
            tmp_Rxt[tmp_Rxa_hits] = NeEvent_Rxt[ch];
            tmp_Rxa_n[tmp_Rxa_hits] = ch;
            tmp_Rxa_hits++;
        }
        
        if (NeEvent_Rya[ch] > 100.) 
        {
            tmp_Rya[tmp_Rya_hits] = NeEvent_Rya[ch];
            tmp_Ryc[tmp_Rya_hits] = NeEvent_Ryc[ch];
            tmp_Ryt[tmp_Rya_hits] = NeEvent_Ryt[ch];
            tmp_Rya_n[tmp_Rya_hits] = ch;
            tmp_Rya_hits++;
        }
        
        if (NeEvent_Rea[ch] > 100.) 
        {
            tmp_Rea[tmp_Rea_hits] = NeEvent_Rea[ch];
            tmp_Ret[tmp_Rea_hits] = NeEvent_Ret[ch];
            tmp_Rea_n[tmp_Rea_hits] = ch;
            tmp_Rea_hits++;
        }
        
        if (NeEvent_Lea[ch] > 100.) 
        {
            tmp_Lea[tmp_Lea_hits] = NeEvent_Lea[ch];
            tmp_Let[tmp_Lea_hits] = NeEvent_Let[ch];
            tmp_Lea_n[tmp_Lea_hits] = ch;
            tmp_Lea_hits++;
        }
    }

    for (int ch = 0; ch < 32; ch++) 
    {
        if (NeEvent_Lxa[ch] > 100.) 
        {
            tmp_Lxa[tmp_Lxa_hits] = NeEvent_Lxa[ch];
            tmp_Lxc[tmp_Lxa_hits] = NeEvent_Lxc[ch];
            tmp_Lxt[tmp_Lxa_hits] = NeEvent_Lxt[ch];
            tmp_Lxa_n[tmp_Lxa_hits] = ch;
            tmp_Lxa_hits++;
        }
        
        if (NeEvent_Lya[ch] > 100.) 
        {
            tmp_Lya[tmp_Lya_hits] = NeEvent_Lya[ch];
            tmp_Lyc[tmp_Lya_hits] = NeEvent_Lyc[ch];
            tmp_Lyt[tmp_Lya_hits] = NeEvent_Lyt[ch];
            tmp_Lya_n[tmp_Lya_hits] = ch;
            tmp_Lya_hits++;
        }
    }
    
    Rxa_hits = tmp_Rxa_hits;
    Rya_hits = tmp_Rya_hits;
    Lxa_hits = tmp_Lxa_hits;
    Lya_hits = tmp_Lya_hits;
    Rea_hits = tmp_Rea_hits;
    Lea_hits = tmp_Lea_hits;

    for (int i = 0; i < min(5, Rxa_hits); i++) 
    {
        int max_index = i;
        for (int j = i + 1; j < Rxa_hits; j++) 
        {
            if (tmp_Rxa[j] > tmp_Rxa[max_index]) 
            {
                max_index = j;
            }
        }
        
        Rxa[i] = tmp_Rxa[max_index];
        Rxc[i] = tmp_Rxc[max_index];
        Rxt[i] = tmp_Rxt[max_index];
        Rxa_n[i] = tmp_Rxa_n[max_index];      
        if (max_index != i) 
        {
            swap(tmp_Rxa[max_index], tmp_Rxa[i]);
            swap(tmp_Rxc[max_index], tmp_Rxc[i]);
            swap(tmp_Rxt[max_index], tmp_Rxt[i]);
            swap(tmp_Rxa_n[max_index], tmp_Rxa_n[i]);
        }
    }
    
    for (int i = 0; i < min(5, Rya_hits); i++) 
    {
        int max_index = i;
        for (int j = i + 1; j < Rya_hits; j++) 
        {
            if (tmp_Rya[j] > tmp_Rya[max_index]) 
            {
                max_index = j;
            }
        }
        
        Rya[i] = tmp_Rya[max_index];
        Ryc[i] = tmp_Ryc[max_index];
        Ryt[i] = tmp_Ryt[max_index];
        Rya_n[i] = tmp_Rya_n[max_index];      
        if (max_index != i) 
        {
            swap(tmp_Rya[max_index], tmp_Rya[i]);
            swap(tmp_Ryc[max_index], tmp_Ryc[i]);
            swap(tmp_Ryt[max_index], tmp_Ryt[i]);
            swap(tmp_Rya_n[max_index], tmp_Rya_n[i]);
        }
    }

    for (int i = 0; i < min(5, Lxa_hits); i++) 
    {
        int max_index = i;
        for (int j = i + 1; j < Lxa_hits; j++) 
        {
            if (tmp_Lxa[j] > tmp_Lxa[max_index]) 
            {
                max_index = j;
            }
        }
        
        Lxa[i] = tmp_Lxa[max_index];
        Lxc[i] = tmp_Lxc[max_index];
        Lxt[i] = tmp_Lxt[max_index];
        Lxa_n[i] = tmp_Lxa_n[max_index];      
        if (max_index != i) 
        {
            swap(tmp_Lxa[max_index], tmp_Lxa[i]);
            swap(tmp_Lxc[max_index], tmp_Lxc[i]);
            swap(tmp_Lxt[max_index], tmp_Lxt[i]);
            swap(tmp_Lxa_n[max_index], tmp_Lxa_n[i]);
        }
    }
    
    for (int i = 0; i < min(5, Lya_hits); i++) 
    {
        int max_index = i;
        for (int j = i + 1; j < Lya_hits; j++) 
        {
            if (tmp_Lya[j] > tmp_Lya[max_index]) 
            {
                max_index = j;
            }
        }
        
        Lya[i] = tmp_Lya[max_index];
        Lyc[i] = tmp_Lyc[max_index];
        Lyt[i] = tmp_Lyt[max_index];
        Lya_n[i] = tmp_Lya_n[max_index];      
        if (max_index != i) 
        {
            swap(tmp_Lya[max_index], tmp_Lya[i]);
            swap(tmp_Lyc[max_index], tmp_Lyc[i]);
            swap(tmp_Lyt[max_index], tmp_Lyt[i]);
            swap(tmp_Lya_n[max_index], tmp_Lya_n[i]);
        }
    }
    
    for (int i = 0; i < min(5, Rea_hits); i++) 
    {
        int max_index = i;
        for (int j = i + 1; j < Rea_hits; j++) 
        {
            if (tmp_Rea[j] > tmp_Rea[max_index]) 
            {
                max_index = j;
            }
        }

        Rea[i] = tmp_Rea[max_index];
        Ret[i] = tmp_Ret[max_index];
        Rea_n[i] = tmp_Rea_n[max_index];      
        if (max_index != i) 
        {
            swap(tmp_Rea[max_index], tmp_Rea[i]);
            swap(tmp_Ret[max_index], tmp_Ret[i]);
            swap(tmp_Rea_n[max_index], tmp_Rea_n[i]);
        }
    }
    
    for (int i = 0; i < min(5, Lea_hits); i++) 
    {
        int max_index = i;
        for (int j = i + 1; j < Lea_hits; j++) 
        {
            if (tmp_Lea[j] > tmp_Lea[max_index]) 
            {
                max_index = j;
            }
        }
        
        Lea[i] = tmp_Lea[max_index];
        Let[i] = tmp_Let[max_index];
        Lea_n[i] = tmp_Lea_n[max_index];      
        if (max_index != i) 
        {
            swap(tmp_Lea[max_index], tmp_Lea[i]);
            swap(tmp_Let[max_index], tmp_Let[i]);
            swap(tmp_Lea_n[max_index], tmp_Lea_n[i]);
        }
    }

    hitTree->Fill();
}
hitTree->Write();
outFile->Close();
}