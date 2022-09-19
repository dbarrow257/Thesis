void Comp() {
  gStyle->SetOptStat(false);
  
  TFile* File_2020 = new TFile("SKJointErrorMatrix2020_Total_fitqun_v4_16042020.root");
  TH1D* Hist_2020 = (TH1D*)File_2020->Get("SK_raw_Erec_diag");

  TFile* File_2022 = new TFile("SKDetErrorMatrixFrankenstein_20210928.root");
  TH1D* Hist_2022 = (TH1D*)File_2022->Get("diagonal_Erec");

  Hist_2020->SetLineColor(kBlack);
  Hist_2022->SetLineColor(kRed);

  TCanvas* Canv = new TCanvas("Canv");
  Canv->SetLogy();
  
  Hist_2022->Draw();
  Hist_2020->Draw("SAME");
}
