void Comp_1Re1de() {
  TString Atm_FileName = "../../MacroInputs/NeutrinoEnergy_Atm.root ";
  TFile* Atm_File = new TFile(Atm_FileName);

  TString T2K_FileName = "../../MacroInputs/NeutrinoEnergy_T2K.root ";
  TFile* T2K_File = new TFile(T2K_FileName);

  TH1D* FC_SubGeV_NuE;
  TH1D* FC_SubGeV_NuMu;
  TH1D* T2K_NuE;
  TH1D* T2K_NuMu;
  
  TH1D* Hist;
  
  Hist = (TH1D*)Atm_File->Get("SubGeV-elike-1dcy_NuE_NuEB");
  FC_SubGeV_NuE = (TH1D*)Hist->Clone();
  
  Hist = (TH1D*)Atm_File->Get("SubGeV-elike-1dcy_NuMu_NuMuB");
  FC_SubGeV_NuMu = (TH1D*)Hist->Clone();
  
  Hist = (TH1D*)T2K_File->Get("FHCCC1pi-2020_NuE_NuEB");
  T2K_NuE = (TH1D*)Hist->Clone();

  Hist = (TH1D*)T2K_File->Get("FHCCC1pi-2020_NuMu_NuMuB");
  T2K_NuMu = (TH1D*)Hist->Clone();
  
  T2K_NuE->SetLineColor(kBlue);
  T2K_NuMu->SetLineColor(kBlue);
  FC_SubGeV_NuE->SetLineColor(kGreen);
  FC_SubGeV_NuMu->SetLineColor(kGreen);

  T2K_NuE->SetLineWidth(3);
  T2K_NuMu->SetLineWidth(3);
  FC_SubGeV_NuE->SetLineWidth(3);
  FC_SubGeV_NuMu->SetLineWidth(3);
  
  T2K_NuE->Scale(1./T2K_NuE->Integral());
  T2K_NuMu->Scale(1./T2K_NuMu->Integral());
  FC_SubGeV_NuE->Scale(1./FC_SubGeV_NuE->Integral());
  FC_SubGeV_NuMu->Scale(1./FC_SubGeV_NuMu->Integral());

  T2K_NuE->Rebin(5);
  T2K_NuMu->Rebin(5);
  FC_SubGeV_NuE->Rebin(5);
  FC_SubGeV_NuMu->Rebin(5);
  
  TCanvas* Canv = new TCanvas("Canv","",500,500);
  Canv->SetLeftMargin(0.15);
  Canv->SetBottomMargin(0.15);
  Canv->SetLogx();
  
  //================================================================================

  T2K_NuE->SetTitle("#nu_{x} #rightarrow #nu_{e}");
  T2K_NuE->GetXaxis()->SetTitleSize(0.05);
  T2K_NuE->GetXaxis()->SetTitleOffset(0.93);
  T2K_NuE->GetYaxis()->SetTitleOffset(1.05);
  T2K_NuE->GetYaxis()->SetTitleSize(0.05);
  T2K_NuE->GetXaxis()->SetRangeUser(0.1,30.);
  T2K_NuE->GetXaxis()->SetTitle("Neutrino Energy (GeV)");
  T2K_NuE->GetYaxis()->SetTitle("Events");

  T2K_NuE->Draw("HIST");
  FC_SubGeV_NuE->Draw("HIST SAME");
  
  TLegend* Leg1 = new TLegend(0.55,0.795-0.05,0.89,0.89-0.05);
  Leg1->SetBorderSize(0);
  Leg1->SetTextSize(0.05);
  Leg1->AddEntry(T2K_NuE,"T2K Events","l");
  Leg1->AddEntry(FC_SubGeV_NuE,"SK Events","l");
  Leg1->Draw("SAME");

  Canv->Print("NeutrinoEnergyDist_Comp_1Re1de_NuE.pdf");

  //================================================================================

  T2K_NuMu->SetTitle("#nu_{x} #rightarrow #nu_{#mu}");
  T2K_NuMu->GetXaxis()->SetTitleSize(0.05);
  T2K_NuMu->GetXaxis()->SetTitleOffset(0.93);
  T2K_NuMu->GetYaxis()->SetTitleOffset(1.05);
  T2K_NuMu->GetYaxis()->SetTitleSize(0.05);
  T2K_NuMu->GetXaxis()->SetRangeUser(0.1,30.);
  T2K_NuMu->GetXaxis()->SetTitle("Neutrino Energy (GeV)");
  T2K_NuMu->GetYaxis()->SetTitle("Events");

  T2K_NuMu->Draw("HIST");
  FC_SubGeV_NuMu->Draw("HIST SAME");
  
  TLegend* Leg2 = new TLegend(0.55,0.795-0.05,0.89,0.89-0.05);
  Leg2->SetBorderSize(0);
  Leg2->SetTextSize(0.05);
  Leg2->AddEntry(T2K_NuMu,"T2K Events","l");
  Leg2->AddEntry(FC_SubGeV_NuMu,"SK Events","l");
  Leg2->Draw("SAME");

  Canv->Print("NeutrinoEnergyDist_Comp_1Re1de_NuMu.pdf");

  
}
