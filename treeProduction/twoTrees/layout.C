void layout(){

   const int A_max = 12;
   float x_projectile[A_max];
   float y_projectile[A_max];
   float status_projectile[A_max];
   float x_target[A_max];
   float y_target[A_max];
   float status_target[A_max];
   int pid_projectile[A_max];
   int pid_target[A_max];

   int nEvent = 0;
   int nA_projectile, nA_target;
   float b, tmp;

   float xMean_projectile=0;
   float yMean_projectile=0;
   float xMean_target=0;
   float yMean_target=0;

   ifstream inFile;
   inFile.open("npart-xy_16.dat");
   inFile>>nEvent; 
   inFile>>tmp; 
   inFile>>nA_projectile; 
   inFile>>nA_target; 
   inFile>>b; 
   for(int i=0; i<nA_projectile; i++){
      inFile>>x_projectile[i];
      inFile>>y_projectile[i];
      inFile>>tmp;
      inFile>>status_projectile[i];
      inFile>>tmp;
      inFile>>tmp;
      inFile>>pid_projectile[i];
      //cout<<x_projectile[i]<<endl;
      xMean_projectile += x_projectile[i]/nA_projectile;
      yMean_projectile += y_projectile[i]/nA_projectile;
   }
   for(int i=0; i<nA_target; i++){
      inFile>>x_target[i];
      inFile>>y_target[i];
      inFile>>tmp;
      inFile>>status_target[i];
      inFile>>tmp;
      inFile>>tmp;
      inFile>>pid_target[i];
      //cout<<x_target[i]<<endl;
      xMean_target += x_target[i]/nA_target;
      yMean_target += y_target[i]/nA_target;
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
 TH1D* hist = new TH1D("hist","",200,-10.,10.0);
 hist->SetXTitle("x (fm)");
 hist->SetYTitle("y (fm)");
 hist->SetMinimum(-10);
 hist->SetMaximum(10);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(1.1);
 hist->GetXaxis()->SetTitleOffset(1.1);
 hist->GetXaxis()->SetTitleSize(0.066);
 hist->GetYaxis()->SetTitleSize(0.066);
 hist->GetXaxis()->SetLabelSize(0.05);
 hist->GetYaxis()->SetLabelSize(0.05);
 hist->Draw(" ");

   TEllipse *projectile = new TEllipse(xMean_projectile, yMean_projectile, 2.75);;
   projectile->SetLineWidth(2);
   projectile->SetLineColor(1);
   projectile->SetLineStyle(2);
   projectile->SetFillStyle(0);
   projectile->Draw("Lfsame");
   TEllipse *target = new TEllipse(xMean_target, yMean_target, 2.75);;
   target->SetLineWidth(2);
   target->SetLineColor(4);
   target->SetLineStyle(2);
   target->SetFillStyle(0);
   target->Draw("Lfsame");

   TEllipse *nucleon_projectile[A_max];
   for(int i=0; i<nA_projectile; i++){
     nucleon_projectile[i] = new TEllipse(x_projectile[i], y_projectile[i], 0.5);
     nucleon_projectile[i]->SetLineWidth(2);
     nucleon_projectile[i]->SetLineColor(1);
     nucleon_projectile[i]->SetFillStyle(3001); 
     nucleon_projectile[i]->SetFillColor(15);
     if(status_projectile[i]>0){
      //nucleon_projectile[i]->SetLineColor(1);
      nucleon_projectile[i]->SetFillStyle(3001); 
      nucleon_projectile[i]->SetFillColor(2);
     }
     if(pid_projectile[i]==2112){
      nucleon_projectile[i]->SetLineWidth(1);
     }

     nucleon_projectile[i]->Draw("Lfsame");
   }

   TEllipse *nucleon_target[A_max];
   for(int i=0; i<nA_target; i++){
     nucleon_target[i] = new TEllipse(x_target[i], y_target[i], 0.5);
     nucleon_target[i]->SetLineWidth(2);
     nucleon_target[i]->SetLineColor(4);
     nucleon_target[i]->SetFillStyle(3001);
     nucleon_target[i]->SetFillColor(38);
     if(status_target[i]>0){
      //nucleon_target[i]->SetLineColor(4);
      nucleon_target[i]->SetFillStyle(3001);
      nucleon_target[i]->SetFillColor(2);
     }
     if(pid_target[i]==2112){
      nucleon_target[i]->SetLineWidth(1);
     }
     nucleon_target[i]->Draw("Lfsame");
   }

    TLatex *tex1= new TLatex(-6.6,7.0,"C+C @ 7.0 TeV, b = 4.3 fm");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.05);
    tex1->SetTextFont(42);
    tex1->Draw();

   c1->SaveAs("plot_CCcollision_layout.png");
   c1->SaveAs("plot_CCcollision_layout.pdf");

}

