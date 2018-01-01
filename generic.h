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

