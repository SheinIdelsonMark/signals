// currNodeValue.c : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <math.h>

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
	if (nrhs >= 2 && nrhs <= 4) {
		int netid = (int)mxGetScalar(prhs[0]);
		size_t nodeid = (size_t)roundl(mxGetScalar(prhs[1]));
		bool appendValue = false;
		if (nlhs > 0 || nrhs == 2) {
			mxArray *v = sqGetNodeCurrValue(netid, nodeid);
			bool vset = true;
			if (v) { 
				v = mxDuplicateArray(v);
			}
			else { // no value set, so return empty
				v = mxCreateDoubleMatrix(0, 0, mxREAL);
				vset = false;
			}
			plhs[0] = v;
			if (nlhs == 2) {
				plhs[1] = mxCreateLogicalScalar(vset);
			}
		}
		if (nrhs >= 3) {
			if (nrhs >= 4) {
				appendValue = mxIsLogicalScalarTrue(prhs[3]);
			}
			mxArray *newv = mxDuplicateArray(prhs[2]);
			mexMakeArrayPersistent(newv);
			sqSetNodeCurrValue(netid, nodeid, newv, appendValue);
		}
	}
	else {
		mexErrMsgIdAndTxt("sq:notEnoughArgs", "Not enough input arguments");
	}
}