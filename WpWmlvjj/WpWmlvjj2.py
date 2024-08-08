import sys
sys.path = [r'C:\root_v6.32.02\bin'] + sys.path

import math
from array import array

from itertools import combinations

import ROOT
from ROOT import TTreeReader, TTreeReaderValue, TFile, TH1F, TLorentzVector, TH1D, TCanvas, TLegend, gStyle

ROOT.gROOT.SetBatch(ROOT.kTRUE)

import ROOT

# Create a canvas
c = ROOT.TCanvas("c", "c", 800, 600)

# Open the ROOT files
file_1 = ROOT.TFile.Open(r"C:\Users\hcds\WpWmlvjj_kl2.root")
file_2 = ROOT.TFile.Open(r"C:\Users\hcds\WpWmlvjj_kl5.root")
file_3 = ROOT.TFile.Open(r"C:\Users\hcds\WpWmlvjj_kl10.root")

# Get the trees
kl2 = file_1.Get('myTree')
kl5 = file_2.Get('myTree')
kl10 = file_3.Get('myTree')

# Create histograms
hist_kl2 = ROOT.TH1F("hist_kl2", "MH_tree;MH_tree;frequency", 25, 0, 250)
hist_kl5 = ROOT.TH1F("hist_kl5", "MH_tree;MH_tree;frequency", 25, 0, 250)
hist_kl10 = ROOT.TH1F("hist_kl10", "MH_tree;MH_tree;frequency", 25, 0, 250)

# Fill histograms with the MH_tree branch values
kl2.Draw("MH_tree>>hist_kl2")
kl5.Draw("MH_tree>>hist_kl5")
kl10.Draw("MH_tree>>hist_kl10")

# Set histogram line colors
hist_kl2.SetLineColor(ROOT.kBlue)
hist_kl5.SetLineColor(ROOT.kRed)
hist_kl10.SetLineColor(ROOT.kGreen)

# Draw histograms on the same canvas
hist_kl2.Draw()
hist_kl5.Draw("same")
hist_kl10.Draw("same")

# Add a legend
legend = ROOT.TLegend(0.75, 0.45, 0.9, 0.6)
legend.AddEntry(hist_kl2, "kl2", "l")
legend.AddEntry(hist_kl5, "kl5", "l")
legend.AddEntry(hist_kl10, "kl10", "l")
legend.Draw()

# Save the canvas
c.SaveAs(r"C:\Users\hcds\histograms.png")
