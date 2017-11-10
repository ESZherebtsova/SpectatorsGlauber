
#ifndef GlauberParGetter_H
#define GlauberParGetter_H 1

#include <vector>
#include "TString.h"
#include "TNamed.h"
#include "TH1F.h"
#include "TTree.h"
#include "TMinuit.h"

class GlauberParGetter : public TNamed
{

    public:

	/**   Default constructor   **/
	GlauberParGetter() ;
        void TestFunc(Int_t nf, Float_t f0, Float_t f1, Int_t nsigma, Int_t nEvents);
        
        void SetSimTree (TString filename, TString treename = "nt_Pb_Pb");
        void GetBHisto (Float_t MultMin,  Float_t MultMax, TH1F* hB, Int_t n = 10000);
        void GetNpartHisto (Float_t MultMin,  Float_t MultMax, TH1F* hNpart, Int_t n = 10000);
	void GetNcollHisto (Float_t MultMin,  Float_t MultMax, TH1F* hNcoll, Int_t n = 10000);
	void GetEstdHisto (Float_t MultMin,  Float_t MultMax, TH1F* hEstd, Int_t n = 10000);
        void DrawHistos (Bool_t isSim = true, Bool_t isData = true, Bool_t isGlauber = false, Bool_t isNBD = false);
	
        
        Double_t NBD(Double_t n, Double_t mu, Double_t k) const;
        void SetNBDhist(Double_t mu, Double_t k);
        /**   Destructor   **/
	virtual ~GlauberParGetter() {};
        
        
        void SetFitParams (Float_t f, Float_t mu, Float_t k) { fF = f;  fMu = mu;  fK = k; }
        
        void SetOutDirName (TString name) { fOutDirName = name; }
        TH1F *GetGlauberFitHisto () { return hGlaub; }
        TH1F *GetNBDHisto ()        { return hNBD;   }
        
    private:

	/**   Data members  **/
        TH1F *hNBD, *hGlaub, *hB, *hNpart,*hNcoll, *hEstd, *hNspecTarget, *hNpartTarget;
        TTree* fSimTree;
        
        Float_t fNpart, fNcoll, fB, fEstd, fNspecTarget, fNpartTarget;
        Float_t fF, fMu, fK;

        TString fOutDirName;
        ClassDef(GlauberParGetter, 2);

};


#endif
