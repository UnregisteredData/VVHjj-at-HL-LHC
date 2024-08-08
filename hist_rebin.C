#include "TFile.h"
#include "TH1F.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"

void hist_rebin(){


TFile* input_hists = TFile::Open("Fit_input.root");
//TString name = "pretagxjet_vpt0_"+histo_name;
cout<<input_hists -> GetSize()<<endl;
//cout<<input_hists ->Get("whjjmVVHjj") -> GetName()<<endl;

TH1F* SignalC = (TH1F*)input_hists->Get("whjjmcVVHjj");
TH1F* Signal1 = (TH1F*)input_hists->Get("whjjmVVHjj");
TH1F* BackgroundC = (TH1F*) input_hists->Get("whjjmcttjj");
TH1F* Background1 = (TH1F*) input_hists->Get("whjjmttjj");
TH1F* SignalC2 = (TH1F*)input_hists->Get("whjjmc2VVHjj");
TH1F* Signal2 = (TH1F*)input_hists->Get("whjjm2VVHjj");
TH1F* BackgroundC2 = (TH1F*) input_hists->Get("whjjmc2ttjj");
TH1F* Background2 = (TH1F*) input_hists->Get("whjjm2ttjj");

std::vector<TH1F*> histosC = {SignalC, BackgroundC};
std::vector<TH1F*> histos1 = {Signal1, Background1};
std::vector<TH1F*> histosC2 = {SignalC2, BackgroundC2};

TFile *Rebinned = new TFile("Rebinned.root", "RECREATE", "Rebinned");
for(Int_t j=0; j<histosC.size();j++){

    float x[35]={0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200, 3300, 3400};
	    
    TH1D* hC_rebin =      new TH1D(histosC[j]->GetName(),histosC[j]->GetName(),34,x); 

    // cout << histos[j]->GetNbinsX() << endl;

    for (Int_t i = 0; i< 35; i++){
      
      hC_rebin->SetBinContent(i,histosC[j]->GetBinContent(i));
      hC_rebin->SetBinError(i,histosC[j]->GetBinError(i));      
      
    }

    hC_rebin->Write(histosC[j]->GetName());

  }
for(Int_t j=0; j<histos1.size();j++){

    float x[17]={0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600};
	    
    TH1D* h1_rebin =      new TH1D(histos1[j]->GetName(),histos1[j]->GetName(),16,x); 

    // cout << histos[j]->GetNbinsX() << endl;

    for (Int_t i = 0; i< 17; i++){
      
      h1_rebin->SetBinContent(i,histos1[j]->GetBinContent(i));
      h1_rebin->SetBinError(i,histos1[j]->GetBinError(i));      
      
    }

    h1_rebin->Write(histos1[j]->GetName());

  }
  for(Int_t j=0; j<histosC2.size();j++){

    float x[41]={0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200, 3300, 3400, 3500, 3600, 3700, 3800, 3900, 4000};
	    
    TH1D* h1_rebin =      new TH1D(histosC2[j]->GetName(),histosC2[j]->GetName(),40,x); 

    // cout << histos[j]->GetNbinsX() << endl;

    for (Int_t i = 0; i< 41; i++){
      
      h1_rebin->SetBinContent(i,histosC2[j]->GetBinContent(i));
      h1_rebin->SetBinError(i,histosC2[j]->GetBinError(i));      
      
    }

    h1_rebin->Write(histosC2[j]->GetName());

  }

 
}
