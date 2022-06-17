TH2D* CalcDifference(TH2D* HistA, TH2D* HistB) {
  TH2D* Hist = (TH2D*)HistA->Clone();

  for (int xBin=1;xBin<=Hist->GetNbinsX();xBin++) {
    for (int yBin=1;yBin<=Hist->GetNbinsY();yBin++) {
      Hist->SetBinContent(xBin,yBin,HistA->GetBinContent(xBin,yBin)-HistB->GetBinContent(xBin,yBin));
    }
  }

  return Hist;
}

void DrawOsc() {

  gStyle->SetOptStat(false);
  
  TString FileName_Matter = "../../MacroInputs/Oscillograms/Oscillograms_Matter_NoChemComp_PREM4_NoProdHeight.root";
  TFile* File = new TFile(FileName_Matter);

  TH2D* H_NuE_CPViol = (TH2D*)File->Get("Osc_NH/Fine/hSecondaryArray_1_1_0");
  TH2D* H_NuE_CPCons = (TH2D*)File->Get("Osc_NH_CPCons/Fine/hSecondaryArray_1_1_0");

  TH2D* H_NuE_Diff = CalcDifference(H_NuE_CPViol,H_NuE_CPCons);

  H_NuE_CPViol->GetZaxis()->SetRangeUser(0.,1.0);
  H_NuE_CPCons->GetZaxis()->SetRangeUser(0.,1.0);
  
  H_NuE_CPViol->GetXaxis()->SetRangeUser(0.1,100.0);
  H_NuE_CPCons->GetXaxis()->SetRangeUser(0.1,100.0);
  H_NuE_Diff->GetXaxis()->SetRangeUser(0.1,100.0);

  H_NuE_CPViol->SetTitle("");
  H_NuE_CPCons->SetTitle("");
  H_NuE_Diff->SetTitle("");

  H_NuE_CPViol->GetXaxis()->SetTitleOffset(1.2);
  H_NuE_CPCons->GetXaxis()->SetTitleOffset(1.2);
  H_NuE_Diff->GetXaxis()->SetTitleOffset(1.2);
  H_NuE_CPViol->GetYaxis()->SetTitleOffset(1.2);
  H_NuE_CPCons->GetYaxis()->SetTitleOffset(1.2);
  H_NuE_Diff->GetYaxis()->SetTitleOffset(1.2);
  
  TPaveText* XTitle = new TPaveText(0.0,0.0,0.03,1.0);
  TText* XText = (TText*)XTitle->AddText("#nu_{#mu} #rightarrow #nu_{e}");
  XText->SetTextAngle(90);
  XTitle->SetBorderSize(0) ;
  XTitle->SetFillColor(0) ;
  XTitle->SetTextSize(0.03) ;

  TPaveText* YTitle1 = new TPaveText(0.03,0.9,0.35,1.0);
  YTitle1->AddText("#delta_{CP} = 1.601");
  YTitle1->SetBorderSize(0) ;
  YTitle1->SetFillColor(0) ;
  YTitle1->SetTextSize(0.03) ;

  TPaveText* YTitle2 = new TPaveText(0.35,0.9,0.67,1.0);
  YTitle2->AddText("#delta_{CP} = 0.0");
  YTitle2->SetBorderSize(0) ;
  YTitle2->SetFillColor(0) ;
  YTitle2->SetTextSize(0.03) ;

  TPaveText* YTitle3 = new TPaveText(0.67,0.9,0.97,1.0);
  YTitle3->AddText("P(#nu_{#mu} #rightarrow #nu_{e};#delta_{CP}=-1.601) - P(#nu_{#mu} #rightarrow #nu_{e};#delta_{CP}=0.)");
  YTitle3->SetBorderSize(0) ;
  YTitle3->SetFillColor(0) ;
  YTitle3->SetTextSize(0.03) ;
  
  TCanvas* Canv = new TCanvas("Canv","",1500,1000);

  XTitle->Draw();
  YTitle1->Draw();
  YTitle2->Draw();
  YTitle3->Draw();
  
  Canv->cd();
  TPad* Pad1 = new TPad("Pad1","",0.03,0.1,0.35,0.9);
  Pad1->Draw();
  Pad1->cd();
  Pad1->SetLogx();
  H_NuE_CPViol->Draw("COLZ");

  Canv->cd();
  TPad* Pad2 = new TPad("Pad1","",0.35,0.1,0.67,0.9);
  Pad2->Draw();
  Pad2->cd();
  Pad2->SetLogx();
  H_NuE_CPCons->Draw("COLZ");

  Canv->cd();
  TPad* Pad3 = new TPad("Pad1","",0.67,0.1,0.97,0.9);
  Pad3->Draw();
  Pad3->SetRightMargin(0.11);
  Pad3->cd();
  Pad3->SetLogx();
  H_NuE_Diff->Draw("COLZ");

  TCanvas* Canv2 = new TCanvas("Canv2","");
  
  Canv2->cd();
  TPad* Pad4 = new TPad("Pad4","",0.05,0.05,0.95,0.93);
  Pad4->Draw();
  Pad4->SetLogx();
  Pad4->cd();
  H_NuE_Diff->Draw("COLZ");

  Canv2->cd();

  TPaveText* YTitle4 = new TPaveText(0.4,0.93,0.6,0.99);
  YTitle4->AddText("P(#nu_{#mu} #rightarrow #nu_{e};#delta_{CP}=-1.601) - P(#nu_{#mu} #rightarrow #nu_{e};#delta_{CP}=0.)");
  YTitle4->SetBorderSize(0) ;
  YTitle4->SetFillColor(0) ;
  YTitle4->SetTextSize(0.05) ;
  
  YTitle4->Draw();

  Canv2->Print("AtmDCPSens.pdf");
}
