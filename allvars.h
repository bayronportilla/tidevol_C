#define AU     149.6e9
#define MS     1.989e30
#define ME     5.9723e24
#define RE     6.371e6
#define RS     6.957e8
#define MJ     1.898e27
#define RJ     6.9911e7
#define YEARS  365.25*86400.0
#define DAYS   86400.0 
#define G      1.0
#define PI     3.14159265358979323
#define InRad  M_PI/180.0
#define InDeg  180.0/M_PI
#define PREC_ECC_ANO 1e-14

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_integration.h>
#include <libconfig.h>
#include "Units.h"
#include "Params.h"
#include "generic.h"
#include "FetchInfo.h"




