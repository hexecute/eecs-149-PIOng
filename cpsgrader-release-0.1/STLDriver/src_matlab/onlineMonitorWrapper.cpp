#include <string>
#include <iostream>
#include <sstream>
#include "stl_driver.h"

#define S_FUNCTION_LEVEL 2
#define S_FUNCTION_NAME  onlineMonitorWrapper

// Need to include simstruc.h for the definition of the SimStruct and
// its associated macro definitions.
#include "simstruc.h"

// TODO make these parameters of the block
#define TOP_ROB 20
#define BOTTOM_ROB -20


#define SIG_IDX 0
#define STL_IDX 1

#define SIGNAL_STRING(S) ssGetSFcnParam(S,SIG_IDX)
#define STL_STRING(S) ssGetSFcnParam(S,STL_IDX)

#define NPARAMS 2

#define NOUTPORT 2
#define UP_IDX 0
#define LOW_IDX 1

#if !defined(MATLAB_MEX_FILE)
/*
 * This file cannot be used directly with the Real-Time Workshop. However,
 * this S-function does work with the Real-Time Workshop via
 * the Target Language Compiler technology. See
 * matlabroot/toolbox/simulink/blocks/tlc_c/sfun_multiport.tlc
 * for the C version
 * matlabroot/toolbox/simulink/blocks/tlc_ada/sfun_multiport.tlc
 * for the Ada version
 */
# error This_file_can_be_used_only_during_simulation_inside_Simulink
#endif

using namespace std;
using namespace stl_transducer;

/*====================*
 * S-function methods *
 *====================*/

#define MDL_CHECK_PARAMETERS
#if defined(MDL_CHECK_PARAMETERS) && defined(MATLAB_MEX_FILE)
/* Function: mdlCheckParameters =============================================
 * Abstract:
 *    Validate our parameters to verify they are okay.
 */
static void mdlCheckParameters(SimStruct *S)
{

	char *signal_buf = mxArrayToString(SIGNAL_STRING(S));
    char *stl_buf = mxArrayToString(STL_STRING(S));

    string phi_st = "signal "+ string(signal_buf) + "\n" + "phi:=" + string(stl_buf);
    mxFree(signal_buf);
    mxFree(stl_buf);

    cout << phi_st << endl;
    Driver *stl_driver = new Driver();
    bool parse_success = stl_driver->parse_string(phi_st);
    if (parse_success==0)
    	ssSetErrorStatus(S,"Error while parsing STL Formula.");
    delete stl_driver;
    
}
#endif /* MDL_CHECK_PARAMETERS */

// Function: mdlInitializeSizes ===============================================
// Abstract:
//    The sizes information is used by Simulink to determine the S-function
//    block's characteristics (number of inputs, outputs, states, etc.).
static void mdlInitializeSizes(SimStruct *S)
{
    // Check the number of expected parameters
    ssSetNumSFcnParams(S, NPARAMS);
    // Parameter mismatch will be reported by Simulink
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        return;
    }
    mdlCheckParameters(S);
    if (ssGetErrorStatus(S) != NULL) {
        return;
    }
    ssSetSFcnParamTunable(S,STL_IDX,true);
    ssSetSFcnParamTunable(S,SIG_IDX,true);
    // Specify I/O
    if (!ssSetNumInputPorts(S, 1)) return;
    if(!ssSetInputPortDimensionInfo(S, 0, DYNAMIC_DIMENSION)) return;
    ssSetInputPortWidth(S, 0, DYNAMICALLY_SIZED);
    ssSetInputPortDirectFeedThrough(S, 0, 1);
    
    if (!ssSetNumOutputPorts(S,1)) return;
    ssSetOutputPortWidth(S, 0, NOUTPORT);
    
    ssSetNumSampleTimes(S, 1);
    
    // Reserve place for C++ object
    ssSetNumPWork(S, 1);
    
    ssSetSimStateCompliance(S, USE_CUSTOM_SIM_STATE);
    
    ssSetOptions(S,
            SS_OPTION_WORKS_WITH_CODE_REUSE |
            SS_OPTION_EXCEPTION_FREE_CODE);
    
}
#if defined(MATLAB_MEX_FILE)
#define MDL_SET_INPUT_PORT_DIMENSION_INFO
static void mdlSetInputPortDimensionInfo(SimStruct *S,
        int_T port, const DimsInfo_T *dimsInfo)
{
    if(!ssSetInputPortDimensionInfo(S, port, dimsInfo)) return;
}
#endif

#if defined(MATLAB_MEX_FILE)
#define MDL_SET_OUTPUT_PORT_DIMENSION_INFO
static void mdlSetOutputPortDimensionInfo(SimStruct *S,
        int_T port, const DimsInfo_T *dimsInfo)
{
    if(!ssSetOutputPortDimensionInfo(S, port, dimsInfo)) return;
}
#endif

#if defined(MATLAB_MEX_FILE)
# define MDL_SET_DEFAULT_PORT_DIMENSION_INFO
/* Function: mdlSetDefaultPortDimensionInfo ===========================================
 * Abstract:
 *   In case no ports were specified, the default is an input port of width 2
 *   and an output port of width 1.
 */
static void mdlSetDefaultPortDimensionInfo(SimStruct *S)
{
    ssSetInputPortWidth(S, 0, 1);
    ssSetOutputPortWidth(S, 0, NOUTPORT);
}
#endif

// Function: mdlInitializeSampleTimes =========================================
// Abstract:
//   This function is used to specify the sample time(s) for your
//   S-function. You must register the same number of sample times as
//   specified in ssSetNumSampleTimes.
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
    ssSetModelReferenceSampleTimeDefaultInheritance(S);
}

// Function: mdlStart =======================================================
// Abstract:
//   This function is called once at start of model execution. If you
//   have states that should be initialized once, this is the place
//   to do it.
#define MDL_START
static void mdlStart(SimStruct *S)
{

	transducer::signal_map.clear();
	transducer::param_map.clear();

    char *signal_buf = mxArrayToString(SIGNAL_STRING(S));
    char *stl_buf = mxArrayToString(STL_STRING(S));

    string phi_st = "signal "+ string(signal_buf) + "\n" + "phi:=" + string(stl_buf);
    mxFree(signal_buf);
    mxFree(stl_buf);

    // Store new C++ object in the pointers vector
    Driver *stl_driver  = new Driver();
    transducer::trace_data_ptr = &(stl_driver->data);

    stl_driver->parse_string(phi_st);

    ssGetPWork(S)[0] = stl_driver;
}

// Function: mdlOutputs =======================================================
// Abstract:
//   In this function, you compute the outputs of your S-function
//   block.
static void mdlOutputs(SimStruct *S, int_T tid)
{
    // Retrieve C++ object from the pointers vector
    Driver *stl_driver = static_cast<Driver *>(ssGetPWork(S)[0]);
    
    // Get data addresses of I/O
    InputRealPtrsType  u = ssGetInputPortRealSignalPtrs(S,0);
    int_T u_width  = ssGetInputPortWidth(S,0);
    real_T *y = ssGetOutputPortRealSignal(S, 0);

    vector<double> points;
    points.push_back(ssGetT(S));
    for(int_T i = 0; i< u_width; ++i ) {
        points.push_back(*u[i]);
    }
    stl_driver->data.push_back(points);

    double rob_up = TOP_ROB;
    double rob_low= BOTTOM_ROB;
    
    // Call UpdateRobust method to add a pair of inputs
    if (stl_driver->data.size()>2) {
    	transducer * phi = stl_driver->formula_map["phi"]->clone();
    	phi->trace_data_ptr= &stl_driver->data;
        rob_up= phi->compute_upper_rob();
        rob_low= phi->compute_lower_rob();
        delete phi;
    }

    if (rob_up==TOP)  // TOP is Inf
    	rob_up= TOP_ROB;
    if (rob_low==BOTTOM) // BOTTOM is -Inf
    	rob_low= BOTTOM_ROB;

    y[UP_IDX] =  rob_up;
    y[LOW_IDX] = rob_low;
}


// Function: mdlTerminate =====================================================
// Abstract:
//   In this function, you should perform any actions that are necessary
//   at the termination of a simulation.  For example, if memory was
//   allocated in mdlStart, this is the place to free it.
static void mdlTerminate(SimStruct *S)
{
    // Retrieve and destroy C++ object
    Driver *stl_driver = static_cast<Driver *>(ssGetPWork(S)[0]);
    delete stl_driver;
}


// Required S-function trailer
#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
