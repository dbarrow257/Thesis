void DrawOsc() {

  bool doPadding = true;
  
  gStyle->SetOptStat(false);
  
  TString FileName = "../../MacroInputs/T2KOscProb/OscProbDCPSens.root";
  TFile* File = new TFile(FileName);

  TH1D* H_NH_NuMu_x_NuE_0 = (TH1D*)File->Get("Osc_NH_0/NuMu_x_NuE");
  TH1D* H_NH_NuMu_x_NuE_pPiDiv2 = (TH1D*)File->Get("Osc_NH_pPiDiv2/NuMu_x_NuE");
  TH1D* H_NH_NuMu_x_NuE_pPi = (TH1D*)File->Get("Osc_NH_pPi/NuMu_x_NuE");
  TH1D* H_NH_NuMu_x_NuE_mPiDiv2 = (TH1D*)File->Get("Osc_NH_mPiDiv2/NuMu_x_NuE");

  int DCP_0_Col = kBlack;
  int DCP_pPiDiv2_Col = kRed;
  int DCP_pPi_Col = kBlue;
  int DCP_mPiDiv2_Col = kGreen;
  
  H_NH_NuMu_x_NuE_0->SetLineColor(DCP_0_Col);
  H_NH_NuMu_x_NuE_pPiDiv2->SetLineColor(DCP_pPiDiv2_Col);
  H_NH_NuMu_x_NuE_pPi->SetLineColor(DCP_pPi_Col);
  H_NH_NuMu_x_NuE_mPiDiv2->SetLineColor(DCP_mPiDiv2_Col);

  H_NH_NuMu_x_NuE_0->SetTitle(";E_{#nu} (GeV);P(#nu_{#mu} #rightarrow #nu_{e})");
  //H_NH_NuMu_x_NuE_0->GetXaxis()->SetTitle("E_{#nu} (GeV)");

  TCanvas* Canv = new TCanvas("Canv","");
  H_NH_NuMu_x_NuE_0->Draw();
  H_NH_NuMu_x_NuE_pPiDiv2->Draw("SAME");
  H_NH_NuMu_x_NuE_pPi->Draw("SAME");
  H_NH_NuMu_x_NuE_mPiDiv2->Draw("SAME");

  H_NH_NuMu_x_NuE_0->SetLineWidth(2);
  H_NH_NuMu_x_NuE_pPiDiv2->SetLineWidth(2);
  H_NH_NuMu_x_NuE_pPi->SetLineWidth(2);
  H_NH_NuMu_x_NuE_mPiDiv2->SetLineWidth(2);

  TLegend* Legend = new TLegend(0.6,0.6,0.89,0.89);
  Legend->AddEntry(H_NH_NuMu_x_NuE_0,"#delta_{CP} = 0.0","l");
  Legend->AddEntry(H_NH_NuMu_x_NuE_pPiDiv2,"#delta_{CP} = #pi/2","l");
  Legend->AddEntry(H_NH_NuMu_x_NuE_pPi,"#delta_{CP} = #pi","l");
  Legend->AddEntry(H_NH_NuMu_x_NuE_mPiDiv2,"#delta_{CP} = -#pi/2","l");

  Legend->SetBorderSize(0);
  Legend->Draw();
}
