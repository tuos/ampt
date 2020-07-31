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
void get_diff(const char* inputFileName){

     int nhadron, nparton, diff;     

     //ifstream input_file;
     //input_file.open("input_file.txt");
     //string tmp;
     //input_file>>tmp;
     //const char* inputFileName = tmp;
     //input_file>>inputFileName;

     //const char* inputFileName = "/store/user/prichaew/slurmcc2/jb0/trees_hadrons_participants_partons_jb0_2.root"; 

     //ofstream diff_file;
     //diff_file.open("diff_file.txt", "write");

     TFile f(inputFileName, "read");
     TTree *t1 = (TTree*)f.Get("hadronTree");
     TTree *t2 = (TTree*)f.Get("partonTree");
     nhadron = t1->GetEntries();
     nparton = t2->GetEntries();
     diff = nparton - nhadron;
    

     if(diff == 0){ 
     cout<<inputFileName<<" ";
     }

}

