
#ifndef TreeInterface_H
#define TreeInterface_H 1

#include <vector>
#include "TNamed.h"

#include "TFile.h"
#include "TTree.h"
#include "TString.h"

#include "TChain.h"

//#include "DataTreeEvent.h"
#include "CentralityEventContainer.h"

class TreeInterface : public TNamed
{

    public:
    TreeInterface ();
 
    
    void WriteCentralityContainer();

    void SetOutFileName (TString OutFileName) {fOutFileName = OutFileName;}
    void SetInFileName  (TString InFileName)  {fInFileName = InFileName;}
    void SetNEntries (int n) { nEntries = n; }

    void SetInTChain  (TTree* tree)  { fInTree = (TTree*)tree; }

private:

    TString fOutFileName;
    TString fInFileName;
    
/**   Data members  **/
    //DataTreeEvent *fEvent;
    
    TFile *fInFile ;
    TTree *fInTree ;    
    
    TTree *fOutTree;
    TFile *fOutFile;
   // CentralityEventContainer *fContainer;

    
    Int_t nEntries;
    
    ClassDef(TreeInterface, 2);

};


#endif
