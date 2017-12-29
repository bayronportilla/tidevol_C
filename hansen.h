#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_integration.h>

struct param_type{
  double e;
  int    q;
};


double f(double E, void * params);


double hansen(double e, int q){
  
  gsl_integration_workspace * w = gsl_integration_workspace_alloc(1000);
  double result, error;
   
  gsl_function F;
  struct param_type params; //= {e,q};
  params.e = e;
  params.q = q;
    
  F.function = &f;
  F.params = &params;

  gsl_integration_qags (&F,0,2*M_PI,0,1e-7,1000,w,&result,&error);

  return result;
}

double f(double E, void * p){

  int n = -3;
  int m = 2; 
  
  struct param_type  * params = (struct param_type *) p;
  double e = (params->e);
  int    q = (params->q);
  
  //double alpha = *(double *) params;
  
  //double e = *(double *) params.eccentricity;
  //int    q = *(double *) params.q;
  double f = 0.5/M_PI * pow((1.0-e*cos(E)),n)*cos( 2*m*atan(pow((1.0+e)/(1.0-e),0.5)*tan(0.5*E)) - (2+q)*(E-e*sin(E)) )*(1.0-e*cos(E));
  return f;
}
