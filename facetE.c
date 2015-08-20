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

  mxArray *V, *type;
  V = prhs[0];
  type = prhs[1];

  if( mxGetM(V) != mxGetM(type)) 
    mexErrMsgIdAndTxt("GeoCalcLib:Dimensions:facet:Enumeration","Matrices V and type must have same number of rows.\n" );

  mxArray *helper, *retCell;
  struct GMPmat *myHelp;

  helper = VertConcat( type , V );
  myHelp = GMPmat_fromMXArray( helper );

  mxDestroyArray(helper);

  myHelp = reducevertices(myHelp);
  myHelp = V2H(myHelp);
  myHelp = reducemat(myHelp);
  GMPmat_invertSignForFacetEnumeration(myHelp);

  helper = MXArray_fromGMPmat(myHelp);
  GMPmat_destroy(myHelp);

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
    plhs[0] = mxDuplicateArray(retCell);
  }
  mxDestroyArray(retCell);
}