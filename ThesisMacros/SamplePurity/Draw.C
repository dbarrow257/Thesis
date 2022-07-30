void Draw() {
  TString FileName = "../../MacroInputs/SamplePurity/SamplePurity.root";
  TFile* File = new TFile(FileName);

  TH2D* Hist;
  
  TKey *Key;
  TIter Next(File->GetListOfKeys());
  while ((Key=(TKey*)Next())) {
    TClass *Cl = gROOT->GetClass(Key->GetClassName());
    if (Cl->InheritsFrom("TH2")) {
      Hist = (TH2D*)Key->ReadObj();
      TString SampleName = Key->GetName();

      //0 = CC nue
      //1 = CC nueb
      //2 = CC numu + numub
      //3 = CC nutau + nutaub
      //4 = NC
      //5 = Total
      
      int CCnue = 0;
      int CCnueb = 1;
      int CCnumu = 2;
      int CCnutau = 3;
      int NC = 4;
      int Total = 5;
      
      int nComponents = 6;
      std::vector<double> Components(nComponents);
      for (int iComp=0;iComp<nComponents;iComp++) {
	Components[iComp] = 0.;
      }
      Components[Total] = (double)Hist->Integral();
      
      int nOscChans = Hist->GetNbinsY();
      for (int iOscChan=0;iOscChan<nOscChans;iOscChan++) {
	
	double CCComp = 0;
	double NCComp = 0;
	
	int nModes = Hist->GetNbinsX();
	for (int iMode=0;iMode<nModes;iMode++) {
	  TString ModeName = Hist->GetXaxis()->GetBinLabel(iMode+1);
	  if (ModeName.Contains("NC")) {
	    NCComp += Hist->GetBinContent(iMode+1,iOscChan+1);
	  } else {
	    CCComp += Hist->GetBinContent(iMode+1,iOscChan+1);
	  }
	}

	Components[NC] += NCComp;
	
	//0  = nue_x_nue
	//1  = nueb_x_nueb
	//2  = numu_x_numu
	//3  = numub_x_numub
	//4  = nue_x_numu
	//5  = nueb_x_numub
	//6  = numu_x_nue
	//7  = numub_x_nueb
	//8  = nue_x_nutau
	//9  = nueb_x_nutaub
	//10 = numu_x_nutau
	//11 = numub_x_nutaub


	
	if (iOscChan == 0) Components[CCnue] += CCComp;
	if (iOscChan == 1) Components[CCnueb] += CCComp;
	if (iOscChan == 2) Components[CCnumu] += CCComp;
	if (iOscChan == 3) Components[CCnumu] += CCComp;
	if (iOscChan == 4) Components[CCnumu] += CCComp;
	if (iOscChan == 5) Components[CCnumu] += CCComp;
	if (iOscChan == 6) Components[CCnue] += CCComp;
	if (iOscChan == 7) Components[CCnueb] += CCComp;
	if (iOscChan == 8) Components[CCnutau] += CCComp;
	if (iOscChan == 9) Components[CCnutau] += CCComp;
	if (iOscChan == 10) Components[CCnutau] += CCComp;
	if (iOscChan == 11) Components[CCnutau] += CCComp;
	
      }

      /*
      std::cout << SampleName << std::endl;
      for (int iComp=0;iComp<nComponents;iComp++) {
	std::cout << "\t" << Components[iComp] << std::endl;
      }
      */
      
      for (int iComp=0;iComp<nComponents;iComp++) {
	Components[iComp] /= Components[Total];
	Components[iComp] *= 100.0;
      }
      
      std::cout.precision(4);
      
      std::cout << "\\texttt{" << SampleName << "} & \\quickmath{" << Components[CCnue] << "} & \\quickmath{" << Components[CCnueb]  << "} & \\quickmath{" << Components[CCnumu] << "} & \\quickmath{" << Components[CCnutau] << "} & \\quickmath{" << Components[NC] << "} \\\\" << std::endl;
      
    }
  }
}
