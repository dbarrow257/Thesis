void DivideByBinWidth(TH1D* Hist) {
  for (int xBin=1;xBin<=Hist->GetNbinsX();xBin++) {
    Hist->SetBinContent(xBin,Hist->GetBinContent(xBin)/Hist->GetXaxis()->GetBinWidth(xBin));
  }
}

void Draw_X() {
  bool DrawLegend = true;
  
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
      TH1D* CCQE_1D = (TH1D*)(CCQE_2D->ProjectionX())->Clone();
      CCQE_1D->SetFillColor(kCyan);
      CCQE_1D->SetLineColor(kBlack);
      
      TH2D* MEC_2D = (TH2D*)Dir->Get("2p2h");
      TH1D* MEC_1D = (TH1D*)(MEC_2D->ProjectionX())->Clone();
      MEC_1D->SetFillColor(kBlue);
      MEC_1D->SetLineColor(kBlack);
      
      TH2D* CCRES_2D = (TH2D*)Dir->Get("CC1pipm");
      TH1D* CCRES_1D = (TH1D*)(CCRES_2D->ProjectionX())->Clone();
      CCRES_1D->SetFillColor(kMagenta);
      CCRES_1D->SetLineColor(kBlack);
	    
      TH2D* CCMPi_2D = (TH2D*)Dir->Get("CCMpi");
      TH1D* CCMPi_1D = (TH1D*)(CCMPi_2D->ProjectionX())->Clone();
      CCMPi_1D->SetFillColor(kRed);
      CCMPi_1D->SetLineColor(kBlack);
	    
      TH2D* CCOther_2D = (TH2D*)Dir->Get("CCcoh");
      CCOther_2D->Add((TH2D*)Dir->Get("CCDIS"));
      CCOther_2D->Add((TH2D*)Dir->Get("CCMisc"));
      CCOther_2D->Add((TH2D*)Dir->Get("CC1pi0"));
      TH1D* CCOther_1D = (TH1D*)(CCOther_2D->ProjectionX())->Clone();
      CCOther_1D->SetFillColor(kOrange);
      CCOther_1D->SetLineColor(kBlack);

      TH2D* NCPi0_2D = (TH2D*)Dir->Get("NC1pi0");
      TH1D* NCPi0_1D = (TH1D*)(NCPi0_2D->ProjectionX())->Clone();
      NCPi0_1D->SetFillColor(kGray);
      NCPi0_1D->SetLineColor(kBlack);
      
      /*
      TH2D* NCRES_2D = (TH2D*)Dir->Get("NC1pipm");
      TH1D* NCRES_1D = (TH1D*)(NCRES_2D->ProjectionX())->Clone();
      NCRES_1D->SetFillColor(kGray);
      
      TH2D* NCMPi_2D = (TH2D*)Dir->Get("NCMpi");
      TH1D* NCMPi_1D = (TH1D*)(NCMPi_2D->ProjectionX())->Clone();
      NCMPi_1D->SetFillColor(kGray);
      
      TH2D* NCCoh_2D = (TH2D*)Dir->Get("NCcoh");
      TH1D* NCCoh_1D = (TH1D*)(NCCoh_2D->ProjectionX())->Clone();
      NCCoh_1D->SetFillColor(kGray);
      
      TH2D* NCOther_2D = (TH2D*)Dir->Get("NCoth");
      NCOther_2D->Add((TH2D*)Dir->Get("NC1gam"));
      NCOther_2D->Add((TH2D*)Dir->Get("NCDIS"));
      TH1D* NCOther_1D = (TH1D*)(NCOther_2D->ProjectionX())->Clone();
      NCOther_1D->SetFillColor(kGray);
      */

      TH2D* NCOther_2D = (TH2D*)Dir->Get("NCoth");
      NCOther_2D->Add((TH2D*)Dir->Get("NC1gam"));
      NCOther_2D->Add((TH2D*)Dir->Get("NC1pipm"));
      NCOther_2D->Add((TH2D*)Dir->Get("NCMpi"));
      NCOther_2D->Add((TH2D*)Dir->Get("NCcoh"));
      NCOther_2D->Add((TH2D*)Dir->Get("NCDIS"));
      TH1D* NCOther_1D = (TH1D*)(NCOther_2D->ProjectionX())->Clone();
      NCOther_1D->SetFillColor(kGray+2);    
      NCOther_1D->SetLineColor(kBlack);

      if (SampleName == "FHC1Rmu-2020" || SampleName == "RHC1Rmu-2020") {
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
      
      if (SampleName == "MultiGeV-elike-nue" || SampleName == "MultiGeV-elike-nuebar" || SampleName == "MultiGeV-mulike" || SampleName == "MultiRing-elike-nue" || SampleName == "MultiRing-elike-nuebar" || SampleName == "MultiRing-mulike" || SampleName == "MultiRingOther-1" || SampleName == "PCStop" || SampleName == "PCThru" || SampleName == "UpStop-mu" || SampleName == "UpThruNonShower-mu" || SampleName == "UpThruShower-mu") {
	Canv->SetLogx(true);
      } else {
	Canv->SetLogx(false);
      }
      
      Stack->Draw("hist");

      Stack->GetXaxis()->SetTitleSize(0.05);
      Stack->GetYaxis()->SetTitleSize(0.05);

      //Stack->SetTitle(SampleName);
      Stack->GetXaxis()->SetTitle(CCQE_1D->GetXaxis()->GetTitle());
      Stack->GetXaxis()->SetTitleOffset(1.1);
      Stack->GetYaxis()->SetTitle("Events/Bin");

      if (SampleName == "FHC1Rmu-2020" || SampleName == "RHC1Rmu-2020") {
	Stack->GetXaxis()->SetRangeUser(0.,3.0);
      }
      
      Canv->Modified();
      Canv->Print(SampleName+"_X.pdf");

      if (DrawLegend) {
	TCanvas* LegendCanv = new TCanvas("LegendCanv","");
	TLegend* Legend = new TLegend(0.1,0.1,0.9,0.9);
	Legend->AddEntry(CCQE_1D,"CCQE","f");
	Legend->AddEntry(MEC_1D,"2p2h","f");
	Legend->AddEntry(CCRES_1D,"CC1#pi^{#pm}","f");
	Legend->AddEntry(CCMPi_1D,"CCM#pi","f");
	Legend->AddEntry(CCOther_1D,"CC Other","f");
	Legend->AddEntry(NCPi0_1D,"NC1#pi^{0}","f");
	Legend->AddEntry(NCOther_1D,"NC Other","f");
	
	Legend->Draw();
	LegendCanv->Print("Legend.pdf");
	DrawLegend = false;
      }
    }
    
    Canv->Clear();
  }
}
