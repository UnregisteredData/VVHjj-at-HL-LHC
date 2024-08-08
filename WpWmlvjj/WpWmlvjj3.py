import sys
sys.path = [r'C:\root_v6.32.02\bin'] + sys.path

import math
from array import array

from itertools import combinations

import ROOT
from ROOT import TTreeReader, TTreeReaderValue, TFile, TH1F, TLorentzVector, TH1D, TCanvas, TLegend, gStyle

ROOT.gROOT.SetBatch(ROOT.kTRUE)


# Open the ROOT files
file_1 = TFile.Open(r"C:\Users\hcds\WpWmlvjj_kl2.root")
file_2 = TFile.Open(r"C:\Users\hcds\WpWmlvjj_kl5.root")
file_3 = TFile.Open(r"C:\Users\hcds\WpWmlvjj_kl10.root")

# Get the trees
kl2 = file_1.Get('myTree')
kl5 = file_2.Get('myTree')
kl10 = file_3.Get('myTree')

# Branch names and histogram properties
branches = ['MH_tree', 'MV_tree', 'PTH_tree', 'PTW_tree', 'tagjet1pt', 'tagjet2pt', 'tagjet1eta', 'tagjet2eta']
hist_props = {
    'MH_tree': (25, 0, 250),
    'MV_tree': (25, 0, 100),
    'PTH_tree': (25, 100, 850),
    'PTW_tree': (25, 100, 600),
    'tagjet1pt': (25, 0, 200),
    'tagjet2pt': (25, 0, 100),
    'tagjet1eta': (25, -4, 4),
    'tagjet2eta': (25, -4, 4)
}

# Function to create and fill histograms
def create_and_fill_histograms(tree, branches, hist_props):
    histograms = {}
    for branch in branches:
        nbins, xmin, xmax = hist_props[branch]
        hist_name = f"hist_{branch}"
        hist = TH1F(hist_name, f"{branch};{branch};frequency", nbins, xmin, xmax)
        tree.Draw(f"{branch}>>{hist_name}")
        histograms[branch] = hist
    return histograms

# Create and fill histograms for each tree
hist_kl2 = create_and_fill_histograms(kl2, branches, hist_props)
hist_kl5 = create_and_fill_histograms(kl5, branches, hist_props)
hist_kl10 = create_and_fill_histograms(kl10, branches, hist_props)

# Draw histograms on separate canvases
for branch in branches:
    canvas = ROOT.TCanvas(f"canvas_{branch}", f"Canvas for {branch}", 800, 600)
    
    hist_kl2[branch].SetLineColor(ROOT.kBlue)
    hist_kl5[branch].SetLineColor(ROOT.kRed)
    hist_kl10[branch].SetLineColor(ROOT.kGreen)

    hist_kl2[branch].DrawNormalized()
    hist_kl5[branch].DrawNormalized("same")
    hist_kl10[branch].DrawNormalized("same")
    
    legend = ROOT.TLegend(0.75, 0.45, 0.9, 0.6)
    legend.AddEntry(hist_kl2[branch], "kl2", "l")
    legend.AddEntry(hist_kl5[branch], "kl5", "l")
    legend.AddEntry(hist_kl10[branch], "kl10", "l")
    legend.Draw()

    canvas.SaveAs(f"C:\\Users\\hcds\\WpWmlvjj_Images\\{branch}.png")
    #canvas.Write()
    

WpWmlvjj_WHjj_hist_2 = TH1F("WpWmlvjj_WHjj_hist_2", "WHjj_tree;WHjj_tree;frequency", 25, 0, 4000)
WpWmlvjj_WHjj_hist_5 = TH1F("WpWmlvjj_WHjj_hist_5", "WHjj_tree;WHjj_tree;frequency", 25, 0, 4000)
WpWmlvjj_WHjj_hist_10 = TH1F("WpWmlvjj_WHjj_hist_10", "WHjj_tree;WHjj_tree;frequency", 25, 0, 4000)

WHjj_canvas = TCanvas()
WHjj_canvas.cd()

for event in kl2:
    WpWmlvjj_WHjj_hist_2.Fill(event.MH_tree + event.MV_tree + event.Mjj_tree)

for event in kl5:
    WpWmlvjj_WHjj_hist_5.Fill(event.MH_tree + event.MV_tree + event.Mjj_tree)

for event in kl10:
    WpWmlvjj_WHjj_hist_10.Fill(event.MH_tree + event.MV_tree + event.Mjj_tree)
    
WpWmlvjj_WHjj_hist_2.SetLineColor(ROOT.kBlue)
WpWmlvjj_WHjj_hist_5.SetLineColor(ROOT.kRed)
WpWmlvjj_WHjj_hist_10.SetLineColor(ROOT.kGreen)

WpWmlvjj_WHjj_hist_2.DrawNormalized()
WpWmlvjj_WHjj_hist_5.DrawNormalized('same')
WpWmlvjj_WHjj_hist_10.DrawNormalized('same')

legend = ROOT.TLegend(0.75, 0.45, 0.9, 0.6)
legend.AddEntry(WpWmlvjj_WHjj_hist_2, "kl2", "l")
legend.AddEntry(WpWmlvjj_WHjj_hist_5, "kl5", "l")
legend.AddEntry(WpWmlvjj_WHjj_hist_10, "kl10", "l")
legend.Draw()

WHjj_canvas.SaveAs(f"C:\\Users\\hcds\\WpWmlvjj_Images\\WHjj.png")


# Close the files
file_1.Close()
file_2.Close()
file_3.Close()
