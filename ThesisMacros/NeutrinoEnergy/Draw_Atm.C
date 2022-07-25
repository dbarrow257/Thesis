void Draw_Atm() {
  TString FileName = "../../MacroInputs/NeutrinoEnergy_Atm.root ";
  TFile* File = new TFile(FileName);

  /*
  KEY: TH1D	UpStop-mu_NuE_NuEB;1	
  KEY: TH1D	UpStop-mu_NuMu_NuMuB;1	
  KEY: TH1D	UpThruNonShower-mu_NuE_NuEB;1	
  KEY: TH1D	UpThruNonShower-mu_NuMu_NuMuB;1	
  KEY: TH1D	UpThruShower-mu_NuE_NuEB;1	
  KEY: TH1D	UpThruShower-mu_NuMu_NuMuB;1
  */

  TH1D* FC_SubGeV_NuE;
  TH1D* FC_SubGeV_NuMu;
  TH1D* FC_SubGeV_NuTau;
  TH1D* FC_MultiGeV_NuE;
  TH1D* FC_MultiGeV_NuMu;
  TH1D* FC_MultiGeV_NuTau;
  TH1D* PC_NuE;
  TH1D* PC_NuMu;
  TH1D* Upmu_NuE;
  TH1D* Upmu_NuMu;
  
  TH1D* Hist;
  
  Hist = (TH1D*)File->Get("SubGeV-elike-0dcy_NuE_NuEB");
  FC_SubGeV_NuE = (TH1D*)Hist->Clone();
  Hist = (TH1D*)File->Get("SubGeV-elike-1dcy_NuE_NuEB");
  FC_SubGeV_NuE->Add(Hist);
  Hist = (TH1D*)File->Get("SubGeV-mulike-0dcy_NuE_NuEB");
  FC_SubGeV_NuE->Add(Hist);
  Hist = (TH1D*)File->Get("SubGeV-mulike-1dcy_NuE_NuEB");
  FC_SubGeV_NuE->Add(Hist);
  Hist = (TH1D*)File->Get("SubGeV-mulike-2dcy_NuE_NuEB");
  FC_SubGeV_NuE->Add(Hist);
  Hist = (TH1D*)File->Get("SubGeV-pi0like_NuE_NuEB");
  FC_SubGeV_NuE->Add(Hist);

  Hist = (TH1D*)File->Get("SubGeV-elike-0dcy_NuMu_NuMuB");
  FC_SubGeV_NuMu = (TH1D*)Hist->Clone();
  Hist = (TH1D*)File->Get("SubGeV-elike-1dcy_NuMu_NuMuB");
  FC_SubGeV_NuMu->Add(Hist);
  Hist = (TH1D*)File->Get("SubGeV-mulike-0dcy_NuMu_NuMuB");
  FC_SubGeV_NuMu->Add(Hist);
  Hist = (TH1D*)File->Get("SubGeV-mulike-1dcy_NuMu_NuMuB");
  FC_SubGeV_NuMu->Add(Hist);
  Hist = (TH1D*)File->Get("SubGeV-mulike-2dcy_NuMu_NuMuB");
  FC_SubGeV_NuMu->Add(Hist);
  Hist = (TH1D*)File->Get("SubGeV-pi0like_NuMu_NuMuB");
  FC_SubGeV_NuMu->Add(Hist);

  Hist = (TH1D*)File->Get("SubGeV-elike-0dcy_NuTau_NuTauB");
  FC_SubGeV_NuTau = (TH1D*)Hist->Clone();
  Hist = (TH1D*)File->Get("SubGeV-elike-1dcy_NuTau_NuTauB");
  FC_SubGeV_NuTau->Add(Hist);
  Hist = (TH1D*)File->Get("SubGeV-mulike-0dcy_NuTau_NuTauB");
  FC_SubGeV_NuTau->Add(Hist);
  Hist = (TH1D*)File->Get("SubGeV-mulike-1dcy_NuTau_NuTauB");
  FC_SubGeV_NuTau->Add(Hist);
  Hist = (TH1D*)File->Get("SubGeV-mulike-2dcy_NuTau_NuTauB");
  FC_SubGeV_NuTau->Add(Hist);
  Hist = (TH1D*)File->Get("SubGeV-pi0like_NuTau_NuTauB");
  FC_SubGeV_NuTau->Add(Hist);

  Hist = (TH1D*)File->Get("MultiGeV-elike-nue_NuE_NuEB");
  FC_MultiGeV_NuE = (TH1D*)Hist->Clone();
  Hist = (TH1D*)File->Get("MultiGeV-elike-nuebar_NuE_NuEB");
  FC_MultiGeV_NuE->Add(Hist);
  Hist = (TH1D*)File->Get("MultiGeV-mulike_NuE_NuEB");
  FC_MultiGeV_NuE->Add(Hist);
  Hist = (TH1D*)File->Get("MultiRing-elike-nue_NuE_NuEB");
  FC_MultiGeV_NuE->Add(Hist);
  Hist = (TH1D*)File->Get("MultiRing-elike-nuebar_NuE_NuEB");
  FC_MultiGeV_NuE->Add(Hist);
  Hist = (TH1D*)File->Get("MultiRing-mulike_NuE_NuEB");
  FC_MultiGeV_NuE->Add(Hist);
  Hist = (TH1D*)File->Get("MultiRingOther-1_NuE_NuEB");
  FC_MultiGeV_NuE->Add(Hist);

  Hist = (TH1D*)File->Get("MultiGeV-elike-nue_NuMu_NuMuB");
  FC_MultiGeV_NuMu = (TH1D*)Hist->Clone();
  Hist = (TH1D*)File->Get("MultiGeV-elike-nuebar_NuMu_NuMuB");
  FC_MultiGeV_NuMu->Add(Hist);
  Hist = (TH1D*)File->Get("MultiGeV-mulike_NuMu_NuMuB");
  FC_MultiGeV_NuMu->Add(Hist);
  Hist = (TH1D*)File->Get("MultiRing-elike-nue_NuMu_NuMuB");
  FC_MultiGeV_NuMu->Add(Hist);
  Hist = (TH1D*)File->Get("MultiRing-elike-nuebar_NuMu_NuMuB");
  FC_MultiGeV_NuMu->Add(Hist);
  Hist = (TH1D*)File->Get("MultiRing-mulike_NuMu_NuMuB");
  FC_MultiGeV_NuMu->Add(Hist);
  Hist = (TH1D*)File->Get("MultiRingOther-1_NuMu_NuMuB");
  FC_MultiGeV_NuMu->Add(Hist);

  Hist = (TH1D*)File->Get("MultiGeV-elike-nue_NuTau_NuTauB");
  FC_MultiGeV_NuTau = (TH1D*)Hist->Clone();
  Hist = (TH1D*)File->Get("MultiGeV-elike-nuebar_NuTau_NuTauB");
  FC_MultiGeV_NuTau->Add(Hist);
  Hist = (TH1D*)File->Get("MultiGeV-mulike_NuTau_NuTauB");
  FC_MultiGeV_NuTau->Add(Hist);
  Hist = (TH1D*)File->Get("MultiRing-elike-nue_NuTau_NuTauB");
  FC_MultiGeV_NuTau->Add(Hist);
  Hist = (TH1D*)File->Get("MultiRing-elike-nuebar_NuTau_NuTauB");
  FC_MultiGeV_NuTau->Add(Hist);
  Hist = (TH1D*)File->Get("MultiRing-mulike_NuTau_NuTauB");
  FC_MultiGeV_NuTau->Add(Hist);
  Hist = (TH1D*)File->Get("MultiRingOther-1_NuTau_NuTauB");
  FC_MultiGeV_NuTau->Add(Hist);

  Hist = (TH1D*)File->Get("PCStop_NuE_NuEB");
  PC_NuE = (TH1D*)Hist->Clone();
  Hist = (TH1D*)File->Get("PCThru_NuE_NuEB");
  PC_NuE->Add(Hist);

  Hist = (TH1D*)File->Get("PCStop_NuMu_NuMuB");
  PC_NuMu = (TH1D*)Hist->Clone();
  Hist = (TH1D*)File->Get("PCThru_NuMu_NuMuB");
  PC_NuMu->Add(Hist);

  Hist = (TH1D*)File->Get("UpStop-mu_NuE_NuEB");
  Upmu_NuE = (TH1D*)Hist->Clone();
  Hist = (TH1D*)File->Get("UpThruNonShower-mu_NuE_NuEB");
  Upmu_NuE->Add(Hist);
  Hist = (TH1D*)File->Get("UpThruShower-mu_NuE_NuEB");
  Upmu_NuE->Add(Hist);

  Hist = (TH1D*)File->Get("UpStop-mu_NuMu_NuMuB");
  Upmu_NuMu = (TH1D*)Hist->Clone();
  Hist = (TH1D*)File->Get("UpThruNonShower-mu_NuMu_NuMuB");
  Upmu_NuMu->Add(Hist);
  Hist = (TH1D*)File->Get("UpThruShower-mu_NuMu_NuMuB");
  Upmu_NuMu->Add(Hist);
  
  FC_SubGeV_NuE->SetLineColor(kBlue);
  FC_SubGeV_NuMu->SetLineColor(kBlue);
  FC_SubGeV_NuTau->SetLineColor(kBlue);
  FC_MultiGeV_NuE->SetLineColor(kRed);
  FC_MultiGeV_NuMu->SetLineColor(kRed);
  FC_MultiGeV_NuTau->SetLineColor(kRed);  
  PC_NuE->SetLineColor(kGreen);
  PC_NuMu->SetLineColor(kGreen);
  Upmu_NuE->SetLineColor(kMagenta);
  Upmu_NuMu->SetLineColor(kMagenta);

  FC_SubGeV_NuE->Rebin(5);
  FC_SubGeV_NuMu->Rebin(5);
  FC_SubGeV_NuTau->Rebin(5);
  FC_MultiGeV_NuE->Rebin(5);
  FC_MultiGeV_NuMu->Rebin(5);
  FC_MultiGeV_NuTau->Rebin(5);
  PC_NuE->Rebin(5);
  PC_NuMu->Rebin(5);
  Upmu_NuE->Rebin(5);
  Upmu_NuMu->Rebin(5);

  TCanvas* Canv = new TCanvas("Canv","",500,500);
  Canv->SetLogx();

  //================================================================================
  FC_SubGeV_NuE->SetTitle("#nu_{x} #rightarrow #nu_{e}");
  FC_SubGeV_NuE->GetXaxis()->SetTitleSize(0.05);
  FC_SubGeV_NuE->GetXaxis()->SetTitleOffset(0.93);
  FC_SubGeV_NuE->GetYaxis()->SetTitleSize(0.05);
  FC_SubGeV_NuE->GetXaxis()->SetTitle("Neutrino Energy (GeV)");
  FC_SubGeV_NuE->GetYaxis()->SetTitle("Events");

  FC_SubGeV_NuE->Draw();
  FC_MultiGeV_NuE->Draw("SAME");
  //PC_NuE->Draw("SAME");
  //Upmu_NuE->Draw("SAME");

  TLegend* Leg1 = new TLegend(0.5,0.795-0.05,0.89,0.89-0.05);
  Leg1->SetBorderSize(0);
  Leg1->SetTextSize(0.05);
  Leg1->AddEntry(FC_SubGeV_NuE,"FC sub-GeV","l");
  Leg1->AddEntry(FC_MultiGeV_NuE,"FC multi-GeV","l");
  Leg1->Draw("SAME");

  Canv->Print("NeutrinoEnergyDist_NuE.pdf");

  //================================================================================
  FC_SubGeV_NuMu->SetTitle("#nu_{x} #rightarrow #nu_{#mu}");
  FC_SubGeV_NuMu->GetXaxis()->SetTitleSize(0.05);
  FC_SubGeV_NuMu->GetXaxis()->SetTitleOffset(0.93);
  FC_SubGeV_NuMu->GetYaxis()->SetTitleSize(0.05);
  FC_SubGeV_NuMu->GetXaxis()->SetTitle("Neutrino Energy (GeV)");
  FC_SubGeV_NuMu->GetYaxis()->SetTitle("Events");
  
  FC_SubGeV_NuMu->Draw();
  FC_MultiGeV_NuMu->Draw("SAME");
  PC_NuMu->Draw("SAME");
  Upmu_NuMu->Draw("SAME");

  TLegend* Leg2 = new TLegend(0.5,0.7-0.05,0.89,0.89-0.05);
  Leg2->SetBorderSize(0);
  Leg2->SetTextSize(0.05);
  Leg2->AddEntry(FC_SubGeV_NuMu,"FC sub-GeV","l");
  Leg2->AddEntry(FC_MultiGeV_NuMu,"FC multi-GeV","l");
  Leg2->AddEntry(PC_NuMu,"PC","l");
  Leg2->AddEntry(Upmu_NuMu,"Up-#mu","l");
  Leg2->Draw("SAME");

  Canv->Print("NeutrinoEnergyDist_NuMu.pdf");

  //================================================================================
  FC_MultiGeV_NuTau->SetTitle("#nu_{x} #rightarrow #nu_{#tau}");
  FC_MultiGeV_NuTau->GetXaxis()->SetTitleSize(0.05);
  FC_MultiGeV_NuTau->GetXaxis()->SetTitleOffset(0.93);
  FC_MultiGeV_NuTau->GetYaxis()->SetTitleSize(0.05);
  FC_MultiGeV_NuTau->GetXaxis()->SetTitle("Neutrino Energy (GeV)");
  FC_MultiGeV_NuTau->GetYaxis()->SetTitle("Events");

  FC_MultiGeV_NuTau->Draw();
  FC_SubGeV_NuTau->Draw("SAME");
  //PC_NuTau->Draw("SAME");
  //Upmu_NuTau->Draw("SAME");

  TLegend* Leg3 = new TLegend(0.5,0.7-0.05,0.89,0.89-0.05);
  Leg3->SetBorderSize(0);
  Leg3->SetTextSize(0.05);
  Leg3->AddEntry(FC_SubGeV_NuTau,"FC sub-GeV","l");
  Leg3->AddEntry(FC_MultiGeV_NuTau,"FC multi-GeV","l");
  //Leg3->AddEntry(PC_NuTau,"PC","l");
  //Leg3->AddEntry(Upmu_NuTau,"Up-#mu","l");
  Leg3->Draw("SAME");
  
  Canv->Print("NeutrinoEnergyDist_NuTau.pdf");
}
