#ifndef cleaner_h
#define cleaner_h 1

#include <iostream>
#include <vector>
#include <stdio.h>
#include "TFile.h"
#include "TObjArray.h"
#include "TTree.h"
#include "Riostream.h"
#include <TString.h>
#include <TRandom3.h>
//
//For ELC library____________________________________

#include "/home/golovkov/ELC/AELC.h"
#include "/home/golovkov/ELC/ELC.h"
R__LOAD_LIBRARY(/home/golovkov/ELC/libEloss.so);
//
AELC *Beam_Si_elo;
AELC *Beam_H_elo;
AELC *Beam_Fe_elo;
AELC *p_Si_elo;
AELC *p_H_elo;
AELC *p_Fe_elo;
//
Double_t A[10], Z[10], W[10];
Int_t s_Nel;
Int_t Beam_A, Beam_Z;
Double_t mass_Beam;
//
Bool_t Analysis;
Bool_t f_track, f_ToF;  
//
Double_t  tBeam;
Double_t  tBeamC;
TLorentzVector *lvBeam; 
Double_t BeamTimeAtTarget;
Double_t ThetaBeam;
Double_t PhiBeam;

//input Tree___________________________________
TTree *inTree;
UShort_t  iSa[16];
UShort_t  iSt[16];
UShort_t  iRa[16];
UShort_t  iRt[16];
UShort_t  iS2a[16];
UShort_t  iS2t[16];
UShort_t  iVa[16];
UShort_t  iVt[16];
UShort_t  iRxa[16];
UShort_t  iRxt[16];
UShort_t  iRya[16];
UShort_t  iRyt[16];
UShort_t  iLxa[32];
UShort_t  iLxt[32];
UShort_t  iLya[32];
UShort_t  iLyt[32];
UShort_t  iCxa[16];
UShort_t  iCxt[16];
UShort_t  iCya[16];
UShort_t  iCyt[16];
UShort_t  iLea[16];
UShort_t  iLet[16];
UShort_t  iRea[16];
UShort_t  iRet[16];
UShort_t  iF3[4];
UShort_t  iFocus3[4];
UShort_t  itF3[4];
UShort_t  iF5[4];
UShort_t  itF5[4];
UShort_t  iF6[4];
UShort_t  itF6[4];
UShort_t  itMWPC[4];
UInt_t  scaler[16];
//
UShort_t  nx1;
UShort_t  ny1;
UShort_t  nx2;
UShort_t  ny2;
UShort_t  ix1[32];
UShort_t  iy1[32];
UShort_t  ix2[32];
UShort_t  iy2[32];
//
Double_t  af3;
Double_t  af5;
Double_t  af6;
Double_t  ToF;
Double_t  xbt;
Double_t  ybt;
Double_t  xbd;
Double_t  ybd;
Double_t mwx1,mwy1;
Double_t mwx2,mwy2;

Double_t  Sc[16];
Double_t  Rc[16];
Double_t  S2c[16];
Double_t  Vc[16];
Double_t  Rxc[16];
Double_t  Ryc[16];
Double_t  Lxc[32];
Double_t  Lyc[32];
Double_t  Cxc[16];
Double_t  Cyc[16];
Double_t  Rec[16];
Double_t  Lec[16];
//
UInt_t  nevent;
UInt_t  trigger;
//____________________________________________
//output Tree___________________________________
Double_t  Lxt[32];
Double_t  Lyt[32];
Double_t  Rxt[16];
Double_t  Ryt[16];
Double_t  Let[16];
Double_t  Ret[16];

Int_t  mLX;
Double_t  LXe[32];
Double_t  LXt[32];
Int_t  LXn[32];
Int_t  mLY;
Double_t  LYe[32];
Double_t  LYt[32];
Int_t  LYn[32];
Int_t  mRX;
Double_t  RXe[16];
Double_t  RXt[16];
Int_t  RXn[16];
Int_t  mRY;
Double_t  RYe[16];
Double_t  RYt[16];
Int_t  RYn[16];
Int_t  mLE;		// Lyso
Double_t  LE[16];
Double_t  LT[16];
Int_t  Ln[16];
Int_t  mRE;		// CsI
Double_t  RE[16];
Double_t  RT[16];
Int_t  Rn[16];

//_______________________________
Double_t F3[5];
Double_t tF3[5];
Double_t F5[5];
Double_t tF5[5];
Double_t F6[5];
Double_t tF6[5];
Double_t tMWPC[4];
Double_t  timeF3;
Double_t  timeF5;
Double_t  timeF6;
//_______________________tracking
UShort_t  mcx1;
UShort_t  mcy1;
UShort_t  mcx2;
UShort_t  mcy2;

#endif

