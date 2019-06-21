void parton_parton_crossSection(){

const int nC=4;

double fragA[nC]={2.2, 2.2, 0.5, 0.55};
double fragB[nC]={0.5, 0.5, 0.9, 0.15};
double alphaS[nC]={0.47, 0.47, 0.33, 0.47140452};
double muon[nC]={1.8, 2.3, 3.2, 3.2264};
double sigma[nC]={0.0, 0.0, 0.0, 0.0};
for(int i=0; i<nC; i++){
sigma[i]=9*3.14159*alphaS[i]*alphaS[i]/(2*muon[i]*muon[i]);
cout<<"sigma["<<i<<"] = "<<sigma[i]<<endl;
} 

// 1) and 2) are from very early RHIC study.
// 3) and 4) are favored from recent study at LHC
// numbers from: https://arxiv.org/pdf/1101.2231.pdf [using 3), which is 1.5mb ]
// equation is from: https://arxiv.org/pdf/nucl-th/0411110.pdf
// dAu/He3Au paper using 1.5mb: https://arxiv.org/pdf/1501.06880.pdf
// ee collision using 3.7mb: https://arxiv.org/pdf/1707.02307.pdf
// pPb/PbPb peripheral paper using 3mb: https://arxiv.org/pdf/1406.2804.pdf
// ArAr paper using 1.5mb: https://arxiv.org/pdf/1904.10415.pdf
// OO paper using 3mb: https://arxiv.org/pdf/1812.08096.pdf


}

