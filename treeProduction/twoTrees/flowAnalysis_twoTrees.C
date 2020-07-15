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
void flowAnalysis_twoTrees(){

     long nEvt, nEvtProcess; 

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

     double eventPlanePlus, eventPlaneMinus;

     TH1D *histEventPlaneRes = new TH1D("histEventPlaneRes", "", 200,-1,1);

     const int NB_SLICE_PT = 15;
     double minPtCut[NB_SLICE_PT] = {0.2,0.4,0.6,0.8,1.1,1.4,1.75,2.2,2.75,3.45,4.2,5.05,6.0,7.2,8.5};
     double maxPtCut[NB_SLICE_PT] = {0.4,0.6,0.8,1.1,1.4,1.75,2.2,2.75,3.45,4.2,5.05,6.0,7.2,8.5,1000}; //15 bins
    
     TH1D *histV2Obs[NB_SLICE_PT];
     TH1D *histV2Corrected[NB_SLICE_PT];
     for(int i=0; i<NB_SLICE_PT; i++){
       histV2Obs[i] = new TH1D(Form("histV2Obs_%d",i), "", 200,-1,1);
       histV2Corrected[i] = new TH1D(Form("histV2Corrected_%d",i), "", 200,-1,1);
     }

     TH2D *hist2Dx_y = new TH2D("hist2Dx_y","Nucleon position x vs y", 200, -10,10, 200,-10,10);

     TFile inFile("./trees_hadrons_participants_ampt_jb0_cuts.root", "read");
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

       if(ne==0){ //The first event
         cout<<"nNucleonsProjectile = "<<nNucleonsProjectile<<endl;
         for(int i=0; i<nNucleonsProjectile; i++){
           hist2Dx_y->Fill(xProjectile[i], yProjectile[i]);
           cout<<"x = "<<xProjectile[i]<<",  y = "<<yProjectile[i]<<endl;
         }
         cout<<"nNucleonsTarget = "<<nNucleonsTarget<<endl;
         for(int i=0; i<nNucleonsTarget; i++){
           hist2Dx_y->Fill(xTarget[i], yTarget[i]);
         }
       }
    
       if(nParticle<400 || nParticle>500) continue;

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
       histEventPlaneRes->Fill(cos(2*(eventPlanePlus - eventPlaneMinus)));

      } // end of the first event loop
      cout<<"Event Plane resolution = "<<sqrt(histEventPlaneRes->GetMean())<<endl;

      //histPt->Draw();
      //hist2DPtVsEta->Draw("colz");

     // starting the second event loop
     for(long ne=0; ne<nEvt; ne++)
     {
       if(ne%2000==0)  cout<<"Have run "<<ne<<" of the total "<<nEvt<<" events; "<<endl;
       t1->GetEntry(ne);

       histQSinPlus->Reset();
       histQSinMinus->Reset();
       histQCosPlus->Reset();
       histQCosMinus->Reset();

       //if(nParticle<120 || nParticle>=150) continue;
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

         int ptBin=-1;
         for(int ipt=0;ipt<NB_SLICE_PT;ipt++){
           if((pt[iParticle]>minPtCut[ipt]&&pt[iParticle]<=maxPtCut[ipt])){
             ptBin=ipt;
           }
         }

         if(eta[iParticle]>0){
           histV2Obs[ptBin]->Fill(cos(2*(phi[iParticle] - eventPlaneMinus)));
           histV2Corrected[ptBin]->Fill(cos(2*(phi[iParticle] - eventPlaneMinus)));
         }
         if(eta[iParticle]<0){
           histV2Obs[ptBin]->Fill(cos(2*(phi[iParticle] - eventPlanePlus)));
           histV2Corrected[ptBin]->Fill(cos(2*(phi[iParticle] - eventPlanePlus)));
         }

       } // end of the particle loop

      } // end of the second event loop

       
      ofstream output_v2;
      output_v2.open("output_v2.txt");
      for(int i=0; i<NB_SLICE_PT; i++){     

        cout<<(minPtCut[i]+maxPtCut[i])/2<<"   "<<histV2Corrected[i]->GetMean()/sqrt(fabs(histEventPlaneRes->GetMean()))<<"   "<<histV2Corrected[i]->GetMeanError()<<endl;
        output_v2<<(minPtCut[i]+maxPtCut[i])/2<<"   "<<histV2Corrected[i]->GetMean()/sqrt(fabs(histEventPlaneRes->GetMean()))<<"   "<<histV2Corrected[i]->GetMeanError()<<endl;
      } 

      TCanvas *c1 = new TCanvas("c1","c1",1,1,650,550);
      hist2Dx_y->SetXTitle("x (fm)");
      hist2Dx_y->SetYTitle("y (fm)"); 
      hist2Dx_y->GetXaxis()->CenterTitle(1);
      hist2Dx_y->GetYaxis()->CenterTitle(1);     
      hist2Dx_y->Draw("box");
      c1->SaveAs("plot_hist2Dx_y.pdf");

}


