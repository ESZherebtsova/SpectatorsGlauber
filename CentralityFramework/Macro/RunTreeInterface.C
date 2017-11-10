//#include "../src/TreeInterface.cxx"
#include <iostream>
#include "TSystem.h"
int RunTreeInterface (/*Int_t FileNumFirst=0, Int_t FileNumLast=9*/)
{
    TString CentralityFrameworkDir = "/home/liza/CentralityFramework/CentralityFramework/";    
    gSystem->Load( CentralityFrameworkDir + "build/libCentrality");

  
 TFile *InFileDir = new TFile( "/home/liza/CentralityFramework/CentralityFramework/Macro/All_0705.root","read");
    TString OutFileDir = CentralityFrameworkDir + "containers/" ;
    TString OutFileName = Form("container.root");
    
    
TTree *t = (TTree*)InFileDir->Get("tree");

    TreeInterface *ti = new TreeInterface();
    ti->SetOutFileName (OutFileDir + OutFileName) ;
    ti->SetInTChain (t);
    ti->SetNEntries (0);
    ti->WriteCentralityContainer();
    
}
