void DrawOsc() {

  bool doPadding = true;
  
  gStyle->SetOptStat(false);
  
  TString FileName_Vacuum = "../../MacroInputs/Oscillograms/Oscillograms_Vacuum_PREM4_NoProdHeight.root";
  TFile* File_Vacuum = new TFile(FileName_Vacuum);

  TString FileName_Matter = "../../MacroInputs/Oscillograms/Oscillograms_Matter_NoChemComp_PREM4_NoProdHeight.root";
  TFile* File_Matter = new TFile(FileName_Matter);

  TH2D* H_NuE_Vacuum = (TH2D*)File_Vacuum->Get("Osc_NH/Fine/hSecondaryArray_1_0_0");
  TH2D* H_NuE_Matter_NH = (TH2D*)File_Matter->Get("Osc_NH/Fine/hSecondaryArray_1_0_0");
  TH2D* H_NuE_Matter_IH = (TH2D*)File_Matter->Get("Osc_IH/Fine/hSecondaryArray_1_0_0");
  TH2D* H_NuEBar_Vacuum = (TH2D*)File_Vacuum->Get("Osc_NH/Fine/hSecondaryArray_0_0_0");
  TH2D* H_NuEBar_Matter_NH = (TH2D*)File_Matter->Get("Osc_NH/Fine/hSecondaryArray_0_0_0");
  TH2D* H_NuEBar_Matter_IH = (TH2D*)File_Matter->Get("Osc_IH/Fine/hSecondaryArray_0_0_0");

  H_NuE_Vacuum->GetZaxis()->SetRangeUser(0.0,1.0);
  H_NuE_Matter_NH->GetZaxis()->SetRangeUser(0.0,1.0);
  H_NuE_Matter_IH->GetZaxis()->SetRangeUser(0.0,1.0);
  H_NuEBar_Vacuum->GetZaxis()->SetRangeUser(0.0,1.0);
  H_NuEBar_Matter_NH->GetZaxis()->SetRangeUser(0.0,1.0);
  H_NuEBar_Matter_IH->GetZaxis()->SetRangeUser(0.0,1.0);

  H_NuE_Vacuum->GetYaxis()->SetTitleOffset(1.);
  H_NuEBar_Vacuum->GetYaxis()->SetTitleOffset(1.);

  H_NuE_Vacuum->GetYaxis()->SetTitleSize(0.05);
  H_NuEBar_Vacuum->GetYaxis()->SetTitleSize(0.05);

  H_NuEBar_Vacuum->GetXaxis()->SetTitleOffset(1.);
  H_NuEBar_Matter_NH->GetXaxis()->SetTitleOffset(1.);
  H_NuEBar_Matter_IH->GetXaxis()->SetTitleOffset(1.);

  H_NuEBar_Vacuum->GetXaxis()->SetTitleSize(0.05);
  H_NuEBar_Matter_NH->GetXaxis()->SetTitleSize(0.05);
  H_NuEBar_Matter_IH->GetXaxis()->SetTitleSize(0.05);
  
  TPaveText* VacuumTitle = new TPaveText(0.1,0.9,0.37,1.0);
  VacuumTitle->AddText("Vacuum");
  VacuumTitle->SetBorderSize(0) ;
  VacuumTitle->SetFillColor(0) ;
  VacuumTitle->SetTextSize(0.04) ;
  
  TPaveText* MatterNHTitle = new TPaveText(0.37,0.9,0.629,1.0);
  MatterNHTitle->AddText("Matter (NH)");
  MatterNHTitle->SetBorderSize(0) ;
  MatterNHTitle->SetFillColor(0) ;
  MatterNHTitle->SetTextSize(0.04) ;

  TPaveText* MatterIHTitle = new TPaveText(0.629,0.9,0.9,1.0);
  MatterIHTitle->AddText("Matter (IH)");
  MatterIHTitle->SetBorderSize(0) ;
  MatterIHTitle->SetFillColor(0) ;
  MatterIHTitle->SetTextSize(0.04) ;

  TPaveText* NuETitle = new TPaveText(0.0,0.4,0.1,1.0);
  TText* NHText = (TText*)NuETitle->AddText("#nu_{e} #rightarrow #nu_{e}");
  NHText->SetTextAngle(90);
  NuETitle->SetBorderSize(0) ;
  NuETitle->SetFillColor(0) ;
  NuETitle->SetTextSize(0.03) ;

  TPaveText* NuEBarTitle = new TPaveText(0.0,0.1,0.1,0.5);
  TText* IHText = (TText*)NuEBarTitle->AddText("#bar{#nu}_{e} #rightarrow #bar{#nu}_{e}");
  IHText->SetTextAngle(90);
  NuEBarTitle->SetBorderSize(0) ;
  NuEBarTitle->SetFillColor(0) ;
  NuEBarTitle->SetTextSize(0.03) ;
  
  H_NuE_Vacuum->SetTitle("");
  H_NuE_Matter_NH->SetTitle("");
  H_NuE_Matter_IH->SetTitle("");
  H_NuEBar_Vacuum->SetTitle("");
  H_NuEBar_Matter_NH->SetTitle("");
  H_NuEBar_Matter_IH->SetTitle("");
  
  H_NuE_Vacuum->GetXaxis()->SetRangeUser(0.1,100.0);
  H_NuE_Matter_NH->GetXaxis()->SetRangeUser(0.1,100.0);
  H_NuE_Matter_IH->GetXaxis()->SetRangeUser(0.1,100.0);
  H_NuEBar_Vacuum->GetXaxis()->SetRangeUser(0.1,100.0);
  H_NuEBar_Matter_NH->GetXaxis()->SetRangeUser(0.1,100.0);
  H_NuEBar_Matter_IH->GetXaxis()->SetRangeUser(0.1,100.0);
  
  TCanvas* Canv = new TCanvas("Canv","",1000,1000);

  VacuumTitle->Draw();
  MatterNHTitle->Draw();
  MatterIHTitle->Draw();
  NuETitle->Draw();
  NuEBarTitle->Draw();
  
  Canv->cd();
  TPad* Pad1 = new TPad("Pad1","",0.1,0.5,0.37,0.9);
  if (doPadding) {
    Pad1->SetLeftMargin(0.1);
    Pad1->SetRightMargin(0.0);
    Pad1->SetBottomMargin(0.0);
    Pad1->SetTopMargin(0.01);
  }
  Pad1->Draw();
  Pad1->cd();
  Pad1->SetLogx();
  H_NuE_Vacuum->Draw("COLZ");

  Canv->cd();
  TPad* Pad2 = new TPad("Pad2","",0.37,0.5,0.629,0.9);
  if (doPadding) {
    Pad2->SetLeftMargin(0.0);
    Pad2->SetRightMargin(0.0);
    Pad2->SetBottomMargin(0.0);
    Pad2->SetTopMargin(0.01);
  }
  Pad2->Draw();
  Pad2->cd();
  Pad2->SetLogx();
  H_NuE_Matter_NH->Draw("COLZ");

  Canv->cd();
  TPad* Pad3 = new TPad("Pad3","",0.629,0.5,0.9,0.9);
  if (doPadding) {
    Pad3->SetLeftMargin(0.0);
    Pad3->SetRightMargin(0.1);
    Pad3->SetBottomMargin(0.0);
    Pad3->SetTopMargin(0.01);
  }
  Pad3->Draw();
  Pad3->cd();
  Pad3->SetLogx();
  H_NuE_Matter_IH->Draw("COLZ");

  Canv->cd();
  TPad* Pad4 = new TPad("Pad4","",0.1,0.07,0.37,0.5);
  if (doPadding) {
    Pad4->SetLeftMargin(0.1);
    Pad4->SetRightMargin(0.0);
    Pad4->SetBottomMargin(0.1);
    Pad4->SetTopMargin(0.0);
  }
  Pad4->Draw();
  Pad4->cd();
  Pad4->SetLogx();
  H_NuEBar_Vacuum->Draw("COLZ");

  Canv->cd();
  TPad* Pad5 = new TPad("Pad5","",0.37,0.07,0.629,0.5);
  if (doPadding) {
    Pad5->SetLeftMargin(0.0);
    Pad5->SetRightMargin(0.0);
    Pad5->SetBottomMargin(0.1);
    Pad5->SetTopMargin(0.0);
  }
  Pad5->Draw();
  Pad5->cd();
  Pad5->SetLogx();
  H_NuEBar_Matter_NH->Draw("COLZ");

  Canv->cd();
  TPad* Pad6 = new TPad("Pad6","",0.629,0.07,0.9,0.5);
  if (doPadding) {
    Pad6->SetLeftMargin(0.0);
    Pad6->SetRightMargin(0.1);
    Pad6->SetBottomMargin(0.1);
    Pad6->SetTopMargin(0.0);
  }
  Pad6->Draw();
  Pad6->cd();
  Pad6->SetLogx();
  H_NuEBar_Matter_IH->Draw("COLZ");

  Canv->Print("Matter_Effect.pdf");  
}
