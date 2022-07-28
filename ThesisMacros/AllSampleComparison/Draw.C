void Draw() {
  gStyle->SetCanvasDefH(800);
  gStyle->SetCanvasDefW(1100);

  TString FileName = "HistogramComparison.root";
  TFile* File = new TFile(FileName);

  TCanvas* Canv = (TCanvas*)File->Get("Canv");
  Canv->Draw();

  TPaveText* Text1 = new TPaveText(0.01,0.01,0.2,0.05);
  Text1->SetFillColor(kWhite);
  Text1->AddText("Momentum");
  Text1->Draw("SAME");

  TPaveText* Text2 = new TPaveText(0.21,0.01,0.4,0.05);
  Text2->SetFillColor(kWhite);
  Text2->AddText("Cosine Zenith");
  Text2->Draw("SAME");

  TPaveText* Text3 = new TPaveText(0.41,0.01,0.6,0.05);
  Text3->SetFillColor(kWhite);
  Text3->AddText("Cosine Zenith");
  Text3->Draw("SAME");

  TPaveText* Text4 = new TPaveText(0.61,0.01,0.8,0.05);
  Text4->SetFillColor(kWhite);
  Text4->AddText("Cosine Zenith");
  Text4->Draw("SAME");

  TPaveText* Text5 = new TPaveText(0.81,0.01,1.0,0.05);
  Text5->SetFillColor(kWhite);
  Text5->AddText("Cosine Zenith");
  Text5->Draw("SAME");

  std::cout << "Due to window size.... This has to be manually saved after maximising window size!" << std::endl;
}
