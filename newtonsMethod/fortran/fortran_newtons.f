      program fortran_newtons

      REAL :: x,v2,Psi,phi0
      REAL functionPhi
      REAL functionPhiDeri
      REAL functionNewtonsMethod

      x = 0.3
      v2 = 0.1
      Psi = 1.5
      phi0 = 3.0

      print *, 'function : ', functionPhi(x, v2, Psi, phi0)
      print *, 'functionDeri : ', functionPhiDeri(x, v2, Psi)

      ! need to implement the better guess here
 
      print *, 'newtonsMethod : ', functionNewtonsMethod(x, v2, 
     *                             Psi, phi0)
      end

      ! phi = phi0 - v2 * sin[2(phi-Psi)]
      ! we need y = x + v2 * sin[2(x-Psi)] - phi0 = 0, where x is phi.
      FUNCTION functionPhi(x, v2, Psi, phi0)
      REAL x, v2, Psi, phi0
      functionPhi = ( x + v2*SIN(2*(x-Psi)) - phi0 )
      RETURN
      END FUNCTION

      ! y' = 1 + v2 * cos[2(x-Psi)]*2
      FUNCTION functionPhiDeri(x, v2, Psi)
      REAL x, v2, Psi
      functionPhiDeri = ( 1 + v2*COS(2*(x-Psi))*2 )
      RETURN
      END FUNCTION

      FUNCTION functionNewtonsMethod(x, v2, Psi, phi0)
      REAL x, v2, Psi, phi0
      REAL ratioFuncDeri
      ratioFuncDeri = functionPhi(x, v2, Psi, phi0) 
     *                / functionPhiDeri(x, v2, Psi)
      DO WHILE (ABS(ratioFuncDeri) > 0.0000001) 
         ratioFuncDeri = functionPhi(x, v2, Psi, phi0) 
     *                   / functionPhiDeri(x, v2, Psi)
         x = x - ratioFuncDeri
      END DO

      functionNewtonsMethod = x
      RETURN
      END FUNCTION
    


