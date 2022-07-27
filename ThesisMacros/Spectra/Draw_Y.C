void DivideByBinWidth(TH1D* Hist) {
  for (int xBin=1;xBin<=Hist->GetNbinsX();xBin++) {
    Hist->SetBinContent(xBin,Hist->GetBinContent(xBin)/Hist->GetXaxis()->GetBinWidth(xBin));
  }
}

void Draw_Y() {
  
  TString FileName = "../../MacroInputs/Spectra/SpectraByMode.root";
  TFile* File = new TFile(FileName);

  TCanvas* Canv = new TCanvas("Canv","");
  Canv->SetLeftMargin(0.15);
  Canv->SetBottomMargin(0.15);
  
  TDirectory* Dir;
  TKey *Key;
  TIter Next(File->GetListOfKeys());
  while ((Key=(TKey*)Next())) {
    TClass *Cl = gROOT->GetClass(Key->GetClassName());
    if (Cl->InheritsFrom("TDirectory")) {
      Dir = (TDirectory*)Key->ReadObj();
      Dir->cd();

      TString SampleName = Key->GetName();
      
      TH2D* CCQE_2D = (TH2D*)Dir->Get("CCQE");
      TH1D* CCQE_1D = (TH1D*)(CCQE_2D->ProjectionY())->Clone();
      CCQE_1D->SetFillColor(kCyan);
      CCQE_1D->SetLineColor(kBlack);
      
      TH2D* MEC_2D = (TH2D*)Dir->Get("2p2h");
      TH1D* MEC_1D = (TH1D*)(MEC_2D->ProjectionY())->Clone();
      MEC_1D->SetFillColor(kBlue);
      MEC_1D->SetLineColor(kBlack);
      
      TH2D* CCRES_2D = (TH2D*)Dir->Get("CC1pipm");
      TH1D* CCRES_1D = (TH1D*)(CCRES_2D->ProjectionY())->Clone();
      CCRES_1D->SetFillColor(kMagenta);
      CCRES_1D->SetLineColor(kBlack);
	    
      TH2D* CCMPi_2D = (TH2D*)Dir->Get("CCMpi");
      TH1D* CCMPi_1D = (TH1D*)(CCMPi_2D->ProjectionY())->Clone();
      CCMPi_1D->SetFillColor(kRed);
      CCMPi_1D->SetLineColor(kBlack);
	    
      TH2D* CCOther_2D = (TH2D*)Dir->Get("CCcoh");
      CCOther_2D->Add((TH2D*)Dir->Get("CCDIS"));
      CCOther_2D->Add((TH2D*)Dir->Get("CCMisc"));
      CCOther_2D->Add((TH2D*)Dir->Get("CC1pi0"));
      TH1D* CCOther_1D = (TH1D*)(CCOther_2D->ProjectionY())->Clone();
      CCOther_1D->SetFillColor(kOrange);
      CCOther_1D->SetLineColor(kBlack);

      TH2D* NCPi0_2D = (TH2D*)Dir->Get("NC1pi0");
      TH1D* NCPi0_1D = (TH1D*)(NCPi0_2D->ProjectionY())->Clone();
      NCPi0_1D->SetFillColor(kGray);
      NCPi0_1D->SetLineColor(kBlack);
      
      /*
      TH2D* NCRES_2D = (TH2D*)Dir->Get("NC1pipm");
      TH1D* NCRES_1D = (TH1D*)(NCRES_2D->ProjectionY())->Clone();
      NCRES_1D->SetFillColor(kGray);
      
      TH2D* NCMPi_2D = (TH2D*)Dir->Get("NCMpi");
      TH1D* NCMPi_1D = (TH1D*)(NCMPi_2D->ProjectionY())->Clone();
      NCMPi_1D->SetFillColor(kGray);
      
      TH2D* NCCoh_2D = (TH2D*)Dir->Get("NCcoh");
      TH1D* NCCoh_1D = (TH1D*)(NCCoh_2D->ProjectionY())->Clone();
      NCCoh_1D->SetFillColor(kGray);
      
      TH2D* NCOther_2D = (TH2D*)Dir->Get("NCoth");
      NCOther_2D->Add((TH2D*)Dir->Get("NC1gam"));
      NCOther_2D->Add((TH2D*)Dir->Get("NCDIS"));
      TH1D* NCOther_1D = (TH1D*)(NCOther_2D->ProjectionY())->Clone();
      NCOther_1D->SetFillColor(kGray);
      */

      TH2D* NCOther_2D = (TH2D*)Dir->Get("NCoth");
      NCOther_2D->Add((TH2D*)Dir->Get("NC1gam"));
      NCOther_2D->Add((TH2D*)Dir->Get("NC1pipm"));
      NCOther_2D->Add((TH2D*)Dir->Get("NCMpi"));
      NCOther_2D->Add((TH2D*)Dir->Get("NCcoh"));
      NCOther_2D->Add((TH2D*)Dir->Get("NCDIS"));
      TH1D* NCOther_1D = (TH1D*)(NCOther_2D->ProjectionY())->Clone();
      NCOther_1D->SetFillColor(kGray+2);    
      NCOther_1D->SetLineColor(kBlack);

      if (SampleName == "FHC1Rmu-2020" || SampleName == "RHC1Rmu-2020" || SampleName == "FHC1Re-2020" || SampleName == "RHC1Re-2020" || SampleName == "FHCCC1pi-2020") {
	DivideByBinWidth(CCQE_1D);
	DivideByBinWidth(MEC_1D);
	DivideByBinWidth(CCRES_1D);
	DivideByBinWidth(CCMPi_1D);
	DivideByBinWidth(CCOther_1D);
	DivideByBinWidth(NCPi0_1D);
	DivideByBinWidth(NCOther_1D);
      }
      
      THStack* Stack = new THStack(SampleName,"");
      Stack->Add(CCQE_1D);
      Stack->Add(MEC_1D);
      Stack->Add(CCRES_1D);
      Stack->Add(CCMPi_1D);
      Stack->Add(CCOther_1D);
      /*
      Stack->Add(NCRES_1D);
      Stack->Add(NCMPi_1D);
      Stack->Add(NCCoh_1D);
      */
      Stack->Add(NCPi0_1D);
      Stack->Add(NCOther_1D);

      /*
      SubGeV-elike-0dcy
      SubGeV-elike-1dcy
      SubGeV-mulike-0dcy
      SubGeV-mulike-1dcy
      SubGeV-mulike-2dcy
      SubGeV-pi0like
      MultiGeV-elike-nue
      MultiGeV-elike-nuebar
      MultiGeV-mulike
      MultiRing-elike-nue
      MultiRing-elike-nuebar
      MultiRing-mulike
      MultiRingOther-1
      PCStop
      PCThru
      UpStop-mu
      UpThruNonShower-mu
      UpThruShower-mu
      FHC1Rmu-2020
      RHC1Rmu-2020
      FHC1Re-2020
      RHC1Re-2020
      FHCCC1pi-2020
      */
      
      Stack->Draw("hist");

      Stack->GetXaxis()->SetTitleSize(0.05);
      Stack->GetYaxis()->SetTitleSize(0.05);

      //Stack->SetTitle(SampleName);
      Stack->GetXaxis()->SetTitle(CCQE_1D->GetXaxis()->GetTitle());
      Stack->GetXaxis()->SetTitleOffset(1.1);
      Stack->GetYaxis()->SetTitle("Events/Bin");

      Canv->Modified();
      Canv->Print(SampleName+"_Y.pdf");
    }
  }
}
