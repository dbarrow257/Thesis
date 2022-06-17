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
  H_NuE_CPViol->GetZaxis()->SetRangeUser(0.,1.0);
  H_NuE_CPViol->GetXaxis()->SetRangeUser(0.1,500.0);

  H_NuE_CPViol->SetTitle("");
  H_NuE_CPViol->GetXaxis()->SetTitleOffset(1.2);
  H_NuE_CPViol->GetYaxis()->SetTitleOffset(1.2);

  TCanvas* Canv2 = new TCanvas("Canv2","");
  
  Canv2->cd();
  TPad* Pad4 = new TPad("Pad4","",0.05,0.05,0.95,0.90);
  Pad4->Draw();
  Pad4->SetLogx();
  Pad4->cd();
  H_NuE_CPViol->Draw("COLZ");

  Canv2->cd();

  TPaveText* YTitle4 = new TPaveText(0.4,0.90,0.6,0.99);
  YTitle4->AddText("P(#nu_{#mu} #rightarrow #nu_{e})");
  YTitle4->SetBorderSize(0) ;
  YTitle4->SetFillColor(0) ;
  YTitle4->SetTextSize(0.05) ;
  
  YTitle4->Draw();

  Canv2->Print("BasicOscillogram.pdf");
}
