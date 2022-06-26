TH2D* CalcDiff(TH2D* HistA, TH2D* HistB) {
  TH2D* ReturnHist = (TH2D*)HistA->Clone();

  for (int xBin=1;xBin<=HistA->GetNbinsX();xBin++) {
    for (int yBin=1;yBin<=HistA->GetNbinsY();yBin++) {
      ReturnHist->SetBinContent(xBin,yBin,HistA->GetBinContent(xBin,yBin)-HistB->GetBinContent(xBin,yBin));
    }
  }

  return ReturnHist;
}

void DrawOsc() {

  bool doPadding = true;
  
  gStyle->SetOptStat(false);
  
  TString FileName_wAverDensity = "../../MacroInputs/Oscillograms/Oscillograms_Matter_WithChemComp_PREM4Averaging_NoProdHeight.root";
  TFile* File_wAverDensity = new TFile(FileName_wAverDensity);

  TString FileName_nAverDensity = "../../MacroInputs/Oscillograms/Oscillograms_Matter_WithChemComp_PREM4_NoProdHeight.root";
  TFile* File_nAverDensity = new TFile(FileName_nAverDensity);

  TH2D* H_NuMu_x_NuE_wAverDensity = (TH2D*)File_wAverDensity->Get("Osc_NH/Coarse/hPrimaryArray_1_1_0");
  TH2D* H_NuMu_x_NuE_nAverDensity = (TH2D*)File_nAverDensity->Get("Osc_NH/Coarse/hPrimaryArray_1_1_0");
  TH2D* H_NuE_x_NuE_wAverDensity = (TH2D*)File_wAverDensity->Get("Osc_NH/Coarse/hPrimaryArray_1_0_0");
  TH2D* H_NuE_x_NuE_nAverDensity = (TH2D*)File_nAverDensity->Get("Osc_NH/Coarse/hPrimaryArray_1_0_0");

  TH2D* H_NuMu_x_NuE_Diff = CalcDiff(H_NuMu_x_NuE_wAverDensity,H_NuMu_x_NuE_nAverDensity);
  TH2D* H_NuE_x_NuE_Diff = CalcDiff(H_NuE_x_NuE_wAverDensity,H_NuE_x_NuE_nAverDensity);

  H_NuMu_x_NuE_nAverDensity->GetYaxis()->SetTitleSize(0.045);
  H_NuE_x_NuE_nAverDensity->GetYaxis()->SetTitleSize(0.045);
  H_NuE_x_NuE_nAverDensity->GetXaxis()->SetTitleSize(0.045);
  H_NuE_x_NuE_wAverDensity->GetXaxis()->SetTitleSize(0.045);
  H_NuMu_x_NuE_Diff->GetYaxis()->SetTitleSize(0.045);
  H_NuE_x_NuE_Diff->GetYaxis()->SetTitleSize(0.045);
  H_NuE_x_NuE_Diff->GetXaxis()->SetTitleSize(0.045);
  
  H_NuMu_x_NuE_wAverDensity->SetTitle("");
  H_NuMu_x_NuE_nAverDensity->SetTitle("");
  H_NuMu_x_NuE_Diff->SetTitle("");
  H_NuE_x_NuE_wAverDensity->SetTitle("");
  H_NuE_x_NuE_nAverDensity->SetTitle("");
  H_NuE_x_NuE_Diff->SetTitle("");
  
  H_NuMu_x_NuE_wAverDensity->GetXaxis()->SetRangeUser(0.1,100.0);
  H_NuMu_x_NuE_nAverDensity->GetXaxis()->SetRangeUser(0.1,100.0);
  H_NuMu_x_NuE_Diff->GetXaxis()->SetRangeUser(0.1,100.0);
  H_NuE_x_NuE_wAverDensity->GetXaxis()->SetRangeUser(0.1,100.0);
  H_NuE_x_NuE_nAverDensity->GetXaxis()->SetRangeUser(0.1,100.0);
  H_NuE_x_NuE_Diff->GetXaxis()->SetRangeUser(0.1,100.0);

  H_NuMu_x_NuE_wAverDensity->GetZaxis()->SetRangeUser(0.,1.0);
  H_NuMu_x_NuE_nAverDensity->GetZaxis()->SetRangeUser(0.,1.0);
  H_NuMu_x_NuE_Diff->GetZaxis()->SetRangeUser(-0.3,0.3);
  H_NuE_x_NuE_wAverDensity->GetZaxis()->SetRangeUser(0.,1.0);
  H_NuE_x_NuE_nAverDensity->GetZaxis()->SetRangeUser(0.,1.0);
  H_NuE_x_NuE_Diff->GetZaxis()->SetRangeUser(-0.3,0.3);

  TPaveText* wProdAvgTitle = new TPaveText(0.356,0.9,0.633,1.0);
  wProdAvgTitle->AddText("Avg. Density");
  wProdAvgTitle->SetBorderSize(0) ;
  wProdAvgTitle->SetFillColor(0) ;
  wProdAvgTitle->SetTextSize(0.03) ;

  TPaveText* nProdAvgTitle = new TPaveText(0.06,0.9,0.356,1.0);
  nProdAvgTitle->AddText("Const. Density");
  nProdAvgTitle->SetBorderSize(0) ;
  nProdAvgTitle->SetFillColor(0) ;
  nProdAvgTitle->SetTextSize(0.03) ;

  TPaveText* DiffTitle = new TPaveText(0.633,0.9,0.98,1.0);
  DiffTitle->AddText("Avg. Density - Const. Density");
  DiffTitle->SetBorderSize(0) ;
  DiffTitle->SetFillColor(0) ;
  DiffTitle->SetTextSize(0.03) ;

  TPaveText* NuMu_x_NuE_Title = new TPaveText(0.0,0.5,0.06,1.0);
  TText* NuMu_x_NuE_Text = (TText*)NuMu_x_NuE_Title->AddText("P(#nu_{#mu} #rightarrow #nu_{e})");
  NuMu_x_NuE_Text->SetTextAngle(90);
  NuMu_x_NuE_Title->SetBorderSize(0) ;
  NuMu_x_NuE_Title->SetFillColor(0) ;
  NuMu_x_NuE_Title->SetTextSize(0.03) ;

  TPaveText* NuE_x_NuE_Title = new TPaveText(0.0,0.0,0.06,0.5);
  TText* NuE_x_NuE_Text = (TText*)NuE_x_NuE_Title->AddText("P(#nu_{e} #rightarrow #nu_{e})");
  NuE_x_NuE_Text->SetTextAngle(90);
  NuE_x_NuE_Title->SetBorderSize(0) ;
  NuE_x_NuE_Title->SetFillColor(0) ;
  NuE_x_NuE_Title->SetTextSize(0.03) ;

  TCanvas* Canv = new TCanvas("Canv","",1000,1000);

  wProdAvgTitle->Draw();
  nProdAvgTitle->Draw();
  DiffTitle->Draw();
  NuMu_x_NuE_Title->Draw();
  NuE_x_NuE_Title->Draw();
  
  Canv->cd();
  TPad* Pad1 = new TPad("Pad1","",0.06,0.5,0.356,0.9);
  if (doPadding) {
    Pad1->SetLeftMargin(0.1);
    Pad1->SetRightMargin(0.0);
    Pad1->SetBottomMargin(0.0);
    Pad1->SetTopMargin(0.01);
  }
  Pad1->Draw();
  Pad1->cd();
  Pad1->SetLogx();
  H_NuMu_x_NuE_nAverDensity->Draw("COLZ");

  Canv->cd();
  TPad* Pad2 = new TPad("Pad2","",0.356,0.5,0.633,0.9);
  if (doPadding) {
    Pad2->SetLeftMargin(0.0);
    Pad2->SetRightMargin(0.1);
    Pad2->SetBottomMargin(0.0);
    Pad2->SetTopMargin(0.01);
  }
  Pad2->Draw();
  Pad2->cd();
  Pad2->SetLogx();
  H_NuMu_x_NuE_wAverDensity->Draw("COLZ");

  Canv->cd();
  TPad* Pad3 = new TPad("Pad3","",0.633,0.5,0.98,0.9);
  if (doPadding) {
    Pad3->SetLeftMargin(0.1);
    Pad3->SetRightMargin(0.15);
    Pad3->SetBottomMargin(0.0);
    Pad3->SetTopMargin(0.01);
  }
  Pad3->Draw();
  Pad3->cd();
  Pad3->SetLogx();
  H_NuMu_x_NuE_Diff->Draw("COLZ");

  Canv->cd();
  TPad* Pad4 = new TPad("Pad4","",0.06,0.1,0.356,0.5);
  if (doPadding) {
    Pad4->SetLeftMargin(0.1);
    Pad4->SetRightMargin(0.0);
    Pad4->SetBottomMargin(0.1);
    Pad4->SetTopMargin(0.0);
  }
  Pad4->Draw();
  Pad4->cd();
  Pad4->SetLogx();
  H_NuE_x_NuE_nAverDensity->Draw("COLZ");

  Canv->cd();
  TPad* Pad5 = new TPad("Pad5","",0.356,0.1,0.633,0.5);
  if (doPadding) {
    Pad5->SetLeftMargin(0.0);
    Pad5->SetRightMargin(0.1);
    Pad5->SetBottomMargin(0.1);
    Pad5->SetTopMargin(0.0);
  }
  Pad5->Draw();
  Pad5->cd();
  Pad5->SetLogx();
  H_NuE_x_NuE_wAverDensity->Draw("COLZ");

  Canv->cd();
  TPad* Pad6 = new TPad("Pad6","",0.633,0.1,0.98,0.5);
  if (doPadding) {
    Pad6->SetLeftMargin(0.1);
    Pad6->SetRightMargin(0.15);
    Pad6->SetBottomMargin(0.1);
    Pad6->SetTopMargin(0.0);
  }
  Pad6->Draw();
  Pad6->cd();
  Pad6->SetLogx();
  H_NuE_x_NuE_Diff->Draw("COLZ");

  Canv->Print("AverageDensityPREMModel.pdf");  
}
