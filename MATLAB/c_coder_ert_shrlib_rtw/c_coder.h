/*
 * File: c_coder.h
 *
 * Code generated for Simulink model 'c_coder'.
 *
 * Model version                  : 8.153
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Tue Jul 23 17:45:33 2024
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

/* user code (top of header file) */
extern void wrapper_c_coder_step(RT_MODEL_c_coder_T *const c_coder_M,
  real_T c_coder_U_Inport,
  real_T c_coder_U_Inport1,
  real_T c_coder_U_Inport2,
  real_T c_coder_U_Inport3,
  real_T c_coder_U_Inport4,
  real_T c_coder_U_Inport5);
extern void wrapper_c_coder_initialize(RT_MODEL_c_coder_T *const c_coder_M,
  real_T c_coder_U_Inport,
  real_T c_coder_U_Inport1,
  real_T c_coder_U_Inport2,
  real_T c_coder_U_Inport3,
  real_T c_coder_U_Inport4,
  real_T c_coder_U_Inport5);
extern uint8_T *getOutput();

/* Block signals (default storage) */
typedef struct {
  real_T Sum2[3];                      /* '<Root>/Sum2' */
  real_T Switch[3];                    /* '<Root>/Switch' */
  real_T Gain3;                        /* '<Root>/Gain3' */
  real_T Saturation2;                  /* '<Root>/Saturation2' */
  real_T Product5;                     /* '<S9>/Product5' */
  real_T TrigonometricFunction1;       /* '<S7>/Trigonometric Function1' */
  real_T z;                            /* '<S7>/Product1' */
  real_T Gain2;                        /* '<Root>/Gain2' */
  real_T Saturation1;                  /* '<Root>/Saturation1' */
  real_T Product5_e;                   /* '<S10>/Product5' */
  real_T TrigonometricFunction2;       /* '<S7>/Trigonometric Function2' */
  real_T x;                            /* '<S7>/Product2' */
  real_T posx;                         /* '<Root>/Discrete-Time Integrator5' */
  real_T TransferFcn13;                /* '<Root>/Transfer Fcn13' */
  real_T posx_filt;                    /* '<Root>/Saturation6' */
  real_T Gain6;                        /* '<S4>/Gain6' */
  real_T Sum;                          /* '<S7>/Sum' */
  real_T TrigonometricFunction;        /* '<S7>/Trigonometric Function' */
  real_T y;                            /* '<S7>/Product' */
  real_T DiscreteTimeIntegrator4;      /* '<Root>/Discrete-Time Integrator4' */
  real_T TransferFcn11;                /* '<Root>/Transfer Fcn11' */
  real_T Saturation4;                  /* '<Root>/Saturation4' */
  real_T Gain1;                        /* '<S4>/Gain1' */
  real_T Sum1;                         /* '<S7>/Sum1' */
  real_T TrigonometricFunction3;       /* '<S7>/Trigonometric Function3' */
  real_T z_n;                          /* '<S7>/Product3' */
  real_T Sum2_n;                       /* '<S7>/Sum2' */
  real_T XT1;                          /* '<S8>/XT1' */
  real_T YT1;                          /* '<S8>/YT1' */
  real_T ZT1;                          /* '<S8>/ZT1' */
  real_T XT2;                          /* '<S8>/XT2' */
  real_T YT2;                          /* '<S8>/YT2' */
  real_T ZT2;                          /* '<S8>/ZT2' */
  real_T XT3;                          /* '<S8>/XT3' */
  real_T YT3;                          /* '<S8>/YT3' */
  real_T ZT3;                          /* '<S8>/ZT3' */
  real_T XT4;                          /* '<S8>/XT4' */
  real_T YT4;                          /* '<S8>/YT4' */
  real_T ZT4;                          /* '<S8>/ZT4' */
  real_T XT5;                          /* '<S8>/XT5' */
  real_T YT5;                          /* '<S8>/YT5' */
  real_T ZT5;                          /* '<S8>/ZT5' */
  real_T XT6;                          /* '<S8>/XT6' */
  real_T YT6;                          /* '<S8>/YT6' */
  real_T ZT6;                          /* '<S8>/ZT6' */
  real_T XB1;                          /* '<S8>/XB1' */
  real_T YB1;                          /* '<S8>/YB1' */
  real_T ZB1;                          /* '<S8>/ZB1' */
  real_T XB2;                          /* '<S8>/XB2' */
  real_T YB2;                          /* '<S8>/YB2' */
  real_T ZB2;                          /* '<S8>/ZB2' */
  real_T XB3;                          /* '<S8>/XB3' */
  real_T YB3;                          /* '<S8>/YB3' */
  real_T ZB3;                          /* '<S8>/ZB3' */
  real_T XB4;                          /* '<S8>/XB4' */
  real_T YB4;                          /* '<S8>/YB4' */
  real_T ZB4;                          /* '<S8>/ZB4' */
  real_T XB5;                          /* '<S8>/XB5' */
  real_T YB5;                          /* '<S8>/YB5' */
  real_T ZB5;                          /* '<S8>/ZB5' */
  real_T XB6;                          /* '<S8>/XB6' */
  real_T YB6;                          /* '<S8>/YB6' */
  real_T ZB6;                          /* '<S8>/ZB6' */
  real_T CL6;                          /* '<S8>/CL6' */
  real_T Add5;                         /* '<S8>/Add5' */
  real_T Divide5;                      /* '<S8>/Divide5' */
  real_T Divide4;                      /* '<S6>/Divide4' */
  real_T CL1;                          /* '<S8>/CL1' */
  real_T Add;                          /* '<S8>/Add' */
  real_T Divide;                       /* '<S8>/Divide' */
  real_T Divide1;                      /* '<S6>/Divide1' */
  real_T CL2;                          /* '<S8>/CL2' */
  real_T Add1;                         /* '<S8>/Add1' */
  real_T Divide1_a;                    /* '<S8>/Divide1' */
  real_T Divide2;                      /* '<S6>/Divide2' */
  real_T CL3;                          /* '<S8>/CL3' */
  real_T Add2;                         /* '<S8>/Add2' */
  real_T Divide2_f;                    /* '<S8>/Divide2' */
  real_T Divide3;                      /* '<S6>/Divide3' */
  real_T CL4;                          /* '<S8>/CL4' */
  real_T Add3;                         /* '<S8>/Add3' */
  real_T Divide3_f;                    /* '<S8>/Divide3' */
  real_T Divide5_f;                    /* '<S6>/Divide5' */
  real_T CL5;                          /* '<S8>/CL5' */
  real_T Add4;                         /* '<S8>/Add4' */
  real_T Divide4_h;                    /* '<S8>/Divide4' */
  real_T Divide6;                      /* '<S6>/Divide6' */
  real_T Derivative1;                  /* '<Root>/Derivative1' */
  real_T Derivative2;                  /* '<Root>/Derivative2' */
  real_T accx;                         /* '<Root>/Cast2' */
  real_T Gain5;                        /* '<S2>/Gain5' */
  real_T accx_filt;                    /* '<Root>/Transfer Fcn7' */
  real_T velx;                         /* '<Root>/Discrete-Time Integrator2' */
  real_T vrlx_filt;                    /* '<Root>/Transfer Fcn10' */
  real_T TransferFcn2;                 /* '<Root>/Transfer Fcn2' */
  real_T Derivative3;                  /* '<Root>/Derivative3' */
  real_T DiscreteTimeIntegrator3;      /* '<Root>/Discrete-Time Integrator3' */
  real_T TransferFcn9;                 /* '<Root>/Transfer Fcn9' */
  real_T Saturation5;                  /* '<Root>/Saturation5' */
  real_T Gain5_d;                      /* '<S4>/Gain5' */
  real_T Sum3;                         /* '<Root>/Sum3' */
  real_T accy;                         /* '<Root>/Cast' */
  real_T accz;                         /* '<Root>/Cast1' */
  real_T posy;                         /* '<Root>/Discrete-Time Integrator10' */
  real_T posz;                         /* '<Root>/Discrete-Time Integrator9' */
  real_T posx_a;                       /* '<Root>/Discrete-Time Integrator11' */
  real_T vely;                         /* '<Root>/Discrete-Time Integrator7' */
  real_T velz;                         /* '<Root>/Discrete-Time Integrator6' */
  real_T velx_m;                       /* '<Root>/Discrete-Time Integrator8' */
  real_T Gain;                         /* '<Root>/Gain' */
  real_T Gain_i;                       /* '<S2>/Gain' */
  real_T Gain1_m;                      /* '<S2>/Gain1' */
  real_T DataTypeConversion3;          /* '<Root>/Data Type Conversion3' */
  real_T DataTypeConversion4;          /* '<Root>/Data Type Conversion4' */
  real_T DataTypeConversion5;          /* '<Root>/Data Type Conversion5' */
  real_T DataTypeConversion6;          /* '<Root>/Data Type Conversion6' */
  real_T DataTypeConversion7;          /* '<Root>/Data Type Conversion7' */
  real_T DataTypeConversion8;          /* '<Root>/Data Type Conversion8' */
  real_T DiscreteTimeIntegrator;       /* '<Root>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator1;      /* '<Root>/Discrete-Time Integrator1' */
  real_T Saturation3;                  /* '<Root>/Saturation3' */
  real_T TransferFcn4;                 /* '<Root>/Transfer Fcn4' */
  real_T TransferFcn5;                 /* '<Root>/Transfer Fcn5' */
  real_T TransferFcn6;                 /* '<Root>/Transfer Fcn6' */
  real_T TransferFcn8;                 /* '<Root>/Transfer Fcn8' */
  uint8_T DataTypeConversion17;        /* '<S6>/Data Type Conversion17' */
  uint8_T DataTypeConversion15;        /* '<S6>/Data Type Conversion15' */
  uint8_T DataTypeConversion4_e;       /* '<S6>/Data Type Conversion4' */
  uint8_T DataTypeConversion2;         /* '<S6>/Data Type Conversion2' */
  uint8_T DataTypeConversion20;        /* '<S6>/Data Type Conversion20' */
  uint8_T DataTypeConversion19;        /* '<S6>/Data Type Conversion19' */
  uint8_T DataTypeConversion22;        /* '<S6>/Data Type Conversion22' */
  uint8_T DataTypeConversion21;        /* '<S6>/Data Type Conversion21' */
  uint8_T DataTypeConversion7_i;       /* '<S6>/Data Type Conversion7' */
  uint8_T DataTypeConversion23;        /* '<S6>/Data Type Conversion23' */
  uint8_T DataTypeConversion13;        /* '<S6>/Data Type Conversion13' */
  uint8_T DataTypeConversion10;        /* '<S6>/Data Type Conversion10' */
  int8_T DataTypeConversion16;         /* '<S6>/Data Type Conversion16' */
  int8_T DataTypeConversion18;         /* '<S6>/Data Type Conversion18' */
  int8_T DataTypeConversion24;         /* '<S6>/Data Type Conversion24' */
  int8_T DataTypeConversion25;         /* '<S6>/Data Type Conversion25' */
  int8_T DataTypeConversion26;         /* '<S6>/Data Type Conversion26' */
  int8_T DataTypeConversion27;         /* '<S6>/Data Type Conversion27' */
  boolean_T Compare[3];                /* '<S1>/Compare' */
} B_c_coder_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T DiscreteTimeIntegrator5_DSTATE;/* '<Root>/Discrete-Time Integrator5' */
  real_T DiscreteTimeIntegrator4_DSTATE;/* '<Root>/Discrete-Time Integrator4' */
  real_T DiscreteTimeIntegrator2_DSTATE;/* '<Root>/Discrete-Time Integrator2' */
  real_T DiscreteTimeIntegrator3_DSTATE;/* '<Root>/Discrete-Time Integrator3' */
  real_T DiscreteTimeIntegrator10_DSTATE;/* '<Root>/Discrete-Time Integrator10' */
  real_T DiscreteTimeIntegrator9_DSTATE;/* '<Root>/Discrete-Time Integrator9' */
  real_T DiscreteTimeIntegrator11_DSTATE;/* '<Root>/Discrete-Time Integrator11' */
  real_T DiscreteTimeIntegrator7_DSTATE;/* '<Root>/Discrete-Time Integrator7' */
  real_T DiscreteTimeIntegrator6_DSTATE;/* '<Root>/Discrete-Time Integrator6' */
  real_T DiscreteTimeIntegrator8_DSTATE;/* '<Root>/Discrete-Time Integrator8' */
  real_T DiscreteTimeIntegrator_DSTATE;/* '<Root>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator1_DSTATE;/* '<Root>/Discrete-Time Integrator1' */
  real_T TimeStampA;                   /* '<Root>/Derivative1' */
  real_T LastUAtTimeA;                 /* '<Root>/Derivative1' */
  real_T TimeStampB;                   /* '<Root>/Derivative1' */
  real_T LastUAtTimeB;                 /* '<Root>/Derivative1' */
  real_T TimeStampA_c;                 /* '<Root>/Derivative2' */
  real_T LastUAtTimeA_k;               /* '<Root>/Derivative2' */
  real_T TimeStampB_c;                 /* '<Root>/Derivative2' */
  real_T LastUAtTimeB_o;               /* '<Root>/Derivative2' */
  real_T TimeStampA_j;                 /* '<Root>/Derivative3' */
  real_T LastUAtTimeA_p;               /* '<Root>/Derivative3' */
  real_T TimeStampB_m;                 /* '<Root>/Derivative3' */
  real_T LastUAtTimeB_oi;              /* '<Root>/Derivative3' */
} DW_c_coder_T;

/* Continuous states (default storage) */
typedef struct {
  real_T TransferFcn13_CSTATE;         /* '<Root>/Transfer Fcn13' */
  real_T TransferFcn11_CSTATE;         /* '<Root>/Transfer Fcn11' */
  real_T TransferFcn7_CSTATE;          /* '<Root>/Transfer Fcn7' */
  real_T TransferFcn10_CSTATE;         /* '<Root>/Transfer Fcn10' */
  real_T TransferFcn2_CSTATE[2];       /* '<Root>/Transfer Fcn2' */
  real_T TransferFcn9_CSTATE;          /* '<Root>/Transfer Fcn9' */
  real_T TransferFcn4_CSTATE;          /* '<Root>/Transfer Fcn4' */
  real_T TransferFcn5_CSTATE;          /* '<Root>/Transfer Fcn5' */
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
  real_T TransferFcn9_CSTATE;          /* '<Root>/Transfer Fcn9' */
  real_T TransferFcn4_CSTATE;          /* '<Root>/Transfer Fcn4' */
  real_T TransferFcn5_CSTATE;          /* '<Root>/Transfer Fcn5' */
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
  boolean_T TransferFcn9_CSTATE;       /* '<Root>/Transfer Fcn9' */
  boolean_T TransferFcn4_CSTATE;       /* '<Root>/Transfer Fcn4' */
  boolean_T TransferFcn5_CSTATE;       /* '<Root>/Transfer Fcn5' */
  boolean_T TransferFcn6_CSTATE;       /* '<Root>/Transfer Fcn6' */
  boolean_T TransferFcn8_CSTATE;       /* '<Root>/Transfer Fcn8' */
} XDis_c_coder_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T Gain4;                  /* '<Root>/Gain4' */
  const real_T Saturation;             /* '<Root>/Saturation' */
  const real_T Product5;               /* '<S11>/Product5' */
  const uint8_T DataTypeConversion;    /* '<S6>/Data Type Conversion' */
  const uint8_T DataTypeConversion1;   /* '<S6>/Data Type Conversion1' */
  const uint8_T DataTypeConversion11;  /* '<S6>/Data Type Conversion11' */
  const uint8_T DataTypeConversion12;  /* '<S6>/Data Type Conversion12' */
  const uint8_T DataTypeConversion14;  /* '<S6>/Data Type Conversion14' */
  const uint8_T DataTypeConversion28;  /* '<S6>/Data Type Conversion28' */
  const uint8_T DataTypeConversion29;  /* '<S6>/Data Type Conversion29' */
  const uint8_T DataTypeConversion3;   /* '<S6>/Data Type Conversion3' */
  const uint8_T DataTypeConversion30;  /* '<S6>/Data Type Conversion30' */
  const uint8_T DataTypeConversion5;   /* '<S6>/Data Type Conversion5' */
  const uint8_T DataTypeConversion6;   /* '<S6>/Data Type Conversion6' */
  const uint8_T DataTypeConversion8;   /* '<S6>/Data Type Conversion8' */
  const uint8_T DataTypeConversion9;   /* '<S6>/Data Type Conversion9' */
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

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern uint8_T out1[25];               /* '<Root>/Out1' */

/* Model entry point functions */
extern void c_coder_initialize(RT_MODEL_c_coder_T *const c_coder_M, real_T
  *c_coder_U_Inport, real_T *c_coder_U_Inport1, real_T *c_coder_U_Inport2,
  real_T *c_coder_U_Inport3, real_T *c_coder_U_Inport4, real_T
  *c_coder_U_Inport5);
extern void c_coder_step(RT_MODEL_c_coder_T *const c_coder_M, real_T
  c_coder_U_Inport, real_T c_coder_U_Inport1, real_T c_coder_U_Inport2, real_T
  c_coder_U_Inport3, real_T c_coder_U_Inport4, real_T c_coder_U_Inport5);
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
 * '<S4>'   : 'c_coder/Subsystem1'
 * '<S5>'   : 'c_coder/Subsystem/Cinemática Inversa Plataforma 6Dof'
 * '<S6>'   : 'c_coder/Subsystem/Escrever 20.01 a 20.06 UNIDRIVE SP ModBus TCP//IP'
 * '<S7>'   : 'c_coder/Subsystem/Cinemática Inversa Plataforma 6Dof/Cinematica aux'
 * '<S8>'   : 'c_coder/Subsystem/Cinemática Inversa Plataforma 6Dof/Cinematica Inversa'
 * '<S9>'   : 'c_coder/Subsystem/Cinemática Inversa Plataforma 6Dof/Deg=>Rad'
 * '<S10>'  : 'c_coder/Subsystem/Cinemática Inversa Plataforma 6Dof/Deg=>Rad1'
 * '<S11>'  : 'c_coder/Subsystem/Cinemática Inversa Plataforma 6Dof/Deg=>Rad2'
 */
#endif                                 /* RTW_HEADER_c_coder_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
