#include "GlauberParGetter.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TMath.h"
#include "TRandom.h"

ClassImp(GlauberParGetter)


// -----   Default constructor   -------------------------------------------
GlauberParGetter::GlauberParGetter() 
  : TNamed()
{

}

void GlauberParGetter::TestFunc(Int_t nf, Float_t f0, Float_t f1, Int_t nsigma, Int_t nEvents)
{
}


void GlauberParGetter::SetSimTree(TString filename, TString treename)
{    
    TFile *fSim = new TFile (filename.Data());
    fSimTree = (TTree*) fSim->Get( treename );
    
    if (!fSimTree) {
        std::cout << "SetSimHistos: *** Error - " << std::endl;
        exit(EXIT_FAILURE);
    }
    
    fSimTree->SetBranchAddress("Npart", &fNpart);
    fSimTree->SetBranchAddress("Ncoll", &fNcoll);
    fSimTree->SetBranchAddress("B"    , &fB);
    fSimTree->SetBranchAddress("NspecTarget"    , &fNspecTarget);
    fSimTree->SetBranchAddress("NpartTarget"    , &fNpartTarget);
//  fSimTree->SetBranchAddress("EccPart"    , &fEstd);        
}

void GlauberParGetter::DrawHistos (Bool_t isSim, Bool_t isData, Bool_t isGlauber, Bool_t isNBD )
{
//    TCanvas *c1 = new TCanvas("c1", "canvas", 1500, 900);

}

void GlauberParGetter::GetBHisto (Float_t MultMin,  Float_t MultMax, TH1F *hB, Int_t n)
{

    Float_t Na;    
    SetNBDhist(fMu, fK);
  
    TRandom* random = new TRandom;  
    random->SetSeed();

    for (Int_t i=0; i<n; i++)
    {
        fSimTree->GetEntry(i);
	//Na = fF*fNpartTarget + (1-fF)*fNspecTarget;
          Na = fF*fNpart + (1-fF)*fNcoll;
//        Na = TMath::Power(fNpart, fF);    
//        Na = TMath::Power(fNcoll, fF);   
        
        Float_t nHits = 0;
        for (Int_t j=0; j<Na; j++){
            nHits += (int)hNBD->GetRandom();
//             std::cout << hNBD->GetRandom() << std::endl;
        }
//         std::cout << "nHits = " << nHits << "  b = " << fB <<  std::endl;
        
        Float_t rand1 = random->Rndm()/* - 0.5*/;  /*cout << rand1 << endl;*/  
        nHits += rand1;
        
        if ( nHits < MultMax && nHits > MultMin )
        {
            hB->Fill(fB);
        }
            
    }
    
}


void GlauberParGetter::GetNpartHisto (Float_t MultMin,  Float_t MultMax, TH1F *hNpart, Int_t n)
{

    Float_t Na;    
    SetNBDhist(fMu, fK);
  
    TRandom* random = new TRandom;  
    random->SetSeed();

    for (Int_t i=0; i<n; i++)
    {
        fSimTree->GetEntry(i);
        Na = fF*fNpart + (1-fF)*fNcoll;
//      Na = TMath::Power(fNpart, f);    //TODO Try later
//      Na = TMath::Power(fNcoll, f);    //TODO Try later
        
        Float_t nHits = 0;
        for (Int_t j=0; j<Na; j++){
            nHits += (int)hNBD->GetRandom();
//             std::cout << hNBD->GetRandom() << std::endl;
        }
//         std::cout << "nHits = " << nHits << "  b = " << fB <<  std::endl;
        
        Float_t rand1 = random->Rndm()/* - 0.5*/;  /*cout << rand1 << endl;*/  
        nHits += rand1;
        
        if ( nHits < MultMax && nHits > MultMin )
        {
            hNpart->Fill(fNpart);
        }
            
    }
    
}

void GlauberParGetter::GetNcollHisto (Float_t MultMin,  Float_t MultMax, TH1F *hNcoll, Int_t n)
{

    Float_t Na;    
    SetNBDhist(fMu, fK);
  
    TRandom* random = new TRandom;  
    random->SetSeed();

    for (Int_t i=0; i<n; i++)
    {
        fSimTree->GetEntry(i);
        Na = fF*fNpart + (1-fF)*fNcoll;
//      Na = TMath::Power(fNpart, f);    //TODO Try later
//      Na = TMath::Power(fNcoll, f);    //TODO Try later
        
        Float_t nHits = 0;
        for (Int_t j=0; j<Na; j++){
            nHits += (int)hNBD->GetRandom();
//             std::cout << hNBD->GetRandom() << std::endl;
        }
//         std::cout << "nHits = " << nHits << "  b = " << fB <<  std::endl;
        
        Float_t rand1 = random->Rndm()/* - 0.5*/;  /*cout << rand1 << endl;*/  
        nHits += rand1;
        
        if ( nHits < MultMax && nHits > MultMin )
        {
            hNcoll->Fill(fNcoll);
        }
            
    }
    
}

void GlauberParGetter::GetEstdHisto (Float_t MultMin,  Float_t MultMax, TH1F *hEstd, Int_t n)
{

    Float_t Na;    
    SetNBDhist(fMu, fK);
  
    TRandom* random = new TRandom;  
    random->SetSeed();

    for (Int_t i=0; i<n; i++)
    {
        fSimTree->GetEntry(i);
        Na = fF*fNpart + (1-fF)*fNcoll;
//      Na = TMath::Power(fNpart, f);    //TODO Try later
//      Na = TMath::Power(fNcoll, f);    //TODO Try later
        
        Float_t nHits = 0;
        for (Int_t j=0; j<Na; j++){
            nHits += (int)hNBD->GetRandom();
//             std::cout << hNBD->GetRandom() << std::endl;
        }
//         std::cout << "nHits = " << nHits << "  b = " << fB <<  std::endl;
        
        Float_t rand1 = random->Rndm()/* - 0.5*/;  /*cout << rand1 << endl;*/  
        nHits += rand1;
        
        if ( nHits < MultMax && nHits > MultMin )
        {
            hEstd->Fill(fEstd);
        }
            
    }
    
}


void GlauberParGetter::SetNBDhist(Double_t mu, Double_t k)
{
    // Interface for TH1F.
    Int_t nBins = 50;
    
    hNBD = new TH1F("hNBD","",nBins, 0, nBins);
    hNBD->SetName(Form("nbd_%f_%f",mu,k));
    hNBD->SetDirectory(0);
    
    for (Int_t i=0; i<nBins; ++i) 
    {
        Double_t val = NBD(i, mu, k);
        if (val>1e-20) hNBD->SetBinContent(i+1, val);
//         std::cout << "val " << val << std::endl;    
    }

}


Double_t GlauberParGetter::NBD(Double_t n, Double_t mu, Double_t k) const
{
    // Compute NBD.
    Double_t F;
    Double_t f;

    if (n+k > 100.0) 
    {
        // log method for handling large numbers
        F  = TMath::LnGamma(n + k)- TMath::LnGamma(n + 1.)- TMath::LnGamma(k);
        f  = n * TMath::Log(mu/k) - (n + k) * TMath::Log(1.0 + mu/k);
        F = F+f;
        F = TMath::Exp(F);
    } 
    else 
    {
        F  = TMath::Gamma(n + k) / ( TMath::Gamma(n + 1.) * TMath::Gamma(k) );
        f  = n * TMath::Log(mu/k) - (n + k) * TMath::Log(1.0 + mu/k);
        f  = TMath::Exp(f);
        F *= f;
    }

    return F;
}

