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
void centralityTree(){

     long nEvt;


     const int nCentralityBin = 100;
     Float_t boundariesBin[nCentralityBin+1] = {0, 1.3729, 1.741, 2.2099, 2.6421, 2.8562, 3.3635, 3.7362, 4.1099, 4.2531, 4.4262, 4.6013, 4.7966, 5.0323, 5.204, 5.4877, 5.6846, 5.8435, 6.0615, 6.2314, 6.3905, 6.6472, 6.8139, 7.0209, 7.1682, 7.4042, 7.5862, 7.7714, 7.9128, 8.0233, 8.1281, 8.2955, 8.4097, 8.5574, 8.7076, 8.7941, 8.9603, 9.0732, 9.1899, 9.368, 9.4944, 9.5966, 9.7297, 9.8263, 9.9763, 10.1016, 10.1974, 10.2881, 10.4453, 10.5936, 10.721, 10.8474, 10.9632, 11.1028, 11.1464, 11.2218, 11.3631, 11.484, 11.5987, 11.678, 11.7674, 11.8259, 11.8936, 11.9457, 12.0305, 12.0886, 12.1306, 12.2455, 12.3373, 12.4371, 12.4978, 12.6049, 12.6563, 12.7315, 12.8183, 12.8779, 13.0076, 13.0803, 13.1648, 13.255, 13.3109, 13.3947, 13.5224, 13.6071, 13.6977, 13.7739, 13.8629, 13.9704, 14.054, 14.1341, 14.2401, 14.3161, 14.3664, 14.4139, 14.4955, 14.5993, 14.6663, 14.7744, 14.8444, 14.931, 14.9944};

     Int_t centralityBinTree;
     Float_t b;

     TFile oldFile("../slurmjob_merged_tree.root", "read");
     TTree *t1 = (TTree*)oldFile.Get("hadronTree");
     t1->SetBranchAddress("bTree", &b);
     nEvt=t1->GetEntries();

     TFile *newFile = new TFile("slurmjob_merged_tree_centrality.root","recreate");
     cout<<"Making a clone of the tree ... ..."<<endl;
     TTree *newTree = t1->CloneTree();

     auto newBranch = newTree->Branch("centralityBinTree", &centralityBinTree, "centralityBinTree/I");
     for(long ne=0; ne<nEvt; ne++)
     {
       if(ne%2000==0)  cout<<"Have run "<<ne<<" of the total "<<nEvt<<" events; "<<endl;
       t1->GetEntry(ne);

       for(int i=0; i<nCentralityBin; i++){
         if(b>boundariesBin[i] && b<=boundariesBin[i+1]){
           centralityBinTree = i;
         }
       }

       newBranch->Fill();
       //newTree->Fill();

     } // end of the first event loop

  newTree->Write();
  newFile->Write();

       
}


