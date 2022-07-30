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
      
      //CC_2D->RebinY(2);
      //NC_2D->RebinY(2);
      
      CC_2D->GetYaxis()->SetTitleOffset(1.2);
      NC_2D->GetYaxis()->SetTitleOffset(1.2);
      
      Canv->cd(1);
      CC_2D->Draw("COL");

      Canv->cd(2);
      NC_2D->Draw("COL");

      Canv->Print("2DSpectra_"+SampleName+".pdf");
      
    }
  }
}
