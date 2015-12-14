// include stuff
#include "mex.h"
#include <string>
#include <iostream>
#include <sstream>
#include "stl_driver.h"

using namespace std;
using namespace stl_transducer;


// mex main 
void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[] ) {

	stringstream fcout;

    if (nrhs<=1)
    	mexErrMsgTxt("Two inputs are expected: a formula (string) and data (array).");

    /* read inputs: a string and data */
    
    char *input_buf = mxArrayToString(prhs[0]);
        string phi_st = string(input_buf);

    int m = mxGetM(prhs[1]);
    int n=  mxGetN(prhs[1]);


    double *data_in = (double *) mxGetPr(prhs[1]);
    trace_data trace;

    vector<double> sample;
    for(int i = 0; i<n; i++){
    	for(int j = 0; j<m; j++) {
            //    		cout << data_in[j+ i*m] << " ";
    		sample.push_back(data_in[j+ i*m]);
      }
    	trace.push_back(sample);
        sample.clear();
        //    	cout << endl;
   }


  /* setup stl_driver with basic signal names */

	Driver stl_driver = Driver();
    transducer::trace_data_ptr = &trace;
	transducer::signal_map["x1"]=1;
	transducer::signal_map["x2"]=2;

    transducer * phi; 
    double rob, rob_up, rob_low;
    Signal z, z_up, z_low;
	bool parse_success = stl_driver.parse_string("phi:="+phi_st);

    if (parse_success) {
		phi = stl_driver.formula_map["phi"]->clone();
        rob= phi->compute_robustness();
        rob_up= phi->compute_upper_rob();
        rob_low= phi->compute_lower_rob();
        z =  phi->z;
        z_low = phi->z_low;
        z_up = phi->z_up;
    }
    else
    	mexErrMsgTxt("Problem parsing formula.");

//    fcout << "z:" << z << endl;
//    fcout << "z_low:" << z_low << endl;
//    fcout << "z_up:" << z_up << endl;

    /* compute and output robustness at 0  */

    int l =  z.size();
    plhs[0] = mxCreateDoubleMatrix(1,l, mxREAL);
    plhs[1] = mxCreateDoubleMatrix(1,l, mxREAL);

    double *t_ptr = mxGetPr(plhs[0]);
    double *rob_ptr = mxGetPr(plhs[1]);

    int pos = 0;
    for(const auto iter_z: z) {
    	t_ptr[pos] = iter_z.time;
    	rob_ptr[pos] = iter_z.value;
    	pos++;
    }

    int l_low =  z_low.size();
    plhs[2] = mxCreateDoubleMatrix(1,l_low, mxREAL);
    plhs[3] = mxCreateDoubleMatrix(1,l_low, mxREAL);

    double *t_low_ptr = mxGetPr(plhs[2]);
    double *rob_low_ptr = mxGetPr(plhs[3]);

    pos = 0;
    for(const auto iter_z: z_low) {
    	t_low_ptr[pos] = iter_z.time;
    	rob_low_ptr[pos] = iter_z.value;
    	pos++;
    }

    int l_up =  z_up.size();
    plhs[4] = mxCreateDoubleMatrix(1,l_up, mxREAL);
    plhs[5] = mxCreateDoubleMatrix(1,l_up, mxREAL);

    double *t_up_ptr = mxGetPr(plhs[4]);
    double *rob_up_ptr = mxGetPr(plhs[5]);

    pos = 0;
    for(const auto iter_z: z_up) {
    	t_up_ptr[pos] = iter_z.time;
    	rob_up_ptr[pos] = iter_z.value;
    	pos++;
    }

//    mexPrintf(fcout.str().c_str());
    // clean
    mxFree(input_buf);
    delete phi;
}


//
