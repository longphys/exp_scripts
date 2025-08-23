{
Double_t Q,Ex,Theta,_15C;
_15C=28.3;
Int_t i,i0,i1;
TGraph *T1Etheta_d_t_C14_0= new TGraph;
TGraph *T1Etheta_d_t_C14_6600= new TGraph;
Double_t Ex_0=0,Ex_6600=3.6;
  for(Theta=0;Theta<30;Theta=Theta+0.01){
    for(Ex=300;Ex<420;Ex=Ex+0.01){
    Q=4.02-((15.0106/4.00260325413-1.)*(_15C*15)+(13.0177800/4.00260325413+1.)*Ex-2.*cos(Theta*3.14159/180.)*sqrt(15.0106*13.0177800*_15C*15*Ex)/4.00260325413);
      if(fabs(Q-Ex_0)<0.001){
	T1Etheta_d_t_C14_0->SetPoint(i++,Theta,Ex);
      }
    }
  }
i=0;
  for(Theta=0;Theta<30;Theta=Theta+0.01){
    for(Ex=300;Ex<420;Ex=Ex+0.01){
    Q=4.02-((15.0106/4.00260325413-1.)*(_15C*15)+(13.0177800/4.00260325413+1.)*Ex-2.*cos(Theta*3.14159/180.)*sqrt(15.0106*13.0177800*_15C*15*Ex)/4.00260325413);
    if(fabs(Q-Ex_6600)<0.001)T1Etheta_d_t_C14_6600->SetPoint(i++,Theta,Ex);
    }
  }

  T1Etheta_d_t_C14_0->SetMarkerColor(2);
  T1Etheta_d_t_C14_0->SetMarkerStyle(6);
  T1Etheta_d_t_C14_0->Draw("samep");

  T1Etheta_d_t_C14_6600->SetMarkerColor(4);
  T1Etheta_d_t_C14_6600->SetMarkerStyle(6);
  T1Etheta_d_t_C14_6600->Draw("samep");

}
