#include <vector>

void PrintEventRate() {
  TFile* SpectraFile = new TFile("Spectra.root");

  std::vector<TString> SampleNames;
  SampleNames.push_back("SubGeV-elike-0dcy");
  SampleNames.push_back("SubGeV-elike-1dcy");
  SampleNames.push_back("SubGeV-mulike-0dcy");
  SampleNames.push_back("SubGeV-mulike-1dcy");
  SampleNames.push_back("SubGeV-mulike-2dcy");

  std::vector<TString> SpectraHistNames;
  SpectraHistNames.push_back("_px");
  
  int nSamples = SampleNames.size();
  int nHists = SpectraHistNames.size();

  for (int iSample=0;iSample<nSamples;iSample++) {
    for(int iHist=0;iHist<nHists;iHist++) {
      
      TString SpectraHistName = SampleNames[iSample]+"/"+SampleNames[iSample]+SpectraHistNames[iHist];
      TH1D* SpectraHist = (TH1D*)SpectraFile->Get(SpectraHistName);
 
      if (!SpectraHist) std::cout << "Did not find " << SpectraHistName << " in Spectra file" << std::endl;

      std::cout << SampleNames[iSample] << " " << SpectraHist->Integral() << std::endl;
    }
  }

}
