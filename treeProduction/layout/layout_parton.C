void layout_parton(){

   const int A_max = 1094;
   float x_projectile[A_max];
   float y_projectile[A_max];
   float status_projectile[A_max];
   int pid_projectile[A_max];

   int nEvent = 0;
   int nA_projectile, nA_target;
   float b, tmp;

   ifstream inFile;
   inFile.open("parton-xy.txt");
   inFile>>nEvent; 
   inFile>>tmp; 
   inFile>>nA_projectile; 
   inFile>>tmp; 
   inFile>>tmp; 
   inFile>>tmp; 
   inFile>>tmp; 
   for(int i=0; i<nA_projectile; i++){
      inFile>>pid_projectile[i];
      if(abs(pid_projectile[i])>3)
        cout<<"pid: "<<pid_projectile[i]<<endl;
      inFile>>tmp;
      inFile>>tmp;
      inFile>>tmp;
      inFile>>tmp;
      inFile>>x_projectile[i];
      inFile>>y_projectile[i];
      inFile>>tmp;
      inFile>>tmp;
      inFile>>tmp;
      inFile>>tmp;
      inFile>>tmp;
      //cout<<x_projectile[i]<<endl;
   }

  TCanvas *c1 = new TCanvas("c1","c1",1,1,650,650);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.15);
  c1->SetBottomMargin(0.15);
  c1->SetTopMargin(0.03);
  c1->SetRightMargin(0.03);
  //c1->Divide(2,1,0,0);
  gStyle->SetOptStat(0);
  c1->SetTicks(-1);
 TH1D* hist = new TH1D("hist","",200,-15.,15.0);
 hist->SetXTitle("x (fm)");
 hist->SetYTitle("y (fm)");
 hist->SetMinimum(-15);
 hist->SetMaximum(15);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(1.1);
 hist->GetXaxis()->SetTitleOffset(1.1);
 hist->GetXaxis()->SetTitleSize(0.066);
 hist->GetYaxis()->SetTitleSize(0.066);
 hist->GetXaxis()->SetLabelSize(0.05);
 hist->GetYaxis()->SetLabelSize(0.05);
 hist->Draw();

   TEllipse *nucleon_projectile[A_max];
   for(int i=0; i<nA_projectile; i++){
     nucleon_projectile[i] = new TEllipse(x_projectile[i], y_projectile[i], 0.2);
     nucleon_projectile[i]->SetLineWidth(1);
     
     if(abs(pid_projectile[i])==1)
       nucleon_projectile[i]->SetLineColor(1); // d 
     if(abs(pid_projectile[i])==2)
       nucleon_projectile[i]->SetLineColor(2); // u
     if(abs(pid_projectile[i])>2)
       nucleon_projectile[i]->SetLineColor(4); // s,c,... 

     //nucleon_projectile[i]->SetFillStyle(3001); 
     //nucleon_projectile[i]->SetFillColor(15);
     nucleon_projectile[i]->Draw("Lfsame");
   }

    TLatex *tex1= new TLatex(-10.6,10.0,"p+Pb @ 5.0 TeV, b = 2.37 fm");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.05);
    tex1->SetTextFont(42);
    tex1->Draw();

   c1->SaveAs("plot_pPbcollision_layout_parton.png");
   c1->SaveAs("plot_pPbcollision_layout_parton.pdf");

}

