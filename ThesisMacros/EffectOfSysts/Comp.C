#include <vector>

enum OscPars {k_dcp, k_th23, n_OscPars};

std::vector<TH1D*> GetHists(TString FileName, TString Caption) {
  TFile* File = new TFile(FileName);
  if (!File) {
    std::cout << "Did not find FileName:" << FileName << std::endl;
    throw;
  }

  TTree* PosteriorTree = (TTree*)File->Get("osc_posteriors");
  if (!PosteriorTree) {
    std::cout << "Did not find osc_posteriors in " << FileName << std::endl;
    throw;
  }

  std::vector<TH1D*> VecHists(n_OscPars);
  VecHists[k_dcp] = new TH1D(Caption+"_dcp","",100,-TMath::Pi(),TMath::Pi());
  VecHists[k_th23] = new TH1D(Caption+"_th23","",100,0.3,0.7);
  
  double dcp;
  PosteriorTree->SetBranchAddress("dcp",&dcp);

  double theta23;
  PosteriorTree->SetBranchAddress("theta23",&theta23);

  int step;
  PosteriorTree->SetBranchAddress("step",&step);

  int burnin = 100000;

  int nEntries = PosteriorTree->GetEntries();
  for (int iEntry=0;iEntry<nEntries;iEntry++) {
    PosteriorTree->GetEntry(iEntry);

    if (step>burnin) {
      VecHists[k_dcp]->Fill(dcp);
      VecHists[k_th23]->Fill(theta23);
    }
  }
  
  return VecHists;
}

void Comp() {
  TString FixedSystsFileName = "../../MacroInputs/EffectOfSysts/FixedSystChain.root";
  TString VariedSystsFileName = "../../MacroInputs/EffectOfSysts/VariedSystChain.root";

  TString FixedSystsFileCap = "FixedSysts";
  TString VariedSystsFileCap = "VariedSysts";

  std::vector<TH1D*> FixedSystHists = GetHists(FixedSystsFileName,FixedSystsFileCap);
  std::vector<TH1D*> VariedSystHists = GetHists(VariedSystsFileName,VariedSystsFileCap);

  TCanvas* Canv = new TCanvas("Canv","");
  TString OutputName = "SystematicComparison.pdf";
  Canv->Print(OutputName+"[");

  for (int iHist=0;iHist<n_OscPars;iHist++) {
    FixedSystHists[iHist]->SetLineColor(kBlack);
    VariedSystHists[iHist]->SetLineColor(kRed);

    FixedSystHists[iHist]->Scale(1.0/FixedSystHists[iHist]->Integral());
    VariedSystHists[iHist]->Scale(1.0/VariedSystHists[iHist]->Integral());
  }
  
  for (int iHist=0;iHist<n_OscPars;iHist++) {
    FixedSystHists[iHist]->Draw();
    VariedSystHists[iHist]->Draw("SAME");

    Canv->Print(OutputName);
  }

  Canv->Print(OutputName+"]");  
}
