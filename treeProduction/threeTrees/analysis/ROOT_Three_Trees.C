#include "TFile.h"
#include "TTree.h"
#include "TVector3.h"
#include <iostream>
using namespace std;
void ROOT_Three_Trees(){
    
    int nEvent = 0;
    int nMultiplicity, nPartA, nPartB, pid;
    float b, tmp, px, py, pz, m, x, y, z, t;
    int savedMultiplicity;
    
    const int maxMultiplicity = 50000;
    Int_t nMultiplicityTree, nPartTree;
    Int_t pidTree[maxMultiplicity];
    Float_t bTree;
    Float_t ptTree[maxMultiplicity], etaTree[maxMultiplicity], phiTree[maxMultiplicity];
    
    const string inputFileName = "/scratch/prichaew/models/slurmcc2/jb0/ana/ampt.dat";
    ifstream inputFile;
    inputFile.open(inputFileName);
    
    TFile *hadronTreeFile = new TFile("tree_three.root", "RECREATE");
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
    
    //hadronTree->Write();

    cout<<"Done for hadron tree!"<<endl;
    cout<<"Number of events saved to the hadron tree is :" <<nEvent<<endl;
    cout<<"The input file is : "<<inputFileName<<endl;
     
    cout<<endl<<"Start working on the participant tree"<<endl;
    //Including positions of participants
    int nEvent2 = 0;
    const int maxNucleons = 208;
    int nNucleonsProjectile, nNucleonsTarget;
    float xProjectile[maxNucleons];
    float yProjectile[maxNucleons];
    int statusProjectile[maxNucleons];
    float xTarget[maxNucleons];
    float yTarget[maxNucleons];
    int statusTarget[maxNucleons];

    Int_t nNucleonsProjectileTree, nNucleonsTargetTree;
    Float_t xProjectileTree[maxNucleons];
    Float_t yProjectileTree[maxNucleons];
    Int_t statusProjectileTree[maxNucleons];
    Float_t xTargetTree[maxNucleons];
    Float_t yTargetTree[maxNucleons];
    Int_t statusTargetTree[maxNucleons];

    const string inputFileName2 = "/scratch/prichaew/models/slurmcc2/jb0/ana/npart-xy.dat";
    ifstream inputFile2;
    inputFile2.open(inputFileName2);

    TTree *participantTree = new TTree("participantTree", "Tree with initial nucleon positions from AMPT");
    participantTree->Branch("nNucleonsProjectileTree", &nNucleonsProjectileTree, "nNucleonsProjectileTree/I");
    participantTree->Branch("xProjectileTree", &xProjectileTree, "xProjectileTree[nNucleonsProjectileTree]/F");
    participantTree->Branch("yProjectileTree", &yProjectileTree, "yProjectileTree[nNucleonsProjectileTree]/F");
    participantTree->Branch("statusProjectileTree", &statusProjectileTree, "statusProjectileTree[nNucleonsProjectileTree]/I");
    participantTree->Branch("nNucleonsTargetTree", &nNucleonsTargetTree, "nNucleonsTargetTree/I");
    participantTree->Branch("xTargetTree", &xTargetTree, "xTargetTree[nNucleonsTargetTree]/F");
    participantTree->Branch("yTargetTree", &yTargetTree, "yTargetTree[nNucleonsTargetTree]/F");
    participantTree->Branch("statusTargetTree", &statusTargetTree, "statusTargetTree[nNucleonsTargetTree]/I");

    while (inputFile2>>nEvent2){
        inputFile2>>tmp;
        inputFile2>>nNucleonsProjectileTree; 
        inputFile2>>nNucleonsTargetTree;
        inputFile2>>tmp;
        for(int i=0; i<nNucleonsProjectileTree; i++){
            inputFile2>>xProjectileTree[i]; 
            inputFile2>>yProjectileTree[i]; 
            inputFile2>>tmp;
            inputFile2>>statusProjectileTree[i]; 
            inputFile2>>tmp;
            inputFile2>>tmp;
            inputFile2>>tmp;
        }
        for(int i=0; i<nNucleonsTargetTree; i++){
            inputFile2>>xTargetTree[i];
            inputFile2>>yTargetTree[i];
            inputFile2>>tmp;
            inputFile2>>statusTargetTree[i];
            inputFile2>>tmp;
            inputFile2>>tmp;
            inputFile2>>tmp;
        }        
        
        participantTree->Fill();
        
        if(nEvent2%1==0) cout<<"Processed "<<nEvent2<<" events"<<endl;
    }
    inputFile2.close();

    //participantTree->Write();
                    
    cout<<"Number of events saved to the participant tree is :" <<nEvent2<<endl;
    cout<<"The input file is : "<<inputFileName2<<endl;
    cout<<"Now working on partonTree"<<endl;


    int nEvent3 = 0;
    const int maxnPartons = 100000;
    int nParton;
    int Partonpid[maxnPartons];
    float xParton[maxnPartons];
    float yParton[maxnPartons];

    Int_t nPartonTree;
    Int_t PartonpidTree[maxnPartons];    
    Float_t xPartonTree[maxnPartons];
    Float_t  yPartonTree[maxnPartons];
    
     
    const string inputFileName3 = "/scratch/prichaew/models/slurmcc2/jb0/ana/parton-initial-afterPropagation.dat";
    ifstream inputFile3;
    inputFile3.open(inputFileName3);

    TTree *partonTree = new TTree("partonTree", "Tree with parton information that enter parton cascade from AMPT");
    partonTree->Branch("nPartonTree", &nPartonTree, "nPartonTree/I");
    partonTree->Branch("PartonpidTree", &PartonpidTree, "PartonpidTree[nPartonTree]/I");
    partonTree->Branch("xPartonTree", &xPartonTree, "xPartonTree[nPartonTree]/F");
    partonTree->Branch("yPartonTree", &yPartonTree, "yPartonTree[nPartonTree]/F");

    while (inputFile3>>nEvent3){
        inputFile3>>tmp;
        inputFile3>>nPartonTree;
        inputFile3>>tmp;
        inputFile3>>tmp;
        inputFile3>>tmp;
        inputFile3>>tmp;
        for(int i=0; i<nPartonTree; i++){
            inputFile3>>PartonpidTree[i];
            inputFile3>>tmp;
            inputFile3>>tmp;
            inputFile3>>tmp;
            inputFile3>>tmp;
            inputFile3>>xPartonTree[i];
            inputFile3>>yPartonTree[i];
            inputFile3>>tmp;
            inputFile3>>tmp;
            inputFile3>>tmp;
            inputFile3>>tmp;
            inputFile3>>tmp;
        }

    partonTree->Fill();      

    if(nEvent3%1==0) cout<<"Processed "<<nEvent3<<endl;
    }
    inputFile3.close();

    //partonTree->Write();

    hadronTreeFile->Write();

    cout<<"Number of events saved to the parton tree is :" <<nEvent3<<endl;
    cout<<"The input file is : "<<inputFileName3<<endl;

    cout<<"Done!"<<endl;

    
}
//
//  
//
//  Created by Sofia Panomitros on 7/1/19.
//
//  Updated by Shengquan and Everett in summer 2020
//
