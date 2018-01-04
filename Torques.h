double tidal_torque(double Omega, double a, double e, Inpar params){

  double sum_tidal;
  double omega, chi;
  double Im, Re;
  double mean_motion = n(params.m_s,params.m_p,params.a);
  double tau_M = params.tau_M;
  double tau_A;
  double alpha = params.alpha;
  double R_p = params.R_p;
  double mu = params.mu;
  double m_p = params.m_p;
  double m_s = params.m_s;
  
  int dolim = -1;
  int uplim = 8;
  int q;

  sum_tidal = 0.0;
  
  for (q=dolim; q<uplim; q++){
    omega = (2.0+q)*mean_motion-2.0*Omega;
    chi   = fabs(omega);
    tau_A = (100.0*exp(-chi/(0.2)) + 1.0)*tau_M ;
    
    Re         = 1.0 + pow(chi*tau_A,-alpha)*cos(0.5*alpha*M_PI)*gsl_sf_gamma(alpha+1.0);   
    Im         = -pow(chi*tau_M,-1.0) - pow(chi*tau_A,-alpha)*sin(0.5*alpha*M_PI)*gsl_sf_gamma(alpha+1.0);
    sum_tidal += pow(hansen(e,q),2)*( -1.5*A_l(R_p,mu,m_p,2)*Im*sign(omega)/( pow(Re + A_l(R_p,mu,m_p,2),2) + Im*Im) );

  }
  
  return 1.5*G*m_s*m_s*pow(R_p,5)*pow(a,-6)*sum_tidal;
}



double triaxial_torque(double theta, double a, double e, Inpar params, double t){
  double BmA,f,M,E,r;
  M = n(params.m_s,params.m_p,a)*t;
  E = solveKepler(e,M);
  r = a*(1.0-e*cos(E));
  f = 2.0*atan(pow((1.0+e)/(1.0-e),0.5)*tan(0.5*E));
  BmA = params.BmAC * Cfactor(params.m_p,params.R_p,params.gyr_rad);
  
  return 1.5*(BmA)*pow(n(params.m_s,params.m_p,a),2)*pow(a/r,3)*sin(2.0*(theta-f));
  
}


