#include "TFile.h"
#include "TH1F.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"

  
bool reorder_by_mass(const TLorentzVector &a, const TLorentzVector &b){
 return a.M() > b.M();
}
bool reorderTLorentz(const TLorentzVector &a, const TLorentzVector &b){
 return a.Pt() > b.Pt();
}
void Analysis(){
    //auto VVHjj = TFile::Open("/usatlas/u/mmollerac/usatlasdata/WWHjj/Delphes-3.5.0/New_Trees/VVHjj.root");
    auto VVHjj = TFile::Open("C:\Users\hcds\VVHjj.root")
    if (!VVHjj || VVHjj->IsZombie()) {
      return;
   }
    //auto ttjj = TFile::Open("/usatlas/u/mmollerac/usatlasdata/WWHjj/Delphes-3.5.0/New_Trees/ttjj.root");
    auto ttjj = TFile::Open("C:\Users\hcds\ttjj.root")
    if (!ttjj || ttjj->IsZombie()) {
      return;
   }

   //Values
   Double_t Lumi = 3000;
   Double_t cross_section_S = 0.00534700156855;
   Double_t cross_section_B = 232.3;
   Double_t Entries_S = 711311;
   Double_t Entries_B = 2565538;
   std::vector<double> Signals(60, 0.0);
   std::vector<double> Backgrounds(60, 0.0);
   Double_t sum_of_weights_S;
   Double_t sum_of_weights_B;
   TTreeReader WeightReader_S("myTree", VVHjj);
   TTreeReaderValue<vector<float>> SignalWeight(WeightReader_S, "weights_event_tree");
   while(WeightReader_S.Next()){
    sum_of_weights_S += (*SignalWeight)[0];
   }
   TTreeReader WeightReader_B("myTree", ttjj);
   TTreeReaderValue<vector<float>> BackgroundWeight(WeightReader_B, "weights_event_tree");
   while(WeightReader_B.Next()){
    sum_of_weights_B += (*BackgroundWeight)[0];
   }
   Double_t Scale_S = (Lumi*cross_section_S*1000)/(Entries_S*sum_of_weights_S);
   Double_t Scale_B = (Lumi*cross_section_B*1000)/(Entries_B*sum_of_weights_B);

   //Weighting:
   Double_t No_W_Scale_S = (Lumi*cross_section_S*1000)/Entries_S;
   Double_t W_Scale = (Lumi*1000)/(Entries_S*sum_of_weights_S);
   Double_t No_W_Scale_B = (Lumi*cross_section_B*1000)/Entries_B;
   //Current selections
   //TString selection1 = "Selection: NFatJets>1, FatJetPt > 200GeV, FatJetMass > 30GeV, Nleptons > 0, LeptonsPt > 30GeV, TagJetsPt>30GeV, 40 GeV < HCandMass < 140 Gev";
   //TString selection2 = "Selection: NFatJets==1, FatJetPt > 200GeV, TagJetsPt>30GeV";
   TString selection = "No Selection";
   TString selection1 = "Seleccion boosteada";
   TString selection2 = "Seleccion hibrida";
   TString selectionc = "Cortes Optimizados";

   //Initializing histograms
   //First Selection:
   auto S1_LeadingFatJetPt_hist = new TH1F("lfjptVVHjj","Leading Large R Jet Pt [GeV]",160,0,1000);
   auto S1_SubleadingFatJetPt_hist = new TH1F("sfjptVVHjj","Subleading Large R Jet Pt [GeV]",160,0,1000);
   auto S1_MissingEt_hist = new TH1F("metVVHjj","MET [GeV]",160,-0.5,800);
   auto S1_Nleptons_hist = new TH1F("nlVVHjj","N Leptons",10,-0.5,9.5);
   auto S1_FatJetMass_hist = new TH1F("fjmVVHjj","Large R Jets Mass [GeV]",160,20,300);
   auto S1_FirstLeptonPt_hist = new TH1F("flptVVHjj","Leading Lepton Pt [GeV]",160,0,1000);
   auto S1_SecondLeptonPt_hist = new TH1F("lptVVHjj","Sub-Leading Lepton Pt [GeV]",160,0,300);
   auto S1_LeadingFatJetMass_hist = new TH1F("lfjmVVHjj","Leading Large R Jet Mass [GeV]",160,20,200);
   auto S1_SubleadingFatJetMass_hist = new TH1F("sfjmVVHjj","Subleading Large R Jet Mass [GeV]",160,20,200);
   auto S1_FatJetDeltaEta_hist = new TH1F("fjdeVVHjj","DeltaEta (Lead Fat Jet, Sub Lead Fat Jet)",160,-4,4);
   auto S1_LFatJetSRJetDeltaR_hist = new TH1F("lfjsrdeVVHjj","Delta R (Lead Fat Jet, SmallRjets)",160,-1,8);
   auto S1_SFatJetSRJetDeltaR_hist = new TH1F("sfjsrdeVVHjj","Delta R (Sublead Fat Jet, SmallRjets)",160,-1,8);
   auto S1_LeptonDeltaR_hist = new TH1F("ldrVVHjj","Delta R (Leptons, SmallRjets)",160,-1,8);
   auto S1_NSmallRJets_hist = new TH1F("nsrjVVHjj","N SmallRJets Pt > 30 GeV",12,-0.5,11.5);
   auto S1_NTagCandidates_hist = new TH1F("ntcVVHjj","N SmallRJets outside boson candidates",12,-0.5,11.5);
   auto S1_NSmallRJetsInside_hist = new TH1F("nsjibcVVHjj","N SmallRJets inside boson candidates",12,-0.5,11.5);
   auto S1_NFatJets_hist = new TH1F("nfjVVHjj","N Large R Jets",10,-0.5,9.5);
   auto S1_NbJets_hist = new TH1F("nbjVVHjj","N bJets Pt > 30 Gev",8,-0.5,7.5);
   auto S1_NFatbJets_hist = new TH1F("nfbjVVHjj","N b-jets per Fat Jets",8,-0.5,7.5);
   auto S1_Nelectrons_hist = new TH1F("neVVHjj","N electrons",8,-0.5,7.5);
   auto S1_Nmuons_hist = new TH1F("nmVVHjj","N muons",8,-0.5,7.5);
   auto S1_NTagJets_hist = new TH1F("ntjVVHjj","N Tag Jets", 5, -0.5, 4.5);
   auto S1_TagJetDeltaEta_hist = new TH1F("tjdeVVHjj","Delta Eta (Tag Jet 1, Tag Jet 2)",160,-1,10);
   auto S1_NbJetsLeadingFatJet_hist = new TH1F("nbjlVVHjj","N b-jets inside Leading Fat Jet",8,-0.5,7.5);
   auto S1_NbJetsSubleadingFatJet_hist = new TH1F("nbjsVVHjj","N b-jets inside Subleading Fat Jet",8,-0.5,7.5);
   auto S1_NFatJetsw2bjets_hist = new TH1F("fjw2bjVVHjj","N Fat Jets with 2 b-jets",8,-0.5,7.5);
   auto S1_FatJets2bJetsMass_hist = new TH1F("fjw2bmVVHjj","Fat Jets with 2 b-jets Mass",160,50,150);
   auto S1_HCandMass_hist = new TH1F("hcmVVHjj","H Candidate Mass [GeV]",160,50,300);
   auto S1_HCandPt_hist = new TH1F("hcptVVHjj","H Candidate Pt [GeV]",160,50,1000);
   auto S1_HCandEta_hist = new TH1F("hcetaVVHjj","H Candidate Eta",160,-8,8);
   auto S1_HCandPhi_hist = new TH1F("hcphiVVHjj","H Candidate Phi",160,-4,4);
   auto S1_WCandMass_hist = new TH1F("wcmVVHjj","W Candidate Mass [GeV]",160,20,300);
   auto S1_WCandPt_hist = new TH1F("wcptVVHjj","W Candidate Pt [GeV]",160,50,1000);
   auto S1_WCandEta_hist = new TH1F("wcetaVVHjj","W Candidate Eta",160,-8,8);
   auto S1_WCandPhi_hist = new TH1F("wcphiVVHjj","W Candidate Phi",160,-4,4);
   auto S1_HCandMassMethod_hist = new TH1F("hcmmVVHjj","H Candidate Mass Picked by Mass [GeV]",160,20,200);
   auto S1_WCandMassMethod_hist = new TH1F("wcmmVVHjj","W Candidate Mass Picked by Mass [GeV]",160,20,150);
   auto S1_TagJetsMass_hist = new TH1F("tjmVVHjj","Mjj [GeV]",160,0,6000);
   auto S1_TagJet1Pt_hist = new TH1F("tj1ptVVHjj","Tag Jet 1 Pt [GeV]",160,50,1000);
   auto S1_TagJet1Eta_hist = new TH1F("tj1etaVVHjj","Tag Jet 1 Eta",160,-8,8);
   auto S1_TagJet1Phi_hist = new TH1F("tj1phiVVHjj","Tag Jet 1 Phi",160,-4,4);
   auto S1_TagJet2Pt_hist = new TH1F("tj2ptVVHjj","Tag Jet 2 Pt [GeV]",160,50,1000);
   auto S1_TagJet2Eta_hist = new TH1F("tj2etaVVHjj","Tag Jet 2 Eta",160,-8,8);
   auto S1_TagJet2Phi_hist = new TH1F("tj2phiVVHjj","Tag Jet 2 Phi",160,-4,4);
   auto S1_ElectronIso_hist = new TH1F("eiVVHjj","Electron Isolation",160,0,0.1);
   auto S1_MuonIso_hist = new TH1F("miVVHjj","Muon Isolation",160,0,0.1);
   auto S1_DeltaEtaNeg_hist = new TH1F("denVVHjj","N events with 2 jets same Eta sign",10,-0.5,9.5);
   auto S1_EventswTagJets_hist = new TH1F("ewtjVVHjj","Percentage of events with elegible tag jets (not inside Fat Jets)",6,-0.5,5.5);
   auto S1_SmallRJetsPt_hist = new TH1F("sjptVVHjj","Small R Jets Pt [GeV]",160,0,1000);
   auto S1_SmallRJetsEta_hist = new TH1F("sjeVVHjj","Small R Jets Eta",160,-10,10);
   auto S1_TagJet1HCandDeltaR_hist = new TH1F("tj1hcdrVVHjj","Delta R (Tag Jet 1, H Candidate) Boosted Selection",160,-1,8);
   auto S1_TagJet1WCandDeltaR_hist = new TH1F("tj1wcdrVVHjj","Delta R (Tag Jet 1, W Candidate) Boosted Selection",160,-1,8);
   auto S1_TagJet2HCandDeltaR_hist = new TH1F("tj2hcdrVVHjj","Delta R (Tag Jet 2, H Candidate) Boosted Selection",160,-1,8);
   auto S1_TagJet2WCandDeltaR_hist = new TH1F("tj2wcdrVVHjj","Delta R (Tag Jet 2, W Candidate) Boosted Selection",160,-1,8);
   auto S1_Truth1RecoDeltaR_hist = new TH1F("t1rdrVVHjj","Delta R (Truth Jet 1, Reco Tag Jet)",160,-0.5,8);
   auto S1_Truth2RecoDeltaR_hist = new TH1F("t2rdrVVHjj","Delta R (Truth Jet 2, Reco Tag Jet)",160,-0.5,8);
   auto S1_Truth1Reco1DeltaR_hist = new TH1F("t1r1drVVHjj","Delta R (Truth Quark 1, Reco Tag Jet 1)",160,-0.5,8);
   auto S1_Truth1Reco2DeltaR_hist = new TH1F("t1r2drVVHjj","Delta R (Truth Quark 1, Reco Tag Jet 2)",160,-0.5,8);
   auto S1_Truth2Reco1DeltaR_hist = new TH1F("t2r1drVVHjj","Delta R (Truth Quark 2, Reco Tag Jet 1)",160,-0.5,8);
   auto S1_Truth2Reco2DeltaR_hist = new TH1F("t2r2drVVHjj","Delta R (Truth Quark 2, Reco Tag Jet 2)",160,-0.5,8);
   auto S1_Truth1HCandDeltaR_hist = new TH1F("t1hcdrVVHjj","Delta R (Truth Quark 1, HCand)",160,-0.5,8);
   auto S1_Truth1WCandDeltaR_hist = new TH1F("t1wcdrVVHjj","Delta R (Truth Quark 1, WCand)",160,-0.5,8);
   auto S1_Truth2HCandDeltaR_hist = new TH1F("t2hcdrVVHjj","Delta R (Truth Quark 2, HCand)",160,-0.5,8);
   auto S1_Truth2WCandDeltaR_hist = new TH1F("t2wcdrVVHjj","Delta R (Truth Quark 2, WCand)",160,-0.5,8);
   auto S1_HCandWCandDeltaR_hist = new TH1F("hcwcdrVVHjj","Delta R (HCand, WCand)",160,-0.5,8);
   auto S1_TruthQuark1Eta_hist = new TH1F("tq1eVVHjj","Truth Quark 1 Eta",160,-8,8);
   auto S1_TruthQuark2Eta_hist = new TH1F("tq2eVVHjj","Truth Quark 2 Eta",160,-8,8);
   auto S1_SmallRJet0InsidePt_hist = new TH1F("sj0iptVVHjj","First Jet Inside Fat Jet Pt [GeV]",160,0,1000);
   auto S1_SmallRJet1InsidePt_hist = new TH1F("sj1iptVVHjj","Second Jet Inside Fat Jet Pt [GeV]",160,0,1000);
   auto S1_SmallRJet2InsidePt_hist = new TH1F("sj2iptVVHjj","Third Jet Inside Fat Jet Pt [GeV]",160,0,1000);
   auto S1_SmallRJet3InsidePt_hist = new TH1F("sj3iptVVHjj","Fourth Jet Inside Fat Jet Pt [GeV]",160,0,1000);
   auto S1_SmallRJet4InsidePt_hist = new TH1F("sj4iptVVHjj","Fifth Jet Inside Fat Jet Pt [GeV]",160,0,1000);
   auto S1_SmallRJet5InsidePt_hist = new TH1F("sj5iptVVHjj","Sixth Jet Inside Fat Jet Pt [GeV]",160,0,1000);
   auto S1_Jet0InsideTruthDeltaR_hist = new TH1F("j0itdrVVHjj","Delta R (First Jet Inside Fat Jet, Truth Quark)",160,-0.5,8);
   auto S1_Jet1InsideTruthDeltaR_hist = new TH1F("j1itdrVVHjj","Delta R (Second Jet Inside Fat Jet, Truth Quark)",160,-0.5,8);
   auto S1_Jet2InsideTruthDeltaR_hist = new TH1F("j2itdrVVHjj","Delta R (Third Jet Inside Fat Jet, Truth Quark)",160,-0.5,8);
   auto S1_Jet3InsideTruthDeltaR_hist = new TH1F("j3itdrVVHjj","Delta R (Fourth Jet Inside Fat Jet, Truth Quark)",160,-0.5,8);
   auto S1_Jet4InsideTruthDeltaR_hist = new TH1F("j4itdrVVHjj","Delta R (Fifth Jet Inside Fat Jet, Truth Quark)",160,-0.5,8);
   auto S1_Jet5InsideTruthDeltaR_hist = new TH1F("j5itdrVVHjj","Delta R (Sixth Jet Inside Fat Jet, Truth Quark)",160,-0.5,8);
   auto S1_TruthTagJet1Eta_hist = new TH1F("ttj1etaVVHjj","Truth Tag Jet 1 Eta",160,-8,8);
   auto S1_TruthTagJet2Eta_hist = new TH1F("ttj2etaVVHjj","Truth Tag Jet 2 Eta",160,-8,8);
   auto S1_WHjjMass_hist = new TH1F("whjjmVVHjj","WHjj Mass",160, 400, 7000);
 
   auto B1_LeadingFatJetPt_hist = new TH1F("lfjptttjj","Leading Large R Jet Pt [GeV]",160,0,1000);
   auto B1_SubleadingFatJetPt_hist = new TH1F("sfjptttjj","Subleading Large R Jet Pt [GeV]",160,0,1000);
   auto B1_MissingEt_hist = new TH1F("metttjj","MET [GeV]",160,-.5,800);
   auto B1_Nleptons_hist = new TH1F("nlttjj","N leptones",10,-.5,9.5);
   auto B1_FatJetMass_hist = new TH1F("fjmttjj","Large R Jets Mass [GeV]",160,20,300);
   auto B1_FirstLeptonPt_hist = new TH1F("flptttjj","Leading Lepton Pt [GeV]",160,0,1000);
   auto B1_SecondLeptonPt_hist = new TH1F("lptttjj","Subleading Lepton Pt [GeV]",160,0,300);
   auto B1_LeadingFatJetMass_hist = new TH1F("lfjmttjj","Leading Large R Jet Mass [GeV]",160,20,200);
   auto B1_SubleadingFatJetMass_hist = new TH1F("sfjmttjj","Subleading Fat Jet Mass [GeV]",160,20,200);
   auto B1_FatJetDeltaEta_hist = new TH1F("fjdettjj","DeltaEta (Lead Fat Jet, Sub Lead Fat Jet)",160,-4,4);
   auto B1_LFatJetSRJetDeltaR_hist = new TH1F("lfjsrdettjj","Delta R (Lead Fat Jet, SmallRjets)",160,-1,8);
   auto B1_SFatJetSRJetDeltaR_hist = new TH1F("sfjsrdettjj","Delta R (Sublead Fat Jet, SmallRjets)",160,-1,8);
   auto B1_LeptonDeltaR_hist = new TH1F("ldrttjj","Minimum Delta R (Lepton, SmallRjets)",160,-1,8);
   auto B1_NSmallRJets_hist = new TH1F("nsrjttjj","N SmallRJets Pt > 30 GeV",12,-0.5,11.5);
   auto B1_NTagCandidates_hist = new TH1F("ntcttjj","N SmallRJets outside boson candidates",12,-0.5,11.5);
   auto B1_NSmallRJetsInside_hist = new TH1F("nsjibcttjj","N SmallRJets inside boson candidates",12,-0.5,11.5);
   auto B1_NFatJets_hist = new TH1F("nfjttjj","N Large R Jets",10,-0.5,9.5);
   auto B1_NbJets_hist = new TH1F("nbjttjj","N bJets Pt > 30 Gev",8,-0.5,7.5);
   auto B1_NFatbJets_hist = new TH1F("nfbjttjj","N b-jets per Fat Jets",8,-0.5,7.5);
   auto B1_Nelectrons_hist = new TH1F("nettjj","N electrons",8,-0.5,7.5);
   auto B1_Nmuons_hist = new TH1F("nmttjj","N muons",8,-0.5,7.5);
   auto B1_NTagJets_hist = new TH1F("ntjttjj","N Tag Jets", 5, -0.5, 4.5);
   auto B1_TagJetDeltaEta_hist = new TH1F("tjdettjj","Delta Eta (Tag Jet 1, Tag Jet 2)",160,-1,10);
   auto B1_NbJetsLeadingFatJet_hist = new TH1F("nbjlttjj","N b-jets inside Leading Fat Jets",8,-0.5,7.5);
   auto B1_NbJetsSubleadingFatJet_hist = new TH1F("nbjsttjj","N b-jets inside Subleading Fat Jets",8,-0.5,7.5);
   auto B1_NFatJetsw2bjets_hist = new TH1F("fjw2bjttjj","N Fat Jets with 2 b-jets",8,-0.5,7.5);
   auto B1_FatJets2bJetsMass_hist = new TH1F("fjw2bmjttjj","Fat Jets with two b-jets Mass",160,50,150);
   auto B1_HCandMass_hist = new TH1F("hcmttjj","H Candidate Mass [GeV]",160,50,300);
   auto B1_HCandPt_hist = new TH1F("hcptttjj","H Candidate Pt [GeV]",160,50,1000);
   auto B1_HCandEta_hist = new TH1F("hcetattjj","H Candidate Eta",160,-8,8);
   auto B1_HCandPhi_hist = new TH1F("hcphittjj","H Candidate Phi",160,-4,4);
   auto B1_WCandMass_hist = new TH1F("wcmttjj","W Candidate Mass [GeV]",160,20,300);
   auto B1_WCandPt_hist = new TH1F("wcptttjj","W Candidate Pt [GeV]",160,50,1000);
   auto B1_WCandEta_hist = new TH1F("wcetattjj","W Candidate Eta",160,-8,8);
   auto B1_WCandPhi_hist = new TH1F("wcphittjj","W Candidate Phi",160,-4,4);
   auto B1_HCandMassMethod_hist = new TH1F("hcmmttjj","H Candidate Mass Picked by Mass [GeV]",160,20,200);
   auto B1_WCandMassMethod_hist = new TH1F("wcmmttjj","W Candidate Mass Picked by Mass [GeV]",160,20,150);
   auto B1_TagJetsMass_hist = new TH1F("tjmttjj","Mjj [GeV]",160,0,6000);
   auto B1_TagJet1Pt_hist = new TH1F("tj1ptttjj","Tag Jet 1 Pt [GeV]",160,50,1000);
   auto B1_TagJet1Eta_hist = new TH1F("tj1etattjj","Tag Jet 1 Eta",160,-8,8);
   auto B1_TagJet1Phi_hist = new TH1F("tj1phittjj","Tag Jet 1 Phi",160,-4,4);
   auto B1_TagJet2Pt_hist = new TH1F("tj2ptttjj","Tag Jet 2 Pt [GeV]",160,50,1000);
   auto B1_TagJet2Eta_hist = new TH1F("tj2etattjj","Tag Jet 2 Eta",160,-8,8);
   auto B1_TagJet2Phi_hist = new TH1F("tj2phittjj","Tag Jet 2 Phi",160,-4,4);
   auto B1_ElectronIso_hist = new TH1F("eittjj","Electron Isolation",160,0,0.1);
   auto B1_MuonIso_hist = new TH1F("mittjj","Muon Isolation",160,0,0.1);
   auto B1_DeltaEtaNeg_hist = new TH1F("denttjj","N events with 2 jets same Eta sign",10,-0.5,9.5);
   auto B1_EventswTagJets_hist = new TH1F("ewtjttjj","Percentage of events with elegible tag jets (not inside Fat Jets)",6,-0.5,5.5);
   auto B1_SmallRJetsPt_hist = new TH1F("sjptttjj","Small R Jets Pt [GeV]",160,0,1000);
   auto B1_SmallRJetsEta_hist = new TH1F("sjettjj","Small R Jets Eta",160,-10,10);
   auto B1_TagJet1HCandDeltaR_hist = new TH1F("tj1hcdrttjj","Delta R (Tag Jet 1, H Candidate)",160,-1,8);
   auto B1_TagJet1WCandDeltaR_hist = new TH1F("tj1wcdrttjj","Delta R (Tag Jet 1, W Candidate)",160,-1,8);
   auto B1_TagJet2HCandDeltaR_hist = new TH1F("tj2hcdrttjj","Delta R (Tag Jet 2, H Candidate)",160,-1,8);
   auto B1_TagJet2WCandDeltaR_hist = new TH1F("tj2wcdrttjj","Delta R (Tag Jet 2, W Candidate)",160,-1,8);
   auto B1_Truth1RecoDeltaR_hist = new TH1F("t1rdrttjj","Delta R (Truth Jet 1, Reco Tag Jet)",160,-0.5,8);
   auto B1_Truth2RecoDeltaR_hist = new TH1F("t2rdrttjj","Delta R (Truth Jet 2, Reco Tag Jet)",160,-0.5,8);
   auto B1_TruthQuark1Eta_hist = new TH1F("ttj1ettjj","Truth Quark 1 Eta",160,-8,8);
   auto B1_TruthQuark2Eta_hist = new TH1F("ttj2ettjj","Truth Quark 2 Eta",160,-8,8);
   auto B1_Truth1Reco1DeltaR_hist = new TH1F("t1r1drttjj","Delta R (Truth Quark 1, Reco Tag Jet 1)",160,-0.5,8);
   auto B1_Truth1Reco2DeltaR_hist = new TH1F("t1r2drttjj","Delta R (Truth Quark 1, Reco Tag Jet 2)",160,-0.5,8);
   auto B1_Truth2Reco1DeltaR_hist = new TH1F("t2r1drttjj","Delta R (Truth Quark 2, Reco Tag Jet 1)",160,-0.5,8);
   auto B1_Truth2Reco2DeltaR_hist = new TH1F("t2r2drttjj","Delta R (Truth Quark 2, Reco Tag Jet 2)",160,-0.5,8);
   auto B1_Truth1HCandDeltaR_hist = new TH1F("t1hcdrttjj","Delta R (Truth Quark 1, HCand)",160,-0.5,8);
   auto B1_Truth1WCandDeltaR_hist = new TH1F("t1wcdrttjj","Delta R (Truth Quark 1, WCand)",160,-0.5,8);
   auto B1_Truth2HCandDeltaR_hist = new TH1F("t2hcdrttjj","Delta R (Truth Quark 2, HCand)",160,-0.5,8);
   auto B1_Truth2WCandDeltaR_hist = new TH1F("t2wcdrttjj","Delta R (Truth Quark 2, WCand)",160,-0.5,8);
   auto B1_HCandWCandDeltaR_hist = new TH1F("hcwcdrttjj","Delta R (HCand, WCand)",160,-0.5,8);
   auto B1_TruthTagJet1Eta_hist = new TH1F("ttj1etattjj","Truth Tag Jet 1 Eta",160,-8,8);
   auto B1_TruthTagJet2Eta_hist = new TH1F("ttj2etattjj","Truth Tag Jet 2 Eta",160,-8,8);
   auto B1_WHjjMass_hist = new TH1F("whjjmttjj","WHjj Mass",160, 400, 7000);

   //Second Selection:
   auto S2_LeadingLargeRJet_hist = new TH1F("ljm2VVHjj","Leading Large R Jet Mass",160,20,150);
   auto S2_WCandPt_hist = new TH1F("wcpt2VVHjj","W Candidate Pt [GeV]",160,0,1000);
   auto S2_WCandEta_hist = new TH1F("wce2VVHjj","W Candidate Eta",160,-8,8);
   auto S2_WCandPhi_hist = new TH1F("wcphi2VVHjj","W Candidate Phi",160,-6,6);
   auto S2_WCandMass_hist = new TH1F("wcm2VVHjj","W Candidate Mass [GeV]",160,20,150);
   auto S2_HCandPt_hist = new TH1F("hcpt2VVHjj","H Candidate Pt [GeV]",160,0,1000);
   auto S2_HCandEta_hist = new TH1F("hce2VVHjj","H Candidate Eta",160,-8,8);
   auto S2_HCandPhi_hist = new TH1F("hcphi2VVHjj","H Candidate Phi",160,-6,6);
   auto S2_HCandMass_hist = new TH1F("hcm2VVHjj","H Candidate Mass [GeV]",160,20,300);
   auto S2_TagJetDeltaEta_hist = new TH1F("tjde2VVHjj","Delta Eta (Tag Jet 1, Tag Jet 2)",160,-1,10);
   auto S2_TagJetsMass_hist = new TH1F("tjm2VVHjj","Mjj [GeV]",160,0,3500);
   auto S2_MWHjj_hist = new TH1F("whjjm2VVHjj","WHjj Mass [GeV]",160,400,7000);
   auto S2_Nbjets_hist = new TH1F("nbj2VVHjj","N b-Jets",8,-0.5,7.5);
   auto S2_bjetsmass_hist = new TH1F("bjm2VVHjj","b-Jets Mass [GeV]",160,0,150);
   auto S2_Truth1RecoDeltaR_hist = new TH1F("t1rdr2VVHjj","Delta R (Truth Jet 1, Reco Tag Jet)",160,-0.5,8);
   auto S2_Truth2RecoDeltaR_hist = new TH1F("t2rdr2VVHjj","Delta R (Truth Jet 2, Reco Tag Jet)",160,-0.5,8);
   auto S2_FirstLeptonPt_hist = new TH1F("flpt2VVHjj","Leading Lepton Pt [GeV]",160,0,1000);
   auto S2_MissingEt_hist = new TH1F("met2VVHjj","Missing Et [GeV]",160,-0.5,800);

   auto B2_LeadingLargeRJet_hist = new TH1F("ljm2ttjj","Leading Large R Jet Mass",160,20,150);
   auto B2_WCandPt_hist = new TH1F("wcpt2ttjj","W Candidate Pt [GeV]",160,0,1000);
   auto B2_WCandEta_hist = new TH1F("wce2ttjj","W Candidate Eta",160,-8,8);
   auto B2_WCandPhi_hist = new TH1F("wcphi2ttjj","W Candidate Phi",160,-6,6);
   auto B2_WCandMass_hist = new TH1F("wcm2ttjj","W Candidate Mass [GeV]",160,20,150);
   auto B2_HCandPt_hist = new TH1F("hcpt2ttjj","H Candidate Pt [GeV]",160,0,1000);
   auto B2_HCandEta_hist = new TH1F("hce2ttjj","H Candidate Eta",160,-8,8);
   auto B2_HCandPhi_hist = new TH1F("hcphi2ttjj","H Candidate Phi",160,-6,6);
   auto B2_HCandMass_hist = new TH1F("hcm2ttjj","H Candidate Mass [GeV]",160,20,300);
   auto B2_TagJetDeltaEta_hist = new TH1F("tjde2ttjj","Delta Eta (Tag Jet 1, Tag Jet 2)",160,-1,10);
   auto B2_TagJetsMass_hist = new TH1F("tjm2ttjj","Mjj [GeV]",160,0,3500);
   auto B2_MWHjj_hist = new TH1F("whjjm2ttjj","WHjj Mass [GeV]",160,400,7000);
   auto B2_Nbjets_hist = new TH1F("nbj2ttjj","N b-Jets",8,-0.5,7.5);
   auto B2_bjetsmass_hist = new TH1F("bjm2ttjj","b-Jets Mass [GeV]",160,0,150);
   auto B2_Truth1RecoDeltaR_hist = new TH1F("t1rdr2ttjj","Delta R (Truth Jet 1, Reco Tag Jet)",160,-0.5,8);
   auto B2_Truth2RecoDeltaR_hist = new TH1F("t2rdr2ttjj","Delta R (Truth Jet 2, Reco Tag Jet)",160,-0.5,8);
   auto B2_FirstLeptonPt_hist = new TH1F("flpt2ttjj","Leading Lepton Pt [GeV]",160,0,1000);
   auto B2_MissingEt_hist = new TH1F("met2ttjj","Missing Et [GeV]",160,-0.5,800);

   //No Selection:
   auto S_TruthQuark1MinDeltaR_hist = new TH1F("tq1mdrnsVVHjj","DeltaR(Truth Quark 1, Nearest Small R Jet)",160,-0.5,8);
   auto S_TruthQuark2MinDeltaR_hist = new TH1F("tq2mdrnsVVHjj","DeltaR(Truth Quark 2, Nearest Small R Jet)",160,-0.5,8);
   auto S_TruthTagJet1Pt_hist = new TH1F("ttj1ptnsVVHjj","Truth Tag Jet 1 Pt [GeV]",160,0,300);
   auto S_TruthTagJet1Eta_hist = new TH1F("ttj1etansVVHjj","Truth Tag Jet 1 Eta",160,-8,8);
   auto S_TruthTagJet1Phi_hist = new TH1F("ttj1phinsVVHjj","Truth Tag Jet 1 Phi",160,-4,4);
   auto S_TruthTagJet1Mass_hist = new TH1F("ttj1mnsVVHjj","Truth Tag Jet 1 Mass [GeV]",160,0,1000);
   auto S_TruthTagJet2Pt_hist = new TH1F("ttj2ptnsVVHjj","Truth Tag Jet 2 Pt [GeV]",160,0,300);
   auto S_TruthTagJet2Eta_hist = new TH1F("ttj2etansVVHjj","Truth Tag Jet 2 Eta",160,-8,8);
   auto S_TruthTagJet2Phi_hist = new TH1F("ttj2phinsVVHjj","Truth Tag Jet 2 Phi",160,-4,4);
   auto S_TruthTagJet2Mass_hist = new TH1F("ttj2mnsVVHjj","Truth Tag Jet 2 Mass [GeV]",160,0,1000);
   auto S_TruthQ1DeltaR_hist = new TH1F("tq1DRnsVVHjj", "Delta R(Trurth Quark 1, TruthJets)", 160 , -0.5, 8);
   auto S_TruthQ2DeltaR_hist = new TH1F("tq2DRnsVVHjj", "Delta R(Trurth Quark 2, TruthJets)", 160 , -0.5, 8);
   auto S_NTruthTagCandidates_hist = new TH1F("nttcnsVVHjj", "N Truth Tag Candidates", 6, -0.5, 5.5);
   auto S_TruthTagCandidatesPt_hist = new TH1F("ttcptnsVVHjj", "Truth Tag Candidates Pt [GeV]", 160, 0, 200);
   auto S_TruthTagCandidatesEta_hist = new TH1F("ttcetansVVHjj", "Truth Tag Candidates Eta", 6, -8, 8);
   auto S_LeadingFatJetPt_hist = new TH1F("ttcphinsVVHjj", "Leading Fat Jet Pt [GeV]", 160, 0, 1000);
   auto S_NFatJets_hist = new TH1F("nfjnsVVHjj", "N Large R Jets", 4, -0.5, 3.5);
   auto S_NLeptons_hist = new TH1F("nlnsVVHjj", "N Leptons", 6, -0.5, 5.5);

   auto B_LeadingFatJetPt_hist = new TH1F("ttcphinsttjj", "Leading Fat Jet Pt [GeV]", 160, 0, 1000);
   auto B_NFatJets_hist = new TH1F("nfjnsttjj", "N Large R Jets", 4, -0.5, 3.5);
   auto B_NLeptons_hist = new TH1F("nlnsttjj", "N Leptons", 6, -0.5, 5.5);
 
   //Optimized cuts histograms (for Boosted selection):
   //Float_t bins_C[] = {500, 700, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200, 3300, 3400, 3500, 3600, 3700, 3800, 3900, 4000, 5000};
   Float_t bins_C[] = {500, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200, 3300, 3400, 3500, 4000, 5000};
   auto SC_TagJetsMass_hist = new TH1F("tjmcttjj","Tag Jets Mass [GeV]",160,70,6000);
   auto SC_TagJetDeltaEta_hist = new TH1F("tjdecVVHjj","Delta Eta (Tag Jet 1, Tag Jet 2)",160,4,10);
   //auto SC_MWHjj_hist = new TH1F("whjjmcVVHjj","WHjj Mass", 160, 300, 5000);
   auto SC_MWHjj_hist = new TH1F("whjjmcVVHjj","WHjj Mass [GeV]", 29, bins_C);
   //auto SC_FirstLeptonPt_hist = new TH1F("flptcVVHjj","First Lepton Pt", 160, 0, 1000);

   auto BC_TagJetsMass_hist = new TH1F("tjmcVVHjj","Tag Jets Mass [GeV]",160,70,6000);
   auto BC_TagJetDeltaEta_hist = new TH1F("tjdecttjj","Delta Eta (Tag Jet 1, Tag Jet 2)",160,4,10);
   //auto BC_MWHjj_hist = new TH1F("whjjmcttjj","WHjj Mass", 160, 300, 5000);
   auto BC_MWHjj_hist = new TH1F("whjjmcttjj","WHjj Mass [GeV]", 29, bins_C);
   //auto BC_FirstLeptonPt_hist = new TH1F("flptcttjj","First Lepton Pt", 160, 0, 1000);


   //Optimized cuts histograms (for Hybrid selection):
   Float_t bins_C2[] = {500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200, 3300, 3400, 3500, 3600, 3700, 3800, 3900, 4000, 4100, 4200, 4300, 4400, 4500, 4600, 4700, 5000};
   //auto SC2_MWHjj_hist = new TH1F("whjjmc2VVHjj","WHjj Mass", 160, 0, 5000);
   auto SC2_MWHjj_hist = new TH1F("whjjmc2VVHjj","WHjj Mass [GeV]", 43, bins_C2);

   //auto BC2_MWHjj_hist = new TH1F("whjjmc2ttjj","WHjj Mass", 160, 0, 5000);
   auto BC2_MWHjj_hist = new TH1F("whjjmc2ttjj","WHjj Mass [GeV]", 43, bins_C2);
   



   //Adding variable binning for the boosted selection as well:
   Float_t bins_1[] = {500, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200, 3300, 3400, 3500, 4000, 5000};
   //auto S1_WHjjMass_hist = new TH1F("whjjmVVHjj","WHjj Mass [GeV]",29, bins_1);
   //auto B1_WHjjMass_hist = new TH1F("whjjmttjj","WHjj Mass [GeV]",29, bins_1);

   //Correlation histograms
   auto S1_MWHjjMjjCorr_hist = new TH2F("Corr1", "Correlation (MWHjj - Mjj)", 160, -0.5, 6000, 160, -0.5, 6000);
   auto S1_MWHjjDeltaEtajjCorr_hist = new TH2F("Corr2", "Correlation (MWHjj - jj Delta Eta)", 160, -0.5, 6000, 160, 0, 10);
   auto S1_MjjDeltaEtajjCorr_hist = new TH2F("Corr3", "Correlation (Mjj - Delta Eta jj)", 160, -0.5, 6000, 160, 0, 10);

   //Tree
   TTreeReader myReader_V("myTree", VVHjj);
   TTreeReaderValue<Float_t> SNlep(myReader_V, "nleptons");
   TTreeReaderValue<Float_t> Slpt(myReader_V, "leptonpt");
   TTreeReaderValue<Float_t> SMet(myReader_V, "MissingEt");
   TTreeReaderValue<Float_t> SNel(myReader_V, "nelectrons");
   TTreeReaderValue<vector<Float_t>> SelPt(myReader_V, "electronpt");
   TTreeReaderValue<vector<Float_t>> Seleta(myReader_V, "electroneta");
   TTreeReaderValue<vector<Float_t>> Selphi(myReader_V, "electronphi");
   TTreeReaderValue<vector<Float_t>> Seliso(myReader_V, "electroniso");
   TTreeReaderValue<Float_t> SNmu(myReader_V, "nmuons");
   TTreeReaderValue<vector<Float_t>> SmuPt(myReader_V, "muonpt");
   TTreeReaderValue<vector<Float_t>> Smueta(myReader_V, "muoneta");
   TTreeReaderValue<vector<Float_t>> Smuphi(myReader_V, "muonphi");
   TTreeReaderValue<vector<Float_t>> Smuiso(myReader_V, "muoniso");
   TTreeReaderValue<vector<Float_t>> Sfatjetpt(myReader_V, "fatjetspt");
   TTreeReaderValue<vector<Float_t>> Sfatjeteta(myReader_V, "fatjetseta");
   TTreeReaderValue<vector<Float_t>> Sfatjetphi(myReader_V, "fatjetsphi");
   TTreeReaderValue<vector<Float_t>> Sfatjetmass(myReader_V, "fatjetsmass");
   TTreeReaderValue<Float_t> SNjets(myReader_V, "nsmallRjets");
   TTreeReaderValue<vector<Float_t>> Sjetpt(myReader_V, "smallRjetspt");
   TTreeReaderValue<vector<Float_t>> Sjeteta(myReader_V, "smallRjetseta");
   TTreeReaderValue<vector<Float_t>> Sjetphi(myReader_V, "smallRjetsphi");
   TTreeReaderValue<vector<Float_t>> Sjetmass(myReader_V, "smallRjetsmass");
   TTreeReaderValue<Float_t> Stagjet1pt(myReader_V, "tagjet1pt");
   TTreeReaderValue<Float_t> Stagjet1eta(myReader_V, "tagjet1eta");
   TTreeReaderValue<Float_t> Stagjet1phi(myReader_V, "tagjet1phi");
   TTreeReaderValue<Float_t> Stagjet1mass(myReader_V, "tagjet1mass");
   TTreeReaderValue<Float_t> Stagjet2pt(myReader_V, "tagjet2pt");
   TTreeReaderValue<Float_t> Stagjet2eta(myReader_V, "tagjet2eta");
   TTreeReaderValue<Float_t> Stagjet2phi(myReader_V, "tagjet2phi");
   TTreeReaderValue<Float_t> Stagjet2mass(myReader_V, "tagjet2mass");
   TTreeReaderValue<vector<Float_t>> StruthparticlePID(myReader_V, "truthparticlesPID");
   TTreeReaderValue<vector<Float_t>> StruthparticleStatus(myReader_V, "truthparticlesStatus");
   TTreeReaderValue<vector<Float_t>> StruthparticleM1(myReader_V, "truthparticlesM1");
   TTreeReaderValue<vector<Float_t>> StruthparticleM2(myReader_V, "truthparticlesM2");
   TTreeReaderValue<vector<Float_t>> StruthparticleD1(myReader_V, "truthparticlesD1");
   TTreeReaderValue<vector<Float_t>> StruthparticleD2(myReader_V, "truthparticlesD2");
   TTreeReaderValue<vector<Float_t>> Struthparticlept(myReader_V, "truthparticlespt");
   TTreeReaderValue<vector<Float_t>> Struthparticleeta(myReader_V, "truthparticleseta");
   TTreeReaderValue<vector<Float_t>> Struthparticlephi(myReader_V, "truthparticlesphi");
   TTreeReaderValue<vector<Float_t>> Struthparticlemass(myReader_V, "truthparticlesmass");
   TTreeReaderValue<vector<Float_t>> Struthjetpt(myReader_V, "truthjetspt");
   TTreeReaderValue<vector<Float_t>> Struthjeteta(myReader_V, "truthjetseta");
   TTreeReaderValue<vector<Float_t>> Struthjetphi(myReader_V, "truthjetsphi");
   TTreeReaderValue<vector<Float_t>> Struthjetmass(myReader_V, "truthjetsmass");
   TTreeReaderValue<vector<int>> Sjetflavor(myReader_V, "jets_flavor");
   TTreeReaderValue<vector<float>> Signal_weight(myReader_V, "weights_event_tree");

   Double_t Signal = 0.;
   Double_t Signal_events_generated = 0.;
   Double_t Signal_events_FatJets_selection = 0.;
   Double_t Signal_events_Nlepton_selection = 0.;
   Double_t Signal_events_TagJets_selection = 0.;
   Double_t Signal_events_HCand_selection = 0.;
   Double_t Signal_events_selected = 0.;

   Double_t S_Tot = 0.;
   Double_t S_Sel = 0.;

   int Signal_Total = 0;
   int Signal1_FatandLep = 0;
   int Signal1_HCandStep = 0;
   int Signal1_FirstTagJetStep = 0;
   int Signal1_SecondTagJetStep = 0;
   int Check_eff_Signal = 0;

   int Signal2_FatandLep = 0;
   int Signal2_HCandStep = 0;
   int Signal2_FirstTagJetStep = 0;
   int Signal2_SecondTagJetStep = 0;
   //Counting events with truth tag jets:
   int Total_events = 0;
   int TagJet_events = 0;

   //TMVA tree:
   TFile *VVHjj_TMVA = new TFile("signalTree.root", "RECREATE", "VVHjj_TMVA");
   TTree *signalTree = new TTree("myTree","A ROOT tree");
   TTree *signalTree2 = new TTree("myTree2","A ROOT tree");
   Float_t MWHjj1_Stree = 0.;
   Float_t Mjj1_Stree = 0.;
   Float_t DeltaEta1_Stree = 0.;
   Float_t LeadingFatJetPt1_Stree = 0.;
   Float_t SubleadingFatJetPt1_Stree = 0.;
   Float_t MissingEt1_Stree = 0.;
   Float_t FirstLeptonPt1_Stree = 0.;
   Float_t WCandMass1_Stree = 0.;
   Float_t MWHjj2_Stree = 0.;
   Float_t Mjj2_Stree = 0.;
   Float_t DeltaEta2_Stree = 0.;
   Float_t HCandPt2_Stree = 0.;
   Float_t WCandPt2_Stree = 0.;
   Float_t MissingEt2_Stree = 0.;
   Float_t FirstLeptonPt2_Stree = 0.;
   Float_t WCandMass2_Stree = 0.;
   Float_t HCandMass2_Stree = 0.;
   Float_t HCandEta2_Stree = 0.;
   signalTree->Branch("MWHjj1", &MWHjj1_Stree);
   signalTree->Branch("LeadingFatJetPt1", &LeadingFatJetPt1_Stree);
   signalTree->Branch("SubleadingFatJetPt1", &SubleadingFatJetPt1_Stree);
   signalTree->Branch("MissingEt1", &MissingEt1_Stree);
   signalTree->Branch("Mjj1", &Mjj1_Stree);
   signalTree->Branch("FirstLeptonPt1", &FirstLeptonPt1_Stree);
   signalTree->Branch("WCandMass1", &WCandMass1_Stree);
   signalTree->Branch("DeltaEta1", &DeltaEta1_Stree);
   signalTree2->Branch("MWHjj2", &MWHjj2_Stree);
   signalTree2->Branch("HCandPt2", &HCandPt2_Stree);
   signalTree2->Branch("WCandPt2", &WCandPt2_Stree);
   signalTree2->Branch("MissingEt2", &MissingEt2_Stree);
   signalTree2->Branch("Mjj2", &Mjj2_Stree);
   signalTree2->Branch("FirstLeptonPt2", &FirstLeptonPt2_Stree);
   signalTree2->Branch("WCandMass2", &WCandMass2_Stree);
   signalTree2->Branch("HCandMass2", &HCandMass2_Stree);
   signalTree2->Branch("DeltaEta2", &DeltaEta2_Stree);
   signalTree2->Branch("HCandEta2", &HCandEta2_Stree);
   
   //Float_t BoostedMWHjjCuts_STree = 0.;
   //Float_t HybridMWHjjCuts_STree = 0.;
   //TTree *signalHybridCutsTree = new TTree("hybridTree", "A ROOT tree");
   //signalHybridCutsTree ->Branch("HybridMWHjjCuts", &HybridMWHjjCuts_STree); 
   //TTree *signalBoostedCutsTree = new TTree("boostedTree", "A ROOT tree");
   //signalBoostedCutsTree ->Branch("BoostedMWHjjCuts", &BoostedMWHjjCuts_STree);

   while (myReader_V.Next()) {
    bool S_Hybrid_bool = false;
    bool S_Boosted_bool = false;
    if((*Signal_weight)[0]<0) continue;
    Signal_events_generated += (*Signal_weight)[0];
    //Measuring total efficiency:
    S_Tot ++;
    Signal_Total ++;

    //Jets: 
    vector<TLorentzVector> FatJets;
    vector<TLorentzVector> SmallRJets;
    vector<TLorentzVector> TruthJets;
    vector<TLorentzVector> HCands;
    vector<TLorentzVector> SignalJets;
    vector<TLorentzVector> TruthTag_candidates;
    TLorentzVector HCand;
    TLorentzVector WCand;
    TLorentzVector HCand_M;
    TLorentzVector WCand_M;
    TLorentzVector FatJet;
    TLorentzVector LeadingFatJet;
    TLorentzVector SubleadingFatJet;
    TLorentzVector TagJet1;
    TLorentzVector TagJet2;
    TLorentzVector sigJet1;
    TLorentzVector sigJet2;
    TLorentzVector TruthQuark1;
    TLorentzVector TruthQuark2;
    TLorentzVector TruthTagJet1;
    TLorentzVector TruthTagJet2;

    //Picking Truth Quarks
    int nIj1 = -1;
    for(int i =0; i < (*StruthparticleStatus).size(); i++){
     if((*StruthparticleStatus)[i] != 21) continue;
     nIj1 = i;
     if (nIj1 != -1) break;
    }
    int nTruthQuark1 = -1;
    for(int j = 0; j < (*StruthparticleStatus).size(); j++){
     if((*StruthparticleStatus)[j] != 23) continue;
     if((*StruthparticlePID)[j] >= 6) continue;
     nTruthQuark1 = j;
     if(nTruthQuark1 != -1) break;
    }
    int nIj2 = -1;
    for(int i =0; i < (*StruthparticleStatus).size(); i++){
     if((*StruthparticleStatus)[i] != 21) continue;
     if(i == nIj1) continue;
     nIj2 = i;
     if (nIj2 != -1) break;
    }
    int nTruthQuark2 = -1;
    for(int j = 0; j < (*StruthparticleStatus).size(); j++){
     if((*StruthparticleStatus)[j] != 23) continue;
     if((*StruthparticlePID)[j] >= 6) continue;
     if(j == nTruthQuark1) continue;
     nTruthQuark2 = j;
     if(nTruthQuark2 != -1) break;
    }
    TruthQuark1.SetPtEtaPhiM((*Struthparticlept)[nTruthQuark1],(*Struthparticleeta)[nTruthQuark1],(*Struthparticlephi)[nTruthQuark1],(*Struthparticlemass)[nTruthQuark1]);
    TruthQuark2.SetPtEtaPhiM((*Struthparticlept)[nTruthQuark2],(*Struthparticleeta)[nTruthQuark2],(*Struthparticlephi)[nTruthQuark2],(*Struthparticlemass)[nTruthQuark2]);
    if(nTruthQuark1 == -1 || nTruthQuark2 == -1) continue;
    
    //Truth jets:
    for(int i = 0; i < (*Struthjetpt).size(); i++){
     TLorentzVector TruthJet;
     TruthJet.SetPtEtaPhiM((*Struthjetpt)[i],(*Struthjeteta)[i],(*Struthjetphi)[i],(*Struthjetmass)[i]);
     TruthJets.push_back(TruthJet);
    }
    
    //Truth Tag Jets:
    Double_t DeltaRQ1 = 99.;
    Double_t DeltaRQ2 = 99.;
    for(int i = 0; i < (*Struthjetpt).size(); i++){
     Double_t temp_DeltaRQ1 = TruthQuark1.DeltaR(TruthJets[i]);
     Double_t temp_DeltaRQ2 = TruthQuark2.DeltaR(TruthJets[i]);
     if(temp_DeltaRQ1<DeltaRQ1) DeltaRQ1 = temp_DeltaRQ1;
     if(temp_DeltaRQ2<DeltaRQ2) DeltaRQ2 = temp_DeltaRQ2;
     if(TruthQuark1.DeltaR(TruthJets[i]) < 0.4||  TruthQuark2.DeltaR(TruthJets[i]) < 0.4){
      TruthTag_candidates.push_back(TruthJets[i]);
     }
     if(TruthQuark1.DeltaR(TruthJets[i]) < 0.4){
      TruthTagJet1 = TruthJets[i];
     }
     if(TruthQuark2.DeltaR(TruthJets[i]) < 0.4){
      TruthTagJet2 = TruthJets[i];
     }
    }
    if(TruthTagJet1.Pt() != 0 && TruthTagJet2.Pt() != 0){
     TagJet_events ++;
     S_TruthTagJet1Pt_hist -> Fill(TruthTagJet1.Pt(), (*Signal_weight)[0]*Scale_S);
     S_TruthTagJet1Eta_hist -> Fill(TruthTagJet1.Eta(), (*Signal_weight)[0]*Scale_S);
     S_TruthTagJet1Phi_hist -> Fill(TruthTagJet1.Phi(), (*Signal_weight)[0]*Scale_S);
     S_TruthTagJet1Mass_hist -> Fill(TruthTagJet1.M(), (*Signal_weight)[0]*Scale_S);
     S_TruthTagJet2Pt_hist -> Fill(TruthTagJet2.Pt(), (*Signal_weight)[0]*Scale_S);
     S_TruthTagJet2Eta_hist -> Fill(TruthTagJet2.Eta(), (*Signal_weight)[0]*Scale_S);
     S_TruthTagJet2Phi_hist -> Fill(TruthTagJet2.Phi(), (*Signal_weight)[0]*Scale_S);
     S_TruthTagJet2Mass_hist -> Fill(TruthTagJet2.M(), (*Signal_weight)[0]*Scale_S);
     S_NTruthTagCandidates_hist -> Fill(TruthTag_candidates.size(), (*Signal_weight)[0]*Scale_S);
    }
    S_TruthQ1DeltaR_hist -> Fill(DeltaRQ1, (*Signal_weight)[0]*Scale_S);
    S_TruthQ2DeltaR_hist -> Fill(DeltaRQ2, (*Signal_weight)[0]*Scale_S);
    //for(int i = 0; i < TruthTag_candidates.size())
    
    //Fat Jets
    for(int i = 0; i < (*Sfatjetpt).size(); i++){
     FatJet.SetPtEtaPhiM((*Sfatjetpt)[i],(*Sfatjeteta)[i],(*Sfatjetphi)[i],(*Sfatjetmass)[i]);
     if(FatJet.M() < 30) continue; //Fat jet mass cut
     if(FatJet.Pt()<200) continue; //Fat jet Pt cut
     FatJets.push_back(FatJet);
    }
    if(FatJets.size()>0){
     LeadingFatJet = FatJets[0];
    }
    if(FatJets.size()>1){ 
     SubleadingFatJet = FatJets[1];
    }
    float FatJetDeltaEta = LeadingFatJet.Eta()-SubleadingFatJet.Eta();
    Signal_events_FatJets_selection += (*Signal_weight)[0];

    //SmallRJets
    int NSmallRJets = 0;
    int NbJets = 0;

    if(*SNjets > 0){
     for(int j =0; j < *SNjets ; j++){
      TLorentzVector SmallRJet;
      SmallRJet.SetPtEtaPhiM((*Sjetpt)[j],(*Sjeteta)[j],(*Sjetphi)[j],(*Sjetmass)[j]);
      if(SmallRJet.Pt() > 20){
       NSmallRJets ++;
       if((*Sjetflavor)[j] == 5) NbJets ++;
       SmallRJets.push_back(SmallRJet);
      }
     }
    }

    //Leptons:
    vector<TLorentzVector> leptons;
    vector<TLorentzVector> electrons;
    vector<TLorentzVector> muons;

    //electrons
    for(int i = 0; i<(*SelPt).size(); i++){
     TLorentzVector electron;
     electron.SetPtEtaPhiM((*SelPt)[i], (*Seleta)[i], (*Selphi)[i], 0.5/1000);
     electrons.push_back(electron);
     leptons.push_back(electron);
    }
      
    //muons
    for(int i = 0; i<(*SmuPt).size(); i++){
     TLorentzVector muon;
     muon.SetPtEtaPhiM((*SmuPt)[i], (*Smueta)[i], (*Smuphi)[i], 105/1000);
     muons.push_back(muon);
     leptons.push_back(muon);
    }
    
    std::sort(leptons.begin(),leptons.end(), reorderTLorentz);

    //Minimum Delta R distribution between Quarks and SmallRJets:
    Double_t MinDR_Q1 = 99.;
    Double_t MinDR_Q2 = 99.;
    for(int i = 0; i < SmallRJets.size(); i++){
     if(TruthQuark1.DeltaR(SmallRJets[i]) < MinDR_Q1) MinDR_Q1 = TruthQuark1.DeltaR(SmallRJets[i]);
    }
    for(int i = 0; i < SmallRJets.size(); i++){
     if(TruthQuark2.DeltaR(SmallRJets[i]) < MinDR_Q2) MinDR_Q2 = TruthQuark2.DeltaR(SmallRJets[i]);
    }
    
    //No Selections plots:
    S_TruthQuark1MinDeltaR_hist -> Fill(MinDR_Q1, (*Signal_weight)[0]*Scale_S);
    S_TruthQuark2MinDeltaR_hist -> Fill(MinDR_Q2, (*Signal_weight)[0]*Scale_S);
    if(LeadingFatJet.Pt() != 0){
     S_LeadingFatJetPt_hist -> Fill(LeadingFatJet.Pt(), No_W_Scale_S);
    }
    S_NFatJets_hist -> Fill(FatJets.size(), No_W_Scale_S);
    S_NLeptons_hist -> Fill(leptons.size(), No_W_Scale_S);

    //Picking SignalJets:
    if (SmallRJets.size() > 2){
     const float M_W   = 80.385  ; //GeV
     float minDiff = 1000;
     int nJet1 = -1, nJet2 = -1;
 
     for ( size_t iJet = 0; iJet < SmallRJets.size(); iJet++){
      for ( size_t jJet = 0; jJet < SmallRJets.size(); jJet++){
       if (iJet == jJet) continue;
       TLorentzVector VHadCandVec = SmallRJets[iJet] + SmallRJets[jJet];
       float diff_W = TMath::Abs( VHadCandVec.M() - M_W );
       if (diff_W < minDiff){
        minDiff = diff_W;
        nJet1 = iJet;
        nJet2 = jJet;
       }
      }
     }
     if (nJet1 != -1 && nJet2 != -1){
      if( SmallRJets[nJet1].Pt() < SmallRJets[nJet2].Pt() ){
       int nJet_temp = nJet1;
       nJet1 = nJet2;
       nJet2 = nJet_temp;
      }
     }
     if (nJet1 != -1 && nJet2 != -1){
      //   vhadres.SetVec(smallRJets.at(nJet1) -> p4() * 1e-3 + smallRJets.at(nJet2) -> p4() * 1e-3);
      sigJet1.SetPtEtaPhiM(SmallRJets[nJet1].Pt(),SmallRJets[nJet1].Eta(),SmallRJets[nJet1].Phi(),SmallRJets[nJet1].M());
      sigJet2.SetPtEtaPhiM(SmallRJets[nJet2].Pt(),SmallRJets[nJet2].Eta(),SmallRJets[nJet2].Phi(),SmallRJets[nJet2].M());
      SignalJets.push_back(sigJet1);
      SignalJets.push_back(sigJet2);
     } 
    }

    //First Selection:
    if(*SNlep >= 1 && FatJets.size() > 1){
     Signal_events_Nlepton_selection += (*Signal_weight)[0]; 
     Signal1_FatandLep ++;
     //H Candidates and mass selections:  
     for(int k= 0; k < FatJets.size(); k++){
      int NFatbJets = 0;
      if(SmallRJets.size()>0){
       for(int i=0; i < SmallRJets.size(); i++){
        if(SmallRJets[i].Pt()<20) continue;
        if(FatJets[k].DeltaR(SmallRJets[i]) > 1.0) continue;
        if((*Sjetflavor)[i] != 5) continue;
        NFatbJets ++;
       }
      }
      if(NFatbJets == 2){
       HCands.push_back(FatJets[k]);
      }
     }
        
     //Pick H and W candidates:  
     if(HCands.size() > 0){
      if(HCands.size() == 1){
       HCand = HCands[0];
      }
      if(HCands.size() > 1){
       std::sort(HCands.begin(),HCands.end(), reorderTLorentz);
       HCand = HCands[0];
      }
      if(HCand == FatJets[0]){
       WCand = FatJets[1];
      } else{
         WCand = FatJets[0];
        }
     }

     if(HCand.M()<70 || HCand.M()>140 || WCand.M() == 0){
      S_Hybrid_bool = true;
      goto S_Hybrid; //continue; //HCand mass selection //HERE
     }
     Signal_events_HCand_selection += (*Signal_weight)[0];
     Signal1_HCandStep ++;

     //Pick the pair of SmallRJets that reconstruct the H and W mass:
     Double_t min_MassDif_H = 1000.;
     int nSmallH1 = -1;
     int nSmallH2 = -1;
     if(SmallRJets.size() > 0){
      for(int i = 0; i< SmallRJets.size(); i++){
       if(SmallRJets[i].DeltaR(HCand)>1.0) continue;
       for(int j = 0; j < SmallRJets.size(); j++){
        if(j==i) continue;
        if(SmallRJets[j].DeltaR(HCand)>1.0) continue;
        Double_t Mjj = (SmallRJets[i] + SmallRJets[j]).M();
        if(abs(125-Mjj)< min_MassDif_H){
         min_MassDif_H = abs(125-Mjj);
         nSmallH1 = i;
         nSmallH2 = j;
        }
       }
      }
     }
     Double_t min_MassDif_W = 1000.;
     int nSmallW1 = -1;
     int nSmallW2 = -1;
     if(SmallRJets.size() > 0){
      for(int i = 0; i< SmallRJets.size(); i++){
       if(SmallRJets[i].DeltaR(WCand)>1.0) continue;
       for(int j = 0; j < SmallRJets.size(); j++){
        if(j==i) continue;
        if(SmallRJets[j].DeltaR(WCand)>1.0) continue;
        Double_t Mjj = (SmallRJets[i] + SmallRJets[j]).M();
        if(abs(80.385-Mjj)< min_MassDif_W){
         min_MassDif_W = abs(80.385-Mjj);
         nSmallW1 = i;
         nSmallW2 = j;
        }
       }
      }
     }
     if(nSmallW1 == -1 || nSmallW2 == -1){
      for(int j = 0; j < SmallRJets.size(); j++){
       if(SmallRJets[j].DeltaR(WCand)>1.0) continue;
       nSmallW1 = j;
      }
     }

     //Pick Tag Jets myself:
     //First, select posible Tag Jets candidates:
     //Test, only removing the ones inside H or W candidates:
     vector<TLorentzVector> Tag_candidates;
     vector<TLorentzVector> SmallRJets_Inside;
     if(SmallRJets.size()> 0){
      for(int i = 0; i < SmallRJets.size(); i++){
       bool elegible = true;
       //if(HCand.DeltaR(SmallRJets[i])< 1.0) elegible = false;
       //if(WCand.DeltaR(SmallRJets[i]) < 1.0) elegible = false;
       if(i==nSmallW1||i==nSmallW2||i==nSmallH1||i==nSmallH2) elegible = false;
       if(elegible) Tag_candidates.push_back(SmallRJets[i]);
       if(!elegible) SmallRJets_Inside.push_back(SmallRJets[i]);
      }
     }
     std::sort(SmallRJets_Inside.begin(),SmallRJets_Inside.end(), reorderTLorentz);
     if(SmallRJets.size()> 0){
      int EventswTagJets = 0;
      if(Tag_candidates.size() > 1) EventswTagJets = 2;
      S1_EventswTagJets_hist -> Fill(EventswTagJets,  (*Signal_weight)[0]*Scale_S);
     }
     S1_NTagCandidates_hist -> Fill(Tag_candidates.size(),(*Signal_weight)[0]*Scale_S);
     S1_NSmallRJetsInside_hist ->Fill(SmallRJets_Inside.size(), (*Signal_weight)[0]*Scale_S);
     if(Tag_candidates.size() < 2){
      S_Hybrid_bool = true;
      goto S_Hybrid; //continue; //HERE
     }
     Signal1_FirstTagJetStep ++;

     //Pick TagJets as the ones with greater mass and different eta signs
     if (Tag_candidates.size() >= 2){ 
      double mJJ = 0.;
      int nTagJet1 = -1;
      int nTagJet2 = -1;

      for ( size_t iJet = 0; iJet < Tag_candidates.size(); iJet++){
       for ( size_t jJet = 0; jJet < Tag_candidates.size(); jJet++){
        if (iJet == jJet) continue;
        double j1pt= Tag_candidates[iJet].Pt();
        double j2pt= Tag_candidates[jJet].Pt();
        if(j1pt<j2pt){
         double tmpj1pt=j1pt;
         j1pt=j2pt;
         j2pt=tmpj1pt;
        }

        if (!(Tag_candidates[iJet].Eta()*Tag_candidates[jJet].Eta() < 0)) continue;
        TLorentzVector DijetCandVec = Tag_candidates[iJet] + Tag_candidates[jJet];
        if (DijetCandVec.M() > mJJ){
         mJJ = DijetCandVec.M();
         nTagJet1 = iJet;
         nTagJet2 = jJet;
        }
       }
      }
      if (nTagJet1 != -1 && nTagJet2 != -1){
       if( Tag_candidates[nTagJet1].Pt() < Tag_candidates[nTagJet2].Pt() ){
        int nTagJet_temp = nTagJet1;
        nTagJet1 = nTagJet2;
        nTagJet2 = nTagJet_temp;
       }
      }
      bool bool_TagInsideFat = false;
      for(int i = 0; i < FatJets.size(); i ++){
       if(Tag_candidates[nTagJet1].DeltaR(FatJets[i]) < 1.0) bool_TagInsideFat = true;      
       if(Tag_candidates[nTagJet2].DeltaR(FatJets[i]) < 1.0) bool_TagInsideFat = true;      
      }
      if (mJJ != 0){
       TagJet1.SetPtEtaPhiM(Tag_candidates[nTagJet1].Pt(),Tag_candidates[nTagJet1].Eta(),Tag_candidates[nTagJet1].Phi(),Tag_candidates[nTagJet1].M());
       TagJet2.SetPtEtaPhiM(Tag_candidates[nTagJet2].Pt(),Tag_candidates[nTagJet2].Eta(),Tag_candidates[nTagJet2].Phi(),Tag_candidates[nTagJet2].M());
      }
     }
     if(TagJet1.Pt() < 20 || TagJet2.Pt() < 20){
      S_Hybrid_bool = true;
      goto S_Hybrid; //continue; //HERE
     }
     Signal1_SecondTagJetStep ++;

     Signal_events_TagJets_selection += (*Signal_weight)[0];

     //Measuring total efficiency:
     S_Sel ++;

     //Looking at Reco Tag Jets wrongly picked
     vector<TLorentzVector> WrongTagJets;
     Double_t Truth1RecoDeltaR = TruthQuark1.DeltaR(TagJet1);
     if(TruthQuark1.DeltaR(TagJet2) < TruthQuark1.DeltaR(TagJet1)) Truth1RecoDeltaR = TruthQuark1.DeltaR(TagJet2);
     Double_t Truth2RecoDeltaR = TruthQuark2.DeltaR(TagJet1);
     if(TruthQuark2.DeltaR(TagJet2) < TruthQuark2.DeltaR(TagJet1)) Truth2RecoDeltaR = TruthQuark2.DeltaR(TagJet2);
     if(Truth1RecoDeltaR > 0.5){
      if(TruthQuark1.DeltaR(TagJet1) < TruthQuark1.DeltaR(TagJet2)) WrongTagJets.push_back(TagJet1); 
      if(TruthQuark1.DeltaR(TagJet2) < TruthQuark1.DeltaR(TagJet1)) WrongTagJets.push_back(TagJet2);
     } 
     if(Truth2RecoDeltaR > 0.5){
      if(TruthQuark2.DeltaR(TagJet1) < TruthQuark2.DeltaR(TagJet2)) WrongTagJets.push_back(TagJet1); 
      if(TruthQuark2.DeltaR(TagJet2) < TruthQuark2.DeltaR(TagJet1)) WrongTagJets.push_back(TagJet2);
     } 

     //Nbjets fatjet1 and fatjet2:
     int Nbjetsleading = 0;
     int Nbjetssubleading = 0;
     if(SmallRJets.size()> 0){
      for(int idx = 0; idx < SmallRJets.size(); idx++){
       if(LeadingFatJet.DeltaR(SmallRJets[idx])<1.0){
        if((*Sjetflavor)[idx] == 5) Nbjetsleading++;
       }
       if(SubleadingFatJet.DeltaR(SmallRJets[idx])<1.0){
        if((*Sjetflavor)[idx] == 5) Nbjetssubleading++;
       }
      }
     }
 
     //Fill bjets N histograms and Fatjets mass:
     int NFatJetsw2bjets = 0;
     for(int k= 0; k < FatJets.size(); k++){
      S1_FatJetMass_hist -> Fill(FatJets[k].M(), (*Signal_weight)[0]*Scale_S);
      int NFatbJets = 0;
      if(SmallRJets.size()>0){
       for(int i=0; i < SmallRJets.size(); i++){
        if(SmallRJets[i].Pt()<20) continue;
        if(FatJets[k].DeltaR(SmallRJets[i]) > 1.2) continue;
        if((*Sjetflavor)[i] != 5) continue;
        NFatbJets ++; 
       }
      }
      if(NFatbJets == 2){
       NFatJetsw2bjets++;
      }
      S1_NFatbJets_hist -> Fill(NFatbJets,(*Signal_weight)[0]*Scale_S);
     }
    
     //Fill H and W candidates histogram:
     if(HCands.size() > 0){
      S1_HCandMass_hist -> Fill(HCand.M(),(*Signal_weight)[0]*Scale_S);
      S1_HCandPt_hist -> Fill(HCand.Pt(),(*Signal_weight)[0]*Scale_S);
      S1_HCandEta_hist -> Fill(HCand.Eta(),(*Signal_weight)[0]*Scale_S);
      S1_HCandPhi_hist -> Fill(HCand.Phi(),(*Signal_weight)[0]*Scale_S);
      S1_WCandMass_hist -> Fill(WCand.M(),(*Signal_weight)[0]*Scale_S);
      S1_WCandPt_hist -> Fill(WCand.Pt(),(*Signal_weight)[0]*Scale_S);
      S1_WCandEta_hist -> Fill(WCand.Eta(),(*Signal_weight)[0]*Scale_S);
      S1_WCandPhi_hist -> Fill(WCand.Phi(),(*Signal_weight)[0]*Scale_S);
     }
     if(HCands.size() > 0){
      for(int i =0; i < HCands.size(); i++){
       S1_FatJets2bJetsMass_hist -> Fill(HCands[i].M(), (*Signal_weight)[0]*Scale_S);
      }
     }
    
     //Fill Tag Jets Histograms:
     S1_TagJetDeltaEta_hist ->Fill(abs(TagJet1.Eta()-TagJet2.Eta()), (*Signal_weight)[0]*Scale_S);
    
     //Fill Mjj and MHWjj histograms and fill TMVA tree:
     S1_TagJetsMass_hist ->Fill( (TagJet1+TagJet2).M(), No_W_Scale_S);
     Mjj1_Stree = (TagJet1+TagJet2).M();
     DeltaEta1_Stree = abs(TagJet1.Eta()-TagJet2.Eta());
     LeadingFatJetPt1_Stree = LeadingFatJet.Pt();
     SubleadingFatJetPt1_Stree = SubleadingFatJet.Pt();
     MissingEt1_Stree = *SMet;
     FirstLeptonPt1_Stree = leptons[0].Pt();
     WCandMass1_Stree = WCand.M();
     MWHjj1_Stree = (TagJet1+TagJet2+HCand+WCand).M();
     signalTree -> Fill();
     S1_WHjjMass_hist ->Fill((TagJet1+TagJet2+HCand+WCand).M(),  No_W_Scale_S);
     S1_MWHjjMjjCorr_hist -> Fill((TagJet1+TagJet2+HCand+WCand).M(), (TagJet1+TagJet2).M(), No_W_Scale_S);
     S1_MWHjjDeltaEtajjCorr_hist -> Fill((TagJet1+TagJet2+HCand+WCand).M(), abs(TagJet1.Eta()-TagJet2.Eta()), No_W_Scale_S);
     S1_MjjDeltaEtajjCorr_hist -> Fill((TagJet1+TagJet2).M(), abs(TagJet1.Eta()-TagJet2.Eta()), No_W_Scale_S);

     //Fill N histograms
     S1_NbJetsLeadingFatJet_hist -> Fill(Nbjetsleading,(*Signal_weight)[0]*Scale_S );
     S1_NbJetsSubleadingFatJet_hist ->Fill(Nbjetssubleading,(*Signal_weight)[0]*Scale_S);
     S1_NFatJetsw2bjets_hist -> Fill(NFatJetsw2bjets, (*Signal_weight)[0]*Scale_S);
     S1_NSmallRJets_hist -> Fill(NSmallRJets,(*Signal_weight)[0]*Scale_S);
     S1_NbJets_hist -> Fill(NbJets,(*Signal_weight)[0]*Scale_S);
     S1_Nelectrons_hist -> Fill(*SNel,(*Signal_weight)[0]*Scale_S);
     S1_Nmuons_hist -> Fill(*SNmu,(*Signal_weight)[0]*Scale_S);
     S1_NFatJets_hist -> Fill(FatJets.size(),(*Signal_weight)[0]*Scale_S);
     bool bool_DeltaEtaNeg = false;
     if(Tag_candidates.size() == 2){
      if (Tag_candidates[0].Eta()*Tag_candidates[1].Eta() < 0) bool_DeltaEtaNeg = true;
     }
     int DeltaEtaNeg = 0;
     if(bool_DeltaEtaNeg) DeltaEtaNeg = 1;
     S1_DeltaEtaNeg_hist ->Fill(DeltaEtaNeg, (*Signal_weight)[0]*Scale_S);
     int NTagJets = 0;
     if(*Stagjet1pt > 20) NTagJets ++;
     if(*Stagjet2pt > 20) NTagJets ++;
     S1_NTagJets_hist -> Fill(NTagJets, (*Signal_weight)[0]*Scale_S);
     
     //Fill Pt, Eta and Mass histograms:
     S1_FatJetDeltaEta_hist -> Fill(FatJetDeltaEta, (*Signal_weight)[0]*Scale_S);
     S1_LeadingFatJetPt_hist ->Fill(LeadingFatJet.Pt(), (*Signal_weight)[0]*Scale_S);
     S1_SubleadingFatJetPt_hist -> Fill(SubleadingFatJet.Pt(), (*Signal_weight)[0]*Scale_S);
     S1_MissingEt_hist -> Fill(*SMet , (*Signal_weight)[0]*Scale_S);
     S1_Nleptons_hist -> Fill(leptons.size() , (*Signal_weight)[0]*Scale_S);
     S1_LeadingFatJetMass_hist -> Fill(LeadingFatJet.M(), (*Signal_weight)[0]*Scale_S);
     S1_SubleadingFatJetMass_hist -> Fill(SubleadingFatJet.M(), (*Signal_weight)[0]*Scale_S);
     if(leptons.size()>1) S1_SecondLeptonPt_hist -> Fill(leptons[1].Pt() , (*Signal_weight)[0]*Scale_S);
     if(SmallRJets.size()>0){
      for(int i =0;i < SmallRJets.size(); i++) S1_SmallRJetsPt_hist -> Fill(SmallRJets[i].Pt() , (*Signal_weight)[0]*Scale_S);
      for(int i =0;i < SmallRJets.size(); i++) S1_SmallRJetsEta_hist -> Fill(SmallRJets[i].Eta() , (*Signal_weight)[0]*Scale_S);
     }
     S1_TruthQuark1Eta_hist -> Fill(TruthQuark1.Eta(), (*Signal_weight)[0]*Scale_S);
     S1_TruthQuark2Eta_hist -> Fill(TruthQuark2.Eta(), (*Signal_weight)[0]*Scale_S);
     S1_TagJet1Pt_hist -> Fill(TagJet1.Pt(), (*Signal_weight)[0]*Scale_S);
     S1_TagJet1Eta_hist -> Fill(TagJet1.Eta(), (*Signal_weight)[0]*Scale_S);
     S1_TagJet1Phi_hist -> Fill(TagJet1.Phi(), (*Signal_weight)[0]*Scale_S);
     S1_TagJet2Pt_hist -> Fill(TagJet2.Pt(), (*Signal_weight)[0]*Scale_S);
     S1_TagJet2Eta_hist -> Fill(TagJet2.Eta(), (*Signal_weight)[0]*Scale_S);
     S1_TagJet2Phi_hist -> Fill(TagJet2.Phi(), (*Signal_weight)[0]*Scale_S);
     if(TruthTagJet1.Eta() != 0){
      S1_TruthTagJet1Eta_hist -> Fill(TruthTagJet1.Eta(), (*Signal_weight)[0]*Scale_S);
     }
     if(TruthTagJet2.Eta() != 0){
      S1_TruthTagJet2Eta_hist -> Fill(TruthTagJet2.Eta(), (*Signal_weight)[0]*Scale_S);
     }
     S1_FirstLeptonPt_hist -> Fill(leptons[0].Pt(), No_W_Scale_S);

     //DeltaR:
     for(int i = 0; i<SmallRJets.size(); i++){
      float LFatJetSRJetDeltaR = LeadingFatJet.DeltaR(SmallRJets[i]);
      float SFatJetSRJetDeltaR = SubleadingFatJet.DeltaR(SmallRJets[i]);
      S1_LFatJetSRJetDeltaR_hist -> Fill(LFatJetSRJetDeltaR,(*Signal_weight)[0]*Scale_S);
      S1_SFatJetSRJetDeltaR_hist -> Fill(SFatJetSRJetDeltaR,(*Signal_weight)[0]*Scale_S);
     }
     vector<float> LeptonDeltaR;
     if(SmallRJets.size()>0){
      for(int j=0; j < SmallRJets.size(); j++){
       LeptonDeltaR.push_back(leptons[1].DeltaR(SmallRJets[j]));
      //S1_LeptonDeltaR_hist ->Fill(leptons[i].DeltaR(SmallRJets[j]),(*Signal_weight)[0]*Scale_S);
     }
     S1_LeptonDeltaR_hist ->Fill(*min_element(LeptonDeltaR.begin(), LeptonDeltaR.end()),(*Signal_weight)[0]*Scale_S);
     }
 
     S1_TagJet1HCandDeltaR_hist -> Fill(TagJet1.DeltaR(HCand), (*Signal_weight)[0]*Scale_S);
     S1_TagJet1WCandDeltaR_hist -> Fill(TagJet1.DeltaR(WCand), (*Signal_weight)[0]*Scale_S);
     S1_TagJet2HCandDeltaR_hist -> Fill(TagJet2.DeltaR(HCand), (*Signal_weight)[0]*Scale_S);
     S1_TagJet2WCandDeltaR_hist -> Fill(TagJet2.DeltaR(WCand), (*Signal_weight)[0]*Scale_S);

     //Tag Jets matching efficiency:
     Double_t MinTrue1RecoTag_DeltaR = TruthTagJet1.DeltaR(TagJet1);
     if(TruthTagJet1.DeltaR(TagJet2) < MinTrue1RecoTag_DeltaR) MinTrue1RecoTag_DeltaR = TruthTagJet1.DeltaR(TagJet2);
     S1_Truth1RecoDeltaR_hist -> Fill(MinTrue1RecoTag_DeltaR,  (*Signal_weight)[0]*Scale_S);
     Double_t MinTrue2RecoTag_DeltaR = TruthTagJet2.DeltaR(TagJet1);
     if(TruthTagJet2.DeltaR(TagJet2) < MinTrue2RecoTag_DeltaR) MinTrue2RecoTag_DeltaR = TruthTagJet2.DeltaR(TagJet2);
     S1_Truth2RecoDeltaR_hist -> Fill(MinTrue2RecoTag_DeltaR,  (*Signal_weight)[0]*Scale_S); 


     //Leptons isolation:
     for(int i = 0; i < (*Seliso).size(); i++){
      S1_ElectronIso_hist ->Fill((*Seliso)[i], (*Signal_weight)[0]*Scale_S);
     }
    
     for(int i = 0; i < (*Smuiso).size(); i++){
      S1_MuonIso_hist ->Fill((*Smuiso)[i], (*Signal_weight)[0]*Scale_S);
     }

     //Fill Mass method candidates mass histograms:
     //std::sort(FatJets.begin(),FatJets.end(), reorder_by_mass);
     //HCand_M = FatJets[0];
     //WCand_M = FatJets[1];
     //S1_HCandMassMethod_hist -> Fill(HCand_M.M(),(*Signal_weight)[0]*Scale_S);
     //S1_WCandMassMethod_hist -> Fill(WCand_M.M(),(*Signal_weight)[0]*Scale_S);
    
     //Signal
     for(int i = 0; i < 60; i++){
      if( (TagJet1.Eta()-TagJet2.Eta()) < i/10.){
       Signals[i] += (*Signal_weight)[0];
      }
     }
     Signal_events_selected += (*Signal_weight)[0];
     
     //Optimized cuts:
     //if(abs(TagJet1.Eta()-TagJet2.Eta()) >  0.330459 && leptons[0].Pt() >  184.114 && LeadingFatJet.Pt() > 197.52){
     //if(abs(TagJet1.Eta()-TagJet2.Eta()) >  0.156399 && leptons[0].Pt() >  112.585 && WCand.M() < 442.791){
     if(abs(TagJet1.Eta()-TagJet2.Eta()) >   0.421087 && leptons[0].Pt() >  185.726 && WCand.M() <  211.418){
      SC_MWHjj_hist -> Fill((TagJet1+TagJet2+HCand+WCand).M() ,No_W_Scale_S);
      SC_TagJetsMass_hist ->Fill((TagJet1+TagJet2).M(), No_W_Scale_S);
      SC_TagJetDeltaEta_hist ->Fill(abs(TagJet1.Eta()-TagJet2.Eta()), No_W_Scale_S);
      //BoostedMWHjjCuts_STree = (WCand+HCand+TagJet1+TagJet2).M();
      //signalBoostedCutsTree -> Fill();
      //SC_FirstLeptonPt_hist ->Fill(leptons[0].Pt(), No_W_Scale_S);
     }   
     S_Boosted_bool = true;
    }
    //if(S_Boosted_bool) continue;
 
    //Here goes the second selection:
    S_Hybrid:
    if(*SNlep > 0 && FatJets.size() >= 1 && SignalJets.size() >= 2){
     Signal2_FatandLep ++;

     vector<TLorentzVector> Tag_candidates;
     vector<TLorentzVector> bJets;
     int N_Hybrid_bjets = 0;

     //HCand by Pt:
     //HCand = FatJets[0];
 
     //Picking H Cand with b-jets:
     if(SmallRJets.size()> 0){
      for(int i = 0; i < SmallRJets.size(); i++){
       if((*Sjetflavor)[i] == 5){
        bJets.push_back(SmallRJets[i]);
        N_Hybrid_bjets ++;
       }
      }
     }
     int nJet1 = -1, nJet2 = -1;
     if (bJets.size() > 1){
      const float M_H   = 125  ; //GeV
      float minDiff = 1000;
 
      for ( size_t iJet = 0; iJet < bJets.size(); iJet++){
       for ( size_t jJet = 0; jJet < bJets.size(); jJet++){
        if (iJet == jJet) continue;
        TLorentzVector HCandVec = bJets[iJet] + bJets[jJet];
        float diff_H = TMath::Abs( HCandVec.M() - M_H );
        if (diff_H < minDiff){
         minDiff = diff_H;
         nJet1 = iJet;
         nJet2 = jJet;
        }
       }
      }
      if (nJet1 != -1 && nJet2 != -1){
       if( bJets[nJet1].Pt() < bJets[nJet2].Pt() ){
        int nJet_temp = nJet1;
        nJet1 = nJet2;
        nJet2 = nJet_temp;
       }
      }
      if (nJet1 != -1 && nJet2 != -1){
       HCand = bJets[nJet1]+bJets[nJet2];
      }
     }else{
       if(SmallRJets.size() < 1) continue;
       const float M_H   = 125  ; //GeV
       float minDiff = 1000;
       for ( size_t iJet = 0; iJet < SmallRJets.size(); iJet++){
        for ( size_t jJet = 0; jJet < SmallRJets.size(); jJet++){
         if (iJet == jJet) continue;
         TLorentzVector HCandVec = SmallRJets[iJet] + SmallRJets[jJet];
         float diff_H = TMath::Abs( HCandVec.M() - M_H );
         if (diff_H < minDiff){
          minDiff = diff_H;
          nJet1 = iJet;
          nJet2 = jJet;
         }
        }
       }
       if (nJet1 != -1 && nJet2 != -1){
        if( SmallRJets[nJet1].Pt() < SmallRJets[nJet2].Pt() ){
         int nJet_temp = nJet1;
         nJet1 = nJet2;
         nJet2 = nJet_temp;
        }
       }
       if (nJet1 != -1 && nJet2 != -1){
        HCand = SmallRJets[nJet1]+SmallRJets[nJet2];
       }
     }  
     //WCand = SignalJets[0]+SignalJets[1];
     //Large jet outside the H:
     vector<TLorentzVector> WCandVec;
     if(bJets.size() > 1){
      for(int i = 0; i < FatJets.size(); i++){
       if(FatJets[i].DeltaR(bJets[nJet1]) > 1 && FatJets[i].DeltaR(bJets[nJet2]) > 1){
        WCandVec.push_back(FatJets[i]);
       }
      }
      if(WCandVec.size()>0) WCand = WCandVec[0];
     } else {
      for(int i = 0; i < FatJets.size(); i++){
       if(FatJets[i].DeltaR(SmallRJets[nJet1]) > 1 && FatJets[i].DeltaR(SmallRJets[nJet2]) > 1){
        WCandVec.push_back(FatJets[i]);
       }
      }
      if(WCandVec.size()>0) WCand = WCandVec[0];
     }

     //if(WCand.M() < 30 || HCand.M() > 135 || HCand.Pt() == 0) continue;
     if(WCand.M() < 30 || HCand.Pt() == 0) continue;
     Signal2_HCandStep ++;

     //Pick Tag Jets myself:
     //First, select posible Tag Jets candidates(outside fat jets):
     //Test, only discard small jets inside H and W candidates

     //Removing the W's jets:
     Double_t min_MassDif_W = 1000.;
     int nSmallW1 = -1;
     int nSmallW2 = -1;
     if(SmallRJets.size() > 0){
      for(int i = 0; i< SmallRJets.size(); i++){
       if(SmallRJets[i].DeltaR(WCand)>1.0) continue;
       for(int j = 0; j < SmallRJets.size(); j++){
        if(j==i) continue;
        if(SmallRJets[j].DeltaR(WCand)>1.0) continue;
        Double_t Mjj = (SmallRJets[i] + SmallRJets[j]).M();
        if(abs(80.385-Mjj)< min_MassDif_W){
         min_MassDif_W = abs(80.385-Mjj);
         nSmallW1 = i;
         nSmallW2 = j;
        }
       }
      }
     }
     //Removing H's jets:

     if(bJets.size() > 1){
      if(SmallRJets.size()> 0){
       for(int i = 0; i<SmallRJets.size(); i++){
        bool elegible = true;
        if(i==nSmallW1||i==nSmallW2||SmallRJets[i]==bJets[nJet1]||SmallRJets[i]==bJets[nJet2]) elegible = false;
        if(elegible) Tag_candidates.push_back(SmallRJets[i]);
       }
      }
     }else {
       if(SmallRJets.size()> 0){
       for(int i = 0; i<SmallRJets.size(); i++){
        bool elegible = true;
        if(i==nSmallW1||i==nSmallW2||SmallRJets[i]==SmallRJets[nJet1]||SmallRJets[i]==SmallRJets[nJet2]) elegible = false;
        if(elegible) Tag_candidates.push_back(SmallRJets[i]);
       }
      }
     }
     

     //Pick TagJets as the ones with greater mass and different eta signs
     if(Tag_candidates.size() < 2) continue;
     Signal2_FirstTagJetStep ++;
     if (Tag_candidates.size() >= 2){ 
      double mJJ = 0.;
      int nTagJet1 = -1;
      int nTagJet2 = -1;
      for ( size_t iJet = 0; iJet < Tag_candidates.size(); iJet++){
       for ( size_t jJet = 0; jJet < Tag_candidates.size(); jJet++){
        if (iJet == jJet) continue;
        double j1pt= Tag_candidates[iJet].Pt();
        double j2pt= Tag_candidates[jJet].Pt();
        if(j1pt<j2pt){
         double tmpj1pt=j1pt;
         j1pt=j2pt;
         j2pt=tmpj1pt;
        }
        if (!(Tag_candidates[iJet].Eta()*Tag_candidates[jJet].Eta() < 0)) continue;
        TLorentzVector DijetCandVec = Tag_candidates[iJet] + Tag_candidates[jJet];
        if (DijetCandVec.M() > mJJ){
         mJJ = DijetCandVec.M();
         nTagJet1 = iJet;
         nTagJet2 = jJet;
        }
       }
      }
      if (nTagJet1 != -1 && nTagJet2 != -1){
       if( Tag_candidates[nTagJet1].Pt() < Tag_candidates[nTagJet2].Pt() ){
        int nTagJet_temp = nTagJet1;
        nTagJet1 = nTagJet2;
        nTagJet2 = nTagJet_temp;
       }
      }
      bool bool_TagInsideFat = false;
      for(int i = 0; i < FatJets.size(); i ++){
       if(Tag_candidates[nTagJet1].DeltaR(FatJets[i]) < 1.0) bool_TagInsideFat = true;      
       if(Tag_candidates[nTagJet2].DeltaR(FatJets[i]) < 1.0) bool_TagInsideFat = true;      
      }
      if (mJJ != 0){
       TagJet1.SetPtEtaPhiM(Tag_candidates[nTagJet1].Pt(),Tag_candidates[nTagJet1].Eta(),Tag_candidates[nTagJet1].Phi(),Tag_candidates[nTagJet1].M());
       TagJet2.SetPtEtaPhiM(Tag_candidates[nTagJet2].Pt(),Tag_candidates[nTagJet2].Eta(),Tag_candidates[nTagJet2].Phi(),Tag_candidates[nTagJet2].M());
      }
     }
     if(TagJet1.Pt() < 20 || TagJet2.Pt() < 20) continue;
     Signal2_SecondTagJetStep ++;

     //Fill Tag Jets Histograms:
     S2_TagJetDeltaEta_hist ->Fill(abs(TagJet1.Eta()-TagJet2.Eta()), (*Signal_weight)[0]*Scale_S);
     S2_TagJetsMass_hist -> Fill((TagJet1 +TagJet2).M(), No_W_Scale_S);   
     
     //Fill histograms:
     S2_LeadingLargeRJet_hist -> Fill(FatJets[0].M(), (*Signal_weight)[0]*Scale_S);
     S2_WCandMass_hist -> Fill(WCand.M(), (*Signal_weight)[0]*Scale_S);
     S2_WCandPt_hist -> Fill(WCand.Pt(), (*Signal_weight)[0]*Scale_S);
     S2_WCandEta_hist -> Fill(WCand.Eta(), (*Signal_weight)[0]*Scale_S);
     S2_WCandPhi_hist -> Fill(WCand.Phi(), (*Signal_weight)[0]*Scale_S);
     S2_HCandMass_hist -> Fill(HCand.M(), No_W_Scale_S);
     S2_HCandPt_hist -> Fill(HCand.Pt(), No_W_Scale_S);
     S2_HCandEta_hist -> Fill(abs(HCand.Eta()), No_W_Scale_S);
     S2_HCandPhi_hist -> Fill(HCand.Phi(), No_W_Scale_S);
     S2_Nbjets_hist -> Fill(N_Hybrid_bjets,  No_W_Scale_S);
     S2_MWHjj_hist -> Fill((HCand+WCand+TagJet1+TagJet2).M(), No_W_Scale_S);
     S2_FirstLeptonPt_hist -> Fill(leptons[0].Pt(), No_W_Scale_S);
     S2_MissingEt_hist -> Fill(*SMet, No_W_Scale_S);
     if(bJets.size() > 0){
      for(int i = 0; i < bJets.size(); i++){
       S2_bjetsmass_hist -> Fill(bJets[i].M(), No_W_Scale_S);
      }
     }

     //Tag Jets matching efficiency:
     Double_t MinTrue1RecoTag_DeltaR = TruthTagJet1.DeltaR(TagJet1);
     if(TruthTagJet1.DeltaR(TagJet2) < MinTrue1RecoTag_DeltaR) MinTrue1RecoTag_DeltaR = TruthTagJet1.DeltaR(TagJet2);
     S2_Truth1RecoDeltaR_hist -> Fill(MinTrue1RecoTag_DeltaR,  (*Signal_weight)[0]*Scale_S);
     Double_t MinTrue2RecoTag_DeltaR = TruthTagJet2.DeltaR(TagJet1);
     if(TruthTagJet2.DeltaR(TagJet2) < MinTrue2RecoTag_DeltaR) MinTrue2RecoTag_DeltaR = TruthTagJet2.DeltaR(TagJet2);
     S2_Truth2RecoDeltaR_hist -> Fill(MinTrue2RecoTag_DeltaR,  (*Signal_weight)[0]*Scale_S); 

     //Fill Mjj and MHWjj histograms and fill TMVA tree:
     Mjj2_Stree = (TagJet1+TagJet2).M();
     DeltaEta2_Stree = abs(TagJet1.Eta()-TagJet2.Eta());
     HCandPt2_Stree = HCand.Pt();
     WCandPt2_Stree = WCand.Pt();
     MissingEt2_Stree = *SMet;
     FirstLeptonPt2_Stree = leptons[0].Pt();
     WCandMass2_Stree = WCand.M();
     HCandMass2_Stree = HCand.M();
     HCandEta2_Stree = abs(HCand.Eta());
     MWHjj2_Stree = (TagJet1+TagJet2+HCand+WCand).M();
     signalTree2 -> Fill();

     //Optimization cuts for Hybrid selection:
     if(abs(HCand.Eta()) < 7.36254 && WCand.M() < 125.467 && leptons[0].Pt() > 266.867){
     //if(HCand.Pt() > 24.5201 && HCand.Eta() <  5.32712 && leptons[0].Pt() > 289.376){
      SC2_MWHjj_hist -> Fill((TagJet1+TagJet2+HCand+WCand).M() , No_W_Scale_S);
      //SC2_TagJetsMass_hist ->Fill((TagJet1+TagJet2).M(), No_W_Scale_S);
      //SC2_TagJetDeltaEta_hist ->Fill(abs(TagJet1.Eta()-TagJet2.Eta()), No_W_Scale_S);
      //HybridMWHjjCuts_STree = (WCand+HCand+TagJet1+TagJet2).M();
      //signalBoostedCutsTree -> Fill();
      Check_eff_Signal ++;
     }
    }
   }
   //signalTree -> Write();
   //signalTree2 -> Write();
   VVHjj_TMVA -> Write();

   cout << "Total Events: " << S_Tot << endl;
   cout << "Events with truth tag jets: " << TagJet_events << endl;
   cout << "Efficiency : " << (double) TagJet_events/S_Tot << endl;
   
   TTreeReader myReader_t("myTree", ttjj);
   TTreeReaderValue<Float_t> BNlep(myReader_t, "nleptons");
   TTreeReaderValue<Float_t> Blpt(myReader_t, "leptonpt");
   TTreeReaderValue<Float_t> BMet(myReader_t, "MissingEt");
   TTreeReaderValue<Float_t> BNel(myReader_t, "nelectrons");
   TTreeReaderValue<vector<Float_t>> BelPt(myReader_t, "electronpt");
   TTreeReaderValue<vector<Float_t>> Beleta(myReader_t, "electroneta");
   TTreeReaderValue<vector<Float_t>> Belphi(myReader_t, "electronphi");
   TTreeReaderValue<vector<Float_t>> Beliso(myReader_t, "electroniso");
   TTreeReaderValue<Float_t> BNmu(myReader_t, "nmuons");
   TTreeReaderValue<vector<Float_t>> BmuPt(myReader_t, "muonpt");
   TTreeReaderValue<vector<Float_t>> Bmueta(myReader_t, "muoneta");
   TTreeReaderValue<vector<Float_t>> Bmuphi(myReader_t, "muonphi");
   TTreeReaderValue<vector<Float_t>> Bmuiso(myReader_t, "muoniso");
   TTreeReaderValue<vector<Float_t>> Bfatjetpt(myReader_t, "fatjetspt");
   TTreeReaderValue<vector<Float_t>> Bfatjeteta(myReader_t, "fatjetseta");
   TTreeReaderValue<vector<Float_t>> Bfatjetphi(myReader_t, "fatjetsphi");
   TTreeReaderValue<vector<Float_t>> Bfatjetmass(myReader_t, "fatjetsmass");
   TTreeReaderValue<Float_t> BNjets(myReader_t, "nsmallRjets");
   TTreeReaderValue<vector<Float_t>> Bjetpt(myReader_t, "smallRjetspt");
   TTreeReaderValue<vector<Float_t>> Bjeteta(myReader_t, "smallRjetseta");
   TTreeReaderValue<vector<Float_t>> Bjetphi(myReader_t, "smallRjetsphi");
   TTreeReaderValue<vector<Float_t>> Bjetmass(myReader_t, "smallRjetsmass");
   TTreeReaderValue<Float_t> Btagjet1pt(myReader_t, "tagjet1pt");
   TTreeReaderValue<Float_t> Btagjet1eta(myReader_t, "tagjet1eta");
   TTreeReaderValue<Float_t> Btagjet1phi(myReader_t, "tagjet1phi");
   TTreeReaderValue<Float_t> Btagjet1mass(myReader_t, "tagjet1mass");
   TTreeReaderValue<Float_t> Btagjet2pt(myReader_t, "tagjet2pt");
   TTreeReaderValue<Float_t> Btagjet2eta(myReader_t, "tagjet2eta");
   TTreeReaderValue<Float_t> Btagjet2phi(myReader_t, "tagjet2phi");
   TTreeReaderValue<Float_t> Btagjet2mass(myReader_t, "tagjet2mass");
   TTreeReaderValue<vector<Float_t>> BtruthparticlePID(myReader_t, "truthparticlesPID");
   TTreeReaderValue<vector<Float_t>> BtruthparticleStatus(myReader_t, "truthparticlesStatus");
   TTreeReaderValue<vector<Float_t>> BtruthparticleM1(myReader_t, "truthparticlesM1");
   TTreeReaderValue<vector<Float_t>> BtruthparticleM2(myReader_t, "truthparticlesM2");
   TTreeReaderValue<vector<Float_t>> BtruthparticleD1(myReader_t, "truthparticlesD1");
   TTreeReaderValue<vector<Float_t>> BtruthparticleD2(myReader_t, "truthparticlesD2");
   TTreeReaderValue<vector<Float_t>> Btruthparticlept(myReader_t, "truthparticlespt");
   TTreeReaderValue<vector<Float_t>> Btruthparticleeta(myReader_t, "truthparticleseta");
   TTreeReaderValue<vector<Float_t>> Btruthparticlephi(myReader_t, "truthparticlesphi");
   TTreeReaderValue<vector<Float_t>> Btruthparticlemass(myReader_t, "truthparticlesmass");
   TTreeReaderValue<vector<Float_t>> Btruthjetpt(myReader_t, "truthjetspt");
   TTreeReaderValue<vector<Float_t>> Btruthjeteta(myReader_t, "truthjetseta");
   TTreeReaderValue<vector<Float_t>> Btruthjetphi(myReader_t, "truthjetsphi");
   TTreeReaderValue<vector<Float_t>> Btruthjetmass(myReader_t, "truthjetsmass");
   TTreeReaderValue<vector<int>> Bjetflavor(myReader_t, "jets_flavor");
   TTreeReaderValue<vector<float>> Background_weight(myReader_t, "weights_event_tree");
   
   Double_t Background = 0.;
   Double_t Background_events_generated = 0;
   Double_t Background_events_FatJets_selection = 0.;
   Double_t Background_events_Nlepton_selection = 0.;
   Double_t Background_events_TagJets_selection = 0.;
   Double_t Background_events_HCand_selection = 0.;
   Double_t Background_events_selected = 0;

   int B_Tot = 0;
   int B_Sel = 0;

   int Bkgnd_Total = 0;
   int Bkgnd1_FatandLep = 0;
   int Bkgnd1_HCandStep = 0;
   int Bkgnd1_FirstTagJetStep = 0;
   int Bkgnd1_SecondTagJetStep = 0;
   int Check_eff_Background = 0;
 
   int Bkgnd2_FatandLep = 0;
   int Bkgnd2_HCandStep = 0;
   int Bkgnd2_FirstTagJetStep = 0;
   int Bkgnd2_SecondTagJetStep = 0;
   //TMVA root tree:
   TFile *ttjj_TMVA = new TFile("backgroundTree.root", "RECREATE", "ttjj_TMVA");
   TTree *backgroundTree = new TTree("myTree","A ROOT tree");
   TTree *backgroundTree2 = new TTree("myTree2","A ROOT tree");
   Float_t MWHjj1_Btree = 0.;
   Float_t Mjj1_Btree = 0.;
   Float_t DeltaEta1_Btree = 0.;
   Float_t LeadingFatJetPt1_Btree = 0.;
   Float_t SubleadingFatJetPt1_Btree = 0.;
   Float_t MissingEt1_Btree = 0.;
   Float_t FirstLeptonPt1_Btree = 0.;
   Float_t WCandMass1_Btree = 0.;
   Float_t MWHjj2_Btree = 0.;
   Float_t Mjj2_Btree = 0.;
   Float_t DeltaEta2_Btree = 0.;
   Float_t HCandPt2_Btree = 0.;
   Float_t WCandPt2_Btree = 0.;
   Float_t MissingEt2_Btree = 0.;
   Float_t FirstLeptonPt2_Btree = 0.;
   Float_t WCandMass2_Btree = 0.;
   Float_t HCandMass2_Btree = 0.;
   Float_t HCandEta2_Btree = 0.;
   backgroundTree->Branch("MWHjj1", &MWHjj1_Btree);
   backgroundTree->Branch("LeadingFatJetPt1", &LeadingFatJetPt1_Btree);
   backgroundTree->Branch("SubleadingFatJetPt1", &SubleadingFatJetPt1_Btree);
   backgroundTree->Branch("MissingEt1", &MissingEt1_Btree);
   backgroundTree->Branch("Mjj1", &Mjj1_Btree);
   backgroundTree->Branch("FirstLeptonPt1", &FirstLeptonPt1_Btree);
   backgroundTree->Branch("WCandMass1", &WCandMass1_Btree);
   backgroundTree->Branch("DeltaEta1", &DeltaEta1_Btree);
   backgroundTree2->Branch("MWHjj2", &MWHjj2_Btree);
   backgroundTree2->Branch("HCandPt2", &HCandPt2_Btree);
   backgroundTree2->Branch("WCandPt2", &WCandPt2_Btree);
   backgroundTree2->Branch("MissingEt2", &MissingEt2_Btree);
   backgroundTree2->Branch("Mjj2", &Mjj2_Btree);
   backgroundTree2->Branch("FirstLeptonPt2", &FirstLeptonPt2_Btree);
   backgroundTree2->Branch("WCandMass2", &WCandMass2_Btree);
   backgroundTree2->Branch("HCandMass2", &HCandMass2_Btree);
   backgroundTree2->Branch("DeltaEta2", &DeltaEta2_Btree);
   backgroundTree2->Branch("HCandEta2", &HCandEta2_Btree);

   //Float_t BoostedMWHjjCuts_BTree = 0.;
   //Float_t HybridMWHjjCuts_BTree = 0.;
   //TTree *backgroundHybridCutsTree = new TTree("hybridTree", "A ROOT tree");
   //backgroundHybridCutsTree ->Branch("HybridMWHjjCuts", &HybridMWHjjCuts_BTree); 
   //TTree *backgroundBoostedCutsTree = new TTree("boostedTree", "A ROOT tree");
   //backgroundBoostedCutsTree ->Branch("BoostedMWHjjCuts", &BoostedMWHjjCuts_BTree);

   while (myReader_t.Next()) {
    bool B_Hybrid_bool = false;
    bool B_Boosted_bool = false;
    if((*Background_weight)[0]<0) continue;
    Background_events_generated += (*Background_weight)[0];

    //Measuring total efficiency:
    B_Tot ++;
    Bkgnd_Total ++;

    //Jets:
    vector<TLorentzVector> FatJets;
    vector<TLorentzVector> SmallRJets;
    vector<TLorentzVector> TruthJets;
    vector<TLorentzVector> HCands;
    vector<TLorentzVector> SignalJets;
    vector<TLorentzVector> TruthTag_candidates;
    TLorentzVector HCand;
    TLorentzVector WCand;
    TLorentzVector HCand_M;
    TLorentzVector WCand_M;
    TLorentzVector FatJet;
    TLorentzVector LeadingFatJet;
    TLorentzVector SubleadingFatJet;
    TLorentzVector TagJet1;
    TLorentzVector TagJet2;
    TLorentzVector sigJet1;
    TLorentzVector sigJet2;
    TLorentzVector TruthQuark1;
    TLorentzVector TruthQuark2;
    TLorentzVector TruthTagJet1;
    TLorentzVector TruthTagJet2;

    //Picking Truth Quarks
    int nIj1 = -1;
    for(int i =0; i < (*BtruthparticleStatus).size(); i++){
     if((*BtruthparticleStatus)[i] != 21) continue;
     nIj1 = i;
     if (nIj1 != -1) break;
    }
    int nTruthQuark1 = -1;
    for(int j = 0; j < (*BtruthparticleStatus).size(); j++){
     if((*BtruthparticleStatus)[j] != 23) continue;
     if((*BtruthparticlePID)[j] >= 6) continue;
     nTruthQuark1 = j;
     if(nTruthQuark1 != -1) break;
    }
    int nIj2 = -1;
    for(int i =0; i < (*BtruthparticleStatus).size(); i++){
     if((*BtruthparticleStatus)[i] != 21) continue;
     if(i == nIj1) continue;
     nIj2 = i;
     if (nIj2 != -1) break;
    }
    int nTruthQuark2 = -1;
    for(int j = 0; j < (*BtruthparticleStatus).size(); j++){
     if((*BtruthparticleStatus)[j] != 23) continue;
     if((*BtruthparticlePID)[j] >= 6) continue;
     if(j == nTruthQuark1) continue;
     nTruthQuark2 = j;
     if(nTruthQuark2 != -1) break;
    }
    TruthQuark1.SetPtEtaPhiM((*Btruthparticlept)[nTruthQuark1],(*Btruthparticleeta)[nTruthQuark1],(*Btruthparticlephi)[nTruthQuark1],(*Btruthparticlemass)[nTruthQuark1]);
    TruthQuark2.SetPtEtaPhiM((*Btruthparticlept)[nTruthQuark2],(*Btruthparticleeta)[nTruthQuark2],(*Btruthparticlephi)[nTruthQuark2],(*Btruthparticlemass)[nTruthQuark2]);

    if(nTruthQuark1 == -1 || nTruthQuark2 == -1) continue;

    //Truth jets:
    for(int i = 0; i < (*Btruthjetpt).size(); i++){
     TLorentzVector TruthJet;
     TruthJet.SetPtEtaPhiM((*Btruthjetpt)[i],(*Btruthjeteta)[i],(*Btruthjetphi)[i],(*Btruthjetmass)[i]);
     TruthJets.push_back(TruthJet);
    }
    
    //Truth Tag Jets:
    Double_t DeltaRQ1 = 99.;
    Double_t DeltaRQ2 = 99.;
    for(int i = 0; i < (*Btruthjetpt).size(); i++){
     Double_t temp_DeltaRQ1 = TruthQuark1.DeltaR(TruthJets[i]);
     Double_t temp_DeltaRQ2 = TruthQuark2.DeltaR(TruthJets[i]);
     if(temp_DeltaRQ1<DeltaRQ1) DeltaRQ1 = temp_DeltaRQ1;
     if(temp_DeltaRQ2<DeltaRQ2) DeltaRQ2 = temp_DeltaRQ2;
     if(TruthQuark1.DeltaR(TruthJets[i]) < 0.4||  TruthQuark2.DeltaR(TruthJets[i]) < 0.4){
      TruthTag_candidates.push_back(TruthJets[i]);
     }
     if(TruthQuark1.DeltaR(TruthJets[i]) < 0.4){
      TruthTagJet1 = TruthJets[i];
     }
     if(TruthQuark2.DeltaR(TruthJets[i]) < 0.4){
      TruthTagJet2 = TruthJets[i];
     }
    }
    if(TruthTagJet1.Pt() != 0 && TruthTagJet2.Pt() != 0){
     TagJet_events ++;
    }

    //Fat Jets
    for(int i = 0; i < (*Bfatjetpt).size(); i++){
     FatJet.SetPtEtaPhiM((*Bfatjetpt)[i],(*Bfatjeteta)[i],(*Bfatjetphi)[i],(*Bfatjetmass)[i]);
     if(FatJet.M() < 30) continue; //Fat Jet Mass cut
     if(FatJet.Pt()<200) continue; //Fat Jet Pt cut
     FatJets.push_back(FatJet);
    }
    if(FatJets.size()>1){
     LeadingFatJet = FatJets[0];
     SubleadingFatJet = FatJets[1];
    }
    float FatJetDeltaEta = LeadingFatJet.Eta()-SubleadingFatJet.Eta();
    Background_events_FatJets_selection += (*Background_weight)[0];
    
    //SmallRJets:
    int NSmallRJets = 0;
    int NbJets = 0;

    if(*BNjets >0){
     for(int j =0; j < *BNjets ; j++){
      TLorentzVector SmallRJet;
      SmallRJet.SetPtEtaPhiM((*Bjetpt)[j],(*Bjeteta)[j],(*Bjetphi)[j],(*Bjetmass)[j]);
      if(SmallRJet.Pt() > 20){
       NSmallRJets ++;
       if((*Bjetflavor)[j] == 5) NbJets ++;
       SmallRJets.push_back(SmallRJet);
      }
     }
    }

    //Leptons:
    vector<TLorentzVector> leptons;
    vector<TLorentzVector> electrons;
    vector<TLorentzVector> muons;

    //electrons
    for(int i = 0; i<(*BelPt).size(); i++){
     TLorentzVector electron;
     electron.SetPtEtaPhiM((*BelPt)[i], (*Beleta)[i], (*Belphi)[i], 0.5/1000);
     electrons.push_back(electron);
     leptons.push_back(electron);
    }
    
    //muons
    for(int i = 0; i<(*BmuPt).size(); i++){
     TLorentzVector muon;
     muon.SetPtEtaPhiM((*BmuPt)[i], (*Bmueta)[i], (*Bmuphi)[i], 105/1000);
     leptons.push_back(muon);
     leptons.push_back(muon);
    }
    std::sort(leptons.begin(),leptons.end(), reorderTLorentz);
    
    //No Selection Plots:
    if(LeadingFatJet.Pt() != 0){
     B_LeadingFatJetPt_hist -> Fill(LeadingFatJet.Pt(), No_W_Scale_B);
    }
    B_NFatJets_hist -> Fill(FatJets.size(), No_W_Scale_B);
    B_NLeptons_hist -> Fill(leptons.size(), No_W_Scale_B);

    //Picking SignalJets:
    if (SmallRJets.size() > 2){
     const float M_W   = 80.385  ; //GeV
     float minDiff = 1000;
     int nJet1 = -1, nJet2 = -1;
 
     for ( size_t iJet = 0; iJet < SmallRJets.size(); iJet++){
      for ( size_t jJet = 0; jJet < SmallRJets.size(); jJet++){
        if (iJet == jJet) continue;
        TLorentzVector VHadCandVec = SmallRJets[iJet] + SmallRJets[jJet];
        float diff_W = TMath::Abs( VHadCandVec.M() - M_W );
        if (diff_W < minDiff){
         minDiff = diff_W;
         nJet1 = iJet;
         nJet2 = jJet;
       }
      }
     }
     if (nJet1 != -1 && nJet2 != -1){
      if( SmallRJets[nJet1].Pt() < SmallRJets[nJet2].Pt() ){
       int nJet_temp = nJet1;
       nJet1 = nJet2;
       nJet2 = nJet_temp;
      }
     }
     if (nJet1 != -1 && nJet2 != -1){
     //      vhadres.SetVec(smallRJets.at(nJet1) -> p4() * 1e-3 + smallRJets.at(nJet2) -> p4() * 1e-3);
      sigJet1.SetPtEtaPhiM(SmallRJets[nJet1].Pt(),SmallRJets[nJet1].Eta(),SmallRJets[nJet1].Phi(),SmallRJets[nJet1].M());
      sigJet2.SetPtEtaPhiM(SmallRJets[nJet2].Pt(),SmallRJets[nJet2].Eta(),SmallRJets[nJet2].Phi(),SmallRJets[nJet2].M());
      SignalJets.push_back(sigJet1);
      SignalJets.push_back(sigJet2);
     }
    } 

    //Firt Selection:
    if(*BNlep >= 1 && FatJets.size()>1){
     Background_events_Nlepton_selection += (*Background_weight)[0];
     Bkgnd1_FatandLep ++;
     //if(*Btagjet1pt < 20) continue;
     //if(*Btagjet2pt < 30) continue;

     //H Candidates and mass selections:
     for(int k= 0; k < FatJets.size(); k++){
      int NFatbJets = 0;
      if(SmallRJets.size()>0){
       for(int i=0; i < SmallRJets.size(); i++){
        if(SmallRJets[i].Pt()<20) continue;
        if(FatJets[k].DeltaR(SmallRJets[i]) > 1.0) continue;
        if((*Bjetflavor)[i] != 5) continue;
        NFatbJets ++;
       }
      }
      if(NFatbJets == 2){
       HCands.push_back(FatJets[k]);
      }
     }

     //Pick H and W candidates:
     if(HCands.size() > 0){
      if(HCands.size() == 1){
       HCand = HCands[0];
      }
      if(HCands.size() > 1){
       std::sort(HCands.begin(),HCands.end(), reorderTLorentz);
       HCand = HCands[0];
      }
       if(HCand == FatJets[0]){
        WCand = FatJets[1];
       } else{
          WCand = FatJets[0];
         }
     }

     if(HCand.M()<70 || HCand.M()>140 || WCand.M() == 0){
      B_Hybrid_bool = true;
      goto B_Hybrid; //continue; //HCand mass selection //HERE
     }
     Background_events_HCand_selection += (*Background_weight)[0];
     Bkgnd1_HCandStep ++;

     //Pick the pair of SmallRJets that reconstruct the H and W mass:
     Double_t min_MassDif_H = 1000.;
     int nSmallH1 = -1;
     int nSmallH2 = -1;
     if(SmallRJets.size() > 0){
      for(int i = 0; i< SmallRJets.size(); i++){
       if(SmallRJets[i].DeltaR(HCand)>1.0) continue;
       for(int j = 0; j < SmallRJets.size(); j++){
        if(j==i) continue;
        if(SmallRJets[j].DeltaR(HCand)>1.0) continue;
        Double_t Mjj = (SmallRJets[i] + SmallRJets[j]).M();
        if(abs(125-Mjj)< min_MassDif_H){
         min_MassDif_H = abs(125-Mjj);
         nSmallH1 = i;
         nSmallH2 = j;
        }
       }
      }
     }
     Double_t min_MassDif_W = 99.;
     int nSmallW1 = -1;
     int nSmallW2 = -1;
     if(SmallRJets.size() > 0){
      for(int i = 0; i< SmallRJets.size(); i++){
       if(SmallRJets[i].DeltaR(WCand)>1.0) continue;
       for(int j = 0; j < SmallRJets.size(); j++){
        if(j==i) continue;
        if(SmallRJets[j].DeltaR(WCand)>1.0) continue;
        Double_t Mjj = (SmallRJets[i] + SmallRJets[j]).M();
        if(abs(80.385-Mjj)< min_MassDif_W){
         min_MassDif_W = abs(80.385-Mjj);
         nSmallW1 = i;
         nSmallW2 = j;
        }
       }
      }
     }
     if(nSmallW1 == -1 || nSmallW2 == -1){
      for(int j = 0; j < SmallRJets.size(); j++){
       if(SmallRJets[j].DeltaR(WCand)>1.0) continue;
       nSmallW1 = j;
      }
     }

     //Pick Tag Jets myself:
     //First, select posible Tag Jets candidates(outside fat jets):
     //Test, only discard small jets inside H and W candidates
     vector<TLorentzVector> Tag_candidates;
     vector<TLorentzVector> SmallRJets_Inside;
     if(SmallRJets.size()> 0){
      for(int i = 0; i < SmallRJets.size(); i++){
       bool elegible = true;
       //if(SmallRJets[i].DeltaR(HCand) < 1.0) elegible = false;
       //if(SmallRJets[i].DeltaR(WCand) < 1.0) elegible = false;
       if(i==nSmallW1||i==nSmallW2||i==nSmallH1||i==nSmallH2) elegible = false;
       if(elegible) Tag_candidates.push_back(SmallRJets[i]);
       if(!elegible) SmallRJets_Inside.push_back(SmallRJets[i]);
      }
     }
     std::sort(SmallRJets_Inside.begin(),SmallRJets_Inside.end(), reorderTLorentz);
     if(SmallRJets.size()> 0){
      int EventswTagJets = 0;
      if(Tag_candidates.size() > 1) EventswTagJets = 2;
      B1_EventswTagJets_hist -> Fill(EventswTagJets,  (*Background_weight)[0]*Scale_B);
     }
     B1_NTagCandidates_hist -> Fill(Tag_candidates.size(),(*Background_weight)[0]*Scale_B);
     B1_NSmallRJetsInside_hist ->Fill(SmallRJets_Inside.size(), (*Background_weight)[0]*Scale_B);
     if(Tag_candidates.size() < 2){
      B_Hybrid_bool = true;
      goto B_Hybrid; //continue; //HERE
     }
     Bkgnd1_FirstTagJetStep ++;
     //Pick TagJets as the ones with greater mass and different eta signs
     if (Tag_candidates.size() >= 2){ 
      double mJJ = 0.;
      int nTagJet1 = -1;
      int nTagJet2 = -1;
      for ( size_t iJet = 0; iJet < Tag_candidates.size(); iJet++){
       for ( size_t jJet = 0; jJet < Tag_candidates.size(); jJet++){
        if (iJet == jJet) continue;
        double j1pt= Tag_candidates[iJet].Pt();
        double j2pt= Tag_candidates[jJet].Pt();
        if(j1pt<j2pt){
         double tmpj1pt=j1pt;
         j1pt=j2pt;
         j2pt=tmpj1pt;
        }

        if (!(Tag_candidates[iJet].Eta()*Tag_candidates[jJet].Eta() < 0)) continue;
        TLorentzVector DijetCandVec = Tag_candidates[iJet] + Tag_candidates[jJet];
        if (DijetCandVec.M() > mJJ){
         mJJ = DijetCandVec.M();
         nTagJet1 = iJet;
         nTagJet2 = jJet;
        }
       }
      }
      if (nTagJet1 != -1 && nTagJet2 != -1){
       if( Tag_candidates[nTagJet1].Pt() < Tag_candidates[nTagJet2].Pt() ){
        int nTagJet_temp = nTagJet1;
        nTagJet1 = nTagJet2;
        nTagJet2 = nTagJet_temp;
       }
      }
      bool bool_TagInsideFat = false;
      for(int i = 0; i < FatJets.size(); i ++){
       if(Tag_candidates[nTagJet1].DeltaR(FatJets[i]) < 1.0) bool_TagInsideFat = true;      
       if(Tag_candidates[nTagJet2].DeltaR(FatJets[i]) < 1.0) bool_TagInsideFat = true;      
      }
      if (mJJ != 0){
       TagJet1.SetPtEtaPhiM(Tag_candidates[nTagJet1].Pt(),Tag_candidates[nTagJet1].Eta(),Tag_candidates[nTagJet1].Phi(),Tag_candidates[nTagJet1].M());
       TagJet2.SetPtEtaPhiM(Tag_candidates[nTagJet2].Pt(),Tag_candidates[nTagJet2].Eta(),Tag_candidates[nTagJet2].Phi(),Tag_candidates[nTagJet2].M());
      }
     }
     if(TagJet1.Pt() < 20 || TagJet2.Pt() < 20){
      B_Hybrid_bool = true;
      goto B_Hybrid; //continue; //HERE
     }
     Bkgnd1_SecondTagJetStep ++;
 
     Background_events_TagJets_selection += (*Background_weight)[0];

     //Measuring total efficiency:
     B_Sel ++;

     //Looking at Reco Tag Jets wrongly picked
     vector<TLorentzVector> WrongTagJets;
     Double_t Truth1RecoDeltaR = TruthQuark1.DeltaR(TagJet1);
     if(TruthQuark1.DeltaR(TagJet2) < TruthQuark1.DeltaR(TagJet1)) Truth1RecoDeltaR = TruthQuark1.DeltaR(TagJet2);
     Double_t Truth2RecoDeltaR = TruthQuark2.DeltaR(TagJet1);
     if(TruthQuark2.DeltaR(TagJet2) < TruthQuark2.DeltaR(TagJet1)) Truth2RecoDeltaR = TruthQuark2.DeltaR(TagJet2);
     if(Truth1RecoDeltaR > 0.5){
      if(TruthQuark1.DeltaR(TagJet1) < TruthQuark1.DeltaR(TagJet2)) WrongTagJets.push_back(TagJet1); 
      if(TruthQuark1.DeltaR(TagJet2) < TruthQuark1.DeltaR(TagJet1)) WrongTagJets.push_back(TagJet2);
     } 
     if(Truth2RecoDeltaR > 0.5){
      if(TruthQuark2.DeltaR(TagJet1) < TruthQuark2.DeltaR(TagJet2)) WrongTagJets.push_back(TagJet1); 
      if(TruthQuark2.DeltaR(TagJet2) < TruthQuark2.DeltaR(TagJet1)) WrongTagJets.push_back(TagJet2);
     } 

     //Nbjets fatjet1 and fatjet2:
     int Nbjetsleading = 0;
     int Nbjetssubleading = 0;
     if(SmallRJets.size()> 0){
      for(int idx = 0; idx < SmallRJets.size(); idx++){
       if(LeadingFatJet.DeltaR(SmallRJets[idx]) < 1.0){
        if((*Bjetflavor)[idx] == 5) Nbjetsleading++;
       }
       if(SubleadingFatJet.DeltaR(SmallRJets[idx]) < 1.0){
        if((*Bjetflavor)[idx] == 5) Nbjetssubleading++;
       }
      }
     }

     //Fill bjets N histograms and Fatjet Mass:
     int NFatJetsw2bjets = 0;
     for(int k= 0; k < FatJets.size(); k++){
      B1_FatJetMass_hist -> Fill(FatJets[k].M(), (*Background_weight)[0]*Scale_B);
      int NFatbJets = 0;
      if(SmallRJets.size()>0){
       for(int i=0; i < SmallRJets.size(); i++){
        if(SmallRJets[i].Pt()<20) continue;
        if(FatJets[k].DeltaR(SmallRJets[i]) > 1.0) continue;
        if((*Bjetflavor)[i] != 5) continue;
        NFatbJets ++;
       }
      }
      if(NFatbJets == 2){
       NFatJetsw2bjets++;
      } 
      B1_NFatbJets_hist -> Fill(NFatbJets,(*Background_weight)[0]*Scale_B);
     }

     //Fill H and W candidates histograms:
     if(HCands.size() > 0){
      B1_HCandMass_hist -> Fill(HCand.M(),(*Background_weight)[0]*Scale_B);
      B1_HCandPt_hist -> Fill(HCand.Pt(),(*Background_weight)[0]*Scale_B);
      B1_HCandEta_hist -> Fill(HCand.Eta(),(*Background_weight)[0]*Scale_B);
      B1_HCandPhi_hist -> Fill(HCand.Phi(),(*Background_weight)[0]*Scale_B);
      B1_WCandMass_hist -> Fill(WCand.M(),(*Background_weight)[0]*Scale_B);
      B1_WCandPt_hist -> Fill(WCand.Pt(),(*Background_weight)[0]*Scale_B);
      B1_WCandEta_hist -> Fill(WCand.Eta(),(*Background_weight)[0]*Scale_B);
      B1_WCandPhi_hist -> Fill(WCand.Phi(),(*Background_weight)[0]*Scale_B);
     }
     if(HCands.size() > 0){
      for(int i =0; i < HCands.size(); i++){
       B1_FatJets2bJetsMass_hist -> Fill(HCands[i].M(), (*Background_weight)[0]*Scale_B);
      }
     }
 
     //Fill Tag Jets histograms:
     B1_TagJetDeltaEta_hist ->Fill(abs(TagJet1.Eta()-TagJet2.Eta()), (*Background_weight)[0]*Scale_B);
    
     //Fill Mjj and MHWjj histograms and fill TMVA Tree:
     B1_TagJetsMass_hist ->Fill((TagJet1+TagJet2).M(), No_W_Scale_B);
     DeltaEta1_Btree = abs(TagJet1.Eta()-TagJet2.Eta());
     Mjj1_Btree = (TagJet1+TagJet2).M();
     LeadingFatJetPt1_Btree = LeadingFatJet.Pt();
     SubleadingFatJetPt1_Btree = SubleadingFatJet.Pt();
     MissingEt1_Btree = *BMet;
     FirstLeptonPt1_Btree = leptons[0].Pt();
     WCandMass1_Btree = WCand.M();
     MWHjj1_Btree = (TagJet1+TagJet2+HCand+WCand).M();
     backgroundTree -> Fill(); 
     B1_WHjjMass_hist ->Fill((TagJet1+TagJet2+HCand+WCand).M(),No_W_Scale_B);
    
     //Fill N histograms
     B1_NFatJetsw2bjets_hist -> Fill(NFatJetsw2bjets, (*Background_weight)[0]*Scale_B);
     B1_NSmallRJets_hist -> Fill(NSmallRJets,(*Background_weight)[0]*Scale_B);
     B1_NbJets_hist -> Fill(NbJets,(*Background_weight)[0]*Scale_B);
     B1_Nelectrons_hist -> Fill(*BNel,(*Background_weight)[0]*Scale_B);
     B1_Nmuons_hist -> Fill(*BNmu,(*Background_weight)[0]*Scale_B);
     B1_NbJetsLeadingFatJet_hist -> Fill(Nbjetsleading,(*Background_weight)[0]*Scale_B);
     B1_NbJetsSubleadingFatJet_hist ->Fill(Nbjetssubleading,(*Background_weight)[0]*Scale_B);
     B1_NFatJets_hist -> Fill(FatJets.size(),(*Background_weight)[0]*Scale_B);
     bool bool_DeltaEtaNeg = false;
     if(Tag_candidates.size() == 2){
      if (Tag_candidates[0].Eta()*Tag_candidates[1].Eta() < 0) bool_DeltaEtaNeg = true;
     }
     int DeltaEtaNeg = 0;
     if(bool_DeltaEtaNeg) DeltaEtaNeg = 1;
     B1_DeltaEtaNeg_hist ->Fill(DeltaEtaNeg, (*Background_weight)[0]*Scale_B);
     int NTagJets = 0;
     if(*Btagjet1pt > 20) NTagJets ++;
     if(*Btagjet2pt > 20) NTagJets ++;
     B1_NTagJets_hist -> Fill(NTagJets, (*Background_weight)[0]*Scale_B);

     //Fill Pt, Eta and Mass histograms:
     B1_FatJetDeltaEta_hist -> Fill(FatJetDeltaEta, (*Background_weight)[0]*Scale_B);
     B1_LeadingFatJetPt_hist ->Fill(LeadingFatJet.Pt(), (*Background_weight)[0]*Scale_B);
     B1_SubleadingFatJetPt_hist -> Fill(SubleadingFatJet.Pt(), (*Background_weight)[0]*Scale_B);
     B1_MissingEt_hist -> Fill(*BMet , (*Background_weight)[0]*Scale_B);
     B1_Nleptons_hist -> Fill(leptons.size() , (*Background_weight)[0]*Scale_B);
     B1_LeadingFatJetMass_hist -> Fill(LeadingFatJet.M(), (*Background_weight)[0]*Scale_B);
     B1_SubleadingFatJetMass_hist -> Fill(SubleadingFatJet.M(), (*Background_weight)[0]*Scale_B);
     if(leptons.size() > 1) B1_SecondLeptonPt_hist -> Fill(leptons[1].Pt() , (*Background_weight)[0]*Scale_B);
     if(SmallRJets.size()>0){
      for(int i =0;i < SmallRJets.size(); i++) B1_SmallRJetsPt_hist -> Fill(SmallRJets[i].Pt() , (*Background_weight)[0]*Scale_B);
      for(int i =0;i < SmallRJets.size(); i++) B1_SmallRJetsEta_hist -> Fill(SmallRJets[i].Eta() , (*Background_weight)[0]*Scale_B);
     }
     B1_TruthQuark1Eta_hist -> Fill(TruthQuark1.Eta(), (*Background_weight)[0]*Scale_B);
     B1_TruthQuark2Eta_hist -> Fill(TruthQuark2.Eta(), (*Background_weight)[0]*Scale_B);
     B1_TagJet1Pt_hist -> Fill(TagJet1.Pt(), (*Background_weight)[0]*Scale_B);
     B1_TagJet1Eta_hist -> Fill(TagJet1.Eta(), (*Background_weight)[0]*Scale_B);
     B1_TagJet1Phi_hist -> Fill(TagJet1.Phi(), (*Background_weight)[0]*Scale_B);
     B1_TagJet2Pt_hist -> Fill(TagJet2.Pt(), (*Background_weight)[0]*Scale_B);
     B1_TagJet2Eta_hist -> Fill(TagJet2.Eta(), (*Background_weight)[0]*Scale_B);
     B1_TagJet2Phi_hist -> Fill(TagJet2.Phi(), (*Background_weight)[0]*Scale_B);
     if(TruthTagJet1.Eta() != 0){
      B1_TruthTagJet1Eta_hist -> Fill(TruthTagJet1.Eta(), (*Background_weight)[0]*Scale_B);
     }
     if(TruthTagJet2.Eta() != 0){
      B1_TruthTagJet2Eta_hist -> Fill(TruthTagJet2.Eta(), (*Background_weight)[0]*Scale_B);
     }
     B1_FirstLeptonPt_hist -> Fill(leptons[0].Pt(), No_W_Scale_B);

     //DeltaR:
     for(int i = 0; i< SmallRJets.size(); i++){
      float LFatJetSRJetDeltaR = LeadingFatJet.DeltaR(SmallRJets[i]);
      float SFatJetSRJetDeltaR = SubleadingFatJet.DeltaR(SmallRJets[i]);
      B1_LFatJetSRJetDeltaR_hist -> Fill(LFatJetSRJetDeltaR,(*Background_weight)[0]*Scale_B);
      B1_SFatJetSRJetDeltaR_hist -> Fill(SFatJetSRJetDeltaR,(*Background_weight)[0]*Scale_B);
     }
     vector<float> LeptonDeltaR;
     if(SmallRJets.size()>0){
      for(int j=0; j < SmallRJets.size(); j++){
       LeptonDeltaR.push_back(leptons[1].DeltaR(SmallRJets[j]));
      }
      B1_LeptonDeltaR_hist ->Fill(*min_element(LeptonDeltaR.begin(), LeptonDeltaR.end()),(*Background_weight)[0]*Scale_B);
     }
     B1_TagJet1HCandDeltaR_hist -> Fill(TagJet1.DeltaR(HCand), (*Background_weight)[0]*Scale_B);
     B1_TagJet1WCandDeltaR_hist -> Fill(TagJet1.DeltaR(WCand), (*Background_weight)[0]*Scale_B);
     B1_TagJet2HCandDeltaR_hist -> Fill(TagJet2.DeltaR(HCand), (*Background_weight)[0]*Scale_B);
     B1_TagJet2WCandDeltaR_hist -> Fill(TagJet2.DeltaR(WCand), (*Background_weight)[0]*Scale_B);
     
     //Tag Jets matching efficiency:
     Double_t MinTrue1RecoTag_DeltaR = TruthTagJet1.DeltaR(TagJet1);
     if(TruthTagJet1.DeltaR(TagJet2) < MinTrue1RecoTag_DeltaR) MinTrue1RecoTag_DeltaR = TruthTagJet1.DeltaR(TagJet2);
     B1_Truth1RecoDeltaR_hist -> Fill(MinTrue1RecoTag_DeltaR,  (*Background_weight)[0]*Scale_B);
     Double_t MinTrue2RecoTag_DeltaR = TruthTagJet2.DeltaR(TagJet1);
     if(TruthTagJet2.DeltaR(TagJet2) < MinTrue2RecoTag_DeltaR) MinTrue2RecoTag_DeltaR = TruthTagJet2.DeltaR(TagJet2);
     B1_Truth2RecoDeltaR_hist -> Fill(MinTrue2RecoTag_DeltaR,  (*Background_weight)[0]*Scale_B);
 
     //Lepton Isolation
     for(int i = 0; i < (*Beliso).size(); i++){
      B1_ElectronIso_hist ->Fill((*Beliso)[i], (*Background_weight)[0]*Scale_B);
     }
     for(int i = 0; i < (*Bmuiso).size(); i++){
      B1_MuonIso_hist ->Fill((*Bmuiso)[i], (*Background_weight)[0]*Scale_B);
     }
     //if(*Bnlep < 1 || *BlepPt < 30) continue;
   
     //Fill mass method candidates mass histograms:
     //std::sort(FatJets.begin(),FatJets.end(), reorder_by_mass);
     //HCand_M = FatJets[0];
     //WCand_M = FatJets[1];

     //B1_HCandMassMethod_hist -> Fill(HCand_M.M(),(*Background_weight)[0]*Scale_B);
     //B1_WCandMassMethod_hist -> Fill(WCand_M.M(),(*Background_weight)[0]*Scale_B);

     //Background
     for(int i = 0; i < 60; i++){
      if( (TagJet1.Eta()-TagJet2.Eta()) < i/10.){
       Backgrounds[i] += (*Background_weight)[0];
      }
     }
     Background_events_selected += (*Background_weight)[0];
 
     //Optimized cuts:
     //if(abs(TagJet1.Eta()-TagJet2.Eta()) >  0.330459 && leptons[0].Pt() >  184.114 && LeadingFatJet.Pt() > 197.52){
     //if(abs(TagJet1.Eta()-TagJet2.Eta()) >  0.156399 && leptons[0].Pt() >  112.585 && WCand.M() < 442.791){
     if(abs(TagJet1.Eta()-TagJet2.Eta()) >   0.421087 && leptons[0].Pt() >  185.726 && WCand.M() <  211.418){
      BC_MWHjj_hist -> Fill((TagJet1+TagJet2+HCand+WCand).M() , No_W_Scale_B);
      BC_TagJetsMass_hist ->Fill((TagJet1+TagJet2).M(), No_W_Scale_B);
      BC_TagJetDeltaEta_hist ->Fill(abs(TagJet1.Eta()-TagJet2.Eta()), No_W_Scale_B);
      //BoostedMWHjjCuts_BTree = (WCand+HCand+TagJet1+TagJet2).M();
      //backgroundBoostedCutsTree -> Fill();
      //BC_FirstLeptonPt_hist -> Fill(leptons[0].Pt(), No_W_Scale_B);
     }
     B_Boosted_bool = true;
    }
    if(B_Boosted_bool) continue; 
    //Here goes the second selection:
    B_Hybrid:
    if(*BNlep >0 && FatJets.size() >=1 && SignalJets.size() >= 2){
     Bkgnd2_FatandLep ++;

     vector<TLorentzVector> Tag_candidates;
     vector<TLorentzVector> bJets;
     int N_Hybrid_bjets = 0;

     //HCand by Pt:
     //HCand = FatJets[0];

     //Picking H Cand with b-jets:
     if(SmallRJets.size()> 0){
      for(int i = 0; i < SmallRJets.size(); i++){
       if((*Sjetflavor)[i] == 5){
        bJets.push_back(SmallRJets[i]);
        N_Hybrid_bjets ++;
       }
      }
     }
     int nJet1 = -1, nJet2 = -1;
     if (bJets.size() > 1){
      const float M_H   = 125  ; //GeV
      float minDiff = 1000;
 
      for ( size_t iJet = 0; iJet < bJets.size(); iJet++){
       for ( size_t jJet = 0; jJet < bJets.size(); jJet++){
        if (iJet == jJet) continue;
        TLorentzVector HCandVec = bJets[iJet] + bJets[jJet];
        float diff_H = TMath::Abs( HCandVec.M() - M_H );
        if (diff_H < minDiff){
         minDiff = diff_H;
         nJet1 = iJet;
         nJet2 = jJet;
        }
       }
      }
      if (nJet1 != -1 && nJet2 != -1){
       if( bJets[nJet1].Pt() < bJets[nJet2].Pt() ){
        int nJet_temp = nJet1;
        nJet1 = nJet2;
        nJet2 = nJet_temp;
       }
      }
      if (nJet1 != -1 && nJet2 != -1){
       HCand = bJets[nJet1]+bJets[nJet2];
      }
     }else{
       if(SmallRJets.size() < 1) continue;
       const float M_H   = 125  ; //GeV
       float minDiff = 1000;
       for ( size_t iJet = 0; iJet < SmallRJets.size(); iJet++){
        for ( size_t jJet = 0; jJet < SmallRJets.size(); jJet++){
         if (iJet == jJet) continue;
         TLorentzVector HCandVec = SmallRJets[iJet] + SmallRJets[jJet];
         float diff_H = TMath::Abs( HCandVec.M() - M_H );
         if (diff_H < minDiff){
          minDiff = diff_H;
          nJet1 = iJet;
          nJet2 = jJet;
         }
        }
       }
       if (nJet1 != -1 && nJet2 != -1){
        if( SmallRJets[nJet1].Pt() < SmallRJets[nJet2].Pt() ){
         int nJet_temp = nJet1;
         nJet1 = nJet2;
         nJet2 = nJet_temp;
        }
       }
       if (nJet1 != -1 && nJet2 != -1){
        HCand = SmallRJets[nJet1]+SmallRJets[nJet2];
       }
     } 
     //WCand = SignalJets[0]+SignalJets[1];
     //Large jet outside the H:
     vector<TLorentzVector> WCandVec;
     if(bJets.size() > 1){
      for(int i = 0; i < FatJets.size(); i++){
       if(FatJets[i].DeltaR(bJets[nJet1]) > 1 && FatJets[i].DeltaR(bJets[nJet2]) > 1){
        WCandVec.push_back(FatJets[i]);
       }
      }
      if(WCandVec.size()>0) WCand = WCandVec[0];
     }else {
       for(int i = 0; i < FatJets.size(); i++){
        if(FatJets[i].DeltaR(SmallRJets[nJet1]) > 1 && FatJets[i].DeltaR(SmallRJets[nJet2]) > 1){
         WCandVec.push_back(FatJets[i]);
        }
       }
       if(WCandVec.size()>0) WCand = WCandVec[0];
     }
     //if(WCand.M() < 30 || HCand.M() > 135 || HCand.Pt() == 0) continue;
     if(WCand.M() < 30 || HCand.Pt() == 0) continue;
     Bkgnd2_HCandStep ++;
     //Pick Tag Jets myself:
     //First, select posible Tag Jets candidates(outside fat jets):
     //Test, only discard small jets inside H and W candidates

     //Removing the W's jets:
     Double_t min_MassDif_W = 1000.;
     int nSmallW1 = -1;
     int nSmallW2 = -1;
     if(SmallRJets.size() > 0){
      for(int i = 0; i< SmallRJets.size(); i++){
       if(SmallRJets[i].DeltaR(WCand)>1.0) continue;
       for(int j = 0; j < SmallRJets.size(); j++){
        if(j==i) continue;
        if(SmallRJets[j].DeltaR(WCand)>1.0) continue;
        Double_t Mjj = (SmallRJets[i] + SmallRJets[j]).M();
        if(abs(80.385-Mjj)< min_MassDif_W){
         min_MassDif_W = abs(80.385-Mjj);
         nSmallW1 = i;
         nSmallW2 = j;
        }
       }
      }
     }
     //Removing H's jets:

     if(bJets.size() > 1){
      if(SmallRJets.size()> 0){
       for(int i = 0; i < SmallRJets.size(); i++){
        bool elegible = true;
        if(i==nSmallW1||i==nSmallW2||SmallRJets[i]==bJets[nJet1]||SmallRJets[i]==bJets[nJet2]) elegible = false;
        if(elegible) Tag_candidates.push_back(SmallRJets[i]);
       }
      }
     }else {
      if(SmallRJets.size()> 0){
       for(int i = 0; i < SmallRJets.size(); i++){
        bool elegible = true;
        if(i==nSmallW1||i==nSmallW2||SmallRJets[i]==SmallRJets[nJet1]||SmallRJets[i]==SmallRJets[nJet2]) elegible = false;
        if(elegible) Tag_candidates.push_back(SmallRJets[i]);
       }
      }
     }

     //Pick TagJets as the ones with greater mass and different eta signs
     if(Tag_candidates.size() < 2) continue;
     Bkgnd2_FirstTagJetStep ++;
     if (Tag_candidates.size() >= 2){ 
      double mJJ = 0.;
      int nTagJet1 = -1;
      int nTagJet2 = -1;
      for ( size_t iJet = 0; iJet < Tag_candidates.size(); iJet++){
       for ( size_t jJet = 0; jJet < Tag_candidates.size(); jJet++){
        if (iJet == jJet) continue;
        double j1pt= Tag_candidates[iJet].Pt();
        double j2pt= Tag_candidates[jJet].Pt();
        if(j1pt<j2pt){
         double tmpj1pt=j1pt;
         j1pt=j2pt;
         j2pt=tmpj1pt;
        }
        if (!(Tag_candidates[iJet].Eta()*Tag_candidates[jJet].Eta() < 0)) continue;
        TLorentzVector DijetCandVec = Tag_candidates[iJet] + Tag_candidates[jJet];
        if (DijetCandVec.M() > mJJ){
         mJJ = DijetCandVec.M();
         nTagJet1 = iJet;
         nTagJet2 = jJet;
        }
       }
      }
      if (nTagJet1 != -1 && nTagJet2 != -1){
       if( Tag_candidates[nTagJet1].Pt() < Tag_candidates[nTagJet2].Pt() ){
        int nTagJet_temp = nTagJet1;
        nTagJet1 = nTagJet2;
        nTagJet2 = nTagJet_temp;
       }
      }
      bool bool_TagInsideFat = false;
      for(int i = 0; i < FatJets.size(); i ++){
       if(Tag_candidates[nTagJet1].DeltaR(FatJets[i]) < 1.0) bool_TagInsideFat = true;      
       if(Tag_candidates[nTagJet2].DeltaR(FatJets[i]) < 1.0) bool_TagInsideFat = true;      
      }
      if (mJJ != 0){
       TagJet1.SetPtEtaPhiM(Tag_candidates[nTagJet1].Pt(),Tag_candidates[nTagJet1].Eta(),Tag_candidates[nTagJet1].Phi(),Tag_candidates[nTagJet1].M());
       TagJet2.SetPtEtaPhiM(Tag_candidates[nTagJet2].Pt(),Tag_candidates[nTagJet2].Eta(),Tag_candidates[nTagJet2].Phi(),Tag_candidates[nTagJet2].M());
      }
     }
     if(TagJet1.Pt() < 20 || TagJet2.Pt() < 20) continue;
     Bkgnd2_SecondTagJetStep ++;
     //Fill Tag Jets Histograms:
     B2_TagJetDeltaEta_hist ->Fill(abs(TagJet1.Eta()-TagJet2.Eta()), (*Background_weight)[0]*Scale_B);
     B2_TagJetsMass_hist -> Fill((TagJet1 +TagJet2).M(), No_W_Scale_B);   

     //Fill Histograms:
     B2_LeadingLargeRJet_hist -> Fill(FatJets[0].M(), (*Background_weight)[0]*Scale_B);
     B2_WCandMass_hist -> Fill(WCand.M(), (*Background_weight)[0]*Scale_B);
     B2_WCandPt_hist -> Fill(WCand.Pt(), (*Background_weight)[0]*Scale_B);
     B2_WCandEta_hist -> Fill(WCand.Eta(), (*Background_weight)[0]*Scale_B);
     B2_WCandPhi_hist -> Fill(WCand.Phi(), (*Background_weight)[0]*Scale_B);
     B2_HCandMass_hist -> Fill(HCand.M(), No_W_Scale_B);
     B2_HCandPt_hist -> Fill(HCand.Pt(), No_W_Scale_B);
     B2_HCandEta_hist -> Fill(abs(HCand.Eta()), No_W_Scale_B);
     B2_HCandPhi_hist -> Fill(HCand.Phi(), No_W_Scale_B);
     B2_Nbjets_hist -> Fill(N_Hybrid_bjets,  No_W_Scale_B);
     B2_MWHjj_hist -> Fill((HCand+WCand+TagJet1+TagJet2).M(), No_W_Scale_B);
     B2_FirstLeptonPt_hist -> Fill(leptons[0].Pt(), No_W_Scale_B);
     B2_MissingEt_hist -> Fill(*BMet, No_W_Scale_B);
     if(bJets.size() > 0){
      for(int i = 0; i < bJets.size(); i++){
       B2_bjetsmass_hist -> Fill(bJets[i].M(), No_W_Scale_B);
      }
     }
     //Tag Jets matching efficiency:
     Double_t MinTrue1RecoTag_DeltaR = TruthTagJet1.DeltaR(TagJet1);
     if(TruthTagJet1.DeltaR(TagJet2) < MinTrue1RecoTag_DeltaR) MinTrue1RecoTag_DeltaR = TruthTagJet1.DeltaR(TagJet2);
     B2_Truth1RecoDeltaR_hist -> Fill(MinTrue1RecoTag_DeltaR,  (*Signal_weight)[0]*Scale_S);
     Double_t MinTrue2RecoTag_DeltaR = TruthTagJet2.DeltaR(TagJet1);
     if(TruthTagJet2.DeltaR(TagJet2) < MinTrue2RecoTag_DeltaR) MinTrue2RecoTag_DeltaR = TruthTagJet2.DeltaR(TagJet2);
     B2_Truth2RecoDeltaR_hist -> Fill(MinTrue2RecoTag_DeltaR,  (*Signal_weight)[0]*Scale_S); 

     //Fill Mjj and MHWjj histograms and fill TMVA tree:
     Mjj2_Btree = (TagJet1+TagJet2).M();
     DeltaEta2_Btree = abs(TagJet1.Eta()-TagJet2.Eta());
     HCandPt2_Btree = HCand.Pt();
     WCandPt2_Btree = WCand.Pt();
     MissingEt2_Btree = *BMet;
     FirstLeptonPt2_Btree = leptons[0].Pt();
     WCandMass2_Btree = WCand.M();
     HCandMass2_Btree = HCand.M();
     HCandEta2_Btree = abs(HCand.Eta());
     MWHjj2_Btree = (TagJet1+TagJet2+HCand+WCand).M();
     backgroundTree2 -> Fill();

     //Optimization cuts for Hybrid selection:
     if(abs(HCand.Eta()) < 7.36254 && WCand.M() < 125.467 && leptons[0].Pt() > 266.867){
     //if(HCand.Pt() > 24.5201 && HCand.Eta() <  5.32712 && leptons[0].Pt() > 289.376){
      BC2_MWHjj_hist -> Fill((TagJet1+TagJet2+HCand+WCand).M() , No_W_Scale_B);
      //BC2_TagJetsMass_hist ->Fill((TagJet1+TagJet2).M(), No_W_Scale_B);
      //BC2_TagJetDeltaEta_hist ->Fill(abs(TagJet1.Eta()-TagJet2.Eta()), No_W_Scale_B);
      //HybridMWHjjCuts_BTree = (WCand+HCand+TagJet1+TagJet2).M();
      //backgroundHybridCutsTree -> Fill();
      Check_eff_Background ++;
     }
    }
   }
  
   ttjj_TMVA -> Write();
   //backgroundTree -> Write();
   //backgroundTree2 -> Write();
  
   //TFile *signalCutsTree  = new TFile("signalCutsTree.root", "RECREATE", "signalCutsTree");
   //signalBoostedCutsTree -> Write();
   //signalHybridCutsTree -> Write();

   //TFile *backgroundCutsTree  = new TFile("backgroundCutsTree.root", "RECREATE", "backgroundCutsTree");
   //backgroundBoostedCutsTree -> Write();
   //backgroundHybridCutsTree -> Write();
   //Fill fit input file:
   TFile *hfile = new TFile("Fit_input.root", "RECREATE", "Fit_input");
   S1_WHjjMass_hist -> Rebin(3); 
   B1_WHjjMass_hist -> Rebin(3); 
   S1_WHjjMass_hist -> Write(); 
   B1_WHjjMass_hist -> Write();
   //SC_MWHjj_hist -> Rebin(6); 
   //BC_MWHjj_hist -> Rebin(6);
   SC_MWHjj_hist ->  Write();
   BC_MWHjj_hist ->  Write();

   S2_MWHjj_hist -> Rebin(3); 
   B2_MWHjj_hist -> Rebin(3); 
   S2_MWHjj_hist -> Write(); 
   B2_MWHjj_hist -> Write();
   //SC2_MWHjj_hist -> Rebin(6); 
   //BC2_MWHjj_hist -> Rebin(6);
   SC2_MWHjj_hist ->  Write();
   BC2_MWHjj_hist ->  Write();
   

   TFile *vvhjj_purity = new TFile("vvhjj_purity.root", "RECREATE", "vvhjj_purity");
   S1_Truth1Reco1DeltaR_hist -> Write();
   S1_Truth1Reco2DeltaR_hist -> Write();
   S1_Truth2Reco1DeltaR_hist -> Write();
   S1_Truth2Reco2DeltaR_hist -> Write();
   S1_Truth1HCandDeltaR_hist -> Write();
   S1_Truth1WCandDeltaR_hist -> Write();
   S1_Truth2HCandDeltaR_hist -> Write();
   S1_Truth2WCandDeltaR_hist -> Write();
   S1_Truth1RecoDeltaR_hist -> Write();
   S1_Truth2RecoDeltaR_hist -> Write();
   S2_Truth1RecoDeltaR_hist -> Write();
   S2_Truth2RecoDeltaR_hist -> Write();
  
   cout << "---BACKGROUND BOOSTED SELECTION:" << endl;
   cout << "Fat and Lep Selection Efficiency(Bkgnd): " << (double) Bkgnd1_FatandLep/Bkgnd_Total << endl;
   cout << "H Candidate Selection Efficiency(Bkgnd): " << (double) Bkgnd1_HCandStep/Bkgnd1_FatandLep << endl;
   cout << "TagJet SmallRJets Selection Efficiency(Bkgnd): " << (double) Bkgnd1_FirstTagJetStep/Bkgnd1_HCandStep << endl;
   cout << "TagJet Eta Region Selection Efficiency(Bkgnd): " << (double) Bkgnd1_SecondTagJetStep/Bkgnd1_FirstTagJetStep << endl;
   cout << "Bkgnd Boosted Selection Efficiency: " << (double) Bkgnd1_SecondTagJetStep/Bkgnd_Total << endl;

   cout << "---SIGNAL BOOSTED SELECTION:" << endl;
   cout << "Fat and Lep Selection Efficiency(Signal): " << (double) Signal1_FatandLep/Signal_Total << endl;
   cout << "H Candidate Selection Efficiency(Signal): " << (double) Signal1_HCandStep/Signal1_FatandLep << endl;
   cout << "TagJet SmallRJets Selection Efficiency (Signal): " << (double) Signal1_FirstTagJetStep/Signal1_HCandStep << endl;
   cout << "TagJet Eta Region Selection Efficiency (Signal): " << (double) Signal1_SecondTagJetStep/Signal1_FirstTagJetStep << endl;
   cout << "Signal Boosted Selection Efficiency: " << (double) Signal1_SecondTagJetStep/Signal_Total << endl;

   cout << "---BACKGROUND HYBRID SELECTION:" << endl;
   cout << "Fat and Lep Selection Efficiency(Bkgnd): " << (double) Bkgnd2_FatandLep/Bkgnd_Total << endl;
   cout << "H Candidate Selection Efficiency(Bkgnd): " << (double) Bkgnd2_HCandStep/Bkgnd2_FatandLep << endl;
   cout << "TagJet SmallRJets Selection Efficiency(Bkgnd): " << (double) Bkgnd2_FirstTagJetStep/Bkgnd2_HCandStep << endl;
   cout << "TagJet Eta Region Selection Efficiency(Bkgnd): " << (double) Bkgnd2_SecondTagJetStep/Bkgnd2_FirstTagJetStep << endl;
   cout << "Bkgnd Hybrid Selection Efficiency: " << (double) Bkgnd2_SecondTagJetStep/Bkgnd_Total << endl;

   cout << "---SIGNAL HYBRID SELECTION:" << endl;
   cout << "Fat and Lep Selection Efficiency(Signal): " << (double) Signal2_FatandLep/Signal_Total << endl;
   cout << "H Candidate Selection Efficiency(Signal): " << (double) Signal2_HCandStep/Signal2_FatandLep << endl;
   cout << "TagJet SmallRJets Selection Efficiency (Signal): " << (double) Signal2_FirstTagJetStep/Signal2_HCandStep << endl;
   cout << "TagJet Eta Region Selection Efficiency (Signal): " << (double) Signal2_SecondTagJetStep/Signal2_FirstTagJetStep << endl;
   cout << "Signal Hybrid Selection Efficiency: " << (double) Signal2_SecondTagJetStep/Signal_Total << endl;

   cout << "---ABSOLUTE VALUES:" << endl;
   cout << "Signal total:" << S_Tot << endl;
   cout << "Signal Boost:" << S_Sel << endl;
   cout << "Signal Hybr:" << Signal2_SecondTagJetStep << endl;
   cout << "Bkgnd total:" << B_Tot << endl;
   cout << "Bkgnd Boost:" << B_Sel << endl;
   cout << "Bkgnd Hybr:" << Bkgnd2_SecondTagJetStep << endl;
   cout << "Total Efficency for Signal:" << (double) S_Sel/S_Tot << endl;
   cout << "Total Efficency for Bkg:" << (double) B_Sel/B_Tot << endl;

   cout << "---Check optimization cuts:" << endl;
   cout << "HCandMass < 136.165 GeV:" << endl;
   cout << "signal: " << (double) Check_eff_Signal/Signal2_SecondTagJetStep << endl;
   cout << "background: " << (double) Check_eff_Background/Bkgnd2_SecondTagJetStep << endl;
   //Plots
   std::vector<TString> titles1 = {"DeltaEta_FatJet","DeltaR_LeadFatJet_smallRJet","DeltaR_SubLeadFatJet_smallRJet","NsmallRJets","NFatJets","Nbjets", "NFatbJets", "TagJet_DeltaEta", "Lepton_DeltaR", "Nelectrons", "Nmuons", "NbJets_LeadingFatJet", "Nbjets_SubleadingFatJet", "NFatJetsw2bJets", "LeadingFatJet_Pt", "SubleadingFatJet_Pt", "MissingEt", "Nleptons", "FatJetMass", "SecondLepton_Pt", "LeadingFatJet_Mass", "SubleadingFatJet_Mass", "HCand_Mass", "FatJets2bJets_Mass", "WCand_Mass", "TagJets_Mass", "WHjj_Mass", "Muon_Iso", "Electron_Iso", "NTagJets", "DeltaEtaNeg", "EventswTagJets", "SmallRJets_Pt", "TagJet1_HCand_DeltaR", "TagJet1_WCand_DeltaR", "TagJet2_HCand_DeltaR", "TagJet2_WCand_DeltaR", "NTagJetCandidates", "SmallRJets_Eta", "HCandPt", "HCandEta", "HCandPhi", "WCandPt", "WCandEta", "WCandPhi", "TruthQuark1_Eta", "TruthQuark2_Eta", "TotalTruth1RecoDeltaR", "TotalTruth2RecoDeltaR", "TagJet1Pt", "TagJet1Eta", "TagJet1Phi", "TagJet2Pt", "TagJet2Eta", "TagJet2Phi", "NSmallRJetsInside", "TruthTagJet1Eta", "TruthTagJet2Eta", "FirstLeptonPt"};
   std::vector<TH1F*> Shistos1 = {S1_FatJetDeltaEta_hist, S1_LFatJetSRJetDeltaR_hist, S1_SFatJetSRJetDeltaR_hist, S1_NSmallRJets_hist, S1_NFatJets_hist, S1_NbJets_hist, S1_NFatbJets_hist, S1_TagJetDeltaEta_hist, S1_LeptonDeltaR_hist, S1_Nelectrons_hist, S1_Nmuons_hist, S1_NbJetsLeadingFatJet_hist, S1_NbJetsSubleadingFatJet_hist, S1_NFatJetsw2bjets_hist, S1_LeadingFatJetPt_hist, S1_SubleadingFatJetPt_hist, S1_MissingEt_hist, S1_Nleptons_hist, S1_FatJetMass_hist, S1_SecondLeptonPt_hist, S1_LeadingFatJetMass_hist, S1_SubleadingFatJetMass_hist, S1_HCandMass_hist, S1_FatJets2bJetsMass_hist, S1_WCandMass_hist, S1_TagJetsMass_hist, S1_WHjjMass_hist, S1_MuonIso_hist, S1_ElectronIso_hist, S1_NTagJets_hist, S1_DeltaEtaNeg_hist, S1_EventswTagJets_hist, S1_SmallRJetsPt_hist, S1_TagJet1HCandDeltaR_hist,S1_TagJet1WCandDeltaR_hist,S1_TagJet2HCandDeltaR_hist,S1_TagJet2WCandDeltaR_hist, S1_NTagCandidates_hist, S1_SmallRJetsEta_hist, S1_HCandPt_hist, S1_HCandEta_hist, S1_HCandPhi_hist, S1_WCandPt_hist, S1_WCandEta_hist, S1_WCandPhi_hist, S1_TruthQuark1Eta_hist, S1_TruthQuark2Eta_hist, S1_Truth1RecoDeltaR_hist, S1_Truth2RecoDeltaR_hist, S1_TagJet1Pt_hist, S1_TagJet1Eta_hist, S1_TagJet1Phi_hist, S1_TagJet2Pt_hist, S1_TagJet2Eta_hist, S1_TagJet2Phi_hist, S1_NSmallRJetsInside_hist, S1_TruthTagJet1Eta_hist, S1_TruthTagJet2Eta_hist, S1_FirstLeptonPt_hist};
   std::vector<TH1F*> Bhistos1 = {B1_FatJetDeltaEta_hist, B1_LFatJetSRJetDeltaR_hist, B1_SFatJetSRJetDeltaR_hist, B1_NSmallRJets_hist, B1_NFatJets_hist, B1_NbJets_hist, B1_NFatbJets_hist, B1_TagJetDeltaEta_hist, B1_LeptonDeltaR_hist, B1_Nelectrons_hist, B1_Nmuons_hist, B1_NbJetsLeadingFatJet_hist, B1_NbJetsSubleadingFatJet_hist, B1_NFatJetsw2bjets_hist, B1_LeadingFatJetPt_hist, B1_SubleadingFatJetPt_hist, B1_MissingEt_hist, B1_Nleptons_hist, B1_FatJetMass_hist, B1_SecondLeptonPt_hist, B1_LeadingFatJetMass_hist, B1_SubleadingFatJetMass_hist, B1_HCandMass_hist, B1_FatJets2bJetsMass_hist, B1_WCandMass_hist, B1_TagJetsMass_hist, B1_WHjjMass_hist, B1_MuonIso_hist, B1_ElectronIso_hist, B1_NTagJets_hist, B1_DeltaEtaNeg_hist, B1_EventswTagJets_hist, B1_SmallRJetsPt_hist, B1_TagJet1HCandDeltaR_hist,B1_TagJet1WCandDeltaR_hist,B1_TagJet2HCandDeltaR_hist,B1_TagJet2WCandDeltaR_hist, B1_NTagCandidates_hist, B1_SmallRJetsEta_hist, B1_HCandPt_hist, B1_HCandEta_hist, B1_HCandPhi_hist, B1_WCandPt_hist, B1_WCandEta_hist, B1_WCandPhi_hist, B1_TruthQuark1Eta_hist, B1_TruthQuark2Eta_hist, B1_Truth1RecoDeltaR_hist, B1_Truth2RecoDeltaR_hist, B1_TagJet1Pt_hist, B1_TagJet1Eta_hist, B1_TagJet1Phi_hist, B1_TagJet2Pt_hist, B1_TagJet2Eta_hist, B1_TagJet2Phi_hist, B1_NSmallRJetsInside_hist, B1_TruthTagJet1Eta_hist, B1_TruthTagJet2Eta_hist, B1_FirstLeptonPt_hist};  
   std::vector<TCanvas*> canvases1(titles1.size());
   for (int i = 0; i < titles1.size(); ++i) {
    TCanvas *c = new TCanvas(("c" + std::to_string(i)).c_str(), titles1[i], 200, 10, 900, 700);
    canvases1[i] = c;
    //c->Divide(1,2);
    //c->cd(1);
    gStyle->SetOptStat(0);
    gStyle->SetLegendFont(132);
    //gStyle->SetOptTitle(0);
    TLegend* leg = new TLegend(0.64,0.68, 0.84, 0.88);
    leg->SetBorderSize(0);
    leg->SetFillStyle (0);
    leg->SetTextSize  (0.04);
    Shistos1[i] -> SetLineColor(2);
    Bhistos1[i] -> SetLineColor(4);
    Shistos1[i] -> SetLineStyle(0);
    Bhistos1[i] -> SetLineStyle(3);
    Shistos1[i] -> SetLineWidth(2);
    Bhistos1[i] -> SetLineWidth(2);
    Shistos1[i]-> GetXaxis()-> SetTitle(Shistos1[i]->GetTitle());
    Bhistos1[i]-> GetXaxis()-> SetTitle(Shistos1[i]->GetTitle());
    Shistos1[i]-> GetYaxis()-> SetTitle("A.U.");
    Bhistos1[i]-> GetYaxis()-> SetTitle("A.U.");
    Shistos1[i]-> SetTitle(" ");
    Bhistos1[i]-> SetTitle(" ");
    Shistos1[i]-> SetName("Signal Stats");
    Bhistos1[i]-> SetName("Bkg Stats");
    if (Shistos1[i] != S1_WHjjMass_hist && Shistos1[i] != S1_NSmallRJets_hist && Shistos1[i] != S1_NFatJets_hist && Shistos1[i] != S1_NbJets_hist && Shistos1[i] != S1_NFatbJets_hist && Shistos1[i] != S1_NTagJets_hist && Shistos1[i] != S1_Nleptons_hist && Shistos1[i] != S1_NTagCandidates_hist && Shistos1[i] != S1_NSmallRJetsInside_hist && Shistos1[i] != S1_Nelectrons_hist && Shistos1[i] != S1_Nmuons_hist && Shistos1[i] != S1_NbJetsLeadingFatJet_hist && Shistos1[i] != S1_NbJetsSubleadingFatJet_hist && Shistos1[i] != S1_NFatJetsw2bjets_hist && Bhistos1[i] != B1_WHjjMass_hist &&  Bhistos1[i] != B1_NSmallRJets_hist && Bhistos1[i] != B1_NFatJets_hist && Bhistos1[i] != B1_NbJets_hist && Bhistos1[i] != B1_NFatbJets_hist && Bhistos1[i] != B1_NTagJets_hist && Bhistos1[i] != B1_Nleptons_hist && Bhistos1[i] != B1_NTagCandidates_hist && Bhistos1[i] != B1_NSmallRJetsInside_hist && Bhistos1[i] != B1_Nelectrons_hist && Bhistos1[i] != B1_Nmuons_hist && Bhistos1[i] != B1_NbJetsLeadingFatJet_hist && Bhistos1[i] != B1_NbJetsSubleadingFatJet_hist && Bhistos1[i] != B1_NFatJetsw2bjets_hist){ 
     Shistos1[i] -> Rebin(2);
     Bhistos1[i] -> Rebin(2);
    }
    //Bhistos1[i] -> Draw("h");
    //Shistos1[i] -> Draw("same, h");
    //leg->Draw();

    TLatex l;
    l.SetNDC();
    l.SetTextFont (132);
    l.SetTextColor(kBlack);
    l.SetTextSize (0.04);
    //l.DrawLatex(0.8, 0.73, "#sqrt{s} = 14 TeV");

    TLatex s;
    s.SetNDC();
    s.SetTextFont (42);
    s.SetTextColor(kBlack);
    s.SetTextSize (0.04);
    //c -> cd(2);

    Shistos1[i] -> DrawNormalized("h");
    //c->Modified(); c->Update();
    //TPaveStats *stats =(TPaveStats*)c->GetPrimitive("stats");
    //stats->SetName("Signal stats");
    //stats->SetY1NDC(.9);
    //stats->SetY2NDC(.82);
    //stats->SetX1NDC(.7);
    //stats->SetX2NDC(.9);
    //stats->SetTextColor(1);
    //stats->SetTextSize(0.04);
    Bhistos1[i] -> DrawNormalized("SAMES h");
    //c-> Modified(); c->Update();
    //TPaveStats *stats2 = (TPaveStats*)c->GetPrimitive("stats");
    //stats2->SetY1NDC(.82);
    //stats2->SetY2NDC(.74);
    //stats2->SetX1NDC(.7);
    //stats2->SetX2NDC(.9);
    //stats2->SetTextColor(1);
    //stats2->SetTextSize(0.04);
    leg->SetHeader(selection1,"");
    leg->AddEntry((TObject*)0,"", "");
    leg->AddEntry(Shistos1[i],  "VVH-jj", "l");
    leg->AddEntry(Bhistos1[i],  "t#bar{t}-jj ", "l");
    leg->Draw();
    l.DrawLatex(0.68, 0.79, "#sqrt{s} = 14 TeV");
    //s.DrawLatex(0.2, 0.8, selection1);
    c->SaveAs(("/usatlas/u/mmollerac/usatlasdata/WWHjj/Delphes-3.5.0/Manu/First_Selection/")+titles1[i] + (".pdf"));
    c->SaveAs(("/usatlas/u/mmollerac/usatlasdata/WWHjj/Delphes-3.5.0/Manu/First_Selection/")+titles1[i] + (".C"));
   }
  
   //Second selection plots:
   std::vector<TString> titles2 = {"LeadingLargeRJetMass", "WcandMass", "TagJets_DeltaEta", "Nbjets", "bjetsMass", "HCandMass", "WCandPt", "WCandEta", "WCandPhi", "HCandPt", "HCandEta", "HCandPhi", "TagJetsMass", "Matchingeff1", "Matchingeff2", "MWHjj", "FirstLeptonPt", "MissingEt"};
   std::vector<TH1F*> Shistos2 = {S2_LeadingLargeRJet_hist, S2_WCandMass_hist, S2_TagJetDeltaEta_hist, S2_Nbjets_hist, S2_bjetsmass_hist, S2_HCandMass_hist, S2_WCandPt_hist, S2_WCandEta_hist, S2_WCandPhi_hist, S2_HCandPt_hist, S2_HCandEta_hist, S2_HCandPhi_hist, S2_TagJetsMass_hist, S2_Truth1RecoDeltaR_hist, S2_Truth2RecoDeltaR_hist, S2_MWHjj_hist, S2_FirstLeptonPt_hist, S2_MissingEt_hist};
   std::vector<TH1F*> Bhistos2 = {B2_LeadingLargeRJet_hist, B2_WCandMass_hist, B2_TagJetDeltaEta_hist, B2_Nbjets_hist, B2_bjetsmass_hist, B2_HCandMass_hist, B2_WCandPt_hist, B2_WCandEta_hist, B2_WCandPhi_hist, B2_HCandPt_hist, B2_HCandEta_hist, B2_HCandPhi_hist, B2_TagJetsMass_hist, B2_Truth1RecoDeltaR_hist, B2_Truth2RecoDeltaR_hist, B2_MWHjj_hist, B2_FirstLeptonPt_hist, B2_MissingEt_hist};
   std::vector<TCanvas*> canvases2(titles2.size());
   for (int i = 0; i < titles2.size(); ++i) {
    TCanvas *c = new TCanvas(("c" + std::to_string(i)).c_str(), titles2[i], 200, 10, 900, 700);
    canvases2[i] = c;
    //c->Divide(1,2);
    //c->cd(1);
    gStyle->SetOptStat(0);
    gStyle->SetLegendFont(132);
    TLegend* leg = new TLegend(0.68, 0.68, 0.88, 0.88);
    leg->SetBorderSize(0);
    leg->SetFillStyle (0);
    leg->SetTextSize  (0.04);
    Shistos2[i] -> SetLineColor(2);
    Bhistos2[i] -> SetLineColor(4);
    Shistos2[i] -> SetLineStyle(0);
    Bhistos2[i] -> SetLineStyle(3);
    Shistos2[i] -> SetLineWidth(2);
    Bhistos2[i] -> SetLineWidth(2);
    Shistos2[i]-> GetXaxis()-> SetTitle(Shistos2[i]->GetTitle());
    Bhistos2[i]-> GetXaxis()-> SetTitle(Shistos2[i]->GetTitle());
    Shistos2[i]-> GetYaxis()-> SetTitle("A.U.");
    Bhistos2[i]-> GetYaxis()-> SetTitle("A.U.");
    Shistos2[i]-> SetTitle(" ");
    Bhistos2[i]-> SetTitle(" ");
    Shistos2[i]-> SetName("Signal Stats");
    Bhistos2[i]-> SetName("Bkg Stats");
    if (Shistos2[i] != S2_Nbjets_hist && Shistos2[i] != S2_MWHjj_hist){ 
    Shistos2[i] -> Rebin(2);
    Bhistos2[i] -> Rebin(2);
    }
     
    TLatex l;
    l.SetNDC();
    l.SetTextFont (132);
    l.SetTextColor(kBlack);
    l.SetTextSize (0.04);
    //c -> cd(2);
    TLatex s;
    s.SetNDC();
    s.SetTextFont (42);
    s.SetTextColor(kBlack);
    s.SetTextSize (0.04);

    Shistos2[i] -> DrawNormalized("h");
    //c->Modified(); c->Update();
    //TPaveStats *stats =(TPaveStats*)c->GetPrimitive("stats");
    //stats->SetName("Signal stats");
    //stats->SetY1NDC(.9);
    //stats->SetY2NDC(.82);
    //stats->SetX1NDC(.7);
    //stats->SetX2NDC(.9);
    //stats->SetTextColor(1);
    //stats->SetTextSize(0.04);
    Bhistos2[i] -> DrawNormalized("SAMES h");
    //c-> Modified(); c->Update();
    //TPaveStats *stats2 = (TPaveStats*)c->GetPrimitive("stats");
    //stats2->SetY1NDC(.82);
    //stats2->SetY2NDC(.74);
    //stats2->SetX1NDC(.7);
    //stats2->SetX2NDC(.9);
    //stats2->SetTextColor(1);
    //stats2->SetTextSize(0.04);
    leg->SetHeader(selection2,"");
    leg->AddEntry((TObject*)0,"", "");
    leg->AddEntry(Shistos2[i],  "VVH-jj", "l");
    leg->AddEntry(Bhistos2[i],  "t#bar{t}-jj ", "l");
    leg->Draw();
    l.DrawLatex(0.68, 0.79, "#sqrt{s} = 14 TeV");
    //s.DrawLatex(0.2, 0.8, selection2);
    c->SaveAs(("/usatlas/u/mmollerac/usatlasdata/WWHjj/Delphes-3.5.0/Manu/Second_Selection/") +titles2[i] + (".pdf"));
    c->SaveAs(("/usatlas/u/mmollerac/usatlasdata/WWHjj/Delphes-3.5.0/Manu/Second_Selection/") +titles2[i] + (".C"));
   }

   //No selection plots:
   std::vector<TString> titles_S = {"DeltaR_NearSmallJetQ1", "DeltaR_NearSmallJetQ2", "TruthTagJet1Pt", "TruthTagJet1Eta", "TruthTagJet1Phi", "TruthTagJet1Mass", "TruthTagJet2Pt", "TruthTagJet2Eta", "TruthTagJet2Phi", "TruthTagJet2Mass", "TruthQ1DeltaR", "TruthQ2DeltaR", "NTruthTag_candiates"};
   std::vector<TH1F*> Shistos_S = {S_TruthQuark1MinDeltaR_hist,S_TruthQuark2MinDeltaR_hist, S_TruthTagJet1Pt_hist, S_TruthTagJet1Eta_hist, S_TruthTagJet1Phi_hist, S_TruthTagJet1Mass_hist, S_TruthTagJet2Pt_hist, S_TruthTagJet2Eta_hist, S_TruthTagJet2Phi_hist, S_TruthTagJet2Mass_hist, S_TruthQ1DeltaR_hist, S_TruthQ2DeltaR_hist, S_NTruthTagCandidates_hist};
   std::vector<TCanvas*> canvases_S(titles_S.size());
   for (int i = 0; i < titles_S.size(); ++i) {
    TCanvas *c = new TCanvas(("c" + std::to_string(i)).c_str(), titles_S[i], 200, 10, 900, 700);
    canvases_S[i] = c;
    gStyle->SetOptStat(0);
    gStyle->SetLegendFont(132);
    TLegend* leg = new TLegend(0.68, 0.68, 0.88, 0.88);
    leg->SetBorderSize(0);
    leg->SetFillStyle (0);
    leg->SetTextSize  (0.04);
    Shistos_S[i] -> SetLineColor(2);
    Shistos_S[i] -> SetLineStyle(0);
    Shistos_S[i] -> SetLineWidth(2);
    Shistos_S[i]-> GetYaxis()-> SetTitle("A.U.");
    Shistos_S[i]-> GetXaxis()-> SetTitle(Shistos_S[i]->GetTitle());
    Shistos_S[i]-> SetTitle(" ");
    Shistos_S[i]-> SetName("Stats");
    TLatex l;
    l.SetNDC();
    l.SetTextFont (132);
    l.SetTextColor(kBlack);
    l.SetTextSize (0.04);
    Shistos_S[i] -> DrawNormalized("h");
   // TPaveStats *stats =(TPaveStats*)c->GetPrimitive("stats");
    //stats->SetName("Signal stats");
    //stats->SetY1NDC(.9);
    //stats->SetY2NDC(.82);
    //stats->SetX1NDC(.7);
    //stats->SetX2NDC(.9);
    //stats->SetTextColor(1);
    //stats->SetTextSize(0.04);
    leg->SetHeader(selection,"");
    leg->AddEntry((TObject*)0,"", "");
    leg->AddEntry(Shistos_S[i],  "VVH-jj", "l");
    leg->Draw();
    TLatex s;
    s.SetNDC();
    s.SetTextFont (42);
    s.SetTextColor(kBlack);
    s.SetTextSize (0.04);
    l.DrawLatex(0.68, 0.79, "#sqrt{s} = 14 TeV");
    //s.DrawLatex(0.7, 0.91, selection);
    c->SaveAs(("/usatlas/u/mmollerac/usatlasdata/WWHjj/Delphes-3.5.0/Manu/NoSel/")+titles_S[i] + (".pdf"));
    c->SaveAs(("/usatlas/u/mmollerac/usatlasdata/WWHjj/Delphes-3.5.0/Manu/NoSel/")+titles_S[i] + (".C"));
   }

   std::vector<TString> titles = {"NFatJets", "LeadingFatJetPt", "NLeptons"};
   std::vector<TH1F*> Shistos = {S_NFatJets_hist, S_LeadingFatJetPt_hist, S_NLeptons_hist};
   std::vector<TH1F*> Bhistos = {B_NFatJets_hist, B_LeadingFatJetPt_hist, B_NLeptons_hist};
   std::vector<TCanvas*> canvases(titles.size());
   for (int i = 0; i < titles.size(); ++i) {
    TCanvas *c = new TCanvas(("c" + std::to_string(i)).c_str(), titles[i], 200, 10, 900, 700);
    canvases[i] = c;
    //gStyle->SetOptStat(11);
    //gStyle->SetPadTickX(1);
    //gStyle->SetPadTickY(1);
    TLegend* leg = new TLegend(0.68, 0.68, 0.88, 0.88);
    leg->SetBorderSize(0);
    leg->SetFillStyle (0);
    leg->SetTextSize  (0.04);
    Shistos[i] -> SetLineColor(2);
    Bhistos[i] -> SetLineColor(4);
    Shistos[i] -> SetLineStyle(0);
    Bhistos[i] -> SetLineStyle(3);
    Shistos[i] -> SetLineWidth(2);
    Bhistos[i] -> SetLineWidth(2);
    Shistos[i]-> GetXaxis()-> SetTitle(Shistos[i]->GetTitle());
    Bhistos[i]-> GetXaxis()-> SetTitle(Shistos[i]->GetTitle());
    Shistos[i]-> GetYaxis()-> SetTitle("A.U.");
    Bhistos[i]-> GetYaxis()-> SetTitle("A.U.");
    Shistos[i]-> SetTitle(" ");
    Bhistos[i]-> SetTitle(" ");
    //Shistos[i]-> SetName("Signal Stats");
    //Bhistos[i]-> SetName("Bkg Stats");
    //Shistos[i] -> Rebin(2);
    //Bhistos[i] -> Rebin(2);
    //Bhistos2[i] -> Draw("h");
    //Shistos2[i] -> Draw("same, h");
 
    TLatex l;
    l.SetNDC();
    l.SetTextFont (132);
    l.SetTextColor(kBlack);
    l.SetTextSize (0.04);
    l.DrawLatex(0.2, 0.2, "#sqrt{s} = 14 TeV");
    //c -> cd(2);
    TLatex s;
    s.SetNDC();
    s.SetTextFont (42);
    s.SetTextColor(kBlack);
    s.SetTextSize (0.04);

    Bhistos[i] -> DrawNormalized("h");
    //c->Modified(); c->Update();
    // TPaveStats *stats =(TPaveStats*)c->GetPrimitive("stats");
    //stats->SetName("Signal stats");
    //stats->SetY1NDC(.9);
    //stats->SetY2NDC(.82);
    //stats->SetX1NDC(.65);
    //stats->SetX2NDC(.9);
    //stats->SetTextColor(1);
    //stats->SetTextSize(0.04);
    Shistos[i] -> DrawNormalized("SAMES h");
    //c-> Modified(); c->Update();
    //TPaveStats *stats2 = (TPaveStats*)c->GetPrimitive("stats");
    //stats2->SetY1NDC(.82);
    //stats2->SetY2NDC(.74);
    //stats2->SetX1NDC(.65);
    //stats2->SetX2NDC(.9);
    //stats2->SetTextColor(1);
    //stats2->SetTextSize(0.04);
    //gStyle->SetOptStat(11);
    gStyle->SetOptStat(0);
    gStyle->SetLegendFont(132);
    //gStyle->SetLegendFont(132);
    //leg->SetBorderSize(0);
    //leg->SetFillStyle (3);
    leg->SetTextSize  (0.04);
    Shistos[i] -> SetLineColor(2);
    Shistos[i] -> SetLineStyle(0);
    Shistos[i]-> GetXaxis()-> SetTitle(Shistos[i]->GetTitle());
    //Shistos[i]-> SetName("Stats");
    leg->SetHeader(selection,"");
    leg->AddEntry((TObject*)0,"", "");
    leg->AddEntry(Shistos[i],  "VVH-jj", "l");
    leg->AddEntry(Bhistos[i],  "t#bar{t}-jj ", "l");
    leg->Draw();
    //s.DrawLatex(0.7, 0.85, selection);
    l.DrawLatex(0.68, 0.79, "#sqrt{s} = 14 TeV");
    c->SaveAs(("/usatlas/u/mmollerac/usatlasdata/WWHjj/Delphes-3.5.0/Manu/NoSel/")+titles[i] + (".pdf"));
    c->SaveAs(("/usatlas/u/mmollerac/usatlasdata/WWHjj/Delphes-3.5.0/Manu/NoSel/")+titles[i] + (".C"));
   }

   //Cut optimization plots:
   //std::vector<TString> titlesc = {"TagJetDeltaEta", "WHjj_Mass", "Mjj", "WHjj_Mass_H"};
   //std::vector<TH1F*> Shistosc = {SC_TagJetDeltaEta_hist, SC_MWHjj_hist, SC_TagJetsMass_hist, SC2_MWHjj_hist};
   //std::vector<TH1F*> Bhistosc = {BC_TagJetDeltaEta_hist, BC_MWHjj_hist, BC_TagJetsMass_hist, BC2_MWHjj_hist};
   std::vector<TString> titlesc = {"TagJetDeltaEta", "WHjj_Mass_boost", "Mjj", "WHjj_Mass_hybr"};
   std::vector<TH1F*> Shistosc = {SC_TagJetDeltaEta_hist, SC_MWHjj_hist, SC_TagJetsMass_hist, SC2_MWHjj_hist};
   std::vector<TH1F*> Bhistosc = {BC_TagJetDeltaEta_hist, BC_MWHjj_hist, BC_TagJetsMass_hist, BC2_MWHjj_hist};
   std::vector<TCanvas*> canvasesc(titlesc.size());
   for (int i = 0; i < titlesc.size(); ++i) {
    TCanvas *c = new TCanvas(("c" + std::to_string(i)).c_str(), titlesc[i], 200, 10, 900, 700);
    canvases[i] = c;
    gStyle->SetOptStat(0);
    gStyle->SetStatFontSize(3);
    gStyle->SetStatW(.2);
    TLegend* leg = new TLegend(0.68, 0.68, 0.88, 0.88);
    leg->SetBorderSize(0);
    leg->SetFillStyle (0);
    leg->SetTextSize  (0.04);
    Shistosc[i] -> SetLineColor(2);
    Shistosc[i] -> SetLineStyle(0);
    Shistosc[i]-> GetXaxis()-> SetTitle(Shistosc[i]->GetTitle());
    Shistosc[i]-> GetYaxis()-> SetTitle("N Eventos/#sigma");
    Shistosc[i]-> SetName("Signal Stats");
    Bhistosc[i] -> SetLineColor(4);
    Bhistosc[i] -> SetLineStyle(3);
    Bhistosc[i]-> GetXaxis()-> SetTitle(Shistosc[i]->GetTitle());
    Bhistosc[i]-> GetYaxis()-> SetTitle("N Eventos/#sigma");
    Bhistosc[i]-> SetName("Bkg Stats");
    Shistosc[i]-> SetTitle(" ");
    Bhistosc[i]-> SetTitle(" ");
    Shistosc[i] -> SetLineWidth(2);
    Bhistosc[i] -> SetLineWidth(2);
    if(Shistosc[i] != SC_MWHjj_hist && Bhistosc[i] != BC_MWHjj_hist && Bhistosc[i] != BC2_MWHjj_hist ){
    //if(Shistosc[i] != SC_MWHjj_hist && Shistosc[i] != SC2_MWHjj_hist && Bhistosc[i] != BC_MWHjj_hist && Bhistosc[i] != BC2_MWHjj_hist){
     Shistosc[i] -> Rebin(6);
     Bhistosc[i] -> Rebin(6);
    }

    TLatex s;
    s.SetNDC();
    s.SetTextFont (42);
    s.SetTextColor(kBlack);
    s.SetTextSize (0.04);
    TLatex l;
    l.SetNDC();
    l.SetTextFont (42);
    l.SetTextColor(kBlack);
    l.SetTextSize (0.04);
    Shistosc[i] -> DrawNormalized("h");
    //c->Modified(); c->Update();
    //TPaveStats *stats =(TPaveStats*)c->GetPrimitive("stats");
    //stats->SetName("Signal stats");
    //stats->SetY1NDC(.95);
    //stats->SetY2NDC(.9);
    //stats->SetTextColor(1);
    
    Bhistosc[i] -> DrawNormalized("SAMES h");
    //c-> Modified(); c->Update();
    //TPaveStats *stats2 = (TPaveStats*)c->GetPrimitive("stats");
    //stats2->SetY1NDC(.9);
    //stats2->SetY2NDC(.85);
    //stats2->SetTextColor(1);
    leg->SetHeader(selectionc,"");
    leg->AddEntry((TObject*)0,"", "");
    leg->AddEntry(Shistosc[i], "VVHjj", "l");
    leg->AddEntry(Bhistosc[i], "ttjj", "l");
    leg->Draw();
    //s.DrawLatex(0.2, 0.91, selectionc);
    l.DrawLatex(0.68, 0.79, "#sqrt{s} = 14 TeV");
    c->SaveAs(("/usatlas/u/mmollerac/usatlasdata/WWHjj/Delphes-3.5.0/Manu/OptCut/")+titlesc[i] + (".pdf"));
    c->SaveAs(("/usatlas/u/mmollerac/usatlasdata/WWHjj/Delphes-3.5.0/Manu/OptCut/")+titlesc[i] + (".C"));
   }

   TCanvas *c = new TCanvas("c", "MWHjj - Mjj correlation", 200, 10, 900, 700);
   gStyle->SetOptStat(0);
   S1_MWHjjMjjCorr_hist-> GetXaxis()-> SetTitle("WHjj Mass");
   S1_MWHjjMjjCorr_hist-> GetYaxis()-> SetTitle("jj Mass");
   S1_MWHjjMjjCorr_hist -> Draw();
   c->SaveAs(("/usatlas/u/mmollerac/usatlasdata/WWHjj/Delphes-3.5.0/Manu/Corr/MjjCorr.png"));

   TCanvas *c1 = new TCanvas("c", "MWHjj - jjDeltaEta correlation", 200, 10, 900, 700);
   gStyle->SetOptStat(0);
   S1_MWHjjDeltaEtajjCorr_hist-> GetXaxis()-> SetTitle("WHjj Mass");
   S1_MWHjjDeltaEtajjCorr_hist-> GetYaxis()-> SetTitle("jj Delta Eta");
   S1_MWHjjDeltaEtajjCorr_hist -> Draw();
   
   c1->SaveAs(("/usatlas/u/mmollerac/usatlasdata/WWHjj/Delphes-3.5.0/Manu/Corr/jjDeltaEtaCorr.png"));

   TCanvas *c2 = new TCanvas("c", "Mjj -jjDeltaEta correlation", 200, 10, 900, 700);
   gStyle->SetOptStat(0);
   S1_MjjDeltaEtajjCorr_hist -> GetXaxis()->SetTitle("Mjj");
   S1_MjjDeltaEtajjCorr_hist -> GetYaxis()->SetTitle("jj Delta Eta");
   S1_MjjDeltaEtajjCorr_hist -> Draw();
   c2->SaveAs(("/usatlas/u/mmollerac/usatlasdata/WWHjj/Delphes-3.5.0/Manu/Corr/MjjDeltaEtaCorr.png"));

   TFile *ttjj_purity = new TFile("ttjj_purity.root", "RECREATE", "ttjj_purity");
   B1_Truth1Reco1DeltaR_hist -> Write();
   B1_Truth1Reco2DeltaR_hist -> Write();
   B1_Truth2Reco1DeltaR_hist -> Write();
   B1_Truth2Reco2DeltaR_hist -> Write();
   B1_Truth1HCandDeltaR_hist -> Write();
   B1_Truth1WCandDeltaR_hist -> Write();
   B1_Truth2HCandDeltaR_hist -> Write();
   B1_Truth2WCandDeltaR_hist -> Write();

 }
