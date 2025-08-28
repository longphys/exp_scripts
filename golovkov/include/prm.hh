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
//
Double_t mass_n	= 939.565;
Double_t mass_p	= 938.272;
Double_t mass_d	= 1875.61;
Double_t mass_He6	= 5605.54;
Double_t mass_He8	= 7482.53;
Double_t mass_Li9	= 8406.87;
Double_t mass_Be10 	= 9325.5;
Double_t Light_S	= 299.792458; 		// Speed of Light (mm/ns)
Double_t D2Rad		= TMath::Pi()/180.;
//
//		Central Si-Lyso telescope
Double_t SiSqThick	= 250.;		// thickness of Si detector 		(um)
Double_t SiSqDeadL	= 2.4;			// nom thickness of Si dead layer 	(um)
Double_t SiSqSize	= 93.2;		// active area size	 		(mm)
Double_t SiSqZ		= 252.2;		// Si Square telescope Z position 	(mm) 
Double_t SiSq_Xoff	= -3.0;		//Si Square X offsets 			(mm)
Double_t SiSq_Yoff	= -3.0;		//Si Square Y offsets 			(mm)
Int_t SiSqNx		= 32;			// number of strips x
Int_t SiSqNy		= 32;			// number of strips y
Double_t SiSqWx	= SiSqSize/SiSqNx;	// x strip width 			(mm)
Double_t SiSqWy	= SiSqSize/SiSqNy;	// y strip width 			(mm)
//
//		Anular telescope
Double_t AnDeadL	= 2.4;			// nom thickness of Si dead layer 	(um)
Double_t AnRin = 16.0;		// all sizes in mm
Double_t AnRout = 62.5;
Double_t AnZpos = -63.;
Double_t AnPhiW  = 360./64.;
Double_t AnDr = (AnRout - AnRin)/16;
//AnDr = (AnRout - AnRin)/16;
//AnPhiW = 360./64.;


