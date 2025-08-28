#include "include/cleaner.hh"
#include "include/prm.hh"
unsigned short GetClasters(unsigned short n, unsigned short *x)
{
	int i;
	unsigned short clasters = 1;

	if(n == 0) clasters = 0;
	else if(n > 1 && n < 32)
	{
		for(i = 1; i < n; ++i)
		{
			if(abs(x[i] - x[i-1]) > 1) clasters += 1;
		}
	}
	else if(n > 31) clasters = 0;
	return clasters;
} //____________________________________________________________________________
//
Double_t GetPosMW(unsigned short n, unsigned short *x)
{
	int i;
	Double_t pos = (Double_t) x[0];

	if(n == 0) pos = -200.;
	else if(n > 1 && n < 32)
	  {
		for(i = 1; i < n; ++i)
		{
			pos = pos + (Double_t) x[i];
		}
		pos = pos/n ;
	  }
	else if(n > 31) pos = -200;
	pos = (pos + gRandom->Uniform())*1.25;	//pos in mm
	return pos;
} //____________________________________________________________________________

bool cleaner()
{	
//this is piece of code for looping over all of the files in some directory (with exceptions
//in creates TChain (group of TTrees) with name TTree from all files with "root" in name
//it uses file paths as TStrings
//
//_______________________________________Parameters
//

lvBeam   = new TLorentzVector();
//lvTarget = new TLorentzVector();
//lvProton = new TLorentzVector();
//lvRes    = new TLorentzVector();

//lvTarget->SetPxPyPzE(0.0,0.0,0.0,mass_d);



//_________________________________________________
TString FileNameIn  =   "run16_00.root";
//TString FileNameIn  =   "run02_16_5.root";
TString FileNameOut =   FileNameIn;
//TString FileNameOut =   "test.root";

TFile *inF = new TFile("/home/golovkov/EXP/25e04/Be10/rawdata/" + FileNameIn, "READ");
inTree = (TTree*)inF->Get("AnalysisxTree");
//
TFile *outF = new TFile("/home/golovkov/EXP/25e04/Be10/clndata/" + FileNameOut, "RECREATE");
TTree *outTree= new TTree("clnTree", "clnTree");

inTree->SetMakeClass(1);

inTree->SetBranchAddress("NeEvent.Sa[16]",   iSa);
inTree->SetBranchAddress("NeEvent.St[16]",   iSt);
inTree->SetBranchAddress("NeEvent.Ra[16]",   iRa);
inTree->SetBranchAddress("NeEvent.Rt[16]",   iRt);
inTree->SetBranchAddress("NeEvent.S2a[16]",  iS2a);
inTree->SetBranchAddress("NeEvent.S2t[16]",  iS2t);
inTree->SetBranchAddress("NeEvent.Va[16]",   iVa);
inTree->SetBranchAddress("NeEvent.Vt[16]",   iVt);
inTree->SetBranchAddress("NeEvent.Rxa[16]",  iRxa);
inTree->SetBranchAddress("NeEvent.Rxt[16]",  iRxt);
inTree->SetBranchAddress("NeEvent.Rya[16]",  iRya);
inTree->SetBranchAddress("NeEvent.Ryt[16]",  iRyt);
inTree->SetBranchAddress("NeEvent.Lxa[32]",  iLxa);
inTree->SetBranchAddress("NeEvent.Lxt[32]",  iLxt);
inTree->SetBranchAddress("NeEvent.Lya[32]",  iLya);
inTree->SetBranchAddress("NeEvent.Lyt[32]",  iLyt);
inTree->SetBranchAddress("NeEvent.Cxa[16]",  iCxa);
inTree->SetBranchAddress("NeEvent.Cxt[16]",  iCxt);
inTree->SetBranchAddress("NeEvent.Cya[16]",  iCya);
inTree->SetBranchAddress("NeEvent.Cyt[16]",  iCyt);
inTree->SetBranchAddress("NeEvent.Lea[16]",  iLea);
inTree->SetBranchAddress("NeEvent.Let[16]",  iLet);
inTree->SetBranchAddress("NeEvent.Rea[16]",  iRea);
inTree->SetBranchAddress("NeEvent.Ret[16]",  iRet);
inTree->SetBranchAddress("NeEvent.Focus3[4]",    iFocus3);
inTree->SetBranchAddress("NeEvent.tF3[4]",   itF3);
inTree->SetBranchAddress("NeEvent.F5[4]",    iF5);
inTree->SetBranchAddress("NeEvent.tF5[4]",   itF5);
inTree->SetBranchAddress("NeEvent.F6[4]",    iF6);
inTree->SetBranchAddress("NeEvent.tF6[4]",   itF6);
inTree->SetBranchAddress("NeEvent.tMWPC[4]",   itMWPC);
inTree->SetBranchAddress("NeEvent.scaler[16]", scaler);
//inTree->SetBranchAddress("NeEvent.af3",  &af3);
//inTree->SetBranchAddress("NeEvent.af5",  &af5);
//inTree->SetBranchAddress("NeEvent.af6",  &af6);
inTree->SetBranchAddress("NeEvent.ToF",  &ToF);
inTree->SetBranchAddress("NeEvent.xbt",  &xbt);
inTree->SetBranchAddress("NeEvent.ybt",  &ybt);
inTree->SetBranchAddress("NeEvent.xbd",  &xbd);
inTree->SetBranchAddress("NeEvent.ybd",  &ybd);
inTree->SetBranchAddress("NeEvent.Sc[16]",  Sc);
inTree->SetBranchAddress("NeEvent.Rc[16]",  Rc);
inTree->SetBranchAddress("NeEvent.S2c[16]",  S2c);
inTree->SetBranchAddress("NeEvent.Vc[16]",  Vc);
inTree->SetBranchAddress("NeEvent.Rxc[16]",  Rxc);
inTree->SetBranchAddress("NeEvent.Ryc[16]",  Ryc);
inTree->SetBranchAddress("NeEvent.Lxc[32]",  Lxc);
inTree->SetBranchAddress("NeEvent.Lyc[32]",  Lyc);
inTree->SetBranchAddress("NeEvent.Cxc[16]",  Cxc);
inTree->SetBranchAddress("NeEvent.Cyc[16]",  Cyc);
inTree->SetBranchAddress("NeEvent.Rec[16]",  Rec);
inTree->SetBranchAddress("NeEvent.Lec[16]",  Lec);

inTree->SetBranchAddress("NeEvent.nx1",  &nx1);
inTree->SetBranchAddress("NeEvent.ny1",  &ny1);
inTree->SetBranchAddress("NeEvent.nx2",  &nx2);
inTree->SetBranchAddress("NeEvent.ny2",  &ny2);
inTree->SetBranchAddress("NeEvent.x1[32]",  ix1);
inTree->SetBranchAddress("NeEvent.y1[32]",  iy1);
inTree->SetBranchAddress("NeEvent.x2[32]",  ix2);
inTree->SetBranchAddress("NeEvent.y2[32]",  iy2);
/*inTree->SetBranchAddress("NeEvent.rx1",  &rx1);
inTree->SetBranchAddress("NeEvent.rx2",  &rx2);
inTree->SetBranchAddress("NeEvent.ry1",  &ry1);
inTree->SetBranchAddress("NeEvent.ry2",  &ry2);
*/
inTree->SetBranchAddress("NeEvent.nevent",  &nevent);
inTree->SetBranchAddress("NeEvent.trigger",   &trigger);
//____________________________________________
outTree->SetMakeClass(1);

outTree->Branch("af3",  &af3,  "af3/D");
outTree->Branch("af5",  &af5,  "af5/D");
outTree->Branch("tF3",  tF3,   "tF3[5]/D");
outTree->Branch("F3",   F3,    "F3[5]/D");
outTree->Branch("tF5",  tF5,   "tF5[5]/D");
outTree->Branch("F5",   F5,    "F5[5]/D");
outTree->Branch("tF6",  tF6,   "tF6[5]/D");
outTree->Branch("F6",   F6,    "F6[5]/D");
outTree->Branch("ToF",  &ToF,  "ToF/D");
outTree->Branch("tBeam",  &tBeam,  "tBeam/D");
outTree->Branch("tBeamC", &tBeamC, "tBeamC/D");
outTree->Bronch("lvBeam",	"TLorentzVector",	&lvBeam);
outTree->Branch("xbt",  &xbt,  "xbt/D");
outTree->Branch("ybt",  &ybt,  "ybt/D");
outTree->Branch("xbd",  &xbd,  "xbd/D");
outTree->Branch("ybd",  &ybd,  "ybd/D");
outTree->Branch("tMWPC",  tMWPC,  "tMWPC[4]/D");

outTree->Branch("Rxc",  Rxc,  "Rxc[16]/D");
outTree->Branch("Rxt",  Rxt,  "Rxt[16]/D");
outTree->Branch("Ryc",  Ryc,  "Ryc[16]/D");
outTree->Branch("Ryt",  Ryt,  "Ryt[16]/D");
outTree->Branch("Lxc",  Lxc,  "Lxc[32]/D");
outTree->Branch("Lxt",  Lxt,  "Lxt[32]/D");
outTree->Branch("Lyc",  Lyc,  "Lyc[32]/D");
outTree->Branch("Lyt",  Lyt,  "Lyt[32]/D");
//
outTree->Branch("mLX",  &mLX, "mLX/I");
outTree->Branch("LXe",  LXe,  "LXe[32]/D");
outTree->Branch("LXt",  LXt,  "LXt[32]/D");
outTree->Branch("LXn",  LXn,  "LXn[32]/I");
outTree->Branch("mLY",  &mLY, "mLY/I");
outTree->Branch("LYe",  LYe,  "LYe[32]/D");
outTree->Branch("LYt",  LYt,  "LYt[32]/D");
outTree->Branch("LYn",  LYn,  "LYn[32]/I");
outTree->Branch("mRX",  &mRX, "mRX/I");
outTree->Branch("RXe",  RXe,  "RXe[16]/D");
outTree->Branch("RXt",  RXt,  "RXt[16]/D");
outTree->Branch("RXn",  RXn,  "RXn[16]/I");
outTree->Branch("mRY",  &mRY, "mRY/I");
outTree->Branch("RYe",  RYe,  "RYe[16]/D");
outTree->Branch("RYt",  RYt,  "RYt[16]/D");
outTree->Branch("RYn",  RYn,  "RYn[16]/I");
outTree->Branch("Lec",  Lec,  "Lec[16]/D");
outTree->Branch("Let",  Let,  "Let[16]/D");
outTree->Branch("Rec",  Rec,  "Rec[16]/D");
outTree->Branch("Ret",  Ret,  "Ret[16]/D");
outTree->Branch("mLE",  &mLE, "mLE/I");		// Lyso
outTree->Branch("LE",  LE,  "LE[16]/D");
outTree->Branch("LT",  LT,  "LT[16]/D");
outTree->Branch("Ln",  Ln,  "Ln[16]/I");
outTree->Branch("mRE",  &mRE, "mRE/I");		// CsI
outTree->Branch("RE",  RE,  "RE[16]/D");
outTree->Branch("RT",  RT,  "RT[16]/D");
outTree->Branch("Rn",  Rn,  "Rn[16]/I");

outTree->Branch("trigger", &trigger, "trigger/I");
//
mass_Beam = mass_Be10;
Beam_A = 10;
Beam_Z = 4;

s_Nel = 1;
A[0]=28;
Z[0]=14;
W[0]=1;
Beam_Si_elo = new ELC(Beam_A,Beam_Z,s_Nel,2.35,A,Z,W,2000.,5000);

s_Nel = 1;
A[0]=1;
Z[0]=1;
W[0]=1;
Beam_H_elo= new ELC(Beam_A,Beam_Z,s_Nel,rho_target,A,Z,W,2000.,5000); 

s_Nel = 1;
A[0]=56;
Z[0]=26;
W[0]=1;
Beam_Fe_elo= new ELC(Beam_A,Beam_Z,s_Nel,7.874,A,Z,W,2000.,5000);

Double_t tF3_offset[4] = {55., 0., -5.6, 1.};
Double_t tF6_offset[4] = {0.0,-16.8 ,-113.3, -103.7};

Long64_t nEntries = inTree->GetEntries();
//nEntries = 100;

short counter = 0;
//Long64_t mwpc_count=0, trig_count=0, tof_range_count=0, F6_count=0;
Long64_t Scaler[16];
for (int iii=0; iii<16; iii++)
  {
    Scaler[iii] = 0.;
  }

printf("##############################################################################\n");
printf("#Loaded files have %lli entries. \n#Processing...\n", nEntries);
for (Long64_t entry = 0; entry<nEntries; entry++)
//for (Long64_t entry = 1000000; entry<1000100; entry++)
{
  inTree->GetEntry(entry);
  if( entry % ( nEntries / 10 ) == 0)
    {
      printf("#Progress: %i%%\n",counter);
      counter+=10;
    }

  for (int iii=0; iii<4; iii++)
  {
    tF3[iii] =  (Double_t) itF3[iii]   + gRandom->Uniform() + tF3_offset[iii];
    F3[iii] =   (Double_t) iFocus3[iii]    + gRandom->Uniform();
    tF5[iii] =  (Double_t) itF5[iii]   + gRandom->Uniform();
    F5[iii] =   (Double_t) iF5[iii]    + gRandom->Uniform();
    tF6[iii] =  (Double_t) itF6[iii]   + gRandom->Uniform() + tF6_offset[iii];
    F6[iii] =   (Double_t) iF6[iii]    + gRandom->Uniform();
    tMWPC[iii]= (Double_t) itMWPC[iii] + gRandom->Uniform();
  }
  af3 = (F3[0]+F3[1]+F3[2]+F3[3])/4.;
  af5 = (F5[0]+F5[1]+F5[2]+F5[3])/4.;
  af6 = (F6[0]+F6[1]+F6[2]+F6[3])/4.;
  
  tF3[4] = 0.;
  tF5[4] = 0.;
  tF6[4] = 0.;

  if(abs(tF3[0]-tF3[1])<50 && abs(tF3[0]-tF3[2])<50 && abs(tF3[0]-tF3[3])<50 &&
      itF3[0] && itF3[1] && itF3[2] && itF3[3] && af3 > 1.)
      tF3[4] = (tF3[0]+tF3[1]+tF3[2]+tF3[3]+4.*gRandom->Uniform())/4.;

  if(abs(tF5[0]-tF5[1])<50 && abs(tF5[0]-tF5[2])<50 && abs(tF5[0]-tF5[3])<50 &&
      itF5[0] && itF5[1] && itF5[2] && itF5[3] && af5 > 1.)
      tF5[4] = (tF5[0]+tF5[1]+tF5[2]+tF5[3]+4.*gRandom->Uniform())/4.;

  if(abs(tF6[0]-tF6[1])<50 && abs(tF6[0]-tF6[2])<50 && abs(tF6[0]-tF6[3])<50 &&
      itF6[0]>0 && itF6[1]>0 && itF6[2]>0 && itF6[3]>0 && af6 > 1.)
      tF6[4] = (tF6[0]+tF6[1]+tF6[2]+tF6[3]+4.*gRandom->Uniform())/4.;

  timeF3 = tF3[4]*0.03125;
  timeF5 = tF5[4]*0.03125;
  timeF6 = tF6[4]*0.03125;
  
  ToF = 0.;
  tBeam = 0.;

  if(timeF3*timeF5!=0)
  {
    ToF 	= timeF5 - timeF3 + ToF_offset; 
  }
  if(ToF>170.&&ToF<210.)
  {
    BeamTimeAtTarget = timeF5;	// start calcul. of time of beam at target
       
    Double_t beta = ((ToF_base/ToF)/Light_S);
    Double_t gamma=1/sqrt(1-beta*beta);
    Double_t pBeam;
    Double_t dt;
//printf("  time at F5: %f\n", BeamTimeAtTarget);			// time at F5.
    
    tBeam = mass_Beam*(gamma-1.0);

//printf("  T before F5: %f\n", tBeam);			// beam energy before F5 sci.
    tBeam = Beam_Si_elo->GetE(tBeam,F5Pl_thick);
//printf("  T after F5: %f\n", tBeam);			// beam energy before MWPC1
    pBeam = sqrt(tBeam*tBeam + 2.*tBeam*mass_Beam);
    beta = pBeam/(tBeam + mass_Beam);
    dt = F5Pl_MWPC1_base/(beta*Light_S);
    BeamTimeAtTarget = BeamTimeAtTarget + dt;

    tBeam = Beam_Si_elo->GetE(tBeam,MWPC_thick);
//printf("  T after MW1: %f\n", tBeam);			// beam energy before MWPC2
    pBeam = sqrt(tBeam*tBeam + 2.*tBeam*mass_Beam);
    beta = pBeam/(tBeam + mass_Beam);
    dt = MWPC1_MWPC2_base/(beta*Light_S);
    BeamTimeAtTarget = BeamTimeAtTarget + dt;

    tBeam = Beam_Si_elo->GetE(tBeam,MWPC_thick);
//printf("  T after MW2: %f\n", tBeam);		// beam energy before target
    pBeam = sqrt(tBeam*tBeam + 2.*tBeam*mass_Beam);
    beta = pBeam/(tBeam + mass_Beam);
    dt = MWPC2_Target_base/(beta*Light_S);
    BeamTimeAtTarget = BeamTimeAtTarget + dt;

    tBeam = Beam_Fe_elo->GetE(tBeam,Target_window_thick);
//printf("  T after target window : %f\n", tBeam);		// beam energy before target 
    tBeam = Beam_H_elo->GetE(tBeam,Target_thick);
//printf("  T at center of target: %f\n\n", tBeam);		// beam energy in the center of target
    tBeamC = Beam_H_elo->GetE(tBeam,Target_thick);
//printf("  T at end of target: %f\n", tBeamC);		// beam energy after target
    tBeamC = Beam_Fe_elo->GetE(tBeamC,Target_window_thick);
//printf("  T after target window: %f\n\n", tBeamC);		// beam energy after target window

  }
  Int_t Lyso_offset[16] = {161,213,162,204,164,209,171,206,159,0,0,0,0,0,0,0};
  Int_t  CsI_offset[16] = {150,213,155,207,155,203,156,206,
                           157,197,167,189,169,190,174,195};

  for (int iii=0; iii<16; iii++)
  {
     Rxt[iii]  = 0.125*((Double_t) iRxt[iii]  + gRandom->Uniform()) - BeamTimeAtTarget;
     Ryt[iii]  = 0.125*((Double_t) iRyt[iii]  + gRandom->Uniform()) - BeamTimeAtTarget;
     Ret[iii]  = 0.125*((Double_t) iRet[iii]  + gRandom->Uniform()) - BeamTimeAtTarget;
     Rec[iii]  = Rec[iii] - CsI_offset[iii];
  }
  for (int iii=0; iii<32; iii++)
  {
     Lxt[iii]  = 0.125*((Double_t) iLxt[iii]  + gRandom->Uniform()) - BeamTimeAtTarget;
     Lyt[iii]  = 0.125*((Double_t) iLyt[iii]  + gRandom->Uniform()) - BeamTimeAtTarget;
     if(iii<16) Lyt[iii] = Lyt[iii] +100.;
  }
  
  for (int iii=0; iii<9; iii++)
  {
     Let[iii]  = 0.125*((Double_t) iLet[iii]  + gRandom->Uniform()) - BeamTimeAtTarget;
     Lec[iii]  = Lec[iii] - Lyso_offset[iii];
  }
  mLX = 0;
  mLY = 0;
  mRX = 0;
  mRY = 0;
  mLE = 0;
  mRE = 0;
  Double_t si_thresh = 0.5;
  Double_t lyso_thresh = 0.5;
  for (int iii=0; iii<32; iii++)
  {
    if(Lxt[iii]>-50&&Lxt[iii]<150 && Lxc[iii] > si_thresh)
    {
      LXe[mLX] = Lxc[iii];	
      LXt[mLX] = Lxt[iii];
      LXn[mLX] = iii;
      mLX++;
    }
    if(Lyt[iii]>-50&&Lyt[iii]<150 && Lyc[iii] > si_thresh)
    {
      LYe[mLY] = Lyc[iii];	
      LYt[mLY] = Lyt[iii];
      LYn[mLY] = iii;
      mLY++;
    }
  }  
  for (int iii=0; iii<16; iii++)
  {
    if(Rxt[iii]>-50&&Rxt[iii]<150 && Rxc[iii] > si_thresh)
    {
      RXe[mRX] = Rxc[iii];	
      RXt[mRX] = Rxt[iii];
      RXn[mRX] = iii;
      mRX++;
    }
    if(Ryt[iii]>-50&&Ryt[iii]<150 && Ryc[iii] > si_thresh)
    {
      RYe[mRY] = Ryc[iii];	
      RYt[mRY] = Ryt[iii];
      RYn[mRY] = iii;
      mRY++;
    }
  }
  for (int iii=0; iii<9; iii++)
  {  
    if(Let[iii]>-105&&Let[iii]<-85 && Lec[iii] > lyso_thresh)
    {
      LE[mLE] = Lec[iii];	
      LT[mLE] = Let[iii];
      Ln[mLE] = iii;
      mLE++;
    }
  }
//______________________________________________________MWPC tracking
    mcx1 = GetClasters(nx1,ix1);
    mcy1 = GetClasters(ny1,iy1);
    mcx2 = GetClasters(nx2,ix2);
    mcy2 = GetClasters(ny2,iy2);

    f_track = false;  

    if(mcx1*mcy1*mcx2*mcy2==1)
    {
      f_track = true;  

    for (int iii=0; iii<4; iii++)
      {
	tMWPC[iii] = tMWPC[iii]*0.03125 - BeamTimeAtTarget;
	if(tMWPC[iii]<20 || tMWPC[iii]>100) f_track=false;
      }

      mwx1 = 16*1.25 - GetPosMW(nx1,ix1) + MWPC1_Xoff;
      mwy1 = GetPosMW(ny1,iy1) - 16*1.25 + MWPC1_Yoff;
//
      mwx2 = 16*1.25 - GetPosMW(nx2,ix2) + MWPC2_Xoff;
      mwy2 = GetPosMW(ny2,iy2) - 16*1.25 + MWPC2_Yoff;
//_____________ beam angles      

      TVector3 track;
      track.SetXYZ(mwx2-mwx1,mwy2-mwy1,MWPC1_MWPC2_base);
      ThetaBeam = track.Theta();
      PhiBeam   = track.Phi();

//      printf("  theta : %f  phi: %f \n\n\n",track.Theta()/D2Rad,track.Phi()/D2Rad);

      xbt = mwx2 + MWPC2_Target_base*tan(ThetaBeam)*cos(PhiBeam);
      ybt = mwy2 + MWPC2_Target_base*tan(ThetaBeam)*sin(PhiBeam);
//	printf("  xbt: %f  ybt: %f \n",xbt,ybt);

      xbd = mwx2 + (MWPC2_Target_base+Zdia)*tan(ThetaBeam)*cos(PhiBeam);
      ybd = mwy2 + (MWPC2_Target_base+Zdia)*tan(ThetaBeam)*sin(PhiBeam);


    }

  
  if(f_track)  
  
  {

      outTree->Fill();
  }

}	// for (Long64_t entry=0; entry<nEntries; entry++)
outTree->Write();

outF->Close();

return 1;
}

