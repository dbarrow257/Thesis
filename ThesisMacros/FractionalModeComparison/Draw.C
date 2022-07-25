#include "TStyle.h"

void Draw() {
  gStyle->SetPaintTextFormat("3.2f");
  
  TString FileName = "../../MacroInputs/FractionalModeContribution.root";
  TFile* File = new TFile(FileName);

  TCanvas* Canv = (TCanvas*)File->Get("Canv");
  Canv->Draw();
  
  TH2D* Hist;
  
  TObject *Obj; 
  TIter Next(Canv->GetListOfPrimitives());
  while ((Obj=Next())) {
    if (Obj->InheritsFrom("TH2")) {
      Hist = (TH2D*)Canv->GetPrimitive(Obj->GetName());
    }
  }

  int nSamples = Hist->GetNbinsY();
  std::cout << "There are " << nSamples << " samples" << std::endl;

  int nReducedModes = 10;
  // 0 = CCQE    |  0
  // 1 = 2p2h    |  9
  // 2 = CC1pipm |  1
  // 3 = CCMpi   |  3
  // 4 = CCOther |  2 + 4 + 11 + 12
  // 5 = NC1pi0  |  5
  // 6 = NC1pipm |  6
  // 7 = NCMpi   |  13
  // 8 = NCcoh   |  7
  // 9 = NCOther |  8 + 10 + 14

  TH2D* NewHist = new TH2D("NewHist","",nReducedModes,0,nReducedModes,nSamples,0,nSamples);

  NewHist->SetMarkerSize(2);
  
  NewHist->GetXaxis()->SetBinLabel(1,"CC QE");
  NewHist->GetXaxis()->SetBinLabel(2,"CC 2p2h");
  NewHist->GetXaxis()->SetBinLabel(3,"CC 1#pi^{#pm}");
  NewHist->GetXaxis()->SetBinLabel(4,"CC M#pi");
  NewHist->GetXaxis()->SetBinLabel(5,"CC Other");
  NewHist->GetXaxis()->SetBinLabel(6,"NC 1#pi^{0}");
  NewHist->GetXaxis()->SetBinLabel(7,"NC 1#pi^{#pm}");
  NewHist->GetXaxis()->SetBinLabel(8,"NC M#pi");
  NewHist->GetXaxis()->SetBinLabel(9,"NC Coh.");
  NewHist->GetXaxis()->SetBinLabel(10,"NC Other");

  NewHist->LabelsOption("v");
  
  for (int iSample=0;iSample<nSamples;iSample++) {
    TString BinLabel = Hist->GetYaxis()->GetBinLabel(iSample+1);

    /*
      SubGeV-elike-0dcy
      SubGeV-elike-1dcy
      SubGeV-mulike-0dcy
      SubGeV-mulike-1dcy
      SubGeV-mulike-2dcy
      SubGeV-pi0like
      FHC1Rmu-2020
      RHC1Rmu-2020
      FHC1Re-2020
      RHC1Re-2020
      FHCCC1pi-2020
    */
    
    if (BinLabel == "SubGeV-elike-0dcy") BinLabel = "S.G. e-like 0de";
    if (BinLabel == "SubGeV-elike-1dcy") BinLabel = "S.G. e-like 1de";
    if (BinLabel == "SubGeV-mulike-0dcy") BinLabel = "S.G. #mu-like 0de";
    if (BinLabel == "SubGeV-mulike-1dcy") BinLabel = "S.G. #mu-like 1de";
    if (BinLabel == "SubGeV-mulike-2dcy") BinLabel = "S.G. #mu-like 2de";
    if (BinLabel == "SubGeV-pi0like") BinLabel = "S.G. #pi^{0}-like";
    if (BinLabel == "FHC1Rmu-2020") BinLabel = "FHC 1R #mu-like";
    if (BinLabel == "RHC1Rmu-2020") BinLabel = "RHC 1R #mu-like";
    if (BinLabel == "FHC1Re-2020") BinLabel = "FHC 1R e-like";
    if (BinLabel == "RHC1Re-2020") BinLabel = "RHC 1R e-like";
    if (BinLabel == "FHCCC1pi-2020") BinLabel = "FHC 1R+1d.e. e-like";

    NewHist->GetYaxis()->SetBinLabel(iSample+1,BinLabel);
  }
  
  for (int iSample=0;iSample<nSamples;iSample++) {
    double CCQE = Hist->GetBinContent(1,iSample+1);
    NewHist->SetBinContent(1,iSample+1,CCQE);

    double MEC = Hist->GetBinContent(10,iSample+1);
    NewHist->SetBinContent(2,iSample+1,MEC);

    double CC1pipm = Hist->GetBinContent(2,iSample+1);
    NewHist->SetBinContent(3,iSample+1,CC1pipm);

    double CCMpi = Hist->GetBinContent(4,iSample+1);
    NewHist->SetBinContent(4,iSample+1,CCMpi);

    double CCOther = Hist->GetBinContent(3,iSample+1)+Hist->GetBinContent(5,iSample+1)+Hist->GetBinContent(12,iSample+1)+Hist->GetBinContent(13,iSample+1);
    NewHist->SetBinContent(5,iSample+1,CCOther);

    double NC1pi0 = Hist->GetBinContent(6,iSample+1);
    NewHist->SetBinContent(6,iSample+1,NC1pi0);
    
    double NC1pipm = Hist->GetBinContent(7,iSample+1);
    NewHist->SetBinContent(7,iSample+1,NC1pipm);

    double NCMpi = Hist->GetBinContent(14,iSample+1);
    NewHist->SetBinContent(8,iSample+1,NCMpi);

    double NCCoh = Hist->GetBinContent(8,iSample+1);
    NewHist->SetBinContent(9,iSample+1,NCCoh);

    double NCOther = Hist->GetBinContent(9,iSample+1)+Hist->GetBinContent(11,iSample+1)+Hist->GetBinContent(15,iSample+1);
    NewHist->SetBinContent(10,iSample+1,NCOther);
  }

  for (int iSample=0;iSample<nSamples;iSample++) {
    double Total = 0.;
    for (int iMode=0;iMode<nReducedModes;iMode++) {
      Total += NewHist->GetBinContent(iMode+1,iSample+1);
    }
    std::cout << "Total (" << iSample << "):" << Total << std::endl;
  }

  gStyle->SetOptStat(false);

  NewHist->GetYaxis()->SetLabelSize(0.05);
  NewHist->GetXaxis()->SetLabelSize(0.05);
  
  TCanvas* NewCanv = new TCanvas("NewCanv","");
  NewCanv->SetGridx();
  NewCanv->SetGridy();
  
  NewCanv->SetLeftMargin(0.23);
  NewCanv->SetBottomMargin(0.15);
  NewHist->Draw("COL TEXT0");

  NewCanv->Print("FractionalModeComparison.pdf");
  
}
