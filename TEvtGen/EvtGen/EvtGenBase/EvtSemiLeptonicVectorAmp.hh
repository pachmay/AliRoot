//--------------------------------------------------------------------------
//
// Environment:
//      This software is part of the EvtGen package developed jointly
//      for the BaBar and CLEO collaborations.  If you use all or part
//      of it, please give an appropriate acknowledgement.
//
// Copyright Information: See EvtGen/COPYRIGHT
//      Copyright (C) 1998      Caltech, UCSB
//
// Module: EvtGen/EvtSemiLeptonicVectorAmp.hh
//
// Description: Class for calcultaion of amplitude for semileptonic
//              decay to a vector particle.
//
// Modification history:
//
//    DJL/RYD     August 11, 1998         Module created
//
//------------------------------------------------------------------------

#ifndef EVTSEMILEPTONICVECTORAMP_HH
#define EVTSEMILEPTONICVECTORAMP_HH

#include "EvtGenBase/EvtSemiLeptonicAmp.hh"

class EvtParticle;
class EvtAmp;
class EvtSemiLeptonicFF;

class EvtSemiLeptonicVectorAmp:public EvtSemiLeptonicAmp {

 public:

  //Daughters are initialized and have been added to the parent.
  //No need to carry around the daughters seperately!
  void CalcAmp( EvtParticle *parent,EvtAmp& amp,
		EvtSemiLeptonicFF *FormFactors );

};

#endif

