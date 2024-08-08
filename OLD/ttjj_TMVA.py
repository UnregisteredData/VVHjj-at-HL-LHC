import sys
sys.path = [r'C:\root_v6.32.02\bin'] + sys.path

import math
from array import array

import ROOT
from ROOT import TTreeReader, TTreeReaderValue, TFile, TH1F, TLorentzVector, TH1D, TCanvas, TLegend, gStyle

background_file = TFile.Open(r'C:\Users\hcds\ttjj.root')
Background = background_file['myTree']

signal_file = TFile.Open(r'C:\Users\hcds\VVHjj.root')
Signal = signal_file['myTree']


fit_input = TFile(r"C:\Users\hcds\selection_tree.root", "RECREATE")
ttjj_TMVA = ROOT.TTree("ttjj_TMVA", "Tree for TMVA")

DeltaEtajj = array('f', [0])
leptonpt = array('f', [0])
tagjet2eta = array('f', [0])
tagjet1eta = array('f', [0])
tagjet2pt = array('f', [0])
tagjet1pt = array('f', [0])
PTW_tree = array('f', [0])
PTH_tree = array('f', [0])
Mjj_tree = array('f', [0])
MVH_tree = array('f', [0])
MV_tree = array('f', [0])
MH_tree = array('f', [0])

ttjj_TMVA.Branch("DeltaEtajj", DeltaEtajj, "DeltaEtajj/F")
ttjj_TMVA.Branch("leptonpt", leptonpt, "leptonpt/F")
ttjj_TMVA.Branch("tagjet2eta", tagjet2eta, "tagjet2eta/F")
ttjj_TMVA.Branch("tagjet1eta", tagjet1eta, "tagjet1eta/F")
ttjj_TMVA.Branch("tagjet2pt", tagjet2pt, "tagjet2pt/F")
ttjj_TMVA.Branch("tagjet1pt", tagjet1pt, "tagjet1pt/F")
ttjj_TMVA.Branch("PTW_tree", PTW_tree, "PTW_tree/F")
ttjj_TMVA.Branch("PTH_tree", PTH_tree, "PTH_tree/F")
ttjj_TMVA.Branch("Mjj_tree", Mjj_tree, "Mjj_tree/F")
ttjj_TMVA.Branch("MVH_tree", MVH_tree, "MVH_tree/F")
ttjj_TMVA.Branch("MV_tree", MV_tree, "MV_tree/F")
ttjj_TMVA.Branch("MH_tree", MH_tree, "MH_tree/F")

for event in Background:
    mhiggs = Background.MH_tree
    if any(pt > 200 for pt in Background.fatjetspt) and Background.fatjetsmass.size() > 1 and any(eta < 2 for eta in Background.fatjetseta) and any(Rpt > 20 for Rpt in Background.smallRjetspt) and mhiggs > 70 and mhiggs < 140:

        DeltaEtajj[0] = Background.DeltaEtajj
        leptonpt[0] = Background.leptonpt
        tagjet2eta[0] = Background.tagjet2eta
        tagjet1eta[0] = Background.tagjet1eta
        tagjet2pt[0] = Background.tagjet2pt
        tagjet1pt[0] = Background.tagjet1pt
        PTW_tree[0] = Background.PTW_tree
        PTH_tree[0] = Background.PTH_tree
        Mjj_tree[0] = Background.Mjj_tree
        MVH_tree[0] = Background.MVH_tree
        MV_tree[0] = Background.MV_tree
        MH_tree[0] = Background.MH_tree

        ttjj_TMVA.Fill()


ttjj_TMVA.Write()


fit_input.Close()
background_file.Close()
signal_file.Close()

print('Done.')

