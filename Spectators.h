

#ifndef Spectators_h
#define Spectators_h

#include <TROOT.h>
#include <TFile.h>
#include <iostream>  
#include <string>
#include <vector>
#include "TTree.h"
using namespace std; 


class Spectators {
public :
   TTree          *fSimTree;   

float fNpartA, fNcoll, fB, fNpart;
int MassNumber=208;

   // List of branches
   

   Spectators(TTree *nt_Pb_Pb=0);
   virtual ~Spectators();
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(); 
   virtual Bool_t   Notify();
 
};

#endif

#ifdef Spectators_cxx
Spectators::Spectators(TTree *nt_Pb_Pb) : fSimTree(0) 
{
   if (nt_Pb_Pb== 0) {
      cout<<"There is no tree";
   }
   Init(nt_Pb_Pb);
}

Spectators::~Spectators()
{
   if (!fSimTree) return;
   delete fSimTree->GetCurrentFile();
}

Int_t Spectators::GetEntry(Long64_t entry)
{
   if (!fSimTree) return 0;
   return fSimTree->GetEntry(entry);
}
Long64_t Spectators::LoadTree(Long64_t entry)
{
   if (!fSimTree) return -5;
   Long64_t centry = fSimTree->LoadTree(entry);
   if (centry < 0) return centry;
   
}

void Spectators::Init(TTree *nt_Pb_Pb)
{
 if (!nt_Pb_Pb) return;
   fSimTree = nt_Pb_Pb;
fSimTree->SetBranchAddress("NpartA", &fNpartA);
fSimTree->SetBranchAddress("Ncoll", &fNcoll);
fSimTree->SetBranchAddress("B", &fB);
fSimTree->SetBranchAddress("Npart", &fNpart);

   Notify();
}

Bool_t Spectators::Notify()
{

   return kTRUE;
}


#endif
