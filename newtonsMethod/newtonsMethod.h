// phi = phi0 - v2 * sin[2(phi-Psi)]
// we need y = x + v2 * sin[2(x-Psi)] - phi0 = 0, where x is phi.



double func(double x, double v2, double Psi, double phi0){
 return ( x + v2*sin(2*(x-Psi)) - phi0 ); 
}

// y' = 1 + v2 * cos[2(x-Psi)]*2
double derivativeFunc(double x, double v2, double Psi){
 return ( 1 + v2*cos(2*(x-Psi))*2 );
}

double newtonMethod(double x, double v2, double Psi, double phi0){
  double ratio = func(x, v2, Psi, phi0) / derivativeFunc(x, v2, Psi);
    while (fabs(ratio) > 0.0000001){ 
        ratio = func(x, v2, Psi, phi0)/derivativeFunc(x, v2, Psi); 
//        cout<<"### Ratio = ###"<<ratio<<endl;  
        // x(i+1) = x(i) - f(x) / f'(x)   
        x = x - ratio; 
    } 
    //cout << "The value of the root is : " << x;   
    return x;
}

