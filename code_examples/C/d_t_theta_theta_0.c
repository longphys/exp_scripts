{
  int count_d_t_theta_theta_0=0,count_d_t_theta_theta_0_06=0;
  TGraph *lisea=new TGraph();
  TGraph *lisea_theta06=new TGraph();
  ifstream ina("/home/zhuhy/JNBook/Experiment2022/taf/check/angle/txt/thetatheta_C15_dt_tC14_0.txt");
  string ssa;
  Double_t thetac, theta;
  if(ina.is_open()){
    getline(ina,ssa);
    count_d_t_theta_theta_0=0;
    while(!ina.eof())
    {
      ina>>thetac>>theta;
      lisea->SetPoint(count_d_t_theta_theta_0++,thetac,theta);
      lisea_theta06->SetPoint(count_d_t_theta_theta_0_06++,thetac-0.4,theta);
      lisea_theta06->SetPoint(count_d_t_theta_theta_0_06++,thetac+0.4,theta);
    }
  }
  ina.close();
  lisea->SetMarkerStyle(6);
  lisea->SetMarkerColor(2);
  lisea->Draw("samep");
  lisea_theta06->SetMarkerStyle(6);
  lisea_theta06->SetMarkerColor(4);
//  lisea_theta06->Draw("samep");

}
