void AtmFluxSystSize() {

  double ScalingFactor = 4;
  
  double xlow = 0.1; //GeV 
  double xhigh = 1000.; //GeV
  int nBins = 1000;
  int nBins_Hist = 50;

  std::vector<double> CalcPoints(nBins+1);
  for (int iBin=0;iBin<(nBins+1);iBin++) {
    CalcPoints[iBin] = pow(10,TMath::Log10(xlow)+(double)iBin*(TMath::Log10(xhigh)-TMath::Log10(xlow))/(double)nBins);
  }

  std::vector<double> CalcPoints_Hist(nBins_Hist+1);
  for (int iBin=0;iBin<(nBins_Hist+1);iBin++) {
    CalcPoints_Hist[iBin] = pow(10,TMath::Log10(xlow)+(double)iBin*(TMath::Log10(xhigh)-TMath::Log10(xlow))/(double)nBins_Hist);
  }

  TString OutputName = "AtmFluxSystSize.pdf";
  TCanvas* Canv = new TCanvas("DummyCanv","");
  Canv->Print(OutputName+"[");
 
  //================================================================================================================================================

  int nFlavours = 4; // nue, numu, nueb, numub
  std::vector<TH1D*> FluxDists(nFlavours);
  std::vector<TString> FlavNames(nFlavours);
  FlavNames[0] = "NuE";
  FlavNames[1] = "NuMu";
  FlavNames[2] = "NuEB";
  FlavNames[3] = "NuMuB";
  
  for (int iFlav=0;iFlav<nFlavours;iFlav++) {
    FluxDists[iFlav] = new TH1D(FlavNames[iFlav],"",nBins_Hist,CalcPoints_Hist.data());
    FluxDists[iFlav]->SetFillStyle(4020);
    FluxDists[iFlav]->SetFillColor(kGray);
    FluxDists[iFlav]->SetLineColor(kBlack);
  }
  
  TFile* File = new TFile("ParsedOutput.root");
  TTree* Tree = (TTree*)File->Get("ParsedMTuple");

  float Energy;
  double Weight;
  int Flavour;

  Tree->SetBranchAddress("Energy",&Energy);
  Tree->SetBranchAddress("FluxWeight",&Weight);
  Tree->SetBranchAddress("Flavour",&Flavour);

  int nEntries = Tree->GetEntries();
  for (int iEntry=0;iEntry<nEntries;iEntry++) {
    Tree->GetEntry(iEntry);
    if ((iEntry % (nEntries/100))==0) {
      std::cout << iEntry << "/" << nEntries << std::endl;
    }

    if (Flavour == 1) {
      FluxDists[0]->Fill(Energy,Weight);
    } else if (Flavour == 2) {
      FluxDists[1]->Fill(Energy,Weight);
    } else if (Flavour == -1) {
      FluxDists[2]->Fill(Energy,Weight);
    } else if (Flavour == -2) {
      FluxDists[3]->Fill(Energy,Weight);
    } else {
      std::cout << "Did not find flavour:" << Flavour << std::endl;
    }
  }

  for (int iFlav=0;iFlav<nFlavours;iFlav++) {
    FluxDists[iFlav]->Scale((1.0/FluxDists[iFlav]->Integral())*ScalingFactor);
  }
  
  //================================================================================================================================================

  std::vector<double> Responses_Norm(nBins+1);
  std::vector<double> Responses_NuNubar(nBins+1);
  std::vector<double> Responses_NuENuEbar(nBins+1);
  std::vector<double> Responses_NuMuNuMubar(nBins+1);
  for (int iBin=0;iBin<(nBins+1);iBin++) {
    Responses_Norm[iBin] = -999;
    Responses_NuNubar[iBin] = -999;
    Responses_NuENuEbar[iBin] = -999;
    Responses_NuMuNuMubar[iBin] = -999;
  }
  
  for (int iBin=0;iBin<(nBins+1);iBin++) {
    double Energy = CalcPoints[iBin];

    //Normalisation
    if (Energy <= 1.) {
      Responses_Norm[iBin] = 0.07 - 0.18*TMath::Log10(Energy);
    } else if (Energy <= 10.) {
      Responses_Norm[iBin] = 0.07;
    } else if (Energy <= 100.) {
      Responses_Norm[iBin] = 0.02 + 0.05*TMath::Log10(Energy);
    } else if (Energy <= 1000.) {
      Responses_Norm[iBin] = -0.04 + 0.08*TMath::Log10(Energy);
    }

    //nu\nubar
    if (Energy <= 1.) {
      Responses_NuNubar[iBin] = 0.02;
    } else if (Energy <= 10.) {
      Responses_NuNubar[iBin] = 0.03;
    } else if (Energy <= 30.) {
      Responses_NuNubar[iBin] = 0.05;
    } else if (Energy <= 1000.) {
      Responses_NuNubar[iBin] = 1.0-(-0.162*TMath::Log10(Energy)+1.176);
    }

    //nue\nuebar
    if (Energy <= 1.) {
      Responses_NuENuEbar[iBin] = 0.05;
    } else if (Energy <= 10.) {
      Responses_NuENuEbar[iBin] = 0.05;
    } else if (Energy <= 100.) {
      Responses_NuENuEbar[iBin] = 0.08;
    } else if (Energy <= 1000.) {
      Responses_NuENuEbar[iBin] = 1.0-(-0.134*TMath::Log10(Energy)+1.205);
    }

    //numu\numubar
    if (Energy <= 1.) {
      Responses_NuMuNuMubar[iBin] = 0.02;
    } else if (Energy <= 10.) {
      Responses_NuMuNuMubar[iBin] = 0.06;
    } else if (Energy <= 50.) {
      Responses_NuMuNuMubar[iBin] = 0.06;
    } else if (Energy <= 1000.) {
      Responses_NuMuNuMubar[iBin] = 1.0-(-0.210*TMath::Log10(Energy)+1.245);
    }
  }

  for (int iBin=0;iBin<(nBins+1);iBin++) {
    if (Responses_Norm[iBin] == -999 || Responses_NuNubar[iBin] == -999 || Responses_NuENuEbar[iBin] == -999 || Responses_NuMuNuMubar[iBin] == -999) {
      std::cout << "Value not set!" << std::endl;
      return;
    }
  }

  TH1D* DummyHist = new TH1D("DummyHist","",nBins,CalcPoints.data());
  DummyHist->GetYaxis()->SetRangeUser(0.,0.5);
  DummyHist->GetXaxis()->SetTitle("Neutrino Energy [GeV]");
  DummyHist->GetYaxis()->SetTitle("Uncertainty (%)");
  DummyHist->GetXaxis()->SetTitleSize(0.05);
  DummyHist->GetYaxis()->SetTitleSize(0.05);
  DummyHist->SetStats(false);
  
  TGraph* Graph_Norm = new TGraph(nBins+1,CalcPoints.data(),Responses_Norm.data());
  Graph_Norm->SetLineColor(kBlack);

  TGraph* Graph_NuNubar = new TGraph(nBins+1,CalcPoints.data(),Responses_NuNubar.data());
  Graph_NuNubar->SetLineColor(kRed);

  TGraph* Graph_NuENuEbar = new TGraph(nBins+1,CalcPoints.data(),Responses_NuENuEbar.data());
  Graph_NuENuEbar->SetLineColor(kBlue);

  TGraph* Graph_NuMuNuMubar = new TGraph(nBins+1,CalcPoints.data(),Responses_NuMuNuMubar.data());
  Graph_NuMuNuMubar->SetLineColor(kBlue);
  
  //================================================================================================================================================
  //NuE
    
  TCanvas* Canv_NuE = new TCanvas("Canv_NuE","");
  Canv_NuE->SetLeftMargin(0.15);
  Canv_NuE->SetBottomMargin(0.15);
  Canv_NuE->SetLogx(true);
  DummyHist->Draw();

  FluxDists[0]->Draw("SAME HIST");
  Graph_Norm->Draw("SAME");
  Graph_NuNubar->Draw("SAME");
  Graph_NuENuEbar->Draw("SAME");
  
  TLegend* Leg_NuE = new TLegend(0.45,0.6,0.7,0.89);
  Leg_NuE->SetBorderSize(0.);
  Leg_NuE->SetFillStyle(0.);
  Leg_NuE->SetTextSize(0.05);
  Leg_NuE->AddEntry(Graph_Norm,"Total Norm.","l");
  Leg_NuE->AddEntry(Graph_NuNubar,"(#bar{#nu}_{#mu}+#nu_{#mu})/(#bar{#nu}_{e}+#nu_{e}) Ratio","l");
  Leg_NuE->AddEntry(Graph_NuENuEbar,"#bar{#nu}_{e}/#nu_{e} Ratio","l");
  Leg_NuE->AddEntry(FluxDists[2],"Pred. #nu_{e} Flux (A.U.)","f");
  Leg_NuE->Draw("SAME");

  Canv_NuE->Print("AtmFluxSyst_NuE.pdf");
  Canv_NuE->Print(OutputName);
  
  //================================================================================================================================================
  //NuEbar
    
  TCanvas* Canv_NuEbar = new TCanvas("Canv_NuEbar","");
  Canv_NuEbar->SetLeftMargin(0.15);
  Canv_NuEbar->SetBottomMargin(0.15);
  Canv_NuEbar->SetLogx(true);
  DummyHist->Draw();

  FluxDists[2]->Draw("SAME HIST");
  Graph_Norm->Draw("SAME");
  Graph_NuNubar->Draw("SAME");
  Graph_NuENuEbar->Draw("SAME");
  
  TLegend* Leg_NuEbar = new TLegend(0.45,0.6,0.7,0.89);
  Leg_NuEbar->SetBorderSize(0.);
  Leg_NuEbar->SetFillStyle(0.);
  Leg_NuEbar->SetTextSize(0.05);
  Leg_NuEbar->AddEntry(Graph_Norm,"Total Norm.","l");
  Leg_NuEbar->AddEntry(Graph_NuNubar,"(#bar{#nu}_{#mu}+#nu_{#mu})/(#bar{#nu}_{e}+#nu_{e}) Ratio","l");
  Leg_NuEbar->AddEntry(Graph_NuENuEbar,"#bar{#nu}_{e}/#nu_{e} Ratio","l");
  Leg_NuEbar->AddEntry(FluxDists[2],"Pred. #bar{#nu}_{e} Flux (A.U.)","f");
  Leg_NuEbar->Draw("SAME");

  Canv_NuEbar->Print("AtmFluxSyst_NuEbar.pdf");
  Canv_NuEbar->Print(OutputName);
  
  //================================================================================================================================================
  //NuMu
    
  TCanvas* Canv_NuMu = new TCanvas("Canv_NuMu","");
  Canv_NuMu->SetLeftMargin(0.15);
  Canv_NuMu->SetBottomMargin(0.15);
  Canv_NuMu->SetLogx(true);
  DummyHist->Draw();

  FluxDists[1]->Draw("SAME HIST");
  Graph_Norm->Draw("SAME");
  Graph_NuNubar->Draw("SAME");
  Graph_NuMuNuMubar->Draw("SAME");
  
  TLegend* Leg_NuMu = new TLegend(0.45,0.6,0.7,0.89);
  Leg_NuMu->SetBorderSize(0.);
  Leg_NuMu->SetFillStyle(0.);
  Leg_NuMu->SetTextSize(0.05);
  Leg_NuMu->AddEntry(Graph_Norm,"Total Norm.","l");
  Leg_NuMu->AddEntry(Graph_NuNubar,"(#bar{#nu}_{#mu}+#nu_{#mu})/(#bar{#nu}_{e}+#nu_{e}) Ratio","l");
  Leg_NuMu->AddEntry(Graph_NuMuNuMubar,"#bar{#nu}_{#mu}/#nu_{#mu} Ratio","l");
  Leg_NuMu->AddEntry(FluxDists[1],"Pred. #nu_{#mu} Flux (A.U.)","f");
  Leg_NuMu->Draw("SAME");

  Canv_NuMu->Print("AtmFluxSyst_NuMu.pdf");
  Canv_NuMu->Print(OutputName);
  
  //================================================================================================================================================
  //NuMu
    
  TCanvas* Canv_NuMubar = new TCanvas("Canv_NuMubar","");
  Canv_NuMubar->SetLeftMargin(0.15);
  Canv_NuMubar->SetBottomMargin(0.15);
  Canv_NuMubar->SetLogx(true);
  DummyHist->Draw();

  FluxDists[3]->Draw("SAME HIST");
  Graph_Norm->Draw("SAME");
  Graph_NuNubar->Draw("SAME");
  Graph_NuMuNuMubar->Draw("SAME");
  
  TLegend* Leg_NuMubar = new TLegend(0.45,0.6,0.7,0.89);
  Leg_NuMubar->SetBorderSize(0.);
  Leg_NuMubar->SetFillStyle(0.);
  Leg_NuMubar->SetTextSize(0.05);
  Leg_NuMubar->AddEntry(Graph_Norm,"Total Norm.","l");
  Leg_NuMubar->AddEntry(Graph_NuNubar,"(#bar{#nu}_{#mu}+#nu_{#mu})/(#bar{#nu}_{e}+#nu_{e}) Ratio","l");
  Leg_NuMubar->AddEntry(Graph_NuMuNuMubar,"#bar{#nu}_{#mu}/#nu_{#mu} Ratio","l");
  Leg_NuMubar->AddEntry(FluxDists[3],"Pred. #bar{#nu}_{#mu} Flux (A.U.)","f");
  Leg_NuMubar->Draw("SAME");

  Canv_NuMubar->Print("AtmFluxSyst_NuMubar.pdf");
  Canv_NuMubar->Print(OutputName);

  Canv->Print(OutputName+"]");
}
