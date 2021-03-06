// @HEADER
// ************************************************************************
//
//               Rapid Optimization Library (ROL) Package
//                 Copyright (2014) Sandia Corporation
//
// Under terms of Contract DE-AC04-94AL85000, there is a non-exclusive
// license for use of this work by or on behalf of the U.S. Government.
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
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact lead developers:
//              Drew Kouri   (dpkouri@sandia.gov) and
//              Denis Ridzal (dridzal@sandia.gov)
//
// ************************************************************************
// @HEADER

/*! \file  test_10.cpp
    \brief Show how to use CompositeEqualityConstraint interface.
*/

#include "ROL_CompositeEqualityConstraint_SimOpt.hpp"
#include "ROL_StdVector.hpp"
#include "Teuchos_oblackholestream.hpp"
#include "Teuchos_GlobalMPISession.hpp"

#include <iostream>

template<class Real>
class valConstraint : public ROL::EqualityConstraint_SimOpt<Real> {
public:
  valConstraint(void) : ROL::EqualityConstraint_SimOpt<Real>() {}

  void value(ROL::Vector<Real> &c, const ROL::Vector<Real> &u, const ROL::Vector<Real> &z, Real &tol) {
    Teuchos::RCP<std::vector<Real> > cp
      = Teuchos::dyn_cast<ROL::StdVector<Real> >(c).getVector();
    Teuchos::RCP<const std::vector<Real> > up
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(u).getVector();
    Teuchos::RCP<const std::vector<Real> > zp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(z).getVector();

    Real half(0.5), two(2);
    // C(0) = U(0) - Z(0)
    (*cp)[0] = (*up)[0]-(*zp)[0];
    // C(1) = 0.5 * (U(0) + U(1) - Z(0))^2
    (*cp)[1] = half*std::pow((*up)[0]+(*up)[1]-(*zp)[0],two);
  }

  void applyJacobian_1(ROL::Vector<Real> &jv, const ROL::Vector<Real> &v,
                       const ROL::Vector<Real> &u, const ROL::Vector<Real> &z, Real &tol) {
    Teuchos::RCP<std::vector<Real> > jvp
      = Teuchos::dyn_cast<ROL::StdVector<Real> >(jv).getVector();
    Teuchos::RCP<const std::vector<Real> > vp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(v).getVector();
    Teuchos::RCP<const std::vector<Real> > up
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(u).getVector();
    Teuchos::RCP<const std::vector<Real> > zp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(z).getVector();
    (*jvp)[0] = (*vp)[0];
    (*jvp)[1] = ((*up)[0] + (*up)[1] - (*zp)[0]) * ((*vp)[0] + (*vp)[1]);
  }

  void applyJacobian_2(ROL::Vector<Real> &jv, const ROL::Vector<Real> &v,
                       const ROL::Vector<Real> &u, const ROL::Vector<Real> &z, Real &tol) {
    Teuchos::RCP<std::vector<Real> > jvp
      = Teuchos::dyn_cast<ROL::StdVector<Real> >(jv).getVector();
    Teuchos::RCP<const std::vector<Real> > vp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(v).getVector();
    Teuchos::RCP<const std::vector<Real> > up
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(u).getVector();
    Teuchos::RCP<const std::vector<Real> > zp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(z).getVector();
    (*jvp)[0] = -(*vp)[0];
    (*jvp)[1] = ((*zp)[0] - (*up)[0] - (*up)[1]) * (*vp)[0];
  }

  void applyAdjointJacobian_1(ROL::Vector<Real> &ajv, const ROL::Vector<Real> &v,
                              const ROL::Vector<Real> &u, const ROL::Vector<Real> &z, Real &tol) {
    Teuchos::RCP<std::vector<Real> > ajvp
      = Teuchos::dyn_cast<ROL::StdVector<Real> >(ajv).getVector();
    Teuchos::RCP<const std::vector<Real> > vp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(v).getVector();
    Teuchos::RCP<const std::vector<Real> > up
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(u).getVector();
    Teuchos::RCP<const std::vector<Real> > zp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(z).getVector();
    (*ajvp)[0] = (*vp)[0] + ((*up)[0] + (*up)[1] - (*zp)[0]) * (*vp)[1];
    (*ajvp)[1] = ((*up)[0] + (*up)[1] - (*zp)[0]) * (*vp)[1];
  }

  void applyAdjointJacobian_2(ROL::Vector<Real> &ajv, const ROL::Vector<Real> &v,
                              const ROL::Vector<Real> &u, const ROL::Vector<Real> &z, Real &tol) {
    Teuchos::RCP<std::vector<Real> > ajvp
      = Teuchos::dyn_cast<ROL::StdVector<Real> >(ajv).getVector();
    Teuchos::RCP<const std::vector<Real> > vp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(v).getVector();
    Teuchos::RCP<const std::vector<Real> > up
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(u).getVector();
    Teuchos::RCP<const std::vector<Real> > zp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(z).getVector();
    (*ajvp)[0] = ((*zp)[0] - (*up)[0] - (*up)[1]) * (*vp)[1] - (*vp)[0];
  }

  void applyAdjointHessian_11(ROL::Vector<Real> &ahwv, const ROL::Vector<Real> &w, const ROL::Vector<Real> &v,
                              const ROL::Vector<Real> &u, const ROL::Vector<Real> &z, Real &tol) {
    Teuchos::RCP<std::vector<Real> > ahwvp
      = Teuchos::dyn_cast<ROL::StdVector<Real> >(ahwv).getVector();
    Teuchos::RCP<const std::vector<Real> > wp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(w).getVector();
    Teuchos::RCP<const std::vector<Real> > vp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(v).getVector();
    Teuchos::RCP<const std::vector<Real> > up
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(u).getVector();
    Teuchos::RCP<const std::vector<Real> > zp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(z).getVector();
    (*ahwvp)[0] = (*wp)[1] * ((*vp)[0] + (*vp)[1]);
    (*ahwvp)[1] = (*wp)[1] * ((*vp)[0] + (*vp)[1]);
  }

  void applyAdjointHessian_12(ROL::Vector<Real> &ahwv, const ROL::Vector<Real> &w, const ROL::Vector<Real> &v,
                              const ROL::Vector<Real> &u, const ROL::Vector<Real> &z, Real &tol) {
    Teuchos::RCP<std::vector<Real> > ahwvp
      = Teuchos::dyn_cast<ROL::StdVector<Real> >(ahwv).getVector();
    Teuchos::RCP<const std::vector<Real> > wp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(w).getVector();
    Teuchos::RCP<const std::vector<Real> > vp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(v).getVector();
    Teuchos::RCP<const std::vector<Real> > up
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(u).getVector();
    Teuchos::RCP<const std::vector<Real> > zp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(z).getVector();
    (*ahwvp)[0] = -(*wp)[1] * ((*vp)[0] + (*vp)[1]);
  }

  void applyAdjointHessian_21(ROL::Vector<Real> &ahwv, const ROL::Vector<Real> &w, const ROL::Vector<Real> &v,
                              const ROL::Vector<Real> &u, const ROL::Vector<Real> &z, Real &tol) {
    Teuchos::RCP<std::vector<Real> > ahwvp
      = Teuchos::dyn_cast<ROL::StdVector<Real> >(ahwv).getVector();
    Teuchos::RCP<const std::vector<Real> > wp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(w).getVector();
    Teuchos::RCP<const std::vector<Real> > vp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(v).getVector();
    Teuchos::RCP<const std::vector<Real> > up
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(u).getVector();
    Teuchos::RCP<const std::vector<Real> > zp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(z).getVector();
    (*ahwvp)[0] = -(*wp)[1] * (*vp)[0];
    (*ahwvp)[1] = -(*wp)[1] * (*vp)[0];
  }

  void applyAdjointHessian_22(ROL::Vector<Real> &ahwv, const ROL::Vector<Real> &w, const ROL::Vector<Real> &v,
                              const ROL::Vector<Real> &u, const ROL::Vector<Real> &z, Real &tol) {
    Teuchos::RCP<std::vector<Real> > ahwvp
      = Teuchos::dyn_cast<ROL::StdVector<Real> >(ahwv).getVector();
    Teuchos::RCP<const std::vector<Real> > wp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(w).getVector();
    Teuchos::RCP<const std::vector<Real> > vp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(v).getVector();
    Teuchos::RCP<const std::vector<Real> > up
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(u).getVector();
    Teuchos::RCP<const std::vector<Real> > zp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(z).getVector();
    (*ahwvp)[0] = (*wp)[1] * (*vp)[0];
  }
};

template<class Real>
class redConstraint : public ROL::EqualityConstraint_SimOpt<Real> {
public:
  redConstraint(void) : ROL::EqualityConstraint_SimOpt<Real>() {}

  void value(ROL::Vector<Real> &c, const ROL::Vector<Real> &u, const ROL::Vector<Real> &z, Real &tol) {
    Teuchos::RCP<std::vector<Real> > cp
      = Teuchos::dyn_cast<ROL::StdVector<Real> >(c).getVector();
    Teuchos::RCP<const std::vector<Real> > up
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(u).getVector();
    Teuchos::RCP<const std::vector<Real> > zp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(z).getVector();

    const Real one(1), two(2);
    // C = exp(U) - (Z^2 + 1)
    (*cp)[0] = std::exp((*up)[0])-(std::pow((*zp)[0],two) + one);
  }

  void applyJacobian_1(ROL::Vector<Real> &jv, const ROL::Vector<Real> &v,
                       const ROL::Vector<Real> &u, const ROL::Vector<Real> &z, Real &tol) {
    Teuchos::RCP<std::vector<Real> > jvp
      = Teuchos::dyn_cast<ROL::StdVector<Real> >(jv).getVector();
    Teuchos::RCP<const std::vector<Real> > vp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(v).getVector();
    Teuchos::RCP<const std::vector<Real> > up
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(u).getVector();
    Teuchos::RCP<const std::vector<Real> > zp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(z).getVector();
    (*jvp)[0] = std::exp((*up)[0]) * (*vp)[0];
  }

  void applyJacobian_2(ROL::Vector<Real> &jv, const ROL::Vector<Real> &v,
                       const ROL::Vector<Real> &u, const ROL::Vector<Real> &z, Real &tol) {
    Teuchos::RCP<std::vector<Real> > jvp
      = Teuchos::dyn_cast<ROL::StdVector<Real> >(jv).getVector();
    Teuchos::RCP<const std::vector<Real> > vp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(v).getVector();
    Teuchos::RCP<const std::vector<Real> > up
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(u).getVector();
    Teuchos::RCP<const std::vector<Real> > zp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(z).getVector();

    const Real two(2);
    (*jvp)[0] = -two * (*zp)[0] * (*vp)[0];
  }

  void applyAdjointJacobian_1(ROL::Vector<Real> &ajv, const ROL::Vector<Real> &v,
                              const ROL::Vector<Real> &u, const ROL::Vector<Real> &z, Real &tol) {
    Teuchos::RCP<std::vector<Real> > ajvp
      = Teuchos::dyn_cast<ROL::StdVector<Real> >(ajv).getVector();
    Teuchos::RCP<const std::vector<Real> > vp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(v).getVector();
    Teuchos::RCP<const std::vector<Real> > up
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(u).getVector();
    Teuchos::RCP<const std::vector<Real> > zp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(z).getVector();
    (*ajvp)[0] = std::exp((*up)[0]) * (*vp)[0];
  }

  void applyAdjointJacobian_2(ROL::Vector<Real> &ajv, const ROL::Vector<Real> &v,
                              const ROL::Vector<Real> &u, const ROL::Vector<Real> &z, Real &tol) {
    Teuchos::RCP<std::vector<Real> > ajvp
      = Teuchos::dyn_cast<ROL::StdVector<Real> >(ajv).getVector();
    Teuchos::RCP<const std::vector<Real> > vp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(v).getVector();
    Teuchos::RCP<const std::vector<Real> > up
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(u).getVector();
    Teuchos::RCP<const std::vector<Real> > zp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(z).getVector();

    const Real two(2);
    (*ajvp)[0] = -two * (*zp)[0] * (*vp)[0];
  }

  void applyInverseJacobian_1(ROL::Vector<Real> &ijv, const ROL::Vector<Real> &v,
                              const ROL::Vector<Real> &u, const ROL::Vector<Real> &z, Real &tol) {
    Teuchos::RCP<std::vector<Real> > ijvp
      = Teuchos::dyn_cast<ROL::StdVector<Real> >(ijv).getVector();
    Teuchos::RCP<const std::vector<Real> > vp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(v).getVector();
    Teuchos::RCP<const std::vector<Real> > up
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(u).getVector();
    Teuchos::RCP<const std::vector<Real> > zp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(z).getVector();
    (*ijvp)[0] = (*vp)[0] / std::exp((*up)[0]);
  }

  void applyInverseAdjointJacobian_1(ROL::Vector<Real> &ijv, const ROL::Vector<Real> &v,
                                     const ROL::Vector<Real> &u, const ROL::Vector<Real> &z, Real &tol) {
    Teuchos::RCP<std::vector<Real> > ijvp
      = Teuchos::dyn_cast<ROL::StdVector<Real> >(ijv).getVector();
    Teuchos::RCP<const std::vector<Real> > vp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(v).getVector();
    Teuchos::RCP<const std::vector<Real> > up
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(u).getVector();
    Teuchos::RCP<const std::vector<Real> > zp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(z).getVector();
    (*ijvp)[0] = (*vp)[0] / std::exp((*up)[0]);
  }

  void applyAdjointHessian_11(ROL::Vector<Real> &ahwv, const ROL::Vector<Real> &w, const ROL::Vector<Real> &v,
                              const ROL::Vector<Real> &u, const ROL::Vector<Real> &z, Real &tol) {
    Teuchos::RCP<std::vector<Real> > ahwvp
      = Teuchos::dyn_cast<ROL::StdVector<Real> >(ahwv).getVector();
    Teuchos::RCP<const std::vector<Real> > wp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(w).getVector();
    Teuchos::RCP<const std::vector<Real> > vp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(v).getVector();
    Teuchos::RCP<const std::vector<Real> > up
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(u).getVector();
    Teuchos::RCP<const std::vector<Real> > zp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(z).getVector();
    (*ahwvp)[0] = std::exp((*up)[0]) * (*wp)[0] * (*vp)[0];
  }

  void applyAdjointHessian_12(ROL::Vector<Real> &ahwv, const ROL::Vector<Real> &w, const ROL::Vector<Real> &v,
                              const ROL::Vector<Real> &u, const ROL::Vector<Real> &z, Real &tol) {
    Teuchos::RCP<std::vector<Real> > ahwvp
      = Teuchos::dyn_cast<ROL::StdVector<Real> >(ahwv).getVector();
    Teuchos::RCP<const std::vector<Real> > wp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(w).getVector();
    Teuchos::RCP<const std::vector<Real> > vp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(v).getVector();
    Teuchos::RCP<const std::vector<Real> > up
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(u).getVector();
    Teuchos::RCP<const std::vector<Real> > zp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(z).getVector();
    (*ahwvp)[0] = static_cast<Real>(0);
  }

  void applyAdjointHessian_21(ROL::Vector<Real> &ahwv, const ROL::Vector<Real> &w, const ROL::Vector<Real> &v,
                              const ROL::Vector<Real> &u, const ROL::Vector<Real> &z, Real &tol) {
    Teuchos::RCP<std::vector<Real> > ahwvp
      = Teuchos::dyn_cast<ROL::StdVector<Real> >(ahwv).getVector();
    Teuchos::RCP<const std::vector<Real> > wp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(w).getVector();
    Teuchos::RCP<const std::vector<Real> > vp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(v).getVector();
    Teuchos::RCP<const std::vector<Real> > up
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(u).getVector();
    Teuchos::RCP<const std::vector<Real> > zp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(z).getVector();
    (*ahwvp)[0] = static_cast<Real>(0);
  }

  void applyAdjointHessian_22(ROL::Vector<Real> &ahwv, const ROL::Vector<Real> &w, const ROL::Vector<Real> &v,
                              const ROL::Vector<Real> &u, const ROL::Vector<Real> &z, Real &tol) {
    Teuchos::RCP<std::vector<Real> > ahwvp
      = Teuchos::dyn_cast<ROL::StdVector<Real> >(ahwv).getVector();
    Teuchos::RCP<const std::vector<Real> > wp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(w).getVector();
    Teuchos::RCP<const std::vector<Real> > vp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(v).getVector();
    Teuchos::RCP<const std::vector<Real> > up
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(u).getVector();
    Teuchos::RCP<const std::vector<Real> > zp
      = Teuchos::dyn_cast<const ROL::StdVector<Real> >(z).getVector();
    (*ahwvp)[0] = static_cast<Real>(-2) * (*wp)[0] * (*vp)[0];
  }
};

typedef double RealT;

int main(int argc, char *argv[]) {

  Teuchos::GlobalMPISession mpiSession(&argc, &argv);

  // This little trick lets us print to std::cout only if a (dummy) command-line argument is provided.
  int iprint     = argc - 1;
  Teuchos::RCP<std::ostream> outStream;
  Teuchos::oblackholestream bhs; // outputs nothing
  if (iprint > 0)
    outStream = Teuchos::rcp(&std::cout, false);
  else
    outStream = Teuchos::rcp(&bhs, false);

  int errorFlag  = 0;

  // *** Example body.

  try {

    int dim = 2;
    int dimz = 1;
    Teuchos::RCP<std::vector<RealT> > ustd  = Teuchos::rcp(new std::vector<RealT>(dim));
    Teuchos::RCP<std::vector<RealT> > dustd = Teuchos::rcp(new std::vector<RealT>(dim));
    Teuchos::RCP<std::vector<RealT> > zstd  = Teuchos::rcp(new std::vector<RealT>(dimz));
    Teuchos::RCP<std::vector<RealT> > dzstd = Teuchos::rcp(new std::vector<RealT>(dimz));
    Teuchos::RCP<std::vector<RealT> > cstd  = Teuchos::rcp(new std::vector<RealT>(dim));
    Teuchos::RCP<std::vector<RealT> > czstd = Teuchos::rcp(new std::vector<RealT>(dimz));
    Teuchos::RCP<std::vector<RealT> > sstd  = Teuchos::rcp(new std::vector<RealT>(dimz));
    Teuchos::RCP<std::vector<RealT> > dsstd = Teuchos::rcp(new std::vector<RealT>(dimz));

    (*ustd)[0]  = static_cast<RealT>(rand())/static_cast<RealT>(RAND_MAX);
    (*ustd)[1]  = static_cast<RealT>(rand())/static_cast<RealT>(RAND_MAX);
    (*dustd)[0] = static_cast<RealT>(rand())/static_cast<RealT>(RAND_MAX);
    (*dustd)[1] = static_cast<RealT>(rand())/static_cast<RealT>(RAND_MAX);
    (*zstd)[0]  = static_cast<RealT>(rand())/static_cast<RealT>(RAND_MAX);
    (*dzstd)[0] = static_cast<RealT>(rand())/static_cast<RealT>(RAND_MAX);
    (*cstd)[0]  = static_cast<RealT>(rand())/static_cast<RealT>(RAND_MAX);
    (*cstd)[1]  = static_cast<RealT>(rand())/static_cast<RealT>(RAND_MAX);
    (*czstd)[0] = static_cast<RealT>(rand())/static_cast<RealT>(RAND_MAX);
    (*sstd)[0]  = static_cast<RealT>(rand())/static_cast<RealT>(RAND_MAX);
    (*dsstd)[0] = static_cast<RealT>(rand())/static_cast<RealT>(RAND_MAX);

    Teuchos::RCP<ROL::Vector<RealT> > u  = Teuchos::rcp(new ROL::StdVector<RealT>(ustd));
    Teuchos::RCP<ROL::Vector<RealT> > du = Teuchos::rcp(new ROL::StdVector<RealT>(dustd));
    Teuchos::RCP<ROL::Vector<RealT> > z  = Teuchos::rcp(new ROL::StdVector<RealT>(zstd));
    Teuchos::RCP<ROL::Vector<RealT> > dz = Teuchos::rcp(new ROL::StdVector<RealT>(dzstd));
    Teuchos::RCP<ROL::Vector<RealT> > c  = Teuchos::rcp(new ROL::StdVector<RealT>(cstd));
    Teuchos::RCP<ROL::Vector<RealT> > cz = Teuchos::rcp(new ROL::StdVector<RealT>(czstd));
    Teuchos::RCP<ROL::Vector<RealT> > s  = Teuchos::rcp(new ROL::StdVector<RealT>(sstd));
    Teuchos::RCP<ROL::Vector<RealT> > ds = Teuchos::rcp(new ROL::StdVector<RealT>(dsstd));

    ROL::Vector_SimOpt<RealT> x(u,s);
    ROL::Vector_SimOpt<RealT> dx(du,ds);
    ROL::Vector_SimOpt<RealT> y(s,z);
    ROL::Vector_SimOpt<RealT> dy(ds,dz);
    ROL::Vector_SimOpt<RealT> w(u,z);
    ROL::Vector_SimOpt<RealT> dw(du,dz);

    Teuchos::RCP<ROL::EqualityConstraint_SimOpt<RealT> > valCon = Teuchos::rcp(new valConstraint<RealT>());
    valCon->checkAdjointConsistencyJacobian_1(*c,*du,*u,*s,true,*outStream);
    valCon->checkAdjointConsistencyJacobian_2(*c,*dz,*u,*s,true,*outStream);
    valCon->checkApplyJacobian_1(*u,*s,*du,*c,true,*outStream);
    valCon->checkApplyJacobian_2(*u,*s,*ds,*c,true,*outStream);
    valCon->checkApplyJacobian(x,dx,*c,true,*outStream);
    valCon->checkApplyAdjointHessian_11(*u,*s,*c,*du,*u,true,*outStream);
    valCon->checkApplyAdjointHessian_12(*u,*s,*c,*du,*s,true,*outStream);
    valCon->checkApplyAdjointHessian_21(*u,*s,*c,*ds,*u,true,*outStream);
    valCon->checkApplyAdjointHessian_22(*u,*s,*c,*ds,*s,true,*outStream);
    valCon->checkApplyAdjointHessian(x,*c,dx,x,true,*outStream);

    Teuchos::RCP<ROL::EqualityConstraint_SimOpt<RealT> > redCon = Teuchos::rcp(new redConstraint<RealT>());
    redCon->checkAdjointConsistencyJacobian_1(*cz,*ds,*s,*z,true,*outStream);
    redCon->checkAdjointConsistencyJacobian_2(*cz,*dz,*s,*z,true,*outStream);
    redCon->checkInverseJacobian_1(*cz,*ds,*s,*z,true,*outStream); 
    redCon->checkInverseAdjointJacobian_1(*ds,*cz,*s,*z,true,*outStream); 
    redCon->checkApplyJacobian_1(*s,*z,*ds,*cz,true,*outStream);
    redCon->checkApplyJacobian_2(*s,*z,*dz,*cz,true,*outStream);
    redCon->checkApplyJacobian(y,dy,*cz,true,*outStream);
    redCon->checkApplyAdjointHessian_11(*s,*z,*cz,*ds,*s,true,*outStream);
    redCon->checkApplyAdjointHessian_12(*s,*z,*cz,*ds,*z,true,*outStream);
    redCon->checkApplyAdjointHessian_21(*s,*z,*cz,*dz,*s,true,*outStream);
    redCon->checkApplyAdjointHessian_22(*s,*z,*cz,*dz,*z,true,*outStream);
    redCon->checkApplyAdjointHessian(y,*cz,dy,y,true,*outStream);

    ROL::CompositeEqualityConstraint_SimOpt<RealT> con(valCon,redCon,*c,*cz,*u,*s,*z);
    con.checkAdjointConsistencyJacobian_1(*c,*du,*u,*z,true,*outStream);
    con.checkAdjointConsistencyJacobian_2(*c,*dz,*u,*z,true,*outStream);
    con.checkApplyJacobian_1(*u,*z,*du,*c,true,*outStream);
    con.checkApplyJacobian_2(*u,*z,*dz,*c,true,*outStream);
    con.checkApplyJacobian(w,dw,*c,true,*outStream);
    con.checkApplyAdjointHessian_11(*u,*z,*c,*du,*u,true,*outStream);
    con.checkApplyAdjointHessian_12(*u,*z,*c,*du,*z,true,*outStream);
    con.checkApplyAdjointHessian_21(*u,*z,*c,*dz,*u,true,*outStream);
    con.checkApplyAdjointHessian_22(*u,*z,*c,*dz,*z,true,*outStream);
    con.checkApplyAdjointHessian(w,*c,dw,w,true,*outStream);
  }
  catch (std::logic_error err) {
    *outStream << err.what() << "\n";
    errorFlag = -1000;
  }; // end try

  if (errorFlag != 0)
    std::cout << "End Result: TEST FAILED\n";
  else
    std::cout << "End Result: TEST PASSED\n";

  return 0;

}

