#define _15C 28
#define NUM 100
#define _N 6

#include "TChain.h"
#include "TCanvas.h"
#include "TGraph.h"
#include <iostream>
#include <fstream>
#include <sstream>

void cali_Li6()
{
    Int_t stripnum=1;
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

    Double_t xxs,ad3_thick[16];
    Double_t silicon_thickness = 300.; // Microns

    std::string ss;
    Double_t aa, bbb, e, dedx;
    // i=0;
    Double_t E0=0.,Etem=0.,Esmall=0.,E2=0.,E=0.,dE=0.,x=0.,dx=0.25;
    // Double_t E0=0.,Etem=0.,Esmall=0.,E2=0.,E=0.,dE=0.,x=0.,dx=1000.0;
    //E0为能量总值，E为能量实时记录值，E1为穿透第一块硅时的能量，E2为穿透第二块时的能量
    Double_t sep[16][_N][NUM];
    
    // TString  str_1H[4];
    TString  str_f_d;
    // str_1H[0]=TString::Format("/home/zhuhy/JNBook/15C_Etheta/TAT0_datacheck/PID/txt/4He-Si.txt");
    str_f_d = TString::Format("/home/long/scripts/exp_scripts/lise/6Li_Si.txt");

    // TGraph *g_1H[4];
    TGraph *g_1;

    // ifstream in_1H(str_1H[0].Data());
    std::ifstream in_1(str_f_d.Data());

    // g_1H[0]=new TGraph;//定义新的二维散点图(TGraph) g1
    g_1 = new TGraph;

    if(in_1.is_open())
    {//检查文件是否存在
        //    getline(in,ss);
        Int_t i = 0; 
        while(!in_1.eof())
        {
            in_1>>aa>>bbb>>e>>dedx>>aa>>bbb>>aa>>bbb>>aa>>bbb>>aa>>bbb>>aa>>bbb;
            // 对照数据文件进行理解。一列一列地读入，提取第3、4列数据。
            g_1->SetPoint(i++, e*4,dedx);//添加数据点到图中，能量单位为MeV/u，对C需乘以12.    
        }
    }
    in_1.close();

    c1->cd();
    g_1->Draw();
    c1->Draw();

    Double_t d[_N-1];
    Int_t k; //kind  0:Si 1:Al 2:Mylar
    Int_t num_CsI=0;
    int i;

    for(num_CsI=stripnum; num_CsI<stripnum+1; num_CsI++){
        
        std::cout<<"num_CsI="<<num_CsI<<'\n';
        //cout<<ad3_thick[num_CsI]<<" : "<<ad4_thick[num_ad4]<<'\n';
        
        // d[0]=0.5*ad3_thick[num_CsI]/150.;
        // d[1]=ad3_thick[num_CsI];
        // d[2]=0.8*ad3_thick[num_CsI]/150.;
        // d[3]=2*ad3_thick[num_CsI]/150.;
        // d[4]=80000;
        
        d[0]=300.;
        d[1]=300.;
        d[2]=300.;
        d[3]=300.;
        d[4]=300.;

        for(i=1; i<(_N-1); i++)d[i]=d[i]+d[i-1];
        for(i=-1; i<NUM; i++)   // Start simulation based on NUM events
        {
            if(i%30==0)
            {
                std::cout<<i<<":"<<NUM<<'\n';
            }
            x=0.;

            //Esmall=rand()%1000;  //初始能量小数部分

            // First half of events NUM, energy from 0 to 40 MeV
            if(i<NUM/2)E0=E=i*40./(Double_t)(NUM);
            // Second half of events NUM, energy from 20 to 320 MeV
            else E0=E=20.+(i-(Double_t)(NUM)/2)*300./(Double_t)(NUM);
            
            //+Esmall/1000;  
            //E0=E=+Esmall/1000;  //能量随机值为300+3位小数
            
            for(Int_t j=0;j<_N;j++)
            {
                sep[num_CsI][j][i]=0;
            }
            sep[num_CsI][_N-1][i]=E0;
            Etem=E0;
            k=1;
            //cout<<" Y1"<<'\n';

            while(1)
            {
                if((fabs(x-d[0])<=(dx/40.)||(x>=0&&x<d[0]))&&E<=0){sep[num_CsI][0][i]=Etem;Etem=0;break;}
                else if(fabs(x-d[0])<=(dx/40.)&&E>0){if(k!=0){sep[num_CsI][0][i]=E0-E;Etem=E;}k=0;}
                
                else if((fabs(x-d[1])<=(dx/2.)||(x>d[0]&&x<d[1]))&&E<=0){sep[num_CsI][1][i]=Etem;Etem=0;break;}
                else if(fabs(x-d[1])<=(dx/2.)&&E>0){if(k!=1){sep[num_CsI][1][i]=Etem-E;Etem=E;}k=1;}
                
                else if((fabs(x-d[2])<=(dx/2.)||(x>d[1]&&x<d[2]))&&E<=0){sep[num_CsI][2][i]=Etem;Etem=0;break;}
                else if(fabs(x-d[2])<=(dx/2.)&&E>0){if(k!=3){sep[num_CsI][2][i]=Etem-E;Etem=E;}k=3;}
                
                else if((fabs(x-d[3])<=(dx/2.)||(x>d[2]&&x<d[3]))&&E<=0){sep[num_CsI][3][i]=Etem;Etem=0;break;}
                else if(fabs(x-d[3])<=(dx/2.)&&E>0){if(k!=2){sep[num_CsI][3][i]=Etem-E;Etem=E;}k=2;}
                
                else if(((fabs(x-d[4])>(dx/40.)&&x>d[4])&&E<=0)){sep[num_CsI][4][i]=Etem;Etem=0;break;}
                else if(((fabs(x-d[4])>(dx/40.)&&x>d[4])&&E>0)){sep[num_CsI][4][i]=Etem-E;Etem=0;break;}
                else if(fabs(x-d[4])<=(dx/40.)&&E>0){if(k!=0){sep[num_CsI][4][i]=Etem-E;Etem=E;}k=0;}
                
                dE=g_1->Eval(E);
                if(k==0&&k==2)
                {
                    E=E-dE*dx;
                    x=x+dx;
                }
                else 
                {
                    E=E-dE*dx/20.;
                    x=x+dx/20.;
                }
            }
            //     cout<<"Num="<<i<<'\t'<<"E="<<E<<'\t'<<"dE_Si="<<sep[num_CsI][1][i]<<'\t'<<"dE_Mylar="<<sep[num_CsI][3][i]<<'\t'<<"dE_CsI="<<sep[num_CsI][4][i]<<'\n';
        } 

    }

    TGraph *calpid13_p[16];
    for(Int_t i=0;i<16;i++)
    {
        calpid13_p[i]=new TGraph();
        //pid31_2[i][j]=new TGraph();
        //cout<<"i="<<i<<" j="<<j<<'\n';
    }

    Int_t keypid=1;
    Int_t ip=0,i03=0,i23=0,i43=0;
        for(Int_t j0=stripnum;j0<stripnum+1;j0++)
        {
            std::cout<<"******************j="<<j0<<"*****************"<<'\n';
                for(Int_t i0=0;i0<NUM;)
                {
                    if(keypid==1&&sep[j0][4][i0]>0)calpid13_p[0]->SetPoint(ip++, sep[j0][1][i0],sep[j0][4][i0]);        
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
}