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
using namespace std; 
void flowAnalysis_twoTrees_nmult_vs_v2(){

     long nEvt, nEvtProcess; 

     Int_t MultIndex;
     Int_t nParticle, iParticle;
     Float_t phi[20000];
     Float_t pt[20000];
     Float_t eta[20000];
     TH1D *histPt = new TH1D("histPt", "histPt", 200,0,10);

     TH2D *hist2DPtVsEta = new TH2D("hist2DPtVsEta","2D histogram of pT vs eta", 200, -2.4,2.4, 200,0.0,10);

     TH1D *histQSinPlus = new TH1D("histQSinPlus", "", 200,-1,1);
     TH1D *histQSinMinus = new TH1D("histQSinMinus", "", 200,-1,1);
     TH1D *histQCosPlus = new TH1D("histQCosPlus", "", 200,-1,1);
     TH1D *histQCosMinus = new TH1D("histQCosMinus", "", 200,-1,1);

     TH1D *histTempEP = new TH1D("histTempEP", "", 200, -1,1);
     TH1D *histTempPP = new TH1D("histTempPP", "", 200, -1,1);


     TH1D *histPPCos = new TH1D("histPPCos", "", 200,-1,1);
     TH1D *histPPSin = new TH1D("histPPSin", "", 200,-1,1); 

     double eventPlanePlus, eventPlaneMinus;

     

     const int NB_SLICE_PT = 10;
     //double minPtCut[NB_SLICE_PT] = {0.2,0.4,0.6,0.8,1.1,1.4,1.75,2.2,2.75,3.45,4.2,5.05,6.0,7.2,8.5};
     //double maxPtCut[NB_SLICE_PT] = {0.4,0.6,0.8,1.1,1.4,1.75,2.2,2.75,3.45,4.2,5.05,6.0,7.2,8.5,1000}; //15 bins
     TH1D *histEventPlaneRes[NB_SLICE_PT];   
     TH1D *histV2EP[NB_SLICE_PT];
     TH1D *histV2PP[NB_SLICE_PT];
     TH1D *histMult[NB_SLICE_PT];
     for(int i=0; i<NB_SLICE_PT; i++){
       histV2EP[i] = new TH1D(Form("histV2EP_%d",i), "", 200,-1,1);
       histV2PP[i] = new TH1D(Form("histV2PP_%d",i), "", 200,-1,1);  
       histMult[i] = new TH1D(Form("histMult_%d",i), "", 200,0,200);
       histEventPlaneRes[i] = new TH1D(Form("histEventPlaneRes_%d",i), "", 200,-1,1);
     }

     TH2D *hist2Dx_y = new TH2D("hist2Dx_y","Nucleon position x vs y", 200, -10,10, 200,-10,10);

     TFile inFile("./trees_testing.root", "read");
     TTree *t1 = (TTree*)inFile.Get("hadronTree");
     t1->SetBranchAddress("nMultiplicityTree", &nParticle);
     t1->SetBranchAddress("ptTree", &pt);
     t1->SetBranchAddress("etaTree", &eta);
     t1->SetBranchAddress("phiTree", &phi);


     const int maxNucleons = 208;
     Int_t nNucleonsProjectile, nNucleonsTarget;
     Float_t xProjectile[maxNucleons];
     Float_t yProjectile[maxNucleons];
     Int_t statusProjectile[maxNucleons];
     Float_t xTarget[maxNucleons];
     Float_t yTarget[maxNucleons];
     Int_t statusTarget[maxNucleons];
     Float_t rpart, phipart, Psipart;

     TTree *t2 = (TTree*)inFile.Get("participantTree");
     t2->SetBranchAddress("nNucleonsProjectileTree", &nNucleonsProjectile);
     t2->SetBranchAddress("xProjectileTree", &xProjectile);
     t2->SetBranchAddress("yProjectileTree", &yProjectile);
     t2->SetBranchAddress("statusProjectileTree", &statusProjectile);
     t2->SetBranchAddress("nNucleonsTargetTree", &nNucleonsTarget);
     t2->SetBranchAddress("xTargetTree", &xTarget);
     t2->SetBranchAddress("yTargetTree", &yTarget);
     t2->SetBranchAddress("statusTargetTree", &statusTarget);

     //t1->AddFriend("t2");

     nEvt=t1->GetEntries();
     //nEvtProcess=50;
     // first event loop for estimatig the event plane resolution
     for(long ne=0; ne<nEvt; ne++)
     {
       if(ne%2000==0)  cout<<"Have run "<<ne<<" of the total "<<nEvt<<" events; "<<endl;
       t1->GetEntry(ne);
       t2->GetEntry(ne);
       
       histQSinPlus->Reset();
       histQSinMinus->Reset();
       histQCosPlus->Reset();
       histQCosMinus->Reset();

       MultIndex = (nParticle-1) / 20;

      // if(ne==0){ //The first event
        // cout<<"nNucleonsProjectile = "<<nNucleonsProjectile<<endl;
         //for(int i=0; i<nNucleonsProjectile; i++){
           //hist2Dx_y->Fill(xProjectile[i], yProjectile[i]);
           //cout<<"x = "<<xProjectile[i]<<",  y = "<<yProjectile[i]<<endl;
         //}
         //cout<<"nNucleonsTarget = "<<nNucleonsTarget<<endl;
         //for(int i=0; i<nNucleonsTarget; i++){
           //hist2Dx_y->Fill(xTarget[i], yTarget[i]);
         //}
       //}
    
       if(nParticle<0 || nParticle>200) continue;

       for(iParticle=0; iParticle<nParticle; iParticle++){
           //cout<<"evtID = "<<ne<<",  particlesPt = "<<pt[iParticle]<<",  particlePhi = "<<phi[iParticle]<<endl;
           histPt->Fill(pt[iParticle]);
           //hist2DPtVsEta->Fill(eta[iParticle], pt[iParticle]);
       
           if(eta[iParticle]>1.0){
             histQSinPlus->Fill(sin(2*phi[iParticle]));
             histQCosPlus->Fill(cos(2*phi[iParticle]));
           }
           if(eta[iParticle]<-1.0){
             histQSinMinus->Fill(sin(2*phi[iParticle]));
             histQCosMinus->Fill(cos(2*phi[iParticle]));
           }
       }

       eventPlanePlus = 1.0/2*atan2(histQSinPlus->GetMean(), histQCosPlus->GetMean()); // EP in (-pi/2, pi/2);
       eventPlaneMinus = 1.0/2*atan2(histQSinMinus->GetMean(), histQCosMinus->GetMean()); // EP in (-pi/2, pi/2);
       histEventPlaneRes[MultIndex]->Fill(cos(2*(eventPlanePlus - eventPlaneMinus)));

      } // end of the first event loop
      //cout<<"Event Plane resolution = "<<sqrt(histEventPlaneRes->GetMean())<<endl;

      //histPt->Draw();
      //hist2DPtVsEta->Draw("colz");

     // starting the second event loop
     for(long ne=0; ne<nEvt; ne++)
     {
       if(ne%2000==0)  cout<<"Have run "<<ne<<" of the total "<<nEvt<<" events; "<<endl;
       t1->GetEntry(ne);
       t2->GetEntry(ne);

       histQSinPlus->Reset();
       histQSinMinus->Reset();
       histQCosPlus->Reset();
       histQCosMinus->Reset();
       histPPCos->Reset();
       histPPSin->Reset();
       histTempEP->Reset();
       histTempPP->Reset();

       MultIndex = (nParticle-1) / 20;

       if(nParticle<0 || nParticle>200) continue;

       histMult[MultIndex]->Fill(nParticle);

       // estimating the participant plane angle
       for(int i=0; i<nNucleonsProjectile; i++){
           if(statusProjectile[i]>0){
               rpart = TMath::Sqrt((xProjectile[i]*xProjectile[i]) + (yProjectile[i]*yProjectile[i]));
               phipart = TMath::ATan2(yProjectile[i], xProjectile[i]);
               histPPCos->Fill(rpart*rpart*(TMath::Cos(2*phipart)));
               histPPSin->Fill(rpart*rpart*(TMath::Sin(2*phipart)));
           }
       }
       for(int i=0; i<nNucleonsTarget; i++){
           if(statusTarget[i]>0){
               rpart = TMath::Sqrt((xTarget[i]*xTarget[i]) + (yTarget[i]*yTarget[i]));
               phipart = TMath::ATan2(yTarget[i], xTarget[i]);
               histPPCos->Fill(rpart*rpart*(TMath::Cos(2*phipart)));
               histPPSin->Fill(rpart*rpart*(TMath::Sin(2*phipart)));
           }
       }
       Psipart=(TMath::ATan2(histPPSin->GetMean(),histPPCos->GetMean())+TMath::Pi())/2.;

       // estimating event plane angle
       for(iParticle=0; iParticle<nParticle; iParticle++){

           if(eta[iParticle]>1.0){
             histQSinPlus->Fill(sin(2*phi[iParticle]));
             histQCosPlus->Fill(cos(2*phi[iParticle]));
           }
           if(eta[iParticle]<-1.0){
             histQSinMinus->Fill(sin(2*phi[iParticle]));
             histQCosMinus->Fill(cos(2*phi[iParticle]));
           }
        }
       eventPlanePlus = 1.0/2*atan2(histQSinPlus->GetMean(), histQCosPlus->GetMean()); // EP in (-pi/2, pi/2);
       eventPlaneMinus = 1.0/2*atan2(histQSinMinus->GetMean(), histQCosMinus->GetMean()); // EP in (-pi/2, pi/2);        
       // calculating v2 for each event
       for(iParticle=0; iParticle<nParticle; iParticle++){
         if(eta[iParticle]<-1.0||eta[iParticle]>1.0) continue;
         //if(phi[iParticle]>3.141592653589793) phi[iParticle]=phi[iParticle]-2*3.141592653589793; 
         if(pt[iParticle]<0.2||pt[iParticle]>1000) continue;

         //int ptBin=-1;
         //for(int ipt=0;ipt<NB_SLICE_PT;ipt++){
           //if((pt[iParticle]>minPtCut[ipt]&&pt[iParticle]<=maxPtCut[ipt])){
             //ptBin=ipt;
           //}
         //}

         if(eta[iParticle]>0){
           histTempEP->Fill(cos(2*(phi[iParticle] - eventPlaneMinus)));
           histTempPP->Fill(cos(2*(phi[iParticle] - Psipart)));
          }
         if(eta[iParticle]<0){
           histTempEP->Fill(cos(2*(phi[iParticle] - eventPlanePlus)));
           histTempPP->Fill(cos(2*(phi[iParticle] - Psipart)));
          }
        
       } // end of the particle loop
       histV2EP[MultIndex]->Fill(histTempEP->GetMean());
       histV2PP[MultIndex]->Fill(histTempPP->GetMean());
       cout<<eventPlaneMinus<<"   "<<eventPlanePlus<<"   "<<Psipart<<endl;


      } // end of the second event loop

       
      ofstream output_nmultv2EP;
      ofstream output_nmultv2PP;
      output_nmultv2EP.open("output_nmultv2EP.txt");
      output_nmultv2PP.open("output_nmultv2PP.txt");
      Float_t error;
      for(int i=0; i<NB_SLICE_PT; i++){     
       
         error = sqrt(pow((histV2EP[i]->GetMeanError()/(histEventPlaneRes[i]->GetMean())),2)+ pow((histV2EP[i]->GetMean()*histEventPlaneRes[i]->GetMeanError()/(pow((histEventPlaneRes[i]->GetMean()) ,2))),2));
        cout<<histMult[i]->GetMean()<<"   "<<histV2EP[i]->GetMean()/sqrt(fabs(histEventPlaneRes[i]->GetMean()))<<"   "<<error<<endl;
        output_nmultv2EP<<histMult[i]->GetMean()<<"   "<<histV2EP[i]->GetMean()/sqrt(fabs(histEventPlaneRes[i]->GetMean()))<<"   "<<error<<"   "<<histEventPlaneRes[i]->GetMean()<<"   "<<histEventPlaneRes[i]->GetMeanError()<<endl;
     
       output_nmultv2PP<<histMult[i]->GetMean()<<"   "<<histV2PP[i]->GetMean()<<"   "<<histV2PP[i]->GetMeanError()<<endl;
       } 

      //TCanvas *c1 = new TCanvas("c1","c1",1,1,650,550);
      //hist2Dx_y->SetXTitle("x (fm)");
      //hist2Dx_y->SetYTitle("y (fm)"); 
      //hist2Dx_y->GetXaxis()->CenterTitle(1);
      //hist2Dx_y->GetYaxis()->CenterTitle(1);     
      //hist2Dx_y->Draw("box");
      //c1->SaveAs("plot_hist2Dx_y.pdf");

}
