void testFile(){

  TFile *af = new TFile("ttree_test.root","recreate");

  TTree *trb = new TTree("trb","trb"); // disk resident
  //gROOT->cd();
  TTree *tr = new TTree("tr","tr"); // memory resident
  
  double x1,y1,z1;
  double x1b,y1b,z1b;
  int ii,jj;
  tr->Branch("x1",&x1,"x1/D");
  tr->Branch("y1",&y1,"y1/D");
  tr->Branch("z1",&z1,"z1/D");

  const int nV = 10;
  double xyzvalues[nV] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
  
  trb->Branch("x1b",&x1b,"x1b/D");
  trb->Branch("y1b",&y1b,"z1b/D");
  trb->Branch("z1b",&z1b,"z1b/D");
  
  for(jj=0;jj<nV;jj++){
      if(jj%2==0) cout<<"jj = "<<jj<<endl;
      x1=xyzvalues[jj]+1; 
      y1=xyzvalues[jj]+2; 
      z1=xyzvalues[jj]+3; 
      tr->Fill();
  }
  for(jj=0;jj<nV;jj++){
      if(jj%2==0) cout<<"jj = "<<jj<<endl;
      x1b=-1*xyzvalues[jj]-1;
      y1b=-1*xyzvalues[jj]-2;
      z1b=-1*xyzvalues[jj]-3;
      trb->Fill();
  }

  af->Write();
  //delete af; // automatically deletes "trb", too
}

