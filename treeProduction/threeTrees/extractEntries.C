#include <stdio.h>
#include <complex>
#include <iostream>
#include "TF1.h"
#include "TFile.h"
#include <TFile.h>
#include "TH1.h"
#include "TH2.h"
#include "TH1F.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TTree.h"
#include <TMath.h>
using namespace std; 
void extractEntries(const char* InputFile = "/store/user/prichaew/slurmcc2/jb0/trees_hadrons_participants_partons_jb0_0.root"){

     TFile *inFile;
     inFile = new TFile(InputFile);
     TTree *t1 = (TTree*)inFile->Get("hadronTree");
     TTree *t2 = (TTree*)inFile->Get("participantTree");
     TTree *t3 = (TTree*)inFile->Get("partonTree");
     
     int nt1 = t1->GetEntries();
     int nt2 = t2->GetEntries();
     int nt3 = t3->GetEntries();

     if(nt1 != nt2 || nt1 != nt3)
     //if(nt1 == nt2 && nt1 == nt3)
       //cout<<"t1: "<<t1->GetEntries()<<" ;  t2: "<<t2->GetEntries()<<" ;  t3: "<<t3->GetEntries()<<"   ; filename = "<<InputFile<<endl;
       cout<<InputFile<<endl;

}

