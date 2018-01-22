#include "allvars.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_integration.h>
#include "hansen.h"
#include <gsl/gsl_sf_gamma.h>
#include "Torques.h"
#include "EOM.h"

int main (void){

  Inpar st;
  st = params();
  FetchInfo(st);

  /*  
  FILE *fp;
  char src[100];
  char dest[100];
  char name_files[100];
  strcpy(src,st.sim_name);
  strcpy(dest,".dat");
  strcpy(name_files,strcat(src,dest));
  fp = fopen(name_files,"w");
  float i;
  for(i=1.995;i<2.005;i+=0.000001){
    //printf("%e \n",tidal_torque(i*n)/C *pow(365.25*86400,2));
    fprintf(fp,"%1.5f     %e\n", i, tidal_torque(i*n(st.m_s,st.m_p,st.a),st.a,st.e,st)/Cfactor(st.m_p,st.R_p,st.gyr_rad) * (YEARS*YEARS/(st.uT*st.uT)) );
  }
  */
  

  
  //gsl_odeiv2_driver_alloc_y_new(const gsl_odeiv2_system * sys,
  //                              const gsl_odeiv2_step_type * T,
  //                              const double hstart,
  //                              const double epsabs,
  //                              const double epsrel)

  
  ////////////////////////////////////////////////////////////
  // This is the only line must be modified by the user
  //
  const gsl_odeiv2_step_type *T = gsl_odeiv2_step_rk2;
  //
  ////////////////////////////////////////////////////////////


  gsl_odeiv2_system sys = { func, NULL, 2, &st}; // Define sistema de ecuaciones
  gsl_odeiv2_driver *d = gsl_odeiv2_driver_alloc_y_new (&sys, T, 1.0e-3, 1e-8, 1e-8);

  
  double n_ini = n(st.m_p,st.m_s,st.a);
  double y[2] = { st.theta_ini, st.res_ini*n_ini}; // y[number of entries of the array] = {}
  
   int i, s;
   double t = st.t_ini;
   double progress;

   
   FILE *fp;
   char src[100];
   char dest[100];
   char name_files[100];
   strcpy(src,st.sim_name);
   strcpy(dest,".dat");
   strcpy(name_files,strcat(src,dest));
   fp = fopen(name_files,"w");
   double ti = t;

   double Omega_ini = st.res_ini*n_ini;
   printf("%e \n",dtheta_dt(st.theta_ini,Omega_ini,st.a,st.e,1.0,st));
   printf("%e \n",dOmega_dt(st.theta_ini,Omega_ini,st.a,st.e,1.0,st));
  
   
   while(t<st.t_end){

     s = gsl_odeiv2_driver_apply(d, &t, ti, y);
     if (s != GSL_SUCCESS){
       printf ("error: driver returned %d\n", s);
       break;
     }
     ti += st.h_output;     
     
     progress = (t/st.t_end)*100.0;
     printf("Progress: %d per cent \n",(int)progress);
     
     if ( (int)progress%10 == 0){
       printf("Progress: %d per cent \n",(int)progress);
     }
     

     fprintf(fp,"%.5e %.5e %.5e %.5e %.5e \n",
	     t,y[0],y[1],st.a,st.e);
   }
   
   gsl_odeiv2_driver_free (d);
   fclose(fp);
  
   
   return 0;
   
}

