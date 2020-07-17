void v2pt_plot() {
  const int nPtBin=15;
  double pt[nPtBin];
  double v2PtP[nPtBin];
  double v2ePtP[nPtBin];
  double v2PnP[nPtBin];
  double v2ePnP[nPtBin];
  double v2EP[nPtBin];
  double v2eEP[nPtBin];
  double temp;

  ifstream inv2ptp;
  ifstream inv2pnp;
  ifstream inv2ep;
  inv2ptp.open("output_v2ptPtP.txt");
  inv2pnp.open("output_v2ptPnP.txt");
  inv2ep.open("output_v2ptEP.txt");
  //inv2.open("output_v2_newptbins_Nch120150.txt");
  if(!inv2ptp.good())    cout<<" input fail"<<endl;
  else cout<<" input OK! "<<endl;
  for(int i=0;i<nPtBin;i++){
    inv2ptp>>pt[i];  
    inv2ptp>>v2PtP[i];  
    inv2ptp>>v2ePtP[i];
    inv2pnp>>temp;
    inv2pnp>>v2PnP[i];
    inv2pnp>>v2ePnP[i];
    inv2ep>>temp;
    inv2ep>>v2EP[i];
    inv2ep>>v2eEP[i];
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
 TH1D* hist = new TH1D("hist","",200,0.,3.0);
 hist->SetXTitle("p_{T} (GeV/c)");
 hist->SetYTitle("v_{2}");
 hist->SetMinimum(-0.1);
 hist->SetMaximum(0.7);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(1.1);
 hist->GetXaxis()->SetTitleOffset(0.95);
 hist->GetXaxis()->SetTitleSize(0.066);
 hist->GetYaxis()->SetTitleSize(0.066);
 hist->GetXaxis()->SetLabelSize(0.05);
 hist->GetYaxis()->SetLabelSize(0.05);
 hist->Draw();

  TF1 *V2vsPt = new TF1("V2vsPt","((x/3.4)^1.8/(1+(x/3)^1.8))*(.00005+(1/x)^0.8)",0.2,10);
  V2vsPt->SetLineColor(2);
  V2vsPt->SetLineWidth(2);
  V2vsPt->SetLineStyle(2);
  // V2vsPt->Draw("same");

  //TGraphErrors *gr2 = new TGraphErrors(nPtBin,pt,v2,0,v2e);
  TGraphErrors *gr2 = new TGraphErrors(8,pt,v2EP,0,v2eEP);
  gr2->SetTitle("");
  gr2->SetMarkerStyle(20);
  gr2->SetMarkerSize(1.2);
  gr2->SetMarkerColor(2);
  gr2->SetLineWidth(2);
  gr2->SetLineColor(2);
  gr2->Draw("psameezL");

  TGraphErrors *gr3 = new TGraphErrors(8,pt,v2PtP,0,v2ePtP);
  gr3->SetTitle("");
  gr3->SetMarkerStyle(21);
  gr3->SetMarkerSize(1.2);
  gr3->SetMarkerColor(3);
  gr3->SetLineWidth(2);
  gr3->SetLineColor(3);
  gr3->Draw("psameezL");

  TGraphErrors *gr4 = new TGraphErrors(8,pt,v2PnP,0,v2ePnP);
  gr4->SetTitle("");
  gr4->SetMarkerStyle(21);
  gr4->SetMarkerSize(1.2);
  gr4->SetMarkerColor(4);
  gr4->SetLineWidth(2);
  gr4->SetLineColor(4);
  gr4->Draw("psameezL");

    TLegend *leg = new TLegend(0.5,0.33,0.78,0.47);
    leg->SetFillColor(10);
    leg->SetBorderSize(0);
    leg->SetTextFont(42);
    leg->SetTextColor(1);
    leg->SetTextSize(0.05);
    //leg->SetLineStyle(0.06);
    leg->AddEntry(gr2,"Event Plane","pl");
    leg->AddEntry(gr3,"Participant Plane","pl");
    leg->AddEntry(gr4,"Parton Plane","pl");
    // leg->AddEntry(V2vsPt,"Input v_{2}","l");
    leg->Draw();
  
    TLatex *tex2= new TLatex(0.3,0.26,"C+C @ 7.0 TeV");
    tex2->SetTextColor(1);
    tex2->SetTextSize(0.05);
    tex2->SetTextFont(42);
    tex2->Draw();
    TLatex *tex3= new TLatex(0.3,0.235,"|#eta| < 2.4");
    tex3->SetTextColor(1);
    tex3->SetTextSize(0.05);
    tex3->SetTextFont(42);
    tex3->Draw();
    TLatex *tex4= new TLatex(0.3,0.21,"AMPT,  #sigma = 3.0 mb, 0-100%");
    tex4->SetTextColor(1);
    tex4->SetTextSize(0.05);
    tex4->SetTextFont(42);
    tex4->Draw();


  c1->Print("v2pt.png");
  c1->Print("v2pt.pdf");

}


