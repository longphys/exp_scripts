{
Double_t Q,Ex,Theta,_15C;
_15C=30.;
Int_t i,i0,i1;
TGraph *T1Etheta_d_t_C14_0= new TGraph;
TGraph *T1Etheta_d_t_C14_6600= new TGraph;
Double_t Ex_0=0.,Ex_6600=0.740;
  for(Theta=0;Theta<10;Theta=Theta+0.01){
    for(Ex=340;Ex<470;Ex=Ex+0.01){
    Q=-5.98-((16.0061/3.01603-1.)*(_15C*16)+(15.0106/3.01603+1.)*Ex-2.*cos(Theta*3.14159/180.)*sqrt(16.0061*15.0106*_15C*16*Ex)/3.01603);
      if((Q-Ex_0)<0.01&&(Q-Ex_0)>-0.01){
	T1Etheta_d_t_C14_0->SetPoint(i++,Theta,Ex);
      }
    }
  }
i=0;
  for(Theta=0;Theta<10;Theta=Theta+0.01){
    for(Ex=340;Ex<470;Ex=Ex+0.01){
    Q=-5.98-((16.0061/3.01603-1.)*(_15C*16)+(15.0106/3.01603+1.)*Ex-2.*cos(Theta*3.14159/180.)*sqrt(16.0061*15.0106*_15C*16*Ex)/3.01603);
    if((Q-Ex_6600)<0.01&&(Q-Ex_6600)>-0.01)T1Etheta_d_t_C14_6600->SetPoint(i++,Theta,Ex);
    }
  }

  T1Etheta_d_t_C14_0->SetMarkerColor(2);
  T1Etheta_d_t_C14_0->SetMarkerStyle(6);
  //T1Etheta_d_t_C14_0->Draw("samep");

  T1Etheta_d_t_C14_6600->SetMarkerColor(2);
  T1Etheta_d_t_C14_6600->SetMarkerStyle(6);
  T1Etheta_d_t_C14_6600->Draw("samep");

}
