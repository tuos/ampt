void eventSimu(){

TF2 *f2 = new TF2("f2","TMath::Gaus(x,0,6)*TMath::Gaus(y,0,2)",-20,20,-20,20);
TF2 *f2ecc = new TF2("f2ecc","TMath::Gaus(x,0,2)*TMath::Gaus(y,0,6)",-20,20,-20,20);

const int n=10000;
double x[n];
double y[n];
double px[n];
double py[n];
TH2D *h2 = new TH2D("h2","",100,-20,20,100,-20,20);
TH2D *h2ecc = new TH2D("h2ecc","",100,-20,20,100,-20,20);
for(int i=0; i<n; i++){
  f2ecc->GetRandom2(x[i], y[i]);
  f2->GetRandom2(px[i], py[i]);
  h2->Fill(px[i], py[i]);
  h2ecc->Fill(x[i], y[i]);
}

h2->Draw("colz");
//h2ecc->Draw("colz");

}


