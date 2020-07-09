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
void centralityBoundaries(){

     long nEvt; 

     Float_t b;
     vector<float> impactPar;

     TChain t1("hadronTree");
     t1.Add("../slurmjob_merged_tree.root");
     t1.SetBranchAddress("bTree", &b);
     nEvt=t1.GetEntries();
     //nEvtProcess=50;
     // first event loop for estimatig the event plane resolution
     for(long ne=0; ne<nEvt; ne++)
     {
       if(ne%2000==0)  cout<<"Have run "<<ne<<" of the total "<<nEvt<<" events; "<<endl;
       t1.GetEntry(ne);
       impactPar.push_back(b);
       
     } // end of the first event loop

     sort(impactPar.begin(), impactPar.end());

     //cout<<"size: "<<impactPar.size()<<endl;

     const int nCentralityBin = 100;
     float binBoundaries[nCentralityBin+1];
     binBoundaries[0] = 0.0; 

     for(int i=0; i< nCentralityBin; i++){
       binBoundaries[i+1] = impactPar[(i+1)*impactPar.size()/nCentralityBin];
       //cout<<"boundaries: "<<binBoundaries[i+1]<<endl;
     }
     binBoundaries[nCentralityBin] = impactPar[impactPar.size()-1];

     ofstream outFile;
     outFile.open("boundaries100Bins.txt");
     for(int i=0; i< nCentralityBin+1; i++){
       cout<<binBoundaries[i]<<", ";
       outFile<<binBoundaries[i]<<", ";
     }
     cout<<endl;
       
}


