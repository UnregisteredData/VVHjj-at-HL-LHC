import sys
#sys.path
#['', 'C:\\Users\\hcds\\AppData\\Local\\Programs\\Python\\Python311\\Lib\\idlelib', 'C:\\Users\\hcds\\AppData\\Local\\Programs\\Python\\Python311\\python311.zip', 'C:\\Users\\hcds\\AppData\\Local\\Programs\\Python\\Python311\\DLLs', 'C:\\Users\\hcds\\AppData\\Local\\Programs\\Python\\Python311\\Lib', 'C:\\Users\\hcds\\AppData\\Local\\Programs\\Python\\Python311', 'C:\\Users\\hcds\\AppData\\Local\\Programs\\Python\\Python311\\Lib\\site-packages']
sys.path = ['C:\\root_v6.32.02\\bin'] + sys.path
#sys.path
#['C:\\root_v6.32.02\\bin', '', 'C:\\Users\\hcds\\AppData\\Local\\Programs\\Python\\Python311\\Lib\\idlelib', 'C:\\Users\\hcds\\AppData\\Local\\Programs\\Python\\Python311\\python311.zip', 'C:\\Users\\hcds\\AppData\\Local\\Programs\\Python\\Python311\\DLLs', 'C:\\Users\\hcds\\AppData\\Local\\Programs\\Python\\Python311\\Lib', 'C:\\Users\\hcds\\AppData\\Local\\Programs\\Python\\Python311', 'C:\\Users\\hcds\\AppData\\Local\\Programs\\Python\\Python311\\Lib\\site-packages']
import ROOT
#ROOT.PyConfig.StartGuiThread = False


from ROOT import TH1D, TCanvas, TFile, gROOT, gPad, gStyle


'''
my_canvas = TCanvas()
example = TH1D("example","example histogram",100,-3,3)
example.FillRandom("gaus",10000)
example.Fit("gaus")
example.Draw()
my_canvas.Draw()
'''

file = TFile(r'C:\Users\hcds\experiment.root')
t = gROOT.FindObject("tree1")
c = TCanvas()
t.Draw('ebeam')

htemp = gPad.GetPrimitive("htemp")
if htemp:
        htemp.SetTitle("ebeam histogram")
        htemp.GetXaxis().SetTitle("ebeam")
        htemp.GetYaxis().SetTitle("frequency")
        htemp.GetYaxis().SetTitleOffset(1.5)
        htemp.Fit('gaus')
        c.Update()

        stats = htemp.FindObject("stats")
        if stats:
                # Set options to display fit parameters
                gStyle.SetOptFit(1111)
                stats.SetOptFit(1111)
                stats.SetOptStat(1111)  # Set options to display statistics

                
                # Redraw the stats box
                stats.SetX1NDC(0.7)  # x start position
                stats.SetX2NDC(0.9)  # x end position
                stats.SetY1NDC(0.6)  # y start position
                stats.SetY2NDC(0.9)  # y end position
                
                c.Modified()
                c.Update()

        
        
c.Draw()

'''
if __name__ == '__main__xxx':
	import time
	while True:
		ROOT.gSystem.ProcessEvents()
		time.sleep(1)
'''

