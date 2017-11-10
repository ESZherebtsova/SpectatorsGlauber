
void RunCentralityFramework()
{
    TString CentralityFrameworkDir = "/home/liza/CentralityFramework/CentralityFramework/";
    gSystem->Load( CentralityFrameworkDir + "build/libCentrality");  
    
    TString OutDir = CentralityFrameworkDir + "output/";    
    TString ContainerFile = CentralityFrameworkDir + "Macro/" + "test_cont.root";
    TString OutFileName = "test";    // without .root!
    
    
    TString sts_det = "M_{STS}";
    TString psd1_det = "E_{PSD}^{1}";
    TString psd2_det = "E_{PSD}^{2}";
    TString psd3_det = "E_{PSD}^{3}";
    
//     TCut cuts = "det1 > 0.6 - 0.6/0.75*det2";
//     TCut cuts = "det2 > 0.6 - 0.6/0.75*det1";    
    TCut cuts = "";


    CentralityManager *manager = new CentralityManager;
    manager->SetDirectory(OutDir);
     
//  For CentralityFinder 
//  ************************************   
    manager->AddDetector(sts_det );  
    manager->AddDetector(psd1_det);
    manager->AddDetector(psd2_det);
    manager->AddDetector(psd3_det);

    manager->SetOutFileName(OutFileName);
    manager->SetContainerFileName ( ContainerFile );  

    manager->SetNormalization (1485808);                  // set full integral (calculated with Glauber model, for mc simulation we don't neeed it?)

    manager->IsSimData(true);                               // write impact parameter value - true for CBM (mc simulations)
    manager->Det1IsInt(true);                               // if multiplicity used as det1 - true; if as det2 - manager->Det2IsInt(true);
//     manager->Do1DAnalisys(true);                            // 1D slicing
    manager->SetDetectorsForCentralityAnalisys (sts_det);   // for 2D slicing give 2 arguments for function (for example sts_det, psd1_det)
    manager->SetCentralityMax(100);                         // set maximum value for centrality, more peripheral events will not be analysed
    manager->SetDirectionCentralEvents(1);                  // 1 - if impact parameter and detector signal is correlated = 1 (PSD1), if anticorelated (STS) = 0   
    manager->SetSliceStep (5);                              // slice step (width) in percents
    manager->SetCuts (cuts);                                // set additional cuts (obsolete probably, since we have config file for containers filling)
    
    manager->RunSliceFinder();
    manager->WriteCentralityFile();
    manager->QA();

//     manager->IsSimData(true);
//     manager->Det1IsInt(true);
//     manager->Do1DAnalisys(false);
//     manager->SetDetectorsForCentralityAnalisys (sts_det, psd1_det);
//     manager->SetCentralityMax(100);
//     manager->SetDirectionCentralEvents(1);
//     manager->SetSliceStep (5);
//     manager->SetCuts (cuts);
//     
//     manager->RunSliceFinder();
//     manager->WriteCentralityFile();
//     manager->QA();


}






