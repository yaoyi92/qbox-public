////////////////////////////////////////////////////////////////////////////////
//
// SlaterDet.h
//
////////////////////////////////////////////////////////////////////////////////
// $Id: SlaterDet.h,v 1.12 2003-11-21 19:10:14 fgygi Exp $

#ifndef SLATERDET_H
#define SLATERDET_H

class FourierTransform;
#include "Context.h"
#include "Basis.h"
#include "Matrix.h"

#include "D3vector.h"
#include <vector>
#include <iostream>
#include "Timer.h"
#include <string>
#include <map>
#if USE_CSTDIO_LFS
#include <cstdio>
#endif
using namespace std;

typedef map<string,Timer> TimerMap;

class SlaterDet
{
  private:

  const Context& ctxt_;
  Basis basis_;
  ComplexMatrix c_;
  vector<double> occ_;
  vector<double> eig_;
  
  void byteswap_double(size_t n, double* x);
  double fermi(double e, double mu, double fermitemp);

  public:
  
  mutable TimerMap tmap;

  SlaterDet(const Context& ctxt, D3vector kpoint);
  SlaterDet(const SlaterDet& rhs);
  ~SlaterDet();
  const Context& context(void) const { return ctxt_; }
  const Basis& basis(void) const { return basis_; }
  const D3vector kpoint(void) const { return basis_.kpoint(); }
  const ComplexMatrix& c(void) const { return c_; }
  ComplexMatrix& c(void) { return c_; }
  const vector<double>& occ(void) const { return occ_; }
  const vector<double>& eig(void) const { return eig_; }
  int nst(void) const { return c_.n(); }
  int nstloc(void) const { return c_.nloc(); }
  void resize(const UnitCell& cell, const UnitCell& refcell,
              double ecut, int nst);
  double ekin(void) const;  // electronic kinetic energy
  void compute_density(FourierTransform& ft, double weight, double* rho) const;
  void rs_mul_add(FourierTransform& ft, double* v, SlaterDet& sdp) const;
  void randomize(double amplitude);
  void cleanup(void);
  void gram(void);
  void riccati(SlaterDet& sd);
  double total_charge(void);
  void update_occ(int nel, int nspin);
  void update_occ(int nspin, double mu, double temp);
  double eig(int i) const { return eig_[i]; };
  double occ(int i) const { return occ_[i]; };
  void set_occ(vector<double>& occ)
    { assert(occ_.size()==occ.size()); occ_ = occ; }
  void set_eig(vector<double>& eig)
    { assert(eig_.size()==eig.size()); eig_ = eig; }
  double entropy(int nspin);
  double ortho_error(void);
  double memsize(void) const;
  double localmemsize(void) const;
  SlaterDet& operator=(SlaterDet& rhs);
  void print(ostream& os, string encoding);
#if USE_CSTDIO_LFS
  void write(FILE* outfile, string encoding);
#endif
  void info(ostream& os);
};
ostream& operator << ( ostream& os, SlaterDet& sd );
#endif