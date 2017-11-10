#include "TSystem.h"
#include "TCanvas.h"
#include "TLine.h"

TStyle * makeplotstyle() {

	TStyle *mystyle = new TStyle("PlottingInStyle", "Style for Summary Plots");
	mystyle->SetPadLeftMargin(0.13);
	mystyle->SetPadBottomMargin(0.13);
	mystyle->SetCanvasColor(10);
	mystyle->SetOptTitle(0);
	mystyle->SetPadTickX(1);
	mystyle->SetPadTickY(1);
	mystyle->SetTitleXSize(0.55);
	mystyle->SetTitleYSize(0.55);
	mystyle->SetTitleOffset(1.0, "XY");
	mystyle->SetNdivisions(508, "X");
	mystyle->SetNdivisions(508, "Y");
	mystyle->SetLabelOffset(0.005, "XY");
	mystyle->SetLabelSize(0.6, "XY");
	mystyle->SetMarkerStyle(8);
	//mystyle->SetGridx();

	return mystyle;
}


void RunGlauberFitter (Int_t nf = 1, Float_t f0 = 1.0, Float_t f1 = 1.0, Int_t nsigma = 2, Float_t StepSigma = 0.1, Int_t nEvents = 500, Int_t MultMin = 40)
{

	
    TString fConfig;

    TString CentralityFrameworkDir = "/home/liza/CentralityFramework/CentralityFramework/build/";   
    gSystem->Load( CentralityFrameworkDir + "libCentrality");    
    
    fConfig="Mult";
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     
    TH1F *h1d_Mult_TPC_Ref;
  
if (fConfig=="Mult") {
    TFile *f = new TFile("/home/liza/NIRS/Diplom/NA49/Mult_NA49_afterfit_0110.root");    
    h1d_Mult_TPC_Ref = (TH1F*)f->Get("MultSignalWithoutPhon");
			}

else if (fConfig=="Spec") {
    TFile *f = new TFile("/home/liza/NIRS/Diplom/CentralityFramework/Glauber/Veto_NA49_afterfit_1.root");    
    h1d_Mult_TPC_Ref = (TH1F*)f->Get("MultSignalWithoutPhon");
			   }

    TH1F *hData1 = h1d_Mult_TPC_Ref;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
    GlauberFitter *test = new GlauberFitter;

if (fConfig=="Spec") {
    test->SetNpartMax (450);
    test->SetNcollMax (250);
    test->SetMultMax (10000);
    test->SetBinSize (100);	
			}
else if (fConfig=="Mult") {
    test->SetNpartMax (450);
    test->SetNcollMax (900);
    test->SetMultMax (500); 
    test->SetBinSize (1);
    }
    TString OutDir = "MinMult_";
    OutDir += MultMin;
    
    test->SetFitMultMin (MultMin);
    test->SetNormMultMin (MultMin);
    test->SetOutDirName (OutDir);

if (fConfig=="Mult") test->SetSimHistos ("/home/liza/NIRS/Diplom/PbPb_NA49.root", nEvents); 
else if (fConfig=="Spec") test->SetSimHistos ("/home/liza/CentralityFramework/CentralityFramework/Macro/SpectatorsTarget_Glauber.root", nEvents);
				

    test->SetInputHisto (h1d_Mult_TPC_Ref);
    test->FitGlauber(nf, f0, f1, nsigma, StepSigma, nEvents);
    test->DrawHistos(true, true, true, false);

/*test->SetGlauberFitHisto (0.95,0.52436,52.1316, 900000, true);

    TH1F *h1 = test->GetGlauberFitHisto ();
    h1->SetLineColor(kRed);

TCanvas *c2 = new TCanvas("c2", "canvas", 1500, 900);
c2->cd();
gPad->SetLogy();
h1->GetXaxis()->SetTitleSize(0.06);
h1->GetYaxis()->SetTitleSize(0.06);
if (fConfig=="Mult") h1->GetXaxis()->SetTitle("M_{trk}");
else h1->GetXaxis()->SetTitle("E_{veto}");
h1->GetYaxis()->SetTitle("Counts");
h1->GetXaxis()->SetLabelSize(0.04);
h1->GetYaxis()->SetLabelSize(0.04);
h1->Draw();
hData1->Draw("sameAP");
    
TFile *file = new TFile("GlauberFit_NA49.root", "RECREATE");
	file->cd();
	h1->Write();
	hData1->Write();
	file->Close();
*/
/*TLegend* legData = new TLegend(0.7,0.8,0.85,0.89);
legData->SetFillColor(0);
legData->SetBorderSize(0);
legData->AddEntry(hData1 ,"E_{veto} NA49", "lp"); 
legData->AddEntry(h1 ,"MWN fit", "l");    
legData->AddEntry(h1 ,"f_{E}=0", ""); 
legData->AddEntry(h1 ,"#mu=52.3", ""); 
legData->AddEntry(h1 ,"#sigma=45.0", "");  
legData->AddEntry(h1 ,"#chi^{2}=2.4", ""); 
legData->AddEntry(h1 ,"Fit range: E_{veto}<4500", "");     
legData->Draw("same"); 
*/

}
