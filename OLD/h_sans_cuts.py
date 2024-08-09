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

ROOT.gROOT.SetBatch(ROOT.kTRUE)

c = TCanvas()
t1 = TLegend(0.75, 0.45, 0.9, 0.6)
output_file = TFile(r'C:\Users\hcds\h_sans_cuts.root', 'RECREATE')


H_signal_hist = TH1F("H_signal_hist", "Higgs Mass;m;frequency", 20, 0, 400)
H_background_hist = TH1F("H_background_hist", "Higgs Mass;m;frequency", 20, 0, 400)


for event in Signal:
    H_signal_hist.Fill(event.MH_tree)
    
for event in Background:
    H_background_hist.Fill(event.MH_tree)
    

H_background_hist.SetStats(0)
H_background_hist.SetLineColor(ROOT.kRed)
H_background_hist.Draw('same')
H_signal_hist.SetStats(0)
H_signal_hist.SetLineColor(ROOT.kBlue)
H_signal_hist.Draw('same')

t1.AddEntry(H_background_hist, "Background", "l")
t1.AddEntry(H_signal_hist, "Signal", 'l')
t1.Draw()

c.SetName('Higgs Sans Cut')
c.Write()

output_file.Close()
signal_file.Close()
background_file.Close()

