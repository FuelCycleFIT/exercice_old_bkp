int Draw(string s_Code1, string s_Code2, string s_Exo1, string s_Exo2, string s_Run1, string s_Run2)
{
gROOT->Reset();
gStyle->SetOptStat(0);

cout<<endl<<"----------------------------------"<<endl;
cout<<"USAGE : "<<endl;
cout<<".x Draw.cxx(\"code1\",\"code2\",\"Prob1\",\"Prob2\",\"Run1\",\"Run2\")"<<endl;
cout<<"EXAMPLE : "<<endl;
cout<<".x Draw.cxx(\"class\",\"class\",\"Prob1\",\"Prob1\",\"1\",\"1\")"<<endl;
cout<<"----------------------------------"<<endl<<endl;

string Code1 = s_Code1; string Code2 = s_Code2;
string Exo1 = s_Exo1; string Exo2 = s_Exo2; 
string Run1 = s_Run1; string Run2 = s_Run2; 
string s_TFile_1; string s_TFile_2;

TTree *TC1; TTree *TC2;

if (Code1 == "class")        s_TFile_1 = Exo1 + "/" + Run1 + "/Scenario.root";
else if (Code1 == "cyclus")  s_TFile_1 = Exo1 + "/" + Run1 + "/cyclus.root";
else
{
    cout<<endl<<"code 1 should be \"class\" or \"cyclus\""<<endl<<endl;
    return 1;
}

if (Code2 == "class") s_TFile_2 = Exo2 + "/" + Run2 + "/Scenario.root";
else if (Code2 == "cyclus") s_TFile_2 = Exo2 + "/" + Run2 + "/cyclus.root";
else
{
    cout<<endl<<"code 2 should be \"class\" or \"cyclus\""<<endl<<endl;
    return 1;
}

cout<<s_TFile_1<<endl;
cout<<s_TFile_2<<endl;

TFile *FC1 = new TFile(s_TFile_1.c_str());
TFile *FC2 = new TFile(s_TFile_2.c_str());

string s_TTreeName_Cyclus = "TT";
string s_TTreeName_Class = "TreeScenario";

if (Code1 == "cyclus") TC1 = (TTree *) FC1->Get("TT");
if (Code1 == "class")  TC1 = (TTree *) FC1->Get("TreeScenario");

if (Code2 == "cyclus") TC2 = (TTree *) FC2->Get("TT");
if (Code2 == "class")  TC2 = (TTree *) FC2->Get("TreeScenario");

TC1->SetLineColor(kRed); TC1->SetMarkerColor(kRed); TC1->SetLineWidth(4);
TC2->SetLineColor(kBlue); TC2->SetMarkerColor(kBlue); TC2->SetLineWidth(2);

// ################################################################################
// Legend
// ################################################################################
    
    TLegend *L01 = new TLegend(0.55,0.10,0.90,0.25);
    L01->AddEntry(TC1, (s_Code1 + " - " + Exo1 + " - Run" + Run1).c_str(), "L");
    L01->AddEntry(TC2, (s_Code2 + " - " + Exo2 + " - Run" + Run2).c_str(), "L");

// ################################################################################
// ENERGY
// ################################################################################

    TCanvas *C00 = new TCanvas("C00","C00",700,500);
    TC1->Draw("P:T","","L");
    TC2->Draw("P:T","","Lsame");
    TH1F *tmp0 = (TH1F*)gPad->GetPrimitive("htemp"); tmp0->SetTitle("Thermal Power");
    tmp0->GetXaxis()->SetTitle("Time (y)");          tmp0->GetXaxis()->CenterTitle();    tmp0->GetXaxis()->SetTitleOffset(0.8);  tmp0->GetXaxis()->SetTitleSize(0.05);
    tmp0->GetYaxis()->SetTitle("Power (W)");         tmp0->GetYaxis()->CenterTitle();    tmp0->GetYaxis()->SetTitleOffset(0.8);  tmp0->GetYaxis()->SetTitleSize(0.05);
    gPad->Update();
    L01->Draw();

// ################################################################################
// Plutonium
// ################################################################################

    TCanvas *C0 = new TCanvas("C0","Pu",1500,900);
    C0->Divide(2,2,0.01,0.01);
        
    C0->cd(1);
    TC1->Draw("B93:T","","L");
    TC2->Draw("B93:T","","Lsame");
    tmp0 = (TH1F*)gPad->GetPrimitive("htemp"); tmp0->SetTitle("Total Pu");
    tmp0->GetXaxis()->SetTitle("Time (y)");    tmp0->GetXaxis()->CenterTitle();    tmp0->GetXaxis()->SetTitleOffset(0.8);  tmp0->GetXaxis()->SetTitleSize(0.05);
    tmp0->GetYaxis()->SetTitle("Mass (tons)"); tmp0->GetYaxis()->CenterTitle();    tmp0->GetYaxis()->SetTitleOffset(0.8);  tmp0->GetYaxis()->SetTitleSize(0.05);
    gPad->Update();
    L01->Draw();
    
    C0->cd(2);
    TC1->Draw("B3:T","","L");
    TC2->Draw("B3:T","","Lsame");
    tmp0 = (TH1F*)gPad->GetPrimitive("htemp"); tmp0->SetTitle("Pu in Stock");
    tmp0->GetXaxis()->SetTitle("Time (y)");    tmp0->GetXaxis()->CenterTitle();    tmp0->GetXaxis()->SetTitleOffset(0.8);  tmp0->GetXaxis()->SetTitleSize(0.05);
    tmp0->GetYaxis()->SetTitle("Mass (tons)"); tmp0->GetYaxis()->CenterTitle();    tmp0->GetYaxis()->SetTitleOffset(0.8);  tmp0->GetYaxis()->SetTitleSize(0.05);
    gPad->Update();
    L01->Draw();

    C0->cd(3);
    TC1->Draw("B98:T","","L");
    TC2->Draw("B98:T","","Lsame");
    tmp0 = (TH1F*)gPad->GetPrimitive("htemp"); tmp0->SetTitle("Total Pu9");
    tmp0->GetXaxis()->SetTitle("Time (y)");    tmp0->GetXaxis()->CenterTitle();    tmp0->GetXaxis()->SetTitleOffset(0.8);  tmp0->GetXaxis()->SetTitleSize(0.05);
    tmp0->GetYaxis()->SetTitle("Mass (tons)"); tmp0->GetYaxis()->CenterTitle();    tmp0->GetYaxis()->SetTitleOffset(0.8);  tmp0->GetYaxis()->SetTitleSize(0.05);
    gPad->Update();
    L01->Draw();
    
    C0->cd(4);
    TC1->Draw("B8:T","","L");
    TC2->Draw("B8:T","","Lsame");
    tmp0 = (TH1F*)gPad->GetPrimitive("htemp"); tmp0->SetTitle("Pu9 in Stock");
    tmp0->GetXaxis()->SetTitle("Time (y)");    tmp0->GetXaxis()->CenterTitle();    tmp0->GetXaxis()->SetTitleOffset(0.8);  tmp0->GetXaxis()->SetTitleSize(0.05);
    tmp0->GetYaxis()->SetTitle("Mass (tons)"); tmp0->GetYaxis()->CenterTitle();    tmp0->GetYaxis()->SetTitleOffset(0.8);  tmp0->GetYaxis()->SetTitleSize(0.05);
    gPad->Update();
    L01->Draw();

// ################################################################################
// U
// ################################################################################

    TCanvas *C1 = new TCanvas("C1","U",1500,900);
    C1->Divide(2,2,0.01,0.01);
        
    C1->cd(1);
    TC1->Draw("B102:T","","L");
    TC2->Draw("B102:T","","Lsame");
    tmp0 = (TH1F*)gPad->GetPrimitive("htemp"); tmp0->SetTitle("Total U5");
    tmp0->GetXaxis()->SetTitle("Time (y)");    tmp0->GetXaxis()->CenterTitle();    tmp0->GetXaxis()->SetTitleOffset(0.8);  tmp0->GetXaxis()->SetTitleSize(0.05);
    tmp0->GetYaxis()->SetTitle("Mass (tons)"); tmp0->GetYaxis()->CenterTitle();    tmp0->GetYaxis()->SetTitleOffset(0.8);  tmp0->GetYaxis()->SetTitleSize(0.05);
    gPad->Update();
    L01->Draw();
    
    C1->cd(2);
    TC1->Draw("B91:T","","L");
    TC2->Draw("B91:T","","Lsame");
    tmp0 = (TH1F*)gPad->GetPrimitive("htemp"); tmp0->SetTitle("Total U");
    tmp0->GetXaxis()->SetTitle("Time (y)");    tmp0->GetXaxis()->CenterTitle();    tmp0->GetXaxis()->SetTitleOffset(0.8);  tmp0->GetXaxis()->SetTitleSize(0.05);
    tmp0->GetYaxis()->SetTitle("Mass (tons)"); tmp0->GetYaxis()->CenterTitle();    tmp0->GetYaxis()->SetTitleOffset(0.8);  tmp0->GetYaxis()->SetTitleSize(0.05);
    gPad->Update();
    L01->Draw();
    
    C1->cd(3);
    TC1->Draw("B12:T","","L");
    TC2->Draw("B12:T","","Lsame");
    tmp0 = (TH1F*)gPad->GetPrimitive("htemp"); tmp0->SetTitle("U5 in Stock");
    tmp0->GetXaxis()->SetTitle("Time (y)");    tmp0->GetXaxis()->CenterTitle();    tmp0->GetXaxis()->SetTitleOffset(0.8);  tmp0->GetXaxis()->SetTitleSize(0.05);
    tmp0->GetYaxis()->SetTitle("Mass (tons)"); tmp0->GetYaxis()->CenterTitle();    tmp0->GetYaxis()->SetTitleOffset(0.8);  tmp0->GetYaxis()->SetTitleSize(0.05);
    gPad->Update();
    L01->Draw();
    
    C1->cd(4);
    TC1->Draw("B1:T","","L");
    TC2->Draw("B1:T","","Lsame");
    tmp0 = (TH1F*)gPad->GetPrimitive("htemp"); tmp0->SetTitle("U in Stock");
    tmp0->GetXaxis()->SetTitle("Time (y)");    tmp0->GetXaxis()->CenterTitle();    tmp0->GetXaxis()->SetTitleOffset(0.8);  tmp0->GetXaxis()->SetTitleSize(0.05);
    tmp0->GetYaxis()->SetTitle("Mass (tons)"); tmp0->GetYaxis()->CenterTitle();    tmp0->GetYaxis()->SetTitleOffset(0.8);  tmp0->GetYaxis()->SetTitleSize(0.05);
    gPad->Update();
    L01->Draw();

// ################################################################################
// MA
// ################################################################################

    TCanvas *C2 = new TCanvas("C2","MA",1500,900);
    C2->Divide(2,2,0.01,0.01);
        
    C2->cd(1);
    TC1->Draw("B96:T","","L");
    TC2->Draw("B96:T","","Lsame");
    tmp0 = (TH1F*)gPad->GetPrimitive("htemp"); tmp0->SetTitle("Total MA");
    tmp0->GetXaxis()->SetTitle("Time (y)");    tmp0->GetXaxis()->CenterTitle();    tmp0->GetXaxis()->SetTitleOffset(0.8);  tmp0->GetXaxis()->SetTitleSize(0.05);
    tmp0->GetYaxis()->SetTitle("Mass (tons)"); tmp0->GetYaxis()->CenterTitle();    tmp0->GetYaxis()->SetTitleOffset(0.8);  tmp0->GetYaxis()->SetTitleSize(0.05);
    gPad->Update();
    L01->Draw();
    
    C2->cd(2);
    TC1->Draw("B94:T","","L");
    TC2->Draw("B94:T","","Lsame");
    tmp0 = (TH1F*)gPad->GetPrimitive("htemp"); tmp0->SetTitle("Total Am");
    tmp0->GetXaxis()->SetTitle("Time (y)");    tmp0->GetXaxis()->CenterTitle();    tmp0->GetXaxis()->SetTitleOffset(0.8);  tmp0->GetXaxis()->SetTitleSize(0.05);
    tmp0->GetYaxis()->SetTitle("Mass (tons)"); tmp0->GetYaxis()->CenterTitle();    tmp0->GetYaxis()->SetTitleOffset(0.8);  tmp0->GetYaxis()->SetTitleSize(0.05);
    gPad->Update();
    L01->Draw();
    
    C2->cd(3);
    TC1->Draw("B92:T","","L");
    TC2->Draw("B92:T","","Lsame");
    tmp0 = (TH1F*)gPad->GetPrimitive("htemp"); tmp0->SetTitle("Total Np");
    tmp0->GetXaxis()->SetTitle("Time (y)");    tmp0->GetXaxis()->CenterTitle();    tmp0->GetXaxis()->SetTitleOffset(0.8);  tmp0->GetXaxis()->SetTitleSize(0.05);
    tmp0->GetYaxis()->SetTitle("Mass (tons)"); tmp0->GetYaxis()->CenterTitle();    tmp0->GetYaxis()->SetTitleOffset(0.8);  tmp0->GetYaxis()->SetTitleSize(0.05);
    gPad->Update();
    L01->Draw();
    
    C2->cd(4);
    TC1->Draw("B95:T","","L");
    TC2->Draw("B95:T","","Lsame");
    tmp0 = (TH1F*)gPad->GetPrimitive("htemp"); tmp0->SetTitle("Total Cm");
    tmp0->GetXaxis()->SetTitle("Time (y)");    tmp0->GetXaxis()->CenterTitle();    tmp0->GetXaxis()->SetTitleOffset(0.8);  tmp0->GetXaxis()->SetTitleSize(0.05);
    tmp0->GetYaxis()->SetTitle("Mass (tons)"); tmp0->GetYaxis()->CenterTitle();    tmp0->GetYaxis()->SetTitleOffset(0.8);  tmp0->GetYaxis()->SetTitleSize(0.05);
    gPad->Update();
    L01->Draw();

// ################################################################################
// WHAT YOU WANT
// ################################################################################

    TCanvas *C3 = new TCanvas("C3","MA",1500,900);
    C3->Divide(2,2,0.01,0.01);
        
    C3->cd(1);
    TC1->Draw("B3:T","","L");
    TC2->Draw("B3:T","","Lsame");
    tmp0 = (TH1F*)gPad->GetPrimitive("htemp"); tmp0->SetTitle("Pu in Stock");
    tmp0->GetXaxis()->SetTitle("Time (y)");    tmp0->GetXaxis()->CenterTitle();    tmp0->GetXaxis()->SetTitleOffset(0.8);  tmp0->GetXaxis()->SetTitleSize(0.05);
    tmp0->GetYaxis()->SetTitle("Mass (tons)"); tmp0->GetYaxis()->CenterTitle();    tmp0->GetYaxis()->SetTitleOffset(0.8);  tmp0->GetYaxis()->SetTitleSize(0.05);
    gPad->Update();
    L01->Draw();
    
    C3->cd(2);
    TC1->Draw("B8/B3:T","","L");
    TC1->Draw("B7/B3:T","","Lsame");
    TC1->Draw("B9/B3:T","","Lsame");
    TC1->Draw("B10/B3:T","","Lsame");
    TC1->Draw("B11/B3:T","","Lsame");
    TC2->Draw("B7/B3:T","","Lsame");
    TC2->Draw("B8/B3:T","","Lsame");
    TC2->Draw("B9/B3:T","","Lsame");
    TC2->Draw("B10/B3:T","","Lsame");
    TC2->Draw("B11/B3:T","","Lsame");
    tmp0 = (TH1F*)gPad->GetPrimitive("htemp"); tmp0->SetTitle("Pu isotopie in Cycle");
    tmp0->GetXaxis()->SetTitle("Time (y)");    tmp0->GetXaxis()->CenterTitle();    tmp0->GetXaxis()->SetTitleOffset(0.8);  tmp0->GetXaxis()->SetTitleSize(0.05);
    tmp0->GetYaxis()->SetTitle("Mass (tons)"); tmp0->GetYaxis()->CenterTitle();    tmp0->GetYaxis()->SetTitleOffset(0.8);  tmp0->GetYaxis()->SetTitleSize(0.05);
    gPad->Update();
    L01->Draw();
    
    C3->cd(3);
    TC2->Draw("B102:T","","L");
    TC1->Draw("B102:T","","Lsame");
    TC1->Draw("B66:T","","Lsame");
    TC2->Draw("B66:T","","Lsame");
    tmp0 = (TH1F*)gPad->GetPrimitive("htemp"); tmp0->SetTitle("U5");
    tmp0->GetXaxis()->SetTitle("Time (y)");    tmp0->GetXaxis()->CenterTitle();    tmp0->GetXaxis()->SetTitleOffset(0.8);  tmp0->GetXaxis()->SetTitleSize(0.05);
    tmp0->GetYaxis()->SetTitle("Mass (tons)"); tmp0->GetYaxis()->CenterTitle();    tmp0->GetYaxis()->SetTitleOffset(0.8);  tmp0->GetYaxis()->SetTitleSize(0.05);
    gPad->Update();
    L01->Draw();
    
    C3->cd(4);
    TC1->Draw("B95:T","","L");
    TC2->Draw("B95:T","","Lsame");
    tmp0 = (TH1F*)gPad->GetPrimitive("htemp"); tmp0->SetTitle("Total Cm");
    tmp0->GetXaxis()->SetTitle("Time (y)");    tmp0->GetXaxis()->CenterTitle();    tmp0->GetXaxis()->SetTitleOffset(0.8);  tmp0->GetXaxis()->SetTitleSize(0.05);
    tmp0->GetYaxis()->SetTitle("Mass (tons)"); tmp0->GetYaxis()->CenterTitle();    tmp0->GetYaxis()->SetTitleOffset(0.8);  tmp0->GetYaxis()->SetTitleSize(0.05);
    gPad->Update();
    L01->Draw();

    return 0;
}
