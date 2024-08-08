import sys
sys.path = [r"C:\root_v6.32.02\bin"] + sys.path

import ROOT
from ROOT import TFile, TCanvas, gROOT, gPad, gStyle, gDirectory, TH1D, TLegend, gStyle

file1 = TFile(r'C:\Users\hcds\VVHjj.root')
file2 = TFile(r'C:\Users\hcds\ttjj.root')
mychain1 = file1['myTree']
mychain2 = file2['myTree']
gStyle.SetOptStat(0)

c1 = TCanvas()
c2 = TCanvas()

SigGRAPH_BOOSTED = TH1D("Signal1", "H Candidate: Boosted Selection", 50, 0, 200)
BackGRAPH_BOOSTED = TH1D("Signal2", "H Candidate: Boosted Selection", 50, 0, 200)
SigGRAPH_HYBRID = TH1D("Signal3", "H Candidate: Hybrid Selection", 50, 0, 200)
BackGRAPH_HYBRID = TH1D("Signal4", "H Candidate: Hybrid Selection", 50, 0, 200)

SigGRAPH_BOOSTED.SetLineColor(ROOT.kGreen)
BackGRAPH_BOOSTED.SetLineColor(ROOT.kMagenta)
SigGRAPH_HYBRID.SetLineColor(ROOT.kGreen)
BackGRAPH_HYBRID.SetLineColor(ROOT.kMagenta)

BackGRAPH_BOOSTED.SetLineWidth(2)
SigGRAPH_HYBRID.SetLineWidth(2)
BackGRAPH_HYBRID.SetLineWidth(2)
SigGRAPH_BOOSTED.SetLineWidth(2)

BOOSTED_COUNT_SIGNAL = 0
HYBRID_COUNT_SIGNAL = 0
BOOSTED_COUNT_BACKGROUND = 0
HYBRID_COUNT_BACKGROUND = 0



entries = mychain1.GetEntriesFast()

for jentry in range( entries ):
    ientry = mychain1.LoadTree( jentry )
    if ientry < 0:
        break

    nb = mychain1.GetEntry( jentry )
    if nb <= 0:
        continue

    nfatjets = mychain1.nfatjets
    fatjetsmass = mychain1.fatjetsmass
    nleptons = mychain1.nleptons
    leptonpt = mychain1.leptonpt
    mhiggs = mychain1.MH_tree
    if any(pt > 200 for pt in mychain1.fatjetspt) and any(eta < 2 for eta in mychain1.fatjetseta) and mhiggs > 70 and mhiggs < 140:
        #BOOSTED
        if (nfatjets > 1) and any(mass > 30 for mass in fatjetsmass) and (nleptons > 0) and (leptonpt > 30):
            BOOSTED_COUNT_SIGNAL += 1
            SigGRAPH_BOOSTED.Fill(mychain1.MH_tree)
        #HYBRID
        elif (nfatjets > 0) and any(mass > 30 for mass in fatjetsmass) and (nleptons > 0) and (leptonpt > 30):
            HYBRID_COUNT_SIGNAL += 1
            SigGRAPH_HYBRID.Fill(mychain1.MH_tree)

print(f"BOOSTED SIGNAL COUNT: {BOOSTED_COUNT_SIGNAL}\nHYBRID SIGNAL COUNT: {HYBRID_COUNT_SIGNAL}")




entries = mychain2.GetEntriesFast()

for jentry in range( entries ):
    ientry = mychain2.LoadTree( jentry )
    if ientry < 0:
        break

    nb = mychain2.GetEntry( jentry )
    if nb <= 0:
        continue

    nfatjets = mychain2.nfatjets
    fatjetsmass = mychain2.fatjetsmass
    nleptons = mychain2.nleptons
    leptonpt = mychain2.leptonpt
    mhiggs = mychain2.MH_tree
    if any(pt > 200 for pt in mychain2.fatjetspt) and any(eta < 2 for eta in mychain2.fatjetseta) and mhiggs > 70 and mhiggs < 140:
        #BOOSTED
        if (nfatjets > 1) and any(mass > 30 for mass in fatjetsmass) and (nleptons > 0) and (leptonpt > 30):
            BOOSTED_COUNT_BACKGROUND += 1
            BackGRAPH_BOOSTED.Fill(mychain2.MH_tree)
        #HYBRID
        elif (nfatjets > 0) and any(mass > 30 for mass in fatjetsmass) and (nleptons > 0) and (leptonpt > 30):
            HYBRID_COUNT_BACKGROUND += 1
            BackGRAPH_HYBRID.Fill(mychain2.MH_tree)

print(f"BOOSTED BACKGROUND COUNT: {BOOSTED_COUNT_BACKGROUND}\nHYBRID BACKGROUND COUNT: {HYBRID_COUNT_BACKGROUND}")

c1.cd()
SigGRAPH_BOOSTED.GetXaxis().SetTitle("GEV")
BackGRAPH_BOOSTED.GetXaxis().SetTitle("GEV")

SigGRAPH_BOOSTED.Draw()
BackGRAPH_BOOSTED.Draw('same')

legend1 = TLegend(0.9, 0.9, 0.75, 0.75)
legend1.AddEntry(SigGRAPH_BOOSTED, "Signal", "l")
legend1.AddEntry(BackGRAPH_BOOSTED, "Background", "l")
legend1.Draw()



c2.cd()
c2.SetWindowPosition(800,10)
SigGRAPH_HYBRID.GetXaxis().SetTitle("GEV")
BackGRAPH_HYBRID.GetXaxis().SetTitle("GEV")

BackGRAPH_HYBRID.Draw()
SigGRAPH_HYBRID.Draw('same')

legend2 = TLegend(0.9, 0.9, 0.75, 0.75)
legend2.AddEntry(SigGRAPH_HYBRID, "Signal", "l")
legend2.AddEntry(BackGRAPH_HYBRID, "Background", "l")
legend2.Draw()

c1.Draw()
c2.Draw()

