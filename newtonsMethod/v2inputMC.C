#include "TH1.h"
#include "TRandom3.h"
using namespace std;
#include "newtonsMethod.h"

void v2inputMC(){

  int nEvent = 10000;
  int multLow = 100;
  const int multHigh = 105;

  float Psi;
  //float pt[multHigh];
  //float eta[multHigh];
  //float phi[multHigh];

  //TF1 *ptDist  = new TF1("ptDist","exp(-(x/0.90))+0.15*exp (-(x/15))", 0.2,10);
  //TF1 *etaDist = new TF1("etaDist","exp(-(x-2.1)^2/6.3)+exp(-(x+2.1)^2/6.3)",-2.4,2.4);
  //TF1 *v2vsPt = new TF1("v2vsPt","((x/3.2)^2.3/(1+(x/3.4)^2.1))*(.00005+(1/x)^1.4)",0.2,10);
  double v2 = 0.3;

  TH1D *v2hist = new TH1D("v2hist","v2hist",120,-1.1,1.1);
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
      //float mypt = ptDist->GetRandom();
      float phi0 = randomN->Uniform(0.0, TMath::Pi()*2);

      float initialPhi = 0.1;

      // get a better initial phi: 
      double phiTmp = -5;
      while (func(phiTmp, v2, Psi, phi0)*func(phiTmp+0.2, v2, Psi, phi0)>0){
        phiTmp = phiTmp + 0.2;
        //cout<<"phiTmp = "<<phiTmp<<endl;
      }   
      initialPhi = phiTmp + 0.1; //update initialPhi to fix the method
      //cout<<"initialPhi = "<<initialPhi<<endl;    
      
      float newPhi = newtonMethod(initialPhi, v2, Psi, phi0);
      v2hist->Fill(cos(2*(newPhi - Psi)));
    }
  }  

  cout<<"v2input = "<<v2<<"  v2Mean = "<<v2hist->GetMean()<<"  v2MeanError = "<<v2hist->GetMeanError()<<endl;
  cout<<"nEvent = "<<nEvent<<"  meanMult = "<<multhist->GetMean()<<endl;

}


