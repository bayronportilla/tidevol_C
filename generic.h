double A_l(double R, double rigidity, double M_p, int l){
  return 4.0*M_PI*pow(R,4)*rigidity*(2.0*l*l + 4.0*l + 3.0)/(3.0*G*l*pow(M_p,2));
}

double n(double m_1, double m_2, double a){
  return pow(G*(m_1 + m_2)/(a*a*a),0.5);
}

int sign(double x){
  if(x > 0.0){
    return 1;
  }
  else if(x<0.0){
    return -1;
  }
  else{
    return 0;
  }
}


/* ----------------------------------------------------------------------
SOLVE KEPLER EQUATION
Source:
Adapted from http://astro.pas.rochester.edu/~aquillen/ast570/code/kepcart.cpp
supposed to be good to second order in e, from Brouwer+Clemence u0 is
first guess
---------------------------------------------------------------------- */

double solveKepler(double e, double M)
{
  double du,u0,l0;
  du=1.0;
  u0=M+e*sin(M)+0.5*e*e*sin(2.0*M);
  while(fabs(du)>PREC_ECC_ANO){
    l0 = u0 - e*sin(u0);
    du = (M - l0)/(1.0 - e*cos(u0));
    u0 += du;
  }
  return u0;
}
