void RunGlauberParGetter()
{
    
    TString CentralityFrameworkDir = "/home/liza/CentralityFramework/CentralityFramework/";
    gSystem->Load( CentralityFrameworkDir + "build/libCentrality");  
    gStyle->SetOptStat(0000);    
    TString dir = CentralityFrameworkDir;    

    TString tpc = "M_{trk}";
    TString veto = "E_{veto}";
   // TString psd2_det = "E_{PSD}^{2}";
   // TString psd3_det = "E_{PSD}^{3}";

    TString ContainerFile = "/home/liza/CentralityFramework/CentralityFramework/Macro/test_cont.root";
//TString ContainerFile = "/home/liza/CentralityFramework/CentralityFramework/Macro/container.root";
    CentralityManager *manager = new CentralityManager;
    manager->SetDirectory(dir);
    manager->IsSimData(true);                               // write impact parameter value - true for CBM (mc simulations)
    manager->Det1IsInt(true);                               // if multiplicity used as det1 - true; if as det2 - manager->Det2IsInt(true);
//  manager->Det2IsInt(true); 
    manager->AddDetector(veto);
//  manager->AddDetector(tpc);

    dir += "output/";
    TString SlicesFileName = dir + "test.root";
    
    manager->LoadCentalityDataFile( SlicesFileName );

    
    TString DataFileName = ContainerFile;
    TFile *DataFile = new TFile ( ContainerFile, "read" );    

    CentralityEventContainer *container = new CentralityEventContainer;
    TTree *ContTree = (TTree*)DataFile->Get("container");
    ContTree->SetBranchAddress("CentralityEventContainer", &container);
        
    Int_t n = ContTree->GetEntries();
    std::cout << "n = " << n  << std::endl;

    TCanvas *c1 = new TCanvas("c1", "canvas", 600, 600);
    
    Float_t f=1, mu=1.10262, k=52.3637;
    TString GlaubFile = "PbPb_NA49.root";
    TString GlaubTreeName = "nt_Pb_Pb";
    CentralityGetter *getter = manager->GetCentralityGetter();
    getter->GetGlauberB( f, mu, k, GlaubFile, GlaubTreeName );


    
}
