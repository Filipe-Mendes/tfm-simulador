/*
 * File: c_coder.h
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

#ifndef RTW_HEADER_c_coder_h_
#define RTW_HEADER_c_coder_h_
#include <math.h>
#include <string.h>
#ifndef c_coder_COMMON_INCLUDES_
#define c_coder_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* c_coder_COMMON_INCLUDES_ */

#include "c_coder_types.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Saturation2;                  /* '<Root>/Saturation2' */
  real_T Saturation1;                  /* '<Root>/Saturation1' */
  real_T posx;                         /* '<Root>/Discrete-Time Integrator5' */
  real_T posx_filt;                    /* '<Root>/Saturation6' */
  real_T DiscreteTimeIntegrator4;      /* '<Root>/Discrete-Time Integrator4' */
  real_T accx;                         /* '<Root>/Cast2' */
  real_T Gain5;                        /* '<S2>/Gain5' */
  real_T accx_filt;                    /* '<Root>/Transfer Fcn7' */
  real_T velx;                         /* '<Root>/Discrete-Time Integrator2' */
  real_T vrlx_filt;                    /* '<Root>/Transfer Fcn10' */
  real_T Derivative3;                  /* '<Root>/Derivative3' */
  real_T TransferFcn2;                 /* '<Root>/Transfer Fcn2' */
  real_T accy;                         /* '<Root>/Cast' */
  real_T accz;                         /* '<Root>/Cast1' */
  real_T Gain1;                        /* '<S2>/Gain1' */
  real_T TransferFcn4;                 /* '<Root>/Transfer Fcn4' */
  real_T Gain;                         /* '<S2>/Gain' */
  real_T TransferFcn5;                 /* '<Root>/Transfer Fcn5' */
  real_T Derivative1;                  /* '<Root>/Derivative1' */
  real_T Derivative2;                  /* '<Root>/Derivative2' */
  real_T DiscreteTimeIntegrator3;      /* '<Root>/Discrete-Time Integrator3' */
  real_T DiscreteTimeIntegrator;       /* '<Root>/Discrete-Time Integrator' */
  real_T TransferFcn6;                 /* '<Root>/Transfer Fcn6' */
  real_T DiscreteTimeIntegrator1;      /* '<Root>/Discrete-Time Integrator1' */
  real_T TransferFcn8;                 /* '<Root>/Transfer Fcn8' */
} B_c_coder_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T DiscreteTimeIntegrator5_DSTATE;/* '<Root>/Discrete-Time Integrator5' */
  real_T DiscreteTimeIntegrator4_DSTATE;/* '<Root>/Discrete-Time Integrator4' */
  real_T DiscreteTimeIntegrator2_DSTATE;/* '<Root>/Discrete-Time Integrator2' */
  real_T DiscreteTimeIntegrator9_DSTATE;/* '<Root>/Discrete-Time Integrator9' */
  real_T DiscreteTimeIntegrator6_DSTATE;/* '<Root>/Discrete-Time Integrator6' */
  real_T DiscreteTimeIntegrator7_DSTATE;/* '<Root>/Discrete-Time Integrator7' */
  real_T DiscreteTimeIntegrator8_DSTATE;/* '<Root>/Discrete-Time Integrator8' */
  real_T DiscreteTimeIntegrator11_DSTATE;/* '<Root>/Discrete-Time Integrator11' */
  real_T DiscreteTimeIntegrator10_DSTATE;/* '<Root>/Discrete-Time Integrator10' */
  real_T DiscreteTimeIntegrator3_DSTATE;/* '<Root>/Discrete-Time Integrator3' */
  real_T DiscreteTimeIntegrator_DSTATE;/* '<Root>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator1_DSTATE;/* '<Root>/Discrete-Time Integrator1' */
  real_T TimeStampA;                   /* '<Root>/Derivative3' */
  real_T LastUAtTimeA;                 /* '<Root>/Derivative3' */
  real_T TimeStampB;                   /* '<Root>/Derivative3' */
  real_T LastUAtTimeB;                 /* '<Root>/Derivative3' */
  real_T TimeStampA_n;                 /* '<Root>/Derivative1' */
  real_T LastUAtTimeA_j;               /* '<Root>/Derivative1' */
  real_T TimeStampB_g;                 /* '<Root>/Derivative1' */
  real_T LastUAtTimeB_h;               /* '<Root>/Derivative1' */
  real_T TimeStampA_c;                 /* '<Root>/Derivative2' */
  real_T LastUAtTimeA_k;               /* '<Root>/Derivative2' */
  real_T TimeStampB_c;                 /* '<Root>/Derivative2' */
  real_T LastUAtTimeB_o;               /* '<Root>/Derivative2' */
} DW_c_coder_T;

/* Continuous states (default storage) */
typedef struct {
  real_T TransferFcn13_CSTATE;         /* '<Root>/Transfer Fcn13' */
  real_T TransferFcn11_CSTATE;         /* '<Root>/Transfer Fcn11' */
  real_T TransferFcn7_CSTATE;          /* '<Root>/Transfer Fcn7' */
  real_T TransferFcn10_CSTATE;         /* '<Root>/Transfer Fcn10' */
  real_T TransferFcn2_CSTATE[2];       /* '<Root>/Transfer Fcn2' */
  real_T TransferFcn4_CSTATE;          /* '<Root>/Transfer Fcn4' */
  real_T TransferFcn5_CSTATE;          /* '<Root>/Transfer Fcn5' */
  real_T TransferFcn9_CSTATE;          /* '<Root>/Transfer Fcn9' */
  real_T TransferFcn6_CSTATE;          /* '<Root>/Transfer Fcn6' */
  real_T TransferFcn8_CSTATE;          /* '<Root>/Transfer Fcn8' */
} X_c_coder_T;

/* State derivatives (default storage) */
typedef struct {
  real_T TransferFcn13_CSTATE;         /* '<Root>/Transfer Fcn13' */
  real_T TransferFcn11_CSTATE;         /* '<Root>/Transfer Fcn11' */
  real_T TransferFcn7_CSTATE;          /* '<Root>/Transfer Fcn7' */
  real_T TransferFcn10_CSTATE;         /* '<Root>/Transfer Fcn10' */
  real_T TransferFcn2_CSTATE[2];       /* '<Root>/Transfer Fcn2' */
  real_T TransferFcn4_CSTATE;          /* '<Root>/Transfer Fcn4' */
  real_T TransferFcn5_CSTATE;          /* '<Root>/Transfer Fcn5' */
  real_T TransferFcn9_CSTATE;          /* '<Root>/Transfer Fcn9' */
  real_T TransferFcn6_CSTATE;          /* '<Root>/Transfer Fcn6' */
  real_T TransferFcn8_CSTATE;          /* '<Root>/Transfer Fcn8' */
} XDot_c_coder_T;

/* State disabled  */
typedef struct {
  boolean_T TransferFcn13_CSTATE;      /* '<Root>/Transfer Fcn13' */
  boolean_T TransferFcn11_CSTATE;      /* '<Root>/Transfer Fcn11' */
  boolean_T TransferFcn7_CSTATE;       /* '<Root>/Transfer Fcn7' */
  boolean_T TransferFcn10_CSTATE;      /* '<Root>/Transfer Fcn10' */
  boolean_T TransferFcn2_CSTATE[2];    /* '<Root>/Transfer Fcn2' */
  boolean_T TransferFcn4_CSTATE;       /* '<Root>/Transfer Fcn4' */
  boolean_T TransferFcn5_CSTATE;       /* '<Root>/Transfer Fcn5' */
  boolean_T TransferFcn9_CSTATE;       /* '<Root>/Transfer Fcn9' */
  boolean_T TransferFcn6_CSTATE;       /* '<Root>/Transfer Fcn6' */
  boolean_T TransferFcn8_CSTATE;       /* '<Root>/Transfer Fcn8' */
} XDis_c_coder_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T Gain4;                  /* '<Root>/Gain4' */
  const real_T Saturation;             /* '<Root>/Saturation' */
  const real_T Product5;               /* '<S10>/Product5' */
  const real_T Constant3;              /* '<Root>/Constant3' */
  const real_T Constant4;              /* '<Root>/Constant4' */
  const uint8_T DataTypeConversion;    /* '<S5>/Data Type Conversion' */
  const uint8_T DataTypeConversion1;   /* '<S5>/Data Type Conversion1' */
  const uint8_T DataTypeConversion11;  /* '<S5>/Data Type Conversion11' */
  const uint8_T DataTypeConversion12;  /* '<S5>/Data Type Conversion12' */
  const uint8_T DataTypeConversion14;  /* '<S5>/Data Type Conversion14' */
  const uint8_T DataTypeConversion28;  /* '<S5>/Data Type Conversion28' */
  const uint8_T DataTypeConversion29;  /* '<S5>/Data Type Conversion29' */
  const uint8_T DataTypeConversion3;   /* '<S5>/Data Type Conversion3' */
  const uint8_T DataTypeConversion30;  /* '<S5>/Data Type Conversion30' */
  const uint8_T DataTypeConversion5;   /* '<S5>/Data Type Conversion5' */
  const uint8_T DataTypeConversion6;   /* '<S5>/Data Type Conversion6' */
  const uint8_T DataTypeConversion8;   /* '<S5>/Data Type Conversion8' */
  const uint8_T DataTypeConversion9;   /* '<S5>/Data Type Conversion9' */
} ConstB_c_coder_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Real-time Model Data Structure */
struct tag_RTM_c_coder_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  B_c_coder_T *blockIO;
  X_c_coder_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[11];
  real_T odeF[3][11];
  ODE3_IntgData intgData;
  DW_c_coder_T *dwork;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

extern const ConstB_c_coder_T c_coder_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void c_coder_initialize(RT_MODEL_c_coder_T *const c_coder_M);
extern void c_coder_step(RT_MODEL_c_coder_T *const c_coder_M, real_T
  c_coder_U_Inport, real_T c_coder_U_Inport1, real_T c_coder_U_Inport2, real_T
  c_coder_U_Inport3, real_T c_coder_U_Inport5, uint8_T c_coder_Y_Out1[25]);
extern void c_coder_terminate(RT_MODEL_c_coder_T *const c_coder_M);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'c_coder'
 * '<S1>'   : 'c_coder/Compare To Constant'
 * '<S2>'   : 'c_coder/Convert m to mm'
 * '<S3>'   : 'c_coder/Subsystem'
 * '<S4>'   : 'c_coder/Subsystem/Cinemática Inversa Plataforma 6Dof'
 * '<S5>'   : 'c_coder/Subsystem/Escrever 20.01 a 20.06 UNIDRIVE SP ModBus TCP//IP'
 * '<S6>'   : 'c_coder/Subsystem/Cinemática Inversa Plataforma 6Dof/Cinematica aux'
 * '<S7>'   : 'c_coder/Subsystem/Cinemática Inversa Plataforma 6Dof/Cinematica Inversa'
 * '<S8>'   : 'c_coder/Subsystem/Cinemática Inversa Plataforma 6Dof/Deg=>Rad'
 * '<S9>'   : 'c_coder/Subsystem/Cinemática Inversa Plataforma 6Dof/Deg=>Rad1'
 * '<S10>'  : 'c_coder/Subsystem/Cinemática Inversa Plataforma 6Dof/Deg=>Rad2'
 */
#endif                                 /* RTW_HEADER_c_coder_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
