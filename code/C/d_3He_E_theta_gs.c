{
  int count_d_t_theta_theta_0=0,count_d_t_theta_theta_0_06=0;
  TGraph *lisea=new TGraph();
  TGraph *lisea2=new TGraph();
  ifstream ina("/home/zhuhy/JNBook/Experiment2022/taf/check/angle/txt/C15_d_3He_E_theta_0.txt");
  string ssa;
  Double_t thetac, theta,Ehigh,Elight;
  if(ina.is_open()){
    count_d_t_theta_theta_0=0;
    while(!ina.eof())
    {
      ina>>thetac>>Ehigh>>theta>>Elight;
      lisea->SetPoint(count_d_t_theta_theta_0++,theta,Elight*3);
    }
  }
  ina.close();


  ifstream ina2("/home/zhuhy/JNBook/Experiment2022/taf/check/angle/txt/C15_d_3He_E_theta_0654.txt");
  if(ina2.is_open()){
    count_d_t_theta_theta_0=0;
    while(!ina2.eof())
    {
      ina2>>thetac>>Ehigh>>theta>>Elight;
      lisea2->SetPoint(count_d_t_theta_theta_0++,theta,Elight*3);
    }
  }
  ina2.close();



  lisea->SetMarkerStyle(6);
  lisea->SetMarkerColor(2);
  lisea->Draw("samep");

  lisea2->SetMarkerStyle(6);
  lisea2->SetMarkerColor(6);
  lisea2->Draw("samep");

}
