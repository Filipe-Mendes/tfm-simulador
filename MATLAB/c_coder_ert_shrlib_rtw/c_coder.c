/*
 * File: c_coder.c
 *
 * Code generated for Simulink model 'c_coder'.
 *
 * Model version                  : 8.73
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Tue Nov 28 20:15:32 2023
 *
 * Target selection: ert_shrlib.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "c_coder.h"
#include "c_coder_private.h"

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si ,
  RT_MODEL_c_coder_T *const c_coder_M, real_T c_coder_U_Inport, real_T
  c_coder_U_Inport1, real_T c_coder_U_Inport2, real_T c_coder_U_Inport3, real_T
  c_coder_U_Inport5, uint8_T c_coder_Y_Out1[25])
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
               c_coder_U_Inport3, c_coder_U_Inport5, c_coder_Y_Out1);
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
               c_coder_U_Inport3, c_coder_U_Inport5, c_coder_Y_Out1);
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
                  c_coder_U_Inport3, real_T c_coder_U_Inport5, uint8_T
                  c_coder_Y_Out1[25])
{
  B_c_coder_T *c_coder_B = c_coder_M->blockIO;
  DW_c_coder_T *c_coder_DW = c_coder_M->dwork;
  X_c_coder_T *c_coder_X = c_coder_M->contStates;

  /* local block i/o variables */
  real_T rtb_velz;
  real_T rtb_vely;
  real_T rtb_velx;
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
    real_T Divide1;
    real_T Divide2;
    real_T Divide5;
    real_T rtb_CL4;
    real_T rtb_CL4_tmp;
    real_T rtb_Product5;
    real_T rtb_Product5_j;
    real_T rtb_Sum2;
    real_T rtb_Sum2_tmp;
    real_T rtb_ZB6;
    real_T rtb_posz;
    real_T rtb_posz_tmp;
    real_T tmp;
    real_T tmp_0;
    real_T tmp_1;
    real_T tmp_2;
    real_T tmp_3;
    real_T tmp_4;
    real_T tmp_5;
    real_T tmp_6;
    real_T tmp_7;
    real_T tmp_8;
    real_T u0;
    real_T *lastU;
    uint8_T rtb_DataTypeConversion15;
    uint8_T rtb_DataTypeConversion17;
    uint8_T rtb_DataTypeConversion19;
    uint8_T rtb_DataTypeConversion2;
    uint8_T rtb_DataTypeConversion20;
    uint8_T rtb_DataTypeConversion21;
    uint8_T rtb_DataTypeConversion22;
    uint8_T rtb_DataTypeConversion23;
    uint8_T rtb_DataTypeConversion4_o;
    uint8_T rtb_DataTypeConversion7_h;

    /* Switch: '<Root>/Switch' incorporates:
     *  Constant: '<Root>/Constant'
     *  Constant: '<S1>/Constant'
     *  Inport: '<Root>/Inport5'
     *  RelationalOperator: '<S1>/Compare'
     *  Sum: '<Root>/Sum2'
     */
    if (c_coder_U_Inport5 <= 180.0) {
      u0 = c_coder_U_Inport5;
    } else {
      u0 = c_coder_U_Inport5 - 360.0;
    }

    /* Gain: '<Root>/Gain3' */
    u0 *= (-1.0);

    /* Saturate: '<Root>/Saturation2' */
    if (u0 > 15.0) {
      /* Saturate: '<Root>/Saturation2' */
      c_coder_B->Saturation2 = 15.0;
    } else if (u0 < (-15.0)) {
      /* Saturate: '<Root>/Saturation2' */
      c_coder_B->Saturation2 = (-15.0);
    } else {
      /* Saturate: '<Root>/Saturation2' */
      c_coder_B->Saturation2 = u0;
    }

    /* End of Saturate: '<Root>/Saturation2' */

    /* Switch: '<Root>/Switch' incorporates:
     *  Constant: '<Root>/Constant'
     *  Constant: '<S1>/Constant'
     *  Inport: '<Root>/Inport3'
     *  RelationalOperator: '<S1>/Compare'
     *  Sum: '<Root>/Sum2'
     */
    if (c_coder_U_Inport3 <= 180.0) {
      u0 = c_coder_U_Inport3;
    } else {
      u0 = c_coder_U_Inport3 - 360.0;
    }

    /* Gain: '<Root>/Gain2' */
    u0 *= 1.0;

    /* Saturate: '<Root>/Saturation1' */
    if (u0 > 15.0) {
      /* Saturate: '<Root>/Saturation1' */
      c_coder_B->Saturation1 = 15.0;
    } else if (u0 < (-15.0)) {
      /* Saturate: '<Root>/Saturation1' */
      c_coder_B->Saturation1 = (-15.0);
    } else {
      /* Saturate: '<Root>/Saturation1' */
      c_coder_B->Saturation1 = u0;
    }

    /* End of Saturate: '<Root>/Saturation1' */
    if (rtmIsMajorTimeStep(c_coder_M)) {
      /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator5' */
      c_coder_B->posx = c_coder_DW->DiscreteTimeIntegrator5_DSTATE;
    }

    /* Product: '<S9>/Product5' incorporates:
     *  Constant: '<S9>/Constant4'
     *  Constant: '<S9>/Constant5'
     */
    rtb_Product5_j = c_coder_B->Saturation1 * 3.1415926535897931 / 180.0;

    /* Product: '<S8>/Product5' incorporates:
     *  Constant: '<S8>/Constant4'
     *  Constant: '<S8>/Constant5'
     */
    rtb_Product5 = c_coder_B->Saturation2 * 3.1415926535897931 / 180.0;

    /* Trigonometry: '<S6>/Trigonometric Function1' incorporates:
     *  Fcn: '<S7>/YT1'
     *  Fcn: '<S7>/YT4'
     */
    Divide2 = cos(rtb_Product5);

    /* Product: '<S6>/Product1' incorporates:
     *  Constant: '<S4>/Constant7'
     *  Trigonometry: '<S6>/Trigonometric Function1'
     */
    rtb_Sum2 = Divide2 * 180.0;

    /* TransferFcn: '<Root>/Transfer Fcn13' */
    rtb_ZB6 = (-6.2831853071795862) * c_coder_X->TransferFcn13_CSTATE + 1.0 *
      c_coder_B->posx;

    /* Saturate: '<Root>/Saturation6' */
    if (rtb_ZB6 > 250.0) {
      /* Saturate: '<Root>/Saturation6' */
      c_coder_B->posx_filt = 250.0;
    } else if (rtb_ZB6 < (-250.0)) {
      /* Saturate: '<Root>/Saturation6' */
      c_coder_B->posx_filt = (-250.0);
    } else {
      /* Saturate: '<Root>/Saturation6' */
      c_coder_B->posx_filt = rtb_ZB6;
    }

    /* End of Saturate: '<Root>/Saturation6' */

    /* Trigonometry: '<S6>/Trigonometric Function2' incorporates:
     *  Fcn: '<S7>/XT4'
     *  Fcn: '<S7>/ZT4'
     */
    rtb_posz = sin(rtb_Product5_j);

    /* Sum: '<S6>/Sum' incorporates:
     *  Product: '<S6>/Product2'
     *  Trigonometry: '<S6>/Trigonometric Function2'
     */
    rtb_ZB6 = rtb_Sum2 * rtb_posz + c_coder_B->posx_filt;
    if (rtmIsMajorTimeStep(c_coder_M)) {
      /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator4' */
      c_coder_B->DiscreteTimeIntegrator4 =
        c_coder_DW->DiscreteTimeIntegrator4_DSTATE;
    }

    /* TransferFcn: '<Root>/Transfer Fcn11' */
    rtb_CL4 = (-6.2831853071795862) * c_coder_X->TransferFcn11_CSTATE + 1.0 *
      c_coder_B->DiscreteTimeIntegrator4;

    /* Trigonometry: '<S6>/Trigonometric Function' incorporates:
     *  Fcn: '<S7>/XT4'
     *  Fcn: '<S7>/ZT4'
     */
    rtb_CL4_tmp = sin(rtb_Product5);

    /* Saturate: '<Root>/Saturation4' */
    if (rtb_CL4 > 250.0) {
      rtb_CL4 = 250.0;
    } else if (rtb_CL4 < (-250.0)) {
      rtb_CL4 = (-250.0);
    }

    /* End of Saturate: '<Root>/Saturation4' */

    /* Sum: '<S6>/Sum1' incorporates:
     *  Constant: '<S4>/Constant7'
     *  Product: '<S6>/Product'
     *  Trigonometry: '<S6>/Trigonometric Function'
     */
    rtb_CL4 += rtb_CL4_tmp * 180.0;

    /* Trigonometry: '<S6>/Trigonometric Function3' incorporates:
     *  Fcn: '<S7>/XT4'
     *  Fcn: '<S7>/ZT4'
     */
    rtb_Sum2_tmp = cos(rtb_Product5_j);

    /* Sum: '<S6>/Sum2' incorporates:
     *  Constant: '<Root>/Constant5'
     *  Constant: '<S4>/Constant5'
     *  Product: '<S6>/Product3'
     *  Trigonometry: '<S6>/Trigonometric Function3'
     */
    rtb_Sum2 = (1100.0 - rtb_Sum2 * rtb_Sum2_tmp) - 180.0;

    /* Fcn: '<S7>/XT4' incorporates:
     *  Constant: '<S4>/Constant2'
     *  Constant: '<S4>/Constant3'
     *  Fcn: '<S7>/YT1'
     *  Fcn: '<S7>/YT4'
     *  Fcn: '<S7>/ZT4'
     */
    u0 = sin(c_coder_ConstB.Product5);
    tmp = cos(c_coder_ConstB.Product5);
    Divide5 = 2.0 * 220.0 + 690.0;

    /* Fcn: '<S7>/XB6' incorporates:
     *  Constant: '<S4>/Constant'
     *  Constant: '<S4>/Constant1'
     *  Fcn: '<S7>/XB1'
     */
    tmp_0 = (2.0 * 1200.0 + 210.0) * 0.28867513459481287;

    /* Fcn: '<S7>/CL6' incorporates:
     *  Constant: '<S4>/Constant1'
     *  Constant: '<S4>/Constant3'
     *  Fcn: '<S7>/XB6'
     *  Fcn: '<S7>/XT4'
     *  Fcn: '<S7>/YB6'
     *  Fcn: '<S7>/YT4'
     *  Fcn: '<S7>/ZT4'
     */
    tmp = (rt_powd_snf((((rtb_CL4_tmp * rtb_posz * u0 + rtb_Sum2_tmp * tmp) *
                         0.16666666666666666 * 1.7320508075688772 * Divide5 -
                         (sin(rtb_Product5) * sin(rtb_Product5_j) * tmp +
                          -rtb_Sum2_tmp * u0) * 0.5 * 690.0) + rtb_ZB6) - tmp_0,
                       2.0) + rt_powd_snf(((0.16666666666666666 * Divide2 * u0 *
              1.7320508075688772 * Divide5 - 0.5 * Divide2 * tmp * 690.0) +
             rtb_CL4) - -0.5 * 210.0, 2.0)) + rt_powd_snf(((rtb_CL4_tmp *
      rtb_Sum2_tmp * u0 + -rtb_posz * tmp) * 0.16666666666666666 *
      1.7320508075688772 * Divide5 - (sin(rtb_Product5) * cos(rtb_Product5_j) *
      tmp + rtb_posz * u0) * 0.5 * 690.0) + rtb_Sum2, 2.0);
    if (tmp < 0.0) {
      tmp = -sqrt(-tmp);
    } else {
      tmp = sqrt(tmp);
    }

    /* End of Fcn: '<S7>/CL6' */

    /* Product: '<S7>/Divide5' incorporates:
     *  Constant: '<S4>/Constant4'
     *  Constant: '<S4>/Constant6'
     *  Sum: '<S7>/Add5'
     */
    Divide5 = (tmp - 750.0) * 10.0;
    if (rtmIsMajorTimeStep(c_coder_M)) {
      /* Product: '<S5>/Divide4' incorporates:
       *  Constant: '<S5>/Constant6'
       */
      rtb_posz = Divide5 / 256.0;

      /* DataTypeConversion: '<S5>/Data Type Conversion16' */
      tmp = floor(rtb_posz);
      if (rtIsNaN(tmp) || rtIsInf(tmp)) {
        tmp = 0.0;
      } else {
        tmp = fmod(tmp, 256.0);
      }

      /* DataTypeConversion: '<S5>/Data Type Conversion17' incorporates:
       *  DataTypeConversion: '<S5>/Data Type Conversion16'
       */
      rtb_DataTypeConversion17 = (uint8_T)(tmp < 0.0 ? (int32_T)(int8_T)-(int8_T)
        (uint8_T)-tmp : (int32_T)(int8_T)(uint8_T)tmp);

      /* DataTypeConversion: '<S5>/Data Type Conversion15' */
      tmp = floor(Divide5);
      if (rtIsNaN(tmp) || rtIsInf(tmp)) {
        tmp = 0.0;
      } else {
        tmp = fmod(tmp, 256.0);
      }

      rtb_DataTypeConversion15 = (uint8_T)(tmp < 0.0 ? (int32_T)(uint8_T)
        -(int8_T)(uint8_T)-tmp : (int32_T)(uint8_T)tmp);

      /* End of DataTypeConversion: '<S5>/Data Type Conversion15' */
    }

    /* Fcn: '<S7>/CL1' incorporates:
     *  Constant: '<S4>/Constant1'
     *  Constant: '<S4>/Constant2'
     *  Constant: '<S4>/Constant3'
     *  Fcn: '<S7>/XT3'
     *  Fcn: '<S7>/YB1'
     *  Fcn: '<S7>/YT3'
     *  Fcn: '<S7>/ZT3'
     */
    tmp = (rt_powd_snf((((sin(rtb_Product5) * sin(rtb_Product5_j) * sin
                          (c_coder_ConstB.Product5) + cos(rtb_Product5_j) * cos
                          (c_coder_ConstB.Product5)) * 0.16666666666666666 *
                         1.7320508075688772 * (2.0 * 220.0 + 690.0) + (sin
               (rtb_Product5) * sin(rtb_Product5_j) * cos
               (c_coder_ConstB.Product5) + -cos(rtb_Product5_j) * sin
               (c_coder_ConstB.Product5)) * 0.5 * 690.0) + rtb_ZB6) - tmp_0, 2.0)
           + rt_powd_snf(((0.16666666666666666 * cos(rtb_Product5) * sin
              (c_coder_ConstB.Product5) * 1.7320508075688772 * (2.0 * 220.0 +
               690.0) + 0.5 * cos(rtb_Product5) * cos(c_coder_ConstB.Product5) *
              690.0) + rtb_CL4) - 0.5 * 210.0, 2.0)) + rt_powd_snf(((sin
      (rtb_Product5) * cos(rtb_Product5_j) * sin(c_coder_ConstB.Product5) + -sin
      (rtb_Product5_j) * cos(c_coder_ConstB.Product5)) * 0.16666666666666666 *
      1.7320508075688772 * (2.0 * 220.0 + 690.0) + (sin(rtb_Product5) * cos
      (rtb_Product5_j) * cos(c_coder_ConstB.Product5) + sin(rtb_Product5_j) *
      sin(c_coder_ConstB.Product5)) * 0.5 * 690.0) + rtb_Sum2, 2.0);
    if (tmp < 0.0) {
      tmp = -sqrt(-tmp);
    } else {
      tmp = sqrt(tmp);
    }

    /* End of Fcn: '<S7>/CL1' */

    /* Product: '<S7>/Divide' incorporates:
     *  Constant: '<S4>/Constant4'
     *  Constant: '<S4>/Constant6'
     *  Sum: '<S7>/Add'
     */
    Divide5 = (tmp - 750.0) * 10.0;
    if (rtmIsMajorTimeStep(c_coder_M)) {
      /* Product: '<S5>/Divide1' incorporates:
       *  Constant: '<S5>/Constant7'
       */
      rtb_posz = Divide5 / 256.0;

      /* DataTypeConversion: '<S5>/Data Type Conversion18' */
      tmp = floor(rtb_posz);
      if (rtIsNaN(tmp) || rtIsInf(tmp)) {
        tmp = 0.0;
      } else {
        tmp = fmod(tmp, 256.0);
      }

      /* DataTypeConversion: '<S5>/Data Type Conversion4' incorporates:
       *  DataTypeConversion: '<S5>/Data Type Conversion18'
       */
      rtb_DataTypeConversion4_o = (uint8_T)(tmp < 0.0 ? (int32_T)(int8_T)
        -(int8_T)(uint8_T)-tmp : (int32_T)(int8_T)(uint8_T)tmp);

      /* DataTypeConversion: '<S5>/Data Type Conversion2' */
      tmp = floor(Divide5);
      if (rtIsNaN(tmp) || rtIsInf(tmp)) {
        tmp = 0.0;
      } else {
        tmp = fmod(tmp, 256.0);
      }

      rtb_DataTypeConversion2 = (uint8_T)(tmp < 0.0 ? (int32_T)(uint8_T)-(int8_T)
        (uint8_T)-tmp : (int32_T)(uint8_T)tmp);

      /* End of DataTypeConversion: '<S5>/Data Type Conversion2' */
    }

    /* Fcn: '<S7>/XT2' incorporates:
     *  Constant: '<S4>/Constant2'
     *  Constant: '<S4>/Constant3'
     *  Fcn: '<S7>/XT5'
     *  Fcn: '<S7>/YT2'
     *  Fcn: '<S7>/ZT2'
     */
    tmp = 690.0 - 220.0;
    Divide5 = 690.0 + 220.0;

    /* Fcn: '<S7>/YT2' incorporates:
     *  Fcn: '<S7>/YT1'
     */
    tmp_0 = 0.5 * cos(rtb_Product5) * cos(c_coder_ConstB.Product5);

    /* Fcn: '<S7>/ZT2' incorporates:
     *  Fcn: '<S7>/ZT1'
     */
    tmp_1 = (sin(rtb_Product5) * cos(rtb_Product5_j) * cos
             (c_coder_ConstB.Product5) + sin(rtb_Product5_j) * sin
             (c_coder_ConstB.Product5)) * 0.5;

    /* Fcn: '<S7>/XT2' incorporates:
     *  Fcn: '<S7>/XT5'
     */
    rtb_CL4_tmp = (sin(rtb_Product5) * sin(rtb_Product5_j) * sin
                   (c_coder_ConstB.Product5) + cos(rtb_Product5_j) * cos
                   (c_coder_ConstB.Product5)) * 0.16666666666666666 *
      1.7320508075688772 * tmp;

    /* Fcn: '<S7>/XB2' incorporates:
     *  Constant: '<S4>/Constant'
     *  Constant: '<S4>/Constant1'
     *  Fcn: '<S7>/XB5'
     */
    rtb_Sum2_tmp = (1200.0 - 210.0) * -0.28867513459481287;

    /* Fcn: '<S7>/YT2' incorporates:
     *  Fcn: '<S7>/YT5'
     */
    tmp_5 = 0.16666666666666666 * cos(rtb_Product5) * sin
      (c_coder_ConstB.Product5) * 1.7320508075688772 * tmp;
    tmp_6 = tmp_0 * Divide5;

    /* Fcn: '<S7>/YB2' incorporates:
     *  Constant: '<S4>/Constant'
     *  Constant: '<S4>/Constant1'
     *  Fcn: '<S7>/YB5'
     */
    tmp_7 = 1200.0 + 210.0;

    /* Fcn: '<S7>/ZT2' incorporates:
     *  Fcn: '<S7>/ZT5'
     */
    tmp *= (sin(rtb_Product5) * cos(rtb_Product5_j) * sin
            (c_coder_ConstB.Product5) + -sin(rtb_Product5_j) * cos
            (c_coder_ConstB.Product5)) * 0.16666666666666666 *
      1.7320508075688772;
    tmp_8 = tmp_1 * Divide5;

    /* Fcn: '<S7>/CL2' incorporates:
     *  Fcn: '<S7>/XB2'
     *  Fcn: '<S7>/XT2'
     *  Fcn: '<S7>/YB2'
     *  Fcn: '<S7>/YT2'
     *  Fcn: '<S7>/ZT2'
     */
    rtb_posz = (rt_powd_snf((((sin(rtb_Product5) * sin(rtb_Product5_j) * cos
      (c_coder_ConstB.Product5) + -cos(rtb_Product5_j) * sin
      (c_coder_ConstB.Product5)) / 2.0 * Divide5 + rtb_CL4_tmp) + rtb_ZB6) -
      rtb_Sum2_tmp, 2.0) + rt_powd_snf(((tmp_5 + tmp_6) + rtb_CL4) - tmp_7 * 0.5,
      2.0)) + rt_powd_snf((tmp + tmp_8) + rtb_Sum2, 2.0);
    if (rtb_posz < 0.0) {
      rtb_posz = -sqrt(-rtb_posz);
    } else {
      rtb_posz = sqrt(rtb_posz);
    }

    /* End of Fcn: '<S7>/CL2' */

    /* Product: '<S7>/Divide1' incorporates:
     *  Constant: '<S4>/Constant4'
     *  Constant: '<S4>/Constant6'
     *  Sum: '<S7>/Add1'
     */
    Divide1 = (rtb_posz - 750.0) * 10.0;
    if (rtmIsMajorTimeStep(c_coder_M)) {
      /* Product: '<S5>/Divide2' incorporates:
       *  Constant: '<S5>/Constant9'
       */
      rtb_posz = Divide1 / 256.0;

      /* DataTypeConversion: '<S5>/Data Type Conversion24' */
      rtb_posz = floor(rtb_posz);
      if (rtIsNaN(rtb_posz) || rtIsInf(rtb_posz)) {
        rtb_posz = 0.0;
      } else {
        rtb_posz = fmod(rtb_posz, 256.0);
      }

      /* DataTypeConversion: '<S5>/Data Type Conversion20' incorporates:
       *  DataTypeConversion: '<S5>/Data Type Conversion24'
       */
      rtb_DataTypeConversion20 = (uint8_T)(rtb_posz < 0.0 ? (int32_T)(int8_T)
        -(int8_T)(uint8_T)-rtb_posz : (int32_T)(int8_T)(uint8_T)rtb_posz);

      /* DataTypeConversion: '<S5>/Data Type Conversion19' */
      rtb_posz = floor(Divide1);
      if (rtIsNaN(rtb_posz) || rtIsInf(rtb_posz)) {
        rtb_posz = 0.0;
      } else {
        rtb_posz = fmod(rtb_posz, 256.0);
      }

      rtb_DataTypeConversion19 = (uint8_T)(rtb_posz < 0.0 ? (int32_T)(uint8_T)
        -(int8_T)(uint8_T)-rtb_posz : (int32_T)(uint8_T)rtb_posz);

      /* End of DataTypeConversion: '<S5>/Data Type Conversion19' */
    }

    /* Fcn: '<S7>/XT1' incorporates:
     *  Constant: '<S4>/Constant2'
     *  Constant: '<S4>/Constant3'
     *  Fcn: '<S7>/XT5'
     *  Fcn: '<S7>/XT6'
     *  Fcn: '<S7>/YT1'
     *  Fcn: '<S7>/YT6'
     *  Fcn: '<S7>/ZT1'
     */
    rtb_posz_tmp = 2.0 * 690.0 + 220.0;
    rtb_posz = rtb_posz_tmp;
    tmp_2 = (sin(rtb_Product5) * sin(rtb_Product5_j) * sin
             (c_coder_ConstB.Product5) + cos(rtb_Product5_j) * cos
             (c_coder_ConstB.Product5)) * -0.16666666666666666 *
      1.7320508075688772 * rtb_posz;
    Divide1 = (sin(rtb_Product5) * sin(rtb_Product5_j) * cos
               (c_coder_ConstB.Product5) + -cos(rtb_Product5_j) * sin
               (c_coder_ConstB.Product5)) * 0.5;
    tmp_3 = Divide1 * 220.0;

    /* Fcn: '<S7>/XB3' incorporates:
     *  Constant: '<S4>/Constant'
     *  Constant: '<S4>/Constant1'
     *  Fcn: '<S7>/XB4'
     */
    tmp_4 = (2.0 * 210.0 + 1200.0) * -0.28867513459481287;

    /* Fcn: '<S7>/YT1' incorporates:
     *  Constant: '<S4>/Constant2'
     *  Fcn: '<S7>/YT6'
     */
    tmp_0 *= 220.0;

    /* Fcn: '<S7>/ZT1' incorporates:
     *  Constant: '<S4>/Constant2'
     *  Fcn: '<S7>/ZT6'
     */
    rtb_Product5_j = (sin(rtb_Product5) * cos(rtb_Product5_j) * sin
                      (c_coder_ConstB.Product5) + -sin(rtb_Product5_j) * cos
                      (c_coder_ConstB.Product5)) * -0.16666666666666666 *
      1.7320508075688772 * rtb_posz;
    tmp_1 *= 220.0;

    /* Fcn: '<S7>/CL3' incorporates:
     *  Constant: '<S4>/Constant'
     *  Fcn: '<S7>/XB3'
     *  Fcn: '<S7>/XT1'
     *  Fcn: '<S7>/YB3'
     *  Fcn: '<S7>/YT1'
     *  Fcn: '<S7>/ZT1'
     */
    u0 = (rt_powd_snf(((-0.16666666666666666 * Divide2 * u0 * 1.7320508075688772
                        * rtb_posz + tmp_0) + rtb_CL4) - 0.5 * 1200.0, 2.0) +
          rt_powd_snf(((tmp_2 + tmp_3) + rtb_ZB6) - tmp_4, 2.0)) + rt_powd_snf
      ((rtb_Product5_j + tmp_1) + rtb_Sum2, 2.0);
    if (u0 < 0.0) {
      u0 = -sqrt(-u0);
    } else {
      u0 = sqrt(u0);
    }

    /* End of Fcn: '<S7>/CL3' */

    /* Product: '<S7>/Divide2' incorporates:
     *  Constant: '<S4>/Constant4'
     *  Constant: '<S4>/Constant6'
     *  Sum: '<S7>/Add2'
     */
    Divide2 = (u0 - 750.0) * 10.0;
    if (rtmIsMajorTimeStep(c_coder_M)) {
      /* Product: '<S5>/Divide3' incorporates:
       *  Constant: '<S5>/Constant16'
       */
      rtb_posz = Divide2 / 256.0;

      /* DataTypeConversion: '<S5>/Data Type Conversion25' */
      u0 = floor(rtb_posz);
      if (rtIsNaN(u0) || rtIsInf(u0)) {
        u0 = 0.0;
      } else {
        u0 = fmod(u0, 256.0);
      }

      /* DataTypeConversion: '<S5>/Data Type Conversion22' incorporates:
       *  DataTypeConversion: '<S5>/Data Type Conversion25'
       */
      rtb_DataTypeConversion22 = (uint8_T)(u0 < 0.0 ? (int32_T)(int8_T)-(int8_T)
        (uint8_T)-u0 : (int32_T)(int8_T)(uint8_T)u0);

      /* DataTypeConversion: '<S5>/Data Type Conversion21' */
      u0 = floor(Divide2);
      if (rtIsNaN(u0) || rtIsInf(u0)) {
        u0 = 0.0;
      } else {
        u0 = fmod(u0, 256.0);
      }

      rtb_DataTypeConversion21 = (uint8_T)(u0 < 0.0 ? (int32_T)(uint8_T)-(int8_T)
        (uint8_T)-u0 : (int32_T)(uint8_T)u0);

      /* End of DataTypeConversion: '<S5>/Data Type Conversion21' */
    }

    /* Fcn: '<S7>/CL4' incorporates:
     *  Constant: '<S4>/Constant'
     *  Fcn: '<S7>/XT6'
     *  Fcn: '<S7>/YB4'
     *  Fcn: '<S7>/YT6'
     *  Fcn: '<S7>/ZT6'
     */
    u0 = (rt_powd_snf(((-0.16666666666666666 * cos(rtb_Product5) * sin
                        (c_coder_ConstB.Product5) * 1.7320508075688772 *
                        rtb_posz_tmp - tmp_0) + rtb_CL4) - -0.5 * 1200.0, 2.0) +
          rt_powd_snf(((tmp_2 - tmp_3) + rtb_ZB6) - tmp_4, 2.0)) + rt_powd_snf
      ((rtb_Product5_j - tmp_1) + rtb_Sum2, 2.0);
    if (u0 < 0.0) {
      u0 = -sqrt(-u0);
    } else {
      u0 = sqrt(u0);
    }

    /* End of Fcn: '<S7>/CL4' */

    /* Product: '<S7>/Divide3' incorporates:
     *  Constant: '<S4>/Constant4'
     *  Constant: '<S4>/Constant6'
     *  Sum: '<S7>/Add3'
     */
    rtb_Product5 = (u0 - 750.0) * 10.0;
    if (rtmIsMajorTimeStep(c_coder_M)) {
      /* Product: '<S5>/Divide5' incorporates:
       *  Constant: '<S5>/Constant18'
       */
      rtb_posz = rtb_Product5 / 256.0;

      /* DataTypeConversion: '<S5>/Data Type Conversion26' */
      u0 = floor(rtb_posz);
      if (rtIsNaN(u0) || rtIsInf(u0)) {
        u0 = 0.0;
      } else {
        u0 = fmod(u0, 256.0);
      }

      /* DataTypeConversion: '<S5>/Data Type Conversion7' incorporates:
       *  DataTypeConversion: '<S5>/Data Type Conversion26'
       */
      rtb_DataTypeConversion7_h = (uint8_T)(u0 < 0.0 ? (int32_T)(int8_T)-(int8_T)
        (uint8_T)-u0 : (int32_T)(int8_T)(uint8_T)u0);

      /* DataTypeConversion: '<S5>/Data Type Conversion23' */
      u0 = floor(rtb_Product5);
      if (rtIsNaN(u0) || rtIsInf(u0)) {
        u0 = 0.0;
      } else {
        u0 = fmod(u0, 256.0);
      }

      rtb_DataTypeConversion23 = (uint8_T)(u0 < 0.0 ? (int32_T)(uint8_T)-(int8_T)
        (uint8_T)-u0 : (int32_T)(uint8_T)u0);

      /* End of DataTypeConversion: '<S5>/Data Type Conversion23' */
    }

    /* Fcn: '<S7>/CL5' incorporates:
     *  Fcn: '<S7>/XT5'
     *  Fcn: '<S7>/YB5'
     *  Fcn: '<S7>/YT5'
     *  Fcn: '<S7>/ZT5'
     */
    u0 = (rt_powd_snf(((rtb_CL4_tmp - Divide1 * Divide5) + rtb_ZB6) -
                      rtb_Sum2_tmp, 2.0) + rt_powd_snf(((tmp_5 - tmp_6) +
            rtb_CL4) - tmp_7 * -0.5, 2.0)) + rt_powd_snf((tmp - tmp_8) +
      rtb_Sum2, 2.0);
    if (u0 < 0.0) {
      u0 = -sqrt(-u0);
    } else {
      u0 = sqrt(u0);
    }

    /* End of Fcn: '<S7>/CL5' */

    /* Product: '<S7>/Divide4' incorporates:
     *  Constant: '<S4>/Constant4'
     *  Constant: '<S4>/Constant6'
     *  Sum: '<S7>/Add4'
     */
    rtb_Sum2 = (u0 - 750.0) * 10.0;
    if (rtmIsMajorTimeStep(c_coder_M)) {
      /* Product: '<S5>/Divide6' incorporates:
       *  Constant: '<S5>/Constant21'
       */
      rtb_posz = rtb_Sum2 / 256.0;

      /* Outport: '<Root>/Out1' */
      c_coder_Y_Out1[0] = c_coder_ConstB.DataTypeConversion1;
      c_coder_Y_Out1[1] = c_coder_ConstB.DataTypeConversion;
      c_coder_Y_Out1[2] = c_coder_ConstB.DataTypeConversion5;
      c_coder_Y_Out1[3] = c_coder_ConstB.DataTypeConversion3;
      c_coder_Y_Out1[4] = c_coder_ConstB.DataTypeConversion8;
      c_coder_Y_Out1[5] = c_coder_ConstB.DataTypeConversion6;
      c_coder_Y_Out1[6] = c_coder_ConstB.DataTypeConversion11;
      c_coder_Y_Out1[7] = c_coder_ConstB.DataTypeConversion9;
      c_coder_Y_Out1[8] = c_coder_ConstB.DataTypeConversion14;
      c_coder_Y_Out1[9] = c_coder_ConstB.DataTypeConversion12;
      c_coder_Y_Out1[10] = c_coder_ConstB.DataTypeConversion30;
      c_coder_Y_Out1[11] = c_coder_ConstB.DataTypeConversion29;
      c_coder_Y_Out1[12] = c_coder_ConstB.DataTypeConversion28;
      c_coder_Y_Out1[13] = rtb_DataTypeConversion17;
      c_coder_Y_Out1[14] = rtb_DataTypeConversion15;
      c_coder_Y_Out1[15] = rtb_DataTypeConversion4_o;
      c_coder_Y_Out1[16] = rtb_DataTypeConversion2;
      c_coder_Y_Out1[17] = rtb_DataTypeConversion20;
      c_coder_Y_Out1[18] = rtb_DataTypeConversion19;
      c_coder_Y_Out1[19] = rtb_DataTypeConversion22;
      c_coder_Y_Out1[20] = rtb_DataTypeConversion21;
      c_coder_Y_Out1[21] = rtb_DataTypeConversion7_h;
      c_coder_Y_Out1[22] = rtb_DataTypeConversion23;

      /* DataTypeConversion: '<S5>/Data Type Conversion27' */
      u0 = floor(rtb_posz);
      if (rtIsNaN(u0) || rtIsInf(u0)) {
        u0 = 0.0;
      } else {
        u0 = fmod(u0, 256.0);
      }

      /* Outport: '<Root>/Out1' incorporates:
       *  DataTypeConversion: '<S5>/Data Type Conversion13'
       *  DataTypeConversion: '<S5>/Data Type Conversion27'
       */
      c_coder_Y_Out1[23] = (uint8_T)(u0 < 0.0 ? (int32_T)(int8_T)-(int8_T)
        (uint8_T)-u0 : (int32_T)(int8_T)(uint8_T)u0);

      /* DataTypeConversion: '<S5>/Data Type Conversion10' */
      u0 = floor(rtb_Sum2);
      if (rtIsNaN(u0) || rtIsInf(u0)) {
        u0 = 0.0;
      } else {
        u0 = fmod(u0, 256.0);
      }

      /* Outport: '<Root>/Out1' incorporates:
       *  DataTypeConversion: '<S5>/Data Type Conversion10'
       */
      c_coder_Y_Out1[24] = (uint8_T)(u0 < 0.0 ? (int32_T)(uint8_T)-(int8_T)
        (uint8_T)-u0 : (int32_T)(uint8_T)u0);

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

    /* Derivative: '<Root>/Derivative3' incorporates:
     *  Derivative: '<Root>/Derivative1'
     *  Derivative: '<Root>/Derivative2'
     */
    u0 = c_coder_M->Timing.t[0];
    if ((c_coder_DW->TimeStampA >= u0) && (c_coder_DW->TimeStampB >= u0)) {
      /* Derivative: '<Root>/Derivative3' */
      c_coder_B->Derivative3 = 0.0;
    } else {
      rtb_posz = c_coder_DW->TimeStampA;
      lastU = &c_coder_DW->LastUAtTimeA;
      if (c_coder_DW->TimeStampA < c_coder_DW->TimeStampB) {
        if (c_coder_DW->TimeStampB < u0) {
          rtb_posz = c_coder_DW->TimeStampB;
          lastU = &c_coder_DW->LastUAtTimeB;
        }
      } else if (c_coder_DW->TimeStampA >= u0) {
        rtb_posz = c_coder_DW->TimeStampB;
        lastU = &c_coder_DW->LastUAtTimeB;
      }

      /* Derivative: '<Root>/Derivative3' */
      c_coder_B->Derivative3 = (c_coder_B->Gain5 - *lastU) / (u0 - rtb_posz);
    }

    /* End of Derivative: '<Root>/Derivative3' */
    if (rtmIsMajorTimeStep(c_coder_M)) {
    }

    /* TransferFcn: '<Root>/Transfer Fcn2' */
    c_coder_B->TransferFcn2 = 0.0;
    c_coder_B->TransferFcn2 += 0.0 * c_coder_X->TransferFcn2_CSTATE[0];
    c_coder_B->TransferFcn2 += 62.831853071795862 *
      c_coder_X->TransferFcn2_CSTATE[1];
    if (rtmIsMajorTimeStep(c_coder_M)) {
    }

    /* DataTypeConversion: '<Root>/Cast' incorporates:
     *  Inport: '<Root>/Inport'
     */
    c_coder_B->accy = c_coder_U_Inport;

    /* DataTypeConversion: '<Root>/Cast1' incorporates:
     *  Inport: '<Root>/Inport1'
     */
    c_coder_B->accz = c_coder_U_Inport1;
    if (rtmIsMajorTimeStep(c_coder_M)) {
      /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator9' */
      rtb_posz = c_coder_DW->DiscreteTimeIntegrator9_DSTATE;

      /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator6' */
      rtb_velz = c_coder_DW->DiscreteTimeIntegrator6_DSTATE;

      /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator7' */
      rtb_vely = c_coder_DW->DiscreteTimeIntegrator7_DSTATE;

      /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator8' */
      rtb_velx = c_coder_DW->DiscreteTimeIntegrator8_DSTATE;

      /* Gain: '<Root>/Gain' */
      rtb_Sum2 = 3.6 * rtb_velx;

      /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator11' */
      rtb_Sum2 = c_coder_DW->DiscreteTimeIntegrator11_DSTATE;

      /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator10' */
      rtb_ZB6 = c_coder_DW->DiscreteTimeIntegrator10_DSTATE;
    }

    /* Gain: '<S2>/Gain1' */
    c_coder_B->Gain1 = 1000.0 * c_coder_B->accz;

    /* TransferFcn: '<Root>/Transfer Fcn4' */
    c_coder_B->TransferFcn4 = 0.0;
    c_coder_B->TransferFcn4 += (-0.62831853071795862) *
      c_coder_X->TransferFcn4_CSTATE;
    c_coder_B->TransferFcn4 += 1.0 * c_coder_B->Gain1;

    /* Gain: '<S2>/Gain' */
    c_coder_B->Gain = 1000.0 * c_coder_B->accy;

    /* TransferFcn: '<Root>/Transfer Fcn5' */
    c_coder_B->TransferFcn5 = 0.0;
    c_coder_B->TransferFcn5 += (-0.62831853071795862) *
      c_coder_X->TransferFcn5_CSTATE;
    c_coder_B->TransferFcn5 += 1.0 * c_coder_B->Gain;

    /* Derivative: '<Root>/Derivative1' */
    if ((c_coder_DW->TimeStampA_n >= u0) && (c_coder_DW->TimeStampB_g >= u0)) {
      /* Derivative: '<Root>/Derivative1' */
      c_coder_B->Derivative1 = 0.0;
    } else {
      rtb_posz = c_coder_DW->TimeStampA_n;
      lastU = &c_coder_DW->LastUAtTimeA_j;
      if (c_coder_DW->TimeStampA_n < c_coder_DW->TimeStampB_g) {
        if (c_coder_DW->TimeStampB_g < u0) {
          rtb_posz = c_coder_DW->TimeStampB_g;
          lastU = &c_coder_DW->LastUAtTimeB_h;
        }
      } else if (c_coder_DW->TimeStampA_n >= u0) {
        rtb_posz = c_coder_DW->TimeStampB_g;
        lastU = &c_coder_DW->LastUAtTimeB_h;
      }

      /* Derivative: '<Root>/Derivative1' */
      c_coder_B->Derivative1 = (c_coder_B->posx_filt - *lastU) / (u0 - rtb_posz);
    }

    /* Derivative: '<Root>/Derivative2' */
    if ((c_coder_DW->TimeStampA_c >= u0) && (c_coder_DW->TimeStampB_c >= u0)) {
      /* Derivative: '<Root>/Derivative2' */
      c_coder_B->Derivative2 = 0.0;
    } else {
      rtb_posz = c_coder_DW->TimeStampA_c;
      lastU = &c_coder_DW->LastUAtTimeA_k;
      if (c_coder_DW->TimeStampA_c < c_coder_DW->TimeStampB_c) {
        if (c_coder_DW->TimeStampB_c < u0) {
          rtb_posz = c_coder_DW->TimeStampB_c;
          lastU = &c_coder_DW->LastUAtTimeB_o;
        }
      } else if (c_coder_DW->TimeStampA_c >= u0) {
        rtb_posz = c_coder_DW->TimeStampB_c;
        lastU = &c_coder_DW->LastUAtTimeB_o;
      }

      /* Derivative: '<Root>/Derivative2' */
      c_coder_B->Derivative2 = (c_coder_B->Derivative1 - *lastU) / (u0 -
        rtb_posz);
    }

    if (rtmIsMajorTimeStep(c_coder_M)) {
      /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator3' */
      c_coder_B->DiscreteTimeIntegrator3 =
        c_coder_DW->DiscreteTimeIntegrator3_DSTATE;

      /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
      c_coder_B->DiscreteTimeIntegrator =
        c_coder_DW->DiscreteTimeIntegrator_DSTATE;

      /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator1' */
      c_coder_B->DiscreteTimeIntegrator1 =
        c_coder_DW->DiscreteTimeIntegrator1_DSTATE;
    }

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
    if (rtmIsMajorTimeStep(c_coder_M)) {
    }
  }

  if (rtmIsMajorTimeStep(c_coder_M)) {
    real_T *lastU;
    if (rtmIsMajorTimeStep(c_coder_M)) {
      /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator5' */
      c_coder_DW->DiscreteTimeIntegrator5_DSTATE += 0.02 * c_coder_B->vrlx_filt;

      /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator4' */
      c_coder_DW->DiscreteTimeIntegrator4_DSTATE += 0.02 *
        c_coder_B->TransferFcn8;

      /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator2' */
      c_coder_DW->DiscreteTimeIntegrator2_DSTATE += 0.02 * c_coder_B->accx_filt;
    }

    /* Update for Derivative: '<Root>/Derivative3' */
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

    *lastU = c_coder_B->Gain5;

    /* End of Update for Derivative: '<Root>/Derivative3' */
    if (rtmIsMajorTimeStep(c_coder_M)) {
      /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator9' */
      c_coder_DW->DiscreteTimeIntegrator9_DSTATE += 0.02 * rtb_velz;

      /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator6' */
      c_coder_DW->DiscreteTimeIntegrator6_DSTATE += 0.02 * c_coder_B->accz;

      /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator7' */
      c_coder_DW->DiscreteTimeIntegrator7_DSTATE += 0.02 * c_coder_B->accy;

      /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator8' */
      c_coder_DW->DiscreteTimeIntegrator8_DSTATE += 0.02 * c_coder_B->accx;

      /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator11' */
      c_coder_DW->DiscreteTimeIntegrator11_DSTATE += 0.02 * rtb_velx;

      /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator10' */
      c_coder_DW->DiscreteTimeIntegrator10_DSTATE += 0.02 * rtb_vely;
    }

    /* Update for Derivative: '<Root>/Derivative1' */
    if (c_coder_DW->TimeStampA_n == (rtInf)) {
      c_coder_DW->TimeStampA_n = c_coder_M->Timing.t[0];
      lastU = &c_coder_DW->LastUAtTimeA_j;
    } else if (c_coder_DW->TimeStampB_g == (rtInf)) {
      c_coder_DW->TimeStampB_g = c_coder_M->Timing.t[0];
      lastU = &c_coder_DW->LastUAtTimeB_h;
    } else if (c_coder_DW->TimeStampA_n < c_coder_DW->TimeStampB_g) {
      c_coder_DW->TimeStampA_n = c_coder_M->Timing.t[0];
      lastU = &c_coder_DW->LastUAtTimeA_j;
    } else {
      c_coder_DW->TimeStampB_g = c_coder_M->Timing.t[0];
      lastU = &c_coder_DW->LastUAtTimeB_h;
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
      /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator3' */
      c_coder_DW->DiscreteTimeIntegrator3_DSTATE += 0.02 *
        c_coder_B->TransferFcn6;

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
      c_coder_U_Inport5, c_coder_Y_Out1);

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

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn4' */
  _rtXdot->TransferFcn4_CSTATE = 0.0;
  _rtXdot->TransferFcn4_CSTATE += (-0.62831853071795862) *
    c_coder_X->TransferFcn4_CSTATE;
  _rtXdot->TransferFcn4_CSTATE += c_coder_B->Gain1;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn5' */
  _rtXdot->TransferFcn5_CSTATE = 0.0;
  _rtXdot->TransferFcn5_CSTATE += (-0.62831853071795862) *
    c_coder_X->TransferFcn5_CSTATE;
  _rtXdot->TransferFcn5_CSTATE += c_coder_B->Gain;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn9' */
  _rtXdot->TransferFcn9_CSTATE = 0.0;
  _rtXdot->TransferFcn9_CSTATE += (-6.2831853071795862) *
    c_coder_X->TransferFcn9_CSTATE;
  _rtXdot->TransferFcn9_CSTATE += c_coder_B->DiscreteTimeIntegrator3;

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
void c_coder_initialize(RT_MODEL_c_coder_T *const c_coder_M)
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

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn13' */
  c_coder_X->TransferFcn13_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn11' */
  c_coder_X->TransferFcn11_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn7' */
  c_coder_X->TransferFcn7_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn10' */
  c_coder_X->TransferFcn10_CSTATE = 0.0;

  /* InitializeConditions for Derivative: '<Root>/Derivative3' */
  c_coder_DW->TimeStampA = (rtInf);
  c_coder_DW->TimeStampB = (rtInf);

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn2' */
  c_coder_X->TransferFcn2_CSTATE[0] = 0.0;
  c_coder_X->TransferFcn2_CSTATE[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn4' */
  c_coder_X->TransferFcn4_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn5' */
  c_coder_X->TransferFcn5_CSTATE = 0.0;

  /* InitializeConditions for Derivative: '<Root>/Derivative1' */
  c_coder_DW->TimeStampA_n = (rtInf);
  c_coder_DW->TimeStampB_g = (rtInf);

  /* InitializeConditions for Derivative: '<Root>/Derivative2' */
  c_coder_DW->TimeStampA_c = (rtInf);
  c_coder_DW->TimeStampB_c = (rtInf);

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn9' */
  c_coder_X->TransferFcn9_CSTATE = 0.0;

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
