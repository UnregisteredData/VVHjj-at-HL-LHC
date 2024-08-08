import sys
sys.path = [r'C:\root_v6.32.02\bin'] + sys.path

import ROOT
from ROOT import TTreeReader, TTreeReaderValue, TFile, TH1F, TLorentzVector

Lumi = 3000
cross_section_S = 0.00534700156855
cross_section_B = 232.3

#Signals = [0.0] * 60
#Backgrounds = [0.0] * 60
sum_of_weights_S = 0.0
sum_of_weights_B = 0.0

VVHjj_file = ROOT.TFile.Open(r"C:\Users\hcds\VVHjj.root")
ttjj_file = ROOT.TFile.Open(r"C:\Users\hcds\ttjj.root")

Signal = VVHjj_file['myTree']
Background = ttjj_file['myTree']
Entries_S = Signal.GetEntriesFast()
Entries_B = Background.GetEntriesFast()

WeightReader_S = TTreeReader("myTree", VVHjj_file)
SignalWeight = TTreeReaderValue(ROOT.std.vector(float))(WeightReader_S, "weights_event_tree")

while WeightReader_S.Next():
    sum_of_weights_S += SignalWeight.front()
print(f"sum of weights {sum_of_weights_S}")

WeightReader_B = TTreeReader("myTree", ttjj_file)
BackgroundWeight = TTreeReaderValue(ROOT.std.vector(float))(WeightReader_B, "weights_event_tree")

while WeightReader_B.Next():
    sum_of_weights_B += BackgroundWeight.front()
print(f"sum of b weights {sum_of_weights_B}")


Scale_S = (Lumi * cross_section_S * 1000) / (Entries_S * sum_of_weights_S)
Scale_B = (Lumi * cross_section_B * 1000) / (Entries_B * sum_of_weights_B)

print(f"scale s {Scale_S}")
print(f"scale b {Scale_B}")

S_TruthTagJet1Pt_hist = TH1F("S_TruthTagJet1Pt", "Title;X-axis;Y-axis", 100, 0, 500)
B1_TagJet1HCandDeltaR_hist = TH1F("B1_TagJet1HCandDeltaR", "Title;X-axis;Y-axis", 100, 0, 5)

for event in Signal:
    S_TruthTagJet1Pt_hist.Fill(event.truthjetspt.front(), SignalWeight.front() * Scale_S)

for event in Background:
    mass = Background.fatjetsmass
    if mass.size() > 1:
        i = 0
        H = TLorentzVector()
        if abs(mass[0]-125) > abs(mass[1]-125):
            i = 1
        H.SetPtEtaPhiM(Background.fatjetspt[i], Background.fatjetseta[i], Background.fatjetsphi[i], mass[i])
        tagjet1 = TLorentzVector()
        tagjet1.SetPtEtaPhiM(Background.tagjet1pt, Background.tagjet1eta, Background.tagjet1phi, Background.tagjet1mass) 
        B1_TagJet1HCandDeltaR_hist.Fill(tagjet1.DeltaR(H), BackgroundWeight.front() * Scale_B)

output_file = TFile(r"C:\Users\hcds\significance.root", "RECREATE")
S_TruthTagJet1Pt_hist.Write()
B1_TagJet1HCandDeltaR_hist.Write()
output_file.Close()

# Close the input files
VVHjj_file.Close()
ttjj_file.Close()
