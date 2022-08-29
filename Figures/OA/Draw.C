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

void Draw(TString DirName) {
  
  TString FileName = "../../MacroInputs/AsimovVsEvalLLHScans/LLHScan.root";
  TFile* File = new TFile(FileName);

  std::vector<TH2D*> Scans = GetHists(File,DirName);
  int nHists = Scans.size();

  if (nHists==0) {
    std::cout << "Did not find any hists" << std::endl;
    throw;
  }

  double Contours_1Sig[1];
  Contours_1Sig[0] = 1.0;

  double Contours_2Sig[1];
  Contours_2Sig[0] = 4.0;
  
  int nSummedHists = 3; //Beam, Atmospheric, All
  std::vector<TString> SummedHistNames(nSummedHists);
  SummedHistNames[0] = "Beam";
  SummedHistNames[1] = "Atmospheric";
  SummedHistNames[2] = "All";
      
  //============================================================
  std::vector<TH2D*> SummedHists(nSummedHists);
  for (int iHist=0;iHist<nSummedHists;iHist++) {
    SummedHists[iHist] = (TH2D*)Scans[0]->Clone();
    SummedHists[iHist]->Reset();
    //SummedHists[iHist]->SetTitle(SummedHistNames[iHist]);
    if (DirName == "DCP") {
      SummedHists[iHist]->GetXaxis()->SetTitle("#delta_{CP} Asimov Point");
      SummedHists[iHist]->GetYaxis()->SetTitle("#delta_{CP} Evaluation Point");
    } else if (DirName == "TH23") {
      SummedHists[iHist]->GetXaxis()->SetTitle("sin^{2}(2#theta_{23}) Asimov Point");
      SummedHists[iHist]->GetYaxis()->SetTitle("sin^{2}(2#theta_{23}) Evaluation Point");
    }
  }
  
  for (int iHist=0;iHist<nHists;iHist++) {
    TString HistName = (TString(Scans[iHist]->GetName())).ReplaceAll("","");
    
    if (HistName.Contains("2020")) {
      SummedHists[0]->Add(Scans[iHist]);
    } else {
      SummedHists[1]->Add(Scans[iHist]);
    }
    SummedHists[2]->Add(Scans[iHist]);
  }
  
  TString OutputName = DirName+"_Scans.pdf";
  TCanvas* Canv = new TCanvas("Canv","");
  Canv->SetRightMargin(0.15);
  Canv->SetTopMargin(0.02);
  Canv->SetBottomMargin(0.15);
  Canv->SetLeftMargin(0.15);
  Canv->Print(OutputName+"[");

  double Max = -1e8;
  for (int iHist=0;iHist<nSummedHists;iHist++) {
    if (SummedHists[iHist]->GetMaximum() > Max) Max = SummedHists[iHist]->GetMaximum();
  }
  for (int iHist=0;iHist<nSummedHists;iHist++) {
    SummedHists[iHist]->SetMaximum(Max);
  }
  
  for (int iHist=0;iHist<nSummedHists;iHist++) {

    SummedHists[iHist]->Draw("COLZ");

    TH2D* CloneHist_1Sig = (TH2D*)SummedHists[iHist]->Clone();
    CloneHist_1Sig->SetContour(1,Contours_1Sig);
    CloneHist_1Sig->SetLineColor(kRed);
    CloneHist_1Sig->SetLineStyle(kDashed);
    CloneHist_1Sig->Draw("cont3 SAME");

    TH2D* CloneHist_2Sig = (TH2D*)SummedHists[iHist]->Clone();
    CloneHist_2Sig->SetContour(1,Contours_2Sig);
    CloneHist_2Sig->SetLineColor(kRed);
    CloneHist_2Sig->Draw("cont3 SAME");

    Canv->Print(OutputName);
  }
  Canv->Print(OutputName+"]");
  //============================================================
}
