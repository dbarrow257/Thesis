#include <vector>

TGraph* GetPREMApproxDensity() {

  int nPoints = 9;

  std::vector<double> Densities(nPoints);
  std::vector<double> Radius(nPoints);

  Radius[0] = 0.;
  Densities[0] = 13.;

  Radius[1] = 1220.;
  Densities[1] = 13.;

  Radius[2] = 1220.;
  Densities[2] = 11.3;

  Radius[3] = 3480.;
  Densities[3] = 11.3;

  Radius[4] = 3480.;
  Densities[4] = 5.0;

  Radius[5] = 5701;
  Densities[5] = 5.0;

  Radius[6] = 5701;
  Densities[6] = 3.3;

  Radius[7] = 6371;
  Densities[7] = 3.3;

  Radius[8] = 6371;
  Densities[8] = 0.;

  TGraph* Graph = new TGraph(nPoints,Radius.data(),Densities.data());
  return Graph;
}

TGraph* GetPREMDensity() {

  double REarth = 6371.0; //km
  double RCenter = 0.;
  
  int nSamplingPoints = 1000;

  std::vector<double> Densities(nSamplingPoints+1);
  
  std::vector<double> SamplingPoints(nSamplingPoints+1);
  for (int iSamplingPoint=0;iSamplingPoint<nSamplingPoints;iSamplingPoint++) {
    SamplingPoints[iSamplingPoint] = RCenter + ((double)iSamplingPoint/(double)nSamplingPoints)*REarth;
  }

  Densities[nSamplingPoints] = 0.;
  SamplingPoints[nSamplingPoints] = REarth;
  
  //Density = Const_A + Const_B * X + Const_C * X**2 + Const_C * X**3, where X = Radius/REarth
  enum Attr{InnerRadius,OuterRadius,Const_A,Const_B,Const_C,Const_D,nAttr};
  
  std::vector< std::vector<double> > Layers;

  std::vector<double> InnerCore(nAttr);
  InnerCore[InnerRadius] = 0.;
  InnerCore[OuterRadius] = 1220.;
  InnerCore[Const_A] = 13.0885;
  InnerCore[Const_B] = 0.0;
  InnerCore[Const_C] = -8.8381;
  InnerCore[Const_D] = 0.0;

  Layers.push_back(InnerCore);
  
  std::vector<double> OuterCore(nAttr);
  OuterCore[InnerRadius] = 1220.;
  OuterCore[OuterRadius] = 3480.;
  OuterCore[Const_A] = 12.5815;
  OuterCore[Const_B] = -1.2638;
  OuterCore[Const_C] = -3.6426;
  OuterCore[Const_D] = -5.5281;

  Layers.push_back(OuterCore);

  std::vector<double> LowerMantle(nAttr);
  LowerMantle[InnerRadius] = 3480.;
  LowerMantle[OuterRadius] = 5701.;
  LowerMantle[Const_A] = 7.9565;
  LowerMantle[Const_B] = -6.4761;
  LowerMantle[Const_C] = 5.5283;
  LowerMantle[Const_D] = -3.0807;

  Layers.push_back(LowerMantle);

  std::vector<double> TransitionZone_A(nAttr);
  TransitionZone_A[InnerRadius] = 5701.;
  TransitionZone_A[OuterRadius] = 5771.;
  TransitionZone_A[Const_A] = 5.3917;
  TransitionZone_A[Const_B] = -1.4836;
  TransitionZone_A[Const_C] = 0.;
  TransitionZone_A[Const_D] = 0.;

  Layers.push_back(TransitionZone_A);

  std::vector<double> TransitionZone_B(nAttr);
  TransitionZone_B[InnerRadius] = 5771.;
  TransitionZone_B[OuterRadius] = 5971.;
  TransitionZone_B[Const_A] = 11.2494;
  TransitionZone_B[Const_B] = -8.0298;
  TransitionZone_B[Const_C] = 0.;
  TransitionZone_B[Const_D] = 0.;

  Layers.push_back(TransitionZone_B);

  std::vector<double> TransitionZone_C(nAttr);
  TransitionZone_C[InnerRadius] = 5971.;
  TransitionZone_C[OuterRadius] = 6151.;
  TransitionZone_C[Const_A] = 7.1089;
  TransitionZone_C[Const_B] = -3.9045;
  TransitionZone_C[Const_C] = 0.;
  TransitionZone_C[Const_D] = 0.;

  Layers.push_back(TransitionZone_C);

  std::vector<double> LVZ_LID(nAttr);
  LVZ_LID[InnerRadius] = 6151.;
  LVZ_LID[OuterRadius] = 6346.6;
  LVZ_LID[Const_A] = 2.6910;
  LVZ_LID[Const_B] = 0.6924;
  LVZ_LID[Const_C] = 0.;
  LVZ_LID[Const_D] = 0.;

  Layers.push_back(LVZ_LID);

  std::vector<double> Crust_A(nAttr);
  Crust_A[InnerRadius] = 6346.6;
  Crust_A[OuterRadius] = 6356.;
  Crust_A[Const_A] = 2.9;
  Crust_A[Const_B] = 0.;
  Crust_A[Const_C] = 0.;
  Crust_A[Const_D] = 0.;

  Layers.push_back(Crust_A);
  
  std::vector<double> Crust_B(nAttr);
  Crust_B[InnerRadius] = 6356.;
  Crust_B[OuterRadius] = 6368.;
  Crust_B[Const_A] = 2.6;
  Crust_B[Const_B] = 0.;
  Crust_B[Const_C] = 0.;
  Crust_B[Const_D] = 0.;

  Layers.push_back(Crust_B);

  std::vector<double> Ocean(nAttr);
  Ocean[InnerRadius] = 6368.;
  Ocean[OuterRadius] = 6371.;
  Ocean[Const_A] = 1.02;
  Ocean[Const_B] = 0.;
  Ocean[Const_C] = 0.;
  Ocean[Const_D] = 0.;

  Layers.push_back(Ocean);

  int nLayers = Layers.size();
  
  for (int iSamplingPoint=0;iSamplingPoint<nSamplingPoints;iSamplingPoint++) {
    double Radius = SamplingPoints[iSamplingPoint];
    double Ratio = Radius/REarth;

    double Density=0;
    
    for (int iLayerToCheck=0;iLayerToCheck<nLayers;iLayerToCheck++) {
      if (Radius >= Layers[iLayerToCheck][InnerRadius] && Radius < Layers[iLayerToCheck][OuterRadius]) {
	Density = Layers[iLayerToCheck][Const_A] + Layers[iLayerToCheck][Const_B]*Ratio + Layers[iLayerToCheck][Const_C]*Ratio*Ratio + Layers[iLayerToCheck][Const_D]*Ratio*Ratio*Ratio;
      }
    }

    Densities[iSamplingPoint] = Density;
  }
  
  TGraph* DensityGraph = new TGraph(nSamplingPoints,SamplingPoints.data(),Densities.data());
  return DensityGraph;
}

TGraph* GetPREMAverageDensity() {

  double REarth = 6371.0; //km
  double RCenter = 0.;
  
  int nSamplingPoints = 1000;

  std::vector<double> Densities(nSamplingPoints+1);
  
  std::vector<double> SamplingPoints(nSamplingPoints+1);
  for (int iSamplingPoint=0;iSamplingPoint<nSamplingPoints;iSamplingPoint++) {
    SamplingPoints[iSamplingPoint] = RCenter + ((double)iSamplingPoint/(double)nSamplingPoints)*REarth;
  }

  Densities[nSamplingPoints] = 0.;
  SamplingPoints[nSamplingPoints] = REarth;
  
  //Density = Const_A + Const_B * X + Const_C * X**2, where X = Radius/REarth
  enum Attr{InnerRadius,OuterRadius,Const_A,Const_B,Const_C,nAttr};
  
  std::vector< std::vector<double> > Layers;

  std::vector<double> InnerCore(nAttr);
  InnerCore[InnerRadius] = 0.;
  InnerCore[OuterRadius] = 1221.5;
  InnerCore[Const_A] = 13.09;
  InnerCore[Const_B] = 0.0;
  InnerCore[Const_C] = -8.84;

  Layers.push_back(InnerCore);
  
  std::vector<double> OuterCore(nAttr);
  OuterCore[InnerRadius] = 1221.5;
  OuterCore[OuterRadius] = 3480.;
  OuterCore[Const_A] = 12.31;
  OuterCore[Const_B] = 1.09;
  OuterCore[Const_C] = -10.02;

  Layers.push_back(OuterCore);

  std::vector<double> LowerMantle(nAttr);
  LowerMantle[InnerRadius] = 3480.;
  LowerMantle[OuterRadius] = 5701.;
  LowerMantle[Const_A] = 6.78;
  LowerMantle[Const_B] = -1.56;
  LowerMantle[Const_C] = -1.25;

  Layers.push_back(LowerMantle);

  std::vector<double> TransitionZone(nAttr);
  TransitionZone[InnerRadius] = 5701.;
  TransitionZone[OuterRadius] = 6371.;
  TransitionZone[Const_A] = -50.42;
  TransitionZone[Const_B] = 123.33;
  TransitionZone[Const_C] = -69.95;

  Layers.push_back(TransitionZone);

  int nLayers = Layers.size();
  
  for (int iSamplingPoint=0;iSamplingPoint<nSamplingPoints;iSamplingPoint++) {
    double Radius = SamplingPoints[iSamplingPoint];
    double Ratio = Radius/REarth;

    double Density=0;
    
    for (int iLayerToCheck=0;iLayerToCheck<nLayers;iLayerToCheck++) {
      if (Radius >= Layers[iLayerToCheck][InnerRadius] && Radius < Layers[iLayerToCheck][OuterRadius]) {
	Density = Layers[iLayerToCheck][Const_A] + Layers[iLayerToCheck][Const_B]*Ratio + Layers[iLayerToCheck][Const_C]*Ratio*Ratio;
      }
    }

    Densities[iSamplingPoint] = Density;
  }
  
  TGraph* DensityGraph = new TGraph(nSamplingPoints,SamplingPoints.data(),Densities.data());
  return DensityGraph;
}

void PREMMacro() {
  TGraph* PREMModel = GetPREMDensity();
  PREMModel->SetLineColor(kBlack);
  
  TGraph* ApproxPremModel = GetPREMApproxDensity();
  ApproxPremModel->SetLineColor(kBlue);
  ApproxPremModel->SetLineStyle(kDashed);

  TGraph* AveragePremModel = GetPREMAverageDensity();
  AveragePremModel->SetLineColor(kRed);
  AveragePremModel->SetLineStyle(kDashed);

  PREMModel->SetTitle(";Radius (km);Density (g/cm^{3})");
  ApproxPremModel->SetTitle("");
  AveragePremModel->SetTitle("");
  
  PREMModel->SetLineWidth(2);
  ApproxPremModel->SetLineWidth(2);
  AveragePremModel->SetLineWidth(2);
  
  TLegend* Legend = new TLegend(0.15,0.15,0.4,0.3);
  Legend->SetBorderSize(0.);
  Legend->SetTextSize(0.05);
  Legend->AddEntry(PREMModel,"PREM Model","l");
  Legend->AddEntry(ApproxPremModel,"Constant Density","l");
  Legend->AddEntry(AveragePremModel,"Average Density","l");
  
  TCanvas* Canv = new TCanvas("Canv","");
  
  PREMModel->Draw();
  ApproxPremModel->Draw("SAME");
  AveragePremModel->Draw("SAME");
  Legend->Draw("SAME");
  
  PREMModel->SetMinimum(0.);
  ApproxPremModel->SetMinimum(0.);
  AveragePremModel->SetMinimum(0.);
  PREMModel->SetMaximum(14.);
  ApproxPremModel->SetMaximum(14.);
  AveragePremModel->SetMaximum(14.);

  PREMModel->GetXaxis()->SetRangeUser(0.,6371.);
  ApproxPremModel->GetXaxis()->SetRangeUser(0.,6371.);
  AveragePremModel->GetXaxis()->SetRangeUser(0.,6371.);

  Canv->Update();
  Canv->Print("DensityComparisonWithAveragePREM.pdf");
}
