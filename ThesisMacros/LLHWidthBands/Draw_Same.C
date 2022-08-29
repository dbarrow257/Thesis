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

void Draw_Same(TString DirName, int Sigma) {
  
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

  std::vector<int> SummedHistColors(nSummedHists);
  SummedHistColors[0] = 1;
  SummedHistColors[1] = 2;
  SummedHistColors[2] = 4;
      
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
      SummedHists[iHist]->GetXaxis()->SetTitle("sin^{2}(#theta_{23}) Asimov Point");
      SummedHists[iHist]->GetYaxis()->SetTitle("sin^{2}(#theta_{23}) Evaluation Point");
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
  
  TString OutputName = DirName+"_Scans"+Form("_%iSig.pdf",Sigma);
  TCanvas* Canv = new TCanvas("Canv","");
  TPad* Pad = (TPad*)Canv->cd(1);
  Pad->Draw();
  Pad->cd();
  Canv->SetRightMargin(0.15);
  Canv->SetTopMargin(0.02);
  Canv->SetBottomMargin(0.15);
  Canv->SetLeftMargin(0.15);

  double Max = -1e8;
  for (int iHist=0;iHist<nSummedHists;iHist++) {
    if (SummedHists[iHist]->GetMaximum() > Max) Max = SummedHists[iHist]->GetMaximum();
  }
  for (int iHist=0;iHist<nSummedHists;iHist++) {
    SummedHists[iHist]->SetMaximum(Max);
  }

  //gStyle->SetHatchesSpacing(0.01);
  //gStyle->SetHatchesLineWidth(1);
  
  std::vector<TH2D*> Contours(nSummedHists);
  for (int iHist=0;iHist<nSummedHists;iHist++) {
    TH2D* CloneHist_1Sig = (TH2D*)SummedHists[iHist]->Clone();
    if (Sigma == 1) {
      CloneHist_1Sig->SetContour(1,Contours_1Sig);
    } else if (Sigma == 2) {
      CloneHist_1Sig->SetContour(1,Contours_2Sig);
    } else {
      std::cout << "Sigma value not defined:" << Sigma << std::endl;
    }
    CloneHist_1Sig->SetLineColor(SummedHistColors[iHist]);
    CloneHist_1Sig->SetLineStyle(kSolid);
    // CloneHist_1Sig->SetFillColor(SummedHistColors[iHist]);
    CloneHist_1Sig->SetFillStyle(3020);
    CloneHist_1Sig->SetFillColorAlpha(SummedHistColors[iHist], 0.35);
    Contours[iHist] = (TH2D*)CloneHist_1Sig->Clone();
  }

  TText* Text;  
  TLegend* Legend;

  TString HeaderText;
  if (Sigma == 1) {
    HeaderText = "1#sigma C.I.";
  } else if (Sigma == 2) {
    HeaderText = "2#sigma C.I.";
  } else {
    std::cout   << "Sigma value not defined:" << Sigma << std::endl;
  }
  
  if (DirName=="DCP") {
    Legend = new TLegend(0.855,0.16,1.0,0.35,HeaderText);
    Text = new TText(-0.5,-0.6,"Included");
    Text->SetTextAngle(41);
  } else {
    Legend = new TLegend(0.855,0.16,1.0,0.35,HeaderText);
    Text = new TText(0.48,0.47,"Included");
    Text->SetTextAngle(40);
  }
  Legend->SetBorderSize(0.);
  for (int iHist=0;iHist<nSummedHists;iHist++) {
    Legend->AddEntry(Contours[iHist],SummedHistNames[iHist],"l");
  }
  
  for (int iHist=nSummedHists-1;iHist>=0;iHist--) {
    if (iHist==nSummedHists-1) {
      Contours[iHist]->Draw("CONT3");
      Text->Draw("SAME");
    } else {
      Contours[iHist]->Draw("CONT3 SAME");
    }
    Legend->Draw("SAME");
  }
  Canv->Print(OutputName);
  //============================================================
}
