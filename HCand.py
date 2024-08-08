import sys
sys.path = [r'C:\root_v6.32.02\bin'] + sys.path

import ROOT
from ROOT import TTreeReader, TTreeReaderValue, TFile, TH1F, TLorentzVector, TH1D

chain = TFile.Open(r'C:\Users\hcds\VVHjj.root')
Signal = chain['myTree']

MVHjjPt_hist = TH1F("MVHjjPt_hist", "MVHjj Pt;pt;frequency", 100, -100, 2000)
MVHjjEta_hist = TH1F("MVHjjEta_hist", "MVHjj Eta;eta;frequency", 100, -7, 7)
MVHjjPhi_hist = TH1F("MVHjjPhi_hist", "MVHjj Phi;phi;frequency", 100, -4, 4)
MVHjjM_hist = TH1F("MVHjjM_hist", "MVHjj M;m;frequency", 100, -100, 6000)

for event in Signal:
    mass = Signal.fatjetsmass
    if mass.size() > 1:
        i = 0
        H = TLorentzVector()
        W = TLorentzVector()
        t1 = TLorentzVector()
        t2 = TLorentzVector()
        if abs(mass[0]-125) > abs(mass[1]-125):
            i = 1
        H.SetPtEtaPhiM(Signal.fatjetspt[i], Signal.fatjetseta[i], Signal.fatjetsphi[i], mass[i])
        W.SetPtEtaPhiM(Signal.fatjetspt[(i+1)%2], Signal.fatjetseta[(i+1)%2], Signal.fatjetsphi[(i+1)%2], mass[(i+1)%2])
        t1.SetPtEtaPhiM(Signal.tagjet1pt, Signal.tagjet1eta, Signal.tagjet1phi, Signal.tagjet1mass)
        t2.SetPtEtaPhiM(Signal.tagjet2pt, Signal.tagjet2eta, Signal.tagjet2phi, Signal.tagjet2mass)

        MVHjj = H+W+t1+t2
    
        MVHjjPt_hist.Fill(MVHjj.Pt())
        MVHjjEta_hist.Fill(MVHjj.Eta())
        MVHjjPhi_hist.Fill(MVHjj.Phi())
        MVHjjM_hist.Fill(MVHjj.M())
        
output_file = TFile(r"C:\Users\hcds\MVHjj.root", "RECREATE")
MVHjjPt_hist.Write()
MVHjjEta_hist.Write()
MVHjjPhi_hist.Write()
MVHjjM_hist.Write()

output_file.Close()
chain.Close()

print("Done.")
