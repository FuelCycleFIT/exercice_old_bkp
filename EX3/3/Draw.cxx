{
gStyle->SetOptStat(0);

TFile *FCy = new TFile("cyclus_exo3_3.root");
TFile *FCl = new TFile("Scenario.root");

TTree *TCy = (TTree *) FCy->Get("TT");
TTree *TCl = (TTree *) FCl->Get("TreeScenario");

TCy->SetLineColor(kRed); TCy->SetMarkerColor(kRed); TCy->SetLineWidth(3);
TCl->SetLineColor(kBlue); TCl->SetMarkerColor(kBlue); TCl->SetLineWidth(3);

// ################################################################################
// ENERGY
// ################################################################################

TCanvas *C00 = new TCanvas("C00","Power",700,500);
TH2D *tmp0 = new TH2D("tmp0","Thermal Power",10,0,102,10,0,4e9);
tmp0->GetXaxis()->SetTitle("Time (y)");       tmp0->GetXaxis()->CenterTitle();    tmp0->GetXaxis()->SetTitleOffset(1.0);
tmp0->GetYaxis()->SetTitle("Power (W)");      tmp0->GetYaxis()->CenterTitle();    tmp0->GetYaxis()->SetTitleOffset(1.0);
tmp0->Draw("");
TCy->Draw("P:T","","Lsame");
TCl->Draw("P:T","","Lsame");

// ################################################################################
// Plutonium
// ################################################################################

TCanvas *C0 = new TCanvas("C0","Pu",1400,900);
C0->Divide(2,2,0.01,0.01);
    
C0->cd(1);
TH2D *tmp1 = new TH2D("tmp1","Total Pu",10,0,102,10,0,50);
tmp1->GetXaxis()->SetTitle("Time (y)");         tmp1->GetXaxis()->CenterTitle();    tmp1->GetXaxis()->SetTitleOffset(1.0);
tmp1->GetYaxis()->SetTitle("Mass (tons)");      tmp1->GetYaxis()->CenterTitle();    tmp1->GetYaxis()->SetTitleOffset(1.0);
tmp1->Draw("");
TCy->Draw("B93/1000:T","","Lsame");
TCl->Draw("B93:T","","Lsame");

C0->cd(2);
TH2D *tmp2 = new TH2D("tmp2","Pu in Stock",10,0,102,10,0,50);
tmp2->GetXaxis()->SetTitle("Time (y)");       tmp2->GetXaxis()->CenterTitle();    tmp2->GetXaxis()->SetTitleOffset(1.0);
tmp2->GetYaxis()->SetTitle("Mass (tons)");    tmp2->GetYaxis()->CenterTitle();    tmp2->GetYaxis()->SetTitleOffset(1.0);
tmp2->Draw("");
TCy->Draw("B3/1000:T","","Lsame");
TCl->Draw("B3:T","","Lsame");

C0->cd(3);
TH2D *tmp3 = new TH2D("tmp3","Total Pu 239",10,0,102,10,0,50);
tmp3->GetXaxis()->SetTitle("Time (y)");       tmp3->GetXaxis()->CenterTitle();    tmp3->GetXaxis()->SetTitleOffset(1.0);
tmp3->GetYaxis()->SetTitle("Mass (tons)");    tmp3->GetYaxis()->CenterTitle();    tmp3->GetYaxis()->SetTitleOffset(1.0);
tmp3->Draw("");
TCy->Draw("B98/1000:T","","Lsame");
TCl->Draw("B98:T","","Lsame");

C0->cd(4); C0->GetPad(4)->SetPhi(120);
TH2D *tmp4 = new TH2D("tmp4","Total Pu 239 in Stock",10,0,102,10,0,50);
tmp4->GetXaxis()->SetTitle("Time (y)");           tmp4->GetXaxis()->SetTitleOffset(1.0);  tmp4->GetXaxis()->CenterTitle();
tmp4->GetYaxis()->SetTitle("Mass (tons)");        tmp4->GetYaxis()->SetTitleOffset(1.0);  tmp4->GetYaxis()->CenterTitle();
tmp4->Draw("");
TCy->Draw("B8/1000:T","","Lsame");
TCl->Draw("B8:T","","Lsame");

// ################################################################################
// MA
// ################################################################################

TCanvas *C1 = new TCanvas("C1","Pu",1400,900);
C1->Divide(2,2,0.01,0.01);
    
C1->cd(1);
TH2D *tmp11 = new TH2D("tmp11","Total MA",10,0,102,10,0,10);
tmp11->GetXaxis()->SetTitle("Time (y)");         tmp11->GetXaxis()->CenterTitle();    tmp11->GetXaxis()->SetTitleOffset(1.0);
tmp11->GetYaxis()->SetTitle("Mass (tons)");      tmp11->GetYaxis()->CenterTitle();    tmp11->GetYaxis()->SetTitleOffset(1.0);
tmp11->Draw("");
TCy->Draw("B96/1000:T","","Lsame");
TCl->Draw("B96:T","","Lsame");

C1->cd(2);
TH2D *tmp12 = new TH2D("tmp12","Total Am",10,0,102,10,0,5);
tmp12->GetXaxis()->SetTitle("Time (y)");       tmp12->GetXaxis()->CenterTitle();    tmp12->GetXaxis()->SetTitleOffset(1.0);
tmp12->GetYaxis()->SetTitle("Mass (tons)");    tmp12->GetYaxis()->CenterTitle();    tmp12->GetYaxis()->SetTitleOffset(1.0);
tmp12->Draw("");
TCy->Draw("B94/1000:T","","Lsame");
TCl->Draw("B94:T","","Lsame");

C1->cd(3);
TH2D *tmp13 = new TH2D("tmp13","Total Np",10,0,102,10,0,3);
tmp13->GetXaxis()->SetTitle("Time (y)");       tmp13->GetXaxis()->CenterTitle();    tmp13->GetXaxis()->SetTitleOffset(1.0);
tmp13->GetYaxis()->SetTitle("Mass (tons)");    tmp13->GetYaxis()->CenterTitle();    tmp13->GetYaxis()->SetTitleOffset(1.0);
tmp13->Draw("");
TCy->Draw("B92/1000:T","","Lsame");
TCl->Draw("B92:T","","Lsame");

C1->cd(4); C1->GetPad(4)->SetPhi(120);
TH2D *tmp14 = new TH2D("tmp14","Total Cm",10,0,102,10,0,0.1);
tmp14->GetXaxis()->SetTitle("Time (y)");           tmp14->GetXaxis()->SetTitleOffset(1.0);  tmp14->GetXaxis()->CenterTitle();
tmp14->GetYaxis()->SetTitle("Mass (tons)");        tmp14->GetYaxis()->SetTitleOffset(1.0);  tmp14->GetYaxis()->CenterTitle();
tmp14->Draw("");
TCy->Draw("B95/1000:T","","Lsame");
TCl->Draw("B95:T","","Lsame");








}
