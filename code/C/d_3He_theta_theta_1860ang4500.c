{
  int count_d_t_theta_theta_0=0,count_d_t_theta_theta_1=0;
  TGraph *lisea=new TGraph();
  TGraph *lisea_2=new TGraph();
  ifstream ina("/home/zhuhy/JNBook/Experiment2022/taf/check/angle/txt/thetatheta_B14He3_1690.txt");
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

  ifstream ina2("/home/zhuhy/JNBook/Experiment2022/taf/check/angle/txt/thetatheta_B14He3_7320.txt");
  string ssa2;
  if(ina2.is_open()){
    getline(ina2,ssa2);
    count_d_t_theta_theta_1=0;
    while(!ina2.eof())
    {
      ina2>>thetac>>theta;
      lisea_2->SetPoint(count_d_t_theta_theta_1++,thetac,theta);
    }
  }
  ina2.close();


  lisea->SetMarkerStyle(6);
  lisea->SetMarkerColor(2);
  lisea->Draw("samep");
  lisea_2->SetMarkerStyle(6);
  lisea_2->SetMarkerColor(4);
  lisea_2->Draw("samep");

}
