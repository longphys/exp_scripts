{
//========= Macro generated from object: test/Graph
//========= by ROOT version6.36.02
   
   std::vector<Double_t> cutg_vect0{ 6014.690481227944, 6355.718817894132, 6722.980103534643, 7028.871288607222, 7137.460697328934, 6911.857336149763, 6418.677895432505, 6161.594995484148, 6019.937071022808, 6014.690481227944 };
   std::vector<Double_t> cutg_vect1{ 18.02785478802986, 16.96688071321706, 15.90590663840426, 15.4675983268241, 16.00941630423965, 16.88924846384051, 17.87259028927676, 18.23487411970064, 18.07960962094755, 18.02785478802986 };
   TCutG *cutg = new TCutG("test", 10, cutg_vect0.data(), cutg_vect1.data());
   cutg->SetVarX("Rea[0]");
   cutg->SetVarY("Ryc[0]");
   cutg->SetTitle("Graph");
   cutg->SetFillStyle(1000);
   cutg->Draw();
}
