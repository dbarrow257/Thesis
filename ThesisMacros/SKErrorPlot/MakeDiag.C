void MakeDiag() {
  TFile* File = new TFile("SKJointErrorMatrix2020_Total_fitqun_v4_16042020.root","UPDATE");

  File->ls();
  TMatrixDSym* CovMatrix = (TMatrixDSym*)File->Get("SKJointError_Erec_Total");
  CovMatrix->Draw();

  int nEntries = CovMatrix->GetNcols()-1;

  TH1D* NewDiag = new TH1D("NewDiag_Dan","",nEntries,0,nEntries);
  for (int xBin=1;xBin<=NewDiag->GetNbinsX();xBin++) {
    double Err = sqrt((*CovMatrix)(xBin-1,xBin-1));
    std::cout << xBin-1 << " : " << Err << std::endl;
    NewDiag->SetBinContent(xBin,Err);
  }

  NewDiag->Draw();
  NewDiag->Write();

  File->Close();
}
