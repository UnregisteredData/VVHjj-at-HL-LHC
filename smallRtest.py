import sys
sys.path = [r'C:\root_v6.32.02\bin'] + sys.path

import math
from array import array
from itertools import combinations

import ROOT
from ROOT import TTreeReader, TTreeReaderValue, TFile, TH1F, TLorentzVector, TCanvas, TLegend

background_file = TFile.Open(r'C:\Users\hcds\ttjj.root')
Background = background_file['myTree']

signal_file = TFile.Open(r'C:\Users\hcds\VVHjj.root')
Signal = signal_file['myTree']

Entries_S = Signal.GetEntriesFast()
Entries_B = Background.GetEntriesFast()

WeightReader_S = TTreeReader("myTree", signal_file)
SignalWeight = TTreeReaderValue(ROOT.std.vector(float))(WeightReader_S, "weights_event_tree")

Lumi = 3000
cross_section_S = 0.00534700156855
cross_section_B = 232.3
sum_of_weights_S = 0.0
sum_of_weights_B = 0.0

while WeightReader_S.Next():
    sum_of_weights_S += SignalWeight.front()

WeightReader_B = TTreeReader("myTree", background_file)
BackgroundWeight = TTreeReaderValue(ROOT.std.vector(float))(WeightReader_B, "weights_event_tree")

while WeightReader_B.Next():
    sum_of_weights_B += BackgroundWeight.front()

Scale_S = (Lumi * cross_section_S * 1000) / (Entries_S * sum_of_weights_S)
Scale_B = (Lumi * cross_section_B * 1000) / (Entries_B * sum_of_weights_B)

ROOT.gROOT.SetBatch(ROOT.kTRUE)

# Define histograms
whjjmcVVH_pt_signal_hist = TH1F("whjjmcVVH_pt_signal_hist", "whjjmcVVH Pt;pt;frequency", 33, -100, 1300)
whjjmcVVH_eta_signal_hist = TH1F("whjjmcVVH_eta_signal_hist", "whjjmcVVH Eta;eta;frequency", 33, -7, 7)
whjjmcVVH_phi_signal_hist = TH1F("whjjmcVVH_phi_signal_hist", "whjjmcVVH Phi;phi;frequency", 33, -4, 4)
whjjmcVVH_m_signal_hist = TH1F("whjjmcVVH_m_signal_hist", "whjjmcVVH M;m;frequency", 33, -100, 6000)
HCand_pt_signal_hist = TH1F("HCand_pt_signal_hist", "HCand Pt;pt;frequency", 33, -2, 2000)
HCand_eta_signal_hist = TH1F("HCand_eta_signal_hist", "HCand Eta;eta;frequency", 33, -7, 7)
HCand_m_signal_hist = TH1F("HCand_m_signal_hist", "HCand M;m;frequency", 33, -2, 500)
WCand_pt_signal_hist = TH1F("WCand_pt_signal_hist", "WCand Pt;pt;frequency", 33, -2, 1500)
WCand_eta_signal_hist = TH1F("WCand_eta_signal_hist", "WCand Eta;eta;frequency", 33, -7, 7)
WCand_m_signal_hist = TH1F("WCand_m_signal_hist", "WCand M;m;frequency", 33, -2, 200)
whjjmcVVH_numRjetspt_signal_hist = TH1F("whjjmcVVH_numRjetspt_signal_hist", "whjjmcVVH NumRJetsPt;numRjetspt;frequency", 21, -1, 20)
whjjmcVVH_numRjetsHW_signal_hist = TH1F("whjjmcVVH_numRjetsHW_signal_hist", "whjjmcVVH NumRJetsHW;numRjetsHW;frequency", 11, -1, 10)
cuts_signal_hist = TH1F("cuts_signal_hist", "Cuts;cuts;frequency", 6, 0, 6)

whjjmcVVH_pt_background_hist = TH1F("whjjmcVVH_pt_background_hist", "whjjmcVVH Pt;pt;frequency", 33, -100, 1300)
whjjmcVVH_eta_background_hist = TH1F("whjjmcVVH_eta_background_hist", "whjjmcVVH Eta;eta;frequency", 33, -7, 7)
whjjmcVVH_phi_background_hist = TH1F("whjjmcVVH_phi_background_hist", "whjjmcVVH Phi;phi;frequency", 33, -4, 4)
whjjmcVVH_m_background_hist = TH1F("whjjmcVVH_m_background_hist", "whjjmcVVH M;m;frequency", 33, -100, 6000)
HCand_pt_background_hist = TH1F("HCand_pt_background_hist", "HCand Pt;pt;frequency", 33, -2, 2000)
HCand_eta_background_hist = TH1F("HCand_eta_background_hist", "HCand Eta;eta;frequency", 33, -7, 7)
HCand_m_background_hist = TH1F("HCand_m_background_hist", "HCand M;m;frequency", 33, -2, 200)
WCand_pt_background_hist = TH1F("WCand_pt_background_hist", "WCand Pt;pt;frequency", 33, -2, 1500)
WCand_eta_background_hist = TH1F("WCand_eta_background_hist", "WCand Eta;eta;frequency", 33, -7, 7)
WCand_m_background_hist = TH1F("WCand_m_background_hist", "WCand M;m;frequency", 33, -2, 300)
whjjmcVVH_numRjetspt_background_hist = TH1F("whjjmcVVH_numRjetspt_background_hist", "whjjmcVVH NumRJetsPt;numRjetspt;frequency", 21, -1, 20)
whjjmcVVH_numRjetsHW_background_hist = TH1F("whjjmcVVH_numRjetsHW_background_hist", "whjjmcVVH NumRJetsHW;numRjetsHW;frequency", 11, -1, 10)
cuts_background_hist = TH1F("cuts_background_hist", "Cuts;cuts;frequency", 6, 0, 6)

signal_counter = 0.0
background_counter = 0.0

# Event selection and histogram filling
def process_events(Tree, Scale, isSignal=True):
    counter = 0
    truth_counter = 0
    c1 = 0
    c2 = 0
    c3 = 0
    c4 = 0
    
    for event in Tree:
        if counter > 1000000000:
            break
        
        mhiggs = event.MH_tree
        if any(pt > 200 for pt in event.fatjetspt) and event.fatjetsmass.size() > 1 and any(eta < 2 for eta in event.fatjetseta) and any(Rpt > 20 for Rpt in event.smallRjetspt) and mhiggs > 70 and mhiggs < 140:
            cuts_signal_hist.Fill(1) if isSignal else cuts_background_hist.Fill(1)
            counter += 1
            c1 += 1
            
            i = 0
            H = TLorentzVector()
            W = TLorentzVector()

            mass = event.fatjetsmass
            H.SetPtEtaPhiM(event.fatjetspt[i], event.fatjetseta[i], event.fatjetsphi[i], mass[i])
            W.SetPtEtaPhiM(event.fatjetspt[(i+1)%2], event.fatjetseta[(i+1)%2], event.fatjetsphi[(i+1)%2], mass[(i+1)%2])

            jets_list = []
            pt20 = 0
            HW = 0
            total = len(event.smallRjetspt)
            for i in range(total):
                pt = event.smallRjetspt[i]
                eta = event.smallRjetseta[i]
                phi = event.smallRjetsphi[i]
                mass = event.smallRjetsmass[i]
                jet = TLorentzVector()
                jet.SetPtEtaPhiM(pt, eta, phi, mass)
        
                if pt > 20 and event.nsmallRjets > 1:
                    pt20 += 1
                if jet.DeltaR(H) > 1.2 and jet.DeltaR(W) > 1.2:
                    HW += 1
                jets_list.append(jet)
    
            cuts_signal_hist.Fill(2) if isSignal else cuts_background_hist.Fill(2)
            c2 += 1
    
            if event.largest_mjj > 200:
                cuts_signal_hist.Fill(3) if isSignal else cuts_background_hist.Fill(3)
                c3 += 1
    
                Higgsmass = 125
                if event.fatjetsmass > (Higgsmass-25) and event.fatjetsmass < (Higgsmass+25):
                    cuts_signal_hist.Fill(4) if isSignal else cuts_background_hist.Fill(4)
                    c4 += 1
    
                    if event.deltaR_HWW > 0.8 and event.nsmallRjets > 1 and event.largest_mjj > 300:
                        cuts_signal_hist.Fill(5) if isSignal else cuts_background_hist.Fill(5)
                        c5 += 1
                        whjjmcVVH_pt_signal_hist.Fill(H.Pt(), Scale * event.weights_event_tree.front()) if isSignal else whjjmcVVH_pt_background_hist.Fill(H.Pt(), Scale * event.weights_event_tree.front())
                        whjjmcVVH_eta_signal_hist.Fill(H.Eta(), Scale * event.weights_event_tree.front()) if isSignal else whjjmcVVH_eta_background_hist.Fill(H.Eta(), Scale * event.weights_event_tree.front())
                        whjjmcVVH_phi_signal_hist.Fill(H.Phi(), Scale * event.weights_event_tree.front()) if isSignal else whjjmcVVH_phi_background_hist.Fill(H.Phi(), Scale * event.weights_event_tree.front())
                        whjjmcVVH_m_signal_hist.Fill(H.M(), Scale * event.weights_event_tree.front()) if isSignal else whjjmcVVH_m_background_hist.Fill(H.M(), Scale * event.weights_event_tree.front())
                        HCand_pt_signal_hist.Fill(W.Pt(), Scale * event.weights_event_tree.front()) if isSignal else HCand_pt_background_hist.Fill(W.Pt(), Scale * event.weights_event_tree.front())
                        HCand_eta_signal_hist.Fill(W.Eta(), Scale * event.weights_event_tree.front()) if isSignal else HCand_eta_background_hist.Fill(W.Eta(), Scale * event.weights_event_tree.front())
                        HCand_m_signal_hist.Fill(W.M(), Scale * event.weights_event_tree.front()) if isSignal else HCand_m_background_hist.Fill(W.M(), Scale * event.weights_event_tree.front())
                        WCand_pt_signal_hist.Fill(W.Pt(), Scale * event.weights_event_tree.front()) if isSignal else WCand_pt_background_hist.Fill(W.Pt(), Scale * event.weights_event_tree.front())
                        WCand_eta_signal_hist.Fill(W.Eta(), Scale * event.weights_event_tree.front()) if isSignal else WCand_eta_background_hist.Fill(W.Eta(), Scale * event.weights_event_tree.front())
                        WCand_m_signal_hist.Fill(W.M(), Scale * event.weights_event_tree.front()) if isSignal else WCand_m_background_hist.Fill(W.M(), Scale * event.weights_event_tree.front())
                        whjjmcVVH_numRjetspt_signal_hist.Fill(pt20, Scale * event.weights_event_tree.front()) if isSignal else whjjmcVVH_numRjetspt_background_hist.Fill(pt20, Scale * event.weights_event_tree.front())
                        whjjmcVVH_numRjetsHW_signal_hist.Fill(HW, Scale * event.weights_event_tree.front()) if isSignal else whjjmcVVH_numRjetsHW_background_hist.Fill(HW, Scale * event.weights_event_tree.front())
                        truth_counter += 1
    
    return counter, c1, c2, c3, c4, c5

# Process Signal events
signal_counter, c1_SIGNAL, c2_SIGNAL, c3_SIGNAL, c4_SIGNAL, c5_SIGNAL = process_events(Signal, Scale_S, isSignal=True)

# Process Background events
background_counter, c1_BACKGROUND, c2_BACKGROUND, c3_BACKGROUND, c4_BACKGROUND, c5_BACKGROUND = process_events(Background, Scale_B, isSignal=False)

print(f"Signal Events: {signal_counter}")
print(f"Background Events: {background_counter}")
print(f"Cuts Passed by Signal: {c1_SIGNAL}, {c2_SIGNAL}, {c3_SIGNAL}, {c4_SIGNAL}, {c5_SIGNAL}")
print(f"Cuts Passed by Background: {c1_BACKGROUND}, {c2_BACKGROUND}, {c3_BACKGROUND}, {c4_BACKGROUND}, {c5_BACKGROUND}")

efficiency_signal = c4_SIGNAL / Entries_S
efficiency_background = c4_BACKGROUND / Entries_B

print(f"Signal Efficiency: {efficiency_signal}")
print(f"Background Efficiency: {efficiency_background}")
