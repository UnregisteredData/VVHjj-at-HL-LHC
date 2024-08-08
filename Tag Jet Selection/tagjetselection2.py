import sys
sys.path = [r'C:\root_v6.32.02\bin'] + sys.path

import math
from array import array
from itertools import combinations
import ROOT
from ROOT import TTreeReader, TTreeReaderValue, TFile, TH1F, TLorentzVector, TCanvas, TLegend, gStyle

# Open files
background_file = TFile.Open(r'C:\Users\hcds\ttjj.root')
Background = background_file['myTree']
signal_file = TFile.Open(r'C:\Users\hcds\VVHjj.root')
Signal = signal_file['myTree']

# Get entries
Entries_S = Signal.GetEntriesFast()
Entries_B = Background.GetEntriesFast()

# Initialize readers
WeightReader_S = TTreeReader("myTree", signal_file)
SignalWeight = TTreeReaderValue(ROOT.std.vector(float))(WeightReader_S, "weights_event_tree")

# Luminosity and cross-sections
Lumi = 3000
cross_section_S = 0.00534700156855
cross_section_B = 232.3

# Sum of weights
sum_of_weights_S = 0.0
sum_of_weights_B = 0.0

# Calculate sum of weights for signal
while WeightReader_S.Next():
    sum_of_weights_S += SignalWeight.front()

# Calculate sum of weights for background
WeightReader_B = TTreeReader("myTree", background_file)
BackgroundWeight = TTreeReaderValue(ROOT.std.vector(float))(WeightReader_B, "weights_event_tree")
while WeightReader_B.Next():
    sum_of_weights_B += BackgroundWeight.front()

# Scaling factors
Scale_S = (Lumi * cross_section_S * 1000) / (Entries_S * sum_of_weights_S)
Scale_B = (Lumi * cross_section_B * 1000) / (Entries_B * sum_of_weights_B)

# Set batch mode
ROOT.gROOT.SetBatch(ROOT.kTRUE)

# Initialize canvases and legends
canvas_names = [
    "whjjmcVVH_pt_hist", "whjjmcVVH_eta_hist", "whjjmcVVH_phi_hist", "whjjmcVVH_m_hist",
    "HCand_pt_hist", "HCand_eta_hist", "HCand_m_hist", "WCand_pt_hist", "WCand_eta_hist", "WCand_m_hist",
    "whjjmcVVH_numRjetspt_hist", "whjjmcVVH_numRjetsHW_hist", "cuts_hist", "efficiency_boosted_hist",
    "efficiency_pt_hist", "efficiency_deltaR_hist", "efficiency_eta_hist"
]
canvases = {name: TCanvas(name) for name in canvas_names}
legends = {f"t{i}": TLegend(0.75, 0.45, 0.9, 0.6) for i in range(1, 18)}

# Initialize histograms for signal and background
histogram_names = [
    "whjjmcVVH_pt", "whjjmcVVH_eta", "whjjmcVVH_phi", "whjjmcVVH_m", "HCand_pt", "HCand_eta", "HCand_m",
    "WCand_pt", "WCand_eta", "WCand_m", "whjjmcVVH_numRjetspt", "whjjmcVVH_numRjetsHW", "cuts"
]
hist_signal = {name: TH1F(f"{name}_signal_hist", f"{name} Signal;{name};frequency", 33, -100, 1300) for name in histogram_names}
hist_background = {name: TH1F(f"{name}_background_hist", f"{name} Background;{name};frequency", 33, -100, 1300) for name in histogram_names}

# Signal and background counters
signal_counter = 0.0
background_counter = 0.0

# Function to process events
def process_events(events, scale, is_signal=True):
    counter = 0
    truth_counter = 0
    c1, c2, c3, c4 = 0, 0, 0, 0
    
    for event in events:
        if counter > 1000:
            break
        
        mhiggs = event.MH_tree
        if (any(pt > 200 for pt in event.fatjetspt) and event.fatjetsmass.size() > 1 and 
            any(eta < 2 for eta in event.fatjetseta) and any(Rpt > 20 for Rpt in event.smallRjetspt) and 
            70 < mhiggs < 140):
            
            if is_signal:
                hist_signal['cuts'].Fill(1)
            else:
                hist_background['cuts'].Fill(1)
                
            counter += 1
            c1 += 1
            
            i = 0
            H = TLorentzVector()
            W = TLorentzVector()
            
            mass = event.fatjetsmass
            H.SetPtEtaPhiM(event.fatjetspt[i], event.fatjetseta[i], event.fatjetsphi[i], mass[i])
            W.SetPtEtaPhiM(event.fatjetspt[(i+1)%2], event.fatjetseta[(i+1)%2], event.fatjetsphi[(i+1)%2], mass[(i+1)%2])
            
            truthjets_list = []
            jets_list = []
            pt20, HW = 0, 0
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
                    c2 += 1
                    if is_signal:
                        hist_signal['cuts'].Fill(2)
                    else:
                        hist_background['cuts'].Fill(2)
                    
                    if jet.DeltaR(H) > 1 and jet.DeltaR(W) > 1:
                        HW += 1
                        c3 += 1
                        if is_signal:
                            hist_signal['cuts'].Fill(3)
                        else:
                            hist_background['cuts'].Fill(3)
                        
                        if ((eta > H.Eta() and eta > W.Eta()) or (eta < H.Eta() and eta < W.Eta())):
                            c4 += 1
                            if is_signal:
                                hist_signal['cuts'].Fill(4)
                            else:
                                hist_background['cuts'].Fill(4)
                            
                            jets_list.append(jet)
            
            if len(jets_list) > 1:
                pairs = list(combinations(jets_list, 2))
                total_pairs = len(pairs)
                
                maximum = 0
                for j in range(total_pairs):
                    jet1 = pairs[j][0]
                    jet2 = pairs[j][1]
                    mass = jet1.M() + jet2.M()
                    if mass > maximum:
                        maximum = mass
                        maximum_index = j
                
                FINAL_JET_1 = pairs[maximum_index][0]
                FINAL_JET_2 = pairs[maximum_index][1]
                
                whjjmcVVH = H + W + FINAL_JET_1 + FINAL_JET_2
                
                if is_signal:
                    hist_signal['whjjmcVVH_pt'].Fill(whjjmcVVH.Pt(), scale)
                    hist_signal['whjjmcVVH_eta'].Fill(whjjmcVVH.Eta(), scale)
                    hist_signal['whjjmcVVH_phi'].Fill(whjjmcVVH.Phi(), scale)
                    hist_signal['whjjmcVVH_m'].Fill(whjjmcVVH.M(), scale)
                    hist_signal['HCand_pt'].Fill(H.Pt(), scale)
                    hist_signal['HCand_eta'].Fill(H.Eta(), scale)
                    hist_signal['HCand_m'].Fill(H.M(), scale)
                    hist_signal['WCand_pt'].Fill(W.Pt(), scale)
                    hist_signal['WCand_eta'].Fill(W.Eta(), scale)
                    hist_signal['WCand_m'].Fill(W.M(), scale)
                    hist_signal['whjjmcVVH_numRjetspt'].Fill(pt20, scale)
                    hist_signal['whjjmcVVH_numRjetsHW'].Fill(HW, scale)
                else:
                    hist_background['whjjmcVVH_pt'].Fill(whjjmcVVH.Pt(), scale)
                    hist_background['whjjmcVVH_eta'].Fill(whjjmcVVH.Eta(), scale)
                    hist_background['whjjmcVVH_phi'].Fill(whjjmcVVH.Phi(), scale)
                    hist_background['whjjmcVVH_m'].Fill(whjjmcVVH.M(), scale)
                    hist_background['HCand_pt'].Fill(H.Pt(), scale)
                    hist_background['HCand_eta'].Fill(H.Eta(), scale)
                    hist_background['HCand_m'].Fill(H.M(), scale)
                    hist_background['WCand_pt'].Fill(W.Pt(), scale)
                    hist_background['WCand_eta'].Fill(W.Eta(), scale)
                    hist_background['WCand_m'].Fill(W.M(), scale)
                    hist_background['whjjmcVVH_numRjetspt'].Fill(pt20, scale)
                    hist_background['whjjmcVVH_numRjetsHW'].Fill(HW, scale)
    
    return counter, c1, c2, c3, c4

# Process signal and background events
signal_counter, c1_S, c2_S, c3_S, c4_S = process_events(Signal, Scale_S, is_signal=True)
background_counter, c1_B, c2_B, c3_B, c4_B = process_events(Background, Scale_B, is_signal=False)

# Total events for initial efficiencies
total_events_signal = signal_counter
total_events_background = background_counter

# Efficiencies for signal
efficiency_c1_S = c1_S / total_events_signal if total_events_signal != 0 else 0
efficiency_c2_S = c2_S / c1_S if c1_S != 0 else 0
efficiency_c3_S = c3_S / c2_S if c2_S != 0 else 0
efficiency_c4_S = c4_S / c3_S if c3_S != 0 else 0

# Efficiencies for background
efficiency_c1_B = c1_B / total_events_background if total_events_background != 0 else 0
efficiency_c2_B = c2_B / c1_B if c1_B != 0 else 0
efficiency_c3_B = c3_B / c2_B if c2_B != 0 else 0
efficiency_c4_B = c4_B / c3_B if c3_B != 0 else 0

# Print significance and efficiency results
significance = signal_counter / math.sqrt(background_counter) if background_counter != 0 else 0
print(f"Significance: {significance:.2f}")
print(f"Number of signal events: {signal_counter}")
print(f"Number of background events: {background_counter}")
print("Efficiencies:")
print(f"Cut 1 (signal): {efficiency_c1_S:.2f}")
print(f"Cut 2 (signal): {efficiency_c2_S:.2f}")
print(f"Cut 3 (signal): {efficiency_c3_S:.2f}")
print(f"Cut 4 (signal): {efficiency_c4_S:.2f}")
print(f"Cut 1 (background): {efficiency_c1_B:.2f}")
print(f"Cut 2 (background): {efficiency_c2_B:.2f}")
print(f"Cut 3 (background): {efficiency_c3_B:.2f}")
print(f"Cut 4 (background): {efficiency_c4_B:.2f}")

# Draw histograms
for hist_name in hist_signal:
    canvases[hist_name + "_hist"].cd()
    hist_signal[hist_name].SetLineColor(ROOT.kRed)
    hist_signal[hist_name].Draw()
    hist_background[hist_name].SetLineColor(ROOT.kBlue)
    hist_background[hist_name].Draw("SAME")
    legends["t1"].AddEntry(hist_signal[hist_name], "Signal", "l")
    legends["t1"].AddEntry(hist_background[hist_name], "Background", "l")
    legends["t1"].Draw()

# Save canvases
for name, canvas in canvases.items():
    canvas.SaveAs(f"C:\\Users\\hcds\\tag_selection_images\\{name}.png")

