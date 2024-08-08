import sys
sys.path = sys.path = [r'C:\root_v6.32.02\bin'] + sys.path

import ROOT
from array import array

background_file = ROOT.TFile.Open(r'C:\Users\hcds\ttjj.root')
Background = background_file['myTree']

# Create a new ROOT file
output_file = ROOT.TFile(r"C:\Users\hcds\test.root", "RECREATE")

# Create a TTree
ttjj_TMVA = ROOT.TTree("ttjj_TMVA", "Tree for TMVA")

# Create branches
leptonpt = array('f', [0])
ttjj_TMVA.Branch("leptonpt", leptonpt, "leptonpt/F")

# Fill the tree with some data
for event in Background:
    leptonpt[0] = Background.leptonpt 
    ttjj_TMVA.Fill()

# Write the tree to the file and close it
ttjj_TMVA.Write()
output_file.Close()

print("Done.")

            
