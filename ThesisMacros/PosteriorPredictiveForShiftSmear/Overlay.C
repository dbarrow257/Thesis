#include <vector>

void Overlay() {
  TFile* SpectraFile = new TFile("../../MacroInputs/PosteriorPredictiveForShiftSmear/Spectra.root");
  TFile* PredictiveFile = new TFile("../../MacroInputs/PosteriorPredictiveForShiftSmear/MaCh3-Atmospherics-MCMC_ShiftSmearTrial_Pred.root");

  std::vector<TString> SampleNames;
  SampleNames.push_back("SubGeV-elike-0dcy");
  //SampleNames.push_back("SubGeV-elike-1dcy");
  //SampleNames.push_back("SubGeV-mulike-0dcy");
  //SampleNames.push_back("SubGeV-mulike-1dcy");
  //SampleNames.push_back("SubGeV-mulike-2dcy");

  std::vector<TString> HistTitles;
  HistTitles.push_back(";Reconstructed Momentum (GeV);Event Rate");
  HistTitles.push_back(";Cosine Zenith;Event Rate");
  
  HistTitles.push_back(";Ring Counting Parameter;Event Rate");
  HistTitles.push_back(";Ring Counting Parameter;Event Rate");
  HistTitles.push_back(";Ring Counting Parameter;Event Rate");
  //HistTitles.push_back(";Ring Counting Parameter;Event Rate");
  HistTitles.push_back(";e/#mu Parameter;Event Rate");
  HistTitles.push_back(";e/#mu Parameter;Event Rate");
  HistTitles.push_back(";e/#mu Parameter;Event Rate");
  //HistTitles.push_back(";e/#mu Parameter;Event Rate");
  HistTitles.push_back(";e/#pi^{0} Parameter;Event Rate");
  HistTitles.push_back(";e/#pi^{0} Parameter;Event Rate");
  HistTitles.push_back(";e/#pi^{0} Parameter;Event Rate");
  //HistTitles.push_back(";e/#pi^{0} Parameter;Event Rate");
  HistTitles.push_back(";#mu/#pi Parameter;Event Rate");
  HistTitles.push_back(";#mu/#pi Parameter;Event Rate");
  HistTitles.push_back(";#mu/#pi Parameter;Event Rate");
  //HistTitles.push_back(";#mu/#pi Parameter;Event Rate");

  std::vector<double> BinMin;
  BinMin.push_back(-100000);
  BinMin.push_back(-100000);
  
  BinMin.push_back(-900);
  BinMin.push_back(-900);
  BinMin.push_back(-900);
  //BinMin.push_back(-900);
  BinMin.push_back(-100);
  BinMin.push_back(-100);
  BinMin.push_back(-100);
  //BinMin.push_back(-100);
  BinMin.push_back(-200);
  BinMin.push_back(-200);
  BinMin.push_back(-200);
  //BinMin.push_back(-200);
  BinMin.push_back(-200);
  BinMin.push_back(-200);
  BinMin.push_back(-200);
  //BinMin.push_back(-200);

  std::vector<double> BinMax;
  BinMax.push_back(100000);
  BinMax.push_back(100000);
  
  BinMax.push_back(600);
  BinMax.push_back(600);
  BinMax.push_back(600);
  //BinMax.push_back(600);
  BinMax.push_back(1500);
  BinMax.push_back(2000);
  BinMax.push_back(4000);
  //BinMax.push_back(5000);
  BinMax.push_back(300);
  BinMax.push_back(300);
  BinMax.push_back(300);
  //BinMax.push_back(300);
  BinMax.push_back(400);
  BinMax.push_back(400);
  BinMax.push_back(400);
  //BinMax.push_back(400);
  
  std::vector<TString> PredictiveHistNames;
  PredictiveHistNames.push_back("_Momentum_FullPredictive");
  PredictiveHistNames.push_back("_CosZ_FullPredictive");

  PredictiveHistNames.push_back("_RC_EVisBin_0_FullPredictive");
  PredictiveHistNames.push_back("_RC_EVisBin_1_FullPredictive");
  PredictiveHistNames.push_back("_RC_EVisBin_2_FullPredictive");
  //PredictiveHistNames.push_back("_RC_EVisBin_3_FullPredictive");
  PredictiveHistNames.push_back("_EMU_EVisBin_0_FullPredictive");
  PredictiveHistNames.push_back("_EMU_EVisBin_1_FullPredictive");
  PredictiveHistNames.push_back("_EMU_EVisBin_2_FullPredictive");
  //PredictiveHistNames.push_back("_EMU_EVisBin_3_FullPredictive");
  PredictiveHistNames.push_back("_EPI0_EVisBin_0_FullPredictive");
  PredictiveHistNames.push_back("_EPI0_EVisBin_1_FullPredictive");
  PredictiveHistNames.push_back("_EPI0_EVisBin_2_FullPredictive");
  //PredictiveHistNames.push_back("_EPI0_EVisBin_3_FullPredictive");
  PredictiveHistNames.push_back("_MUPIP_EVisBin_0_FullPredictive");
  PredictiveHistNames.push_back("_MUPIP_EVisBin_1_FullPredictive");
  PredictiveHistNames.push_back("_MUPIP_EVisBin_2_FullPredictive");
  //PredictiveHistNames.push_back("_MUPIP_EVisBin_3_FullPredictive");
  
  std::vector<TString> SpectraHistNames;
  SpectraHistNames.push_back("_px");
  SpectraHistNames.push_back("_py");
  
  SpectraHistNames.push_back("_AtmDetSyst_MC_ParamIndex_0_DetDimBinIndex_0");
  SpectraHistNames.push_back("_AtmDetSyst_MC_ParamIndex_0_DetDimBinIndex_1");
  SpectraHistNames.push_back("_AtmDetSyst_MC_ParamIndex_0_DetDimBinIndex_2");
  //SpectraHistNames.push_back("_AtmDetSyst_MC_ParamIndex_0_DetDimBinIndex_3");
  SpectraHistNames.push_back("_AtmDetSyst_MC_ParamIndex_1_DetDimBinIndex_0");
  SpectraHistNames.push_back("_AtmDetSyst_MC_ParamIndex_1_DetDimBinIndex_1");
  SpectraHistNames.push_back("_AtmDetSyst_MC_ParamIndex_1_DetDimBinIndex_2");
  //SpectraHistNames.push_back("_AtmDetSyst_MC_ParamIndex_1_DetDimBinIndex_3");
  SpectraHistNames.push_back("_AtmDetSyst_MC_ParamIndex_2_DetDimBinIndex_0");
  SpectraHistNames.push_back("_AtmDetSyst_MC_ParamIndex_2_DetDimBinIndex_1");
  SpectraHistNames.push_back("_AtmDetSyst_MC_ParamIndex_2_DetDimBinIndex_2");
  //SpectraHistNames.push_back("_AtmDetSyst_MC_ParamIndex_2_DetDimBinIndex_3");
  SpectraHistNames.push_back("_AtmDetSyst_MC_ParamIndex_3_DetDimBinIndex_0");
  SpectraHistNames.push_back("_AtmDetSyst_MC_ParamIndex_3_DetDimBinIndex_1");
  SpectraHistNames.push_back("_AtmDetSyst_MC_ParamIndex_3_DetDimBinIndex_2");
  //SpectraHistNames.push_back("_AtmDetSyst_MC_ParamIndex_3_DetDimBinIndex_3");

  int nSamples = SampleNames.size();
  int nHists = SpectraHistNames.size();

  TCanvas* Canv = new TCanvas("Canv","");
  TString OutputName = "Overlay_ShiftSmear.pdf";
  Canv->Print(OutputName+"[");
  Canv->SetLeftMargin(0.15);

  TLegend* Legend;
  bool MadeLegend = false;
  
  for (int iSample=0;iSample<nSamples;iSample++) {
    for(int iHist=0;iHist<nHists;iHist++) {
      TString PredictiveHistName = "FullPredictive/"+SampleNames[iSample]+"/"+SampleNames[iSample]+PredictiveHistNames[iHist];
      TH2D* PredictiveHist = (TH2D*)PredictiveFile->Get(PredictiveHistName);

      /*
      for (int xBin=1;xBin<=PredictiveHist->GetNbinsX();xBin++) {
	double Integral = 0;
	for (int yBin=1;yBin<=PredictiveHist->GetNbinsY();yBin++) {
	  Integral += PredictiveHist->GetBinContent(xBin,yBin);
	}
	std::cout << Integral << std::endl;
      }
      */
      
      TString AsymErrorName = "FullPredictive/"+SampleNames[iSample]+"/"+SampleNames[iSample]+PredictiveHistNames[iHist]+"_Asym";
      TGraphAsymmErrors* AsymmError = (TGraphAsymmErrors*)PredictiveFile->Get(AsymErrorName);
      
      TString SpectraHistName = SampleNames[iSample]+"/"+SampleNames[iSample]+SpectraHistNames[iHist];
      TH1D* SpectraHist = (TH1D*)SpectraFile->Get(SpectraHistName);
 
      SpectraHist->SetLineWidth(2);
      SpectraHist->SetLineColor(kRed);
      
      if (!PredictiveHist) std::cout << "Did not find " << PredictiveHistName << " in Predictive file" << std::endl;
      if (!SpectraHist) std::cout << "Did not find " << SpectraHistName << " in Spectra file" << std::endl;

      //PredictiveHist->SetTitle(SampleNames[iSample]+", "+HistTitles[iHist]);
      PredictiveHist->SetTitle(HistTitles[iHist]);
      PredictiveHist->GetXaxis()->SetTitleOffset(0.9);
      PredictiveHist->GetYaxis()->SetTitleOffset(1.1);
      PredictiveHist->GetXaxis()->SetTitleSize(0.05);
      PredictiveHist->GetYaxis()->SetTitleSize(0.05);

      std::cout << BinMin[iHist] << " " << BinMax[iHist] << std::endl;
      PredictiveHist->GetXaxis()->SetRangeUser(BinMin[iHist],BinMax[iHist]);
      //PredictiveHist->GetYaxis()->SetRange(2,PredictiveHist->GetNbinsY());
      
      PredictiveHist->Draw("COLZ");
      AsymmError->Draw("P SAME");
      SpectraHist->Draw("SAME");

      if (!MadeLegend) {
	Legend = new TLegend(0.7,0.9,0.9,0.94);
	Legend->AddEntry(SpectraHist,"Post-BANFF","l");
	//Legend->SetBorderSize(0);
	MadeLegend = true;
      }

      Legend->Draw("SAME");
      
      Canv->Print(OutputName);
    }
  }

  Canv->Print(OutputName+"]");
}
