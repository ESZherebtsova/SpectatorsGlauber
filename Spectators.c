
#define Spectators_cxx
#include "Spectators.h"
#include "math.h"
#include "TFile.h"
#include "TTree.h"

void Spectators::Loop()
 {

if (fSimTree == 0) return;
	Long64_t nentries = fSimTree->GetEntries();

TFile *fileSpec = new TFile("SpectatorsTarget_Glauber.root", "RECREATE");
TTree *myTree  = new TTree("nt_Pb_Pb","nt_Pb_Pb");

float NspecTarget, NpartTarget, Ncoll, B, Npart;


myTree->Branch("NpartTarget",&NpartTarget,"NpartTarget/F");
myTree->Branch("NspecTarget",&NspecTarget,"NspecTarget/F");
myTree->Branch("Ncoll", &Ncoll,"Ncoll/F");
myTree->Branch("Npart", &Npart,"Npart/F");
myTree->Branch("B", &B, "B/F");

TTree* nt_Pb_Pb = myTree->CloneTree();

Long64_t nbytes = 0, nb = 0, n = 0;

	cout << "Entries: " << nentries << endl;

	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
	
		nb = fSimTree->GetEntry(jentry);   nbytes += nb;
		n++;
		NspecTarget=MassNumber-fNpartA;
		NpartTarget=fNpartA;
		Ncoll=fNcoll;
		Npart=fNpart;
		B=fB;
	//cout<<"Spec = "<<NspecTarget<<"Npart  ="<<NpartTarget<<endl;
		nt_Pb_Pb->Fill();
		
}
	
	fileSpec->cd();
	nt_Pb_Pb ->Write();
	fileSpec->Close();
}
