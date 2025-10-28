{
//========= Macro generated from object: 12Be/Graph
//========= by ROOT version6.36.02
   
   std::vector<Double_t> cutg_vect0{ 6222.861777770478, 7385.308070163911, 7792.919107756415, 7823.112517948451, 7038.083852955483, 6192.668367578441, 5936.024380946124, 6102.088137002329, 6222.861777770478 };
   std::vector<Double_t> cutg_vect1{ 19.91031102417507, 18.27534018269148, 15.91371563388185, 13.55209108507222, 15.36872535338732, 17.36702304853392, 18.45700360952299, 20.4553013046696, 19.91031102417507 };
   TCutG *cutg = new TCutG("12Be", 9, cutg_vect0.data(), cutg_vect1.data());
   cutg->SetVarX("Rea[0]");
   cutg->SetVarY("Rxc[0]");
   cutg->SetTitle("Graph");
   cutg->SetFillStyle(1000);
   cutg->Draw();
}
