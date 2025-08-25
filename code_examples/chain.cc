void chain(){        
/*******16C CH2*********/
//          int start = 344;
//          int stop = 378;
/*******15C CH2*********/
//          int start = 420;
//          int stop = 452;
/*******15C CD2*********/
        int start = 453;
        int stop = 530;
/*******15C C*********/
//        int start = 531;
//        int stop = 551;
/*******15C 空*********/
//        int start = 552;
//        int stop = 560;
/*******16N CH2*********/
//        int start = 591;
//        int stop = 601;
/*******16N CD2*********/
//        int start = 563;
//        int stop = 586;
/*******16N C*********/
//        int start = 587;
//        int stop = 590;
/*******16N CD2*********/
//        int start = 602;
//        int stop = 603;

        TChain *fch;
  	fch = new TChain("tree", "tele");
  	for (int i= start; i<=stop; i++){
          TString fileName = TString::Format("tele%04d.root" , i);
          fch->AddFile(fileName.Data());}
/*******15C CH2*********/
//        start = 799;
//        stop = 809;
/*******15C CD2*********/
// 	start = 748;
//        stop = 789;
/*******15C C*********/
//        start = 792;
//        stop = 798;
/*******15C 空*********/
//        start = 790;
//        stop = 791;

	for (int i= start; i<stop; i++){
          TString fileName = TString::Format("tele%04d.root" , i);
//          fch->AddFile(fileName.Data());
	}

/*  	start = 871;
  	stop = 904;
  	for (int i= start; i<=stop; i++){
    	  TString fileName = TString::Format("tele%04d.root" , i);
    	  fch->AddFile(fileName.Data());}      
  */      
/*	TString fileName = TString::Format("all3He.root");
        fch->AddFile(fileName.Data());
*/
}
