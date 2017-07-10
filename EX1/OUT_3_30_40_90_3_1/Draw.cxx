{

gStyle->SetOptStat(0);

TFile *FCy = new TFile("cyclus_exo1_1.root")
TFile *FCl = new TFile("Scenario.root")

TTree *TCy = (TTree *) FCy->Get("TT")
TTree *TCl = (TTree *) FCl->Get("TreeScenario")

}
