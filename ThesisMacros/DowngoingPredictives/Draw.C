TH1D* DoProjection(TH2D* Hist_2D) {
  TH1D* Hist_1D = new TH1D("Projection","",Hist_2D->GetNbinsX(),Hist_2D->GetXaxis()->GetXbins()->GetArray());

  for (int xBin=1;xBin<=Hist_2D->GetNbinsX();xBin++) {
    for (int yBin=1;yBin<=Hist_2D->GetNbinsY();yBin++) {
      if (Hist_2D->GetYaxis()->GetBinLowEdge(yBin) >= 0.4) {
	Hist_1D->SetBinContent(xBin,Hist_1D->GetBinContent(xBin)+Hist_2D->GetBinContent(xBin,yBin));
      }
    }
  }

  return Hist_1D;
}

void CalcFracErr(TH1D* Hist) {
  for (int xBin=1;xBin<=Hist->GetNbinsX();xBin++) {
    std::cout << Hist->GetBinError(xBin)/Hist->GetBinContent(xBin) << std::endl;  
  }
}

void Draw(TString SampleName) {
  gStyle->SetOptStat(false);

  TCanvas* Canv = new TCanvas("Canv","");
  Canv->SetLeftMargin(0.15);
  Canv->SetBottomMargin(0.15);
  
  TString PreFitPredFileName = "../../MacroInputs/DowngoingPredictives/MaCh3-Atmospherics-MCMC_PreFit_Pred.root";
  TFile* PreFitPredFile = new TFile(PreFitPredFileName);

  TString PostFitPredFileName = "../../MacroInputs/DowngoingPredictives/MaCh3-Atmospherics-MCMC_PostFit_Pred.root";
  TFile* PostFitPredFile = new TFile(PostFitPredFileName);

  TString PreBANFFFileName = "../../MacroInputs/DowngoingPredictives/Spectra_Generated.root";
  TFile* PreBANFFFile = new TFile(PreBANFFFileName);
  
  TString DataFileName = "../../MacroInputs/DowngoingPredictives/Data.root";
  TFile* DataFile = new TFile(DataFileName);

  TH1D* Sample_PreFitPred = (TH1D*)PreFitPredFile->Get("HistogramStats/"+SampleName+"/Total/"+SampleName+"_Total_Stats_X");
  Sample_PreFitPred->SetLineColor(kRed);
  Sample_PreFitPred->SetFillColor(kRed);
  Sample_PreFitPred->SetFillStyle(3353);

  std::cout << "Pre fit:" << std::endl;
  CalcFracErr(Sample_PreFitPred);
  
  TH1D* Sample_PostFitPred = (TH1D*)PostFitPredFile->Get("HistogramStats/"+SampleName+"/Total/"+SampleName+"_Total_Stats_X");
  Sample_PostFitPred->SetLineColor(kBlue);
  Sample_PostFitPred->SetFillColor(kBlue);
  Sample_PostFitPred->SetFillStyle(3335);
  
  std::cout << "Post fit:" << std::endl;
  CalcFracErr(Sample_PostFitPred);
  
  TH2D* Sample_PreBANFF_2D = (TH2D*)PreBANFFFile->Get("Spectra_"+SampleName);
  //TH1D* Sample_PreBANFF = Sample_PreBANFF_2D->ProjectionX(" ",7,10);
  TH1D* Sample_PreBANFF = DoProjection(Sample_PreBANFF_2D);
  Sample_PreBANFF->SetLineColor(kMagenta);
  Sample_PreBANFF->SetLineWidth(3);
  
  TH2D* Sample_Data_2D = (TH2D*)DataFile->Get(SampleName);
  TH1D* Sample_Data = (TH1D*)Sample_Data_2D->ProjectionX();
  Sample_Data->SetLineColor(kBlack);
  Sample_Data->SetLineWidth(2);

  double Max = Sample_Data->GetMaximum();
  if (Sample_PreFitPred->GetMaximum() > Max) Max = Sample_PreFitPred->GetMaximum();
  if (Sample_PostFitPred->GetMaximum() > Max) Max = Sample_PostFitPred->GetMaximum();
  Sample_Data->GetYaxis()->SetRangeUser(0.,Max*1.3);

  Sample_Data->GetXaxis()->SetTitle("Reconstructed Neutrino Momentum (MeV)");
  Sample_Data->GetYaxis()->SetTitle("Events");
  Sample_Data->GetXaxis()->SetTitleSize(0.05);
  Sample_Data->GetYaxis()->SetTitleSize(0.05);
      
  Sample_Data->Draw("P");
  Sample_PreFitPred->Draw("SAME E2");
  Sample_PostFitPred->Draw("SAME E2");
  Sample_Data->Draw("SAME E");
  Sample_PreBANFF->Draw("SAME");

  Canv->Print("Predictive_"+SampleName+".pdf");
}
