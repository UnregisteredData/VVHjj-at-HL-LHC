import sys
sys.path = [r'C:\root_v6.32.02\bin'] + sys.path

import math
from array import array

from itertools import combinations

import ROOT
from ROOT import TTreeReader, TTreeReaderValue, TFile, TH1F, TLorentzVector, TH1D, TCanvas, TLegend, gStyle

#ROOT.gROOT.SetBatch(ROOT.kTRUE)

file_1 = TFile.Open(r"C:\Users\hcds\WpWmlvjj_kl2_both.root")
file_2 = TFile.Open(r"C:\Users\hcds\WpWmlvjj_kl5_both.root")
file_3 = TFile.Open(r"C:\Users\hcds\WpWmlvjj_kl10_both.root")
file_4 = TFile.Open(r"C:\Users\hcds\VVHjj.root")
kl1 = file_4 ['myTree']
kl2 = file_1['myTree']
kl5 = file_2['myTree']
kl10 = file_3['myTree']

trees = [kl2, kl5, kl10]

output_file = TFile(r'C:\Users\hcds\WpWmlvjj.root', 'RECREATE')

WpWmlvjj_MH_hist_1 = TH1F("WpWmlvjj_MH_hist_1", "MH_tree;MH_tree;frequency", 25, 0, 500)
WpWmlvjj_MV_hist_1 = TH1F("WpWmlvjj_MV_hist_1", "MV_tree;MV_tree;frequency", 25, 0, 100)
WpWmlvjj_PTH_hist_1 = TH1F("WpWmlvjj_PTH_hist_1", "PTH_tree;PTH_tree;frequency", 25, 100, 850)
WpWmlvjj_PTW_hist_1 = TH1F("WpWmlvjj_PTW_hist_1", "PTW_tree;PTW_tree;frequency", 25, 100, 600)
WpWmlvjj_WHjj_hist_1 = TH1F("WpWmlvjj_WHjj_hist_1", "WHjj_tree;WHjj_tree;frequency", 25, 0, 4000)
WpWmlvjj_tagjet1pt_hist_1 = TH1F("WpWmlvjj_tagjet1pt_hist_1", "tagjet1pt;tagjet1pt;frequency", 25, 0, 200)
WpWmlvjj_tagjet2pt_hist_1 = TH1F("WpWmlvjj_tagjet2pt_hist_1", "tagjet2pt;tagjet2pt;frequency", 25, 0, 100)
WpWmlvjj_tagjet1eta_hist_1 = TH1F("WpWmlvjj_tagjet1eta_hist_1", "tagjet1eta;tagjet1eta;frequency", 25, -4, 4)
WpWmlvjj_tagjet2eta_hist_1 = TH1F("WpWmlvjj_tagjet2eta_hist_1", "tagjet2eta;tagjet2eta;frequency", 25, -4, 4)

WpWmlvjj_MH_hist_2 = TH1F("WpWmlvjj_MH_hist_2", "MH_tree;MH_tree;frequency", 25, 0, 500)
WpWmlvjj_MV_hist_2 = TH1F("WpWmlvjj_MV_hist_2", "MV_tree;MV_tree;frequency", 25, 0, 100)
WpWmlvjj_PTH_hist_2 = TH1F("WpWmlvjj_PTH_hist_2", "PTH_tree;PTH_tree;frequency", 25, 100, 850)
WpWmlvjj_PTW_hist_2 = TH1F("WpWmlvjj_PTW_hist_2", "PTW_tree;PTW_tree;frequency", 25, 100, 600)
WpWmlvjj_WHjj_hist_2 = TH1F("WpWmlvjj_WHjj_hist_2", "WHjj_tree;WHjj_tree;frequency", 25, 0, 4000)
WpWmlvjj_tagjet1pt_hist_2 = TH1F("WpWmlvjj_tagjet1pt_hist_2", "tagjet1pt;tagjet1pt;frequency", 25, 0, 200)
WpWmlvjj_tagjet2pt_hist_2 = TH1F("WpWmlvjj_tagjet2pt_hist_2", "tagjet2pt;tagjet2pt;frequency", 25, 0, 100)
WpWmlvjj_tagjet1eta_hist_2 = TH1F("WpWmlvjj_tagjet1eta_hist_2", "tagjet1eta;tagjet1eta;frequency", 25, -4, 4)
WpWmlvjj_tagjet2eta_hist_2 = TH1F("WpWmlvjj_tagjet2eta_hist_2", "tagjet2eta;tagjet2eta;frequency", 25, -4, 4)

WpWmlvjj_MH_hist_5 = TH1F("WpWmlvjj_MH_hist_5", "MH_tree;MH_tree;frequency", 25, 0, 500)
WpWmlvjj_MV_hist_5 = TH1F("WpWmlvjj_MV_hist_5", "MV_tree;MV_tree;frequency", 25, 0, 100)
WpWmlvjj_PTH_hist_5 = TH1F("WpWmlvjj_PTH_hist_5", "PTH_tree;PTH_tree;frequency", 25, 100, 850)
WpWmlvjj_PTW_hist_5 = TH1F("WpWmlvjj_PTW_hist_5", "PTW_tree;PTW_tree;frequency", 25, 100, 600)
WpWmlvjj_WHjj_hist_5 = TH1F("WpWmlvjj_WHjj_hist_5", "WHjj_tree;WHjj_tree;frequency", 25, 0, 4000)
WpWmlvjj_tagjet1pt_hist_5 = TH1F("WpWmlvjj_tagjet1pt_hist_5", "tagjet1pt;tagjet1pt;frequency", 25, 0, 200)
WpWmlvjj_tagjet2pt_hist_5 = TH1F("WpWmlvjj_tagjet2pt_hist_5", "tagjet2pt;tagjet2pt;frequency", 25, 0, 100)
WpWmlvjj_tagjet1eta_hist_5 = TH1F("WpWmlvjj_tagjet1eta_hist_5", "tagjet1eta;tagjet1eta;frequency", 25, -4, 4)
WpWmlvjj_tagjet2eta_hist_5 = TH1F("WpWmlvjj_tagjet2eta_hist_5", "tagjet2eta;tagjet2eta;frequency", 25, -4, 4)

WpWmlvjj_MH_hist_10 = TH1F("WpWmlvjj_MH_hist_10", "MH_tree;MH_tree;frequency", 25, 0, 500)
WpWmlvjj_MV_hist_10 = TH1F("WpWmlvjj_MV_hist_10", "MV_tree;MV_tree;frequency", 25, 0, 100)
WpWmlvjj_PTH_hist_10 = TH1F("WpWmlvjj_PTH_hist_10", "PTH_tree;PTH_tree;frequency", 25, 100, 850)
WpWmlvjj_PTW_hist_10 = TH1F("WpWmlvjj_PTW_hist_10", "PTW_tree;PTW_tree;frequency", 25, 100, 600)
WpWmlvjj_WHjj_hist_10 = TH1F("WpWmlvjj_WHjj_hist_10", "WHjj_tree;WHjj_tree;frequency", 25, 0, 4000)
WpWmlvjj_tagjet1pt_hist_10 = TH1F("WpWmlvjj_tagjet1pt_hist_10", "tagjet1pt;tagjet1pt;frequency", 25, 0, 200)
WpWmlvjj_tagjet2pt_hist_10 = TH1F("WpWmlvjj_tagjet2pt_hist_10", "tagjet2pt;tagjet2pt;frequency", 25, 0, 100)
WpWmlvjj_tagjet1eta_hist_10 = TH1F("WpWmlvjj_tagjet1eta_hist_10", "tagjet1eta;tagjet1eta;frequency", 25, -4, 4)
WpWmlvjj_tagjet2eta_hist_10 = TH1F("WpWmlvjj_tagjet2eta_hist_10", "tagjet2eta;tagjet2eta;frequency", 25, -4, 4)

WpWmlvjj_MH_hist = TCanvas()
WpWmlvjj_MV_hist = TCanvas()
WpWmlvjj_PTH_hist = TCanvas()
WpWmlvjj_PTW_hist = TCanvas()
WpWmlvjj_tagjet1pt_hist = TCanvas()
WpWmlvjj_tagjet2pt_hist = TCanvas()
WpWmlvjj_tagjet1eta_hist = TCanvas()
WpWmlvjj_tagjet2eta_hist = TCanvas()
WpWmlvjj_WHjj_hist = TCanvas()

t1 = TLegend(0.75, 0.45, 0.9, 0.6)
t2 = TLegend(0.75, 0.45, 0.9, 0.6)
t3 = TLegend(0.75, 0.45, 0.9, 0.6)
t4 = TLegend(0.75, 0.45, 0.9, 0.6)
t5 = TLegend(0.75, 0.45, 0.9, 0.6)
t6 = TLegend(0.75, 0.45, 0.9, 0.6)
t7 = TLegend(0.75, 0.45, 0.9, 0.6)
t8 = TLegend(0.75, 0.45, 0.9, 0.6)
t9 = TLegend(0.75, 0.45, 0.9, 0.6)

canvases = [WpWmlvjj_MH_hist, WpWmlvjj_MV_hist, WpWmlvjj_PTH_hist,
            WpWmlvjj_PTW_hist, WpWmlvjj_tagjet1pt_hist,
            WpWmlvjj_tagjet2pt_hist, WpWmlvjj_tagjet1eta_hist,
            WpWmlvjj_tagjet2eta_hist]

canvas_names = ['WpWmlvjj_MH_hist', 'WpWmlvjj_MV_hist', 'WpWmlvjj_PTH_hist',
                'WpWmlvjj_PTW_hist', 'WpWmlvjj_tagjet1pt_hist',
                'WpWmlvjj_tagjet2pt_hist', 'WpWmlvjj_tagjet1eta_hist',
                'WpWmlvjj_tagjet2eta_hist']

TLegends = [t1, t2, t3, t4, t5, t6, t7, t8, t9]

histograms = [(WpWmlvjj_MH_hist_2, WpWmlvjj_MH_hist_5, WpWmlvjj_MH_hist_10),
              (WpWmlvjj_MV_hist_2, WpWmlvjj_MV_hist_5, WpWmlvjj_MV_hist_10),
              (WpWmlvjj_PTH_hist_2, WpWmlvjj_PTH_hist_5, WpWmlvjj_PTH_hist_10),
              (WpWmlvjj_PTW_hist_2, WpWmlvjj_PTW_hist_5, WpWmlvjj_PTW_hist_10),
              (WpWmlvjj_tagjet1pt_hist_2, WpWmlvjj_tagjet1pt_hist_5, WpWmlvjj_tagjet1pt_hist_10),
              (WpWmlvjj_tagjet2pt_hist_2, WpWmlvjj_tagjet2pt_hist_5, WpWmlvjj_tagjet2pt_hist_10),
              (WpWmlvjj_tagjet1eta_hist_2, WpWmlvjj_tagjet1eta_hist_5, WpWmlvjj_tagjet1eta_hist_10),
              (WpWmlvjj_tagjet2eta_hist_2, WpWmlvjj_tagjet2eta_hist_5, WpWmlvjj_tagjet2eta_hist_10)]

branches = [(kl2.MH_tree, kl5.MH_tree, kl10.MH_tree),
            (kl2.MV_tree, kl5.MV_tree, kl10.MV_tree),
            (kl2.PTH_tree, kl5.PTH_tree, kl10.PTH_tree),
            (kl2.PTW_tree, kl5.PTW_tree, kl10.PTW_tree),
            (kl2.tagjet1pt, kl5.tagjet1pt, kl10.tagjet1pt),
            (kl2.tagjet2pt, kl5.tagjet2pt, kl10.tagjet2pt),
            (kl2.tagjet1eta, kl5.tagjet1eta, kl10.tagjet1eta),
            (kl2.tagjet2eta, kl5.tagjet2eta, kl10.tagjet2eta)]

def loop(tree, histograms, branches, index):
    for i in range(len(branches)):
        tree.Draw(f"{branches[i][index]}>>histograms[i][index]")


def draw(histograms, canvases, canvas_names):
    for i in range(len(histograms)):
        hist_kl2 = histograms[i][0]
        hist_kl5 = histograms[i][1]
        hist_kl10 = histograms[i][2]
        canvases[i].cd()

        hist_kl2.SetLineColor(ROOT.kBlue)
        hist_kl2.Draw('same')
        hist_kl5.SetLineColor(ROOT.kRed)
        hist_kl5.Draw('same')
        hist_kl10.SetLineColor(ROOT.kGreen)
        hist_kl10.Draw('same')

        TLegends[i].AddEntry(hist_kl2, "kl2", "l")
        TLegends[i].AddEntry(hist_kl5, "kl5", "l")
        TLegends[i].AddEntry(hist_kl10, "kl10", "l")
        TLegends[i].Draw()

        canvases[i].SetName(canvas_names[i])
        canvases[i].Write()

total_trees = len(trees)
for j in range(total_trees):
    loop(trees[j], histograms, branches, j)

#loop(kl2, histograms, branches, 0)
#loop(kl2, histograms, branches, 0)
#loop(kl5, histograms, branches, 1)
#loop(k10, histograms, branches, 2)

draw(histograms, canvases, canvas_names)
        
#Entries_S = Signal.GetEntriesFast()
#Entries_B = Background.GetEntriesFast()



