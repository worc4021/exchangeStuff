#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <assert.h>
#include "mex.h"
#include "matrix.h"
#include "tmwtypes.h"

struct GMPmat{
    mpq_t *data;
    size_t m, n;
};



struct GMPmat *GMPmat_fromMXArray (const mxArray *pm)
{
       struct GMPmat *A;
       size_t         i, j;

       A = calloc (1, sizeof (*A));
       assert (A != NULL);

       double *ptr = mxGetPr(pm);

       A->m    = mxGetM(pm);
       A->n    = mxGetN(pm);
       A->data = calloc (A->m*A->n, sizeof(*A->data));
       assert ( A->data != NULL );

         for (i=0; i!=A->m; ++i){
           for (j=0; j!=A->n; ++j){
            mpq_init (A->data[i*(A->n) + j]);
            mpq_set_d(A->data[i*(A->n) + j], ptr[i + j*A->m]);
          }
        }

       return (A);
}

void GMPmat_destroy (struct GMPmat *A)
     {
       assert (A != NULL);
       size_t i, j;
       for (i = 0; i < A->m; ++i)
       {
        for (j = 0; j < A->n; ++j)
        {
            mpq_clear(A->data[i*(A->n) + j]);
        }
       }
       if (A->data != NULL) free (A->data);
       A->data = NULL;
       A->n   = 0;
       A->m   = 0;
       free (A);
     }

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    if ( nrhs != 1 ) {
        mexErrMsgIdAndTxt("MATLAB:mexTest:rhs","Only one matrix!");
    } 

    struct GMPmat *calcMat;

    calcMat = GMPmat_fromMXArray(prhs[0]);
    GMPmat_destroy(calcMat);

}