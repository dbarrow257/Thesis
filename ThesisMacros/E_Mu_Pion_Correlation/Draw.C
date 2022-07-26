void DrawHist(TString CanvName, TString Title_Short, TString Title_Long) {
  TString FileName = "../../MacroInputs/out_QuickTreePlotter.root";
  TFile* File = new TFile(FileName);

  //File->ls();
  TCanvas* SG0DcyCanv = (TCanvas*)File->Get(CanvName);

  TH2D* Hist;
  TObject *Obj;
  TIter Next(SG0DcyCanv->GetListOfPrimitives());
  while ((Obj=Next())) {
    if (Obj->InheritsFrom("TH2")) {
      Hist = (TH2D*)SG0DcyCanv->GetPrimitive(Obj->GetName());
    }
  }  

  Hist->Rebin2D(5);
  
  Hist->SetStats(false);
  Hist->SetTitle(Title_Long);
  Hist->GetXaxis()->SetTitle("log(L_{e}/L_{#pi})");
  Hist->GetYaxis()->SetTitle("log(L_{e}/L_{#mu})");
  Hist->GetXaxis()->SetTitleSize(0.06);
  Hist->GetYaxis()->SetTitleSize(0.06);

  TText* SG0Text;
  
  if (Title_Short == "SG2Dcy") {
    Hist->GetXaxis()->SetRangeUser(-1000.,3000.);
    Hist->GetYaxis()->SetRangeUser(-1000.,3000.);
    SG0Text = new TText(-600.,2600.,Form("Correlation = %4.3f",Hist->GetCorrelationFactor()));
  } else {
    SG0Text = new TText(-4000.,4000.,Form("Correlation = %4.3f",Hist->GetCorrelationFactor()));
  }
    
  TCanvas* Canv = new TCanvas("Canv_"+Title_Short,"");
  Canv->SetLeftMargin(0.15);
  Canv->SetBottomMargin(0.15);
  Canv->SetRightMargin(0.15);
  Hist->Draw("COLZ");
  SG0Text->Draw("SAME");

  Canv->Print("Correlation_"+Title_Short+".pdf");
}

void Draw() {
  DrawHist("c_dNllemuvseppSG0dcy","SG0Dcy","SubGeV Events with 0 Decay Electrons");
  DrawHist("c_dNllemuvseppSG1dcy","SG1Dcy","SubGeV Events with 1 Decay Electrons");
  DrawHist("c_dNllemuvseppSG2dcy","SG2Dcy","SubGeV Events with 2 Decay Electrons");
}
