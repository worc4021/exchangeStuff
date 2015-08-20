#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <assert.h>
#include "mex.h"
#include "matrix.h"
#include "tmwtypes.h"
#include "translation_functions.h"


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  if ( nrhs != 2 ) {
        mexErrMsgIdAndTxt("MATLAB:mexTest:rhs","One for !");
  } 

  mxArray *helper;
  struct GMPmat *myHelp, *calcMat;

  helper = VertConcat( prhs[1] , prhs[0] );
  myHelp = GMPmat_fromMXArray( helper );
  
  mxDestroyArray(helper);
  

  GMPmat_invertSignForFacetEnumeration(myHelp);
  calcMat = H2V(myHelp);

  helper = MXArray_fromGMPmat(calcMat);
  GMPmat_destroy(calcMat);

  VertSplit(plhs[0],plhs[1],helper);
  
  mxDestroyArray(helper);
}