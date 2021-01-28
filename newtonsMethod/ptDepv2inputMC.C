#include "TH1.h"
#include "TRandom3.h"
using namespace std;
#include "newtonsMethod.h"

void ptDepv2inputMC(){

  int nEvent = 10000;
  int multLow = 100;
  const int multHigh = 105;

  float Psi;
  float pt[multHigh];
  float eta[multHigh];
  float phi[multHigh];
  const int nPtBin = 14;
  float ptBins[nPtBin+1] = {0.2, 0.4, 0.6, 0.8, 1.0, 1.5, 2.0, 2.5, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 10.0};

  TF1 *ptDist  = new TF1("ptDist","exp(-(x/0.90))+0.15*exp (-(x/15))", 0.2,10);
  TF1 *etaDist = new TF1("etaDist","exp(-(x-2.1)^2/6.3)+exp(-(x+2.1)^2/6.3)",-2.4,2.4);
  TF1 *v2vsPt = new TF1("v2vsPt","((x/3.2)^2.3/(1+(x/3.4)^2.1))*(.00005+(1/x)^1.4)",0.2,10);

  TH1D *v2hist[nPtBin];
  TH1D *v2Input[nPtBin];
  TH1D *meanPt[nPtBin];
  for(int i=0; i<nPtBin; i++){
    v2hist[i] = new TH1D(Form("v2hist_%d", i), Form("v2hist_%d", i), 120,-1.1,1.1);
    v2Input[i] = new TH1D(Form("v2Input_%d", i), Form("v2Input_%d", i), 120,-1.1,1.1);
    meanPt[i] = new TH1D(Form("meanPt_%d", i), Form("meanPt_%d", i), 100,0,10);
  }
  TH1D *pthist = new TH1D("pthist","pthist",100,0,10);
  TH1D *etahist = new TH1D("etahist","etahist",100,-3,3);
  TH1D *multhist = new TH1D("multhist","multhist",100,multLow-5,multHigh+5);

  TRandom3 *randomN;
  randomN = new TRandom3(0);
  gRandom->SetSeed(0);

  for(int i=0; i<nEvent; i++){
    if(i%1000 == 0){
      cout<<" i = "<<i<<" , nEvent = "<<nEvent<<endl;
    }
    Psi = randomN->Uniform(0.0, TMath::Pi()*2);
    int mult = randomN->Uniform(multLow, multHigh);
    multhist->Fill(mult);
    //cout<<"Psi = "<<Psi<<"   mult = "<<mult<<endl;
    for(int j=0; j<mult; j++){
      float mypt = ptDist->GetRandom();
      pthist->Fill(mypt);
      float myeta = etaDist->GetRandom();
      etahist->Fill(myeta);
      float phi0 = randomN->Uniform(0.0, TMath::Pi()*2);

      float v2 = v2vsPt->Eval(mypt);
      float initialPhi = 0.01;

      // get a better initial phi: 
      double phiTmp = -5;
      while (func(phiTmp, v2, Psi, phi0)*func(phiTmp+0.2, v2, Psi, phi0)>0){
        phiTmp = phiTmp + 0.2;
        //cout<<"phiTmp = "<<phiTmp<<endl;
      }   
      initialPhi = phiTmp + 0.1; //update initialPhi to fix the method
      //cout<<"initialPhi = "<<initialPhi<<endl;    

      float newPhi = newtonMethod(initialPhi, v2, Psi, phi0);

      for(int k=0; k<nPtBin; k++){
        if(mypt>ptBins[k] && mypt<ptBins[k+1]){
          v2hist[k]->Fill(cos(2*(newPhi - Psi)));
          v2Input[k]->Fill(v2);
          meanPt[k]->Fill(mypt);
        }
      }

    }
  }  

  cout<<"nEvent = "<<nEvent<<"  meanMult = "<<multhist->GetMean()<<endl;
  for(int k=0; k<nPtBin; k++){
    //cout<<"k = "<<k<<"  v2input = "<<v2Input[k]->GetMean()<<"  v2Mean = "<<v2hist[k]->GetMean()<<"  v2MeanError = "<<v2hist[k]->GetMeanError()<<endl;
    cout<<k<<"  "<<meanPt[k]->GetMean()<<"  "<<v2Input[k]->GetMean()<<"   "<<v2hist[k]->GetMean()<<"  "<<v2hist[k]->GetMeanError()<<endl;
  }

}


