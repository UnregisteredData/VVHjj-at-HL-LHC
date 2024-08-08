import sys
sys.path = [r'C:\root_v6.32.02\bin'] + sys.path
import ROOT
from ROOT import TH1D, TH2D, TCanvas, TFile, gROOT, gPad, gStyle, gDirectory, TMath

file = TFile(r'C:\Users\hcds\experiment.root')
t = gROOT.FindObject('tree1')
c1 = TCanvas()
c2 = TCanvas()

c1.cd()
t.Draw("sqrt(px*px + py*py) >> htemp(100,-1,30)")

htemp1 = gPad.GetPrimitive("htemp")
if htemp1:
    htemp1.SetTitle("Transverse Momentum")
    htemp1.GetXaxis().SetTitle("pt (GEV)")
    htemp1.GetYaxis().SetTitle('frequency')
    htemp1.GetYaxis().SetTitleOffset(1.5)
    c1.Update()
else:
    pass

c2.cd()
c2.SetWindowPosition(800,10)
t.Draw("atan2(sqrt(px*px + py*py),pz) >> h1(100, -3.14, 3.14)")

htemp2 = gPad.GetPrimitive("htemp2")
if htemp2:
    htemp2.SetTitle("arctan")
    htemp2.GetXaxis().SetTitle("pt (GEV)")
    htemp2.GetYaxis().SetTitle('theta')
    htemp2.GetYaxis().SetTitleOffset(1.5)
    c2.Update()
else:
    pass


c1.Draw()
c2.Draw()
