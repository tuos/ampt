#include <stdio.h>
#include <complex>
#include <iostream>
#include "TF1.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH1F.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TTree.h"
#include <TMath.h>
#include "TComplex.h"
#include "TRandom3.h"
using namespace std; 
void simu_correlation_vs_nmult(){

     long nEvt, nEvtProcess;
     float tempEccPtP, tempV2PtP, tempEccPnP, tempV2PnP; 

     //Int_t MultIndex;
     Int_t multBin = -1;
     Int_t nParticle, iParticle;
     Float_t phi[20000];
     Float_t pt[20000];
     Double_t px[20000];
     Double_t py[20000];
     Float_t eta[20000];
     TH1D *histPt = new TH1D("histPt", "histPt", 200,0,10);

     TF2 *f2 = new TF2("f2","TMath::Gaus(x,0,6)*TMath::Gaus(y,0,2)",-10,10,-10,10);
     TF2 *f2ecc = new TF2("f2ecc","TMath::Gaus(x,0,2)*TMath::Gaus(y,0,6)",-10,10,-10,10);

     TH1D *histTempPtP = new TH1D("histTempPtP", "", 200, -1,1);
     TH1D *histTempPnP = new TH1D("histTempPnP", "", 200, -1, 1);


     TH1D *histPtPCos = new TH1D("histPtPCos", "", 200,-1,1);
     TH1D *histPtPSin = new TH1D("histPtPSin", "", 200,-1,1); 
     TH1D *histPnPCos = new TH1D("histPnPCos", "", 200,-1,1);
     TH1D *histPnPSin = new TH1D("histPnPSin", "", 200,-1,1);  

     TH1D *histEccPtPCos = new TH1D("histEccPtPCos", "", 200,-1,1);
     TH1D *histEccPtPSin = new TH1D("histEccPtPSin", "", 200,-1,1);
     TH1D *histEccPtPR = new TH1D("histEccPtPR", "", 200,-1,1);
     TH1D *histEccPnPCos = new TH1D("histEccPnPCos", "", 200,-1,1);
     TH1D *histEccPnPSin = new TH1D("histEccPnPSin", "", 200,-1,1);
     TH1D *histEccPnPR = new TH1D("histEccPnPR", "", 200,-1,1);

     

     const int NB_SLICE_MULT = 30;
     double minMultCut[NB_SLICE_MULT] =  {0, 10, 20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290}; 
     double maxMultCut[NB_SLICE_MULT] = {10, 20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190, 200,210,220,230,240,250,260,270,280,290,300}; //30 bins
     TH1D *histMult[NB_SLICE_MULT];
     TH2D *histCorrPtP[NB_SLICE_MULT];
     TH2D *histCorrPnP[NB_SLICE_MULT];
     TH1D *histQEcc2V2Numerator[NB_SLICE_MULT];
     TH1D *histQEcc2Sqr[NB_SLICE_MULT];
     TH1D *histQV2Sqr[NB_SLICE_MULT];
     for(int i=0; i<NB_SLICE_MULT; i++){
       histMult[i] = new TH1D(Form("histMult_%d",i), "", 300,0,300);
       histCorrPtP[i] = new TH2D(Form("histCorrPtP_%d",i), "", 100,0,10,100,0,10);
       histCorrPnP[i] = new TH2D(Form("histCorrPnP_%d",i), "", 100,0,10,100,0,10);
       histQEcc2V2Numerator[i] = new TH1D(Form("histQEcc2V2Numerator_%d",i), "", 220,-1.1,1.1);
       histQEcc2Sqr[i] = new TH1D(Form("histQEcc2Sqr_%d",i), "", 200,0,2);
       histQV2Sqr[i] = new TH1D(Form("histQV2Sqr_%d",i), "", 200,0,2);
     }
     double QEcc2V2[NB_SLICE_MULT];


     Int_t Partonpid[200000];
     Int_t nParton;
     Double_t xParton[200000];
     Double_t yParton[200000];
     Float_t rparton, phiparton, Psiparton;

     nEvt=10000;

     // starting the second event loop
     for(long ne=0; ne<nEvt; ne++)
     {
       if(ne%2000==0)  cout<<"Have run "<<ne<<" of the total "<<nEvt<<" events; "<<endl;

       histPtPCos->Reset();
       histPtPSin->Reset();
       histPnPCos->Reset();
       histPnPSin->Reset();

       histTempPtP->Reset();
       histTempPnP->Reset();

       histEccPtPCos->Reset();
       histEccPtPSin->Reset();
       histEccPtPR->Reset();
       histEccPnPCos->Reset();
       histEccPnPSin->Reset();
       histEccPnPR->Reset();

       TComplex Ecc2Pn=0;
       TComplex V2Final=0;

       TRandom3 *rnd = new TRandom3(0);
       nParticle = rnd->Uniform(0,300);

       if(nParticle<0 || nParticle>300) continue;

       for(int imult=0;imult<NB_SLICE_MULT;imult++){
          if((nParticle>minMultCut[imult]&&nParticle<=maxMultCut[imult])){
              multBin=imult;
          }
       }

      histMult[multBin]->Fill(nParticle);


      // finding parton plane eccentricity
      int nParton = rnd->Uniform(0,300);
      //int nParton = nParticle;
      for(int i=0; i<nParton; i++){
          f2ecc->GetRandom2(xParton[i], yParton[i]);
          rparton = TMath::Sqrt((xParton[i]*xParton[i]) + (yParton[i]*yParton[i]));
          phiparton = TMath::ATan2(yParton[i], xParton[i]);
          histEccPnPCos->Fill(rparton*rparton*(TMath::Cos(2*phiparton)));
          histEccPnPSin->Fill(rparton*rparton*(TMath::Sin(2*phiparton)));
          histEccPnPR->Fill(rparton*rparton);
          Ecc2Pn += TComplex::Exp(TComplex(0,2*(phiparton-TMath::Pi()/2)));
          //Ecc2Pn += TComplex::Exp(TComplex(0,2*(phiparton)));
      }

      tempEccPnP = TMath::Sqrt(pow(histEccPnPCos->GetMean(), 2)+pow(histEccPnPCos->GetMean(), 2))/(histEccPnPR->GetMean());
      //histEccPnP[multBin]->Fill(TMath::Sqrt(pow(histEccPnPCos->GetMean(), 2)+pow(histEccPnPCos->GetMean(), 2))/(histEccPnPR->GetMean()));


       // calculating v2 for each event
       for(iParticle=0; iParticle<nParticle; iParticle++){
         //if(pt[iParticle]<0.2||pt[iParticle]>1000) continue;

         f2->GetRandom2(px[iParticle], py[iParticle]);
         phi[iParticle] = TMath::ATan2(py[iParticle],px[iParticle]);//*180/TMath::Pi();

         histTempPtP->Fill(cos(2*(phi[iParticle] - 0)));
         histTempPnP->Fill(cos(2*(phi[iParticle] - 0)));

         V2Final += TComplex::Exp(TComplex(0,2*phi[iParticle]));
       } // end of the particle loop
       //histV2EP[multBin]->Fill(histTempEP->GetMean());
       //
       tempV2PtP = histTempPtP->GetMean();
       tempV2PnP = histTempPnP->GetMean();
       //histV2PtP[multBin]->Fill(histTempPtP->GetMean()/(TMath::Sqrt(pow(histEccPtPCos->GetMean(), 2)+pow(histEccPtPCos->GetMean(), 2))/(histEccPtPR->GetMean())));
       //histV2PnP[multBin]->Fill(histTempPnP->GetMean()/(TMath::Sqrt(pow(histEccPnPCos->GetMean(), 2)+pow(histEccPnPCos->GetMean(), 2))/(histEccPnPR->GetMean())));
       //cout<<eventPlaneMinus<<"   "<<eventPlanePlus<<"   "<<Psipart<<"   "<<Psiparton<<endl;
       histCorrPtP[multBin]->Fill(tempEccPtP, tempV2PtP);
       histCorrPnP[multBin]->Fill(tempEccPnP, tempV2PtP);

       double tmpnParton=nParton;
       histQEcc2V2Numerator[multBin]->Fill( ((Ecc2Pn/tmpnParton)*TComplex::Conjugate(V2Final/histTempPnP->GetEntries())).Re() );
       histQEcc2Sqr[multBin]->Fill(TComplex::Abs(Ecc2Pn/tmpnParton)*TComplex::Abs(Ecc2Pn/tmpnParton));
       histQV2Sqr[multBin]->Fill(TComplex::Abs(V2Final/histTempPnP->GetEntries())*TComplex::Abs(V2Final/histTempPnP->GetEntries()));
       //histQEcc2V2Numerator[multBin]->Fill( ((Ecc2Pn*1.0)*TComplex::Conjugate(V2Final)).Re() );
       //histQEcc2Sqr[multBin]->Fill(TComplex::Abs(Ecc2Pn*1.0)*TComplex::Abs(Ecc2Pn*1.0));
       //histQV2Sqr[multBin]->Fill(TComplex::Abs(V2Final)*TComplex::Abs(V2Final));
      } // end of the second event loop

     //ofstream output_corr_vs_nmult_PtP;
     //ofstream output_corr_vs_nmult_PnP;
     ofstream output_Qecc2v2_vs_nmult;
     //output_corr_vs_nmult_PtP.open("output_corr_vs_nmult_PtP.txt");
     //output_corr_vs_nmult_PnP.open("output_corr_vs_nmult_PnP.txt");
     output_Qecc2v2_vs_nmult.open("test_output_Qecc2v2_vs_nmult.txt");

     for(int i=0; i<NB_SLICE_MULT; i++){
         QEcc2V2[i]=histQEcc2V2Numerator[i]->GetMean()/sqrt(histQEcc2Sqr[i]->GetMean()*histQV2Sqr[i]->GetMean());
         ///cout<<histMult[i]->GetEntries()<<"   "<<histMult[i]->GetMean()<<"   "<<histQEcc2V2Numerator[i]->GetMean()<<"   "<<histQEcc2Sqr[i]->GetMean()<<"   "<<histQV2Sqr[i]->GetMean()<<", V2="<<sqrt(histQV2Sqr[i]->GetMean())<<endl;
         //cout<<histMult[i]->GetMean()<<"   "<<histCorrPtP[i]->GetCorrelationFactor()<<"   "<<histCorrPnP[i]->GetCorrelationFactor()<<endl;
         //output_corr_vs_nmult_PtP<<histMult[i]->GetMean()<<"   "<<histCorrPtP[i]->GetCorrelationFactor()<<"   "<<(1-(pow(histCorrPtP[i]->GetCorrelationFactor(),2)))/pow(histCorrPtP[i]->GetEntries(),0.5)<<endl;
         //output_corr_vs_nmult_PnP<<histMult[i]->GetMean()<<"   "<<histCorrPnP[i]->GetCorrelationFactor()<<"   "<<(1-(pow(histCorrPnP[i]->GetCorrelationFactor(),2)))/pow(histCorrPnP[i]->GetEntries(),0.5)<<endl;
         output_Qecc2v2_vs_nmult<<histMult[i]->GetEntries()<<"   "<<histMult[i]->GetMean()<<"   "<<QEcc2V2[i]<<endl;
         cout<<histMult[i]->GetEntries()<<","<<histMult[i]->GetMean()<<","<<QEcc2V2[i]<<endl;
     }
/*
    TFile *outFile = new TFile("out_correlationCoeff.root","recreate");
    outFile->cd();
    for(int i=0; i<NB_SLICE_MULT; i++){
      histCorrPtP[i]->Write();
      histCorrPnP[i]->Write();
    }
*/    

      //TCanvas *c1 = new TCanvas("c1","c1",1,1,650,550);
      //hist2Dx_y->SetXTitle("x (fm)");
      //hist2Dx_y->SetYTitle("y (fm)"); 
      //hist2Dx_y->GetXaxis()->CenterTitle(1);
      //hist2Dx_y->GetYaxis()->CenterTitle(1);     
      //hist2Dx_y->Draw("box");
      //c1->SaveAs("plot_hist2Dx_y.pdf");

     TComplex tmpEcc2Pn=TComplex(0,2*3.13159*45/180);
     cout<<tmpEcc2Pn<<endl;

}
