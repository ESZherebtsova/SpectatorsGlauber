#include "TreeInterface.h"
//#include "../config/ContConfig.C"

ClassImp(TreeInterface)

using std::cout;
using std::endl;
using std::flush;


// -----   Default constructor   -------------------------------------------
TreeInterface::TreeInterface() 
  : TNamed(),
    //fEvent (new DataTreeEvent),
    fInFileName(""),
   // fPsdGeomConfig ("CBM_44"),
  //  nEntries (0)
{
}

void TreeInterface::WriteCentralityContainer ()
{
    
    
    if (fInFileName != "")
    {
        fInFile = new TFile ("Tracks_0705.root");
        fInTree = (TTree*) fInFile->Get("tree"); 
    }
    
int number_tracks;
	float VetoEn;
    fInTree->SetBranchAddress("VetoEn", &VetoEn);
    fInTree->SetBranchAddress("number_tracks", &number_tracks);

    //fInTree->SetBranchAddress("DTEvent", &fEvent);
    fContainer = new CentralityEventContainer;
    
   // CentralityDetectorEvent psd; 
    CentralityDetectorEvent tpc; 
    CentralityDetectorEvent veto; 
    
     fContainer->AddDetector(tpc);  
     fContainer->AddDetector(veto); 
            
    fOutFile = new TFile (fOutFileName.Data(), "recreate");    
    fOutTree = new TTree ( "container", "container" );
    fOutTree->Branch("CentralityEventContainer", "CentralityEventContainer", &fContainer);
    fOutTree->SetDirectory(0);  
    
   /* if (!nEntries) nEntries = fInTree->GetEntries();
    
    cout << "Reading " << nEntries << " events from chain..." << endl;
    for (Int_t iEntry = 0; iEntry<nEntries; iEntry++)
    {
        
        if ((iEntry+1) % 100 == 0) cout << "Event # " << iEntry+1 << "... \r" << flush; 
        
        fInTree->GetEntry (iEntry);
        
        if (!isSelectedEvent (fEvent)) continue;
        
        //int nTracks_Ref = GetRefMultiplicity(fEvent);
                

       /* std::vector <float> psd1 = SetPsdVector(1);
        std::vector <float> psd2 = SetPsdVector(2);
        std::vector <float> psd3 = SetPsdVector(3);*/
        std::vector <float> (1,sts);
	std::vector <float> (1,veto);

int entry;
while(entry < fInTree->GetEntries()) {
		fInTree->GetEntry(entry);
		veto.push_back(VetoEn);
		sts.push_back(number_tracks);
		entry++;
	}

        fContainer->AddDetectorEvent (0, sts);
        /*fContainer->AddDetectorEvent (1, psd1);
        fContainer->AddDetectorEvent (2, psd2);        
        fContainer->AddDetectorEvent (3, psd3);   */ 
	 fContainer->AddDetectorEvent (0, veto);    

      /*  fContainer->SetRunId (fEvent->GetRunId());
        fContainer->SetEventId(fEvent->GetEventId());
        fContainer->SetB (fEvent->GetImpactParameter());*/

        fOutTree->Fill();        
        
    }

    cout << "Writing centrility container..." << endl;
    fOutTree->Write();
    fOutFile->Close();
    cout << "Done! Centrality container " <<  fOutFileName <<  " created!" << endl;
    
}


    return psdEnergies;
}



