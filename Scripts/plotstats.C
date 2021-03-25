#include <TAxis.h>
#include <TCanvas.h>
#include <TColor.h>
#include <TDatime.h>
#include <TGraph.h>
#include <TH1.h>
#include <TLegend.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TTree.h>
//#include "/home/nirkko/Dropbox/PhD/ND280_software/CommonStyle.H"

// Compile & run:     clear && root -l -b -q plotstats.C+g 
void plotstats() {

  TGaxis::SetMaxDigits(3);

  // This macro plots my thesis metadata over time
  // Martti Nirkko, 30.04.2016
  
  // Define the time offset and the histogram limits
  TDatime T0(2018,04,01,00,00,00);  // offset
  int X0 = T0.Convert();
  TDatime T1(2018,04,01,00,00,00);  // lowest
  int X1 = T1.Convert()-X0;
  TDatime T2(2018,07,10,00,00,00);  // highest
  int X2 = T2.Convert()-X0;

  // Set plotting style
  //CommonStyle();
  gStyle->SetTimeOffset(X0);
  gStyle->SetLineWidth(3);
  gStyle->SetPadRightMargin(0.05);
  
  // TODO - Fill file stats
  int date, pages, words, filesize;
  TTree *tree = new TTree("tree","title");
  tree->ReadFile("thesis.pdf.stats","date/I:pages/I:words/I:filesize/I");
  tree->SetBranchAddress("date",&date);
  tree->SetBranchAddress("pages",&pages);
  tree->SetBranchAddress("words",&words);
  tree->SetBranchAddress("filesize",&filesize);
  const int n = (const int)tree->GetEntries();
  float *x = new float[n];
  float *y = new float[n];
  float *z = new float[n];
  float *v = new float[n];
  for (int i=0; i<n; i++) {
    tree->GetEntry(i);
    //printf("%d %d %d %d\n",date,pages,words,filesize/1024);
    x[i] = (float)date-X0;
    y[i] = (float)pages;
    z[i] = (float)words;
    v[i] = (float)filesize/1024./1024.;
  }

  
  TGraph *gr1 = new TGraph(n,x,y);
  gr1->GetXaxis()->SetTimeDisplay(1);
  gr1->SetLineColor(2);
  TF1 *fit1 = new TF1("fit", "[0]*x+[1]", x[0], x[n]);
  fit1->SetLineColor(gr1->GetLineColor());
  fit1->SetLineStyle(kDashed);
  fit1->SetLineWidth(2);
  gr1->Fit(fit1, "Q");
  
  TGraph *gr2 = new TGraph(n,x,z);
  gr2->GetXaxis()->SetTimeDisplay(1);
  gr2->SetLineColor(3);
  TF1 *fit2 = new TF1("fit", "[0]*x+[1]", x[0], x[n]);
  fit2->SetLineColor(gr2->GetLineColor());
  fit2->SetLineStyle(kDashed);
  fit2->SetLineWidth(2);
  gr2->Fit(fit2, "Q");
  
  TGraph *gr3 = new TGraph(n,x,v);
  gr3->GetXaxis()->SetTimeDisplay(1);
  gr3->SetLineColor(4);
  TF1 *fit3 = new TF1("fit", "[0]*x+[1]", x[0], x[n]);
  fit3->SetLineColor(gr3->GetLineColor());
  fit3->SetLineStyle(kDashed);
  fit3->SetLineWidth(2);
  gr3->Fit(fit3, "Q");
  
  TCanvas *c1 = new TCanvas("c1","Thesis",1024, 1024);
  c1->SetLeftMargin(c1->GetLeftMargin()*1.1);
  c1->SetGrid();
  c1->Print("thesis_stats.pdf[");

  gr1->SetTitle("Page count");
  gr1->GetYaxis()->SetTitleOffset(1.1);
  gr1->GetXaxis()->SetTimeFormat("%d.%m.%y");
  gr1->GetXaxis()->SetLimits(X1,X2);
  gr1->GetXaxis()->SetNdivisions(5,4,0,false);
  gr1->Draw("AL");
  c1->Modified();
  c1->Update();
  gr1->GetXaxis()->SetTitle("Date");
  gr1->GetYaxis()->SetTitle("Pages");
  gr1->GetYaxis()->SetRangeUser(0, 350);
  c1->Print("thesis_stats.pdf");

  c1->Clear();
  gr2->SetTitle("Word count");
  gr2->GetYaxis()->SetTitleOffset(1.1);
  gr2->GetXaxis()->SetTimeFormat("%d.%m.%y");
  gr2->GetXaxis()->SetLimits(X1,X2);
  gr2->GetXaxis()->SetNdivisions(5,4,0,false);
  gr2->Draw("AL");
  gr2->GetXaxis()->SetTitle("Date");
  gr2->GetYaxis()->SetTitle("Words");
  c1->Modified();
  c1->Update();
  gr2->GetYaxis()->SetRangeUser(0, 200000);
  c1->Print("thesis_stats.pdf");

  c1->Clear();
  gr3->SetTitle("Filesize, MB");
  gr3->GetYaxis()->SetTitleOffset(1.1);
  gr3->GetXaxis()->SetTimeFormat("%d.%m.%y");
  gr3->GetXaxis()->SetLimits(X1,X2);
  gr3->GetXaxis()->SetNdivisions(5,4,0,false);
  gr3->Draw("AL");
  c1->Modified();
  c1->Update();
  gr3->GetXaxis()->SetTitle("Date");
  gr3->GetYaxis()->SetTitle("Filesize, MB");
  gr3->GetYaxis()->SetRangeUser(0, 40);
  c1->Print("thesis_stats.pdf");

  c1->Print("thesis_stats.pdf]");
  c1->Close();
  
  return;
}
