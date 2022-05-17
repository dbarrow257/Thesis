void Marginalisation() {

  gStyle->SetOptStat(false);
  TRandom* Rnd = new TRandom();

  const int nPars = 2;
  double ParNom[nPars] = {0,0};
  double ParThrows[nPars] = {0,0};
  double Cov[nPars * nPars] = {1.0,-0.5,-0.5,1.0};
  //double Cov[nPars * nPars] = {1.0,0.,0.,1.0};

  TH2D* Hist_All = new TH2D("Hist",";x;y",40,-5.,5.,40,-5.,5.);
  TH2D* Hist_Marg = new TH2D("Hist_Marg",";x;y",40,-5.,5.,40,-5.,5.);

  /*
  TH2D* Hist_Marg_1 = new TH2D("Hist_Marg_1",";x;y",40,-5.,5.,40,-5.,5.);
  TH2D* Hist_Marg_2 = new TH2D("Hist_Marg_2",";x;y",40,-5.,5.,40,-5.,5.);
  TH2D* Hist_Marg_3 = new TH2D("Hist_Marg_3",";x;y",40,-5.,5.,40,-5.,5.);
  */
  
  TH1D* y_All = new TH1D("Hist_y",";y",40,-5.,5.);
  TH1D* y_Marg = new TH1D("Hist_yMarg",";y",40,-5.,5.);

  /*
  TH1D* y_Marg_1 = new TH1D("Hist_yMarg_1",";y",40,-5.,5.);
  TH1D* y_Marg_2 = new TH1D("Hist_yMarg_2",";y",40,-5.,5.);
  TH1D* y_Marg_3 = new TH1D("Hist_yMarg_3",";y",40,-5.,5.);
  */
  
  int nThrows = 100000;

  for (int iThrow=0;iThrow<nThrows;iThrow++) {
    for (int iPar=0;iPar<nPars;iPar++) {
      ParThrows[iPar] = Rnd->Gaus(0,1);
    }

    ParThrows[0] = Cov[0]*ParThrows[0]+Cov[1]*ParThrows[1];
    ParThrows[1] = Cov[2]*ParThrows[0]+Cov[3]*ParThrows[1];

    Hist_All->Fill(ParThrows[0],ParThrows[1]);
    y_All->Fill(ParThrows[1]);
  }

  for (int iThrow=0;iThrow<nThrows;iThrow++) {
    for (int iPar=0;iPar<nPars;iPar++) {
      ParThrows[iPar] = Rnd->Gaus(0,1);
    }

    ParThrows[0] = Cov[0]*ParThrows[0]+Cov[1]*ParThrows[1];
    ParThrows[1] = Cov[2]*ParThrows[0]+Cov[3]*ParThrows[1];

    if (ParThrows[0]>0.) {
      Hist_Marg->Fill(ParThrows[0],ParThrows[1]);
      y_Marg->Fill(ParThrows[1]);
    }

    /*
    if (ParThrows[0]>1.) {
      y_Marg_1->Fill(ParThrows[1]);
      Hist_Marg_1->Fill(ParThrows[0],ParThrows[1]);
    } else if (ParThrows[0]>-1.) {
      y_Marg_2->Fill(ParThrows[1]);
      Hist_Marg_2->Fill(ParThrows[0],ParThrows[1]);
    } else {
      y_Marg_3->Fill(ParThrows[1]);
      Hist_Marg_3->Fill(ParThrows[0],ParThrows[1]);
    }
    */
  }

  y_All->Scale(1.0/(0.8*y_All->Integral()));
  y_Marg->Scale(1.0/y_Marg->Integral());
  /*
  y_Marg_1->Scale(1.0/y_Marg_1->Integral());
  y_Marg_2->Scale(1.0/y_Marg_2->Integral());
  y_Marg_3->Scale(1.0/y_Marg_3->Integral());
  */
  
  TCanvas* Canv = new TCanvas("2D","");
  Hist_All->Draw();

  Hist_Marg->SetMarkerColor(kRed);
  Canv->Print("Marginalisation2D_Single.pdf");

  Hist_Marg->Draw("SAME");
  Canv->Print("Marginalisation2D_Double.pdf");

  /*
  TCanvas* Canv4 = new TCanvas("2D_2","");
  Hist_Marg_1->SetMarkerColor(kBlack);
  Hist_Marg_2->SetMarkerColor(kBlue);
  Hist_Marg_3->SetMarkerColor(kRed);

  Hist_Marg_1->Draw();
  Hist_Marg_2->Draw("SAME");
  Hist_Marg_3->Draw("SAME");

  Canv4->Print("Marginalisation2D_1.pdf");
  */
  
  TCanvas* Canv2 = new TCanvas("1D","");

  y_All->SetMaximum(y_All->GetMaximum() > y_Marg->GetMaximum() ? y_All->GetMaximum()*1.1 : y_Marg->GetMaximum()*1.1);
  y_All->SetLineColor(kBlack);
  y_Marg->SetLineColor(kRed);
  y_All->Draw("HIST");

  Canv2->Print("Marginalisation1D_Single.pdf");

  y_Marg->Draw("HIST SAME");
  Canv2->Print("Marginalisation1D_Double.pdf");

  /*
  TCanvas* Canv3 = new TCanvas("1D_2","");
  //y_All->Draw("HIST");
  y_Marg_1->SetLineColor(kBlack);
  y_Marg_1->Draw("HIST");
  y_Marg_2->SetLineColor(kBlue);
  y_Marg_2->Draw("HIST SAME");
  y_Marg_3->SetLineColor(kRed);
  y_Marg_3->Draw("HIST SAME");

  Canv3->Print("Marginalisation1D_1.pdf");
  */
}
