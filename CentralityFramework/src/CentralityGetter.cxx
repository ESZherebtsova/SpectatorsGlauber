
#include <iostream>
#include <fstream>

#include "CentralityGetter.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TRandom.h"
#include "TMath.h"
#include "TGraphErrors.h"
#include "TH2.h"
#include "TLegend.h"
#include "TLatex.h"
TStyle * makeplotstyle2() {

	TStyle *style = new TStyle("PlottingInStyle", "Style for Summary Plots");
    style->SetTitleSize(0.08,"X");
    style->SetTitleSize(0.08,"Y");
    style->SetTitleOffset(1.1,"Y");
    style->SetTitleOffset(0.9,"X");
    style->SetFrameLineWidth(2);
    style->SetLabelSize(0.06,"X");
    style->SetLabelSize(0.06,"Y");
    style->SetPadTopMargin(0.1);
    style->SetPadBottomMargin(0.18);
    style->SetPadLeftMargin(0.18);
    style->SetPadTopMargin(0.1);
    style->SetPadRightMargin(0.1);
    //style->SetMarkerSize(2.);
    style->SetErrorX(0);
    style->SetOptStat(0);
    style->SetCanvasColor(0);
    style->SetTitleFillColor(0);
    style->SetTitleBorderSize(0);
    //style->SetMarkerStyle(20);
    style->SetHistLineWidth(3);
    style->SetLineWidth(2);
    style->SetCanvasBorderMode(0);
    style->SetLegendBorderSize(0);
    style->SetPadBorderMode(0);

	return style;
}


using std::vector;
using std::cout;
using std::endl;
using std::ifstream;

ClassImp(CentralityGetter)

CentralityGetter::CentralityGetter() :
fNSlices (20),
isDet1Int(false),
isDet2Int(false),
fSlice (new CentralitySlice),
fDet1Norm (-1),
fDet2Norm (-1)
{
}

CentralityGetter::~CentralityGetter()
{
}


void CentralityGetter::LoadCentalityDataFile (TString fileName)
{

    fCentrFile = new TFile(fileName.Data(), "READ");
    fCentrTree = (TTree*) fCentrFile->Get("CentrTree");    
    fCentrTree->SetBranchAddress("CentralitySlice", &fSlice);   
}

void CentralityGetter::SetRunId (Int_t RunId)
{
    fCentrTree->GetEntry(0);    
    UInt_t nRuns = fSlice->GetRunIdVec().size();
    Bool_t isOK = false;
    
//     std::cout << nRuns << std::endl;
    
    for (UInt_t i=0; i<nRuns; i++)
    {
        if (fSlice->GetRunIdVec().at(i) == RunId)
        {
//             std::cout << fSlice->GetRunIdVec().at(i) << std::endl;
            isOK = true;
            fDet1Norm = fSlice->GetDet1NormVec().at(i);
            if ( fSlice->GetDet2NormVec().size() > i)   fDet2Norm = fSlice->GetDet2NormVec().at(i);
            fRunId = RunId;
            break;
        }
    }
    if (!isOK)   std::cout << "*** Warning! *** Corrections for run # " << RunId << " was not found! Uncorrected value will be used!" << std::endl;
    if (isOK)    std::cout << "   Correction factor(s) for run # " << RunId << " = " << fDet1Norm ;
    if (isOK && fDet2Norm != -1)    std::cout << "  and  " << fDet2Norm ;
    if (isOK)  std::cout << std::endl;
    
}



Float_t CentralityGetter::GetCentrality (Double_t det1)
{    
    float centrality = -1;
    fCentrTree->GetEntry(0);
    TRandom* random = new TRandom;  
    random->SetSeed();
    if (isDet1Int){ 
        Float_t rand1 = random->Rndm()/* - 0.5*/;  /*cout << rand1 << endl;*/  
//         cout << "det1 = " << det1 << endl;
        det1 += rand1; 
//         cout << "  det1 = " << det1 << endl;

    }
    
    if (fDet1Norm != -1)  det1 *= fDet1Norm;
    det1 /= fSlice->GetDet1Max();
    bool isOK = false;

    Float_t step = fSlice->GetSlicesStep ();
    Int_t NSlices = fSlice->GetNSlices();
    
//     cout << "  det1 = " << det1 << endl;
//     cout << "NSlices = " << NSlices << endl;
//     cout << "step = " << step << endl;
    
    Int_t direction = fSlice->GetDirectionCentralEvents();
    
    if ( (direction == 1 && det1 > fSlice->GetXi(0)) || (direction == 0 && det1 < fSlice->GetXi(0)) )  //most central events
    {
        centrality = step*(0.5);
        return centrality;
    }

    if ( (direction == 1 && det1 < fSlice->GetXi(NSlices-1)) || (direction == 0 && det1 > fSlice->GetXi(NSlices-1)) )  //most peripheral events
    {
        centrality = step*(NSlices+0.5);
        return centrality;
    }    
    
    
    for (Int_t i=1; i<=NSlices; i++)
    {
//         cout << "x = " << fSlice->GetXi(i) << endl;
        if ( (det1-fSlice->GetXi(i))*(det1-fSlice->GetXi(i-1)) <= 0 )
        {
            centrality = step*(i+0.5);
		//cout<<"CENTRI = "<<centrality<<endl;
            isOK = true;
            break;
        }
    }

    if (!isOK)
        cout << "*** Warning *** GetCentrality: centrality is not found!" << endl;

    
    return centrality;
}

Float_t CentralityGetter::GetCentrality (Double_t det1, Double_t det2)
{    
    float centrality = -1;

    fCentrTree->GetEntry(0);
    Float_t step = fSlice->GetSlicesStep ();
    Int_t NSlices = fSlice->GetNSlices();
    TRandom* random = new TRandom;  
    random->SetSeed();
    if (isDet1Int){ 
        Float_t rand1 = random->Rndm()/* - 0.5*/;  /*cout << rand1 << endl;*/  
        det1 += rand1; 
    }
    if (isDet2Int){ 
        Float_t rand2 = random->Rndm()/* - 0.5*/;  /*cout << rand1 << endl;*/  
        det2 += rand2; 
    }
    
    if (fDet1Norm != -1)  det1 *= fDet1Norm;
    if (fDet2Norm != -1)  det2 *= fDet2Norm;
    
    det1 /= fSlice->GetDet1Max();
    det2 /= fSlice->GetDet2Max();    
    bool isOK = false;

     cout  << "   det1 = " << det1 << "   det2 = " << det2  << endl;
        
    Float_t x0 = (det2-fSlice->GetAi(0))/fSlice->GetBi(0);
    Float_t xn = (det2-fSlice->GetAi(NSlices-1))/fSlice->GetBi(NSlices-1);
    Int_t direction = fSlice->GetDirectionCentralEvents();

//     cout  << "   x0 = " << x0 << "   xn = " << xn  << endl;

    
    if ( (direction == 1 && det1 > x0) || (direction == 0 && det1 < x0) )  //most central events
    {
        centrality = step*(0.5);
        return centrality;
    }
    if ( (direction == 1 && det1 < xn) || (direction == 0 && det1 > xn) )  //most peripheral events
    {
        centrality = step*(NSlices+0.5);
        return centrality;
    }    
    
    for (Int_t i=1; i<NSlices; i++)
    {
        
        Float_t xi = (det2-fSlice->GetAi(i))/fSlice->GetBi(i);
        Float_t xi_1 = (det2-fSlice->GetAi(i-1))/fSlice->GetBi(i-1);

        if ( (det1-xi)*(det1-xi_1) <= 0 )
        {
            centrality = step*(i+0.5);
            isOK = true;
            break;
        }
    }        
        
    if (!isOK)
        cout << "*** Warning *** GetCentrality: centrality is not found!" << endl;
    
    return centrality;
}


void CentralityGetter::GetGlauberB (Float_t f, Float_t mu, Float_t k, TString GlaubFile, TString GlaubTreeName )
{
    
    TString fConfig;
    fConfig="Mult";
    TCanvas *c1 = new TCanvas("c1", "c1", 1500, 900);

    GlauberParGetter *gg = new GlauberParGetter;
    gg->SetSimTree ( GlaubFile, GlaubTreeName );
    gg->SetFitParams (f, mu, k);
    
    fCentrTree->GetEntry(0);
    
    Float_t step = fSlice->GetSlicesStep ();
    Int_t NSlices = fSlice->GetNSlices();
    Float_t norm = fSlice->GetDet1Max();  

    std::vector <Float_t> centrality;    
    for (UInt_t i=0; i<NSlices; i++)
        centrality.push_back( (i+0.5)*step );

   std::vector <Float_t> centrality2; 

    std::vector <Float_t> GlaubSigmaB_B;
    std::vector <Float_t> GlaubSigmaB;
    std::vector <Float_t> GlaubB;
    std::vector <Float_t> GlaubSigmaB_hist;
    std::vector <Float_t> GlaubB_hist;
    std::vector <Float_t> GlaubSigmaB_B_hist;
    std::vector <Float_t> GlaubSigmaNpart_Npart;
    std::vector <Float_t> GlaubSigmaNpart;
    std::vector <Float_t> GlaubNpart;
    std::vector <Float_t> GlaubSigmaNcoll_Ncoll;
    std::vector <Float_t> GlaubSigmaNcoll;
    std::vector <Float_t> GlaubNcoll;

    std::vector <Float_t> GlaubSigmaEstd_Estd;
    std::vector <Float_t> GlaubSigmaEstd;
    std::vector <Float_t> GlaubEstd;
//     c1->Divide(2,2);
   TH2F *hNpartCentr = new TH2F ("hNpartCentr", "hNpartCentr", 20, 0, 20,650,0,65); //NEW
    
    TH1F *hTotal = new TH1F ("hTotal", "hTotal", 200, 0, 20);
//TH1F *hTotal = new TH1F ("hTotal", "hTotal", 100, 0, 1);
    
   
    c1->cd();
    gPad->SetLogy();
    
    Int_t colors [20] = { kRed+0, kBlue+0, kMagenta+0, kGreen+0, kYellow+0,  
                          kRed+1, kBlue+1, kMagenta+1, kGreen+1, kYellow+1,
                          kRed+2, kBlue+2, kMagenta+2, kGreen+2, kYellow+2,
                          kRed+3, kBlue+3, kMagenta+3, kGreen+3, kYellow+3
    };
	Float_t centr;

	Float_t MultMax, MultMin;
    for (Int_t i=0; i<NSlices; i++)
    {
        centr=(i+0.5)*step; 
        
	if (fConfig=="Mult") {
	MultMax = 1e5;
        if (i>0) MultMax = fSlice->GetXi(i-1) * norm;   
	MultMin = fSlice->GetXi(i) * norm;   
	cout<<fSlice->GetXi(i) * norm<<endl;
				}
	else if (fConfig=="Spec") {
	MultMin=0.0;
	if (i>0) MultMin = fSlice->GetXi(i-1) * norm;
	MultMax = fSlice->GetXi(i) * norm;
	cout<<fSlice->GetXi(i) * norm<<endl;
				}
        TH1F *h1 = new TH1F ("h1", "", 200, 0, 20);
        h1->SetName(Form("hB_%f_%f", MultMin, MultMax));
        h1->SetLineColor(colors[i]);
        h1->GetXaxis()->SetTitle("b, fm");
	h1->GetYaxis()->SetTitle("Counts");
	h1->GetXaxis()->SetTitleSize(0.06);
	h1->GetYaxis()->SetTitleSize(0.06);
	h1->GetXaxis()->SetLabelSize(0.06);
	h1->GetYaxis()->SetLabelSize(0.06);

        std::cout << "MultMin = " << MultMin << "  MultMax = " << MultMax << std::endl;

        fSlice->GetXi(i);
        gg->GetBHisto(MultMin, MultMax, h1, 1e5);
        //h1->GetYaxis()->SetRangeUser(1, 5000);
        if (i==0)  h1->Draw();
        else       h1->Draw("same");
	float RMS=h1->GetRMS();
	float Mean=h1->GetMean();
        h1->Fit("gaus", "Q");
        TF1 *fFit = h1->GetFunction("gaus");
        fFit->SetLineColor(colors[i]);
        Float_t meanB = fFit->GetParameter(1); 
        Float_t sigmaB = fFit->GetParameter(2); 
        GlaubSigmaB_hist.push_back (RMS);
        GlaubB_hist.push_back (Mean);
	GlaubSigmaB_B_hist.push_back (RMS/Mean);
        float div=sigmaB/meanB;
        std::cout << "mean = " << meanB << "    sigma = " << sigmaB <<"meanhist = " << Mean << "SigmaRMS = " <<RMS<<"    area = " << h1->Integral() << std::endl;
          std::cout << "sigmaB/meanB = " <<div<<std::endl;
        GlaubSigmaB_B.push_back (sigmaB/meanB);
        GlaubSigmaB.push_back (sigmaB);
        GlaubB.push_back (meanB);
      
	hNpartCentr->Fill(meanB,centr); //NEW

        hTotal->Add(h1);
        //hTotalNpart->Add(h2); //NEW
        gPad->Update();
    }
/*      TLatex *t2 = new TLatex(0.5, 10, "0-5%");
	t2->Draw();
	TLatex *t3 = new TLatex(0.5, 2000, "Pb+Pb, 40 AGeV");
	t3->Draw(); */
    hTotal->Draw("same");
 // hTotalNpart->Draw("same"); //NEW
c1->SaveAs("B_inClasses.C");


TCanvas *GR1 = new TCanvas("GR1", "GR1", 1500, 900); 
TGraphErrors *grSigmaB4 = new TGraphErrors (NSlices, &(centrality[0]), &(GlaubSigmaB_B[0]), 0, 0);
        grSigmaB4->SetMarkerStyle(22);  
	grSigmaB4->SetLineColor(kRed);
grSigmaB4->Draw();

TFile *fileBSigmaB = new TFile("BSigmaB_part.root", "RECREATE");
	fileBSigmaB->cd();
	grSigmaB4->Write();
	fileBSigmaB->Close();

TGraphErrors *grSigmaB5 = new TGraphErrors (NSlices, &(centrality[0]), &(GlaubSigmaB_B_hist[0]), 0, 0);
        grSigmaB5->SetMarkerStyle(24);  
	grSigmaB5->SetLineColor(kBlue);
	//grSigmaB5->Draw("same");

//     c1->cd(3);
    if (false)
    {
        gPad->SetLogy();
        std::vector <Float_t> TempVecB, TempdB;
        for (UInt_t j=0; j<NSlices; j++){
            
            float temp_dB = fSlice->GetdB().at(j);
            float temp_B = fSlice->GetMeanB().at(j);
            float temp_sB = fSlice->GetSigmaB().at(j);
            float temp_dsB = fSlice->GetdSigmaB().at(j);
            
            TempVecB.push_back(temp_sB/temp_B);
            
            float ddd = TMath::Sqrt ( (temp_dsB/temp_B)*(temp_dsB/temp_B) + (temp_dsB/temp_B/temp_B*temp_dB)*(temp_dsB/temp_B/temp_B*temp_dB) );
            
           cout << "d_sigma = " << (temp_dsB/temp_B) << endl;
    //         cout << "d_b = " << (temp_dsB/temp_B/temp_B*temp_dB) << endl;
            
            TempdB.push_back( ddd );
		 
        }

	TCanvas *GR = new TCanvas("GR", "GR", 1500, 900); 

        TGraphErrors *grSigmaB = new TGraphErrors (NSlices, &(centrality[0]), &(TempVecB[0]), 0, &(TempdB[0]));
        grSigmaB->SetMarkerStyle(23);    
        grSigmaB->GetXaxis()->SetTitle( "Centrality" );
        grSigmaB->GetYaxis()->SetTitle( "sigma_{B}/<B>" );  
	grSigmaB->GetXaxis()->SetTitleSize(0.06);
grSigmaB->GetYaxis()->SetTitleSize(0.06);
grSigmaB->GetXaxis()->SetLabelSize(0.06);
grSigmaB->GetYaxis()->SetLabelSize(0.06);  
        grSigmaB->GetYaxis()->SetRangeUser(0.01, 0.5);
        cout << "d_sigma = " <<  endl;
        grSigmaB->Draw("APL");

        TGraphErrors *grSigmaB1 = new TGraphErrors (NSlices, &(centrality[0]), &(GlaubSigmaB_B[0]), 0, 0);
        grSigmaB1->SetMarkerStyle(22);    
        grSigmaB1->SetMarkerColor(kRed);    
        grSigmaB1->SetLineColor(kRed);    

        grSigmaB1->Draw("PLsame");

	
    }

//     c1->cd(4);
    
    TCanvas *c2 = new TCanvas("c2", "c2", 1500, 900);
    
    TGraphErrors *grB;
    if (false)
    {    
        grB = new TGraphErrors (NSlices, &(centrality[0]), &(fSlice->GetMeanB()[0]), 0, &(fSlice->GetSigmaB()[0]));
        grB->SetMarkerStyle(23);    
        grB->GetXaxis()->SetTitle( "Event classes, %" );
        grB->GetYaxis()->SetTitle( "<b> #pm #sigma, fm" );    
        grB->GetYaxis()->SetRangeUser(0.0, 20.0);
        grB->GetXaxis()->SetTitleSize(0.06);
        grB->GetYaxis()->SetTitleSize(0.06);
	grB->GetXaxis()->SetLabelSize(0.06);
	grB->GetYaxis()->SetLabelSize(0.06); 
        grB->Draw("APL");
	TLatex *t3 = new TLatex(10, 15, "Pb+Pb, 40 AGeV");
	t3->Draw();         
TFile *file = new TFile("B_spect.root", "RECREATE");
	file->cd();
	grB->Write();
	file->Close();
    }
    
    TGraphErrors *grB1 = new TGraphErrors (NSlices, &(centrality[0]), &(GlaubB[0]), 0, &(GlaubSigmaB[0]));
    grB1->SetMarkerStyle(22);    
    grB1->SetMarkerColor(kRed);    
    grB1->SetLineColor(kRed);    
    grB1->GetXaxis()->SetTitle( "Event classes, %" );
    grB1->GetYaxis()->SetTitle( "<b> #pm #sigma, fm" );   
    grB1->GetXaxis()->SetTitleSize(0.06);
    grB1->GetYaxis()->SetTitleSize(0.06);
    grB1->GetXaxis()->SetLabelSize(0.06);
    grB1->GetYaxis()->SetLabelSize(0.06);  
    grB1->Draw("APL");
TLatex *t4 = new TLatex(10, 15, "Pb+Pb, 40 AGeV");
	t4->Draw();
TFile *file = new TFile("B_VETO.root", "RECREATE");
	file->cd();
	grB1->Write();
	file->Close();

 TCanvas *cc2 = new TCanvas("cc2", "cc2", 1200, 900);
cc2->cd();
	 TGraphErrors *grNpart1 = new TGraphErrors (NSlices, &(centrality[0]), &(GlaubNpart[0]), 0, &(GlaubSigmaNpart[0]));
    grNpart1->SetMarkerStyle(22);    
    grNpart1->SetMarkerColor(kRed);    
    grNpart1->SetLineColor(kRed);    
    grNpart1->GetXaxis()->SetTitle( "Centrality" );
    grNpart1->GetYaxis()->SetTitle( "N_{part}" );    
    grNpart1->Draw("APL");

 TCanvas *cc3 = new TCanvas("cc3", "cc3", 1500, 900);
cc3->cd();

 TGraphErrors *grNcoll1 = new TGraphErrors (NSlices, &(centrality[0]), &(GlaubNcoll[0]), 0, &(GlaubSigmaNcoll[0]));
    grNcoll1->SetMarkerStyle(22);    
    grNcoll1->SetMarkerColor(kRed);    
    grNcoll1->SetLineColor(kRed);    
    grNcoll1->GetXaxis()->SetTitle( "Centrality" );
    grNcoll1->GetYaxis()->SetTitle( "N_{coll}" );    
    grNcoll1->Draw("APL");

    
    if (false)
    { 
        TLegend* leg1 = new TLegend(0.7, 0.75, 0.85, 0.89);    
        leg1->AddEntry(grB, "Model", "p"); 
        leg1->AddEntry(grB1, "MC-Glauber", "p");
        leg1->Draw("same");     
    }
    gPad->Update();


    
    

    
}






