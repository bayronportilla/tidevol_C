double dtheta_dt(double theta, double Omega, double a, double e, double t, Inpar params){
  return Omega;
}

double dOmega_dt(double theta, double Omega, double a, double e, double t, Inpar params){
  double m_p     = params.m_p;
  double R_p     = params.R_p;
  double gyr_rad = params.gyr_rad;
  
  return (tidal_torque(Omega,a,e,params) + triaxial_torque(theta,a,e,t,params)) / Cfactor(m_p,R_p,gyr_rad);

}


int func (double t, const double y[], double f[], void *params){
  (void)(t);

  Inpar parameters = *(Inpar *) params;
  double a = parameters.a;
  double e = parameters.e;

  double theta = y[0];
  double Omega = y[1];

  f[0] = dtheta_dt(theta,Omega,a,e,t,parameters);
  f[1] = dOmega_dt(theta,Omega,a,e,t,parameters);
  
  return GSL_SUCCESS;

}
