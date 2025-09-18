//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// main.cpp
//
// Code generation for function 'main'
//

/*************************************************************************/
/* This automatically generated example C++ main file shows how to call  */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

// Include files
#include "main.h"
#include "primitives.h"
#include "rt_nonfinite.h"

// Function Declarations
static double argInit_real_T();

// Function Definitions
static double argInit_real_T()
{
  return 0.0;
}

int main(int, char **)
{
  // The initialize function is being called automatically from your entry-point
  // function. So, a call to initialize is not included here. Invoke the
  // entry-point functions.
  // You can call entry-point functions multiple times.
  main_pass_primitive();
  main_pass_primitive_j0();
  main_stop_primitive();
  main_stop_primitive_j0();
  // Terminate the application.
  // You do not need to do this more than one time.
  primitives_terminate();
  return 0;
}

void main_pass_primitive()
{
  double coeffsT1[6];
  double coeffsT2[6];
  double T1;
  double T2;
  double v0_tmp;
  double v1;
  double v2;
  // Initialize function 'pass_primitive' input arguments.
  v0_tmp = argInit_real_T();
  // Call the entry-point 'pass_primitive'.
  pass_primitive(v0_tmp, v0_tmp, v0_tmp, v0_tmp, v0_tmp, v0_tmp, v0_tmp,
                 coeffsT2, &v2, &T2, coeffsT1, &v1, &T1);
}

void main_pass_primitive_j0()
{
  double coefsj0[6];
  double tfj0;
  double vfj0;
  // Initialize function 'pass_primitive_j0' input arguments.
  vfj0 = argInit_real_T();
  // Call the entry-point 'pass_primitive_j0'.
  pass_primitive_j0(vfj0, vfj0, vfj0, vfj0, vfj0, coefsj0, &vfj0, &tfj0);
}

void main_stop_primitive()
{
  double coefs[6];
  double maxsf;
  double tf;
  // Initialize function 'stop_primitive' input arguments.
  maxsf = argInit_real_T();
  // Call the entry-point 'stop_primitive'.
  stop_primitive(maxsf, maxsf, maxsf, coefs, &maxsf, &tf);
}

void main_stop_primitive_j0()
{
  double coefsj0[6];
  double sfj0;
  double tfj0;
  double v0_tmp;
  // Initialize function 'stop_primitive_j0' input arguments.
  v0_tmp = argInit_real_T();
  // Call the entry-point 'stop_primitive_j0'.
  stop_primitive_j0(v0_tmp, v0_tmp, coefsj0, &sfj0, &tfj0);
}

// End of code generation (main.cpp)
