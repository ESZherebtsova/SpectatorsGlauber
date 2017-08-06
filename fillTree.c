void fillTree(bool isItTest=0) {
	gROOT->ProcessLine(".L Spectators.C+");

	TFile *fSim = new TFile ("PbPb_NA49.root","READ");
TTree *fSimTree;
fSimTree = (TTree*) fSim->Get("nt_Pb_Pb");

	Spectators* object = new Spectators(fSimTree);
	object->Loop();

}
