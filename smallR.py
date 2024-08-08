import sys
sys.path = [r'C:\root_v6.32.02\bin'] + sys.path

import math
from array import array
import numpy as np

from itertools import combinations

import ROOT
from ROOT import TTreeReader, TTreeReaderValue, TFile, TH1F, TLorentzVector, TH1D, TCanvas, TLegend, gStyle

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

whjjmcVVH_pt_hist = TCanvas()
whjjmcVVH_eta_hist = TCanvas()
whjjmcVVH_phi_hist = TCanvas()
whjjmcVVH_m_hist = TCanvas()
HCand_pt_hist = TCanvas()
HCand_eta_hist = TCanvas()
HCand_m_hist = TCanvas()
WCand_pt_hist = TCanvas()
WCand_eta_hist = TCanvas()
WCand_m_hist = TCanvas()
whjjmcVVH_numRjetspt_hist = TCanvas()
whjjmcVVH_numRjetsHW_hist = TCanvas()
cuts_hist = TCanvas()
tagjet1_pt_hist = TCanvas()
tagjet1_eta_hist = TCanvas()
tagjet2_pt_hist = TCanvas()
tagjet2_eta_hist = TCanvas()
whjjmcVVHjj_hist = TCanvas()
whjjmcttjj_hist = TCanvas()

t1 = TLegend(0.75, 0.45, 0.9, 0.6)
t2 = TLegend(0.75, 0.45, 0.9, 0.6)
t3 = TLegend(0.75, 0.45, 0.9, 0.6)
t4 = TLegend(0.75, 0.45, 0.9, 0.6)
t5 = TLegend(0.75, 0.45, 0.9, 0.6)
t6 = TLegend(0.75, 0.45, 0.9, 0.6)
t7 = TLegend(0.75, 0.45, 0.9, 0.6)
t8 = TLegend(0.75, 0.45, 0.9, 0.6)
t9 = TLegend(0.75, 0.45, 0.9, 0.6)
t10 = TLegend(0.75, 0.45, 0.9, 0.6)
t11 = TLegend(0.75, 0.45, 0.9, 0.6)
t12 = TLegend(0.75, 0.45, 0.9, 0.6)
t13 = TLegend(0.75, 0.45, 0.9, 0.6)
t14 = TLegend(0.75, 0.45, 0.9, 0.6)
t15 = TLegend(0.75, 0.45, 0.9, 0.6)
t16 = TLegend(0.75, 0.45, 0.9, 0.6)
t17 = TLegend(0.75, 0.45, 0.9, 0.6)
t18 = TLegend(0.75, 0.45, 0.9, 0.6)


bins_C = np.array([500, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700,
                   1800, 1900, 2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700,
                   2800, 2900, 3000, 3100, 3200, 3300, 3400, 3500, 4000, 5000],
                  dtype = 'float64')

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
tagjet1_pt_signal_hist = TH1F("tagjet1_pt_signal_hist", "Tag Jet 1 Pt;pt;frequency", 33, 0, 300)
tagjet1_eta_signal_hist = TH1F("tagjet1_eta_signal_hist", "Tag Jet 1 Eta;eta;frequency", 33, -5, 5)
tagjet2_pt_signal_hist = TH1F("tagjet2_pt_signal_hist", "Tag Jet 2 Pt;pt;frequency", 33, 0, 150)
tagjet2_eta_signal_hist = TH1F("tagjet2_eta_signal_hist", "Tag Jet 2 Eta;eta;frequency", 33, -5, 5)
whjjmcVVHjj = TH1F("whjjmcVVHjj", "WHjj Mass [GeV]", len(bins_C)-1, bins_C)



whjjmcVVH_pt_background_hist = TH1F("whjjmcVVH_pt_background_hist", "whjjmcVVH Pt;pt;frequency", 33, -100, 1300)
whjjmcVVH_eta_background_hist = TH1F("whjjmcVVH_eta_background_hist", "whjjmcVVH Eta;eta;frequency", 33, -7, 7)
whjjmcVVH_phi_background_hist = TH1F("whjjmcVVH_phi_background_hist", "whjjmcVVH Phi;phi;frequency", 33, -4, 4)
whjjmcVVH_m_background_hist = TH1F("whjjmcVVH_m_background_hist", "whjjmcVVH M;m;frequency", 33, -100, 6000)
HCand_pt_background_hist = TH1F("HCand_pt_background_hist", "HCand Pt;pt;frequency", 33, -2, 2000)
HCand_eta_background_hist = TH1F("HCand_eta_background_hist", "HCand Eta;eta;frequency", 33, -7, 7)
HCand_m_background_hist = TH1F("HCand_m_background_hist", "HCand M;m;frequency", 33, -2, 500)
WCand_pt_background_hist = TH1F("WCand_pt_background_hist", "WCand Pt;pt;frequency", 33, -2, 1500)
WCand_eta_background_hist = TH1F("WCand_eta_background_hist", "WCand Eta;eta;frequency", 33, -7, 7)
WCand_m_background_hist = TH1F("WCand_m_background_hist", "WCand M;m;frequency", 33, -2, 300)
whjjmcVVH_numRjetspt_background_hist = TH1F("whjjmcVVH_numRjetspt_background_hist", "whjjmcVVH NumRJetsPt;numRjetspt;frequency", 21, -1, 20)
whjjmcVVH_numRjetsHW_background_hist = TH1F("whjjmcVVH_numRjetsHW_background_hist", "whjjmcVVH NumRJetsHW;numRjetsHW;frequency", 11, -1, 10)
cuts_background_hist = TH1F("cuts_background_hist", "Cuts;cuts;frequency", 6, 0, 6)
tagjet1_pt_background_hist = TH1F("tagjet1_pt_background_hist", "Tag Jet 1 Pt;pt;frequency", 33, 0, 300)
tagjet1_eta_background_hist = TH1F("tagjet1_eta_background_hist", "Tag Jet 1 Eta;eta;frequency", 33, -5, 5)
tagjet2_pt_background_hist = TH1F("tagjet2_pt_background_hist", "Tag Jet 2 Pt;pt;frequency", 33, 0, 150)
tagjet2_eta_background_hist = TH1F("tagjet2_eta_background_hist", "Tag Jet 2 Eta;eta;frequency", 33, -5, 5)
whjjmcttjj = TH1F("whjjmcttjj", "WHjj Mass [GeV]", len(bins_C)-1, bins_C)

'''
print('whjjmcVVHjj')
for bin_num in range(1,len(bins_C)):
    print(whjjmcVVHjj.GetBinWidth(bin_num))

print("whjjmcttjj")
for bin_num in range(1,len(bins_C)):
    print(whjjmcttjj.GetBinWidth(bin_num))
'''


signal_counter = 0.0
background_counter = 0.0

counter = 0
signal_truth = 0
c1_SIGNAL = 0
c2_SIGNAL = 0
c3_SIGNAL = 0
c4_SIGNAL = 0

for event in Signal:
    if counter > 10000000:
        break

    mhiggs = Signal.MH_tree
    if any(pt > 200 for pt in Signal.fatjetspt) and Signal.fatjetsmass.size() > 1 and any(eta < 2 for eta in Signal.fatjetseta) and any(Rpt > 20 for Rpt in Signal.smallRjetspt) and 70 < mhiggs < 140:
        cuts_signal_hist.Fill(1)
        counter += 1
        c1_SIGNAL += 1
        
        i = 0
        H = TLorentzVector()
        W = TLorentzVector()

        H.SetPtEtaPhiM(Signal.PTH_tree, Signal.fatjetseta[i], Signal.fatjetsphi[i], Signal.MH_tree)
        W.SetPtEtaPhiM(Signal.PTW_tree, Signal.fatjetseta[(i+1)%2], Signal.fatjetsphi[(i+1)%2], Signal.MV_tree)

        truthjets_list = []
        jets_list = []
        temp_1 = []
        pt20 = 0
        HW = 0
        total = len(Signal.smallRjetspt)
        pt_tracker = 0
        deltaR_tracker = 0
        eta_tracker = 0
        for i in range(total):
            pt = Signal.smallRjetspt[i]
            eta = Signal.smallRjetseta[i]
            phi = Signal.smallRjetsphi[i]
            mass = Signal.smallRjetsmass[i]
            jet = TLorentzVector()
            jet.SetPtEtaPhiM(pt, eta, phi, mass)
    
            if pt > 20 and Signal.nsmallRjets > 1:
                pt20 += 1
                if pt_tracker == 0:
                    c2_SIGNAL += 1
                    pt_tracker += 1
                cuts_signal_hist.Fill(2)

                if jet.DeltaR(H) > 1 and jet.DeltaR(W) > 1:
                    HW += 1
                    if deltaR_tracker == 0:
                        c3_SIGNAL += 1
                        deltaR_tracker += 1
                    cuts_signal_hist.Fill(3)

                    if (eta > H.Eta() and eta > W.Eta()) or (eta < H.Eta() and eta < W.Eta()):
                        if eta_tracker == 0:
                            c4_SIGNAL += 1
                            eta_tracker += 1
                        cuts_signal_hist.Fill(4)
                        jets_list.append(jet)
                        temp_1 = jets_list

        jets_list = temp_1
        if len(jets_list) > 1:
            pairs = list(combinations(jets_list, 2))
            total_pairs = len(pairs)

            maximum = 0
            maximum_index = 0
            for j in range(total_pairs):
                jet1 = pairs[j][0]
                jet2 = pairs[j][1]
                mass = jet1.M() + jet2.M()
                if mass > maximum:
                    maximum = mass
                    maximum_index = j

            global FINAL_JET_1
            global FINAL_JET_2
                    
            FINAL_JET_1 = pairs[maximum_index][0]
            FINAL_JET_2 = pairs[maximum_index][1]

            whjjmcVVHjj_sys = TLorentzVector()
            whjjmcVVHjj_sys = H + W + FINAL_JET_1 + FINAL_JET_2
                    
            sys_mass = whjjmcVVHjj_sys.M()
        
            whjjmcVVH_pt_signal_hist.Fill(whjjmcVVHjj_sys.Pt())
            whjjmcVVH_eta_signal_hist.Fill(whjjmcVVHjj_sys.Eta())
            whjjmcVVH_phi_signal_hist.Fill(whjjmcVVHjj_sys.Phi())
            whjjmcVVH_m_signal_hist.Fill(sys_mass)
            whjjmcVVH_numRjetspt_signal_hist.Fill(pt20)
            whjjmcVVH_numRjetsHW_signal_hist.Fill(HW)
            HCand_pt_signal_hist.Fill(H.Pt())
            HCand_eta_signal_hist.Fill(H.Eta())
            HCand_m_signal_hist.Fill(H.M())
            WCand_pt_signal_hist.Fill(W.Pt())
            WCand_eta_signal_hist.Fill(W.Eta())
            WCand_m_signal_hist.Fill(W.M())
            tagjet1_pt_signal_hist.Fill(FINAL_JET_1.Pt())
            tagjet1_eta_signal_hist.Fill(FINAL_JET_1.Eta())
            tagjet2_pt_signal_hist.Fill(FINAL_JET_2.Pt())
            tagjet2_eta_signal_hist.Fill(FINAL_JET_2.Eta())
            whjjmcVVHjj.Fill(sys_mass)
            

            signal_counter += 1

                                
        total = len(Signal.truthjetspt)
        for i in range(total):
            pt_truth = Signal.truthjetspt[i]
            eta_truth = Signal.truthjetseta[i]
            phi_truth = Signal.truthjetsphi[i]
            mass_truth = Signal.truthjetsmass[i]
            truth_jet = TLorentzVector()
            truth_jet.SetPtEtaPhiM(pt_truth, eta_truth, phi_truth, mass_truth)

            if pt_truth > 20 and Signal.truthjetseta.size() > 1 and truth_jet.DeltaR(H) > 1 and truth_jet.DeltaR(W) > 1 and ((eta_truth > H.Eta() and eta_truth > W.Eta()) or (eta_truth < H.Eta() and eta_truth< W.Eta())):
                truthjets_list.append(truth_jet)
                temp_2 = truthjets_list

        truthjets_list = temp_2
        if len(truthjets_list) > 1:
            pairs = list(combinations(truthjets_list, 2))
            total_pairs = len(pairs)

            mass = 0
            maximum = 0
            for j in range(total_pairs):
                jet1 = pairs[j][0]
                jet2 = pairs[j][1]
                mass = jet1.M() + jet2.M()

                if mass > maximum:
                    maximum = mass
                    maximum_index = j

            FINAL_TRUTH_JET_1 = pairs[maximum_index][0]
            FINAL_TRUTH_JET_2 = pairs[maximum_index][1]

            if (FINAL_TRUTH_JET_1.DeltaR(FINAL_JET_1) <= 0.4 or FINAL_TRUTH_JET_1.DeltaR(FINAL_JET_2) <= 0.4) and (FINAL_TRUTH_JET_2.DeltaR(FINAL_JET_1) <= 0.4 or FINAL_TRUTH_JET_2.DeltaR(FINAL_JET_2) <= 0.4):
                signal_truth += 1
print("Signal Done.")

counter = 0
background_truth = 0
c1_BACKGROUND = 0
c2_BACKGROUND = 0
c3_BACKGROUND = 0
c4_BACKGROUND = 0
    
for event in Background:
    if counter > 10000000:
        break
    mhiggs = Background.MH_tree
    if any(pt > 200 for pt in Background.fatjetspt) and Background.fatjetsmass.size() > 1 and any(eta < 2 for eta in Background.fatjetseta) and any(Rpt > 20 for Rpt in Background.smallRjetspt) and mhiggs > 70 and mhiggs < 140:
        cuts_background_hist.Fill(1)
        counter += 1
        c1_BACKGROUND += 1
        
        i = 0
        H = TLorentzVector()
        W = TLorentzVector()

        H.SetPtEtaPhiM(Background.PTH_tree, Background.fatjetseta[i], Background.fatjetsphi[i], Background.MH_tree)
        W.SetPtEtaPhiM(Background.PTW_tree, Background.fatjetseta[(i+1)%2], Background.fatjetsphi[(i+1)%2], Background.MV_tree)

        truthjets_list = []
        jets_list = []
        temp_1 = []
        pt20 = 0
        HW = 0
        total = len(Background.smallRjetspt)
        pt_tracker = 0
        deltaR_tracker = 0
        eta_tracker = 0
        for i in range(total):
            pt = Background.smallRjetspt[i]
            eta = Background.smallRjetseta[i]
            phi = Background.smallRjetsphi[i]
            mass = Background.smallRjetsmass[i]
            jet = TLorentzVector()
            jet.SetPtEtaPhiM(pt, eta, phi, mass)
    
            if pt > 20 and Background.nsmallRjets > 1:
                pt20 += 1
                if pt_tracker == 0:
                    c2_BACKGROUND += 1
                    pt_tracker += 1
                cuts_background_hist.Fill(2)

                if jet.DeltaR(H) > 1 and jet.DeltaR(W) > 1:
                    HW += 1
                    if deltaR_tracker == 0:
                        c3_BACKGROUND += 1
                        deltaR_tracker += 1
                    cuts_background_hist.Fill(3)

                    if (eta > H.Eta() and eta > W.Eta()) or (eta < H.Eta() and eta < W.Eta()):
                        if eta_tracker == 0:
                            c4_BACKGROUND += 1
                            eta_tracker += 1
                        cuts_background_hist.Fill(4)
                        jets_list.append(jet)
                        temp_1 = jets_list

        jets_list = temp_1
        if len(jets_list) > 1:
            pairs = list(combinations(jets_list, 2))
            total_pairs = len(pairs)

            maximum = 0
            maximum_index = 0
            for j in range(total_pairs):
                jet1 = pairs[j][0]
                jet2 = pairs[j][1]
                mass = jet1.M() + jet2.M()
                if mass > maximum:
                    maximum = mass
                    maximum_index = j
                
            FINAL_JET_1 = pairs[maximum_index][0]
            FINAL_JET_2 = pairs[maximum_index][1]

            whjjmcttjj_sys = TLorentzVector()
            whjjmcttjj_sys = H + W + FINAL_JET_1 + FINAL_JET_2

            sys_mass = whjjmcttjj_sys.M()
                    
            whjjmcVVH_pt_background_hist.Fill(whjjmcttjj_sys.Pt())
            whjjmcVVH_eta_background_hist.Fill(whjjmcttjj_sys.Eta())
            whjjmcVVH_phi_background_hist.Fill(whjjmcttjj_sys.Phi())
            whjjmcVVH_m_background_hist.Fill(sys_mass)
            whjjmcVVH_numRjetspt_background_hist.Fill(pt20)
            whjjmcVVH_numRjetsHW_background_hist.Fill(HW)
            HCand_pt_background_hist.Fill(H.Pt())
            HCand_eta_background_hist.Fill(H.Eta())
            HCand_m_background_hist.Fill(H.M())
            WCand_pt_background_hist.Fill(W.Pt())
            WCand_eta_background_hist.Fill(W.Eta())
            WCand_m_background_hist.Fill(W.M())
            tagjet1_pt_background_hist.Fill(FINAL_JET_1.Pt())
            tagjet1_eta_background_hist.Fill(FINAL_JET_1.Eta())
            tagjet2_pt_background_hist.Fill(FINAL_JET_2.Pt())
            tagjet2_eta_background_hist.Fill(FINAL_JET_2.Eta())
            whjjmcttjj.Fill(sys_mass)

            background_counter += 1

                                
        total = len(Background.truthjetspt)
        for i in range(total):
            pt_truth = Background.truthjetspt[i]
            eta_truth = Background.truthjetseta[i]
            phi_truth = Background.truthjetsphi[i]
            mass_truth = Background.truthjetsmass[i]
            truth_jet = TLorentzVector()
            truth_jet.SetPtEtaPhiM(pt_truth, eta_truth, phi_truth, mass_truth)

            if pt_truth > 20 and Background.truthjetseta.size() > 1 and truth_jet.DeltaR(H) > 1 and truth_jet.DeltaR(W) > 1 and ((eta_truth > H.Eta() and eta_truth > W.Eta()) or (eta_truth < H.Eta() and eta_truth< W.Eta())):
                truthjets_list.append(truth_jet)
                temp_2 = truthjets_list

        truthjets_list = temp_2
        if len(truthjets_list) > 1:
            pairs = list(combinations(truthjets_list, 2))
            total_pairs = len(pairs)

            mass = 0
            maximum = 0
            for j in range(total_pairs):
                jet1 = pairs[j][0]
                jet2 = pairs[j][1]
                mass = jet1.M() + jet2.M()
                
                if mass > maximum:
                    maximum = mass
                    maximum_index = j

            FINAL_TRUTH_JET_1 = pairs[maximum_index][0]
            FINAL_TRUTH_JET_2 = pairs[maximum_index][1]

            if (FINAL_TRUTH_JET_1.DeltaR(FINAL_JET_1) <= 0.4 or FINAL_TRUTH_JET_1.DeltaR(FINAL_JET_2) <= 0.4) and (FINAL_TRUTH_JET_2.DeltaR(FINAL_JET_1) <= 0.4 or FINAL_TRUTH_JET_2.DeltaR(FINAL_JET_2) <= 0.4):
                background_truth += 1




print('Background Done.')

print(f"Significance: {signal_counter/math.sqrt(background_counter)}")

print(f"Signal Truth Jets: {signal_truth}")
print(f"Signal Passed: {int(signal_counter)}")
print(f"Background Truth Jets: {background_truth}")
print(f"Background Passed: {int(background_counter)}")


print(f"Boosted Signal Efficiency: {float(c1_SIGNAL/Entries_S)}")
print(f"Boosted Background Efficiency: {float(c1_BACKGROUND/Entries_B)}")
print(f"Pt Cut Signal Efficiency: {float((c2_SIGNAL)/c1_SIGNAL)}")
print(f"Pt Cut Background Efficiency: {float((c2_BACKGROUND)/c1_BACKGROUND)}")
print(f"HW Cut Signal Efficiency: {float((c3_SIGNAL)/c2_SIGNAL)}")
print(f"HW Cut Background Efficiency: {float((c3_BACKGROUND)/c2_BACKGROUND)}")
print(f"Eta Cut Signal Efficiency: {float((c4_SIGNAL)/c3_SIGNAL)}")
print(f"Eta Cut Background Efficiency: {float((c4_BACKGROUND)/c3_BACKGROUND)}")
print(f"Overall Signal Efficiency: {float(c4_SIGNAL/Entries_S)}")
print(f"Overall Background Efficiency: {float(c4_BACKGROUND/Entries_B)}")


#output_file = TFile(r'C:\Users\hcds\tag_selection.root', 'RECREATE')
output_file = TFile(r'C:\Users\hcds\tag_selection.root', 'RECREATE')

gStyle.SetOptStat(0)


histograms = [(whjjmcVVH_pt_signal_hist, whjjmcVVH_pt_background_hist),
              (whjjmcVVH_eta_signal_hist, whjjmcVVH_eta_background_hist),
              (whjjmcVVH_phi_signal_hist, whjjmcVVH_phi_background_hist),
              (whjjmcVVH_m_signal_hist, whjjmcVVH_m_background_hist),
              (HCand_pt_signal_hist, HCand_pt_background_hist),
              (HCand_eta_signal_hist, HCand_eta_background_hist),
              (HCand_m_signal_hist, HCand_m_background_hist),
              (WCand_pt_signal_hist, WCand_pt_background_hist),
              (WCand_eta_signal_hist, WCand_eta_background_hist),
              (WCand_m_signal_hist, WCand_m_background_hist),
              (whjjmcVVH_numRjetspt_signal_hist, whjjmcVVH_numRjetspt_background_hist),
              (whjjmcVVH_numRjetsHW_signal_hist, whjjmcVVH_numRjetsHW_background_hist),
              (cuts_signal_hist, cuts_background_hist),
              (tagjet1_pt_signal_hist, tagjet1_pt_background_hist),
              (tagjet1_eta_signal_hist, tagjet1_eta_background_hist),
              (tagjet2_pt_signal_hist, tagjet2_pt_background_hist),
              (tagjet2_eta_signal_hist, tagjet2_eta_background_hist)]

canvases = [whjjmcVVH_pt_hist, whjjmcVVH_eta_hist, whjjmcVVH_phi_hist,
            whjjmcVVH_m_hist, HCand_pt_hist, HCand_eta_hist, HCand_m_hist,
            WCand_pt_hist, WCand_eta_hist, WCand_m_hist,
            whjjmcVVH_numRjetspt_hist, whjjmcVVH_numRjetsHW_hist, cuts_hist,
            tagjet1_pt_hist, tagjet1_eta_hist, tagjet2_pt_hist, tagjet2_eta_hist]

canvas_names = ["whjjmcVVH Pt", "whjjmcVVH Eta", "whjjmcVVH Phi", "whjjmcVVH M",
                "H Candidate Pt", "H Candidate Eta", "H Candidate M",
                "W Candidate Pt", "W Candidate Eta", "W Candidate M",
                "Number of R Jets Post Pt Cut", "Number of R Jets Post HW Delta R Cut",
                "Remaining Jets at Each Cut", "Tag Jet 1 Pt", "Tag Jet 1 Eta",
                "Tag Jet 2 Pt", "Tag Jet 2 Eta"]
                
TLegends = [t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15,
            t16, t17]

rebin = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1]

def draw(histograms, canvases, rebin, canvas_names):
    for i in range(len(histograms)):
        signal = histograms[i][0]
        background = histograms[i][1]
        canvases[i].cd()

        if rebin[i] == 1:
            signal.Rebin(3)
            background.Rebin(3)

        background.SetLineColor(ROOT.kRed)
        background.SetLineStyle(1)
        background.Draw()
        signal.SetLineColor(ROOT.kBlue)
        signal.SetLineStyle(1)
        signal.Draw('same')

        TLegends[i].AddEntry(signal, "Signal", "l")
        TLegends[i].AddEntry(background, "Background", "l")
        TLegends[i].Draw()

        canvases[i].SetName(canvas_names[i])
        canvases[i].Write()
        
        

draw(histograms, canvases, rebin, canvas_names)

output_file.Close()

output_file = TFile(r'C:\Users\hcds\Fit_Copy\Fit_input.root', 'RECREATE')

whjjmcVVHjj_hist.cd()
whjjmcVVHjj.Write()

whjjmcttjj_hist.cd()
whjjmcttjj.Write()


output_file.Close()
#background_file.Close()
#signal_file.Close()



