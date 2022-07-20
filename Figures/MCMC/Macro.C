void Macro() {
  TCanvas* Canv = new TCanvas("Canv","");
  
  TFile* File = new TFile("LLHStep.root");
  TGraph* Graph = (TGraph*)File->Get("Graph");
  Graph->SetLineColor(kBlack);
  Graph->SetTitle("");
  Graph->Draw("AP");

  TLine* Line = new TLine(100000,Graph->GetYaxis()->GetXmin(),100000,Graph->GetYaxis()->GetXmax());
  Line->SetLineColor(kRed);
  Line->SetLineStyle(kDashed);
  Line->Draw("SAME");

  Graph->GetXaxis()->SetTitle("Step Number");
  Graph->GetYaxis()->SetTitle("-log(Likelihood)");
  Graph->GetYaxis()->SetTitleOffset(1.15);

  Canv->Print("MCTechnique_LLHStep.pdf");
}
