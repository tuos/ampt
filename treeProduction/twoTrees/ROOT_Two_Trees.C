#include "TFile.h"
#include "TTree.h"
#include "TVector3.h"
#include <iostream>
using namespace std;
void ROOT_Two_Trees(){
    
    int nEvent = 0;
    int nMultiplicity, nPartA, nPartB, pid;
    float b, tmp, px, py, pz, m, x, y, z, t;
    int savedMultiplicity;
    
    const int maxMultiplicity = 50000;
    Int_t nMultiplicityTree, nPartTree;
    Int_t pidTree[maxMultiplicity];
    Float_t bTree;
    Float_t ptTree[maxMultiplicity], etaTree[maxMultiplicity], phiTree[maxMultiplicity];
    
    const string inputFileName = "/scratch/tuos/models/reu2020/slurm/jb0/ana/ampt.dat";
    ifstream inputFile;
    inputFile.open(inputFileName);
    
    TFile *hadronTreeFile = new TFile("tree_hadrons_ampt_new_jb0_cuts.root", "RECREATE");
    TTree *hadronTree = new TTree("hadronTree", "Tree with hadron output from AMPT");
    hadronTree->Branch("nMultiplicityTree", &nMultiplicityTree, "nMultiplicityTree/I");
    hadronTree->Branch("nPartTree", &nPartTree, "nPartTree/I");
    hadronTree->Branch("bTree", &bTree, "bTree/F");
    hadronTree->Branch("pidTree", &pidTree, "pidTree[nMultiplicityTree]/I");
    hadronTree->Branch("ptTree", &ptTree, "ptTree[nMultiplicityTree]/F");
    hadronTree->Branch("etaTree", &etaTree, "etaTree[nMultiplicityTree]/F");
    hadronTree->Branch("phiTree", &phiTree, "phiTree[nMultiplicityTree]/F");
    
    // Using the TVector3 class for calculating Pt, Phi and Eta
    // https://root.cern.ch/doc/master/TVector3_8cxx_source.html
    while (inputFile>>nEvent){
        //inputFile>>nEvent;
        inputFile>>tmp;
        inputFile>>nMultiplicity; inputFile>>b;
        inputFile>>nPartA; inputFile>>nPartB;
        inputFile>>tmp; inputFile>>tmp;
        inputFile>>tmp; inputFile>>tmp; inputFile>>tmp;
        savedMultiplicity = 0;
        for(int i=0; i<nMultiplicity; i++){
            inputFile>>pid; inputFile>>px;
            inputFile>>py; inputFile>>pz;
            inputFile>>m; inputFile>>x;
            inputFile>>y; inputFile>>z; inputFile>>t;
            TVector3 particles;
            particles.SetXYZ(px, py, pz);
            if(particles.Perp()<0.2) continue;
	    if(particles.PseudoRapidity()<-2.4 || particles.PseudoRapidity()>2.4) continue;
            //if(nEvent==1 && i == 0)  cout<<"pid: "<<pid<<" pz = "<<pz<<endl;
            //if(particles.Phi()==0) cout<<px<<"  "<<py<<"  "<<pz<<endl;
            if(abs(pid)==2212 || abs(pid)==321 || abs(pid)==211){
                pidTree[savedMultiplicity] = pid;
                ptTree[savedMultiplicity] = particles.Perp();
                etaTree[savedMultiplicity] = particles.PseudoRapidity();
                phiTree[savedMultiplicity] = particles.Phi();
                savedMultiplicity++;
            }
        }
        //nMultiplicityTree = nMultiplicity;
        nMultiplicityTree = savedMultiplicity;
        nPartTree = nPartA + nPartB;
        bTree = b;
        
        hadronTree->Fill();
        
        if(nEvent%1==0) cout<<"Processed "<<nEvent<<" events"<<endl;
    }
    inputFile.close();
    
    hadronTree->Write();
    
    cout<<"Done!"<<endl;
    cout<<"Number of events saved to the ROOT tree is :" <<nEvent<<endl;
    cout<<"The input file is : "<<inputFileName<<endl;
    
}
//
//  
//
//  Created by Sofia Panomitros on 7/1/19.
//
//  Updated by Shengquan and Everett in 2020
//

