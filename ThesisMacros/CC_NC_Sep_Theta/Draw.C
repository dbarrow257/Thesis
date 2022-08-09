void Draw() {
  gStyle->SetOptStat(false);
  
  bool DrawLegend = true;
  
  TString FileName = "../../MacroInputs/Spectra/SpectraByMode.root";
  TFile* File = new TFile(FileName);

  TCanvas* Canv = new TCanvas("Canv","");
  Canv->Divide(2,1);
  Canv->SetLeftMargin(0.15);
  Canv->SetBottomMargin(0.15);
  
  TDirectory* Dir;
  TKey *Key;
  TIter Next(File->GetListOfKeys());
  while ((Key=(TKey*)Next())) {
    TClass *Cl = gROOT->GetClass(Key->GetClassName());
    if (Cl->InheritsFrom("TDirectory")) {
      Dir = (TDirectory*)Key->ReadObj();
      Dir->cd();

      TString SampleName = Key->GetName();
      if (!(SampleName.Contains("1Re") || SampleName.Contains("CC1pi"))) continue;
      
      TH2D* CC_2D = (TH2D*)Dir->Get("CCQE");
      CC_2D->Add((TH2D*)Dir->Get("2p2h"));
      CC_2D->Add((TH2D*)Dir->Get("CC1pipm"));
      CC_2D->Add((TH2D*)Dir->Get("CCMpi"));
      CC_2D->Add((TH2D*)Dir->Get("CCcoh"));
      CC_2D->Add((TH2D*)Dir->Get("CCDIS"));
      CC_2D->Add((TH2D*)Dir->Get("CCMisc"));
      CC_2D->Add((TH2D*)Dir->Get("CC1pi0"));
      
      TH2D* NC_2D = (TH2D*)Dir->Get("NCoth");
      NC_2D->Add((TH2D*)Dir->Get("NC1pi0"));
      NC_2D->Add((TH2D*)Dir->Get("NC1gam"));
      NC_2D->Add((TH2D*)Dir->Get("NC1pipm"));
      NC_2D->Add((TH2D*)Dir->Get("NCMpi"));
      NC_2D->Add((TH2D*)Dir->Get("NCcoh"));
      NC_2D->Add((TH2D*)Dir->Get("NCDIS"));

      TH1D* CC_1D = (TH1D*)(CC_2D->ProjectionY())->Clone();
      TH1D* NC_1D = (TH1D*)(NC_2D->ProjectionY())->Clone();
      
      CC_1D->SetTitle("Charged Current Modes");
      NC_1D->SetTitle("Neutral Current Modes");
      CC_1D->GetXaxis()->SetTitle("Reconstructed Lepton Theta [Deg]");
      NC_1D->GetXaxis()->SetTitle("Reconstructed Lepton Theta [Deg]");
      CC_1D->GetYaxis()->SetTitle("Events/Bin");
      NC_1D->GetYaxis()->SetTitle("Events/Bin");
      
      //CC_2D->RebinY(2);
      //NC_2D->RebinY(2);

      CC_1D->SetTitleSize(0.05);
      CC_1D->GetXaxis()->SetTitleSize(0.05);
      CC_1D->GetYaxis()->SetTitleSize(0.05);
      NC_1D->SetTitleSize(0.05);
      NC_1D->GetXaxis()->SetTitleSize(0.05);
      NC_1D->GetYaxis()->SetTitleSize(0.05);
      
      TPad* Pad1 = (TPad*)Canv->cd(1);
      //Pad1->SetRightMargin(0.2);
      Pad1->SetLeftMargin(0.13);
      CC_1D->Draw();

      TLegend* Leg1 = new TLegend(0.4,0.7,0.89,0.89);
      Leg1->SetBorderSize(0.);
      Leg1->SetTextSize(0.06);
      Leg1->SetFillStyle(0);
      Leg1->AddEntry((TObject*)0,Form("Mean = %2.2f#circ",CC_1D->GetMean()),"");
      Leg1->AddEntry((TObject*)0,Form("RMS = %2.2f#circ",CC_1D->GetRMS()),"");
      Leg1->Draw("SAME");

      TPad* Pad2 = (TPad*)Canv->cd(2);
      //Pad2->SetRightMargin(0.2);
      Pad2->SetLeftMargin(0.13);
      NC_1D->Draw();

      TLegend* Leg2 = new TLegend(0.4,0.7,0.89,0.89);
      Leg2->SetBorderSize(0.);
      Leg2->SetTextSize(0.06);
      Leg2->SetFillStyle(0);
      Leg2->AddEntry((TObject*)0,Form("Mean = %2.2f#circ",NC_1D->GetMean()),"");
      Leg2->AddEntry((TObject*)0,Form("RMS = %2.2f#circ",NC_1D->GetRMS()),"");
      Leg2->Draw("SAME");

      Canv->Print("1DSpectra_"+SampleName+".pdf");
      
    }
  }
}
