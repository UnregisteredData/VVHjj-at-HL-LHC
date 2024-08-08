import sys
sys.path = [r'C:\root_v6.32.02\bin'] + sys.path

import math
from array import array
import numpy as np

from itertools import combinations

import ROOT
from ROOT import TTreeReader, TTreeReaderValue, TFile, TH1F, TLorentzVector, TH1D, TCanvas, TLegend, gStyle

bins_C = np.array([500, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700,
                   1800, 1900, 2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700,
                   2800, 2900, 3000, 3100, 3200, 3300, 3400, 3500, 4000, 5000],
                  dtype = 'float64')

whjjmcVVHjj = TH1F("whjjmcVVHjj", "WHjj Mass [GeV]", len(bins_C), bins_C)
whjjmcttjj = TH1F("whjjmcttjj", "WHjj Mass [GeV]", len(bins_C), bins_C)

print('whjjmcVVHjj')
for bin_num in range(len(bins_C)):
    print(f"bin_num: {bin_num}")
    print(whjjmcVVHjj.GetBinWidth(bin_num))

print("whjjmcttjj")
for bin_num in range(len(bins_C)):
    print(f"bin_num: {bin_num}")
    print(whjjmcttjj.GetBinWidth(bin_num))
