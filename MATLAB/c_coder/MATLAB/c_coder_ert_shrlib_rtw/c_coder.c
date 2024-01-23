/*
 * File: c_coder.c
 *
 * Code generated for Simulink model 'c_coder'.
 *
 * Model version                  : 8.132
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Tue Jan 23 03:23:04 2024
 *
 * Target selection: ert_shrlib.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "c_coder.h"
#include "c_coder_private.h"

/* user code (top of source file) */
#include <stdint.h>

__declspec(dllexport) void wrapper_c_coder_step(RT_MODEL_c_coder_T *const
  c_coder_M,
  real_T c_coder_U_Inport,
  real_T c_coder_U_Inport1,
  real_T c_coder_U_Inport2,
  real_T c_coder_U_Inport3,
  real_T c_coder_U_Inport4,
  real_T c_coder_U_Inport5)
{
  c_coder_step(c_coder_M, c_coder_U_Inport, c_coder_U_Inport1, c_coder_U_Inport2,
               c_coder_U_Inport3, c_coder_U_Inport4, c_coder_U_Inport5);
}

__declspec(dllexport) void wrapper_c_coder_initialize(RT_MODEL_c_coder_T *const
  c_coder_M,
  real_T c_coder_U_Inport,
  real_T c_coder_U_Inport1,
  real_T c_coder_U_Inport2,
  real_T c_coder_U_Inport3,
  real_T c_coder_U_Inport4,
  real_T c_coder_U_Inport5)
{
  c_coder_initialize(c_coder_M, &c_coder_U_Inport, &c_coder_U_Inport1,
                     &c_coder_U_Inport2, &c_coder_U_Inport3, &c_coder_U_Inport4,
                     &c_coder_U_Inport5);
}

/* Exported block signals */
uint8_T out1[25];                      /* '<Root>/Out1' */

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si ,
  RT_MODEL_c_coder_T *const c_coder_M, real_T c_coder_U_Inport, real_T
  c_coder_U_Inport1, real_T c_coder_U_Inport2, real_T c_coder_U_Inport3, real_T
  c_coder_U_Inport4, real_T c_coder_U_Inport5)
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 11;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  c_coder_derivatives(c_coder_M);

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  c_coder_step(c_coder_M, c_coder_U_Inport, c_coder_U_Inport1, c_coder_U_Inport2,
               c_coder_U_Inport3, c_coder_U_Inport4, c_coder_U_Inport5);
  c_coder_derivatives(c_coder_M);

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  c_coder_step(c_coder_M, c_coder_U_Inport, c_coder_U_Inport1, c_coder_U_Inport2,
               c_coder_U_Inport3, c_coder_U_Inport4, c_coder_U_Inport5);
  c_coder_derivatives(c_coder_M);

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    real_T tmp;
    real_T tmp_0;
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/* Model step function */
void c_coder_step(RT_MODEL_c_coder_T *const c_coder_M, real_T c_coder_U_Inport,
                  real_T c_coder_U_Inport1, real_T c_coder_U_Inport2, real_T
                  c_coder_U_Inport3, real_T c_coder_U_Inport4, real_T
                  c_coder_U_Inport5)
{
  B_c_coder_T *c_coder_B = c_coder_M->blockIO;
  DW_c_coder_T *c_coder_DW = c_coder_M->dwork;
  X_c_coder_T *c_coder_X = c_coder_M->contStates;
  if (rtmIsMajorTimeStep(c_coder_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&c_coder_M->solverInfo,((c_coder_M->Timing.clockTick0+
      1)*c_coder_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(c_coder_M)) {
    c_coder_M->Timing.t[0] = rtsiGetT(&c_coder_M->solverInfo);
  }

  {
    real_T tmp;
    real_T tmp_0;
    real_T tmp_idx_1;
    real_T *lastU;

    /* RelationalOperator: '<S1>/Compare' incorporates:
     *  Constant: '<S1>/Constant'
     *  Inport: '<Root>/Inport3'
     *  Inport: '<Root>/Inport4'
     *  Inport: '<Root>/Inport5'
     */
    c_coder_B->Compare[0] = (c_coder_U_Inport3 <= 180.0);
    c_coder_B->Compare[1] = (c_coder_U_Inport4 <= 180.0);
    c_coder_B->Compare[2] = (c_coder_U_Inport5 <= 180.0);

    /* Sum: '<Root>/Sum2' incorporates:
     *  Constant: '<Root>/Constant'
     *  Inport: '<Root>/Inport3'
     *  Inport: '<Root>/Inport4'
     *  Inport: '<Root>/Inport5'
     */
    c_coder_B->Sum2[0] = c_coder_U_Inport3 - 360.0;
    c_coder_B->Sum2[1] = c_coder_U_Inport4 - 360.0;
    c_coder_B->Sum2[2] = c_coder_U_Inport5 - 360.0;

    /* Switch: '<Root>/Switch' incorporates:
     *  Inport: '<Root>/Inport3'
     *  Inport: '<Root>/Inport4'
     *  Inport: '<Root>/Inport5'
     */
    tmp = c_coder_U_Inport3;
    tmp_idx_1 = c_coder_U_Inport4;
    tmp_0 = c_coder_U_Inport5;
    if (c_coder_B->Compare[0]) {
      c_coder_B->Switch[0] = tmp;
    } else {
      c_coder_B->Switch[0] = c_coder_B->Sum2[0];
    }

    if (c_coder_B->Compare[1]) {
      c_coder_B->Switch[1] = tmp_idx_1;
    } else {
      c_coder_B->Switch[1] = c_coder_B->Sum2[1];
    }

    if (c_coder_B->Compare[2]) {
      c_coder_B->Switch[2] = tmp_0;
    } else {
      c_coder_B->Switch[2] = c_coder_B->Sum2[2];
    }

    /* End of Switch: '<Root>/Switch' */

    /* Gain: '<Root>/Gain3' */
    c_coder_B->Gain3 = (-1.0) * c_coder_B->Switch[2];

    /* Saturate: '<Root>/Saturation2' */
    tmp = c_coder_B->Gain3;
    tmp_idx_1 = (-15.0);
    tmp_0 = 15.0;
    if (tmp > tmp_0) {
      /* Saturate: '<Root>/Saturation2' */
      c_coder_B->Saturation2 = tmp_0;
    } else if (tmp < tmp_idx_1) {
      /* Saturate: '<Root>/Saturation2' */
      c_coder_B->Saturation2 = tmp_idx_1;
    } else {
      /* Saturate: '<Root>/Saturation2' */
      c_coder_B->Saturation2 = tmp;
    }

    /* End of Saturate: '<Root>/Saturation2' */

    /* Product: '<S9>/Product5' incorporates:
     *  Constant: '<S9>/Constant4'
     *  Constant: '<S9>/Constant5'
     */
    c_coder_B->Product5 = c_coder_B->Saturation2 * 3.1415926535897931 / 180.0;

    /* Trigonometry: '<S7>/Trigonometric Function1' */
    c_coder_B->TrigonometricFunction1 = cos(c_coder_B->Product5);

    /* Product: '<S7>/Product1' incorporates:
     *  Constant: '<S5>/Constant7'
     */
    c_coder_B->z = c_coder_B->TrigonometricFunction1 * 180.0;

    /* Gain: '<Root>/Gain2' */
    c_coder_B->Gain2 = 1.0 * c_coder_B->Switch[0];

    /* Saturate: '<Root>/Saturation1' */
    tmp = c_coder_B->Gain2;
    tmp_idx_1 = (-15.0);
    tmp_0 = 15.0;
    if (tmp > tmp_0) {
      /* Saturate: '<Root>/Saturation1' */
      c_coder_B->Saturation1 = tmp_0;
    } else if (tmp < tmp_idx_1) {
      /* Saturate: '<Root>/Saturation1' */
      c_coder_B->Saturation1 = tmp_idx_1;
    } else {
      /* Saturate: '<Root>/Saturation1' */
      c_coder_B->Saturation1 = tmp;
    }

    /* End of Saturate: '<Root>/Saturation1' */

    /* Product: '<S10>/Product5' incorporates:
     *  Constant: '<S10>/Constant4'
     *  Constant: '<S10>/Constant5'
     */
    c_coder_B->Product5_e = c_coder_B->Saturation1 * 3.1415926535897931 / 180.0;

    /* Trigonometry: '<S7>/Trigonometric Function2' */
    c_coder_B->TrigonometricFunction2 = sin(c_coder_B->Product5_e);

    /* Product: '<S7>/Product2' */
    c_coder_B->x = c_coder_B->z * c_coder_B->TrigonometricFunction2;
    if (rtmIsMajorTimeStep(c_coder_M)) {
      /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator5' */
      c_coder_B->posx = c_coder_DW->DiscreteTimeIntegrator5_DSTATE;
    }

    /* TransferFcn: '<Root>/Transfer Fcn13' */
    c_coder_B->TransferFcn13 = 0.0;
    c_coder_B->TransferFcn13 += (-6.2831853071795862) *
      c_coder_X->TransferFcn13_CSTATE;
    c_coder_B->TransferFcn13 += 1.0 * c_coder_B->posx;

    /* Saturate: '<Root>/Saturation6' */
    tmp = c_coder_B->TransferFcn13;
    tmp_idx_1 = (-250.0);
    tmp_0 = 250.0;
    if (tmp > tmp_0) {
      /* Saturate: '<Root>/Saturation6' */
      c_coder_B->posx_filt = tmp_0;
    } else if (tmp < tmp_idx_1) {
      /* Saturate: '<Root>/Saturation6' */
      c_coder_B->posx_filt = tmp_idx_1;
    } else {
      /* Saturate: '<Root>/Saturation6' */
      c_coder_B->posx_filt = tmp;
    }

    /* End of Saturate: '<Root>/Saturation6' */

    /* Sum: '<S7>/Sum' */
    c_coder_B->Sum = c_coder_B->x + c_coder_B->posx_filt;

    /* Trigonometry: '<S7>/Trigonometric Function' */
    c_coder_B->TrigonometricFunction = sin(c_coder_B->Product5);

    /* Product: '<S7>/Product' incorporates:
     *  Constant: '<S5>/Constant7'
     */
    c_coder_B->y = c_coder_B->TrigonometricFunction * 180.0;
    if (rtmIsMajorTimeStep(c_coder_M)) {
      /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator4' */
      c_coder_B->DiscreteTimeIntegrator4 =
        c_coder_DW->DiscreteTimeIntegrator4_DSTATE;
    }

    /* TransferFcn: '<Root>/Transfer Fcn11' */
    c_coder_B->TransferFcn11 = 0.0;
    c_coder_B->TransferFcn11 += (-6.2831853071795862) *
      c_coder_X->TransferFcn11_CSTATE;
    c_coder_B->TransferFcn11 += 1.0 * c_coder_B->DiscreteTimeIntegrator4;

    /* Saturate: '<Root>/Saturation4' */
    tmp = c_coder_B->TransferFcn11;
    tmp_idx_1 = (-250.0);
    tmp_0 = 250.0;
    if (tmp > tmp_0) {
      /* Saturate: '<Root>/Saturation4' */
      c_coder_B->Saturation4 = tmp_0;
    } else if (tmp < tmp_idx_1) {
      /* Saturate: '<Root>/Saturation4' */
      c_coder_B->Saturation4 = tmp_idx_1;
    } else {
      /* Saturate: '<Root>/Saturation4' */
      c_coder_B->Saturation4 = tmp;
    }

    /* End of Saturate: '<Root>/Saturation4' */

    /* Sum: '<S7>/Sum1' */
    c_coder_B->Sum1 = c_coder_B->y + c_coder_B->Saturation4;

    /* Trigonometry: '<S7>/Trigonometric Function3' */
    c_coder_B->TrigonometricFunction3 = cos(c_coder_B->Product5_e);

    /* Product: '<S7>/Product3' */
    c_coder_B->z_n = c_coder_B->z * c_coder_B->TrigonometricFunction3;

    /* Sum: '<S7>/Sum2' incorporates:
     *  Constant: '<Root>/Constant5'
     *  Constant: '<S5>/Constant5'
     */
    c_coder_B->Sum2_n = (1002.0 - c_coder_B->z_n) - 180.0;

    /* Fcn: '<S8>/XT1' incorporates:
     *  Constant: '<S5>/Constant2'
     *  Constant: '<S5>/Constant3'
     */
    c_coder_B->XT1 = ((sin(c_coder_B->Product5) * sin(c_coder_B->Product5_e) *
                       sin(c_coder_ConstB.Product5) + cos(c_coder_B->Product5_e)
                       * cos(c_coder_ConstB.Product5)) * -0.16666666666666666 *
                      1.7320508075688772 * (2.0 * 690.0 + 220.0) + (sin
      (c_coder_B->Product5) * sin(c_coder_B->Product5_e) * cos
      (c_coder_ConstB.Product5) + -cos(c_coder_B->Product5_e) * sin
      (c_coder_ConstB.Product5)) * 0.5 * 220.0) + c_coder_B->Sum;

    /* Fcn: '<S8>/YT1' incorporates:
     *  Constant: '<S5>/Constant2'
     *  Constant: '<S5>/Constant3'
     */
    c_coder_B->YT1 = (-0.16666666666666666 * cos(c_coder_B->Product5) * sin
                      (c_coder_ConstB.Product5) * 1.7320508075688772 * (2.0 *
      690.0 + 220.0) + 0.5 * cos(c_coder_B->Product5) * cos
                      (c_coder_ConstB.Product5) * 220.0) + c_coder_B->Sum1;

    /* Fcn: '<S8>/ZT1' incorporates:
     *  Constant: '<S5>/Constant2'
     *  Constant: '<S5>/Constant3'
     */
    c_coder_B->ZT1 = ((sin(c_coder_B->Product5) * cos(c_coder_B->Product5_e) *
                       sin(c_coder_ConstB.Product5) + -sin(c_coder_B->Product5_e)
                       * cos(c_coder_ConstB.Product5)) * -0.16666666666666666 *
                      1.7320508075688772 * (2.0 * 690.0 + 220.0) + (sin
      (c_coder_B->Product5) * cos(c_coder_B->Product5_e) * cos
      (c_coder_ConstB.Product5) + sin(c_coder_B->Product5_e) * sin
      (c_coder_ConstB.Product5)) * 0.5 * 220.0) + c_coder_B->Sum2_n;

    /* Fcn: '<S8>/XT2' incorporates:
     *  Constant: '<S5>/Constant2'
     *  Constant: '<S5>/Constant3'
     */
    c_coder_B->XT2 = ((sin(c_coder_B->Product5) * sin(c_coder_B->Product5_e) *
                       sin(c_coder_ConstB.Product5) + cos(c_coder_B->Product5_e)
                       * cos(c_coder_ConstB.Product5)) * 0.16666666666666666 *
                      1.7320508075688772 * (690.0 - 220.0) + (sin
      (c_coder_B->Product5) * sin(c_coder_B->Product5_e) * cos
      (c_coder_ConstB.Product5) + -cos(c_coder_B->Product5_e) * sin
      (c_coder_ConstB.Product5)) / 2.0 * (690.0 + 220.0)) + c_coder_B->Sum;

    /* Fcn: '<S8>/YT2' incorporates:
     *  Constant: '<S5>/Constant2'
     *  Constant: '<S5>/Constant3'
     */
    c_coder_B->YT2 = (0.16666666666666666 * cos(c_coder_B->Product5) * sin
                      (c_coder_ConstB.Product5) * 1.7320508075688772 * (690.0 -
      220.0) + 0.5 * cos(c_coder_B->Product5) * cos(c_coder_ConstB.Product5) *
                      (690.0 + 220.0)) + c_coder_B->Sum1;

    /* Fcn: '<S8>/ZT2' incorporates:
     *  Constant: '<S5>/Constant2'
     *  Constant: '<S5>/Constant3'
     */
    c_coder_B->ZT2 = ((sin(c_coder_B->Product5) * cos(c_coder_B->Product5_e) *
                       sin(c_coder_ConstB.Product5) + -sin(c_coder_B->Product5_e)
                       * cos(c_coder_ConstB.Product5)) * 0.16666666666666666 *
                      1.7320508075688772 * (690.0 - 220.0) + (sin
      (c_coder_B->Product5) * cos(c_coder_B->Product5_e) * cos
      (c_coder_ConstB.Product5) + sin(c_coder_B->Product5_e) * sin
      (c_coder_ConstB.Product5)) * 0.5 * (690.0 + 220.0)) + c_coder_B->Sum2_n;

    /* Fcn: '<S8>/XT3' incorporates:
     *  Constant: '<S5>/Constant2'
     *  Constant: '<S5>/Constant3'
     */
    c_coder_B->XT3 = ((sin(c_coder_B->Product5) * sin(c_coder_B->Product5_e) *
                       sin(c_coder_ConstB.Product5) + cos(c_coder_B->Product5_e)
                       * cos(c_coder_ConstB.Product5)) * 0.16666666666666666 *
                      1.7320508075688772 * (2.0 * 220.0 + 690.0) + (sin
      (c_coder_B->Product5) * sin(c_coder_B->Product5_e) * cos
      (c_coder_ConstB.Product5) + -cos(c_coder_B->Product5_e) * sin
      (c_coder_ConstB.Product5)) * 0.5 * 690.0) + c_coder_B->Sum;

    /* Fcn: '<S8>/YT3' incorporates:
     *  Constant: '<S5>/Constant2'
     *  Constant: '<S5>/Constant3'
     */
    c_coder_B->YT3 = (0.16666666666666666 * cos(c_coder_B->Product5) * sin
                      (c_coder_ConstB.Product5) * 1.7320508075688772 * (2.0 *
      220.0 + 690.0) + 0.5 * cos(c_coder_B->Product5) * cos
                      (c_coder_ConstB.Product5) * 690.0) + c_coder_B->Sum1;

    /* Fcn: '<S8>/ZT3' incorporates:
     *  Constant: '<S5>/Constant2'
     *  Constant: '<S5>/Constant3'
     */
    c_coder_B->ZT3 = ((sin(c_coder_B->Product5) * cos(c_coder_B->Product5_e) *
                       sin(c_coder_ConstB.Product5) + -sin(c_coder_B->Product5_e)
                       * cos(c_coder_ConstB.Product5)) * 0.16666666666666666 *
                      1.7320508075688772 * (2.0 * 220.0 + 690.0) + (sin
      (c_coder_B->Product5) * cos(c_coder_B->Product5_e) * cos
      (c_coder_ConstB.Product5) + sin(c_coder_B->Product5_e) * sin
      (c_coder_ConstB.Product5)) * 0.5 * 690.0) + c_coder_B->Sum2_n;

    /* Fcn: '<S8>/XT4' incorporates:
     *  Constant: '<S5>/Constant2'
     *  Constant: '<S5>/Constant3'
     */
    c_coder_B->XT4 = ((sin(c_coder_B->Product5) * sin(c_coder_B->Product5_e) *
                       sin(c_coder_ConstB.Product5) + cos(c_coder_B->Product5_e)
                       * cos(c_coder_ConstB.Product5)) * 0.16666666666666666 *
                      1.7320508075688772 * (2.0 * 220.0 + 690.0) - (sin
      (c_coder_B->Product5) * sin(c_coder_B->Product5_e) * cos
      (c_coder_ConstB.Product5) + -cos(c_coder_B->Product5_e) * sin
      (c_coder_ConstB.Product5)) * 0.5 * 690.0) + c_coder_B->Sum;

    /* Fcn: '<S8>/YT4' incorporates:
     *  Constant: '<S5>/Constant2'
     *  Constant: '<S5>/Constant3'
     */
    c_coder_B->YT4 = (0.16666666666666666 * cos(c_coder_B->Product5) * sin
                      (c_coder_ConstB.Product5) * 1.7320508075688772 * (2.0 *
      220.0 + 690.0) - 0.5 * cos(c_coder_B->Product5) * cos
                      (c_coder_ConstB.Product5) * 690.0) + c_coder_B->Sum1;

    /* Fcn: '<S8>/ZT4' incorporates:
     *  Constant: '<S5>/Constant2'
     *  Constant: '<S5>/Constant3'
     */
    c_coder_B->ZT4 = ((sin(c_coder_B->Product5) * cos(c_coder_B->Product5_e) *
                       sin(c_coder_ConstB.Product5) + -sin(c_coder_B->Product5_e)
                       * cos(c_coder_ConstB.Product5)) * 0.16666666666666666 *
                      1.7320508075688772 * (2.0 * 220.0 + 690.0) - (sin
      (c_coder_B->Product5) * cos(c_coder_B->Product5_e) * cos
      (c_coder_ConstB.Product5) + sin(c_coder_B->Product5_e) * sin
      (c_coder_ConstB.Product5)) * 0.5 * 690.0) + c_coder_B->Sum2_n;

    /* Fcn: '<S8>/XT5' incorporates:
     *  Constant: '<S5>/Constant2'
     *  Constant: '<S5>/Constant3'
     */
    c_coder_B->XT5 = ((sin(c_coder_B->Product5) * sin(c_coder_B->Product5_e) *
                       sin(c_coder_ConstB.Product5) + cos(c_coder_B->Product5_e)
                       * cos(c_coder_ConstB.Product5)) * 0.16666666666666666 *
                      1.7320508075688772 * (690.0 - 220.0) - (sin
      (c_coder_B->Product5) * sin(c_coder_B->Product5_e) * cos
      (c_coder_ConstB.Product5) + -cos(c_coder_B->Product5_e) * sin
      (c_coder_ConstB.Product5)) * 0.5 * (690.0 + 220.0)) + c_coder_B->Sum;

    /* Fcn: '<S8>/YT5' incorporates:
     *  Constant: '<S5>/Constant2'
     *  Constant: '<S5>/Constant3'
     */
    c_coder_B->YT5 = (0.16666666666666666 * cos(c_coder_B->Product5) * sin
                      (c_coder_ConstB.Product5) * 1.7320508075688772 * (690.0 -
      220.0) - 0.5 * cos(c_coder_B->Product5) * cos(c_coder_ConstB.Product5) *
                      (690.0 + 220.0)) + c_coder_B->Sum1;

    /* Fcn: '<S8>/ZT5' incorporates:
     *  Constant: '<S5>/Constant2'
     *  Constant: '<S5>/Constant3'
     */
    c_coder_B->ZT5 = ((sin(c_coder_B->Product5) * cos(c_coder_B->Product5_e) *
                       sin(c_coder_ConstB.Product5) + -sin(c_coder_B->Product5_e)
                       * cos(c_coder_ConstB.Product5)) * 0.16666666666666666 *
                      1.7320508075688772 * (690.0 - 220.0) - (sin
      (c_coder_B->Product5) * cos(c_coder_B->Product5_e) * cos
      (c_coder_ConstB.Product5) + sin(c_coder_B->Product5_e) * sin
      (c_coder_ConstB.Product5)) * 0.5 * (690.0 + 220.0)) + c_coder_B->Sum2_n;

    /* Fcn: '<S8>/XT6' incorporates:
     *  Constant: '<S5>/Constant2'
     *  Constant: '<S5>/Constant3'
     */
    c_coder_B->XT6 = ((sin(c_coder_B->Product5) * sin(c_coder_B->Product5_e) *
                       sin(c_coder_ConstB.Product5) + cos(c_coder_B->Product5_e)
                       * cos(c_coder_ConstB.Product5)) * -0.16666666666666666 *
                      1.7320508075688772 * (2.0 * 690.0 + 220.0) - (sin
      (c_coder_B->Product5) * sin(c_coder_B->Product5_e) * cos
      (c_coder_ConstB.Product5) + -cos(c_coder_B->Product5_e) * sin
      (c_coder_ConstB.Product5)) * 0.5 * 220.0) + c_coder_B->Sum;

    /* Fcn: '<S8>/YT6' incorporates:
     *  Constant: '<S5>/Constant2'
     *  Constant: '<S5>/Constant3'
     */
    c_coder_B->YT6 = (-0.16666666666666666 * cos(c_coder_B->Product5) * sin
                      (c_coder_ConstB.Product5) * 1.7320508075688772 * (2.0 *
      690.0 + 220.0) - 0.5 * cos(c_coder_B->Product5) * cos
                      (c_coder_ConstB.Product5) * 220.0) + c_coder_B->Sum1;

    /* Fcn: '<S8>/ZT6' incorporates:
     *  Constant: '<S5>/Constant2'
     *  Constant: '<S5>/Constant3'
     */
    c_coder_B->ZT6 = ((sin(c_coder_B->Product5) * cos(c_coder_B->Product5_e) *
                       sin(c_coder_ConstB.Product5) + -sin(c_coder_B->Product5_e)
                       * cos(c_coder_ConstB.Product5)) * -0.16666666666666666 *
                      1.7320508075688772 * (2.0 * 690.0 + 220.0) - (sin
      (c_coder_B->Product5) * cos(c_coder_B->Product5_e) * cos
      (c_coder_ConstB.Product5) + sin(c_coder_B->Product5_e) * sin
      (c_coder_ConstB.Product5)) * 0.5 * 220.0) + c_coder_B->Sum2_n;

    /* Fcn: '<S8>/XB1' incorporates:
     *  Constant: '<S5>/Constant'
     *  Constant: '<S5>/Constant1'
     */
    c_coder_B->XB1 = (2.0 * 1200.0 + 210.0) * 0.28867513459481287;

    /* Fcn: '<S8>/YB1' incorporates:
     *  Constant: '<S5>/Constant1'
     */
    c_coder_B->YB1 = 0.5 * 210.0;

    /* Fcn: '<S8>/ZB1' */
    c_coder_B->ZB1 = 0.0;

    /* Fcn: '<S8>/XB2' incorporates:
     *  Constant: '<S5>/Constant'
     *  Constant: '<S5>/Constant1'
     */
    c_coder_B->XB2 = (1200.0 - 210.0) * -0.28867513459481287;

    /* Fcn: '<S8>/YB2' incorporates:
     *  Constant: '<S5>/Constant'
     *  Constant: '<S5>/Constant1'
     */
    c_coder_B->YB2 = (1200.0 + 210.0) * 0.5;

    /* Fcn: '<S8>/ZB2' */
    c_coder_B->ZB2 = 0.0;

    /* Fcn: '<S8>/XB3' incorporates:
     *  Constant: '<S5>/Constant'
     *  Constant: '<S5>/Constant1'
     */
    c_coder_B->XB3 = (2.0 * 210.0 + 1200.0) * -0.28867513459481287;

    /* Fcn: '<S8>/YB3' incorporates:
     *  Constant: '<S5>/Constant'
     */
    c_coder_B->YB3 = 0.5 * 1200.0;

    /* Fcn: '<S8>/ZB3' */
    c_coder_B->ZB3 = 0.0;

    /* Fcn: '<S8>/XB4' incorporates:
     *  Constant: '<S5>/Constant'
     *  Constant: '<S5>/Constant1'
     */
    c_coder_B->XB4 = (2.0 * 210.0 + 1200.0) * -0.28867513459481287;

    /* Fcn: '<S8>/YB4' incorporates:
     *  Constant: '<S5>/Constant'
     */
    c_coder_B->YB4 = -0.5 * 1200.0;

    /* Fcn: '<S8>/ZB4' */
    c_coder_B->ZB4 = 0.0;

    /* Fcn: '<S8>/XB5' incorporates:
     *  Constant: '<S5>/Constant'
     *  Constant: '<S5>/Constant1'
     */
    c_coder_B->XB5 = (1200.0 - 210.0) * -0.28867513459481287;

    /* Fcn: '<S8>/YB5' incorporates:
     *  Constant: '<S5>/Constant'
     *  Constant: '<S5>/Constant1'
     */
    c_coder_B->YB5 = (1200.0 + 210.0) * -0.5;

    /* Fcn: '<S8>/ZB5' */
    c_coder_B->ZB5 = 0.0;

    /* Fcn: '<S8>/XB6' incorporates:
     *  Constant: '<S5>/Constant'
     *  Constant: '<S5>/Constant1'
     */
    c_coder_B->XB6 = (2.0 * 1200.0 + 210.0) * 0.28867513459481287;

    /* Fcn: '<S8>/YB6' incorporates:
     *  Constant: '<S5>/Constant1'
     */
    c_coder_B->YB6 = -0.5 * 210.0;

    /* Fcn: '<S8>/ZB6' */
    c_coder_B->ZB6 = 0.0;

    /* Fcn: '<S8>/CL6' */
    tmp = c_coder_B->XT4 - c_coder_B->XB6;
    tmp_idx_1 = rt_powd_snf(tmp, 2.0);
    tmp_0 = c_coder_B->YT4 - c_coder_B->YB6;
    tmp = rt_powd_snf(tmp_0, 2.0);
    tmp_0 = c_coder_B->ZT4 - c_coder_B->ZB6;
    tmp_0 = rt_powd_snf(tmp_0, 2.0);
    tmp_idx_1 = (tmp_idx_1 + tmp) + tmp_0;
    if (tmp_idx_1 < 0.0) {
      tmp_idx_1 = -sqrt(-tmp_idx_1);
    } else {
      tmp_idx_1 = sqrt(tmp_idx_1);
    }

    /* Fcn: '<S8>/CL6' */
    c_coder_B->CL6 = tmp_idx_1;

    /* Sum: '<S8>/Add5' incorporates:
     *  Constant: '<S5>/Constant4'
     */
    c_coder_B->Add5 = c_coder_B->CL6 - 750.0;

    /* Product: '<S8>/Divide5' incorporates:
     *  Constant: '<S5>/Constant6'
     */
    c_coder_B->Divide5 = c_coder_B->Add5 * 10.0;
    if (rtmIsMajorTimeStep(c_coder_M)) {
      /* Product: '<S6>/Divide4' incorporates:
       *  Constant: '<S6>/Constant6'
       */
      c_coder_B->Divide4 = c_coder_B->Divide5 / 256.0;

      /* DataTypeConversion: '<S6>/Data Type Conversion16' */
      tmp = floor(c_coder_B->Divide4);
      if (rtIsNaN(tmp) || rtIsInf(tmp)) {
        tmp = 0.0;
      } else {
        tmp = fmod(tmp, 256.0);
      }

      /* DataTypeConversion: '<S6>/Data Type Conversion16' */
      c_coder_B->DataTypeConversion16 = (int8_T)(tmp < 0.0 ? (int32_T)(int8_T)
        -(int8_T)(uint8_T)-tmp : (int32_T)(int8_T)(uint8_T)tmp);

      /* DataTypeConversion: '<S6>/Data Type Conversion17' */
      c_coder_B->DataTypeConversion17 = (uint8_T)c_coder_B->DataTypeConversion16;

      /* DataTypeConversion: '<S6>/Data Type Conversion15' */
      tmp = floor(c_coder_B->Divide5);
      if (rtIsNaN(tmp) || rtIsInf(tmp)) {
        tmp = 0.0;
      } else {
        tmp = fmod(tmp, 256.0);
      }

      /* DataTypeConversion: '<S6>/Data Type Conversion15' */
      c_coder_B->DataTypeConversion15 = (uint8_T)(tmp < 0.0 ? (int32_T)(uint8_T)
        -(int8_T)(uint8_T)-tmp : (int32_T)(uint8_T)tmp);
    }

    /* Fcn: '<S8>/CL1' */
    tmp = c_coder_B->XT3 - c_coder_B->XB1;
    tmp_idx_1 = rt_powd_snf(tmp, 2.0);
    tmp_0 = c_coder_B->YT3 - c_coder_B->YB1;
    tmp = rt_powd_snf(tmp_0, 2.0);
    tmp_0 = c_coder_B->ZT3 - c_coder_B->ZB1;
    tmp_0 = rt_powd_snf(tmp_0, 2.0);
    tmp_idx_1 = (tmp_idx_1 + tmp) + tmp_0;
    if (tmp_idx_1 < 0.0) {
      tmp_idx_1 = -sqrt(-tmp_idx_1);
    } else {
      tmp_idx_1 = sqrt(tmp_idx_1);
    }

    /* Fcn: '<S8>/CL1' */
    c_coder_B->CL1 = tmp_idx_1;

    /* Sum: '<S8>/Add' incorporates:
     *  Constant: '<S5>/Constant4'
     */
    c_coder_B->Add = c_coder_B->CL1 - 750.0;

    /* Product: '<S8>/Divide' incorporates:
     *  Constant: '<S5>/Constant6'
     */
    c_coder_B->Divide = c_coder_B->Add * 10.0;
    if (rtmIsMajorTimeStep(c_coder_M)) {
      /* Product: '<S6>/Divide1' incorporates:
       *  Constant: '<S6>/Constant7'
       */
      c_coder_B->Divide1 = c_coder_B->Divide / 256.0;

      /* DataTypeConversion: '<S6>/Data Type Conversion18' */
      tmp = floor(c_coder_B->Divide1);
      if (rtIsNaN(tmp) || rtIsInf(tmp)) {
        tmp = 0.0;
      } else {
        tmp = fmod(tmp, 256.0);
      }

      /* DataTypeConversion: '<S6>/Data Type Conversion18' */
      c_coder_B->DataTypeConversion18 = (int8_T)(tmp < 0.0 ? (int32_T)(int8_T)
        -(int8_T)(uint8_T)-tmp : (int32_T)(int8_T)(uint8_T)tmp);

      /* DataTypeConversion: '<S6>/Data Type Conversion4' */
      c_coder_B->DataTypeConversion4_e = (uint8_T)
        c_coder_B->DataTypeConversion18;

      /* DataTypeConversion: '<S6>/Data Type Conversion2' */
      tmp = floor(c_coder_B->Divide);
      if (rtIsNaN(tmp) || rtIsInf(tmp)) {
        tmp = 0.0;
      } else {
        tmp = fmod(tmp, 256.0);
      }

      /* DataTypeConversion: '<S6>/Data Type Conversion2' */
      c_coder_B->DataTypeConversion2 = (uint8_T)(tmp < 0.0 ? (int32_T)(uint8_T)
        -(int8_T)(uint8_T)-tmp : (int32_T)(uint8_T)tmp);
    }

    /* Fcn: '<S8>/CL2' */
    tmp = c_coder_B->XT2 - c_coder_B->XB2;
    tmp_idx_1 = rt_powd_snf(tmp, 2.0);
    tmp_0 = c_coder_B->YT2 - c_coder_B->YB2;
    tmp = rt_powd_snf(tmp_0, 2.0);
    tmp_0 = c_coder_B->ZT2 - c_coder_B->ZB2;
    tmp_0 = rt_powd_snf(tmp_0, 2.0);
    tmp_idx_1 = (tmp_idx_1 + tmp) + tmp_0;
    if (tmp_idx_1 < 0.0) {
      tmp_idx_1 = -sqrt(-tmp_idx_1);
    } else {
      tmp_idx_1 = sqrt(tmp_idx_1);
    }

    /* Fcn: '<S8>/CL2' */
    c_coder_B->CL2 = tmp_idx_1;

    /* Sum: '<S8>/Add1' incorporates:
     *  Constant: '<S5>/Constant4'
     */
    c_coder_B->Add1 = c_coder_B->CL2 - 750.0;

    /* Product: '<S8>/Divide1' incorporates:
     *  Constant: '<S5>/Constant6'
     */
    c_coder_B->Divide1_a = c_coder_B->Add1 * 10.0;
    if (rtmIsMajorTimeStep(c_coder_M)) {
      /* Product: '<S6>/Divide2' incorporates:
       *  Constant: '<S6>/Constant9'
       */
      c_coder_B->Divide2 = c_coder_B->Divide1_a / 256.0;

      /* DataTypeConversion: '<S6>/Data Type Conversion24' */
      tmp = floor(c_coder_B->Divide2);
      if (rtIsNaN(tmp) || rtIsInf(tmp)) {
        tmp = 0.0;
      } else {
        tmp = fmod(tmp, 256.0);
      }

      /* DataTypeConversion: '<S6>/Data Type Conversion24' */
      c_coder_B->DataTypeConversion24 = (int8_T)(tmp < 0.0 ? (int32_T)(int8_T)
        -(int8_T)(uint8_T)-tmp : (int32_T)(int8_T)(uint8_T)tmp);

      /* DataTypeConversion: '<S6>/Data Type Conversion20' */
      c_coder_B->DataTypeConversion20 = (uint8_T)c_coder_B->DataTypeConversion24;

      /* DataTypeConversion: '<S6>/Data Type Conversion19' */
      tmp = floor(c_coder_B->Divide1_a);
      if (rtIsNaN(tmp) || rtIsInf(tmp)) {
        tmp = 0.0;
      } else {
        tmp = fmod(tmp, 256.0);
      }

      /* DataTypeConversion: '<S6>/Data Type Conversion19' */
      c_coder_B->DataTypeConversion19 = (uint8_T)(tmp < 0.0 ? (int32_T)(uint8_T)
        -(int8_T)(uint8_T)-tmp : (int32_T)(uint8_T)tmp);
    }

    /* Fcn: '<S8>/CL3' */
    tmp = c_coder_B->XT1 - c_coder_B->XB3;
    tmp_idx_1 = rt_powd_snf(tmp, 2.0);
    tmp_0 = c_coder_B->YT1 - c_coder_B->YB3;
    tmp = rt_powd_snf(tmp_0, 2.0);
    tmp_0 = c_coder_B->ZT1 - c_coder_B->ZB3;
    tmp_0 = rt_powd_snf(tmp_0, 2.0);
    tmp_idx_1 = (tmp_idx_1 + tmp) + tmp_0;
    if (tmp_idx_1 < 0.0) {
      tmp_idx_1 = -sqrt(-tmp_idx_1);
    } else {
      tmp_idx_1 = sqrt(tmp_idx_1);
    }

    /* Fcn: '<S8>/CL3' */
    c_coder_B->CL3 = tmp_idx_1;

    /* Sum: '<S8>/Add2' incorporates:
     *  Constant: '<S5>/Constant4'
     */
    c_coder_B->Add2 = c_coder_B->CL3 - 750.0;

    /* Product: '<S8>/Divide2' incorporates:
     *  Constant: '<S5>/Constant6'
     */
    c_coder_B->Divide2_f = c_coder_B->Add2 * 10.0;
    if (rtmIsMajorTimeStep(c_coder_M)) {
      /* Product: '<S6>/Divide3' incorporates:
       *  Constant: '<S6>/Constant16'
       */
      c_coder_B->Divide3 = c_coder_B->Divide2_f / 256.0;

      /* DataTypeConversion: '<S6>/Data Type Conversion25' */
      tmp = floor(c_coder_B->Divide3);
      if (rtIsNaN(tmp) || rtIsInf(tmp)) {
        tmp = 0.0;
      } else {
        tmp = fmod(tmp, 256.0);
      }

      /* DataTypeConversion: '<S6>/Data Type Conversion25' */
      c_coder_B->DataTypeConversion25 = (int8_T)(tmp < 0.0 ? (int32_T)(int8_T)
        -(int8_T)(uint8_T)-tmp : (int32_T)(int8_T)(uint8_T)tmp);

      /* DataTypeConversion: '<S6>/Data Type Conversion22' */
      c_coder_B->DataTypeConversion22 = (uint8_T)c_coder_B->DataTypeConversion25;

      /* DataTypeConversion: '<S6>/Data Type Conversion21' */
      tmp = floor(c_coder_B->Divide2_f);
      if (rtIsNaN(tmp) || rtIsInf(tmp)) {
        tmp = 0.0;
      } else {
        tmp = fmod(tmp, 256.0);
      }

      /* DataTypeConversion: '<S6>/Data Type Conversion21' */
      c_coder_B->DataTypeConversion21 = (uint8_T)(tmp < 0.0 ? (int32_T)(uint8_T)
        -(int8_T)(uint8_T)-tmp : (int32_T)(uint8_T)tmp);
    }

    /* Fcn: '<S8>/CL4' */
    tmp = c_coder_B->XT6 - c_coder_B->XB4;
    tmp_idx_1 = rt_powd_snf(tmp, 2.0);
    tmp_0 = c_coder_B->YT6 - c_coder_B->YB4;
    tmp = rt_powd_snf(tmp_0, 2.0);
    tmp_0 = c_coder_B->ZT6 - c_coder_B->ZB4;
    tmp_0 = rt_powd_snf(tmp_0, 2.0);
    tmp_idx_1 = (tmp_idx_1 + tmp) + tmp_0;
    if (tmp_idx_1 < 0.0) {
      tmp_idx_1 = -sqrt(-tmp_idx_1);
    } else {
      tmp_idx_1 = sqrt(tmp_idx_1);
    }

    /* Fcn: '<S8>/CL4' */
    c_coder_B->CL4 = tmp_idx_1;

    /* Sum: '<S8>/Add3' incorporates:
     *  Constant: '<S5>/Constant4'
     */
    c_coder_B->Add3 = c_coder_B->CL4 - 750.0;

    /* Product: '<S8>/Divide3' incorporates:
     *  Constant: '<S5>/Constant6'
     */
    c_coder_B->Divide3_f = c_coder_B->Add3 * 10.0;
    if (rtmIsMajorTimeStep(c_coder_M)) {
      /* Product: '<S6>/Divide5' incorporates:
       *  Constant: '<S6>/Constant18'
       */
      c_coder_B->Divide5_f = c_coder_B->Divide3_f / 256.0;

      /* DataTypeConversion: '<S6>/Data Type Conversion26' */
      tmp = floor(c_coder_B->Divide5_f);
      if (rtIsNaN(tmp) || rtIsInf(tmp)) {
        tmp = 0.0;
      } else {
        tmp = fmod(tmp, 256.0);
      }

      /* DataTypeConversion: '<S6>/Data Type Conversion26' */
      c_coder_B->DataTypeConversion26 = (int8_T)(tmp < 0.0 ? (int32_T)(int8_T)
        -(int8_T)(uint8_T)-tmp : (int32_T)(int8_T)(uint8_T)tmp);

      /* DataTypeConversion: '<S6>/Data Type Conversion7' */
      c_coder_B->DataTypeConversion7_i = (uint8_T)
        c_coder_B->DataTypeConversion26;

      /* DataTypeConversion: '<S6>/Data Type Conversion23' */
      tmp = floor(c_coder_B->Divide3_f);
      if (rtIsNaN(tmp) || rtIsInf(tmp)) {
        tmp = 0.0;
      } else {
        tmp = fmod(tmp, 256.0);
      }

      /* DataTypeConversion: '<S6>/Data Type Conversion23' */
      c_coder_B->DataTypeConversion23 = (uint8_T)(tmp < 0.0 ? (int32_T)(uint8_T)
        -(int8_T)(uint8_T)-tmp : (int32_T)(uint8_T)tmp);
    }

    /* Fcn: '<S8>/CL5' */
    tmp = c_coder_B->XT5 - c_coder_B->XB5;
    tmp_idx_1 = rt_powd_snf(tmp, 2.0);
    tmp_0 = c_coder_B->YT5 - c_coder_B->YB5;
    tmp = rt_powd_snf(tmp_0, 2.0);
    tmp_0 = c_coder_B->ZT5 - c_coder_B->ZB5;
    tmp_0 = rt_powd_snf(tmp_0, 2.0);
    tmp_idx_1 = (tmp_idx_1 + tmp) + tmp_0;
    if (tmp_idx_1 < 0.0) {
      tmp_idx_1 = -sqrt(-tmp_idx_1);
    } else {
      tmp_idx_1 = sqrt(tmp_idx_1);
    }

    /* Fcn: '<S8>/CL5' */
    c_coder_B->CL5 = tmp_idx_1;

    /* Sum: '<S8>/Add4' incorporates:
     *  Constant: '<S5>/Constant4'
     */
    c_coder_B->Add4 = c_coder_B->CL5 - 750.0;

    /* Product: '<S8>/Divide4' incorporates:
     *  Constant: '<S5>/Constant6'
     */
    c_coder_B->Divide4_h = c_coder_B->Add4 * 10.0;
    if (rtmIsMajorTimeStep(c_coder_M)) {
      /* Product: '<S6>/Divide6' incorporates:
       *  Constant: '<S6>/Constant21'
       */
      c_coder_B->Divide6 = c_coder_B->Divide4_h / 256.0;

      /* DataTypeConversion: '<S6>/Data Type Conversion27' */
      tmp = floor(c_coder_B->Divide6);
      if (rtIsNaN(tmp) || rtIsInf(tmp)) {
        tmp = 0.0;
      } else {
        tmp = fmod(tmp, 256.0);
      }

      /* DataTypeConversion: '<S6>/Data Type Conversion27' */
      c_coder_B->DataTypeConversion27 = (int8_T)(tmp < 0.0 ? (int32_T)(int8_T)
        -(int8_T)(uint8_T)-tmp : (int32_T)(int8_T)(uint8_T)tmp);

      /* DataTypeConversion: '<S6>/Data Type Conversion13' */
      c_coder_B->DataTypeConversion13 = (uint8_T)c_coder_B->DataTypeConversion27;

      /* DataTypeConversion: '<S6>/Data Type Conversion10' */
      tmp = floor(c_coder_B->Divide4_h);
      if (rtIsNaN(tmp) || rtIsInf(tmp)) {
        tmp = 0.0;
      } else {
        tmp = fmod(tmp, 256.0);
      }

      /* DataTypeConversion: '<S6>/Data Type Conversion10' */
      c_coder_B->DataTypeConversion10 = (uint8_T)(tmp < 0.0 ? (int32_T)(uint8_T)
        -(int8_T)(uint8_T)-tmp : (int32_T)(uint8_T)tmp);

      /* Outport: '<Root>/Out1' */
      out1[0] = c_coder_ConstB.DataTypeConversion1;
      out1[1] = c_coder_ConstB.DataTypeConversion;
      out1[2] = c_coder_ConstB.DataTypeConversion5;
      out1[3] = c_coder_ConstB.DataTypeConversion3;
      out1[4] = c_coder_ConstB.DataTypeConversion8;
      out1[5] = c_coder_ConstB.DataTypeConversion6;
      out1[6] = c_coder_ConstB.DataTypeConversion11;
      out1[7] = c_coder_ConstB.DataTypeConversion9;
      out1[8] = c_coder_ConstB.DataTypeConversion14;
      out1[9] = c_coder_ConstB.DataTypeConversion12;
      out1[10] = c_coder_ConstB.DataTypeConversion30;
      out1[11] = c_coder_ConstB.DataTypeConversion29;
      out1[12] = c_coder_ConstB.DataTypeConversion28;
      out1[13] = c_coder_B->DataTypeConversion17;
      out1[14] = c_coder_B->DataTypeConversion15;
      out1[15] = c_coder_B->DataTypeConversion4_e;
      out1[16] = c_coder_B->DataTypeConversion2;
      out1[17] = c_coder_B->DataTypeConversion20;
      out1[18] = c_coder_B->DataTypeConversion19;
      out1[19] = c_coder_B->DataTypeConversion22;
      out1[20] = c_coder_B->DataTypeConversion21;
      out1[21] = c_coder_B->DataTypeConversion7_i;
      out1[22] = c_coder_B->DataTypeConversion23;
      out1[23] = c_coder_B->DataTypeConversion13;
      out1[24] = c_coder_B->DataTypeConversion10;
    }

    /* Derivative: '<Root>/Derivative1' */
    if ((c_coder_DW->TimeStampA >= c_coder_M->Timing.t[0]) &&
        (c_coder_DW->TimeStampB >= c_coder_M->Timing.t[0])) {
      /* Derivative: '<Root>/Derivative1' */
      c_coder_B->Derivative1 = 0.0;
    } else {
      tmp_idx_1 = c_coder_DW->TimeStampA;
      lastU = &c_coder_DW->LastUAtTimeA;
      if (c_coder_DW->TimeStampA < c_coder_DW->TimeStampB) {
        if (c_coder_DW->TimeStampB < c_coder_M->Timing.t[0]) {
          tmp_idx_1 = c_coder_DW->TimeStampB;
          lastU = &c_coder_DW->LastUAtTimeB;
        }
      } else if (c_coder_DW->TimeStampA >= c_coder_M->Timing.t[0]) {
        tmp_idx_1 = c_coder_DW->TimeStampB;
        lastU = &c_coder_DW->LastUAtTimeB;
      }

      tmp_idx_1 = c_coder_M->Timing.t[0] - tmp_idx_1;

      /* Derivative: '<Root>/Derivative1' */
      c_coder_B->Derivative1 = (c_coder_B->posx_filt - *lastU) / tmp_idx_1;
    }

    /* End of Derivative: '<Root>/Derivative1' */

    /* Derivative: '<Root>/Derivative2' */
    if ((c_coder_DW->TimeStampA_c >= c_coder_M->Timing.t[0]) &&
        (c_coder_DW->TimeStampB_c >= c_coder_M->Timing.t[0])) {
      /* Derivative: '<Root>/Derivative2' */
      c_coder_B->Derivative2 = 0.0;
    } else {
      tmp_idx_1 = c_coder_DW->TimeStampA_c;
      lastU = &c_coder_DW->LastUAtTimeA_k;
      if (c_coder_DW->TimeStampA_c < c_coder_DW->TimeStampB_c) {
        if (c_coder_DW->TimeStampB_c < c_coder_M->Timing.t[0]) {
          tmp_idx_1 = c_coder_DW->TimeStampB_c;
          lastU = &c_coder_DW->LastUAtTimeB_o;
        }
      } else if (c_coder_DW->TimeStampA_c >= c_coder_M->Timing.t[0]) {
        tmp_idx_1 = c_coder_DW->TimeStampB_c;
        lastU = &c_coder_DW->LastUAtTimeB_o;
      }

      tmp_idx_1 = c_coder_M->Timing.t[0] - tmp_idx_1;

      /* Derivative: '<Root>/Derivative2' */
      c_coder_B->Derivative2 = (c_coder_B->Derivative1 - *lastU) / tmp_idx_1;
    }

    /* End of Derivative: '<Root>/Derivative2' */
    if (rtmIsMajorTimeStep(c_coder_M)) {
      /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator2' */
      c_coder_B->velx = c_coder_DW->DiscreteTimeIntegrator2_DSTATE;
    }

    /* DataTypeConversion: '<Root>/Cast2' incorporates:
     *  Inport: '<Root>/Inport2'
     */
    c_coder_B->accx = c_coder_U_Inport2;

    /* Gain: '<S2>/Gain5' */
    c_coder_B->Gain5 = 1000.0 * c_coder_B->accx;

    /* TransferFcn: '<Root>/Transfer Fcn7' */
    c_coder_B->accx_filt = 0.0;
    c_coder_B->accx_filt += (-0.62831853071795862) *
      c_coder_X->TransferFcn7_CSTATE;
    c_coder_B->accx_filt += 1.0 * c_coder_B->Gain5;

    /* TransferFcn: '<Root>/Transfer Fcn10' */
    c_coder_B->vrlx_filt = 0.0;
    c_coder_B->vrlx_filt += (-1.8849555921538759) *
      c_coder_X->TransferFcn10_CSTATE;
    c_coder_B->vrlx_filt += 1.0 * c_coder_B->velx;
    if (rtmIsMajorTimeStep(c_coder_M)) {
    }

    /* TransferFcn: '<Root>/Transfer Fcn2' */
    c_coder_B->TransferFcn2 = 0.0;
    c_coder_B->TransferFcn2 += 0.0 * c_coder_X->TransferFcn2_CSTATE[0];
    c_coder_B->TransferFcn2 += 62.831853071795862 *
      c_coder_X->TransferFcn2_CSTATE[1];
    if (rtmIsMajorTimeStep(c_coder_M)) {
    }

    /* Derivative: '<Root>/Derivative3' */
    if ((c_coder_DW->TimeStampA_j >= c_coder_M->Timing.t[0]) &&
        (c_coder_DW->TimeStampB_m >= c_coder_M->Timing.t[0])) {
      /* Derivative: '<Root>/Derivative3' */
      c_coder_B->Derivative3 = 0.0;
    } else {
      tmp_idx_1 = c_coder_DW->TimeStampA_j;
      lastU = &c_coder_DW->LastUAtTimeA_p;
      if (c_coder_DW->TimeStampA_j < c_coder_DW->TimeStampB_m) {
        if (c_coder_DW->TimeStampB_m < c_coder_M->Timing.t[0]) {
          tmp_idx_1 = c_coder_DW->TimeStampB_m;
          lastU = &c_coder_DW->LastUAtTimeB_oi;
        }
      } else if (c_coder_DW->TimeStampA_j >= c_coder_M->Timing.t[0]) {
        tmp_idx_1 = c_coder_DW->TimeStampB_m;
        lastU = &c_coder_DW->LastUAtTimeB_oi;
      }

      tmp_idx_1 = c_coder_M->Timing.t[0] - tmp_idx_1;

      /* Derivative: '<Root>/Derivative3' */
      c_coder_B->Derivative3 = (c_coder_B->Gain5 - *lastU) / tmp_idx_1;
    }

    /* End of Derivative: '<Root>/Derivative3' */
    if (rtmIsMajorTimeStep(c_coder_M)) {
      /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator3' */
      c_coder_B->DiscreteTimeIntegrator3 =
        c_coder_DW->DiscreteTimeIntegrator3_DSTATE;
    }

    /* TransferFcn: '<Root>/Transfer Fcn9' */
    c_coder_B->TransferFcn9 = 0.0;
    c_coder_B->TransferFcn9 += (-6.2831853071795862) *
      c_coder_X->TransferFcn9_CSTATE;
    c_coder_B->TransferFcn9 += 1.0 * c_coder_B->DiscreteTimeIntegrator3;

    /* Saturate: '<Root>/Saturation5' */
    tmp = c_coder_B->TransferFcn9;
    tmp_idx_1 = (-250.0);
    tmp_0 = 250.0;
    if (tmp > tmp_0) {
      /* Saturate: '<Root>/Saturation5' */
      c_coder_B->Saturation5 = tmp_0;
    } else if (tmp < tmp_idx_1) {
      /* Saturate: '<Root>/Saturation5' */
      c_coder_B->Saturation5 = tmp_idx_1;
    } else {
      /* Saturate: '<Root>/Saturation5' */
      c_coder_B->Saturation5 = tmp;
    }

    /* End of Saturate: '<Root>/Saturation5' */

    /* Sum: '<Root>/Sum3' incorporates:
     *  Constant: '<Root>/Constant2'
     */
    c_coder_B->Sum3 = c_coder_B->Saturation5 + 1100.0;

    /* DataTypeConversion: '<Root>/Cast' incorporates:
     *  Inport: '<Root>/Inport'
     */
    c_coder_B->accy = c_coder_U_Inport;

    /* DataTypeConversion: '<Root>/Cast1' incorporates:
     *  Inport: '<Root>/Inport1'
     */
    c_coder_B->accz = c_coder_U_Inport1;
    if (rtmIsMajorTimeStep(c_coder_M)) {
      /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator10' */
      c_coder_B->posy = c_coder_DW->DiscreteTimeIntegrator10_DSTATE;

      /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator9' */
      c_coder_B->posz = c_coder_DW->DiscreteTimeIntegrator9_DSTATE;

      /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator11' */
      c_coder_B->posx_a = c_coder_DW->DiscreteTimeIntegrator11_DSTATE;

      /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator7' */
      c_coder_B->vely = c_coder_DW->DiscreteTimeIntegrator7_DSTATE;

      /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator6' */
      c_coder_B->velz = c_coder_DW->DiscreteTimeIntegrator6_DSTATE;

      /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator8' */
      c_coder_B->velx_m = c_coder_DW->DiscreteTimeIntegrator8_DSTATE;

      /* Gain: '<Root>/Gain' */
      c_coder_B->Gain = 3.6 * c_coder_B->velx_m;

      /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
      c_coder_B->DiscreteTimeIntegrator =
        c_coder_DW->DiscreteTimeIntegrator_DSTATE;

      /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator1' */
      c_coder_B->DiscreteTimeIntegrator1 =
        c_coder_DW->DiscreteTimeIntegrator1_DSTATE;
    }

    /* Gain: '<S2>/Gain' */
    c_coder_B->Gain_i = 1000.0 * c_coder_B->accy;

    /* Gain: '<S2>/Gain1' */
    c_coder_B->Gain1 = 1000.0 * c_coder_B->accz;

    /* DataTypeConversion: '<Root>/Data Type Conversion3' incorporates:
     *  Inport: '<Root>/Inport2'
     */
    c_coder_B->DataTypeConversion3 = c_coder_U_Inport2;

    /* DataTypeConversion: '<Root>/Data Type Conversion4' incorporates:
     *  Inport: '<Root>/Inport'
     */
    c_coder_B->DataTypeConversion4 = c_coder_U_Inport;

    /* DataTypeConversion: '<Root>/Data Type Conversion5' incorporates:
     *  Inport: '<Root>/Inport1'
     */
    c_coder_B->DataTypeConversion5 = c_coder_U_Inport1;

    /* DataTypeConversion: '<Root>/Data Type Conversion6' incorporates:
     *  Inport: '<Root>/Inport5'
     */
    c_coder_B->DataTypeConversion6 = c_coder_U_Inport5;

    /* DataTypeConversion: '<Root>/Data Type Conversion7' incorporates:
     *  Inport: '<Root>/Inport3'
     */
    c_coder_B->DataTypeConversion7 = c_coder_U_Inport3;

    /* DataTypeConversion: '<Root>/Data Type Conversion8' incorporates:
     *  Inport: '<Root>/Inport4'
     */
    c_coder_B->DataTypeConversion8 = c_coder_U_Inport4;

    /* Saturate: '<Root>/Saturation3' */
    tmp = c_coder_B->Switch[1];
    tmp_idx_1 = (-15.0);
    tmp_0 = 15.0;
    if (tmp > tmp_0) {
      /* Saturate: '<Root>/Saturation3' */
      c_coder_B->Saturation3 = tmp_0;
    } else if (tmp < tmp_idx_1) {
      /* Saturate: '<Root>/Saturation3' */
      c_coder_B->Saturation3 = tmp_idx_1;
    } else {
      /* Saturate: '<Root>/Saturation3' */
      c_coder_B->Saturation3 = tmp;
    }

    /* End of Saturate: '<Root>/Saturation3' */

    /* TransferFcn: '<Root>/Transfer Fcn4' */
    c_coder_B->TransferFcn4 = 0.0;
    c_coder_B->TransferFcn4 += (-0.62831853071795862) *
      c_coder_X->TransferFcn4_CSTATE;
    c_coder_B->TransferFcn4 += 1.0 * c_coder_B->Gain1;

    /* TransferFcn: '<Root>/Transfer Fcn5' */
    c_coder_B->TransferFcn5 = 0.0;
    c_coder_B->TransferFcn5 += (-0.62831853071795862) *
      c_coder_X->TransferFcn5_CSTATE;
    c_coder_B->TransferFcn5 += 1.0 * c_coder_B->Gain_i;

    /* TransferFcn: '<Root>/Transfer Fcn6' */
    c_coder_B->TransferFcn6 = 0.0;
    c_coder_B->TransferFcn6 += (-1.8849555921538759) *
      c_coder_X->TransferFcn6_CSTATE;
    c_coder_B->TransferFcn6 += 1.0 * c_coder_B->DiscreteTimeIntegrator;

    /* TransferFcn: '<Root>/Transfer Fcn8' */
    c_coder_B->TransferFcn8 = 0.0;
    c_coder_B->TransferFcn8 += (-1.8849555921538759) *
      c_coder_X->TransferFcn8_CSTATE;
    c_coder_B->TransferFcn8 += 1.0 * c_coder_B->DiscreteTimeIntegrator1;
  }

  if (rtmIsMajorTimeStep(c_coder_M)) {
    real_T *lastU;
    if (rtmIsMajorTimeStep(c_coder_M)) {
      /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator5' */
      c_coder_DW->DiscreteTimeIntegrator5_DSTATE += 0.02 * c_coder_B->vrlx_filt;

      /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator4' */
      c_coder_DW->DiscreteTimeIntegrator4_DSTATE += 0.02 *
        c_coder_B->TransferFcn8;
    }

    /* Update for Derivative: '<Root>/Derivative1' */
    if (c_coder_DW->TimeStampA == (rtInf)) {
      c_coder_DW->TimeStampA = c_coder_M->Timing.t[0];
      lastU = &c_coder_DW->LastUAtTimeA;
    } else if (c_coder_DW->TimeStampB == (rtInf)) {
      c_coder_DW->TimeStampB = c_coder_M->Timing.t[0];
      lastU = &c_coder_DW->LastUAtTimeB;
    } else if (c_coder_DW->TimeStampA < c_coder_DW->TimeStampB) {
      c_coder_DW->TimeStampA = c_coder_M->Timing.t[0];
      lastU = &c_coder_DW->LastUAtTimeA;
    } else {
      c_coder_DW->TimeStampB = c_coder_M->Timing.t[0];
      lastU = &c_coder_DW->LastUAtTimeB;
    }

    *lastU = c_coder_B->posx_filt;

    /* End of Update for Derivative: '<Root>/Derivative1' */

    /* Update for Derivative: '<Root>/Derivative2' */
    if (c_coder_DW->TimeStampA_c == (rtInf)) {
      c_coder_DW->TimeStampA_c = c_coder_M->Timing.t[0];
      lastU = &c_coder_DW->LastUAtTimeA_k;
    } else if (c_coder_DW->TimeStampB_c == (rtInf)) {
      c_coder_DW->TimeStampB_c = c_coder_M->Timing.t[0];
      lastU = &c_coder_DW->LastUAtTimeB_o;
    } else if (c_coder_DW->TimeStampA_c < c_coder_DW->TimeStampB_c) {
      c_coder_DW->TimeStampA_c = c_coder_M->Timing.t[0];
      lastU = &c_coder_DW->LastUAtTimeA_k;
    } else {
      c_coder_DW->TimeStampB_c = c_coder_M->Timing.t[0];
      lastU = &c_coder_DW->LastUAtTimeB_o;
    }

    *lastU = c_coder_B->Derivative1;

    /* End of Update for Derivative: '<Root>/Derivative2' */
    if (rtmIsMajorTimeStep(c_coder_M)) {
      /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator2' */
      c_coder_DW->DiscreteTimeIntegrator2_DSTATE += 0.02 * c_coder_B->accx_filt;
    }

    /* Update for Derivative: '<Root>/Derivative3' */
    if (c_coder_DW->TimeStampA_j == (rtInf)) {
      c_coder_DW->TimeStampA_j = c_coder_M->Timing.t[0];
      lastU = &c_coder_DW->LastUAtTimeA_p;
    } else if (c_coder_DW->TimeStampB_m == (rtInf)) {
      c_coder_DW->TimeStampB_m = c_coder_M->Timing.t[0];
      lastU = &c_coder_DW->LastUAtTimeB_oi;
    } else if (c_coder_DW->TimeStampA_j < c_coder_DW->TimeStampB_m) {
      c_coder_DW->TimeStampA_j = c_coder_M->Timing.t[0];
      lastU = &c_coder_DW->LastUAtTimeA_p;
    } else {
      c_coder_DW->TimeStampB_m = c_coder_M->Timing.t[0];
      lastU = &c_coder_DW->LastUAtTimeB_oi;
    }

    *lastU = c_coder_B->Gain5;

    /* End of Update for Derivative: '<Root>/Derivative3' */
    if (rtmIsMajorTimeStep(c_coder_M)) {
      /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator3' */
      c_coder_DW->DiscreteTimeIntegrator3_DSTATE += 0.02 *
        c_coder_B->TransferFcn6;

      /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator10' */
      c_coder_DW->DiscreteTimeIntegrator10_DSTATE += 0.02 * c_coder_B->vely;

      /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator9' */
      c_coder_DW->DiscreteTimeIntegrator9_DSTATE += 0.02 * c_coder_B->velz;

      /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator11' */
      c_coder_DW->DiscreteTimeIntegrator11_DSTATE += 0.02 * c_coder_B->velx_m;

      /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator7' */
      c_coder_DW->DiscreteTimeIntegrator7_DSTATE += 0.02 * c_coder_B->accy;

      /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator6' */
      c_coder_DW->DiscreteTimeIntegrator6_DSTATE += 0.02 * c_coder_B->accz;

      /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator8' */
      c_coder_DW->DiscreteTimeIntegrator8_DSTATE += 0.02 * c_coder_B->accx;

      /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
      c_coder_DW->DiscreteTimeIntegrator_DSTATE += 0.02 *
        c_coder_B->TransferFcn4;

      /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator1' */
      c_coder_DW->DiscreteTimeIntegrator1_DSTATE += 0.02 *
        c_coder_B->TransferFcn5;
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(c_coder_M)) {
    rt_ertODEUpdateContinuousStates(&c_coder_M->solverInfo, c_coder_M,
      c_coder_U_Inport, c_coder_U_Inport1, c_coder_U_Inport2, c_coder_U_Inport3,
      c_coder_U_Inport4, c_coder_U_Inport5);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++c_coder_M->Timing.clockTick0;
    c_coder_M->Timing.t[0] = rtsiGetSolverStopTime(&c_coder_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.02s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.02, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      c_coder_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void c_coder_derivatives(RT_MODEL_c_coder_T *const c_coder_M)
{
  B_c_coder_T *c_coder_B = c_coder_M->blockIO;
  X_c_coder_T *c_coder_X = c_coder_M->contStates;
  XDot_c_coder_T *_rtXdot;
  _rtXdot = ((XDot_c_coder_T *) c_coder_M->derivs);

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn13' */
  _rtXdot->TransferFcn13_CSTATE = 0.0;
  _rtXdot->TransferFcn13_CSTATE += (-6.2831853071795862) *
    c_coder_X->TransferFcn13_CSTATE;
  _rtXdot->TransferFcn13_CSTATE += c_coder_B->posx;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn11' */
  _rtXdot->TransferFcn11_CSTATE = 0.0;
  _rtXdot->TransferFcn11_CSTATE += (-6.2831853071795862) *
    c_coder_X->TransferFcn11_CSTATE;
  _rtXdot->TransferFcn11_CSTATE += c_coder_B->DiscreteTimeIntegrator4;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn7' */
  _rtXdot->TransferFcn7_CSTATE = 0.0;
  _rtXdot->TransferFcn7_CSTATE += (-0.62831853071795862) *
    c_coder_X->TransferFcn7_CSTATE;
  _rtXdot->TransferFcn7_CSTATE += c_coder_B->Gain5;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn10' */
  _rtXdot->TransferFcn10_CSTATE = 0.0;
  _rtXdot->TransferFcn10_CSTATE += (-1.8849555921538759) *
    c_coder_X->TransferFcn10_CSTATE;
  _rtXdot->TransferFcn10_CSTATE += c_coder_B->velx;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn2' */
  _rtXdot->TransferFcn2_CSTATE[0] = 0.0;
  _rtXdot->TransferFcn2_CSTATE[0] += (-125.66370614359172) *
    c_coder_X->TransferFcn2_CSTATE[0];
  _rtXdot->TransferFcn2_CSTATE[1] = 0.0;
  _rtXdot->TransferFcn2_CSTATE[0] += (-62.831853071795862) *
    c_coder_X->TransferFcn2_CSTATE[1];
  _rtXdot->TransferFcn2_CSTATE[1] += c_coder_X->TransferFcn2_CSTATE[0];
  _rtXdot->TransferFcn2_CSTATE[0] += c_coder_B->accx;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn9' */
  _rtXdot->TransferFcn9_CSTATE = 0.0;
  _rtXdot->TransferFcn9_CSTATE += (-6.2831853071795862) *
    c_coder_X->TransferFcn9_CSTATE;
  _rtXdot->TransferFcn9_CSTATE += c_coder_B->DiscreteTimeIntegrator3;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn4' */
  _rtXdot->TransferFcn4_CSTATE = 0.0;
  _rtXdot->TransferFcn4_CSTATE += (-0.62831853071795862) *
    c_coder_X->TransferFcn4_CSTATE;
  _rtXdot->TransferFcn4_CSTATE += c_coder_B->Gain1;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn5' */
  _rtXdot->TransferFcn5_CSTATE = 0.0;
  _rtXdot->TransferFcn5_CSTATE += (-0.62831853071795862) *
    c_coder_X->TransferFcn5_CSTATE;
  _rtXdot->TransferFcn5_CSTATE += c_coder_B->Gain_i;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn6' */
  _rtXdot->TransferFcn6_CSTATE = 0.0;
  _rtXdot->TransferFcn6_CSTATE += (-1.8849555921538759) *
    c_coder_X->TransferFcn6_CSTATE;
  _rtXdot->TransferFcn6_CSTATE += c_coder_B->DiscreteTimeIntegrator;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn8' */
  _rtXdot->TransferFcn8_CSTATE = 0.0;
  _rtXdot->TransferFcn8_CSTATE += (-1.8849555921538759) *
    c_coder_X->TransferFcn8_CSTATE;
  _rtXdot->TransferFcn8_CSTATE += c_coder_B->DiscreteTimeIntegrator1;
}

/* Model initialize function */
void c_coder_initialize(RT_MODEL_c_coder_T *const c_coder_M, real_T
  *c_coder_U_Inport, real_T *c_coder_U_Inport1, real_T *c_coder_U_Inport2,
  real_T *c_coder_U_Inport3, real_T *c_coder_U_Inport4, real_T
  *c_coder_U_Inport5)
{
  DW_c_coder_T *c_coder_DW = c_coder_M->dwork;
  X_c_coder_T *c_coder_X = c_coder_M->contStates;
  B_c_coder_T *c_coder_B = c_coder_M->blockIO;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&c_coder_M->solverInfo, &c_coder_M->Timing.simTimeStep);
    rtsiSetTPtr(&c_coder_M->solverInfo, &rtmGetTPtr(c_coder_M));
    rtsiSetStepSizePtr(&c_coder_M->solverInfo, &c_coder_M->Timing.stepSize0);
    rtsiSetdXPtr(&c_coder_M->solverInfo, &c_coder_M->derivs);
    rtsiSetContStatesPtr(&c_coder_M->solverInfo, (real_T **)
                         &c_coder_M->contStates);
    rtsiSetNumContStatesPtr(&c_coder_M->solverInfo,
      &c_coder_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&c_coder_M->solverInfo,
      &c_coder_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&c_coder_M->solverInfo,
      &c_coder_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&c_coder_M->solverInfo,
      &c_coder_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&c_coder_M->solverInfo, (&rtmGetErrorStatus(c_coder_M)));
    rtsiSetRTModelPtr(&c_coder_M->solverInfo, c_coder_M);
  }

  rtsiSetSimTimeStep(&c_coder_M->solverInfo, MAJOR_TIME_STEP);
  c_coder_M->intgData.y = c_coder_M->odeY;
  c_coder_M->intgData.f[0] = c_coder_M->odeF[0];
  c_coder_M->intgData.f[1] = c_coder_M->odeF[1];
  c_coder_M->intgData.f[2] = c_coder_M->odeF[2];
  c_coder_M->contStates = ((X_c_coder_T *) c_coder_X);
  rtsiSetSolverData(&c_coder_M->solverInfo, (void *)&c_coder_M->intgData);
  rtsiSetSolverName(&c_coder_M->solverInfo,"ode3");
  rtmSetTPtr(c_coder_M, &c_coder_M->Timing.tArray[0]);
  c_coder_M->Timing.stepSize0 = 0.02;

  /* block I/O */
  (void) memset(((void *) c_coder_B), 0,
                sizeof(B_c_coder_T));

  /* states (continuous) */
  {
    (void) memset((void *)c_coder_X, 0,
                  sizeof(X_c_coder_T));
  }

  /* states (dwork) */
  (void) memset((void *)c_coder_DW, 0,
                sizeof(DW_c_coder_T));

  /* external inputs */
  *c_coder_U_Inport = 0.0;
  *c_coder_U_Inport1 = 0.0;
  *c_coder_U_Inport2 = 0.0;
  *c_coder_U_Inport3 = 0.0;
  *c_coder_U_Inport4 = 0.0;
  *c_coder_U_Inport5 = 0.0;

  /* external outputs */
  (void)memset(&out1[0], 0, 25U * sizeof(uint8_T));

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn13' */
  c_coder_X->TransferFcn13_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn11' */
  c_coder_X->TransferFcn11_CSTATE = 0.0;

  /* InitializeConditions for Derivative: '<Root>/Derivative1' */
  c_coder_DW->TimeStampA = (rtInf);
  c_coder_DW->TimeStampB = (rtInf);

  /* InitializeConditions for Derivative: '<Root>/Derivative2' */
  c_coder_DW->TimeStampA_c = (rtInf);
  c_coder_DW->TimeStampB_c = (rtInf);

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn7' */
  c_coder_X->TransferFcn7_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn10' */
  c_coder_X->TransferFcn10_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn2' */
  c_coder_X->TransferFcn2_CSTATE[0] = 0.0;
  c_coder_X->TransferFcn2_CSTATE[1] = 0.0;

  /* InitializeConditions for Derivative: '<Root>/Derivative3' */
  c_coder_DW->TimeStampA_j = (rtInf);
  c_coder_DW->TimeStampB_m = (rtInf);

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn9' */
  c_coder_X->TransferFcn9_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn4' */
  c_coder_X->TransferFcn4_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn5' */
  c_coder_X->TransferFcn5_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn6' */
  c_coder_X->TransferFcn6_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn8' */
  c_coder_X->TransferFcn8_CSTATE = 0.0;
}

/* Model terminate function */
void c_coder_terminate(RT_MODEL_c_coder_T *const c_coder_M)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(c_coder_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
