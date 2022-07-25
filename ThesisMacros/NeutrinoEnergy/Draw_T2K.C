]1;95;0cvoid Draw_T2K() {
  TString FileName = "../../MacroInputs/NeutrinoEnergy_T2K.root ";
  TFile* File = new TFile(FileName);

  /*
  KEY: TH1D	FHC1Rmu-2020_NuE_NuEB
  KEY: TH1D	FHC1Rmu-2020_NuMu_NuMuB
  KEY: TH1D	RHC1Rmu-2020_NuE_NuEB
  KEY: TH1D	RHC1Rmu-2020_NuMu_NuMuB
  KEY: TH1D	FHC1Re-2020_NuE_NuEB
  KEY: TH1D	FHC1Re-2020_NuMu_NuMuB
  KEY: TH1D	RHC1Re-2020_NuE_NuEB
  KEY: TH1D	RHC1Re-2020_NuMu_NuMuB
  KEY: TH1D	FHCCC1pi-2020_NuE_NuEB
  KEY: TH1D	FHCCC1pi-2020_NuMu_NuMuB
   */
  
  TH1D* CC0Pi_NuE;
  TH1D* CC0Pi_NuMu;
  TH1D* CC1Pi_NuE;
  TH1D* CC1Pi_NuMu;
  
  TH1D* Hist;
  
  Hist = (TH1D*)File->Get("FHC1Rmu-2020_NuE_NuEB");
  CC0Pi_NuE = (TH1D*)Hist->Clone();
  Hist = (TH1D*)File->Get("RHC1Rmu-2020_NuE_NuEB");
  CC0Pi_NuE->Add(Hist);
  Hist = (TH1D*)File->Get("FHC1Re-2020_NuE_NuEB");
  CC0Pi_NuE->Add(Hist);
  Hist = (TH1D*)File->Get("RHC1Re-2020_NuE_NuEB");
  CC0Pi_NuE->Add(Hist);

  Hist = (TH1D*)File->Get("FHC1Rmu-2020_NuMu_NuMuB");
  CC0Pi_NuMu = (TH1D*)Hist->Clone();
  Hist = (TH1D*)File->Get("RHC1Rmu-2020_NuMu_NuMuB");
  CC0Pi_NuMu->Add(Hist);
  Hist = (TH1D*)File->Get("FHC1Re-2020_NuMu_NuMuB");
  CC0Pi_NuMu->Add(Hist);
  Hist = (TH1D*)File->Get("RHC1Re-2020_NuMu_NuMuB");
  CC0Pi_NuMu->Add(Hist);
    
  Hist = (TH1D*)File->Get("FHCCC1pi-2020_NuE_NuEB");
  CC1Pi_NuE = (TH1D*)Hist->Clone();

  Hist = (TH1D*)File->Get("FHCCC1pi-2020_NuMu_NuMuB");
  CC1Pi_NuMu = (TH1D*)Hist->Clone();
  
  CC0Pi_NuE->SetLineColor(kBlue);
  CC0Pi_NuMu->SetLineColor(kBlue);
  CC1Pi_NuE->SetLineColor(kGreen);
  CC1Pi_NuMu->SetLineColor(kGreen);

  CC0Pi_NuE->Rebin(5);
  CC0Pi_NuMu->Rebin(5);
  CC1Pi_NuE->Rebin(5);
  CC1Pi_NuMu->Rebin(5);

  TCanvas* Canv = new TCanvas("Canv","",500,500);
  Canv->SetLogx();

  //================================================================================
  CC0Pi_NuE->SetTitle("#nu_{x} #rightarrow #nu_{e}");
  CC0Pi_NuE->GetXaxis()->SetTitleSize(0.05);
  CC0Pi_NuE->GetXaxis()->SetTitleOffset(0.93);
  CC0Pi_NuE->GetYaxis()->SetTitleSize(0.05);
  CC0Pi_NuE->GetXaxis()->SetRangeUser(0.1,30.);
  CC0Pi_NuE->GetXaxis()->SetTitle("Neutrino Energy (GeV)");
  CC0Pi_NuE->GetYaxis()->SetTitle("Events");

  CC0Pi_NuE->Draw();
  CC1Pi_NuE->Draw("SAME");
  
  TLegend* Leg1 = new TLegend(0.4,0.795-0.05,0.89,0.89-0.05);
  Leg1->SetBorderSize(0);
  Leg1->SetTextSize(0.05);
  Leg1->AddEntry(CC0Pi_NuE,"0 Decay Electron","l");
  Leg1->AddEntry(CC1Pi_NuE,"1 Decay Electron","l");
  Leg1->Draw("SAME");

  Canv->Print("NeutrinoEnergyDist_T2K_NuE.pdf");

  //================================================================================
  CC0Pi_NuMu->SetTitle("#nu_{x} #rightarrow #nu_{#mu}");
  CC0Pi_NuMu->GetXaxis()->SetTitleSize(0.05);
  CC0Pi_NuMu->GetXaxis()->SetTitleOffset(0.93);
  CC0Pi_NuMu->GetYaxis()->SetTitleSize(0.05);
  CC0Pi_NuMu->GetXaxis()->SetRangeUser(0.1,30.);
  CC0Pi_NuMu->GetYaxis()->SetRangeUser(0.,40.);
  CC0Pi_NuMu->GetXaxis()->SetTitle("Neutrino Energy (GeV)");
  CC0Pi_NuMu->GetYaxis()->SetTitle("Events");
  
  CC0Pi_NuMu->Draw();
  //CC1Pi_NuMu->Draw("SAME");

  TLegend* Leg2 = new TLegend(0.4,0.8-0.05,0.89,0.89-0.05);
  Leg2->SetBorderSize(0);
  Leg2->SetFillStyle(0);
  Leg2->SetTextSize(0.05);
  Leg2->AddEntry(CC0Pi_NuMu,"0 Decay Electron","l");
  //Leg2->AddEntry(CC1Pi_NuMu,"CC1#pi Samples","l");
  Leg2->Draw("SAME");

  Canv->Print("NeutrinoEnergyDist_T2K_NuMu.pdf");

}
