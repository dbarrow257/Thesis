void DrawDist(TString DistName, TString SaveName) {
  TString FileName = "../../MacroInputs/AtmDetHists_ByTopology.root";
  TFile* File = new TFile(FileName);

  TCanvas* SG0DcyCanv = (TCanvas*)File->Get(DistName);
  
  THStack* Stack;
  TObject *Obj;
  TIter Next(SG0DcyCanv->GetListOfPrimitives());
  while ((Obj=Next())) {
    if (Obj->InheritsFrom("THStack")) {
      Stack = (THStack*)SG0DcyCanv->GetPrimitive(Obj->GetName());
    }
  }

  Stack->SetTitle("");
  Stack->GetXaxis()->SetTitleSize(0.05);
  Stack->GetYaxis()->SetTitleSize(0.05);
  Stack->GetYaxis()->SetTitle("Events");

  TCanvas* NewCanv = new TCanvas("NewCanv_"+SaveName,"");
  NewCanv->SetLeftMargin(0.15);
  NewCanv->SetBottomMargin(0.15);
  Stack->Draw();

  NewCanv->Print(SaveName+".pdf");
}

void Draw() {
  DrawDist("SKDetSystDists_SubGeV-elike-0dcy_RCPar","RCParam_SGE0Dcy");
  DrawDist("SKDetSystDists_MultiRing-elike-nue_RCPar","RCParam_MRENue");

  TCanvas* LegCanv = new TCanvas("LegCanv","");
  TString FileName = "../../MacroInputs/AtmDetHists_ByTopology.root";
  TFile* File = new TFile(FileName);
  TLegend* Legend = (TLegend*)File->Get("Legend");

  TObject *Obj;
  TIter Next(Legend->GetListOfPrimitives());
  int counter = 0;
  while ((Obj=Next())) {
    TLegendEntry* Entry = (TLegendEntry*)Obj;
    if (counter == 5) {
      Entry->SetLabel("1#pi^{#pm} or 1Proton");
    }
    counter += 1;
  }
  
  Legend->Draw();
  LegCanv->Print("RCParameterLegend.pdf");
}
