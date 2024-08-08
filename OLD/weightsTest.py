import sys
sys.path = [r'C:\root_v6.32.02\bin'] + sys.path

import ROOT
from ROOT import TTreeReader, TTreeReaderValue

WeightReader_S = TTreeReader("myTree", ROOT.TFile.Open(r"C:\Users\hcds\VVHjj.root"))
SignalWeight = TTreeReaderValue(ROOT.std.vector(float))(WeightReader_S, "weights_event_tree")
entry_count = 0
empty_count = 0
totalEntries = 0

while WeightReader_S.Next():
    weight_vector = SignalWeight.Get()
    
    if weight_vector.size() > 0:
        print(f"type: {type(weight_vector)}")
        print(f"size: {weight_vector.size()}")
        print(f"get: {weight_vector.front()}")
        entry_count += 1
        totalEntries += 1
    else:
        empty_count += 1
        totalEntries += 1

print(f"Total sized vectors: {entry_count}")
print(f"Total empty vectors: {empty_count}")
print(f"Total entries checked: {totalEntries}")
