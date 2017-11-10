
void RunCentralityGetterQA( TString SlicesFile = "/home/liza/CentralityFramework/CentralityFramework/output/test.root" /*TH1D *hIn*/  )
{

    TString CentralityFrameworkDir = "/home/liza/CentralityFramework/CentralityFramework/";
    gSystem->Load( CentralityFrameworkDir + "build/libCentrality");


    TFile *InFile = new TFile("generated_func.root", "read") ;
    TH1D *hIn = (TH1D*) InFile->Get("glaub");

/*  TFile *InFile = new TFile("EnergyVeto_NA49.root", "read") ;
    TH1D *hIn = (TH1D*) InFile->Get("hEnergyVeto");*/

    CentralityManager* fCentralityManager;
    fCentralityManager = new CentralityManager();
    fCentralityManager -> SetDirectory(CentralityFrameworkDir);
    fCentralityManager -> LoadCentalityDataFile(SlicesFile);
    fCentralityManager -> Det1IsInt(true); 
//fCentralityManager -> Det2IsInt(true);                     
    
    TH1F *hTest = new TH1F("hTest", "hTest", 100, 0, 100 );
    
    for (Int_t iBin = 0; iBin<hIn->GetNbinsX(); ++iBin )
    {
        Int_t Mult = iBin;        
        //std::cout << iBin << std::endl; 
        for (Int_t j = 0; j<hIn->GetBinContent(iBin+1); ++j )
        {
            double c = fCentralityManager->GetCentrality(Mult);
            hTest->Fill(c);
        }
    }    
    
    hTest->Draw("E");



TFile *DataFile = new TFile ( "test_cont.root", "read" );    
//TFile *DataFile = new TFile ( "test_contSum.root", "read" );  
    CentralityEventContainer *container = new CentralityEventContainer;
     TTree *ContTree = (TTree*)DataFile->Get("container");
    ContTree->SetBranchAddress("CentralityEventContainer", &container);

//CentralityEventContainer *container2 = new CentralityEventContainer;
//TTree *ContTree2 = (TTree*)DataFile->Get("container2");
    //ContTree2->SetBranchAddress("CentralityEventContainer", &container2);

    TH1F *hCentr = new TH1F ("hCentr", "", 550, 0, 550);
 TH1F *hCentr2 = new TH1F ("hCentr2", "", 101, 0., 101.);
 TH1F *hCentr3 = new TH1F ("hCentr3", "", 100, 0, 100);
TH2F *h2DCor = new TH2F ("h2DCor", "", 100, 0, 100, 500, 0, 500);


    Float_t PSD1, PSD2, PSD3, PSD12, M;
    Float_t Centrality;
    
    Int_t n = ContTree->GetEntries();
    // Int_t n2 = ContTree2->GetEntries();
    //std::cout << "n = " << n  <<"n2 = "<<n2<< std::endl;

    TCanvas *c1 = new TCanvas("c1", "canvas", 900, 900);

    Int_t RunId = 0;
//     manager->SetGetterRunId (RunId);
    
    
    CentralityGetter *getter = fCentralityManager->GetCentralityGetter();
    
    CentralitySlice *fSlice = new CentralitySlice;
    TFile *fCentrFile = new TFile("test.root", "READ");
    TTree *fCentrTree1 = (TTree*) fCentrFile->Get("CentrTree");    
    fCentrTree1->SetBranchAddress("CentralitySlice", &fSlice);   
    fCentrTree1->GetEntry(0);        
 /*TTree *fCentrTree2 = (TTree*) fCentrFile->Get("CentrTree2"); 
fCentrTree2->SetBranchAddress("CentralitySlice", &fSlice);   
    fCentrTree2->GetEntry(0); */

    Int_t NSlices = fSlice->GetNSlices();
cout<<"bhjjb = "<<NSlices<<endl;
    Int_t Int,j;
     for (Int_t i=0; i<NSlices; i++)
    {
        std::cout << fSlice->GetXi(i)*fSlice->GetDet1Max() << std::endl;
        gPad->Update();
        Float_t x = fSlice->GetXi(i)*fSlice->GetDet1Max();
         Double_t xr = gPad->GetX2()-gPad->GetX1();
         double x1 = (x-gPad->GetX1()) / xr;
         TLine l2;
	cout<<" x= "<<x<<"x    = "<<fSlice->GetXi(i)<<"xr = "<<xr<<"x1 = "<<x1<<endl;
         l2.SetLineColor(11);
         l2.DrawLineNDC(x1, 0.10, x1, 0.9); }

    
    Int_t i;
     for (i=0; i<n; i++)
     {
	
         ContTree->GetEntry(i);


if (RunId != container->GetRunId())
         {
            RunId = container->GetRunId();
             manager->SetGetterRunId (RunId);
         }
//PSD1 = container->GetDetectorWeight(0);

 /*if (i<n2) {
	
         ContTree2->GetEntry(i);
if (RunId != container2->GetRunId())
         {
            RunId = container2->GetRunId();
             manager->SetGetterRunId (RunId);
         }
M = container2->GetDetectorWeight(0); 
 //mult.push_back(container2->GetDetectorWeight(0));
hCentr2->Fill(M);
}*/
         //Centrality = fCentralityManager->GetCentrality (M,PSD1);
	//Centrality = fCentralityManager->GetCentrality (container->GetDetectorWeight(0));
	//cout<<"CENTRA = "<<Centrality<<endl;
  //      hCentr->Fill(PSD1);
//	  hCentr3->Fill(Centrality);
	//h2DCor->Fill (Centrality, PSD1);
     //}
    

 /*for (Int_t i=0; i<n2; i++)
     {
	
         ContTree2->GetEntry(i);
if (RunId != container2->GetRunId())
         {
            RunId = container2->GetRunId();
             manager->SetGetterRunId (RunId);
         }
M = container2->GetDetectorWeight(0); 
 //mult.push_back(container2->GetDetectorWeight(0));
hCentr2->Fill(M);
}*/

 //std::cout << "Integral = "  << hCentr->Integral(147, 151) << std::endl;

TCanvas *cc = new TCanvas("cc", "canvas", 900, 900);
cc->cd();
hCentr2->Draw();

}
