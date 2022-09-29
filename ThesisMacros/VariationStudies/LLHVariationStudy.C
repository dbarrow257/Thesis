std::vector<double> ReturnFineEnergyBinning(TString FileName, TString TreeName) {

  TFile* File = new TFile(FileName);
  if (!File) {
    std::cout << "Did not find:" << FileName << std::endl;
  }

  TTree* Tree = (TTree*)File->Get(TreeName);
  if (!Tree) {
    std::cerr << "Have not found Tree:" << TreeName << " in File:" << FileName << std::endl;
    throw;
  }
  int nEntries = Tree->GetEntries();

  int SubDivisionBinning;
  Tree->SetBranchAddress("numFineEnergyBins",&SubDivisionBinning);

  std::vector<double> SubDivisionBinningVec;

  for (int iEntry=0;iEntry<nEntries;iEntry++) {
    Tree->GetEntry(iEntry);

    //Iterate through vector of stored SubDivisionBinning and see if we've already found that value
    bool foundSubDivisionBinning = false;
    for (int iSubDivisionBinning=0;iSubDivisionBinning<SubDivisionBinningVec.size();iSubDivisionBinning++) {
      if (SubDivisionBinning == SubDivisionBinningVec[iSubDivisionBinning]) {
        foundSubDivisionBinning = true;
        break;
      }
    }

    if (!foundSubDivisionBinning) {
      SubDivisionBinningVec.push_back(SubDivisionBinning);
    }
  }

  return SubDivisionBinningVec;
}

int ReturnNThrows(TString FileName, TString TreeName) {

  TFile* File = new TFile(FileName);
  if (!File) {
    std::cout << "Did not find:" << FileName << std::endl;
  }

  TTree* Tree = (TTree*)File->Get(TreeName);
  if (!Tree) {
    std::cerr << "Have not found Tree:" << TreeName << " in File:" << FileName << std::endl;
    throw;
  }
  int nEntries = Tree->GetEntries();

  int Throw;
  Tree->SetBranchAddress("iThrow",&Throw);

  int nOscThrows = -1;

  for (int iEntry=0;iEntry<nEntries;iEntry++) {
    Tree->GetEntry(iEntry);

    if (Throw >= nOscThrows) {
      nOscThrows = Throw+1;
    } else {
      break;
    }
  }

  return nOscThrows;
}

std::vector<TString> ReturnTreeNames(TString FileName) {

  std::vector<TString> TreeNames;
  TreeNames.push_back("SubGeV-elike-0dcy");
  TreeNames.push_back("SubGeV-elike-1dcy");
  TreeNames.push_back("SubGeV-mulike-0dcy");
  TreeNames.push_back("SubGeV-mulike-1dcy");
  TreeNames.push_back("SubGeV-mulike-2dcy");
  TreeNames.push_back("SubGeV-pi0like");
  TreeNames.push_back("MultiGeV-elike-nue");
  TreeNames.push_back("MultiGeV-elike-nuebar");
  TreeNames.push_back("MultiGeV-mulike");
  TreeNames.push_back("MultiRing-elike-nue");
  TreeNames.push_back("MultiRing-elike-nuebar");
  TreeNames.push_back("MultiRing-mulike");
  TreeNames.push_back("MultiRingOther-1");
  TreeNames.push_back("PCStop");
  TreeNames.push_back("PCThru");
  TreeNames.push_back("UpStop-mu");
  TreeNames.push_back("UpThruNonShower-mu");
  TreeNames.push_back("UpThruShower-mu");
  
  return TreeNames;
}

std::vector< std::vector< std::vector<double> > > ReturnVector(TString FileName, std::vector<TString> TreeNames, TString BranchName, std::vector<double> SubDivisionBinningVec, int nOscThrows) {
  std::cout << std::endl;
  
  TFile* File = new TFile(FileName);
  if (!File) {
    std::cout << "Did not find:" << FileName << std::endl;
  }
  
  int nSubDivisionBinning = SubDivisionBinningVec.size();

  int nTrees = TreeNames.size();
  
  std::vector< std::vector< std::vector<double> > > VariableVector(nTrees);
  for (int iTree=0;iTree<nTrees;iTree++) {
    VariableVector[iTree].resize(nOscThrows);
    for (int iThrow=0;iThrow<nOscThrows;iThrow++) {
      VariableVector[iTree][iThrow].resize(nSubDivisionBinning);
    }
  }

  double Variable;
  int Throw;
  int SubDivisionBinning;

  TTree* Tree;
  int nEntries;
  
  for (int iTree=0;iTree<nTrees;iTree++) {
    Tree = (TTree*)File->Get(TreeNames[iTree]);

    Tree->SetBranchAddress(BranchName,&Variable);
    Tree->SetBranchAddress("iThrow",&Throw);
    Tree->SetBranchAddress("numFineEnergyBins",&SubDivisionBinning);

    nEntries = Tree->GetEntries();
    for (int iEntry=0;iEntry<nEntries;iEntry++) {
      Tree->GetEntry(iEntry);

      int Index = -1;
      
      bool foundSubDivisionBinning = false;
      for (int iSubDivisionBinning=0;iSubDivisionBinning<nSubDivisionBinning;iSubDivisionBinning++) {
	if (SubDivisionBinningVec[iSubDivisionBinning] == SubDivisionBinning) {

	  if (foundSubDivisionBinning) {
	    std::cout << "Already set value for some reason" << std::endl;
	    throw;
	  }

	  Index = iSubDivisionBinning;
	  
	  foundSubDivisionBinning = true;
	  break;
	}
      }

      if (!foundSubDivisionBinning) {
	std::cerr << "Not found SubDivisionBinning!" << std::endl;
	throw;
      }

      VariableVector[iTree][Throw][Index] = Variable;
    }
  }

  return VariableVector;
}

void Print3DVector(std::vector< std::vector< std::vector<double> > > Vector) {
  int nTrees = Vector.size();
  int nOscThrows = Vector[0].size();
  int SubDivisionBinning = Vector[0][0].size();

  for (int iTree=0;iTree<nTrees;iTree++) {
    for (int iThrow=0;iThrow<nOscThrows;iThrow++) {
      for (int iFineEnergyBins=0;iFineEnergyBins<SubDivisionBinning;iFineEnergyBins++) {
	std::cout << iTree << " " << iThrow << " " << iFineEnergyBins << " " << Vector[iTree][iThrow][iFineEnergyBins] << std::endl;
      }
    }
  }
  
}

void Print2DVector(std::vector< std::vector<double> > Vector) {
  int nTrees = Vector.size();
  int nOscThrows = Vector[0].size();

  for (int iTree=0;iTree<nTrees;iTree++) {
    for (int iThrow=0;iThrow<nOscThrows;iThrow++) {
      std::cout << iTree << " " << iThrow << " " << Vector[iTree][iThrow] << std::endl;
    }
  }
  
}

//Vector is indexed [][Throw][nSubDivisions]
std::vector< std::vector<double> > ReturnMeanVector(std::vector< std::vector< std::vector<double> > > Vector, int IndexToAverageOver) {
  int nTrees = Vector.size();
  int nOscThrows = Vector[0].size();
  int SubDivisionBinning = Vector[0][0].size();
    
  std::vector< std::vector<double> > MeanVector;

  if (IndexToAverageOver == 3) {
    MeanVector.resize(nTrees);
    for (int iTree=0;iTree<nTrees;iTree++) {
      MeanVector[iTree].resize(nOscThrows);
    }
    
    for (int iTree=0;iTree<nTrees;iTree++) {
      for (int iThrow=0;iThrow<nOscThrows;iThrow++) {
	
	double Sum = 0;
	int nCounts = 0;
	
	for (int iFineEnergyBins=0;iFineEnergyBins<SubDivisionBinning;iFineEnergyBins++) {
	  if (iFineEnergyBins < (SubDivisionBinning-5)) continue;
	  Sum += Vector[iTree][iThrow][iFineEnergyBins];
	  nCounts += 1;
	}
	
	double Mean = Sum/double(nCounts);
	MeanVector[iTree][iThrow] = Mean;
      }
    }
  }

  else if (IndexToAverageOver == 2) {
    MeanVector.resize(nTrees);
    for (int iTree=0;iTree<nTrees;iTree++) {
      MeanVector[iTree].resize(SubDivisionBinning);
    }

    for (int iTree=0;iTree<nTrees;iTree++) {
      for (int iFineEnergyBins=0;iFineEnergyBins<SubDivisionBinning;iFineEnergyBins++) {
	
        double Sum = 0;
        int nCounts = 0;

	for (int iThrow=0;iThrow<nOscThrows;iThrow++) {
	  Sum += Vector[iTree][iThrow][iFineEnergyBins];
          nCounts += 1;
	}

	double Mean = Sum/double(nCounts);
        MeanVector[iTree][iFineEnergyBins] = Mean;
      }
    }
  }

  else {
    std::cerr << "Invalid option" << std::endl;
    throw;
  }

  return MeanVector;
}

std::vector< std::vector<double> > ReturnVarianceVector(std::vector< std::vector<double> > Mean_Squared_MeanToDifference_Vector, std::vector< std::vector<double> > Mean_DifferenceToMean_Vector) {
  std::vector< std::vector<double> > ReturnVector;

  int nTrees = Mean_Squared_MeanToDifference_Vector.size();
  int nSubDivisionBinning = Mean_Squared_MeanToDifference_Vector[0].size();

  ReturnVector.resize(nTrees);
  for (int iTree=0;iTree<nTrees;iTree++) {
    ReturnVector[iTree].resize(nSubDivisionBinning);
  }

  for (int iTree=0;iTree<nTrees;iTree++) {
    for (int iFineEnergyBins=0;iFineEnergyBins<nSubDivisionBinning;iFineEnergyBins++) {
      ReturnVector[iTree][iFineEnergyBins] = Mean_Squared_MeanToDifference_Vector[iTree][iFineEnergyBins] - pow(Mean_DifferenceToMean_Vector[iTree][iFineEnergyBins],2);
      //std::cout << iTree << " " << iFineEnergyBins << " " << Mean_Squared_MeanToDifference_Vector[iTree][iFineEnergyBins] << " " << Mean_DifferenceToMean_Vector[iTree][iFineEnergyBins] << " " << pow(Mean_DifferenceToMean_Vector[iTree][iFineEnergyBins],2) << " " << ReturnVector[iTree][iFineEnergyBins] << std::endl;                                                                                          
    }
  }

  return ReturnVector;
}

std::vector< std::vector< std::vector<double> > > ReturnDifferenceVector(std::vector< std::vector< std::vector<double> > > VariableVector, std::vector< std::vector<double> > MeanVector, int Power) {
  int nTrees = VariableVector.size();
  int nOscThrows = VariableVector[0].size();
  int nSubDivisionBinning = VariableVector[0][0].size();

  std::vector< std::vector< std::vector<double> > > DifferenceVector(nTrees);
  for (int iTree=0;iTree<nTrees;iTree++) {
    DifferenceVector[iTree].resize(nOscThrows);
    for (int iThrow=0;iThrow<nOscThrows;iThrow++) {
      DifferenceVector[iTree][iThrow].resize(nSubDivisionBinning);
    }
  }

  for (int iTree=0;iTree<nTrees;iTree++) {
    for (int iThrow=0;iThrow<nOscThrows;iThrow++) {
      for (int iFineEnergyBins=0;iFineEnergyBins<nSubDivisionBinning;iFineEnergyBins++) {
	DifferenceVector[iTree][iThrow][iFineEnergyBins] = pow((VariableVector[iTree][iThrow][iFineEnergyBins] - MeanVector[iTree][iThrow]),Power);
      }
    }
  }

  return DifferenceVector;
}

void PrintAllVectors(std::vector< std::vector< std::vector<double> > > VariableVector, std::vector< std::vector<double> > MeanVector, std::vector< std::vector< std::vector<double> > > SquaredDifferenceVector) {
  int nTrees = VariableVector.size();
  int nOscThrows = VariableVector[0].size();
  int nSubDivisionBinning = VariableVector[0][0].size();

  for (int iTree=0;iTree<nTrees;iTree++) {
    for (int iThrow=0;iThrow<nOscThrows;iThrow++) {
      for (int iFineEnergyBins=0;iFineEnergyBins<nSubDivisionBinning;iFineEnergyBins++) {
        std::cout << iTree << " " << iThrow << " " << iFineEnergyBins << " " << VariableVector[iTree][iThrow][iFineEnergyBins] << " " << MeanVector[iTree][iThrow] << " " << SquaredDifferenceVector[iTree][iThrow][iFineEnergyBins] << std::endl;
      }
    }
  }
}

std::vector< std::vector<TGraph*> > ReturnGraphs(std::vector< std::vector< std::vector<double> > > Vector, std::vector<double> SubDivisionBinning) {
  int nTrees = Vector.size();
  int nOscThrows = Vector[0].size();

  std::vector< std::vector<TGraph*> > GraphVector(nTrees);
  for (int iTree=0;iTree<nTrees;iTree++) {
    GraphVector[iTree].resize(nOscThrows);
  }

  int nPoints = Vector[0][0].size();

  for (int iTree=0;iTree<nTrees;iTree++) {
    for (int iThrow=0;iThrow<nOscThrows;iThrow++) {
      GraphVector[iTree][iThrow] = new TGraph(nPoints,SubDivisionBinning.data(),(Vector[iTree][iThrow]).data());
      GraphVector[iTree][iThrow]->SetTitle(Form("Throw_%i",iThrow));
    }
  }

  return GraphVector;
}

std::vector<TGraph*> ReturnVarianceGraphs(std::vector< std::vector<double> > Vector, std::vector<double> SubDivisionBinning, std::vector<TString> TreeNames) {
  int nTrees = Vector.size();
  int nPoints = Vector[0].size();
  
  std::vector<TGraph*> GraphVector(nTrees);

  for (int iTree=0;iTree<nTrees;iTree++) {
    GraphVector[iTree] = new TGraph(nPoints,SubDivisionBinning.data(),(Vector[iTree]).data());
    GraphVector[iTree]->SetTitle(TreeNames[iTree]);
  }

  return GraphVector;
}

void plotVariableGraphs(std::vector< std::vector<TGraph*> > VariableGraphs, std::vector< std::vector<double> > MeanVector, std::vector<TString> TreeNames, TString OutputName, double XAxisRange, TString XAxisCaption, TString YAxisCaption) {
  TCanvas* Canv = new TCanvas("VariableCanv","");
  Canv->Print(OutputName+"[");
  
  int nDiv = 5;
  int nPlots = 30;

  int nTrees = TreeNames.size();
  for (int iTree=0;iTree<nTrees;iTree++) {
    Canv->Divide(nDiv+1,int(nPlots/nDiv));

    TLatex *lat = new TLatex();
    lat->DrawLatexNDC(.4,.95,TreeNames[iTree]);
    
    for (int iPlot=0;iPlot<nPlots;iPlot++) {
      Canv->cd(nDiv+2+iPlot);

      VariableGraphs[iTree][iPlot]->Draw();
      VariableGraphs[iTree][iPlot]->GetXaxis()->SetRangeUser(0.,XAxisRange);
      VariableGraphs[iTree][iPlot]->GetXaxis()->SetTitle(XAxisCaption);
      VariableGraphs[iTree][iPlot]->GetXaxis()->SetLabelOffset(0.02);
      VariableGraphs[iTree][iPlot]->GetXaxis()->SetLabelSize(0.05);
      VariableGraphs[iTree][iPlot]->GetXaxis()->SetTitleOffset(1);
      VariableGraphs[iTree][iPlot]->GetYaxis()->SetTitle(YAxisCaption);

      TLine* Line = new TLine(0.,MeanVector[iTree][iPlot],XAxisRange,MeanVector[iTree][iPlot]);
      Line->SetLineColor(kRed);
      Line->Draw("SAME");
    }

    Canv->Print(OutputName);
    Canv->Clear();
  }

  Canv->Print(OutputName+"]");
}

void plotSquaredDifferenceGraphs(std::vector< std::vector<TGraph*> > SquaredDifferenceGraphs, std::vector<TString> TreeNames, TString OutputName, double XAxisRange, TString XAxisCaption, TString YAxisCaption) {
  TCanvas* Canv = new TCanvas("SquaredDifferenceCanv","");
  Canv->Print(OutputName+"[");
  
  int nDiv = 5;
  int nPlots = 30;

  int nTrees = TreeNames.size();
  for (int iTree=0;iTree<nTrees;iTree++) {
    Canv->Divide(nDiv+1,int(nPlots/nDiv));
    
    TLatex *lat = new TLatex();
    lat->DrawLatexNDC(.4,.95,TreeNames[iTree]);
    
    for (int iPlot=0;iPlot<nPlots;iPlot++) {
      Canv->cd(nDiv+2+iPlot);
      gPad->SetLogy(true);
      
      SquaredDifferenceGraphs[iTree][iPlot]->Draw();
      SquaredDifferenceGraphs[iTree][iPlot]->GetXaxis()->SetRangeUser(0.,XAxisRange);
      SquaredDifferenceGraphs[iTree][iPlot]->GetXaxis()->SetTitle(XAxisCaption);
      SquaredDifferenceGraphs[iTree][iPlot]->GetXaxis()->SetLabelOffset(0.037);
      SquaredDifferenceGraphs[iTree][iPlot]->GetXaxis()->SetLabelSize(0.05);
      SquaredDifferenceGraphs[iTree][iPlot]->GetXaxis()->SetTitleOffset(1.6);
      SquaredDifferenceGraphs[iTree][iPlot]->GetYaxis()->SetTitle(YAxisCaption);
    }

    Canv->Print(OutputName);
    Canv->Clear();
  }

  Canv->Print(OutputName+"]");
}

void plotVarianceGraphs(std::vector<TGraph*> VarianceGraphs, std::vector<TString> TreeNames, TString OutputName, double XAxisRange, TString XAxisCaption, TString YAxisCaption) {
  TCanvas* Canv = new TCanvas("VarianceCanv","");
  
  int nDiv = 3;
  int nPlots = VarianceGraphs.size();
  if (nPlots < nDiv) {nDiv = nPlots;}

  Canv->Divide(int(nPlots/nDiv),nDiv);

  double DefaultThreshold = 0.001;
  double Threshold;

  int nTrees = TreeNames.size();
  for (int iTree=0;iTree<nTrees;iTree++) {

    TPad* Pad = (TPad*)Canv->cd(1+iTree);
    Pad->Draw();
    Pad->cd();
    Pad->SetLeftMargin(0.25);
    gPad->SetLogy(true);
    
    VarianceGraphs[iTree]->Draw();
    VarianceGraphs[iTree]->GetXaxis()->SetRangeUser(0.,XAxisRange);
    VarianceGraphs[iTree]->GetXaxis()->SetTitle(XAxisCaption);
    VarianceGraphs[iTree]->GetXaxis()->SetLabelOffset(0.027);
    VarianceGraphs[iTree]->GetXaxis()->SetLabelSize(0.05);
    VarianceGraphs[iTree]->GetXaxis()->SetTitleOffset(1.3);
    VarianceGraphs[iTree]->GetYaxis()->SetTitle(YAxisCaption);

    double MaxY = -1e8;
    double X, Y;
    for (int iPoint=0;iPoint<VarianceGraphs[iTree]->GetN();iPoint++) {
      VarianceGraphs[iTree]->GetPoint(iPoint,X,Y);
      if (Y > MaxY) MaxY = Y;
    }
    if (MaxY < DefaultThreshold) {
      Threshold = MaxY;
    } else {
      Threshold = DefaultThreshold;
    }

    TLine* Line1 = new TLine(0.,Threshold,XAxisRange,Threshold);
    Line1->SetLineColor(kRed);
    Line1->Draw("SAME");

    TLine* Line2 = new TLine(10.,0.,10.,Threshold);
    Line2->SetLineColor(kRed);
    Line2->SetLineStyle(kDashed);
    Line2->Draw("SAME");
  }

  Canv->Print(OutputName);
}

void plotVarianceGraphsOneCanvas(std::vector<TGraph*> VarianceGraphs, std::vector<TString> TreeNames, TString OutputName, double XAxisRange, TString XAxisCaption, TString YAxisCaption) {
  TCanvas* Canv = new TCanvas("VarianceCanvOneCanv","");
  Canv->SetLogy(true);
  
  int nTrees = TreeNames.size();
  //for (int iTree=0;iTree<nTrees;iTree++) {
  for (int iTree=0;iTree<1;iTree++) {

    if (iTree==0) {
      VarianceGraphs[iTree]->Draw();
    } else {
      VarianceGraphs[iTree]->Draw("SAME");
    }
    VarianceGraphs[iTree]->GetXaxis()->SetRangeUser(0.,XAxisRange);
    VarianceGraphs[iTree]->GetXaxis()->SetTitle(XAxisCaption);
    VarianceGraphs[iTree]->GetXaxis()->SetLabelOffset(0.0);

    //VarianceGraphs[iTree]->GetXaxis()->SetLabelOffset(0.027);
    //VarianceGraphs[iTree]->GetXaxis()->SetTitleOffset(1.3);

    VarianceGraphs[iTree]->GetYaxis()->SetTitle(YAxisCaption);

  }

  Canv->Print(OutputName);
}

void LLHVariationStudy() {
  TString FileName = "../../MacroInputs/VariationStudies/AsimovA_1D_FloatingOscPars_EventRateVariation_CosZ_Varied_Energy_Varied.root";

  gStyle->SetTitleSize(0.06,"X");
  gStyle->SetTitleSize(0.06,"Y");
  gStyle->SetTitleSize(0.08,"A");

  gStyle->SetPadBottomMargin(0.2);
  gStyle->SetPadLeftMargin(0.2);

  gStyle->SetLabelSize(0.1,"X");
  gStyle->SetLabelSize(0.08,"Y");
  
  std::vector<TString> TreeNames = ReturnTreeNames(FileName);
  std::cout << "TreeNames[0]:" << TreeNames[0] << std::endl;
  
  std::vector<double> SubDivisionBinning = ReturnFineEnergyBinning(FileName,TreeNames[0]);
  int nSubDivisionBinning = SubDivisionBinning.size();

  std::cout << "nSubDivisionBinning:" << nSubDivisionBinning << std::endl;

  std::cout << "\n" << "SubDivisionBinning:" << std::endl;
  for (int iSubDivisionBinning=0;iSubDivisionBinning<nSubDivisionBinning;iSubDivisionBinning++) {
    std::cout << SubDivisionBinning[iSubDivisionBinning] << ", ";
  }
  std::cout << "\n" << std::endl;
  
  int nOscThrows = ReturnNThrows(FileName,TreeNames[0]);
  std::cout << "nOscThrows:" << nOscThrows << std::endl;

  TString BranchName = "Likelihood";
  std::cout << "BranchName:" << BranchName << std::endl;

  //############################################################################################################################################
  //Start analysis with inputs gathered from ROOT file

  // [Sample][Throw][N]
  std::vector< std::vector< std::vector<double> > > Variable_Vector = ReturnVector(FileName,TreeNames,BranchName,SubDivisionBinning,nOscThrows);
  std::vector< std::vector<TGraph*> > Variable_Graphs = ReturnGraphs(Variable_Vector,SubDivisionBinning);

  // [Sample][Throw]
  std::vector< std::vector<double> > Mean_Vector = ReturnMeanVector(Variable_Vector,3);

  // [Sample][Throw][N]
  std::vector< std::vector< std::vector<double> > > DifferenceToMean_Vector = ReturnDifferenceVector(Variable_Vector,Mean_Vector,1);
  std::vector< std::vector< std::vector<double> > > Squared_DifferenceToMean_Vector = ReturnDifferenceVector(Variable_Vector,Mean_Vector,2);

  // [Sample][N]
  std::vector< std::vector<double> > Mean_DifferenceToMean_Vector = ReturnMeanVector(DifferenceToMean_Vector,2);
  std::vector< std::vector<double> > Mean_Squared_DifferenceToMean_Vector = ReturnMeanVector(Squared_DifferenceToMean_Vector,2);

  // [Sample][N]
  std::vector< std::vector<double> > Variance_Vector = ReturnVarianceVector(Mean_Squared_DifferenceToMean_Vector,Mean_DifferenceToMean_Vector);
  std::vector<TGraph*> Variance_Graph = ReturnVarianceGraphs(Variance_Vector,SubDivisionBinning,TreeNames);

  //############################################################################################################################################
  //Start plotting
  
  TString VariableGraphOutputName = BranchName+"_VariableGraphs.pdf";
  std::cout << "Outputting Variable Graphs to:" << VariableGraphOutputName << std::endl;
  plotVariableGraphs(Variable_Graphs,Mean_Vector,TreeNames,VariableGraphOutputName,SubDivisionBinning[nSubDivisionBinning-1],"SubDivision","LLH");

  TString VarianceGraphOutputName = BranchName+"_VarianceGraphs.pdf";
  std::cout << "Outputting Variance Graphs to:" << VarianceGraphOutputName << std::endl;
  plotVarianceGraphs(Variance_Graph,TreeNames,VarianceGraphOutputName,SubDivisionBinning[nSubDivisionBinning-1],"SubDivision","Variance in LLH");

}
