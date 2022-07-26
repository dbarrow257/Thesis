void DrawMap(TString MapName) {
  TString FileName = "../../MacroInputs/RCTables_Oct15_2021_T2K_beam_and_SK_atm1_to_14.root";
  TFile* File = new TFile(FileName);
  
  TH2D* RC_1e_Nue = (TH2D*)File->Get(MapName);
  
  //RC_1e_Nue->Smooth();
  RC_1e_Nue->RebinY(5);
  RC_1e_Nue->SetStats(false);
  
  for (int yBin=1;yBin<=RC_1e_Nue->GetNbinsY();yBin++) {
    double Total=0;
    for (int xBin=1;xBin<=RC_1e_Nue->GetNbinsX();xBin++) {
      Total += RC_1e_Nue->GetBinContent(xBin,yBin);
    }
    for (int xBin=1;xBin<=RC_1e_Nue->GetNbinsX();xBin++) {
      if (Total == 0.) {
	RC_1e_Nue->SetBinContent(xBin,yBin,0.);
      } else {
	RC_1e_Nue->SetBinContent(xBin,yBin,RC_1e_Nue->GetBinContent(xBin,yBin)/Total);
      }
    }
  }

  RC_1e_Nue->SetBinContent(1,1,0.0);
  RC_1e_Nue->SetBinContent(2,1,0.0);
  RC_1e_Nue->SetBinContent(1,2,0.0);
  RC_1e_Nue->SetBinContent(2,2,0.0);
    
  RC_1e_Nue->GetXaxis()->SetRangeUser(0.5,4.5);
  //RC_1e_Nue->GetYaxis()->SetRangeUser(-1000.,3500.);
  RC_1e_Nue->GetYaxis()->SetTitleOffset(1.2);
  RC_1e_Nue->GetXaxis()->SetTitle("Number of Reconstructed Rings");
  RC_1e_Nue->GetYaxis()->SetTitle("Ring Counting Parameter");

  if (MapName == "NuFlavour_14_Top_1") {
    RC_1e_Nue->SetTitle("1#mu Final State for True #nu_{#mu} Events");
  } else if (MapName == "NuFlavour_14_Top_3") {
    RC_1e_Nue->SetTitle("1#mu+Other Final State for True #nu_{#mu} Events");
  }
  
  TCanvas* Canv = new TCanvas("CanvName_"+MapName,"");
  RC_1e_Nue->Draw("COLZ");
  Canv->Print(MapName+".pdf");
}

void Draw() {
  DrawMap("NuFlavour_14_Top_1");
  DrawMap("NuFlavour_14_Top_3");
}
