{
Double_t Q,Ex,Theta,_15C;
_15C=28.3;
Int_t i;
TGraph *T1Etheta_d_t_C14_0= new TGraph;
TGraph *T1Etheta_d_t_C14_6600= new TGraph;
Double_t Ex_0=0,Ex_6600=6.094;
//    Q=1.01-((15.0106/14.003241988-1.)*(_15C*15)+(2.01410177811/14.003241988+1.)*Ex
//       -2.*cos(Theta*3.14159/180.)*sqrt(15.0106*2.01410177811*_15C*15*Ex)/14.003241988);

  for(Theta=0;Theta<50;Theta=Theta+0.05){
    for(Ex=0;Ex<100;Ex=Ex+0.01){
    Q=1.01-((15.0106/14.003241988-1.)*(_15C*15)+(2.01410177811/14.003241988+1.)*Ex-2.*cos(Theta*3.14159/180.)*sqrt(15.0106*2.01410177811*_15C*15*Ex)/14.003241988);
    if((Q-Ex_0)<0.01&&(Q-Ex_0)>-0.01)T1Etheta_d_t_C14_0->SetPoint(i++,Theta,Ex);
    }
  }
  for(Theta=0;Theta<50;Theta=Theta+0.05){
    for(Ex=0;Ex<100;Ex=Ex+0.01){
    Q=1.01-((15.0106/14.003241988-1.)*(_15C*15)+(2.01410177811/14.003241988+1.)*Ex-2.*cos(Theta*3.14159/180.)*sqrt(15.0106*2.01410177811*_15C*15*Ex)/14.003241988);
    if((Q-Ex_6600)<0.01&&(Q-Ex_6600)>-0.01)T1Etheta_d_t_C14_6600->SetPoint(i++,Theta,Ex);
    }
  }

  T1Etheta_d_t_C14_0->SetMarkerColor(4);
  T1Etheta_d_t_C14_0->SetMarkerStyle(6);
  T1Etheta_d_t_C14_0->Draw("samep");

  T1Etheta_d_t_C14_6600->SetMarkerColor(6);
  T1Etheta_d_t_C14_6600->SetMarkerStyle(6);
  T1Etheta_d_t_C14_6600->Draw("samep");

}
