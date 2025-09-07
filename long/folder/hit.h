#ifndef cleaner_h
#define cleaner_h 
#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include "TFile.h"
#include "TObjArray.h"
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TString.h"
#include "TRandom3.h"
#include "TLorentzVector.h"
#include "Riostream.h"

// Energy loss library
#include "/home/long/ELC/AELC.h"
#include "/home/long/ELC/ELC.h"
R__LOAD_LIBRARY(/home/long/ELC/libEloss.so);

//! Variables to be read from the input tree
//! Variables that will be changed/refilled in the loop will have "NeEvent_" prefix)

UShort_t  iSa[16];
UShort_t  iSt[16];
UShort_t  iRa[16];
UShort_t  iRt[16];
UShort_t  iS2a[16];
UShort_t  iS2t[16];
UShort_t  iVa[16];
UShort_t  iVt[16];

// Right silicon
    // amplitude and time branches
UShort_t  NeEvent_Rxa[16];
UShort_t  NeEvent_Rxt[16];
UShort_t  NeEvent_Rya[16];
UShort_t  NeEvent_Ryt[16];
    // energy calibrated branches
Double_t  NeEvent_Rxc[16];
Double_t  NeEvent_Ryc[16];

// Left silicon
UShort_t  NeEvent_Lxa[32];
UShort_t  NeEvent_Lxt[32];
UShort_t  NeEvent_Lya[32];
UShort_t  NeEvent_Lyt[32];
Double_t  NeEvent_Lxc[32];
Double_t  NeEvent_Lyc[32];

// Center telescope
UShort_t  iCxa[16];
UShort_t  iCxt[16];
UShort_t  iCya[16];
UShort_t  iCyt[16];

// Left scintillator: amplitude and time
UShort_t  NeEvent_Lea[16];
UShort_t  NeEvent_Let[16];

// Right scintillator
UShort_t  NeEvent_Rea[16];
UShort_t  NeEvent_Ret[16];

// Focal plane scintillators and MWPC
UShort_t  NeEvent_F3[4];
UShort_t  NeEvent_tF3[4];
UShort_t  NeEvent_F5[4];
UShort_t  NeEvent_tF5[4];
UShort_t  NeEvent_F6[4];
UShort_t  NeEvent_tF6[4];
UShort_t  itMWPC[4];
UInt_t    scaler[16];

// ?
UShort_t  nx1;
UShort_t  ny1;
UShort_t  nx2;
UShort_t  ny2;
UShort_t  ix1[32];
UShort_t  iy1[32];
UShort_t  ix2[32];
UShort_t  iy2[32];

// ToF, dE at ToF plastics, and MWPC variables
Double_t  af3;
Double_t  af5;
Double_t  af6;
Double_t  ToF;
Double_t  xbt;
Double_t  ybt;
Double_t  xbd;
Double_t  ybd;

// Variables for MWPC position calculation
Double_t mwx1,mwy1;
Double_t mwx2,mwy2;

// Unused calibrated variables
Double_t  Sc[16];
Double_t  Rc[16];
Double_t  S2c[16];
Double_t  Vc[16];
Double_t  Cxc[16];
Double_t  Cyc[16];
Double_t  Rec[16];
Double_t  Lec[16];

// Event number and trigger number
UInt_t  nevent;
UInt_t  trigger;

//! New variables to be saved
// while charge values are stored in array of 4 elements (4 PMTs)
// time values are stored in array of 5 elements, last element is reserved for new calculation.
Double_t  F3[4]    = {0.};
Double_t  tF3[5]   = {0.};
Double_t  F5[4]    = {0.};
Double_t  tF5[5]   = {0.};
Double_t  F6[4]    = {0.};
Double_t  tF6[5]   = {0.};

// Define hit structure variables
// Right x_strip silicon
Double_t Rxa[5] = {0.};      // Raw Amplitude (Top 5)
Double_t Rxc[5] = {0.};     // Calibrated energy（Top 5）
Double_t Rxt[5] = {0.};     // Time（Sorted by descending energy）
Int_t Rxa_n[5]  = {-1};        // Corresponding strip number (channel number)
Int_t Rxa_hits = 0;           // Actual effective hit number

// Right y_strip silicon
Double_t Rya[5] = {0.};      
Double_t Ryc[5] = {0.};    
Double_t Ryt[5] = {0.};   
Int_t Rya_n[5]  = {-1};     
Int_t Rya_hits = 0;        

// Left x_strip silicon
Double_t Lxa[5] = {0.};    
Double_t Lxc[5] = {0.};   
Double_t Lxt[5] = {0.};   
Int_t Lxa_n[5]  = {-1};     
Int_t Lxa_hits = 0;        

// Left y_strip silicon
Double_t Lya[5] = {0.};   
Double_t Lyc[5] = {0.};  
Double_t Lyt[5] = {0.};    
Int_t Lya_n[5]  = {-1};     
Int_t Lya_hits = 0;        

// Right scintillator crystals
Double_t Rea[5] = {0};    
Double_t Ret[5] = {0};    
Int_t Rea_n[5] = {-1};    
Int_t Rea_hits = 0;         

// Left scintillator crystals
Double_t Lea[5] = {0};   
Double_t Let[5] = {0};  
Int_t Lea_n[5] = {-1};  
Int_t Lea_hits = 0;   

//! Important for calculation
// Temp variables
Double_t tF3c, tF5c, tF6c; // converted time values
Double_t tBeam; // Kinetic energy of the beam
Double_t  tBeamC; // Kinetic energy of the beam after the target
Double_t  tBeamS[10]; // energy of the beam after the silicon
Double_t BeamTimeAtTarget;

// Beam variables
AELC *Beam_Si_elo;
AELC *Beam_H_elo;
AELC *Beam_Fe_elo;
AELC *p_Si_elo;
AELC *p_H_elo;
AELC *p_Fe_elo;
Double_t A[10], Z[10], W[10];
Int_t s_Nel;
Int_t Beam_A, Beam_Z;
Double_t mass_Beam;

// Parameters
Double_t mass_n	= 939.565;
Double_t mass_p	= 938.272;
Double_t mass_d	= 1875.61;
Double_t mass_He6	= 5605.54;
Double_t mass_He8	= 7482.53;
Double_t mass_Li9	= 8406.87;
Double_t mass_Be10 	= 9325.5;
Double_t Light_S	= 299.792458; 		// Speed of Light (mm/ns)

Double_t tF3_offset[4] = {55., 0., -5.6, 1.};
Double_t tF6_offset[4] = {0.0,-16.8 ,-113.3, -103.7};
Double_t ToF_base		= 12388.;	//in mm
Double_t F5Pl_MWPC1_base	= 91.;		//in mm
Double_t MWPC1_Xoff		= 0.;		//MWPC offsets (mm)
Double_t MWPC1_Yoff		= 0.;		//MWPC offsets
Double_t MWPC2_Xoff		= 0.;		//MWPC offsets
Double_t MWPC2_Yoff		= 0.;		//MWPC offsets
Double_t MWPC1_MWPC2_base	= 544.;	//in mm
Double_t MWPC2_Target_base	= 269.5;	//in mm ???
Double_t F5Pl_thick		= 148.*1.0;	//nom sum F5 + 2*MWPC== 644. um (Si equiv)
Double_t MWPC_thick		= 248.*1.0;		
Double_t Target_window_thick	= 7.2 + 0.5;	// thickness of target window (Fe, um)
Double_t STPtarget_dens	= 8.3748e-5;
Double_t target_temp		= 30.;		// K
Double_t target_pres		= 1.;
Double_t rho_target = STPtarget_dens*target_pres*293.15/target_temp;
//Double_t rho_target		= 0.0013156/1.5;
Double_t Target_thick		= 3000.;	// half of target thickness  (H2 gas, um)
//Double_t ToF_offset		= 68.475;	//  (ns)
Double_t ToF_offset		= 68.475 + 0.250;		//  (ns)
Double_t Ztarget		= 0.;		// target    Z position (mm)
Double_t Zdia			= -145.;	// diaphragm Z position (mm)

// channels to ps
Double_t convert_time = 0.03125;

#endif