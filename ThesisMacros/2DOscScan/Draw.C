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

void Draw() {
  gStyle->SetNumberContours(80);
  //gStyle->SetPalette(kCherry);

  Int_t MyPalette[255];
  Double_t red[9]   = { 0.2082, 0.0592, 0.0780, 0.0232, 0.1802, 0.5301, 0.8186, 0.9956, 0.9764};
  Double_t green[9] = { 0.1664, 0.3599, 0.5041, 0.6419, 0.7178, 0.7492, 0.7328, 0.7862, 0.9832};
  Double_t blue[9]  = { 0.5293, 0.8684, 0.8385, 0.7914, 0.6425, 0.4662, 0.3499, 0.1968, 0.0539};
  //Double_t stops[9] = { 0.0000, 0.1250, 0.2500, 0.3750, 0.5000, 0.6250, 0.7500, 0.8750, 1.0000};
  Double_t stops[9] = { 0.0000, 0.1250/4, 0.2500/4, 0.3750/3, 0.5000/3, 0.450/2, 0.500, 0.750, 1.0000};
  int Idx = TColor::CreateGradientColorTable(9, stops, red, green, blue, 255, 1.0);
  for (int i=0;i<255;i++) MyPalette[i] = Idx+i;

  gStyle->SetPalette(255, MyPalette);
  
  TString FileName = "../../MacroInputs/2DOscLLH/2DLLHOscScan.root";
  TFile* File = new TFile(FileName);

  std::vector<TH2D*> DisScans = GetHists(File,"Disappearance");
  std::vector<TH2D*> AppScans = GetHists(File,"Appearance");
  int nHists = DisScans.size();

  if (nHists==0) {
    std::cout << "Did not find any hists" << std::endl;
    throw;
  }

  std::vector<double> TruePoints(4);
  TruePoints[0] = 0.528;
  TruePoints[1] = 2.509e-3;
  TruePoints[2] = 0.0218;
  TruePoints[3] = -1.601;

  int Dis_XBin_True = DisScans[0]->GetXaxis()->FindBin(TruePoints[0]);
  int Dis_YBin_True = DisScans[0]->GetYaxis()->FindBin(TruePoints[1]);
  int App_XBin_True = AppScans[0]->GetXaxis()->FindBin(TruePoints[2]);
  int App_YBin_True = AppScans[0]->GetYaxis()->FindBin(TruePoints[3]);

  std::cout << "Dis True:" << Dis_XBin_True << " " << Dis_YBin_True << std::endl;
  std::cout << "App True:" << App_XBin_True << " " << App_YBin_True << std::endl;
  
  TMarker* DisMarker = new TMarker(TruePoints[0],TruePoints[1],5);
  TMarker* AppMarker = new TMarker(TruePoints[2],TruePoints[3],5);

  double Contours_3Sig[1];
  Contours_3Sig[0] = 9;

  double Contours_2Sig[1];
  Contours_2Sig[0] = 4;
  
  int X, Y, Z;
  int nSummedHists = 3; //Beam, Atmospheric, All
  std::vector<TString> SummedHistNames(nSummedHists);
  SummedHistNames[0] = "Beam";
  SummedHistNames[1] = "Atmospheric";
  SummedHistNames[2] = "All";
      
  //============================================================
  std::vector<TH2D*> SummedHists_Dis(nSummedHists);
  for (int iHist=0;iHist<nSummedHists;iHist++) {
    SummedHists_Dis[iHist] = (TH2D*)DisScans[0]->Clone();
    SummedHists_Dis[iHist]->Reset();
    SummedHists_Dis[iHist]->GetXaxis()->SetTitle("sin^{2}(#theta_{23})");
    SummedHists_Dis[iHist]->GetYaxis()->SetTitle("#Delta m^{2}_{32} [MeV]");
    SummedHists_Dis[iHist]->GetZaxis()->SetTitle("-2 #times ln(Likelihood)");
    SummedHists_Dis[iHist]->GetXaxis()->SetTitleSize(0.06);
    SummedHists_Dis[iHist]->GetYaxis()->SetTitleSize(0.06);
    SummedHists_Dis[iHist]->GetZaxis()->SetTitleSize(0.05);
    SummedHists_Dis[iHist]->GetYaxis()->SetTitleOffset(1.2);
    SummedHists_Dis[iHist]->GetZaxis()->SetTitleOffset(0.9);
    SummedHists_Dis[iHist]->GetXaxis()->SetLabelSize(0.05);
    SummedHists_Dis[iHist]->GetYaxis()->SetLabelSize(0.05);
    //SummedHists_Dis[iHist]->SetTitle(SummedHistNames[iHist]);
  }

 for (int iHist=0;iHist<nHists;iHist++) {
   DisScans[iHist]->Scale(2);
 }
  
  for (int iHist=0;iHist<nHists;iHist++) {
    TString HistName = (TString(DisScans[iHist]->GetName())).ReplaceAll("_Dis","");

    if (HistName.Contains("2020")) {
      SummedHists_Dis[0]->Add(DisScans[iHist]);
    } else {
      SummedHists_Dis[1]->Add(DisScans[iHist]);
    }
    SummedHists_Dis[2]->Add(DisScans[iHist]);
  }

  for (int iHist=0;iHist<nSummedHists;iHist++) {
    SummedHists_Dis[iHist]->SetMaximum(1400);
    SummedHists_Dis[iHist]->GetYaxis()->SetRangeUser(-0.004,0.004);
  }
  
  TString DisOutputName = "DisappearanceScans.pdf";
  TCanvas* DisCanv = new TCanvas("DisCanv","");
  DisCanv->SetRightMargin(0.15);
  DisCanv->SetTopMargin(0.02);
  DisCanv->SetBottomMargin(0.15);
  DisCanv->SetLeftMargin(0.15);
  DisCanv->Print(DisOutputName+"[");
  for (int iHist=0;iHist<nSummedHists;iHist++) {
    SummedHists_Dis[iHist]->Draw("COLZ");

    TH2D* CloneHist_3Sig = (TH2D*)SummedHists_Dis[iHist]->Clone();
    CloneHist_3Sig->SetContour(1,Contours_3Sig);
    CloneHist_3Sig->SetLineColor(kRed);
    CloneHist_3Sig->Draw("cont3 SAME");

    TH2D* CloneHist_2Sig = (TH2D*)SummedHists_Dis[iHist]->Clone();
    CloneHist_2Sig->SetContour(1,Contours_2Sig);
    CloneHist_2Sig->SetLineColor(kRed);
    CloneHist_2Sig->SetLineStyle(kDashed);
    CloneHist_2Sig->Draw("cont3 SAME");

    SummedHists_Dis[iHist]->GetBinXYZ(SummedHists_Dis[iHist]->GetMinimumBin(),X,Y,Z);
    TMarker* Marker  = new TMarker(SummedHists_Dis[iHist]->GetXaxis()->GetBinLowEdge(X),SummedHists_Dis[iHist]->GetYaxis()->GetBinCenter(Y),22);
    Marker->Draw("SAME");

    std::cout << "Dis:" << SummedHistNames[iHist] << " | " << X << " " << Y << std::endl;

    DisMarker->Draw("SAME");
    
    DisCanv->Print(DisOutputName);
  }
  DisCanv->Print(DisOutputName+"]");
  //============================================================
  //============================================================
  std::vector<TH2D*> SummedHists_App(nSummedHists);
  for (int iHist=0;iHist<nSummedHists;iHist++) {
    SummedHists_App[iHist] = (TH2D*)AppScans[0]->Clone();
    SummedHists_App[iHist]->Reset();
    SummedHists_App[iHist]->GetXaxis()->SetTitle("sin^{2}(#theta_{13})");
    SummedHists_App[iHist]->GetYaxis()->SetTitle("#delta_{CP}");
    SummedHists_App[iHist]->GetZaxis()->SetTitle("-2 #times ln(Likelihood)");
    SummedHists_App[iHist]->GetXaxis()->SetTitleSize(0.06);
    SummedHists_App[iHist]->GetYaxis()->SetTitleSize(0.06);
    SummedHists_App[iHist]->GetZaxis()->SetTitleSize(0.05);
    SummedHists_App[iHist]->GetYaxis()->SetTitleOffset(0.85);
    SummedHists_App[iHist]->GetZaxis()->SetTitleOffset(0.9);
    SummedHists_App[iHist]->GetXaxis()->SetLabelSize(0.05);
    SummedHists_App[iHist]->GetYaxis()->SetLabelSize(0.05);
    //SummedHists_App[iHist]->SetTitle(SummedHistNames[iHist]);
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

  TString AppOutputName = "AppearanceScans.pdf";
  TCanvas* AppCanv = new TCanvas("AppCanv","");

  //AppCanv->SetLogz(true);
  
  AppCanv->SetRightMargin(0.15);
  AppCanv->SetTopMargin(0.02);
  AppCanv->SetBottomMargin(0.15);
  AppCanv->SetLeftMargin(0.12);
  AppCanv->Print(AppOutputName+"[");
  for (int iHist=0;iHist<nSummedHists;iHist++) {
    SummedHists_App[iHist]->Draw("COLZ");

    TH2D* CloneHist_3Sig = (TH2D*)SummedHists_App[iHist]->Clone();
    CloneHist_3Sig->SetContour(1,Contours_3Sig);
    CloneHist_3Sig->SetLineColor(kRed);
    CloneHist_3Sig->Draw("cont3 SAME");

    TH2D* CloneHist_2Sig = (TH2D*)SummedHists_App[iHist]->Clone();
    CloneHist_2Sig->SetContour(1,Contours_2Sig);
    CloneHist_2Sig->SetLineColor(kRed);
    CloneHist_2Sig->SetLineStyle(kDashed);
    CloneHist_2Sig->Draw("cont3 SAME");
    
    SummedHists_App[iHist]->GetBinXYZ(SummedHists_App[iHist]->GetMinimumBin(),X,Y,Z);
    TMarker* Marker  = new TMarker(SummedHists_App[iHist]->GetXaxis()->GetBinCenter(X),SummedHists_App[iHist]->GetYaxis()->GetBinCenter(Y),22);
    Marker->Draw("SAME");

    std::cout << "App:" << SummedHistNames[iHist] << " | " << X << " " << Y << std::endl;

    AppMarker->Draw("SAME");
    
    AppCanv->Print(AppOutputName);
  }
  AppCanv->Print(AppOutputName+"]");
  //======================================================================
}
