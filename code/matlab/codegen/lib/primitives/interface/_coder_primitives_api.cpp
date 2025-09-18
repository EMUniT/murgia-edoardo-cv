//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// _coder_primitives_api.cpp
//
// Code generation for function 'pass_primitive'
//

// Include files
#include "_coder_primitives_api.h"
#include "_coder_primitives_mex.h"

// Variable Definitions
emlrtCTX emlrtRootTLSGlobal{nullptr};

emlrtContext emlrtContextGlobal{
    true,                                                 // bFirstTime
    false,                                                // bInitialized
    131659U,                                              // fVersionInfo
    nullptr,                                              // fErrorFunction
    "primitives",                                         // fFunctionName
    nullptr,                                              // fRTCallStack
    false,                                                // bDebugMode
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, // fSigWrd
    nullptr                                               // fSigMem
};

// Function Declarations
static real_T b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId);

static void emlrtExitTimeCleanupDtorFcn(const void *r);

static real_T emlrt_marshallIn(const emlrtStack &sp, const mxArray *b_nullptr,
                               const char_T *identifier);

static real_T emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId);

static const mxArray *emlrt_marshallOut(real_T u[6]);

static const mxArray *emlrt_marshallOut(const real_T u);

// Function Definitions
static real_T b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims{0};
  real_T ret;
  emlrtCheckBuiltInR2012b((emlrtConstCTX)&sp, msgId, src, "double", false, 0U,
                          (const void *)&dims);
  ret = *static_cast<real_T *>(emlrtMxGetData(src));
  emlrtDestroyArray(&src);
  return ret;
}

static void emlrtExitTimeCleanupDtorFcn(const void *r)
{
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

static real_T emlrt_marshallIn(const emlrtStack &sp, const mxArray *b_nullptr,
                               const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  real_T y;
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = emlrt_marshallIn(sp, emlrtAlias(b_nullptr), &thisId);
  emlrtDestroyArray(&b_nullptr);
  return y;
}

static real_T emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = b_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static const mxArray *emlrt_marshallOut(real_T u[6])
{
  static const int32_T iv[2]{0, 0};
  static const int32_T iv1[2]{1, 6};
  const mxArray *m;
  const mxArray *y;
  y = nullptr;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, &u[0]);
  emlrtSetDimensions((mxArray *)m, &iv1[0], 2);
  emlrtAssign(&y, m);
  return y;
}

static const mxArray *emlrt_marshallOut(const real_T u)
{
  const mxArray *m;
  const mxArray *y;
  y = nullptr;
  m = emlrtCreateDoubleScalar(u);
  emlrtAssign(&y, m);
  return y;
}

void pass_primitive_api(const mxArray *const prhs[7], int32_T nlhs,
                        const mxArray *plhs[6])
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  real_T(*coeffsT1)[6];
  real_T(*coeffsT2)[6];
  real_T T1;
  real_T T2;
  real_T Tmax;
  real_T Tmin;
  real_T a0;
  real_T sf;
  real_T v0;
  real_T v1;
  real_T v2;
  real_T vfmax;
  real_T vfmin;
  st.tls = emlrtRootTLSGlobal;
  coeffsT2 = (real_T(*)[6])mxMalloc(sizeof(real_T[6]));
  coeffsT1 = (real_T(*)[6])mxMalloc(sizeof(real_T[6]));
  // Marshall function inputs
  v0 = emlrt_marshallIn(st, emlrtAliasP(prhs[0]), "v0");
  a0 = emlrt_marshallIn(st, emlrtAliasP(prhs[1]), "a0");
  sf = emlrt_marshallIn(st, emlrtAliasP(prhs[2]), "sf");
  vfmin = emlrt_marshallIn(st, emlrtAliasP(prhs[3]), "vfmin");
  vfmax = emlrt_marshallIn(st, emlrtAliasP(prhs[4]), "vfmax");
  Tmin = emlrt_marshallIn(st, emlrtAliasP(prhs[5]), "Tmin");
  Tmax = emlrt_marshallIn(st, emlrtAliasP(prhs[6]), "Tmax");
  // Invoke the target function
  pass_primitive(v0, a0, sf, vfmin, vfmax, Tmin, Tmax, *coeffsT2, &v2, &T2,
                 *coeffsT1, &v1, &T1);
  // Marshall function outputs
  plhs[0] = emlrt_marshallOut(*coeffsT2);
  if (nlhs > 1) {
    plhs[1] = emlrt_marshallOut(v2);
  }
  if (nlhs > 2) {
    plhs[2] = emlrt_marshallOut(T2);
  }
  if (nlhs > 3) {
    plhs[3] = emlrt_marshallOut(*coeffsT1);
  }
  if (nlhs > 4) {
    plhs[4] = emlrt_marshallOut(v1);
  }
  if (nlhs > 5) {
    plhs[5] = emlrt_marshallOut(T1);
  }
}

void pass_primitive_j0_api(const mxArray *const prhs[5], int32_T nlhs,
                           const mxArray *plhs[3])
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  real_T(*coefsj0)[6];
  real_T a0;
  real_T sf;
  real_T tfj0;
  real_T v0;
  real_T vfj0;
  real_T vfmax;
  real_T vfmin;
  st.tls = emlrtRootTLSGlobal;
  coefsj0 = (real_T(*)[6])mxMalloc(sizeof(real_T[6]));
  // Marshall function inputs
  v0 = emlrt_marshallIn(st, emlrtAliasP(prhs[0]), "v0");
  a0 = emlrt_marshallIn(st, emlrtAliasP(prhs[1]), "a0");
  sf = emlrt_marshallIn(st, emlrtAliasP(prhs[2]), "sf");
  vfmin = emlrt_marshallIn(st, emlrtAliasP(prhs[3]), "vfmin");
  vfmax = emlrt_marshallIn(st, emlrtAliasP(prhs[4]), "vfmax");
  // Invoke the target function
  pass_primitive_j0(v0, a0, sf, vfmin, vfmax, *coefsj0, &vfj0, &tfj0);
  // Marshall function outputs
  plhs[0] = emlrt_marshallOut(*coefsj0);
  if (nlhs > 1) {
    plhs[1] = emlrt_marshallOut(vfj0);
  }
  if (nlhs > 2) {
    plhs[2] = emlrt_marshallOut(tfj0);
  }
}

void primitives_atexit()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtPushHeapReferenceStackR2021a(&st, false, nullptr,
                                    (void *)&emlrtExitTimeCleanupDtorFcn,
                                    nullptr, nullptr, nullptr);
  emlrtEnterRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  primitives_xil_terminate();
  primitives_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void primitives_initialize()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, nullptr);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

void primitives_terminate()
{
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

void stop_primitive_api(const mxArray *const prhs[3], int32_T nlhs,
                        const mxArray *plhs[3])
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  real_T(*coefs)[6];
  real_T a0;
  real_T maxsf;
  real_T sf;
  real_T tf;
  real_T v0;
  st.tls = emlrtRootTLSGlobal;
  coefs = (real_T(*)[6])mxMalloc(sizeof(real_T[6]));
  // Marshall function inputs
  v0 = emlrt_marshallIn(st, emlrtAliasP(prhs[0]), "v0");
  a0 = emlrt_marshallIn(st, emlrtAliasP(prhs[1]), "a0");
  sf = emlrt_marshallIn(st, emlrtAliasP(prhs[2]), "sf");
  // Invoke the target function
  stop_primitive(v0, a0, sf, *coefs, &maxsf, &tf);
  // Marshall function outputs
  plhs[0] = emlrt_marshallOut(*coefs);
  if (nlhs > 1) {
    plhs[1] = emlrt_marshallOut(maxsf);
  }
  if (nlhs > 2) {
    plhs[2] = emlrt_marshallOut(tf);
  }
}

void stop_primitive_j0_api(const mxArray *const prhs[2], int32_T nlhs,
                           const mxArray *plhs[3])
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  real_T(*coefsj0)[6];
  real_T a0;
  real_T sfj0;
  real_T tfj0;
  real_T v0;
  st.tls = emlrtRootTLSGlobal;
  coefsj0 = (real_T(*)[6])mxMalloc(sizeof(real_T[6]));
  // Marshall function inputs
  v0 = emlrt_marshallIn(st, emlrtAliasP(prhs[0]), "v0");
  a0 = emlrt_marshallIn(st, emlrtAliasP(prhs[1]), "a0");
  // Invoke the target function
  stop_primitive_j0(v0, a0, *coefsj0, &sfj0, &tfj0);
  // Marshall function outputs
  plhs[0] = emlrt_marshallOut(*coefsj0);
  if (nlhs > 1) {
    plhs[1] = emlrt_marshallOut(sfj0);
  }
  if (nlhs > 2) {
    plhs[2] = emlrt_marshallOut(tfj0);
  }
}

// End of code generation (_coder_primitives_api.cpp)
