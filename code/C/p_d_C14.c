{
Double_t Q,Ex,Theta,_15C;
_15C=28.3;
Int_t i,i0,i1;
TGraph *nT1Etheta_d_t_C14_0= new TGraph;
TGraph *nT1Etheta_d_t_C14_6600= new TGraph;
Double_t Ex_0=0,Ex_6600=6.5;
  for(Theta=0;Theta<10;Theta=Theta+0.01){
    for(Ex=315;Ex<427;Ex=Ex+0.01){
    Q=1.01-((15.0106/2.01410177811-1.)*(_15C*15)+(14.003241988/2.01410177811+1.)*Ex-2.*cos(Theta*3.14159/180.)*sqrt(15.0106*14.003241988*_15C*15*Ex)/2.01410177811);
      if((Q-Ex_0)<0.01&&(Q-Ex_0)>-0.01){
	nT1Etheta_d_t_C14_0->SetPoint(i++,Theta,Ex);
      }
    }
  }
i=0;
  for(Theta=0;Theta<10;Theta=Theta+0.01){
    for(Ex=315;Ex<427;Ex=Ex+0.01){
    Q=1.01-((15.0106/2.01410177811-1.)*(_15C*15)+(14.003241988/2.01410177811+1.)*Ex-2.*cos(Theta*3.14159/180.)*sqrt(15.0106*14.003241988*_15C*15*Ex)/2.01410177811);
    if((Q-Ex_6600)<0.01&&(Q-Ex_6600)>-0.01)nT1Etheta_d_t_C14_6600->SetPoint(i++,Theta,Ex);
    }
  }

  nT1Etheta_d_t_C14_0->SetMarkerColor(2);
  nT1Etheta_d_t_C14_0->SetMarkerStyle(6);
  nT1Etheta_d_t_C14_0->Draw("samep");

  nT1Etheta_d_t_C14_6600->SetMarkerColor(4);
  nT1Etheta_d_t_C14_6600->SetMarkerStyle(6);
  nT1Etheta_d_t_C14_6600->Draw("samep");

}
