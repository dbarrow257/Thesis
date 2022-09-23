#include <vector>
  
std::vector<TH2D*> GetHists(TFile* File, TString DirName) {
  TDirectory* Dir = (TDirectory*)File->Get(DirName);
  if (!Dir) {
    std::cout << DirName << " not found in File!" << std::endl;
    exit(-1);
  }

  std::vector<TH2D*> ReturnVec;
  
  TKey* Key;
  TIter Next(Dir->GetListOfKeys());
  while ((Key=(TKey*)Next())) {
    TClass *cl = gROOT->GetClass(Key->GetClassName());
    if (cl->InheritsFrom("TH2D")) {
      TH2D* Hist = (TH2D*)(Key->ReadObj());
      ReturnVec.push_back((TH2D*)Hist->Clone());
    }
  }

  return ReturnVec;
}

void Draw_ReacConstaintComp() {
  
  TString FileName = "../../MacroInputs/2DOscLLH/2DLLHOscScan.root";
  TFile* File = new TFile(FileName);

  std::vector<TH2D*> AppScans = GetHists(File,"Appearance");
  int nHists = AppScans.size();

  if (nHists==0) {
    std::cout << "Did not find any hists" << std::endl;
    throw;
  }

  int nSummedHists = 3; //Beam, Atmospheric, All
  std::vector<TString> SummedHistNames(nSummedHists);
  SummedHistNames[0] = "Beam";
  SummedHistNames[1] = "Atmospheric";
  SummedHistNames[2] = "All";
      
  //============================================================
  std::vector<TH2D*> SummedHists_App(nSummedHists);
  for (int iHist=0;iHist<nSummedHists;iHist++) {
    SummedHists_App[iHist] = (TH2D*)AppScans[0]->Clone();
    SummedHists_App[iHist]->Reset();
  }
  
  for (int iHist=0;iHist<nHists;iHist++) {
    TString HistName = (TString(AppScans[iHist]->GetName())).ReplaceAll("_App","");
    
    if (HistName.Contains("2020")) {
      SummedHists_App[0]->Add(AppScans[iHist]);
    } else {
      SummedHists_App[1]->Add(AppScans[iHist]);
    }
    SummedHists_App[2]->Add(AppScans[iHist]);
  }

  TCanvas* Canv = new TCanvas("Canv","");
  Canv->Divide(2);
  
  TH2D* SKApp = (TH2D*)SummedHists_App[1]->Clone();

  for (int xBin=1;xBin<=SKApp->GetNbinsX();xBin++) {
    std::cout << xBin << " " << SKApp->GetXaxis()->GetBinLowEdge(xBin) << std::endl;
  }
  
  TH1D* SKApp_1D = (TH1D*)SKApp->ProjectionY();
  SKApp_1D->SetLineColor(kBlack);
  //SKApp_1D->Scale(1.0/SKApp_1D->Integral());
  TH1D* SKApp_1D_wRC = (TH1D*)SKApp->ProjectionY("Proj",17,22);
  SKApp_1D_wRC->SetLineColor(kRed);
  //SKApp_1D_wRC->Scale(1.0/SKApp_1D_wRC->Integral());
  
  Canv->cd(1);
  SKApp_1D_wRC->Draw("HIST");

  Canv->cd(2);
  SKApp_1D->Draw("HIST SAME");
    
  //======================================================================
}
