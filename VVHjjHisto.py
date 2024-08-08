import sys
sys.path = [r"C:\root_v6.32.02\bin"] + sys.path

import ROOT
from ROOT import TFile, TCanvas, gROOT, gPad, gStyle, gDirectory, TH1D, TLegend, gStyle

c = TCanvas()
gStyle.SetOptStat(0)


file1 = TFile( r'C:\Users\hcds\VVHjj.root' )
mychain = file1['myTree']

SigGRAPH = TH1D("Signal", "fatjetsmass", 100, 0, 400)
SigGRAPH.SetLineColor(ROOT.kGreen)
SigGRAPH.SetLineWidth(2)
mychain.Project(SigGRAPH.GetName(), 'fatjetsmass')



file2 = TFile(r'C:\Users\hcds\ttjj.root')
mychain = file2['myTree']

BackGRAPH = TH1D("Background", "MH_tree", 100, 0, 400)
BackGRAPH.SetLineColor(ROOT.kMagenta)
BackGRAPH.SetLineWidth(2)
mychain.Project(BackGRAPH.GetName(), 'MH_tree')

BackGRAPH.GetXaxis().SetTitle("GEV")
SigGRAPH.GetXaxis().SetTitle("GEV")


SigGRAPH.DrawNormalized('same')
BackGRAPH.DrawNormalized('same')


legend = TLegend(0.9, 0.9, 0.75, 0.75)
legend.AddEntry(SigGRAPH, "Signal", "l")
legend.AddEntry(BackGRAPH, "Background", "l")
legend.Draw()

c.Draw()

