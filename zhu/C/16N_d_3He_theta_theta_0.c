{
  int count_d_t_theta_theta_0=0,count_d_t_theta_theta_740=0;
  TGraph *lisea=new TGraph();
  TGraph *lisea_754=new TGraph();
  ifstream ina("/home/zhuhy/JNBook/Experiment2022/taf/check/angle/txt/thetatheta_C15He3_0.txt");
  string ssa;
  Double_t thetac, theta;
  if(ina.is_open()){
    getline(ina,ssa);
    count_d_t_theta_theta_0=0;
    while(!ina.eof())
    {
      ina>>thetac>>theta;
      lisea->SetPoint(count_d_t_theta_theta_0++,thetac,theta);
    }
  }
  ina.close();

  ifstream ina2("/home/zhuhy/JNBook/Experiment2022/taf/check/angle/txt/thetatheta_C15He3_740.txt");
  if(ina2.is_open()){
    getline(ina2,ssa);
    count_d_t_theta_theta_0=0;
    while(!ina2.eof())
    {
      ina2>>thetac>>theta;
      lisea_754->SetPoint(count_d_t_theta_theta_740++,thetac,theta);
    }
  }
  ina2.close();

  lisea->SetMarkerStyle(6);
  lisea->SetMarkerColor(2);
  //lisea->Draw("samep");
  lisea_754->SetMarkerStyle(6);
  lisea_754->SetMarkerColor(2);
  lisea_754->Draw("samep");

}
