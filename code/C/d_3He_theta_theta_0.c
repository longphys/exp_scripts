{
  int count_d_t_theta_theta_0=0,count_d_t_theta_theta_0_1800=0,count_d_t_theta_theta_0_4500=0;
  TGraph *lisea=new TGraph();
  TGraph *lisea_1800=new TGraph();
  TGraph *lisea_4500=new TGraph();
  ifstream ina("/home/zhuhy/JNBook/Experiment2022/taf/check/angle/txt/thetatheta_B14He3_0.txt");
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

  ifstream ina2("/home/zhuhy/JNBook/Experiment2022/taf/check/angle/txt/thetatheta_B14He3_654.txt");
  if(ina2.is_open()){
    getline(ina2,ssa);
    count_d_t_theta_theta_1800=0;
    while(!ina2.eof())
    {
      ina2>>thetac>>theta;
      lisea_1800->SetPoint(count_d_t_theta_theta_1800++,thetac,theta);
    }
  }
  ina2.close();

  ifstream ina3("/home/zhuhy/JNBook/Experiment2022/taf/check/angle/txt/thetatheta_B14He3_4500.txt");
  if(ina3.is_open()){
    getline(ina3,ssa);
    count_d_t_theta_theta_4500=0;
    while(!ina3.eof())
    {
      ina3>>thetac>>theta;
      lisea_4500->SetPoint(count_d_t_theta_theta_4500++,thetac,theta);
    }
  }
  ina3.close();


  lisea->SetMarkerStyle(6);
  lisea->SetMarkerColor(2);
  lisea->Draw("samep");

  lisea_1800->SetMarkerStyle(6);
  lisea_1800->SetMarkerColor(4);
  lisea_1800->Draw("samep");

  lisea_4500->SetMarkerStyle(6);
  lisea_4500->SetMarkerColor(4);
  //lisea_4500->Draw("samep");
}
