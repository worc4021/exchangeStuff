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

  mxArray *helper, *retCell;
  struct GMPmat *myHelp, *calcMat;

  helper = VertConcat( prhs[1] , prhs[0] );
  myHelp = GMPmat_fromMXArray( helper );
  
  mxDestroyArray(helper);
  

  GMPmat_invertSignForFacetEnumeration(myHelp);
  calcMat = H2V(myHelp);

  helper = MXArray_fromGMPmat(calcMat);
  GMPmat_destroy(calcMat);

  retCell = VertBreakdown(helper);
  mxDestroyArray(helper);

  if (nlhs==2){

    mwSize nsubs=2, subs[2];
    mwIndex index;
    subs[0] = 0;
    subs[1] = 0;
    index = mxCalcSingleSubscript(retCell, nsubs, subs);
    plhs[0] = mxGetCell(retCell,index);

    subs[1] = 1;
    index = mxCalcSingleSubscript(retCell, nsubs, subs);
    plhs[1] = mxGetCell(retCell,index);
  } else {
    plhs[0] = retCell;
  }
  mxDestroyArray(retCell);
}