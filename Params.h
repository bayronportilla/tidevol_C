typedef struct Inpar_params{

  // Planet properties
  double m_p;
  double R_p;
  double BmAC;
  double gyr_rad;
  double a;
  double e;
  double P_rot;
  double tau_M;
  double mu;
  double alpha;

  // Inner B properties
  double m_s ;

  // General properties
  const char *sim_name;
  double t_ini;
  double t_end;
  double h_output;

  // Canonical units info.
  double uM;
  double uL;
  double uT;

  
} Inpar; // Defining a new datatype *Inpar*
         //which is a structure of the tyoe *Inpar_params*


Inpar params(){
  
  Inpar rest; //defining the REturnSTucture

  config_t cfg;
  config_setting_t *setting;


  config_init(&cfg);
  
  // Read the file. If there is an error, report it and exit. 
  if(! config_read_file(&cfg, "config.cfg"))
    {
      fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
	      config_error_line(&cfg), config_error_text(&cfg));
      config_destroy(&cfg);
    }

  ////////////////////////////////////////////////////////////
  //
  // Getting and storing General Properties
  //
  ////////////////////////////////////////////////////////////

  const char *sim_name;
  double t_ini;
  double t_end;
  double h_output;
  double uM;
  double uL;
  
  
  //config_lookup_string(&cfg, "method", &met);
  config_lookup_string(&cfg, "sim_name"   , &sim_name);
  config_lookup_float(&cfg,  "t_ini"      , &t_ini);
  config_lookup_float(&cfg,  "t_end"      , &t_end);
  config_lookup_float(&cfg,  "h_output"   , &h_output);
  config_lookup_float(&cfg,  "uM"         , &uM);
  config_lookup_float(&cfg,  "uL"         , &uL);

  
  ////////////////////////////////////////////////////////////
  //
  // Getting information about planet
  //
  ////////////////////////////////////////////////////////////
  
  double m_p;
  double R_p;
  double BmAC;
  double gyr_rad;
  double a;
  double e;
  double P_rot;
  double tau_M;
  double mu;
  double alpha;
  
  
  setting = config_lookup(&cfg, "bodies.planet");
  if(setting != NULL){
    int count = config_setting_length(setting);
    int i;
    
    for(i = 0; i < count; ++i){
      config_setting_t *object = config_setting_get_elem(setting, i);
      
      config_setting_lookup_float(object,  "mass",    &m_p);
      config_setting_lookup_float(object,  "radius",  &R_p);
      config_setting_lookup_float(object,  "gyr_rad", &gyr_rad);
      config_setting_lookup_float(object,  "a",       &a);
      config_setting_lookup_float(object,  "e",       &e);
      config_setting_lookup_float(object,  "P_rot",   &P_rot);
      config_setting_lookup_float(object,  "mu",      &mu);
      config_setting_lookup_float(object,  "alpha",   &alpha);
    }
  }
  
 
  ////////////////////////////////////////////////////////////
  //
  // Getting information about star
  //
  ////////////////////////////////////////////////////////////
  
  double m_s;
  setting = config_lookup(&cfg, "bodies.star");
  if(setting != NULL){
    int count = config_setting_length(setting);
    int i;
    
    for(i = 0; i < count; ++i){
      config_setting_t *object = config_setting_get_elem(setting, i);
      
      config_setting_lookup_float(object,  "mass",    &m_s);
    }
  }
  
  
  ////////////////////////////////////////////////////////////
  //
  // Finding derived time canonical unit
  //
  ////////////////////////////////////////////////////////////
  
  double uT =  units(uM,uL,"uT")[2];


  rest.m_p      = m_p * ME/uM;
  rest.R_p      = R_p * RS/uL;
  rest.BmAC     = BmAC;
  rest.gyr_rad  = gyr_rad;
  rest.a        = a * AU/uL;
  rest.e        = e;
  rest.P_rot    = P_rot * DAYS/uT;
  rest.tau_M    = tau_M * DAYS/uT;
  rest.mu       = mu;
  rest.alpha    = alpha;
  rest.m_s      = m_s * MS/uM;
  rest.sim_name = sim_name;
  rest.t_ini    = t_ini * YEARS/uT;
  rest.t_end    = t_end * YEARS/uT;
  rest.h_output = h_output * YEARS/uT;

  rest.uM       = uM;
  rest.uL       = uL;
  rest.uT       = uT;
  
  return rest;
  config_destroy(&cfg);

}
