{
  int count_d_t_theta_theta_0=0,count_d_t_theta_theta_1=0;
  TGraph *lisea=new TGraph();
  ifstream ina("/home/zhuhy/JNBook/Experiment2022/taf/check/angle/txt/C15_d_d_thetatheta_20.txt");
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

  TGraph *lisea1=new TGraph();
  ifstream ina1("/home/zhuhy/JNBook/Experiment2022/taf/check/angle/txt/C15_d_d_thetatheta_30.txt");
  if(ina1.is_open()){
    getline(ina1,ssa);
    count_d_t_theta_theta_1=0;
    while(!ina1.eof())
    {
      ina1>>thetac>>theta;
      lisea1->SetPoint(count_d_t_theta_theta_1++,thetac,theta);
    }
  }
  ina1.close();


  lisea->SetMarkerStyle(6);
  lisea->SetMarkerColor(4);
  lisea->Draw("samep");
  lisea1->SetMarkerStyle(6);
  lisea1->SetMarkerColor(4);
  lisea1->Draw("samep");

}
