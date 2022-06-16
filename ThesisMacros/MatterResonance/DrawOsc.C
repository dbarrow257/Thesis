void DrawOsc() {

  bool doPadding = true;
  
  gStyle->SetOptStat(false);
  
  TString FileName = "../../MacroInputs/MatterResonance/Oscillograms.root";
  TFile* File = new TFile(FileName);

  TH2D* H_Nu_NH = (TH2D*)File->Get("OscNH/Fine/hSecondaryArray_1_0_0");
  TH2D* H_NuBar_NH = (TH2D*)File->Get("OscNH/Fine/hSecondaryArray_0_0_0");
  TH2D* H_Nu_IH = (TH2D*)File->Get("OscIH/Fine/hSecondaryArray_1_0_0");
  TH2D* H_NuBar_IH = (TH2D*)File->Get("OscIH/Fine/hSecondaryArray_0_0_0");

  H_Nu_NH->GetZaxis()->SetRangeUser(0.0,1.0);
  H_NuBar_NH->GetZaxis()->SetRangeUser(0.0,1.0);
  H_Nu_IH->GetZaxis()->SetRangeUser(0.0,1.0);
  H_NuBar_IH->GetZaxis()->SetRangeUser(0.0,1.0);
  
  H_Nu_NH->GetYaxis()->SetTitleOffset(1.3);
  H_Nu_IH->GetYaxis()->SetTitleOffset(1.3);
  H_Nu_IH->GetXaxis()->SetTitleOffset(1.3);
  H_NuBar_IH->GetXaxis()->SetTitleOffset(1.3);
  
  TPaveText* NuTitle = new TPaveText(0.1,0.9,0.5,1.0);
  NuTitle->AddText(H_Nu_NH->GetTitle());
  NuTitle->SetBorderSize(0) ;
  NuTitle->SetFillColor(0) ;
  NuTitle->SetTextSize(0.04) ;
  
  TPaveText* NuBarTitle = new TPaveText(0.5,0.9,0.9,1.0);
  NuBarTitle->AddText(H_NuBar_NH->GetTitle());
  NuBarTitle->SetBorderSize(0) ;
  NuBarTitle->SetFillColor(0) ;
  NuBarTitle->SetTextSize(0.04) ;

  TPaveText* NHTitle = new TPaveText(0.0,0.4,0.1,1.0);
  TText* NHText = (TText*)NHTitle->AddText("Normal Hierarchy");
  NHText->SetTextAngle(90);
  NHTitle->SetBorderSize(0) ;
  NHTitle->SetFillColor(0) ;
  NHTitle->SetTextSize(0.03) ;

  TPaveText* IHTitle = new TPaveText(0.0,0.1,0.1,0.5);
  TText* IHText = (TText*)IHTitle->AddText("Inverted Hierarchy");
  IHText->SetTextAngle(90);
  IHTitle->SetBorderSize(0) ;
  IHTitle->SetFillColor(0) ;
  IHTitle->SetTextSize(0.03) ;
  
  H_Nu_NH->SetTitle("");
  H_NuBar_NH->SetTitle("");
  H_Nu_IH->SetTitle("");
  H_NuBar_IH->SetTitle("");
  
  H_Nu_NH->GetXaxis()->SetRangeUser(0.1,100.0);
  H_NuBar_NH->GetXaxis()->SetRangeUser(0.1,100.0);
  H_Nu_IH->GetXaxis()->SetRangeUser(0.1,100.0);
  H_NuBar_IH->GetXaxis()->SetRangeUser(0.1,100.0);
  
  TCanvas* Canv = new TCanvas("Canv","",1000,1000);

  NuTitle->Draw();
  NuBarTitle->Draw();
  NHTitle->Draw();
  IHTitle->Draw();
  
  Canv->cd();
  TPad* Pad1 = new TPad("Pad1","",0.1,0.5,0.5,0.9);
  if (doPadding) {
    Pad1->SetLeftMargin(0.1);
    Pad1->SetRightMargin(0.0);
    Pad1->SetBottomMargin(0.0);
    Pad1->SetTopMargin(0.01);
  }
  Pad1->Draw();
  Pad1->cd();
  Pad1->SetLogx();
  H_Nu_NH->Draw("COLZ");

  Canv->cd();
  TPad* Pad2 = new TPad("Pad2","",0.5,0.5,0.9,0.9);
  if (doPadding) {
    Pad2->SetLeftMargin(0.0);
    Pad2->SetRightMargin(0.1);
    Pad2->SetBottomMargin(0.0);
    Pad2->SetTopMargin(0.01);
  }
  Pad2->Draw();
  Pad2->cd();
  Pad2->SetLogx();
  H_NuBar_NH->Draw("COLZ");

  Canv->cd();
  TPad* Pad3 = new TPad("Pad3","",0.1,0.07,0.5,0.5);
  if (doPadding) {
    Pad3->SetLeftMargin(0.1);
    Pad3->SetRightMargin(0.0);
    Pad3->SetBottomMargin(0.1);
    Pad3->SetTopMargin(0.0);
  }
  Pad3->Draw();
  Pad3->cd();
  Pad3->SetLogx();
  H_Nu_IH->Draw("COLZ");

  Canv->cd();
  TPad* Pad4 = new TPad("Pad4","",0.5,0.07,0.9,0.5);
  if (doPadding) {
    Pad4->SetLeftMargin(0.0);
    Pad4->SetRightMargin(0.1);
    Pad4->SetBottomMargin(0.1);
    Pad4->SetTopMargin(0.0);
  }
  Pad4->Draw();
  Pad4->cd();
  Pad4->SetLogx();
  H_NuBar_IH->Draw("COLZ");

  Canv->Print("MatterResonanceEffect.pdf");  
}
