/*
//@HEADER
// ************************************************************************
//
//                        Adelus v. 1.0
//       Copyright (2020) National Technology & Engineering
//               Solutions of Sandia, LLC (NTESS).
//
// Under the terms of Contract DE-NA0003525 with NTESS,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of NTESS nor the names of the contributors may be
// used to endorse or promote products derived from this software without
// specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY NTESS "AS IS" AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL NTESS OR THE CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
// IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact Vinh Dang (vqdang@sandia.gov)
//                    Joseph Kotulski (jdkotul@sandia.gov)
//                    Siva Rajamanickam (srajama@sandia.gov)
//
// ************************************************************************
//@HEADER
*/

#ifndef __ADELUS_DEFINES_H__
#define __ADELUS_DEFINES_H__


#undef CBLAS
#undef DEBUG
#define  OVERLAP
//#undef  PRINT_STATUS
#undef   TIMING0


#ifdef DREAL
#define MPI_DATA_TYPE MPI_DOUBLE
#define MPI_DATA_TYPE2 MPI_DOUBLE_INT
#endif
#ifdef SREAL
#define MPI_DATA_TYPE MPI_FLOAT
#define MPI_DATA_TYPE2 MPI_FLOAT_INT
#endif

/*  ------------------ Define Data Types -------------------------- */
#ifdef ZCPLX
    typedef struct {
      double r;
      double i;
    } dcomplex ;
#define DATA_TYPE dcomplex
#define COMPLEX
#define MPI_DATA_TYPE MPI_DOUBLE
#define MPI_DATA_TYPE2 MPI_DOUBLE_INT
#endif

#ifdef SCPLX
    typedef struct {
      float r;
      float i;
    } scomplex ;
#define DATA_TYPE scomplex
#define COMPLEX
#define MPI_DATA_TYPE  MPI_FLOAT
#define MPI_DATA_TYPE2 MPI_FLOAT_INT
#endif

#ifdef DREAL

#define DATA_TYPE double
#undef COMPLEX
#endif

#ifdef SREAL

#define DATA_TYPE float
#undef COMPLEX
#endif


/*  ------------------ Define Constants and Operations ------------ */

#ifdef ZCPLX

#define ADELUS_CONST_ONE {1.0, 0.0}
#define ADELUS_CONST_MINUS_ONE {-1.0, 0.0}
#define ADELUS_CONST_ZERO {0.0, 0.0}
#define ADELUS_NEGATIVE(X,Y) (Y).r=-(X).r;(Y).i=-(X).i
#define ADELUS_ABS_VAL(X) ((X).r * (X).r + (X).i * (X).i)
#define ADELUS_INVERSE(X,W,Z) (Z).r=(X).r/(W);(Z).i=-(X).i/(W)
#define ADELUS_MULTIPLY(X,Y,Z) (Z).r=(X).r*(Y).r-(X).i*(Y).i;(Z).i=(X).r*(Y).i+(X).i*(Y).r
#define ADELUS_DIVIDE(X,Y,W,Z) (Z).r=((X).r*(Y).r+(X).i*(Y).i)/(W);(Z).i=((X).i*(Y).r-(X).r*(Y).i)/(W)

#endif

#ifdef  SCPLX

#define ADELUS_CONST_ONE {1.0, 0.0}
#define ADELUS_CONST_MINUS_ONE {-1.0, 0.0}
#define ADELUS_CONST_ZERO {0.0, 0.0}
#define ADELUS_NEGATIVE(X,Y) (Y).r=-(X).r;(Y).i=-(X).i
#define ADELUS_ABS_VAL(X) ((X).r * (X).r + (X).i * (X).i)
#define ADELUS_INVERSE(X,W,Z) (Z).r=(X).r/(W);(Z).i=-(X).i/(W)
#define ADELUS_MULTIPLY(X,Y,Z) (Z).r=(X).r*(Y).r-(X).i*(Y).i;(Z).i=(X).r*(Y).i+(X).i*(Y).r
#define ADELUS_DIVIDE(X,Y,W,Z) (Z).r=((X).r*(Y).r+(X).i*(Y).i)/(W);(Z).i=((X).i*(Y).r-(X).r*(Y).i)/(W)

#endif


#ifdef DREAL

#define ADELUS_CONST_ONE 1.0
#define ADELUS_CONST_MINUS_ONE -1.0
#define ADELUS_CONST_ZERO 0.0
#define ADELUS_NEGATIVE(X,Y) (Y)=-(X)
#define ADELUS_ABS_VAL(X) (fabs(X))
#define ADELUS_INVERSE(X,W,Z) (Z)=CONST_ONE/(X)
#define ADELUS_MULTIPLY(X,Y,Z) (Z)=(X)*(Y)
#define ADELUS_DIVIDE(X,Y,W,Z) (Z)=(X)/(Y)

#endif

#ifdef SREAL

#define ADELUS_CONST_ONE 1.0
#define ADELUS_CONST_MINUS_ONE -1.0
#define ADELUS_CONST_ZERO 0.0
#define ADELUS_NEGATIVE(X,Y) (Y)=-(X)
#define ADELUS_ABS_VAL(X) (fabs(X))
#define ADELUS_INVERSE(X,W,Z) (Z)=CONST_ONE/(X)
#define ADELUS_MULTIPLY(X,Y,Z) (Z)=(X)*(Y)
#define ADELUS_DIVIDE(X,Y,W,Z) (Z)=(X)/(Y)

#endif

/*  ------------------- Define BLAS prototype definitions ------------  */

#ifdef ZCPLX
//#include "zblassp.h"
#define XGEMM_  zgemm_
#define XGEMMS_ zgemm_
#define XGEMM  zgemm
#define XLU_SOLVE_ zlusolve_
#define X_SOLVE_ zsolve_
#define X_FACTOR_ zfactor_
#define X_PERMUTE_ zpermute_
#endif

#ifdef SCPLX
//#include "cblassp.h"
#define XGEMM_  cgemm_
#define XGEMM  cgemm
#define XLU_SOLVE_ clusolve_
#define X_SOLVE_ csolve_
#define X_FACTOR_ cfactor_
#define X_PERMUTE_ cpermute_
#endif

#ifdef DREAL
//#include "dblassp.h"
#define XGEMM_  dgemm_
#define XGEMM  dgemm
#define XGEMMS_ dgemm_
#define XLU_SOLVE_ dlusolve_
#define X_SOLVE_ dsolve_
#define X_FACTOR_ dfactor_
#define X_PERMUTE_ dpermute_
#endif

#ifdef SREAL
//#include "sblassp.h"
#define XGEMM_  sgemm_
#define XGEMM  sgemm
#define XGEMMS_  sgemm_
#define XLU_SOLVE_ slusolve_
#define X_SOLVE_ ssolve_
#define X_FACTOR_ sfactor_
#define X_PERMUTE_ spermute_
#endif

#endif
