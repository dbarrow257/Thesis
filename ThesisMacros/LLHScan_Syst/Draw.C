void Draw() {
  bool DrawLeg = true;
  
  TString FileName = "../../MacroInputs/LLHScans_Systs/MaCh3-Atmospherics-MCMC_SystLLHScan.root";
  TFile* File = new TFile(FileName);

  TDirectory* Dir;
  TKey* Key;
  
  Dir = (TDirectory*)File->Get("Samples");

  std::vector<TString> SampleNames;
  
  TIter SampleNext(Dir->GetListOfKeys());
  while ((Key=(TKey*)SampleNext())) {
    SampleNames.push_back(Key->GetName());
  }

  int nSamples = SampleNames.size();
  if (SampleNames.size() == 0) {
    std::cout << "No samples found!" << std::endl;
    return;
  }
  for (int iSample=0;iSample<nSamples;iSample++) {
    std::cout << SampleNames[iSample] << std::endl;
  }
  
  Dir = (TDirectory*)File->Get("Samples/"+SampleNames[0]);

  std::vector<TString> SystNames;

  TIter SystNext(Dir->GetListOfKeys());
  while ((Key=(TKey*)SystNext())) {
    TString SystName = (TString(Key->GetName()).ReplaceAll(SampleNames[0],TString(""))).Replace(0,1,"");
    SystNames.push_back(SystName);
  }

  int nSysts = SystNames.size();
  if (nSysts == 0) {
    std::cout << "No systs found!" << std::endl;
    return;
  }
  for (int iSyst=0;iSyst<nSysts;iSyst++) {
    std::cout << SystNames[iSyst] << std::endl;
  }
  
  TString OutputName = "LLHScans_Systs.pdf";
  TCanvas* Canv = new TCanvas("Canv","");
  Canv->Print(OutputName+"[");

  for (int iSyst=0;iSyst<nSysts;iSyst++) {

    int nHists;
    std::vector<TH1D*> Hists;
    std::vector<int> HistColors;
    std::vector<TString> HistNames;

    /*
    SubGeV-elike-0dcy
      SubGeV-elike-1dcy
      SubGeV-mulike-0dcy
      SubGeV-mulike-1dcy
      SubGeV-mulike-2dcy
      SubGeV-pi0like
      MultiGeV-elike-nue
      MultiGeV-elike-nuebar
      MultiGeV-mulike
      MultiRing-elike-nue
      MultiRing-elike-nuebar
      MultiRing-mulike
      MultiRingOther-1
      PCStop
      PCThru
      UpStop-mu
      UpThruNonShower-mu
      UpThruShower-mu
      FHC1Rmu-2020
      RHC1Rmu-2020
      FHC1Re-2020
      RHC1Re-2020
      FHCCC1pi-2020
    */

    nHists = 6;
    Hists.resize(nHists); //Beam E, Beam Mu, SG E, SG Mu, MG, PC + Upmu
    
    HistNames.resize(nHists);
    HistNames[0] = "SubGeV e-like";
    HistNames[1] = "SubGeV #mu-like";
    HistNames[2] = "MultiGeV";
    HistNames[3] = "PC + Up-#mu";
    HistNames[4] = "Beam FD";
    HistNames[5] = "Beam ND";
    
    HistColors.resize(nHists);
    HistColors[0] = kGreen+2;
    HistColors[1] = kRed;
    HistColors[2] = kMagenta;
    HistColors[3] = kBlue;
    HistColors[4] = kOrange+1;
    HistColors[5] = kBlack;
    
    Hists[0] = (TH1D*)File->Get("Samples/SubGeV-elike-0dcy/SubGeV-elike-0dcy_"+SystNames[iSyst]);
    Hists[0]->Add((TH1D*)File->Get("Samples/SubGeV-elike-1dcy/SubGeV-elike-1dcy_"+SystNames[iSyst]));
    Hists[0]->Add((TH1D*)File->Get("Samples/SubGeV-pi0like/SubGeV-pi0like_"+SystNames[iSyst]));
    
    Hists[1] = (TH1D*)File->Get("Samples/SubGeV-mulike-0dcy/SubGeV-mulike-0dcy_"+SystNames[iSyst]);
    Hists[1]->Add((TH1D*)File->Get("Samples/SubGeV-mulike-1dcy/SubGeV-mulike-1dcy_"+SystNames[iSyst]));
    Hists[1]->Add((TH1D*)File->Get("Samples/SubGeV-mulike-2dcy/SubGeV-mulike-2dcy_"+SystNames[iSyst]));
    
    Hists[2] = (TH1D*)File->Get("Samples/MultiGeV-elike-nue/MultiGeV-elike-nue_"+SystNames[iSyst]);
    Hists[2]->Add((TH1D*)File->Get("Samples/MultiRing-elike-nue/MultiRing-elike-nue_"+SystNames[iSyst]));
    Hists[2]->Add((TH1D*)File->Get("Samples/MultiGeV-elike-nuebar/MultiGeV-elike-nuebar_"+SystNames[iSyst]));
    Hists[2]->Add((TH1D*)File->Get("Samples/MultiRing-elike-nuebar/MultiRing-elike-nuebar_"+SystNames[iSyst]));
    Hists[2]->Add((TH1D*)File->Get("Samples/MultiGeV-mulike/MultiGeV-mulike_"+SystNames[iSyst]));
    Hists[2]->Add((TH1D*)File->Get("Samples/MultiRing-mulike/MultiRing-mulike_"+SystNames[iSyst]));
    Hists[2]->Add((TH1D*)File->Get("Samples/MultiRingOther-1/MultiRingOther-1_"+SystNames[iSyst]));
    
    Hists[3] = (TH1D*)File->Get("Samples/PCStop/PCStop_"+SystNames[iSyst]);
    Hists[3]->Add((TH1D*)File->Get("Samples/PCThru/PCThru_"+SystNames[iSyst]));
    Hists[3]->Add((TH1D*)File->Get("Samples/UpStop-mu/UpStop-mu_"+SystNames[iSyst]));
    Hists[3]->Add((TH1D*)File->Get("Samples/UpThruNonShower-mu/UpThruNonShower-mu_"+SystNames[iSyst]));
    Hists[3]->Add((TH1D*)File->Get("Samples/UpThruShower-mu/UpThruShower-mu_"+SystNames[iSyst]));
    
    Hists[4] = (TH1D*)File->Get("Samples/FHC1Re-2020/FHC1Re-2020_"+SystNames[iSyst]);
    Hists[4]->Add((TH1D*)File->Get("Samples/RHC1Re-2020/RHC1Re-2020_"+SystNames[iSyst]));
    Hists[4]->Add((TH1D*)File->Get("Samples/FHCCC1pi-2020/FHCCC1pi-2020_"+SystNames[iSyst]));
    Hists[4]->Add((TH1D*)File->Get("Samples/FHC1Rmu-2020/FHC1Rmu-2020_"+SystNames[iSyst]));
    Hists[4]->Add((TH1D*)File->Get("Samples/RHC1Rmu-2020/RHC1Rmu-2020_"+SystNames[iSyst]));

    Hists[5] = (TH1D*)File->Get("Samples/ND/ND_"+SystNames[iSyst]);
    
    //Hists[0]->SetTitle("");
    Hists[0]->SetTitle("");
    Hists[0]->GetYaxis()->SetTitle("-2 #times ln(Likelihood)");
    Hists[0]->GetXaxis()->SetTitle("Dial Value");
    Hists[0]->GetYaxis()->SetTitleOffset(0.95);
    Hists[0]->GetXaxis()->SetTitleOffset(0.95);

    Hists[0]->GetXaxis()->SetTitleSize(0.05);
    Hists[0]->GetYaxis()->SetTitleSize(0.05);

    double Max = -1e8;
    for (int iHist=0;iHist<nHists;iHist++) {
      Hists[iHist]->SetLineColor(HistColors[iHist]);
      if (Hists[iHist]->GetMaximum() > Max) Max = Hists[iHist]->GetMaximum();
    }

    for (int iHist=0;iHist<nHists;iHist++) {
      Hists[iHist]->SetMaximum(Max*1.1);
    }

    Canv->cd();
    Canv->SetLeftMargin(0.1);
    Canv->SetTopMargin(0.01);
    Canv->SetBottomMargin(0.1);
    Canv->SetRightMargin(0.02);

    if (DrawLeg) {
      TLegend* Leg = new TLegend(0.1,0.1,0.9,0.9);
      
      Leg->SetTextSize(0.09);
      for (int iHist=0;iHist<nHists;iHist++) {
	Leg->AddEntry(Hists[iHist],HistNames[iHist],"l");
      }
      Leg->Draw();
      Canv->Print(OutputName);
      Canv->Clear();

      DrawLeg = false;
    }

    for (int iHist=0;iHist<nHists;iHist++) {
      if (iHist==0) {
	Hists[iHist]->Draw();
      } else {
	Hists[iHist]->Draw("SAME");
      }
    }
    Canv->Print(OutputName);

    nHists = 0;
    Hists.clear();
    HistNames.clear();
    Canv->Clear();
  }

  Canv->Print(OutputName+"]");
}
