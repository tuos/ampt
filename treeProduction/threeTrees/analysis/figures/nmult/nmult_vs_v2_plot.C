void nmult_vs_v2_plot() {
  const int nMultBin=21;
  double ccmultEP[nMultBin];
  double ccmultPP[nMultBin];
  double pcmultEP[nMultBin];
  double pcmultPP[nMultBin];
  double temp;
  double temp2;
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

  double pbpbmult[nMultBin];
  double pbpbv2[nMultBin];
  double pbpbv2e[nMultBin];
  double ppbmult[nMultBin];
  double ppbv2[nMultBin];
  double ppbv2e[nMultBin];

 

  ifstream in1;
  ifstream in2;
  ifstream in3;
  ifstream in4;
  ifstream in5;
  ifstream in6;
  ifstream in7;
  ifstream in8;
  in1.open("../../cc/nmult/output_nmultv2EP.txt");
  in2.open("../../cc/nmult/small_bins/output_nmultv2PtP.txt");
  in3.open("../../cc/nmult/small_bins/output_nmultv2PnP.txt");
  in4.open("../../pc/nmult/output_nmultv2EP.txt");
  in5.open("../../pc/nmult/small_bins/output_nmultv2PtP.txt");
  in6.open("../../pc/nmult/small_bins/output_nmultv2PnP.txt");
  in7.open("PbPb.txt");
  in8.open("pPb.txt");
  //inv2.open("output_v2_newptbins_Nch120150.txt");
  if(!in1.good())    cout<<" input fail"<<endl;
  else cout<<" input OK! "<<endl;
  for(int i=0;i<nMultBin;i++){
    in1>>ccmultEP[i];  
    in1>>ccv2EP[i];  
    in1>>ccv2eEP[i];
    in1>>ccres[i];
    in1>>ccrese[i];

    in2>>ccmultPP[i];
    in2>>ccv2PtP[i];
    in2>>ccv2ePtP[i];

    in3>>temp;
    in3>>ccv2PnP[i];
    in3>>ccv2ePnP[i];

    in4>>pcmultEP[i];
    in4>>pcv2EP[i];
    in4>>pcv2eEP[i];
    in4>>pcres[i];
    in4>>pcrese[i];

    in5>>pcmultPP[i];
    in5>>pcv2PtP[i];
    in5>>pcv2ePtP[i];

    in6>>temp;
    in6>>pcv2PnP[i];
    in6>>pcv2ePnP[i];

    in7>>pbpbmult[i];
    in7>>pbpbv2[i];
    in7>>temp;
    in7>>temp2;
    pbpbv2e[i] = pow(temp*temp + temp2*temp2, 0.5);

    in8>>ppbmult[i];
    in8>>ppbv2[i];
    in8>>temp;
    in8>>temp2;
    ppbv2e[i] = pow(temp*temp + temp2*temp2, 0.5);


//v2[i]=v2[i]*1.35;
  } 
  


////////////////

////////
  TCanvas *c1 = new TCanvas("c1","c1",1,1,650,550);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.15);
  c1->SetBottomMargin(0.15);
  c1->SetTopMargin(0.02);
  c1->SetRightMargin(0.02);
  //c1->Divide(2,1,0,0);
 gStyle->SetOptStat(0);
  c1->SetTicks(-1);
 TH1D* hist = new TH1D("hist","",200,0.,205.);
 hist->SetXTitle("N_{Mult}");
 hist->SetYTitle("v_{2}");
 hist->SetMinimum(-0.01);
 hist->SetMaximum(0.21);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(1.1);
 hist->GetXaxis()->SetTitleOffset(0.95);
 hist->GetXaxis()->SetTitleSize(0.066);
 hist->GetYaxis()->SetTitleSize(0.066);
 hist->GetXaxis()->SetLabelSize(0.05);
 hist->GetYaxis()->SetLabelSize(0.05);
 hist->Draw();

  //TF1 *V2vsNpart = new TF1("V2vsNpart","((x/3.4)^1.8/(1+(x/3)^1.8))*(.00005+(1/x)^0.8)",0.2,10);
  //V2vsNpart->SetLineColor(2);
  //V2vsNpart->SetLineWidth(2);
  //V2vsNpart->SetLineStyle(2);
  // V2vsPt->Draw("same");

  //TGraphErrors *gr2 = new TGraphErrors(nPtBin,pt,v2,0,v2e);
  TGraphErrors *gr1 = new TGraphErrors(10,ccmultEP,ccv2EP,0,ccv2eEP);
  gr1->SetTitle("");
  gr1->SetMarkerStyle(33);
  gr1->SetMarkerSize(1);
  gr1->SetMarkerColor(kAzure+10);
  gr1->SetLineWidth(2);
  gr1->SetLineColor(kAzure+7);
  gr1->Draw("psameezL");
 
  TGraphErrors *gr2 = new TGraphErrors(21,ccmultPP,ccv2PtP,0,ccv2ePtP);
  gr2->SetTitle("");
  gr2->SetMarkerStyle(20);
  gr2->SetMarkerSize(1);
  gr2->SetMarkerColor(8);
  gr2->SetLineWidth(2);
  gr2->SetLineColor(8);
  gr2->Draw("psameezL");

  TGraphErrors *gr3 = new TGraphErrors(21,ccmultPP,ccv2PnP,0,ccv2ePnP);
  gr3->SetTitle("");
  gr3->SetMarkerStyle(21);
  gr3->SetMarkerSize(1);
  gr3->SetMarkerColor(kBlue-7);
  gr3->SetLineWidth(2);
  gr3->SetLineColor(kBlue-7);
  gr3->Draw("psameezL");

  TGraphErrors *gr4 = new TGraphErrors(10,pcmultEP,pcv2EP,0,pcv2eEP);
  gr4->SetTitle("");
  gr4->SetMarkerStyle(27);
  gr4->SetMarkerSize(1);
  gr4->SetMarkerColor(kPink+9);
  gr4->SetLineWidth(2);
  gr4->SetLineColor(kPink+9);
  gr4->Draw("psameezL");

  TGraphErrors *gr5 = new TGraphErrors(21,pcmultPP,pcv2PtP,0,pcv2ePtP);
  gr5->SetTitle("");
  gr5->SetMarkerStyle(24);
  gr5->SetMarkerSize(1);
  gr5->SetMarkerColor(2);
  gr5->SetLineWidth(2);
  gr5->SetLineColor(2);
  gr5->Draw("psameezL");

  TGraphErrors *gr6 = new TGraphErrors(21,pcmultPP,pcv2PnP,0,pcv2ePnP);
  gr6->SetTitle("");
  gr6->SetMarkerStyle(25);
  gr6->SetMarkerSize(1);
  gr6->SetMarkerColor(1);
  gr6->SetLineWidth(2);
  gr6->SetLineColor(1);
  gr6->Draw("psameezL");


  TGraphErrors *gr7 = new TGraphErrors(11,pbpbmult,pbpbv2,0,pbpbv2e);
  gr7->SetTitle("");
  gr7->SetMarkerStyle(43);
  gr7->SetMarkerSize(2);
  gr7->SetMarkerColor(2);
  //gr7->SetLineWidth(2);
  //gr7->SetLineColor(1);
  gr7->Draw("psameez");

  TGraphErrors *gr8 = new TGraphErrors(11,ppbmult,ppbv2,0,ppbv2e);
  gr8->SetTitle("");
  gr8->SetMarkerStyle(42);
  gr8->SetMarkerSize(2);
  gr8->SetMarkerColor(2);
  //gr7->SetLineWidth(2);
  //gr7->SetLineColor(1);
  gr8->Draw("psameez");


    TLegend *leg = new TLegend(0.69,0.52,0.96,1);
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
    leg->AddEntry(gr7,"2PC Pb+Pb","pl");
    leg->AddEntry(gr8,"2PC p+Pb","pl");
    // leg->AddEntry(V2vsPt,"Input v_{2}","l");
    leg->Draw();
 
    TLatex *tex2= new TLatex(20,0.1785,"AMPT, #sqrt{s_{NN}} = 7.0 TeV");
    tex2->SetTextColor(1);
    tex2->SetTextSize(0.04);
    tex2->SetTextFont(42);
    tex2->Draw();
    TLatex *tex3= new TLatex(20,0.1635,"#sigma = 3.0 mb");
    tex3->SetTextColor(1);
    tex3->SetTextSize(0.04);
    tex3->SetTextFont(42);
    tex3->Draw();
    TLatex *tex4= new TLatex(20,0.1485,"0.2 < p_{T} [GeV/c] < 1000");
    tex4->SetTextColor(1);
    tex4->SetTextSize(0.04);
    tex4->SetTextFont(42);
    tex4->Draw();

    TLatex *tex5= new TLatex(186, 0.1935, "(a)");
    tex5->SetTextColor(1);
    tex5->SetTextSize(0.035);
    tex5->Draw();


  c1->Print("nmult_v2.png");
  c1->Print("nmult_v2.pdf");

}


