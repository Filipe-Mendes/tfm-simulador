/*
 * File: c_coder_private.h
 *
 * Code generated for Simulink model 'c_coder'.
 *
 * Model version                  : 8.148
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Tue Feb 27 18:39:06 2024
 *
 * Target selection: ert_shrlib.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_c_coder_private_h_
#define RTW_HEADER_c_coder_private_h_
#include "rtwtypes.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

extern real_T rt_powd_snf(real_T u0, real_T u1);

/* private model entry point functions */
extern void c_coder_derivatives(RT_MODEL_c_coder_T *const c_coder_M);

#endif                                 /* RTW_HEADER_c_coder_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
