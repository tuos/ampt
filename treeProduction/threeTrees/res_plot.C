void res_plot() {
  const int nMultBin=10;
  double nmult[nMultBin];
  double v2[nMultBin];
  double v2e[nMultBin];
  double res[nMultBin];
  double rese[nMultBin];

  ifstream inv2;
  inv2.open("output_nmultv2EP.txt");
  //inv2.open("output_v2_newptbins_Nch120150.txt");
  if(!inv2.good())    cout<<" input fail"<<endl;
  else cout<<" input OK! "<<endl;
  for(int i=0;i<nMultBin;i++){
    inv2>>nmult[i];  
    inv2>>v2[i];  
    inv2>>v2e[i];
    inv2>>res[i];
    inv2>>rese[i];  
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
 TH1D* hist = new TH1D("hist","",200,0.,200.);
 hist->SetXTitle("N_{mult}");
 hist->SetYTitle("Resolution{EP}");
 hist->SetMinimum(0.0);
 hist->SetMaximum(1.);
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
  TGraphErrors *gr2 = new TGraphErrors(10,nmult,res,0,rese);
  gr2->SetTitle("");
  gr2->SetMarkerStyle(20);
  gr2->SetMarkerSize(1.2);
  gr2->SetMarkerColor(2);
  gr2->SetLineWidth(2);
  gr2->SetLineColor(2);
  gr2->Draw("psameezL");
 

    TLegend *leg = new TLegend(0.5,0.33,0.78,0.47);
    leg->SetFillColor(10);
    leg->SetBorderSize(0);
    leg->SetTextFont(42);
    leg->SetTextColor(1);
    leg->SetTextSize(0.05);
    //leg->SetLineStyle(0.06);
    leg->AddEntry(gr2,"AMPT, #sigma = 3.0 mb ","pl");
    // leg->AddEntry(V2vsPt,"Input v_{2}","l");
    leg->Draw();
  
    TLatex *tex2= new TLatex(0.3,0.26,"C+C @ 7.0 TeV");
    tex2->SetTextColor(1);
    tex2->SetTextSize(0.05);
    tex2->SetTextFont(42);
    tex2->Draw();
    TLatex *tex3= new TLatex(0.3,0.235,"1.0 < |#eta| < 2.4");
    tex3->SetTextColor(1);
    tex3->SetTextSize(0.05);
    tex3->SetTextFont(42);
    tex3->Draw();
    TLatex *tex4= new TLatex(0.3,0.21,"0-100%");
    tex4->SetTextColor(1);
    tex4->SetTextSize(0.05);
    tex4->SetTextFont(42);
    //tex4->Draw();


  c1->Print("eventplane_res.png");
  c1->Print("eventplane_res.pdf");

}


