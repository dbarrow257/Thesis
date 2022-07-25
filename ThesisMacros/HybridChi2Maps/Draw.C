void DrawHist(TString HistName) {
  TString FileName = "../../MacroInputs/hmupi_hpi0_chi2_maps_14c_320_320_corr.root";
  TFile* File = new TFile(FileName);

  gStyle->SetOptStat(false);

  TCanvas* Canv = new TCanvas("Canv"+HistName,"");
  Canv->SetLeftMargin(0.14);
  Canv->SetRightMargin(0.17);
  
  TH2D* Hist_1 = (TH2D*)File->Get(HistName);
  Hist_1->Rebin2D(5);
  Hist_1->Smooth();
  
  double Min = 1e8;
  for (int xBin=0;xBin<Hist_1->GetNbinsX();xBin++) {
    for (int yBin=0;yBin<Hist_1->GetNbinsY();yBin++) {
      double BinContent = Hist_1->GetBinContent(xBin+1,yBin+1);
      if (BinContent < Min) Min = BinContent;
    }
  }

  TString CanvName;
  
  if (HistName == "h_pi0_chi2_emu0") {
    Hist_1->GetXaxis()->SetRangeUser(0.996,1.008);
    Hist_1->GetYaxis()->SetRangeUser(2,14);
    Hist_1->SetTitle("e/#mu PID, 30 < E_{vis} (MeV) < 300");
    CanvName = "EMUPID_Elt300_Chi2Map.pdf";
  }

  if (HistName == "h_pi0_chi2_epi00") {
    Hist_1->GetXaxis()->SetRangeUser(1.0,1.017);
    Hist_1->GetYaxis()->SetRangeUser(-17,-11);
    Hist_1->SetTitle("e/#pi^{0} PID | 30 < E_{vis} (MeV) < 300");
    CanvName = "EPI0PID_Elt300_Chi2Map.pdf";
  }
  
  Hist_1->SetMaximum(Min+50);

  Hist_1->GetZaxis()->SetTitleOffset(1.2);
  Hist_1->Draw("COLZ");

  Canv->Print(CanvName);
}

void Draw() {
  DrawHist("h_pi0_chi2_emu0");
  DrawHist("h_pi0_chi2_epi00");
}
