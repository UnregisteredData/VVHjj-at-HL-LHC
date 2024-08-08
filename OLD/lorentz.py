import sys
sys.path = [r'C:\root_v6.32.02\bin'] + sys.path
import ROOT
from ROOT import TLorentzVector, TFile

file = TFile(r'C:\Users\hcds\VVHjj.root')
chain = file['myTree']

v = TLorentzVector()
v.SetPtEtaPhiM(chain.tagjet1pt, chain.tagjet1eta, chain.tagjet1phi, chain.tagjet1mass)

print(v)
