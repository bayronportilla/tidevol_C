typedef struct parameters{
  double e;
  int    q;
}vpar;

double integrand(double E, void *p){

  int n = -3;
  int m = 2; 
    
  vpar params = *(vpar*)p;
  double e = params.e;
  int q = params.q;
  
  double f = 0.5/M_PI * pow((1.0-e*cos(E)),n)*cos( 2*m*atan(pow((1.0+e)/(1.0-e),0.5)*tan(0.5*E)) - (2+q)*(E-e*sin(E)) )*(1.0-e*cos(E));

  return f;
}


double hansen(double e, int q){
  int n_interval = 1000;
  gsl_integration_workspace * w = gsl_integration_workspace_alloc(n_interval);
  double result, error;
  gsl_function F;
  struct parameters params; 
  params.e = e;
  params.q = q;
    
  F.function = &integrand;
  F.params = &params;

  gsl_integration_qag(&F,0.0,2*M_PI,1e-7,1e-7,n_interval,1,w,&result,&error);

  gsl_integration_workspace_free(w);
  return result;
}

