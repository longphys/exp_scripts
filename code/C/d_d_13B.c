{
Double_t Q,Ex,Theta,_15C;
_15C=28.3;
Int_t i,i0,i1;
TGraph *nT1Etheta_d_t_C14_0a= new TGraph;
TGraph *nT1Etheta_d_t_C14_6600a= new TGraph;
Double_t Ex_0=25.4,Ex_6600=0;
  for(Theta=0;Theta<10;Theta=Theta+0.01){
    for(Ex=30;Ex<420;Ex=Ex+0.01){
    Q=-((15.0106/2.01410177811-1.)*(_15C*15)+(15.0106/2.01410177811+1.)*Ex-2.*cos(Theta*3.14159/180.)*sqrt(15.0106*15.0106*_15C*15*Ex)/2.01410177811);
      if((Q-Ex_0)<0.1&&(Q-Ex_0)>-0.1){
	nT1Etheta_d_t_C14_0a->SetPoint(i++,Theta,Ex*13./15.);
      }
    }
  }
i=0;
  for(Theta=0;Theta<10;Theta=Theta+0.01){
    for(Ex=315;Ex<427;Ex=Ex+0.01){
    Q=-((15.0106/2.01410177811-1.)*(_15C*15)+(15.0106/2.01410177811+1.)*Ex-2.*cos(Theta*3.14159/180.)*sqrt(15.0106*15.0106*_15C*15*Ex)/2.01410177811);
    if((Q-Ex_6600)<0.1&&(Q-Ex_6600)>-0.1)nT1Etheta_d_t_C14_6600a->SetPoint(i++,Theta,Ex*14./15.);
    }
  }

  nT1Etheta_d_t_C14_0a->SetMarkerColor(2);
  nT1Etheta_d_t_C14_0a->SetMarkerStyle(6);
  nT1Etheta_d_t_C14_0a->Draw("samep");

  nT1Etheta_d_t_C14_6600a->SetMarkerColor(2);
  nT1Etheta_d_t_C14_6600a->SetMarkerStyle(1);
  //nT1Etheta_d_t_C14_6600a->Draw("samep");

}
