//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// _coder_primitives_api.h
//
// Code generation for function 'pass_primitive'
//

#ifndef _CODER_PRIMITIVES_API_H
#define _CODER_PRIMITIVES_API_H

// Include files
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void pass_primitive(real_T v0, real_T a0, real_T sf, real_T vfmin, real_T vfmax,
                    real_T Tmin, real_T Tmax, real_T coeffsT2[6], real_T *v2,
                    real_T *T2, real_T coeffsT1[6], real_T *v1, real_T *T1);

void pass_primitive_api(const mxArray *const prhs[7], int32_T nlhs,
                        const mxArray *plhs[6]);

void pass_primitive_j0(real_T v0, real_T a0, real_T sf, real_T vfmin,
                       real_T vfmax, real_T coefsj0[6], real_T *vfj0,
                       real_T *tfj0);

void pass_primitive_j0_api(const mxArray *const prhs[5], int32_T nlhs,
                           const mxArray *plhs[3]);

void primitives_atexit();

void primitives_initialize();

void primitives_terminate();

void primitives_xil_shutdown();

void primitives_xil_terminate();

void stop_primitive(real_T v0, real_T a0, real_T sf, real_T coefs[6],
                    real_T *maxsf, real_T *tf);

void stop_primitive_api(const mxArray *const prhs[3], int32_T nlhs,
                        const mxArray *plhs[3]);

void stop_primitive_j0(real_T v0, real_T a0, real_T coefsj0[6], real_T *sfj0,
                       real_T *tfj0);

void stop_primitive_j0_api(const mxArray *const prhs[2], int32_T nlhs,
                           const mxArray *plhs[3]);

#endif
// End of code generation (_coder_primitives_api.h)
