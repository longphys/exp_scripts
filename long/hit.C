#include "TChain.h"
#include "TFile.h"
#include <algorithm>
#include <iostream>

using std::min;
using std::swap;

void hit()
{
    int start = 0;
    // int stop = start;
    int stop = 2;
    TChain *fch;
    fch = new TChain("AnalysisxTree");
    for (int i= start; i<=stop; i++){
    TString fileName = TString::Format("~/data/25e04/10Be/rawdata/run25_%02d.root" , i);
    fch->AddFile(fileName.Data());
    }

    start = 16;
    stop = 21;
    for (int i= start; i<=stop; i++){
    TString fileName = TString::Format("~/data/25e04/10Be/rawdata/run%02d.root" , i);
    fch->AddFile(fileName.Data());
    }

    start = 22;
    stop = 24;
    for (int i= start; i<=stop; i++){
    TString fileName = TString::Format("~/data/25e04/10Be/rawdata/run%02d_00.root" , i);
    fch->AddFile(fileName.Data());
    }

    // Create a new ROOT file
    // TString outFileName = TString::Format("~/data/25e04/10Be/hit/run25_%02d_hit.root", start);
    TString outFileName = "~/data/25e04/10Be/hit/run_16_25_hit.root";
    TFile *outFile = new TFile(outFileName, "recreate");
    TTree *hitTree = new TTree("tree", "tree");

    Int_t n_event = 0;
    // Define hit structure variables
    // Right x_strip silicon
    Double_t Rxa[5] = {0.};      // Raw Amplitude (Top 5)
    Double_t Rxc[5] = {0.};     // Calibrated energy（Top 5）
    Int_t Rxa_n[5] = {-1};        // Corresponding strip number (channel number)

    Int_t Rxa_hits = 0;           // Actual effective hit number

    // Right y_strip silicon
    Double_t Rya[5] = {0.};      // 原始能量（前5大）
    Double_t Ryc[5] = {0.};     // 刻度后能量（前5大）
    Int_t Rya_n[5] = {-1};        // 对应的条号（通道号）

    Int_t Rya_hits = 0;           // 实际有效hit数量

    // Left x_strip silicon
    Double_t Lxa[5] = {0.};      // 原始能量（前5大）
    Double_t Lxc[5] = {0.};     // 刻度后能量（前5大）
    Int_t Lxa_n[5] = {-1};        // 对应的条号（通道号）

    Int_t Lxa_hits = 0;           // 实际有效hit数量

    // Left y_strip silicon
    Double_t Lya[5] = {0.};      // 原始能量（前5大）
    Double_t Lyc[5] = {0.};     // 刻度后能量（前5大）
    Int_t Lya_n[5] = {-1};        // 对应的条号（通道号）

    Int_t Lya_hits = 0;           // 实际有效hit数量

    // Right scintillator crystals
    Double_t Rea[5] = {0};      // 原始能量（前5大
    Int_t Rea_n[5] = {-1};        // 对应的条号（通道号）
    Double_t Rea_e = 0.;          // 大硅d2信号能量

    Int_t Rea_hits = 0;           // 实际有效hit数量

    // Left scintillator crystals
    Double_t Lea[5] = {0};      // 原始能量（前5大
    Int_t Lea_n[5] = {-1};        // 对应的条号（通道号）

    Int_t Lea_hits = 0;           // 实际有效hit数量

    // TOF
    Double_t ToF = 0.;
    Double_t af3 = 0.;
    Double_t af5 = 0.;

    // Beam profile
    Double_t xbt = 0.;
    Double_t ybt = 0.;
    Double_t xbd = 0.;
    Double_t ybd = 0.;

    // Create branches
    hitTree->Branch("n_event", &n_event, "n_events/D");

    // Right x_strip silicon
    hitTree->Branch("Rxa", Rxa, "Rxa[5]/D");
    hitTree->Branch("Rxc", Rxc, "Rxc[5]/D");
    hitTree->Branch("Rxa_n", Rxa_n, "Rxa_n[5]/I");
    hitTree->Branch("Rxa_hits", &Rxa_hits, "Rxa_hits/I");

    // Right y_strip silicon
    hitTree->Branch("Rya", Rya, "Rya[5]/D");
    hitTree->Branch("Ryc", Ryc, "Ryc[5]/D");
    hitTree->Branch("Rya_n", Rya_n, "Rya_n[5]/I");
    hitTree->Branch("Rya_hits", &Rya_hits, "Rya_hits/I");

    // Left x_strip silicon
    hitTree->Branch("Lxa", Lxa, "Lxa[5]/D");
    hitTree->Branch("Lxc", Lxc, "Lxc[5]/D");
    hitTree->Branch("Lxa_n", Lxa_n, "Lxa_n[5]/I");
    hitTree->Branch("Lxa_hits", &Lxa_hits, "Lxa_hits/I");

    // Left y_strip silicon
    hitTree->Branch("Lya", Lya, "Lya[5]/D");
    hitTree->Branch("Lyc", Lyc, "Lyc[5]/D");
    hitTree->Branch("Lya_n", Lya_n, "Lya_n[5]/I");
    hitTree->Branch("Lya_hits", &Lya_hits, "Lya_hits/I");

    // Right scintillator crystals
    hitTree->Branch("Rea", Rea, "Rea[5]/D");
    hitTree->Branch("Rea_n", Rea_n, "Rea_n[5]/I");
    hitTree->Branch("Rea_hits", &Rea_hits, "Rea_hits/I");

    // Left scintillator crystals
    hitTree->Branch("Lea", Lea, "Lea[5]/D");
    hitTree->Branch("Lea_n", Lea_n, "Lea_n[5]/I");
    hitTree->Branch("Lea_hits", &Lea_hits, "Lea_hits/I");

    // ToF
    hitTree->Branch("ToF", &ToF, "ToF/D");
    hitTree->Branch("af3", &af3, "af3/D");
    hitTree->Branch("af5", &af5, "af5/D");

    // Beam profile
    hitTree->Branch("xbt", &xbt, "xbt/D");
    hitTree->Branch("ybt", &ybt, "ybt/D");
    hitTree->Branch("xbd", &xbd, "xbd/D");
    hitTree->Branch("ybd", &ybd, "ybd/D");
    
    //Telescopes
    //Silicons
    UShort_t        NeEvent_Rxa[16];
    Double_t        NeEvent_Rxc[16];

    UShort_t        NeEvent_Rya[16];
    Double_t        NeEvent_Ryc[16];

    UShort_t        NeEvent_Lxa[32];
    Double_t        NeEvent_Lxc[32];

    UShort_t        NeEvent_Lya[32];
    Double_t        NeEvent_Lyc[32];
    //Scintillators
    UShort_t        NeEvent_Rea[16];
    UShort_t        NeEvent_Lea[16];

    //ToF
    Double_t        NeEvent_af3;
    Double_t        NeEvent_af5;
    Double_t        NeEvent_ToF;

    //Beam profile
    Double_t        NeEvent_xbt;
    Double_t        NeEvent_ybt;
    Double_t        NeEvent_xbd;
    Double_t        NeEvent_ybd;

    //Link the branches to address in the TChain
    //fch->GetListOfBranches()->Print();
    fch->SetBranchAddress("NeEvent.Rxa[16]", NeEvent_Rxa);
    fch->SetBranchAddress("NeEvent.Rxc[16]", NeEvent_Rxc);

    fch->SetBranchAddress("NeEvent.Rya[16]", NeEvent_Rya);
    fch->SetBranchAddress("NeEvent.Ryc[16]", NeEvent_Ryc);

    fch->SetBranchAddress("NeEvent.Lxa[32]", NeEvent_Lxa);
    fch->SetBranchAddress("NeEvent.Lxc[32]", NeEvent_Lxc);

    fch->SetBranchAddress("NeEvent.Lya[32]", NeEvent_Lya);
    fch->SetBranchAddress("NeEvent.Lyc[32]", NeEvent_Lyc);

    fch->SetBranchAddress("NeEvent.Rea[16]", NeEvent_Rea);
    fch->SetBranchAddress("NeEvent.Lea[16]", NeEvent_Lea);

    fch->SetBranchAddress("NeEvent.af3", &NeEvent_af3);
    fch->SetBranchAddress("NeEvent.af5", &NeEvent_af5);
    fch->SetBranchAddress("NeEvent.ToF", &NeEvent_ToF);

    fch->SetBranchAddress("NeEvent.xbt", &NeEvent_xbt);
    fch->SetBranchAddress("NeEvent.ybt", &NeEvent_ybt);
    fch->SetBranchAddress("NeEvent.xbd", &NeEvent_xbd);
    fch->SetBranchAddress("NeEvent.ybd", &NeEvent_ybd);

    Long64_t entries = fch->GetEntries();
    // Long64_t entries = 20000000;
    // std::cout << "number of entries: " << entries << "\n";

    for (Long64_t entry=0; entry<entries; entry++)
    {
        fch->GetEntry(entry);

        if(entry%1000000==0)
        // std::cout<< "Entry: " << entry <<"\n";
        
        /********hit 结构 35°**************/
        // 重置hit计数器
        Rxa_hits = 0;
        Rya_hits = 0;
        Lxa_hits = 0;
        Lya_hits = 0;
        Rea_hits = 0;
        Lea_hits = 0;

        for (int i = 0; i < 5; i++)
        {
            Rxa[i] = 0;
            Rxc[i] = 0;
            Rxa_n[i] = -1;
            
            Rya[i] = 0;
            Ryc[i] = 0;
            Rya_n[i] = -1;
            
            Lxa[i] = 0;
            Lxc[i] = 0;
            Lxa_n[i] = -1;
            
            Lya[i] = 0;
            Lyc[i] = 0;
            Lya_n[i] = -1;

            Rea[i] = {0};
            Rea_n[i] = {-1};
            
            Lea[i] = {0};
            Lea_n[i] = {-1};

        }

        // Temporary number of hits
        Int_t tmp_Rxa_hits = 0;
        Int_t tmp_Rya_hits = 0;
        Int_t tmp_Lxa_hits = 0;
        Int_t tmp_Lya_hits = 0;
        Int_t tmp_Rea_hits = 0;
        Int_t tmp_Lea_hits = 0;

        // 临时存储hit数据
        Double_t tmp_Rxa[16] = {0.};      // 原始能量
        Double_t tmp_Rxc[16] = {0.};     // 刻度后能量
        Int_t tmp_Rxa_n[16] = {-1};        // 通道号

        // 临时存储hit数据
        Double_t tmp_Lxa[32] = {0.};      // 原始能量
        Double_t tmp_Lxc[32] = {0.};     // 刻度后能量
        Int_t tmp_Lxa_n[32] = {-1};        // 通道号

        // 临时存储hit数据
        Double_t tmp_Rya[16] = {0.};      // 原始能量
        Double_t tmp_Ryc[16] = {0.};     // 刻度后能量
        Int_t tmp_Rya_n[16] = {-1};        // 通道号

        // 临时存储hit数据
        Double_t tmp_Lya[32] = {0.};      // 原始能量
        Double_t tmp_Lyc[32] = {0.};     // 刻度后能量
        Int_t tmp_Lya_n[32] = {-1};        // 通道号
        
        // 临时存储hit数据
        Double_t tmp_Rea[16] = {0.};      // 原始能量
        Int_t tmp_Rea_n[16] = {-1};        // 通道号

        // 临时存储hit数据
        Double_t tmp_Lea[16] = {0.};      // 原始能量
        Int_t tmp_Lea_n[16] = {-1};        // 通道号
        
        // 收集所有超过阈值的hit
        for (int ch = 0; ch < 16; ch++) 
        {  // 只处理0-15通道
            // if (chdata2[ch] > pedel[ch]) 
            if (NeEvent_Rxa[ch] > 0.) 
            {
                tmp_Rxa[tmp_Rxa_hits] = NeEvent_Rxa[ch];
                tmp_Rxc[tmp_Rxa_hits] = NeEvent_Rxc[ch];
                tmp_Rxa_n[tmp_Rxa_hits] = ch;
                tmp_Rxa_hits++;
            }
            
            if (NeEvent_Rya[ch] > 0.) 
            {
                tmp_Rya[tmp_Rya_hits] = NeEvent_Rya[ch];
                tmp_Ryc[tmp_Rya_hits] = NeEvent_Ryc[ch];
                tmp_Rya_n[tmp_Rya_hits] = ch;
                tmp_Rya_hits++;
            }
            
            if (NeEvent_Rea[ch] > 5.) 
            {
                tmp_Rea[tmp_Rea_hits] = NeEvent_Rea[ch];
                tmp_Rea_n[tmp_Rea_hits] = ch;
                tmp_Rea_hits++;
            }
            
            if (NeEvent_Lea[ch] > 5.) 
            {
                tmp_Lea[tmp_Lea_hits] = NeEvent_Lea[ch];
                tmp_Lea_n[tmp_Lea_hits] = ch;
                tmp_Lea_hits++;
            }
        }

        for (int ch = 0; ch < 32; ch++) 
        {
            if (NeEvent_Lxa[ch] > 0.) 
            {
                tmp_Lxa[tmp_Lxa_hits] = NeEvent_Lxa[ch];
                tmp_Lxc[tmp_Lxa_hits] = NeEvent_Lxc[ch];
                tmp_Lxa_n[tmp_Lxa_hits] = ch;
                tmp_Lxa_hits++;
            }
            
            if (NeEvent_Lya[ch] > 0.) 
            {
                tmp_Lya[tmp_Lya_hits] = NeEvent_Lya[ch];
                tmp_Lyc[tmp_Lya_hits] = NeEvent_Lyc[ch];
                tmp_Lya_n[tmp_Lya_hits] = ch;
                tmp_Lya_hits++;
            }
        }
        
        // 按能量从大到小排序（选择排序）
        Rxa_hits = tmp_Rxa_hits;
        Rya_hits = tmp_Rya_hits;
        Lxa_hits = tmp_Lxa_hits;
        Lya_hits = tmp_Lya_hits;
        Rea_hits = tmp_Rea_hits;
        Lea_hits = tmp_Lea_hits;

        // std::cout << "SEG FAULT CHECK\n";
        for (int i = 0; i < min(5, Rxa_hits); i++) 
        {
            // 找出当前最大能量的hit
            int max_index = i;
            for (int j = i + 1; j < Rxa_hits; j++) 
            {
                if (tmp_Rxa[j] > tmp_Rxa[max_index]) 
                {
                    max_index = j;
                }
            }
            
            // 保存前5个hit
            Rxa[i] = tmp_Rxa[max_index];
            Rxc[i] = tmp_Rxc[max_index];
            Rxa_n[i] = tmp_Rxa_n[max_index];      
            // 将已选中的hit移到末尾（避免重复选择）
            if (max_index != i) 
            {
                swap(tmp_Rxa[max_index], tmp_Rxa[i]);
                swap(tmp_Rxc[max_index], tmp_Rxc[i]);
                swap(tmp_Rxa_n[max_index], tmp_Rxa_n[i]);
            }
        }
        
        for (int i = 0; i < min(5, Rya_hits); i++) 
        {
            // 找出当前最大能量的hit
            int max_index = i;
            for (int j = i + 1; j < Rya_hits; j++) 
            {
                if (tmp_Rya[j] > tmp_Rya[max_index]) 
                {
                    max_index = j;
                }
            }
            
            // 保存前5个hit
            Rya[i] = tmp_Rya[max_index];
            Ryc[i] = tmp_Ryc[max_index];
            Rya_n[i] = tmp_Rya_n[max_index];      
            // 将已选中的hit移到末尾（避免重复选择）
            if (max_index != i) 
            {
                swap(tmp_Rya[max_index], tmp_Rya[i]);
                swap(tmp_Ryc[max_index], tmp_Ryc[i]);
                swap(tmp_Rya_n[max_index], tmp_Rya_n[i]);
            }
        }

        for (int i = 0; i < min(5, Lxa_hits); i++) 
        {
            // 找出当前最大能量的hit
            int max_index = i;
            for (int j = i + 1; j < Lxa_hits; j++) 
            {
                if (tmp_Lxa[j] > tmp_Lxa[max_index]) 
                {
                    max_index = j;
                }
            }
            
            // 保存前5个hit
            Lxa[i] = tmp_Lxa[max_index];
            Lxc[i] = tmp_Lxc[max_index];
            Lxa_n[i] = tmp_Lxa_n[max_index];      
            // 将已选中的hit移到末尾（避免重复选择）
            if (max_index != i) 
            {
                swap(tmp_Lxa[max_index], tmp_Lxa[i]);
                swap(tmp_Lxc[max_index], tmp_Lxc[i]);
                swap(tmp_Lxa_n[max_index], tmp_Lxa_n[i]);
            }
        }
        
        for (int i = 0; i < min(5, Lya_hits); i++) 
        {
            // 找出当前最大能量的hit
            int max_index = i;
            for (int j = i + 1; j < Lya_hits; j++) 
            {
                if (tmp_Lya[j] > tmp_Lya[max_index]) 
                {
                    max_index = j;
                }
            }
            
            // 保存前5个hit
            Lya[i] = tmp_Lya[max_index];
            Lyc[i] = tmp_Lyc[max_index];
            Lya_n[i] = tmp_Lya_n[max_index];      
            // 将已选中的hit移到末尾（避免重复选择）
            if (max_index != i) 
            {
                swap(tmp_Lya[max_index], tmp_Lya[i]);
                swap(tmp_Lyc[max_index], tmp_Lyc[i]);
                swap(tmp_Lya_n[max_index], tmp_Lya_n[i]);
            }
        }
        
        for (int i = 0; i < min(5, Rea_hits); i++) 
        {
            // 找出当前最大能量的hit
            int max_index = i;
            for (int j = i + 1; j < Rea_hits; j++) 
            {
                if (tmp_Rea[j] > tmp_Rea[max_index]) 
                {
                    max_index = j;
                }
            }
            
            // 保存前5个hit
            Rea[i] = tmp_Rea[max_index];
            Rea_n[i] = tmp_Rea_n[max_index];      
            // 将已选中的hit移到末尾（避免重复选择）
            if (max_index != i) 
            {
                swap(tmp_Rea[max_index], tmp_Rea[i]);
                swap(tmp_Rea_n[max_index], tmp_Rea_n[i]);
            }
        }
        
        for (int i = 0; i < min(5, Lea_hits); i++) 
        {
            // 找出当前最大能量的hit
            int max_index = i;
            for (int j = i + 1; j < Lea_hits; j++) 
            {
                if (tmp_Lea[j] > tmp_Lea[max_index]) 
                {
                    max_index = j;
                }
            }
            
            // 保存前5个hit
            Lea[i] = tmp_Lea[max_index];
            Lea_n[i] = tmp_Lea_n[max_index];      
            // 将已选中的hit移到末尾（避免重复选择）
            if (max_index != i) 
            {
                swap(tmp_Lea[max_index], tmp_Lea[i]);
                swap(tmp_Lea_n[max_index], tmp_Lea_n[i]);
            }
        }

        // if(Rxa[0]>0. && Rea[0]>0. && Rya[0]>0. && Lxa[0]>0. && Lea[0]>0. && Lya[0]>0.)
        // {
        //     std::cout << "Entry: " << entry << "\n";
        //     std::cout << "Rxa[0] = " << Rxa[0] << "; Rxa_n[0] = " << Rxa_n[0] << "\n"
        //     << "Rya[0] = " << Rya[0] << "; Rya_n[0] = " << Rya_n[0] << "\n"
        //     << "Rea[0] = " << Rea[0] << "; Rea_n[0] = " << Rea_n[0] << "\n";   

        //     std::cout << "Rxa_hits = " << Rxa_hits << "; Rya_hits = " << Rya_hits << "; Rea_hits = " << Rea_hits << "\n\n";

        //     std::cout << "Lxa[0] = " << Lxa[0] << "; Lxa_n[0] = " << Lxa_n[0] << "\n"
        //     << "Lya[0] = " << Lya[0] << "; Lya_n[0] = " << Lya_n[0] << "\n"
        //     << "Lea[0] = " << Lea[0] << "; Lea_n[0] = " << Lea_n[0] << "\n";   

        //     std::cout << "Lxa_hits = " << Lxa_hits << "; Lya_hits = " << Lya_hits << "; Lea_hits = " << Lea_hits << "\n\n";
        // }

        //ToF
        af3 = NeEvent_af3;
        af5 = NeEvent_af5;
        ToF = NeEvent_ToF;
        
        //Beam profile
        xbt = NeEvent_xbt;
        ybt = NeEvent_ybt;
        xbd = NeEvent_xbd;
        ybd = NeEvent_ybd;
        
        // 填充树
        hitTree->Fill();
        n_event++;
    }
    // 保存并关闭文件
    hitTree->Write();
    outFile->Write();
    outFile->Close();
}