#ifndef TOFv1_H
#define TOFv1_H
/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

/* $Id$ */

///////////////////////////////////////////////////////
//  Manager and hits classes for set:TOF  version 1  //
///////////////////////////////////////////////////////
 
#include "AliTOF.h"
#include "AliHit.h"
 
 
class AliTOFv1 : public AliTOF {

private:
  Int_t fIdFTOA;
  Int_t fIdFTOB; // First sensitive volume identifier
  Int_t fIdFTOC; // Second sensitive volume identifier
  Int_t fIdFLTA; // Third sensitive volume identifier
  Int_t fIdFLTB; // Fourth sensitive volume identifier
  Int_t fIdFLTC; // Fifth sensitive volume identifier
 
public:
  AliTOFv1();
  AliTOFv1(const char *name, const char *title);
  virtual       ~AliTOFv1() {}
  virtual void   BuildGeometry();
  virtual void   CreateGeometry();
  virtual void   CreateMaterials();
  virtual void   Init();
  virtual Int_t  IsVersion() const {return 1;}
  virtual void   TOFpc(Float_t,Float_t,Float_t,Float_t,Float_t,Float_t);
  virtual void   StepManager();
  virtual void   DrawModule();
 
   ClassDef(AliTOFv1,1)  //Time Of Flight version 1
};
 
#endif
