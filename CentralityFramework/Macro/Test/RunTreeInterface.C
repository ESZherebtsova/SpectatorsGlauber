
#include "TreeInterface.cxx"

int RunTreeInterface (/*Int_t FileNumFirst=0, Int_t FileNumLast=9*/)
{
    TString CentralityFrameworkDir = "/home/liza/CentralityFramework/CentralityFramework/";    
    gSystem->Load( CentralityFrameworkDir + "build/libCentrality");

    TFile *InFileDir = new TFile( "/home/liza/CentralityFramework/CentralityFramework/Macro/Test/Tracks_0705.root","read");
    TString OutFileDir = CentralityFrameworkDir + "Glauber/root_files/" ;
    TString OutFileName = Form("cbm_urqmd_10AGeV.root");
    
   /* TChain *t = new TChain("fDataTree");
    
    for (Int_t i=FileNumFirst; i<=FileNumLast; ++i)
        t->Add( InFileDir + Form( "%d/tree.root", i ) );*/
    

TTree *t = (TTree*)InFileDir->Get("tree");

    TreeInterface *ti = new TreeInterface();
    ti->SetOutFileName (OutFileDir+ OutFileName); 
   ti->SetInTChain (t);

    //ti->SetNEntries (0);
    ti->WriteCentralityContainer();
    
}
