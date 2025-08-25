{
Double_t Q,Ex,Theta,_15C;
_15C=28.3;
Int_t i,i0,i1;
TGraph *T1Etheta_d_t_C14_0= new TGraph;
TGraph *T1Etheta_d_t_C14_6600= new TGraph;
Double_t Ex_0=0,Ex_6600=6.094;
  for(Theta=0;Theta<10;Theta=Theta+0.01){
    for(Ex=315;Ex<427;Ex=Ex+0.01){
    Q=5.04-((15.0106/3.0160492-1.)*(_15C*15)+(14.003241988/3.0160492+1.)*Ex-2.*cos(Theta*3.14159/180.)*sqrt(15.0106*14.003241988*_15C*15*Ex)/3.0160492);
      if((Q-Ex_0)<0.1&&(Q-Ex_0)>-0.1){
	T1Etheta_d_t_C14_0->SetPoint(i++,Theta,Ex);
      }
    }
  }
i=0;
  for(Theta=0;Theta<10;Theta=Theta+0.01){
    for(Ex=315;Ex<427;Ex=Ex+0.01){
    Q=5.04-((15.0106/3.0160492-1.)*(_15C*15)+(14.003241988/3.0160492+1.)*Ex-2.*cos(Theta*3.14159/180.)*sqrt(15.0106*14.003241988*_15C*15*Ex)/3.0160492);
    if((Q-Ex_6600)<0.1&&(Q-Ex_6600)>-0.1)T1Etheta_d_t_C14_6600->SetPoint(i++,Theta,Ex);
    }
  }

  T1Etheta_d_t_C14_0->SetMarkerColor(2);
  T1Etheta_d_t_C14_0->SetMarkerStyle(1);
  T1Etheta_d_t_C14_0->Draw("samep");

  T1Etheta_d_t_C14_6600->SetMarkerColor(4);
  T1Etheta_d_t_C14_6600->SetMarkerStyle(1);
  T1Etheta_d_t_C14_6600->Draw("samep");

}
