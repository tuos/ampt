void macro_nmult_vs_v2_plot_twopanels() {
  const int nMultBin=15;
  double ccpt[nMultBin];
  double pcpt[nMultBin];
  double temp;
  double ccv2PtP[nMultBin];
  double ccv2ePtP[nMultBin];
  double ccv2PnP[nMultBin];
  double ccv2ePnP[nMultBin];
  double ccv2EP[nMultBin];
  double ccv2eEP[nMultBin]; 
  double pcv2PtP[nMultBin];
  double pcv2ePtP[nMultBin];
  double pcv2PnP[nMultBin];
  double pcv2ePnP[nMultBin];
  double pcv2EP[nMultBin];
  double pcv2eEP[nMultBin];


  double ccres[nMultBin];
  double ccrese[nMultBin];
  double pcres[nMultBin];
  double pcrese[nMultBin];

  ifstream in1;
  ifstream in2;
  ifstream in3;
  ifstream in4;
  ifstream in5;
  ifstream in6;
  in1.open("./cc/output_nmultv2EP.txt");
  in2.open("./cc/output_nmultv2PtP.txt");
  in3.open("./cc/output_nmultv2PnP.txt");
  in4.open("./pc/output_nmultv2EP.txt");
  in5.open("./pc/output_nmultv2PtP.txt");
  in6.open("./pc/output_nmultv2PnP.txt");
  //inv2.open("output_v2_newptbins_Nch120150.txt");
  if(!in1.good())    cout<<" input fail"<<endl;
  else cout<<" input OK! "<<endl;
  for(int i=0;i<nMultBin;i++){
    in1>>ccpt[i];  
    in1>>ccv2EP[i];  
    in1>>ccv2eEP[i];
    in1>>ccres[i];
    in1>>ccrese[i];

    in2>>temp;
    in2>>ccv2PtP[i];
    in2>>ccv2ePtP[i];

    in3>>temp;
    in3>>ccv2PnP[i];
    in3>>ccv2ePnP[i];

    in4>>pcpt[i];
    in4>>pcv2EP[i];
    in4>>pcv2eEP[i];
    in4>>pcres[i];
    in4>>pcrese[i];

    in5>>temp;
    in5>>pcv2PtP[i];
    in5>>pcv2ePtP[i];

    in6>>temp;
    in6>>pcv2PnP[i];
    in6>>pcv2ePnP[i];

//v2[i]=v2[i]*1.35;
  } 
  


////////////////

////////
  TCanvas *c1 = new TCanvas("c1","c1",1,1,450,700);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.15);
  c1->SetBottomMargin(0.15);
  c1->SetTopMargin(0.02);
  c1->SetRightMargin(0.01);
  //c1->Divide(2,1,0,0);
  //c1->Divide(1,2,0,0);
  gStyle->SetOptStat(0);
  c1->SetTicks(-1);
  c1->Divide(1,2,0,0);

  c1->cd(1);

 gPad->SetRightMargin(0.01);
 gPad->SetTicks(-1);
 TH1D* hist = new TH1D("hist","",200,0.,205.);
 hist->SetXTitle("N_{Mult}");
 hist->SetYTitle("v_{2}");
 hist->SetMinimum(-0.01);
 hist->SetMaximum(0.19);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(1.3);
 hist->GetXaxis()->SetTitleOffset(0.95);
 hist->GetXaxis()->SetTitleSize(0.066);
 hist->GetYaxis()->SetTitleSize(0.066);
 hist->GetXaxis()->SetLabelSize(0.05);
 hist->GetYaxis()->SetLabelSize(0.06);
 hist->Draw();


  //TF1 *V2vsNpart = new TF1("V2vsNpart","((x/3.4)^1.8/(1+(x/3)^1.8))*(.00005+(1/x)^0.8)",0.2,10);
  //V2vsNpart->SetLineColor(2);
  //V2vsNpart->SetLineWidth(2);
  //V2vsNpart->SetLineStyle(2);
  // V2vsPt->Draw("same");

  //TGraphErrors *gr2 = new TGraphErrors(nPtBin,pt,v2,0,v2e);
  TGraphErrors *gr1 = new TGraphErrors(10,ccpt,ccv2EP,0,ccv2eEP);
  gr1->SetTitle("");
  gr1->SetMarkerStyle(20);
  gr1->SetMarkerSize(1);
  gr1->SetMarkerColor(kAzure+10);
  gr1->SetLineWidth(2);
  gr1->SetLineColor(kAzure+7);
  gr1->Draw("psameezL");
 
  TGraphErrors *gr2 = new TGraphErrors(10,ccpt,ccv2PtP,0,ccv2ePtP);
  gr2->SetTitle("");
  gr2->SetMarkerStyle(20);
  gr2->SetMarkerSize(1);
  gr2->SetMarkerColor(8);
  gr2->SetLineWidth(2);
  gr2->SetLineColor(8);
  gr2->Draw("psameezL");

  TGraphErrors *gr3 = new TGraphErrors(10,ccpt,ccv2PnP,0,ccv2ePnP);
  gr3->SetTitle("");
  gr3->SetMarkerStyle(20);
  gr3->SetMarkerSize(1);
  gr3->SetMarkerColor(kBlue-7);
  gr3->SetLineWidth(2);
  gr3->SetLineColor(kBlue-7);
  gr3->Draw("psameezL");

  TGraphErrors *gr4 = new TGraphErrors(10,pcpt,pcv2EP,0,pcv2eEP);
  gr4->SetTitle("");
  gr4->SetMarkerStyle(24);
  gr4->SetMarkerSize(1);
  gr4->SetMarkerColor(kPink+9);
  gr4->SetLineWidth(2);
  gr4->SetLineColor(kPink+9);
  gr4->Draw("psameezL");

  TGraphErrors *gr5 = new TGraphErrors(10,pcpt,pcv2PtP,0,pcv2ePtP);
  gr5->SetTitle("");
  gr5->SetMarkerStyle(24);
  gr5->SetMarkerSize(1);
  gr5->SetMarkerColor(2);
  gr5->SetLineWidth(2);
  gr5->SetLineColor(2);
  gr5->Draw("psameezL");

  TGraphErrors *gr6 = new TGraphErrors(10,pcpt,pcv2PnP,0,pcv2ePnP);
  gr6->SetTitle("");
  gr6->SetMarkerStyle(24);
  gr6->SetMarkerSize(1);
  gr6->SetMarkerColor(1);
  gr6->SetLineWidth(2);
  gr6->SetLineColor(1);
  gr6->Draw("psameezL");



    TLegend *leg = new TLegend(0.72,0.6,0.92,0.84);
    leg->SetFillColor(10);
    leg->SetBorderSize(0);
    leg->SetTextFont(42);
    leg->SetTextColor(1);
    leg->SetTextSize(0.04);
    //leg->SetLineStyle(0.06);
    leg->AddEntry(gr1,"EP C+C","pl");
    leg->AddEntry(gr2,"PtP C+C","pl");
    leg->AddEntry(gr3,"PnP C+C","pl");
    leg->AddEntry(gr4,"EP p+C","pl");
    leg->AddEntry(gr5,"PtP p+C","pl");
    leg->AddEntry(gr6,"PnP p+C","pl");
    // leg->AddEntry(V2vsPt,"Input v_{2}","l");
    leg->Draw();
 
    TLatex *tex2= new TLatex(20,0.1785,"AMPT, #sqrt{s} = 7.0 TeV");
    tex2->SetTextColor(1);
    tex2->SetTextSize(0.04);
    tex2->SetTextFont(42);
    tex2->Draw();
    TLatex *tex3= new TLatex(20,0.1635,"#sigma = 3.0 mb, 0-100%");
    tex3->SetTextColor(1);
    tex3->SetTextSize(0.04);
    tex3->SetTextFont(42);
    tex3->Draw();
    TLatex *tex4= new TLatex(20,0.1485,"3 < p_{T} [GeV/c] < 1000");
    tex4->SetTextColor(1);
    tex4->SetTextSize(0.04);
    tex4->SetTextFont(42);
    tex4->Draw();

    TLatex *tex5= new TLatex(186, 0.1935, "(b)");
    tex5->SetTextColor(1);
    tex5->SetTextSize(0.035);
    tex5->Draw();


  c1->cd(2);
 gPad->SetTicks(-1);
 gPad->SetRightMargin(0.01);
 TH1D* hist2 = new TH1D("hist2","",200,0.,205.);
 hist2->SetXTitle("N_{Mult}");
 hist2->SetYTitle("v_{2}");
 hist2->SetMinimum(-0.001);
 hist2->SetMaximum(0.0299);
 hist2->GetXaxis()->CenterTitle(1);
 hist2->GetYaxis()->CenterTitle(1);
 hist2->GetYaxis()->SetTitleOffset(1.3);
 hist2->GetXaxis()->SetTitleOffset(0.95);
 hist2->GetXaxis()->SetTitleSize(0.066);
 hist2->GetYaxis()->SetTitleSize(0.066);
 hist2->GetXaxis()->SetLabelSize(0.05);
 hist2->GetYaxis()->SetLabelSize(0.05);
 hist2->Draw();

  TGraphErrors *gr2b = new TGraphErrors(10,ccpt,ccv2PtP,0,ccv2ePtP);
  gr2b->SetTitle("");
  gr2b->SetMarkerStyle(20);
  gr2b->SetMarkerSize(1);
  gr2b->SetMarkerColor(8);
  gr2b->SetLineWidth(2);
  gr2b->SetLineColor(8);
  gr2b->Draw("psameezL");

  TGraphErrors *gr3b = new TGraphErrors(10,ccpt,ccv2PnP,0,ccv2ePnP);
  gr3b->SetTitle("");
  gr3b->SetMarkerStyle(20);
  gr3b->SetMarkerSize(1);
  gr3b->SetMarkerColor(kBlue-7);
  gr3b->SetLineWidth(2);
  gr3b->SetLineColor(kBlue-7);
  gr3b->Draw("psameezL");

  TGraphErrors *gr5b = new TGraphErrors(10,pcpt,pcv2PtP,0,pcv2ePtP);
  gr5b->SetTitle("");
  gr5b->SetMarkerStyle(24);
  gr5b->SetMarkerSize(1);
  gr5b->SetMarkerColor(2);
  gr5b->SetLineWidth(2);
  gr5b->SetLineColor(2);
  gr5b->Draw("psameezL");

  TGraphErrors *gr6b = new TGraphErrors(10,pcpt,pcv2PnP,0,pcv2ePnP);
  gr6b->SetTitle("");
  gr6b->SetMarkerStyle(24);
  gr6b->SetMarkerSize(1);
  gr6b->SetMarkerColor(1);
  gr6b->SetLineWidth(2);
  gr6b->SetLineColor(1);
  gr6b->Draw("psameezL");


  //c1->Print("plot_nmult_v2.png");
  //c1->Print("plot_nmult_v2.pdf");



}


