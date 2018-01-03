#include "allvars.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_integration.h>
#include "hansen.h"
#include <gsl/gsl_sf_gamma.h>
#include "Torques.h"

int main (void){

  Inpar st;
  st = params();

  printf("%s \n",st.sim_name);

  printf("%1.11f\n",solveKepler(0.0,120*InRad));
  
  exit(0);
  double C = st.gyr_rad*st.m_p*st.R_p*st.R_p;
  FetchInfo(st);
  printf("%Le\n",tidal_torque(2.002*st.uT,st.a,st.e,st)/C /(st.uT*st.uT));

  FILE *fp;
  char src[100];
  char dest[100];
  char name_files[100];
  strcpy(src,st.sim_name);
  strcpy(dest,".dat");
  strcpy(name_files,strcat(src,dest));
  fp = fopen(name_files,"w");

    
  float i;
  for(i=1.9996;i<2.0004;i+=0.000001){
    //printf("%e \n",tidal_torque(i*n)/C *pow(365.25*86400,2));
    fprintf(fp,"%1.5f     %Le\n", i, tidal_torque(i*n(st.m_s,st.m_p,st.a),st.a,st.e,st)/C * (YEARS*YEARS/(st.uT*st.uT)) );
  }

  exit(0);  
    //  Inpar st;
    //st = params();

  //gsl_odeiv2_driver_alloc_y_new(const gsl_odeiv2_system * sys,
  //                              const gsl_odeiv2_step_type * T,
  //                              const double hstart,
  //                              const double epsabs,
  //                              const double epsrel)

  /*  
  ////////////////////////////////////////////////////////////
  // This is the only line must be modified by the user
  //
  const gsl_odeiv2_step_type *T = gsl_odeiv2_step_rkf45;
  //
  ////////////////////////////////////////////////////////////


  gsl_odeiv2_system sys = { func, NULL, 16, &st}; // Define sistema de ecuaciones
  gsl_odeiv2_driver *d = gsl_odeiv2_driver_alloc_y_new (&sys, T, 1e-3, 1e-8, 1e-8);


  printf("hola \n");


  double y[16] = { st.a_in, st.a_out, st.e_in, st.e_out, 
		   st.I_in, st.I_out, st.W_in, st.W_out,
		   st.w_in, st.w_out, st.Om_Ax, st.Om_Ay,
		   st.Om_Az, st.Om_Bx, st.Om_By, st.Om_Bz}; // y[number of entries of the array] = {}
  
   int i, s;
   double t = st.t_ini;
   double progress;

   
   FetchInfo(st);
   
   FILE *fp;
   char src[100];
   char dest[100];
   char name_files[100];
   strcpy(src,st.sim_name);
   strcpy(dest,".dat");
   strcpy(name_files,strcat(src,dest));
   fp = fopen(name_files,"w");
   double ti = t;



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
     

     fprintf(fp,"%.5e %.5e %.5e %.5e %.5e %.5e %.5e %.5e %.5e %.5e %.5e %.5e %.5e %.5e %.5e %.5e %.5e \n",
	     t,y[0],y[1],y[2],y[3],y[4],y[5],y[6],y[7],y[8],y[9],y[10],y[11],y[12],y[13],y[14],y[15]);
   }
   
   gsl_odeiv2_driver_free (d);
   fclose(fp);
  */
   
   return 0;
   
}

