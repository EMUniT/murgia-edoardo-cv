//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// primitives.h
//
// Code generation for function 'primitives'
//

#ifndef PRIMITIVES_H
#define PRIMITIVES_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void pass_primitive(double v0, double a0, double sf, double vfmin,
                           double vfmax, double Tmin, double Tmax,
                           double coeffsT2[6], double *v2, double *T2,
                           double coeffsT1[6], double *v1, double *T1);

extern void pass_primitive_j0(double v0, double a0, double sf, double vfmin,
                              double vfmax, double coefsj0[6], double *vfj0,
                              double *tfj0);

extern void primitives_initialize();

extern void primitives_terminate();

extern void stop_primitive(double v0, double a0, double sf, double coefs[6],
                           double *maxsf, double *tf);

extern void stop_primitive_j0(double v0, double a0, double coefsj0[6],
                              double *sfj0, double *tfj0);

#endif
// End of code generation (primitives.h)
