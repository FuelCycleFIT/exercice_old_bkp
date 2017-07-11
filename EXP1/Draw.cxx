void Draw(string s_Exo, string s_Run)
{
gStyle->SetOptStat(0);

string s_TFile_Cyclus = s_Exo + "/" + s_Run + "/cyclus.root";
string s_TFile_Class = s_Exo + "/" + s_Run + "/Scenario.root";

cout<<s_TFile_Cyclus<<endl;
cout<<s_TFile_Class<<endl;


TFile *FCy = new TFile(s_TFile_Cyclus.c_str());
TFile *FCl = new TFile(s_TFile_Class.c_str());

TTree *TCy = (TTree *) FCy->Get("TT");
TTree *TCl = (TTree *) FCl->Get("TreeScenario");

TCy->SetLineColor(kRed); TCy->SetMarkerColor(kRed); TCy->SetLineWidth(3);
TCl->SetLineColor(kBlue); TCl->SetMarkerColor(kBlue); TCl->SetLineWidth(3);

// ################################################################################
// Legend
// ################################################################################
    
    TLegend *L01 = new TLegend(0.75,0.10,0.90,0.25);
    L01->AddEntry(TCy, "Cyclus", "L");
    L01->AddEntry(TCl, "CLASS", "L");

// ################################################################################
// ENERGY
// ################################################################################

    TCanvas *C00 = new TCanvas("C00","C00",700,500);
    TCy->Draw("P:T","","L");
    TCl->Draw("P:T","","Lsame");
    TH1F *tmp0 = (TH1F*)gPad->GetPrimitive("htemp"); tmp0->SetTitle("Thermal Power");
    tmp0->GetXaxis()->SetTitle("Time (y)");          tmp0->GetXaxis()->CenterTitle();    tmp0->GetXaxis()->SetTitleOffset(0.8);  tmp0->GetXaxis()->SetTitleSize(0.05);
    tmp0->GetYaxis()->SetTitle("Power (W)");         tmp0->GetYaxis()->CenterTitle();    tmp0->GetYaxis()->SetTitleOffset(0.8);  tmp0->GetYaxis()->SetTitleSize(0.05);
    gPad->Update();
    L01->Draw();

// ################################################################################
// Plutonium
// ################################################################################

    TCanvas *C0 = new TCanvas("C0","Pu",1400,900);
    C0->Divide(2,2,0.01,0.01);
        
    C0->cd(1);
    TCy->Draw("B93/1000:T","","L");
    TCl->Draw("B93:T","","Lsame");
    tmp0 = (TH1F*)gPad->GetPrimitive("htemp"); tmp0->SetTitle("Total Pu");
    tmp0->GetXaxis()->SetTitle("Time (y)");    tmp0->GetXaxis()->CenterTitle();    tmp0->GetXaxis()->SetTitleOffset(0.8);  tmp0->GetXaxis()->SetTitleSize(0.05);
    tmp0->GetYaxis()->SetTitle("Mass (tons)"); tmp0->GetYaxis()->CenterTitle();    tmp0->GetYaxis()->SetTitleOffset(0.8);  tmp0->GetYaxis()->SetTitleSize(0.05);
    gPad->Update();
    L01->Draw();
    
    C0->cd(2);
    TCy->Draw("B3/1000:T","","L");
    TCl->Draw("B3:T","","Lsame");
    tmp0 = (TH1F*)gPad->GetPrimitive("htemp"); tmp0->SetTitle("Pu in Stock");
    tmp0->GetXaxis()->SetTitle("Time (y)");    tmp0->GetXaxis()->CenterTitle();    tmp0->GetXaxis()->SetTitleOffset(0.8);  tmp0->GetXaxis()->SetTitleSize(0.05);
    tmp0->GetYaxis()->SetTitle("Mass (tons)"); tmp0->GetYaxis()->CenterTitle();    tmp0->GetYaxis()->SetTitleOffset(0.8);  tmp0->GetYaxis()->SetTitleSize(0.05);
    gPad->Update();
    L01->Draw();

    C0->cd(3);
    TCy->Draw("B98/1000:T","","L");
    TCl->Draw("B98:T","","Lsame");
    tmp0 = (TH1F*)gPad->GetPrimitive("htemp"); tmp0->SetTitle("Total Pu9");
    tmp0->GetXaxis()->SetTitle("Time (y)");    tmp0->GetXaxis()->CenterTitle();    tmp0->GetXaxis()->SetTitleOffset(0.8);  tmp0->GetXaxis()->SetTitleSize(0.05);
    tmp0->GetYaxis()->SetTitle("Mass (tons)"); tmp0->GetYaxis()->CenterTitle();    tmp0->GetYaxis()->SetTitleOffset(0.8);  tmp0->GetYaxis()->SetTitleSize(0.05);
    gPad->Update();
    L01->Draw();
    
    C0->cd(4);
    TCy->Draw("B8/1000:T","","L");
    TCl->Draw("B8:T","","Lsame");
    tmp0 = (TH1F*)gPad->GetPrimitive("htemp"); tmp0->SetTitle("Pu9 in Stock");
    tmp0->GetXaxis()->SetTitle("Time (y)");    tmp0->GetXaxis()->CenterTitle();    tmp0->GetXaxis()->SetTitleOffset(0.8);  tmp0->GetXaxis()->SetTitleSize(0.05);
    tmp0->GetYaxis()->SetTitle("Mass (tons)"); tmp0->GetYaxis()->CenterTitle();    tmp0->GetYaxis()->SetTitleOffset(0.8);  tmp0->GetYaxis()->SetTitleSize(0.05);
    gPad->Update();
    L01->Draw();

// ################################################################################
// MA
// ################################################################################

    TCanvas *C1 = new TCanvas("C1","MA",1400,900);
    C1->Divide(2,2,0.01,0.01);
        
    C1->cd(1);
    TCy->Draw("B96/1000:T","","L");
    TCl->Draw("B96:T","","Lsame");
    tmp0 = (TH1F*)gPad->GetPrimitive("htemp"); tmp0->SetTitle("Total MA");
    tmp0->GetXaxis()->SetTitle("Time (y)");    tmp0->GetXaxis()->CenterTitle();    tmp0->GetXaxis()->SetTitleOffset(0.8);  tmp0->GetXaxis()->SetTitleSize(0.05);
    tmp0->GetYaxis()->SetTitle("Mass (tons)"); tmp0->GetYaxis()->CenterTitle();    tmp0->GetYaxis()->SetTitleOffset(0.8);  tmp0->GetYaxis()->SetTitleSize(0.05);
    gPad->Update();
    L01->Draw();
    
    C1->cd(2);
    TCy->Draw("B94/1000:T","","L");
    TCl->Draw("B94:T","","Lsame");
    tmp0 = (TH1F*)gPad->GetPrimitive("htemp"); tmp0->SetTitle("Total Am");
    tmp0->GetXaxis()->SetTitle("Time (y)");    tmp0->GetXaxis()->CenterTitle();    tmp0->GetXaxis()->SetTitleOffset(0.8);  tmp0->GetXaxis()->SetTitleSize(0.05);
    tmp0->GetYaxis()->SetTitle("Mass (tons)"); tmp0->GetYaxis()->CenterTitle();    tmp0->GetYaxis()->SetTitleOffset(0.8);  tmp0->GetYaxis()->SetTitleSize(0.05);
    gPad->Update();
    L01->Draw();
    
    C1->cd(3);
    TCy->Draw("B92/1000:T","","L");
    TCl->Draw("B92:T","","Lsame");
    tmp0 = (TH1F*)gPad->GetPrimitive("htemp"); tmp0->SetTitle("Total Np");
    tmp0->GetXaxis()->SetTitle("Time (y)");    tmp0->GetXaxis()->CenterTitle();    tmp0->GetXaxis()->SetTitleOffset(0.8);  tmp0->GetXaxis()->SetTitleSize(0.05);
    tmp0->GetYaxis()->SetTitle("Mass (tons)"); tmp0->GetYaxis()->CenterTitle();    tmp0->GetYaxis()->SetTitleOffset(0.8);  tmp0->GetYaxis()->SetTitleSize(0.05);
    gPad->Update();
    L01->Draw();
    
    C1->cd(4);
    TCy->Draw("B95/1000:T","","L");
    TCl->Draw("B95:T","","Lsame");
    tmp0 = (TH1F*)gPad->GetPrimitive("htemp"); tmp0->SetTitle("Total Cm");
    tmp0->GetXaxis()->SetTitle("Time (y)");    tmp0->GetXaxis()->CenterTitle();    tmp0->GetXaxis()->SetTitleOffset(0.8);  tmp0->GetXaxis()->SetTitleSize(0.05);
    tmp0->GetYaxis()->SetTitle("Mass (tons)"); tmp0->GetYaxis()->CenterTitle();    tmp0->GetYaxis()->SetTitleOffset(0.8);  tmp0->GetYaxis()->SetTitleSize(0.05);
    gPad->Update();
    L01->Draw();
}
