import sys
sys.path = [r"C:\root_v6.32.02\bin"] + sys.path
from ROOT import TH1D, TCanvas, TFile, gROOT, gPad

file = TFile(r"C:\Users\hcds\experiment.root")
t = gROOT.FindObject("tree1")
c1 = TCanvas()
c1.Divide(2)


c1.cd(1)
t.Draw("ebeam","","e")

htemp1 = gPad.GetPrimitive("htemp")
if htemp1:
    htemp1.GetXaxis().SetTitle("Ebeam")
    htemp1.GetYaxis().SetTitle("Num Events")
    htemp1.GetYaxis().SetTitleOffset(1.5)
    c1.Update()

else:
    pass


c1.cd(2)
t.Draw("chi2","","e")

htemp2 = gPad.GetPrimitive("htemp")
if htemp2:
    htemp2.GetXaxis().SetTitle("Chi2")
    htemp2.GetYaxis().SetTitle("Num Events")
    htemp2.GetYaxis().SetTitleOffset(1.5)
    c1.Update()

else:
    pass

c1.Draw()
