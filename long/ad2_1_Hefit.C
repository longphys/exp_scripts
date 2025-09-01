#define _15C 28
#define NUM 500
#define _N 6

#include "TChain.h"
#include "TCanvas.h"
#include "TGraph.h"
#include <iostream>
#include <fstream>
#include <sstream>

void ad2_1_Hefit()
{
    /******************/
    Int_t stripnum=14;
    /******************/

    int start = 420;
    int stop = 530;
    TChain *fch;
    fch = new TChain("tree", "tele");
    for (int i= start; i<=stop; i++){
        TString fileName = TString::Format("/data/d1/zhuhy/lanzhou2022/getdatappac/test3/tele%04d.root" , i);
        fch->AddFile(fileName.Data());
    }
    TCanvas *c1=new TCanvas("c1","c1");
    Double_t xxs,ad3_thick[16];

    char str_thick[100]="/home/zhuhy/JNBook/Experiment2022/taf/csicali/txt/taf_ad0_thickreal.txt";
    std::ifstream in_thick(str_thick);
    if(in_thick.is_open()){
    //    getline(in,ss);
        Int_t i=0; 
        while(i<16)
        {
        in_thick>>xxs>>ad3_thick[i];
        i++;
        }
    }
    in_thick.close();
    for(Int_t ii=0;ii<16;ii++)ad3_thick[ii]=ad3_thick[ii]*141.5/150.;

    std::string ss;
    Double_t aa, bbb, e, dedx;
    // i=0;
    Double_t E0=0,Etem=0,Esmall=0,E2=0,E=0,dE=0,x=0,dx=0.25;
    //E0为能量总值，E为能量实时记录值，E1为穿透第一块硅时的能量，E2为穿透第二块时的能量
    Double_t sep[16][_N][NUM];

    TString  str_1H[4];
    str_1H[0]=TString::Format("/home/long/scripts/exp_scripts/lise/6Li_Si.txt");

    TGraph *g_1H[4];

    std::ifstream in_1H(str_1H[0].Data());

    g_1H[0]=new TGraph;//定义新的二维散点图(TGraph) g1
    if(in_1H.is_open()){//检查文件是否存在
    //    getline(in,ss);
        Int_t i=0; 
        while(!in_1H.eof())
        {
        in_1H>>aa>>bbb>>e>>dedx>>aa>>bbb>>aa>>bbb>>aa>>bbb>>aa>>bbb>>aa>>bbb;
        // 对照数据文件进行理解。一列一列地读入，提取第3、4列数据。
        g_1H[0]->SetPoint(i++, e*4,dedx);//添加数据点到图中，能量单位为MeV/u，对C需乘以12.    
        }
    }
    in_1H.close();


        c1->cd();
        g_1H[0]->Draw();
        c1->Draw();

    Double_t d[_N-1];
    //d[0]=ad3_thick[stripnum];
    //d[1]=1;
    //d[2]=ad3_thick[stripnum];
    Int_t k; //kind  0:Si 1:Al 2:Mylar
    Int_t num_ad3=0;
    Int_t ui;

    for(num_ad3=stripnum;num_ad3<stripnum+1;num_ad3++){
        
    std::cout<<"num_ad3="<<num_ad3<<'\n';
    //cout<<ad3_thick[num_ad3]<<" : "<<ad4_thick[num_ad4]<<'\n';
        
    d[0]=0.;
    d[1]=0.;
    d[2]=0.;
    d[3]=300.;
    d[4]=80000;
    for(int i=1;i<(_N-1);i++)d[i]=d[i]+d[i-1];
    for(int i=-1;i<NUM;i++)   //开始NUM次模拟
    {
    if(i%30==0)std::cout<<i<<":"<<NUM<<'\n';
    x=0;
    //Esmall=rand()%1000;  //初始能量小数部分
    if(i<NUM/2)E0=E=i*40./(Double_t)(NUM);
    else E0=E=20.+(i-(Double_t)(NUM)/2)*300./(Double_t)(NUM);
    //+Esmall/1000;  
    //E0=E=+Esmall/1000;  //能量随机值为300+3位小数
    for(Int_t j=0;j<_N;j++)sep[num_ad3][j][i]=0;
    sep[num_ad3][_N-1][i]=E0;
    Etem=E0;
    Int_t k=1;
    //cout<<" Y1"<<'\n';
        ui=0;
        x=0.;
    while(1)
        {
        
    //     if(ui%500==0)cout<<x<<"  ";
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
        
        dE=g_1H[0]->Eval(E);
        // if(k==0&&k==2){
        E=E-dE*dx;
        x=x+dx;
        // }
        // else {
        // E=E-dE*dx/20.;
        // x=x+dx/20.;
        // }
        ui++;
        }
    //     cout<<"Num="<<i<<'\t'<<"E="<<E<<'\t'<<"dE_Si="<<sep[num_ad3][1][i]<<'\t'<<"dE_Mylar="<<sep[num_ad3][3][i]<<'\t'<<"dE_CsI="<<sep[num_ad3][4][i]<<'\n';
    } 
    
    }

    //cout<<"*************************************************************************************************************"<<'\n';

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
                
                double energy;
                if(i0<NUM/2) energy = i0*80./(Double_t)(NUM);
                else energy = 40.+(i0-(Double_t)(NUM)/2)*300./(Double_t)(NUM);

                if(keypid==1&&sep[j0][4][i0]>0)
                {
                    std::cout << "energy = " << energy << "; dE = " << sep[j0][3][i0] << "; E = " << sep[j0][4][i0] << "\n";
                    calpid13_p[0]->SetPoint(ip++, sep[j0][3][i0],sep[j0][4][i0]);       
                }
                // if(keypid==1&&sep[j0][4][i0]>0)calpid13_p[0]->SetPoint(ip++, sep[j0][1][i0],sep[j0][4][i0]);       
                i0++;
        }
        ip=0;
        i03=0;
        i23=0;
        i43=0;
        keypid=0;
    }

    TCanvas* c2 = new TCanvas();
    c2->Clear();
    calpid13_p[0]->SetMarkerStyle(3);
    calpid13_p[0]->Draw("ap");
    c2->Draw();

}