      program fortran_newtons

      REAL :: x,v2,Psi,phi0,functionPhi
      REAL functionPhiF
      REAL functionPhiDeri

      x = 0.3
      v2 = 0.1
      Psi = 1.5
      phi0 = 3.0
      call functionPhiEval(x, v2, Psi, phi0, functionPhi)
      print *, functionPhi
      print *, 'function : ', functionPhiF(x, v2, Psi, phi0)
      end

      ! phi = phi0 - v2 * sin[2(phi-Psi)]
      ! we need y = x + v2 * sin[2(x-Psi)] - phi0 = 0, where x is phi.
      subroutine functionPhiEval(x, v2, Psi, phi0, functionPhi)
        implicit none
        real, intent(IN)  :: x, v2, Psi, phi0
        real, intent(OUT) :: functionPhi

        functionPhi = ( x + v2*SIN(2*(x-Psi)) - phi0 ) 

      end subroutine functionPhiEval

      FUNCTION functionPhiF(x, v2, Psi, phi0)
      REAL x, v2, Psi, phi0
      functionPhiF = ( x + v2*SIN(2*(x-Psi)) - phi0 )
      RETURN
      END FUNCTION

      FUNCTION functionPhiDeri(x, v2, Psi)
      REAL x, v2, Psi
      functionPhiDeri = ( 1 + v2*cos(2*(x-Psi))*2 )
      RETURN
      END FUNCTION




