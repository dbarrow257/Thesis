void Draw() {
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

      CC_2D->SetTitle("Charged Current Modes");
      NC_2D->SetTitle("Neutral Current Modes");
      CC_2D->GetZaxis()->SetTitle("Events/Bin");
      NC_2D->GetZaxis()->SetTitle("Events/Bin");
      
      //CC_2D->RebinY(2);
      //NC_2D->RebinY(2);

      CC_2D->SetTitleSize(0.05);
      CC_2D->GetXaxis()->SetTitleSize(0.05);
      CC_2D->GetYaxis()->SetTitleSize(0.05);
      CC_2D->GetZaxis()->SetTitleSize(0.05);
      NC_2D->SetTitleSize(0.05);
      NC_2D->GetXaxis()->SetTitleSize(0.05);
      NC_2D->GetYaxis()->SetTitleSize(0.05);
      NC_2D->GetZaxis()->SetTitleSize(0.05);
      
      CC_2D->GetZaxis()->SetTitleOffset(1.2);
      NC_2D->GetZaxis()->SetTitleOffset(1.2);
      
      TPad* Pad1 = (TPad*)Canv->cd(1);
      Pad1->SetRightMargin(0.2);
      Pad1->SetLeftMargin(0.12);
      CC_2D->Draw("COLZ");

      TPad* Pad2 = (TPad*)Canv->cd(2);
      Pad2->SetRightMargin(0.2);
      Pad2->SetLeftMargin(0.12);
      NC_2D->Draw("COLZ");

      Canv->Print("2DSpectra_"+SampleName+".pdf");
      
    }
  }
}
