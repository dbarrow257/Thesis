void Comp() {

  gStyle->SetOptStat(false);
  
  TFile* CUDAProb3_CPU_40_File = new TFile("../../MacroInputs/TimeHistograms/TimeHist_CUDAProb3_CPU40.root");
  TH1D* CUDAProb3_CPU_40 = (TH1D*)CUDAProb3_CPU_40_File->Get("TimePerCalc");
  CUDAProb3_CPU_40->SetLineColor(kBlack);
  CUDAProb3_CPU_40->SetLineStyle(kDashed);
  
  TFile* CUDAProb3_CPU_File = new TFile("../../MacroInputs/TimeHistograms/TimeHist_CUDAProb3_CPU.root");
  TH1D* CUDAProb3_CPU = (TH1D*)CUDAProb3_CPU_File->Get("TimePerCalc");
  CUDAProb3_CPU->SetLineColor(kBlack);
  
  TFile* CUDAProb3_GPU_File = new TFile("../../MacroInputs/TimeHistograms/TimeHist_CUDAProb3_GPU.root");
  TH1D* CUDAProb3_GPU = (TH1D*)CUDAProb3_GPU_File->Get("TimePerCalc");
  CUDAProb3_GPU->SetLineColor(kBlue);
  
  TFile* Prob3_File = new TFile("../../MacroInputs/TimeHistograms/TimeHist_Prob3.root");
  TH1D* Prob3 = (TH1D*)Prob3_File->Get("TimePerCalc");
  Prob3->SetLineColor(kGreen);
  
  TFile* ProbGPU_File = new TFile("../../MacroInputs/TimeHistograms/TimeHist_ProbGPU.root");
  TH1D* ProbGPU = (TH1D*)ProbGPU_File->Get("TimePerCalc");
  ProbGPU->SetLineColor(kRed);

  TCanvas* Canv = new TCanvas("Canv","");

  ProbGPU->GetXaxis()->SetRangeUser(0.,0.4);

  CUDAProb3_GPU->Rebin(2);
  ProbGPU->Rebin(2);
  CUDAProb3_CPU->Rebin(2);
  CUDAProb3_CPU_40->Rebin(2);

  CUDAProb3_GPU->GetYaxis()->SetTitle("Number of Calculations");
  CUDAProb3_GPU->GetXaxis()->SetTitleSize(0.05);
  CUDAProb3_GPU->GetYaxis()->SetTitleSize(0.05);
  
  CUDAProb3_GPU->Draw();
  ProbGPU->Draw("SAME");
  CUDAProb3_CPU->Draw("SAME");
  CUDAProb3_CPU_40->Draw("SAME");

  TLegend* Legend = new TLegend(0.514,0.63,0.9,0.9);
  Legend->SetTextSize(0.039);
  Legend->AddEntry(ProbGPU,"ProbGPU","l");
  Legend->AddEntry(CUDAProb3_GPU,"CUDAProb3 (GPU)","l");
  Legend->AddEntry(CUDAProb3_CPU,"CUDAProb3 (CPU, 8thr)","l");
  Legend->AddEntry(CUDAProb3_CPU_40,"CUDAProb3 (CPU, 40thr)","l");

  Legend->Draw("SAME");

  Canv->Print("CalculationTime.pdf");
}
