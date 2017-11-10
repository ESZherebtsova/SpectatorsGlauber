#include <vector>

#pragma link C++ class vector<float>;


void RunCentralityFrameworkWithHisto(/*TH1D *hIn*/)
{

TFile *InFile2 = new TFile("generated_func.root", "read") ;
TH1D *hIn2 = (TH1D*) InFile2->Get("glaub");

    TString CentralityFrameworkDir = "/home/liza/CentralityFramework/CentralityFramework/";
    gSystem->Load( CentralityFrameworkDir + "build/libCentrality");  

CentralityEventContainer *fContainer = new CentralityEventContainer;
    ContFile = new TFile ("test_cont.root", "recreate");    
    ContTree = new TTree ( "container", "container" );
    ContTree->Branch("CentralityEventContainer", "CentralityEventContainer", &fContainer);
    ContTree->SetDirectory(0); 

    CentralityDetectorEvent TrakingDet ; 
    fContainer->AddDetector(TrakingDet);
   //CentralityDetectorEvent veto ; 
   // fContainer->AddDetector(veto);
    
Int_t iBin, VetoEn;
    for (iBin = 0; iBin<hIn2->GetNbinsX(); ++iBin )
    {
        Int_t Mult = iBin;
        std::vector <Float_t> tracks (1, Mult);
        
        for (Int_t j = 0; j<hIn2->GetBinContent(iBin+1); ++j )
        {
            fContainer->AddDetectorEvent (0, tracks);
            ContTree->Fill(); 
        }
    }
    

    cout << "Writing centrility container..." << endl;
    ContTree->Write();
    ContFile->Close();
    
    TString OutDir = CentralityFrameworkDir + "output/";    
    //TString ContainerFile = CentralityFrameworkDir + "containers/" + "cbm_urqmd_merged.root";
    TString OutFileName = "test";    // without .root!

    CentralityManager *manager = new CentralityManager;
    manager->SetDirectory(OutDir);
     
    manager->AddDetector( "Tracking detector" );  
//  manager->AddDetector( "veto" );  


    manager->SetOutFileName(OutFileName);
    manager->SetContainerFileName ( "test_cont.root" );  
//  manager->SetContainerFileName ( "container.root" ); 

    manager->IsSimData ( false ); 
  // manager->SetNormalization (299558);                                 // set full integral (calculated with Glauber model, for mc simulation we don't neeed it?)
    manager->Det1IsInt(true);
//manager->Det2IsInt(true);                                            // if multiplicity used as det1 - true; if as det2 - manager->Det2IsInt(true);
    manager->Do1DAnalisys(true);                                      // 1D slicing
    manager->SetDetectorsForCentralityAnalisys ("Tracking detector"/*,"veto"*/);    // for 2D slicing give 2 arguments for function (for example sts_det, psd1_det)
    manager->SetCentralityMax(100);                                      // set maximum value for centrality, more peripheral events will not be analysed
    manager->SetDirectionCentralEvents(1);                               // if impact parameter and detector signal is correlated = 0 (forfard energy), if anticorelated (tracks) = 1   
    manager->SetSliceStep (5);                                           // slice step (width) in percents

    manager->RunSliceFinder();
//manager->FindMeanSignalsInSlice (manager->RunSliceFinder());
    manager->WriteCentralityFile();
  manager->QA();
        

}
