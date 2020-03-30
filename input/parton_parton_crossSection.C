// the output is not mb, but 0.1*mb, therefore, output of
// 0.3 means sigma = 3mb !
void parton_parton_crossSection(){

const int nC=5;

double fragA[nC]={2.2, 2.2, 0.5, 0.55, 0.5};
double fragB[nC]={0.5, 0.5, 0.9, 0.15, 0.9};
double alphaS[nC]={0.47, 0.47, 0.33, 0.47140452, 0.47140452};
double muon[nC]={1.8, 2.3, 3.2, 3.2264, 3.2264};
double sigma[nC]={0.0, 0.0, 0.0, 0.0, 0.0};
for(int i=0; i<nC; i++){
sigma[i]=9*3.14159*alphaS[i]*alphaS[i]/(2*muon[i]*muon[i]);
cout<<"sigma["<<i<<"] = "<<sigma[i]<<endl;
} 

// 1) and 2) are from very early RHIC study.
// 3) and 4) are favored from recent study at LHC
// 5) is from the CMS AMPT default setup, good for pp/pPb with 3mb
// numbers from: https://arxiv.org/pdf/1101.2231.pdf [using 3), which is 1.5mb ]
// equation is from: https://arxiv.org/pdf/nucl-th/0411110.pdf
// dAu/He3Au paper using 1.5mb: https://arxiv.org/pdf/1501.06880.pdf
// ee collision using 3.7mb: https://arxiv.org/pdf/1707.02307.pdf
// pPb/PbPb peripheral paper using 3mb: https://arxiv.org/pdf/1406.2804.pdf
// ArAr paper using 1.5mb: https://arxiv.org/pdf/1904.10415.pdf
// OO paper using 3mb: https://arxiv.org/pdf/1812.08096.pdf

// from https://arxiv.org/pdf/1403.6321.pdf:
// a=0.5, b=0.9 works well for pp (and default in HIJING)
// not work for dN/deta in PbPb at SPS, so tuned to a=2.2, b=0.5
// with RHIC top energy AuAu, fitting low pT data get a=0.55, b=0.15
// with LHC, fitting ALICE PbPbdata gets a=0.30 and b=0.15
// In conclusion, for pp collision at LHC energy, let's use a=0.5 and b=0.9

// output:
// sigma[0] = 0.963857
// sigma[1] = 0.59034
// sigma[2] = 0.150345
// sigma[3] = 0.301796
// sigma[4] = 0.301796

// unit analysis in the equation: sigma=9*pi*alpha*alpha/muon/muon
// alpha unit=1, muon unit is fm-1; 1mb=10^(-31)m^2=0.1*(fm)^2=>
// (fm)^2=10*1mb, therefore, sigma=9*3.14*XXXXX*10*1mb,
// which is why we have the factor 10 come out.


}

