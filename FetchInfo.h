int FetchInfo(Inpar st){
  FILE *fp;
  char src[100];
  char dest[100];
  char name_files[100];
  strcpy(src,st.sim_name);
  strcpy(dest,".log");
  strcpy(name_files,strcat(src,dest));
  
  fp = fopen(name_files,"w");

  fprintf(fp,"0   m_p           %1.17e \n\
1   R_p           %1.17e \n\
2   BmAC          %1.17e \n\
3   gyr_rad       %1.17e \n\
4   a             %1.17e \n\
5   e             %1.17e \n\
6   P_rot         %1.17e \n\
7   tau_M         %1.17e \n\
8   mu            %1.17e \n\
9   alpha         %1.17e \n\
10  m_s           %1.17e \n\
11  t_ini         %1.17e \n\
12  t_end         %1.17e \n\
13  uM            %1.17e \n\
14  uL            %1.17e \n\
15  uT            %1.17e \n\
16  h_output      %1.17e \n\
17  sim_name      %s     \n\
16  theta_ini     %1.17e \n\
16  res_ini       %1.17e \n",
	  st.m_p,st.R_p,st.BmAC,st.gyr_rad,st.a,st.e,st.P_rot,st.tau_M,st.mu,
	  st.alpha,st.m_s,st.t_ini,st.t_end,st.uM,st.uL,st.uT,
	  st.h_output,st.sim_name,st.theta_ini,st.res_ini);
  
  return 0;
}

