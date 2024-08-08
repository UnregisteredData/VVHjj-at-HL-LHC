import sys
sys.path = [r'C:\root_v6.32.02\bin'] + sys.path
import ROOT
from ROOT import TH1D, TH2D, TCanvas, TFile, gROOT, gPad, gStyle, gDirectory
file = TFile(r'C:\Users\hcds\experiment.root')
t = gROOT.FindObject('tree1')
c = TCanvas()

t.Draw("zv:ebeam", "", "LEGO")
c.Draw()
