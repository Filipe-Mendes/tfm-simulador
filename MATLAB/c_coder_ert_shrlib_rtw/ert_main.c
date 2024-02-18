/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'c_coder'.
 *
 * Model version                  : 8.145
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Wed Feb 14 05:36:51 2024
 *
 * Target selection: ert_shrlib.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include <stddef.h>
#include <stdio.h>            /* This example main program uses printf/fflush */
#include "c_coder.h"                   /* Model's header file */

static RT_MODEL_c_coder_T c_coder_M_;
static RT_MODEL_c_coder_T *const c_coder_MPtr = &c_coder_M_;/* Real-time model */
static B_c_coder_T c_coder_B;          /* Observable signals */
static DW_c_coder_T c_coder_DW;        /* Observable states */
static X_c_coder_T c_coder_X;          /* Observable continuous states */

/* '<Root>/Inport' */
static real_T c_coder_U_Inport;

/* '<Root>/Inport1' */
static real_T c_coder_U_Inport1;

/* '<Root>/Inport2' */
static real_T c_coder_U_Inport2;

/* '<Root>/Inport3' */
static real_T c_coder_U_Inport3;

/* '<Root>/Inport4' */
static real_T c_coder_U_Inport4;

/* '<Root>/Inport5' */
static real_T c_coder_U_Inport5;

/*
 * Associating rt_OneStep with a real-time clock or interrupt service routine
 * is what makes the generated code "real-time".  The function rt_OneStep is
 * always associated with the base rate of the model.  Subrates are managed
 * by the base rate from inside the generated code.  Enabling/disabling
 * interrupts and floating point context switches are target specific.  This
 * example code indicates where these should take place relative to executing
 * the generated code step function.  Overrun behavior should be tailored to
 * your application needs.  This example simply sets an error status in the
 * real-time model and returns from rt_OneStep.
 */
void rt_OneStep(RT_MODEL_c_coder_T *const c_coder_M);
void rt_OneStep(RT_MODEL_c_coder_T *const c_coder_M)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(c_coder_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model for base rate */
  c_coder_step(c_coder_M, c_coder_U_Inport, c_coder_U_Inport1, c_coder_U_Inport2,
               c_coder_U_Inport3, c_coder_U_Inport4, c_coder_U_Inport5);

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

/*
 * The example "main" function illustrates what is required by your
 * application code to initialize, execute, and terminate the generated code.
 * Attaching rt_OneStep to a real-time clock is target specific.  This example
 * illustrates how you do this relative to initializing the model.
 */
int_T main(int_T argc, const char *argv[])
{
  RT_MODEL_c_coder_T *const c_coder_M = c_coder_MPtr;

  /* Unused arguments */
  (void)(argc);
  (void)(argv);

  /* Pack model data into RTM */
  c_coder_M->blockIO = &c_coder_B;
  c_coder_M->dwork = &c_coder_DW;
  c_coder_M->contStates = &c_coder_X;

  /* Initialize model */
  c_coder_initialize(c_coder_M, &c_coder_U_Inport, &c_coder_U_Inport1,
                     &c_coder_U_Inport2, &c_coder_U_Inport3, &c_coder_U_Inport4,
                     &c_coder_U_Inport5);

  /* Simulating the model step behavior (in non real-time) to
   *  simulate model behavior at stop time.
   */
  while ((rtmGetErrorStatus(c_coder_M) == (NULL)) && !rtmGetStopRequested
         (c_coder_M)) {
    rt_OneStep(c_coder_M);
  }

  /* Disable rt_OneStep here */
  /* Terminate model */
  c_coder_terminate(c_coder_M);
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
