{
Double_t Q,Ex,Theta,_15C;
_15C=28.3;
Int_t i,i0,i1;
TGraph *T1Etheta_d_t_C14_0= new TGraph;
TGraph *T1Etheta_d_t_C14_6600= new TGraph;
Double_t Ex_0=1.50,Ex_6600=7.57;
  for(Theta=0;Theta<12;Theta=Theta+0.01){
    for(Ex=250;Ex<408;Ex=Ex+0.01){
    Q=-15.59-((15.0106/3.01603-1.)*(_15C*15)+(14.0254/3.01603+1.)*Ex-2.*cos(Theta*3.14159/180.)*sqrt(15.0106*14.0254*_15C*15*Ex)/3.01603);
      if(fabs(Q-Ex_0)<0.001){
	T1Etheta_d_t_C14_0->SetPoint(i++,Theta,(Ex)*13./14.);
      }
    }
  }
i=0;
  for(Theta=0;Theta<12;Theta=Theta+0.01){
    for(Ex=250;Ex<408;Ex=Ex+0.01){
    Q=-15.59-((15.0106/3.01603-1.)*(_15C*15)+(14.0254/3.01603+1.)*Ex-2.*cos(Theta*3.14159/180.)*sqrt(15.0106*14.0254*_15C*15*Ex)/3.01603);
    if(fabs(Q-Ex_6600)<0.001)T1Etheta_d_t_C14_6600->SetPoint(i++,Theta,(Ex)*13./14.);
    }
  }

  T1Etheta_d_t_C14_0->SetMarkerColor(2);
  T1Etheta_d_t_C14_0->SetMarkerStyle(6);
  T1Etheta_d_t_C14_0->Draw("samep");

  T1Etheta_d_t_C14_6600->SetMarkerColor(4);
  T1Etheta_d_t_C14_6600->SetMarkerStyle(6);
  T1Etheta_d_t_C14_6600->Draw("samep");

}
