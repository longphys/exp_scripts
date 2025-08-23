#define _N 5
#define stripnum 0
#define realthick 137.25
{
Double_t Q,Ex,Theta,_15C;
_15C=28.3;
Int_t i;
TGraph *T1Etheta_d_t_C14_0= new TGraph;
TGraph *T1Etheta_d_t_C14_6600= new TGraph;
Double_t E_0[20000],E_6600[20000],thetaE0[20000],thetaE6600[20000];
Int_t countE0=0,countE6600=0;
Double_t Ex_0=1.86,Ex_6600=4.5;

  ifstream ina("/home/zhuhy/JNBook/Experiment2022/taf/check/angle/txt/C15_d_3He_E_theta_1610.txt");
  string ssa;
  Double_t thetac, theta,Ehigh,Elight;
  if(ina.is_open()){
    count_d_t_theta_theta_0=0;
    while(!ina.eof())
    {
      ina>>thetac>>Ehigh>>theta>>Elight;
      if(theta>20&&theta<50&&Elight*3<25){
        E_0[countE0]=Elight*3;
        thetaE0[countE0++]=theta;
      }
    }
  }
  ina.close();


  ifstream ina2("/home/zhuhy/JNBook/Experiment2022/taf/check/angle/txt/C15_d_3He_E_theta_3270.txt");
  if(ina2.is_open()){
    while(!ina2.eof())
    {
      ina2>>thetac>>Ehigh>>theta>>Elight;
      if(theta>20&&theta<50&&Elight*3<25){
        E_0[countE0]=Elight*3;
        thetaE0[countE0++]=theta;
      }
    }
  }
  ina2.close();

  ifstream ina3("/home/zhuhy/JNBook/Experiment2022/taf/check/angle/txt/C15_d_3He_E_theta_5130.txt");
  if(ina3.is_open()){
    while(!ina3.eof())
    {
      ina3>>thetac>>Ehigh>>theta>>Elight;
      if(theta>20&&theta<50&&Elight*3<25){
        E_0[countE0]=Elight*3;
        thetaE0[countE0++]=theta;
      }
    }
  }
  ina3.close();


  ifstream ina4("/home/zhuhy/JNBook/Experiment2022/taf/check/angle/txt/C15_d_3He_E_theta_7640.txt");
  if(ina4.is_open()){
    while(!ina4.eof())
    {
      ina4>>thetac>>Ehigh>>theta>>Elight;
      if(theta>20&&theta<50&&Elight*3<25){
        E_0[countE0]=Elight*3;
        thetaE0[countE0++]=theta;
      }
    }
  }
  ina4.close();


/*
  for(Theta=20;Theta<50;Theta=Theta+0.05){
    for(Ex=0;Ex<30;Ex=Ex+0.03){
    Q=-15.59-((15.0106/14.0254-1.)*(_15C*15)+(3.01603/14.0254+1.)*Ex-2.*cos(Theta*3.14159/180.)*sqrt(15.0106*3.01603*_15C*15*Ex)/14.0254);
	if(abs(Q-Ex_0)<0.000001){
		T1Etheta_d_t_C14_0->SetPoint(i++,Theta,Ex);
		E_0[countE0]=Ex;
		thetaE0[countE0++]=Theta;
                break;
	}
    }
  }
*/
  for(Theta=20;Theta<50;Theta=Theta+0.05){
    for(Ex=0;Ex<30;Ex=Ex+0.03){
    Q=-15.59-((15.0106/14.0254-1.)*(_15C*15)+(3.01603/14.0254+1.)*Ex-2.*cos(Theta*3.14159/180.)*sqrt(15.0106*3.01603*_15C*15*Ex)/14.0254);
    	if(abs(Q-Ex_6600)<0.000001){
                T1Etheta_d_t_C14_6600->SetPoint(i++,Theta,Ex);
                E_6600[countE6600]=Ex;
                thetaE6600[countE6600++]=Theta;
		break;
	}
    }
  }



/*
  T1Etheta_d_t_C14_0->SetMarkerColor(1);
  T1Etheta_d_t_C14_0->SetMarkerStyle(1);
  T1Etheta_d_t_C14_0->Draw();

  T1Etheta_d_t_C14_6600->SetMarkerColor(2);
  T1Etheta_d_t_C14_6600->SetMarkerStyle(1);
  T1Etheta_d_t_C14_6600->Draw("samep");

	//cout<<"countE0="<<countE0<<'\n';
	for(Int_t ii=0;ii<countE0;ii++){
	//	cout<<E_0[ii]<<'\t'<<thetaE0[ii]<<'\n';
	}
*/
Double_t xxs,ad3_thick[16];

char str_thick[100]="/home/zhuhy/JNBook/Experiment2022/taf/csicali/txt/taf_ad0_thickreal.txt";
ifstream in_thick(str_thick);
  if(in_thick.is_open()){
//    getline(in,ss);
    Int_t i=0; 
    while(i<16)
    {
      in_thick>>xxs>>ad3_thick[i];
      ad3_thick[i]=ad3_thick[i]*realthick/150.;
      i++;
    }
  }
  in_thick.close();


  string ss;
  Double_t aa, bbb, e, dedx;
  i=0;
  Double_t E0=0,Etem=0,Esmall=0,E2=0,E=0,dE=0,x=0,dx=0.25;
//E0为能量总值，E为能量实时记录值，E1为穿透第一块硅时的能量，E2为穿透第二块时的能量
  Double_t sep[16][_N][10000];
  Double_t sed[16][_N][10000];
  Double_t sett[16][_N][10000];

  TString  str_1H[4];
  str_1H[0]=TString::Format("/home/zhuhy/JNBook/15C_Etheta/TAT0_datacheck/PID/txt/3He-CD2.txt");
  str_1H[1]=TString::Format("/home/zhuhy/JNBook/15C_Etheta/TAT0_datacheck/PID/txt/3He-Al.txt");
  str_1H[2]=TString::Format("/home/zhuhy/JNBook/15C_Etheta/TAT0_datacheck/PID/txt/3He-Si.txt");
  str_1H[2]=TString::Format("/home/zhuhy/JNBook/15C_Etheta/TAT0_datacheck/PID/txt/3He-CsI.txt");

  TGraph *g_1H[4];

  ifstream in_1H(str_1H[0].Data());

  g_1H[0]=new TGraph;//定义新的二维散点图(TGraph) g1
  if(in_1H.is_open()){//检查文件是否存在
//    getline(in,ss);
    Int_t i=0; 
    while(!in_1H.eof())
    {
      in_1H>>aa>>bbb>>e>>dedx>>aa>>bbb>>aa>>bbb>>aa>>bbb>>aa>>bbb;
      // 对照数据文件进行理解。一列一列地读入，提取第3、4列数据。
      g_1H[0]->SetPoint(i++, e*3,dedx);//添加数据点到图中，能量单位为MeV/u，对C需乘以12.    
    }
  }
  in_1H.close();

  ifstream in1_1H(str_1H[1].Data());
  g_1H[1]=new TGraph;
  if(in1_1H.is_open()){
//    getline(in1,ss);
    i=0;
    while(!in1_1H.eof())
    {
      in1_1H>>aa>>bbb>>e>>dedx>>aa>>bbb>>aa>>bbb>>aa>>bbb>>aa>>bbb;
      g_1H[1]->SetPoint(i++, e*3,dedx);
    }
  }
  in1_1H.close();


  ifstream in2_1H(str_1H[2]);
  g_1H[2]=new TGraph;
  if(in2_1H.is_open()){
//    getline(in1,ss);
    i=0;
    while(!in2_1H.eof())
    {
      in2_1H>>aa>>bbb>>e>>dedx>>aa>>bbb>>aa>>bbb>>aa>>bbb>>aa>>bbb;
      g_1H[2]->SetPoint(i++, e*3,dedx);
    }
  }
  in2_1H.close();

  ifstream in3_1H(str_1H[3]);
  g_1H[3]=new TGraph;
  if(in3_1H.is_open()){
//    getline(in1,ss);
    i=0;
    while(!in3_1H.eof())
    {
      in3_1H>>aa>>bbb>>e>>dedx>>aa>>bbb>>aa>>bbb>>aa>>bbb>>aa>>bbb;
      g_1H[3]->SetPoint(i++, e*3,dedx);
    }
  }
  in3_1H.close();


 Double_t d[_N-1];
 Int_t k; //kind  0:Si 1:Al 2:Mylar
 Int_t num_ad3=0;
 Int_t ui;

for(num_ad3=stripnum;;num_ad3=5){
 // cout<<"num_ad3="<<num_ad3<<'\n';
 //cout<<ad3_thick[num_ad3]<<" : "<<ad4_thick[num_ad4]<<'\n';

 d[0]=23.35*ad3_thick[num_ad3]/realthick; 
 d[1]=0.5*ad3_thick[num_ad3]/realthick;
 d[2]=ad3_thick[num_ad3];
 d[3]=1000000;
 for(i=1;i<(_N-1);i++)d[i]=d[i]+d[i-1];
 for(i=-1;i<countE0;x=0)   //开始countE0次模拟
  {
  if(i%100==0)cout<<i<<":"<<countE0<<'\n';
  i++;
  if(i>=countE0)break;
  x=0;
  //Esmall=rand()%1000;  //初始能量小数部分
  E0=E=E_0[i];
  //+Esmall/1000;  
  //E0=E=+Esmall/1000;  //能量随机值为300+3位小数
  for(Int_t j=0;j<_N;j++)sep[num_ad3][j][i]=0;
  sep[num_ad3][_N-1][i]=E0;
  Etem=E0;
  Int_t k=0;
//cout<<" Y1"<<'\n';
     ui=0;
     x=0.;
  while(1)
    {
      
 //     if(ui%500==0)cout<<x<<"  ";
     if((fabs(x-d[0])<=(dx/40.)||(x>=0&&x<d[0]))&&E<=0){sep[num_ad3][0][i]=Etem;Etem=0;break;}
     else if(fabs(x-d[0])<=(dx/40.)&&E>0){if(k!=1){sep[num_ad3][0][i]=E0-E;Etem=E;}k=1;}

     else if((fabs(x-d[1])<=(dx/40.)||(x>d[0]&&x<d[1]))&&E<=0){sep[num_ad3][1][i]=Etem;Etem=0;break;}
     else if(fabs(x-d[1])<=(dx/40.)&&E>0){if(k!=2){sep[num_ad3][1][i]=Etem-E;Etem=E;}k=2;}

     else if((fabs(x-d[2])<=(dx/40.)||(x>d[1]&&x<d[2]))&&E<=0){sep[num_ad3][2][i]=Etem;Etem=0;break;}
     else if(fabs(x-d[2])<=(dx/40.)&&E>0){if(k!=3){sep[num_ad3][2][i]=Etem-E;Etem=E;}k=3;}

     else if(((fabs(x-d[3])>(dx/40.)&&x>d[3])&&E<=0)){sep[num_ad3][3][i]=Etem;Etem=0;break;}
     else if(((fabs(x-d[3])>(dx/40.)&&x>d[3])&&E>0)){sep[num_ad3][3][i]=Etem-E;Etem=0;break;}
     else if(fabs(x-d[3])<=(dx/40.)&&E>0){if(k!=2){sep[num_ad3][3][i]=Etem-E;Etem=E;}k=2;}
     
     dE=g_1H[k]->Eval(E);
     E=E-dE*dx/20.;
     x=x+dx/20.;
     ui++;
     if(x>1000)break;
    }


 //    cout<<"Num="<<i<<'\t'<<"E="<<E0<<'\t'<<"dE_Si="<<sep[num_ad3][1][i]<<'\t'<<"dE_Mylar="<<sep[num_ad3][3][i]<<'\t'<<"dE_CsI="<<sep[num_ad3][4][i]<<'\n';
  } 
  if(num_ad3>=0)break; 
  num_ad3=5; 
}
  TGraph *Etheta_d[16];
  for(Int_t i=0;i<16;i++){
        Etheta_d[i]=new TGraph();
  }


  Int_t keypid=1;
  Int_t ip=0,i03=0,i23=0,i43=0;
  for(Int_t j0=stripnum;;j0=5){
      cout<<"******************j="<<j0<<"*****************"<<'\n';
          for(Int_t i0=0;i0<countE0;){
            if(sep[j0][2][i0]>0.1&&sep[j0][3][i0]<10)Etheta_d[j0]->SetPoint(ip++,thetaE0[i0],sep[j0][2][i0]);       
            i0++;
      }
      ip=0;
      i03=0;
      i23=0;
      i43=0;
      keypid=0;
      if(j0==5)break; 
  }

  Etheta_d[5]->SetMarkerColor(4);
  Etheta_d[5]->SetMarkerStyle(6);
  //Etheta_d[5]->Draw("samep");

  Etheta_d[0]->SetMarkerColor(2);
  Etheta_d[0]->SetMarkerStyle(6);
  Etheta_d[0]->Draw("samep");


}
