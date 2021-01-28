void figure_v2input(){
  const int nPtBin=14;
  double pt[nPtBin];
  double v2in[nPtBin];
  double v2[nPtBin];
  double v2e[nPtBin];
  double tmp;

  ifstream inv2;
  inv2.open("out_ptDep.txt");
  if(!inv2.good())    cout<<" input fail"<<endl;
  else cout<<" input OK! "<<endl;
  for(int i=0;i<nPtBin;i++){
    inv2>>tmp;
    inv2>>pt[i];  
    inv2>>v2in[i];  
    inv2>>v2[i];  
    inv2>>v2e[i];  
  } 

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
 TH1D* hist = new TH1D("hist","",200,0.,10.0);
 hist->SetXTitle("p_{T} (GeV/c)");
 hist->SetYTitle("v_{2}");
 hist->SetMinimum(0.0001);
 hist->SetMaximum(0.199);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(1.1);
 hist->GetXaxis()->SetTitleOffset(0.95);
 hist->GetXaxis()->SetTitleSize(0.066);
 hist->GetYaxis()->SetTitleSize(0.066);
 hist->GetXaxis()->SetLabelSize(0.05);
 hist->GetYaxis()->SetLabelSize(0.05);
 hist->Draw();

  TF1 *v2vsPt = new TF1("v2vsPt","((x/3.2)^2.3/(1+(x/3.4)^2.1))*(.00005+(1/x)^1.4)",0.2,10);
  v2vsPt->SetLineColor(1);
  v2vsPt->SetLineWidth(2);
  v2vsPt->SetLineStyle(2);
  v2vsPt->Draw("same");

  TGraphErrors *gr1 = new TGraphErrors(nPtBin,pt,v2in,0,0);
  gr1->SetTitle("");
  gr1->SetMarkerStyle(25);
  gr1->SetMarkerSize(1.2);
  gr1->SetMarkerColor(1);
  gr1->SetLineWidth(2);
  gr1->SetLineColor(1);
  gr1->Draw("psameezL");

  TGraphErrors *gr2 = new TGraphErrors(nPtBin,pt,v2,0,v2e);
  gr2->SetTitle("");
  gr2->SetMarkerStyle(20);
  gr2->SetMarkerSize(1.2);
  gr2->SetMarkerColor(2);
  gr2->SetLineWidth(2);
  gr2->SetLineColor(2);
  gr2->Draw("psameezL");
 

    TLegend *leg = new TLegend(0.6,0.66,0.88,0.92);
    leg->SetFillColor(10);
    leg->SetBorderSize(0);
    leg->SetTextFont(42);
    leg->SetTextColor(1);
    leg->SetTextSize(0.05);
    //leg->SetLineStyle(0.06);
    leg->AddEntry(v2vsPt,"Input v_{2} curve","l");
    leg->AddEntry(gr1,"Input v_{2} ","pl");
    leg->AddEntry(gr2,"Final v_{2} ","pl");
    leg->Draw();
  
    TLatex *tex2= new TLatex(0.3,0.26,"Pb+Pb @ 5.0 TeV, 10k events");
    tex2->SetTextColor(1);
    tex2->SetTextSize(0.05);
    tex2->SetTextFont(42);
    //tex2->Draw();

  c1->Print("plot_ptDepv2input.png");
  c1->Print("plot_ptDepv2input.pdf");

}


