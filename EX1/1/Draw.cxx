{
gStyle->SetOptStat(0);

TFile *FCy = new TFile("cyclus_exo1_1.root");
TFile *FCl = new TFile("Scenario.root");

TTree *TCy = (TTree *) FCy->Get("TT");
TTree *TCl = (TTree *) FCl->Get("TreeScenario");

TCy->SetLineColor(kRed); TCy->SetMarkerColor(kRed); TCy->SetLineWidth(3);
TCl->SetLineColor(kBlue); TCl->SetMarkerColor(kBlue); TCl->SetLineWidth(3);


TCanvas *C0 = new TCanvas("C0","Pu",1400,900);
C0->Divide(2,2,0.01,0.01);
    
C0->cd(1);
TH2D *tmp1 = new TH2D("tmp1","Total Pu",10,0,102,10,0,50);
tmp1->GetXaxis()->SetTitle("Time (y)");         tmp1->GetXaxis()->CenterTitle();    tmp1->GetXaxis()->SetTitleOffset(1.0);
tmp1->GetYaxis()->SetTitle("Mass (tons)");      tmp1->GetYaxis()->CenterTitle();    tmp1->GetYaxis()->SetTitleOffset(1.0);
tmp1->Draw("");
TCy->Draw("B93:T","","Lsame");
TCl->Draw("B93:T","","Lsame");

C0->cd(2);
TH2D *tmp2 = new TH2D("tmp2","Pu in Stock",10,0,102,10,0,50);
tmp2->GetXaxis()->SetTitle("Time (y)");       tmp2->GetXaxis()->CenterTitle();    tmp2->GetXaxis()->SetTitleOffset(1.0);
tmp2->GetYaxis()->SetTitle("Mass (tons)");    tmp2->GetYaxis()->CenterTitle();    tmp2->GetYaxis()->SetTitleOffset(1.0);
tmp2->Draw("");
TCy->Draw("B3:T","","Lsame");
TCl->Draw("B3:T","","Lsame");

C0->cd(3);
TH2D *tmp3 = new TH2D("tmp3","Pu in Reactor",10,0,102,10,0,1);
tmp3->GetXaxis()->SetTitle("Time (y)");       tmp3->GetXaxis()->CenterTitle();    tmp3->GetXaxis()->SetTitleOffset(1.0);
tmp3->GetYaxis()->SetTitle("Mass (tons)");    tmp3->GetYaxis()->CenterTitle();    tmp3->GetYaxis()->SetTitleOffset(1.0);
tmp3->Draw("");
TCy->Draw("B57:T","","Lsame");
TCl->Draw("B57:T","","Lsame");

C0->cd(4); C0->GetPad(4)->SetPhi(120);
TH2D *tmp4 = new TH2D("tmp4","Pu 239 in Reactor",10,0,102,10,0,0.6);
tmp4->GetXaxis()->SetTitle("Time (y)");           tmp4->GetXaxis()->SetTitleOffset(1.0);  tmp4->GetXaxis()->CenterTitle();
tmp4->GetYaxis()->SetTitle("Mass (tons)");        tmp4->GetYaxis()->SetTitleOffset(1.0);  tmp4->GetYaxis()->CenterTitle();
tmp4->Draw("");
TCy->Draw("B170:T","","Lsame");
TCl->Draw("B170:T","","Lsame");
}
