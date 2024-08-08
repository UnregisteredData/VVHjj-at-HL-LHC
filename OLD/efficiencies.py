import sys
sys.path = [r"C:\root_v6.32.02\bin"] + sys.path


#largest and smallest eta and check that they have opposite signs and chekc
# that eta of the smaller one is smaler than smallest fat jet eta 

import ROOT
from ROOT import TFile, gROOT

file1 = TFile(r'C:\Users\hcds\VVHjj.root')
file2 = TFile(r'C:\Users\hcds\ttjj.root')
mychain1 = file1['myTree']
mychain2 = file2['myTree']

BOOSTED_COUNT_SIGNAL = 0
HYBRID_COUNT_SIGNAL = 0


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
    if any(pt > 200 for pt in mychain1.fatjetspt) and any(eta < 2 for eta in mychain1.fatjetseta):
        #BOOSTED
        if (nfatjets > 1) and any(mass > 30 for mass in fatjetsmass) and (nleptons > 0) and (leptonpt > 30):
            BOOSTED_COUNT_SIGNAL += 1
        #HYBRID
        elif (nfatjets > 0) and any(mass > 30 for mass in fatjetsmass) and (nleptons > 0) and (leptonpt > 30):
            HYBRID_COUNT_SIGNAL += 1

print(f"BOOSTED SIGNAL COUNT: {BOOSTED_COUNT_SIGNAL}\nHYBRID SIGNAL COUNT: {HYBRID_COUNT_SIGNAL}")
print(f"entries: {entries}")

