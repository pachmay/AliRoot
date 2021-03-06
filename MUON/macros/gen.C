/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

/* $Id$ */

/// \ingroup macros
/// \file gen.C
/// \brief Configuration macro for generation of kinematics tree which 
/// can be then used as an external event generator.
///
/// According to: $ALICE_ROOT/test/genkine/gen/fastGen.C

#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include <TH1F.h>
#include <TStopwatch.h>
#include <TDatime.h>
#include <TRandom.h>
#include <TDatabasePDG.h>
#include <TParticle.h>
#include <TArrayI.h>

#include "AliGenerator.h"
#include "AliPDG.h"
#include "AliRunLoader.h"
#include "AliRun.h"
#include "AliStack.h"
#include "AliHeader.h"
#include "PYTHIA6/AliGenPythia.h"
#include "PYTHIA6/AliPythia.h"
#endif

void gen(Int_t nev = 1, 
         const char* genConfig = "$ALICE_ROOT/MUON/macros/genTestConfig.C")
{
  // Load libraries
  // gSystem->SetIncludePath("-I$ROOTSYS/include -I$ALICE_ROOT/include -I$ALICE_ROOT");
  gSystem->Load("liblhapdf");      // Parton density functions
  gSystem->Load("libEGPythia6");   // TGenerator interface
  gSystem->Load("libpythia6");     // Pythia
  gSystem->Load("libAliPythia6");  // ALICE specific implementations

  AliPDG::AddParticlesToPdgDataBase();
  TDatabasePDG::Instance();

  // Run loader
  AliRunLoader* rl = AliRunLoader::Open("galice.root","FASTRUN","recreate");
  
  rl->SetCompressionLevel(2);
  rl->SetNumberOfEventsPerFile(nev);
  rl->LoadKinematics("RECREATE");
  rl->MakeTree("E");
  gAlice->SetRunLoader(rl);
  
  //  Create stack
  rl->MakeStack();
  AliStack* stack = rl->Stack();
  
  //  Header
  AliHeader* header = rl->GetHeader();
  
  //  Create and Initialize Generator
  gROOT->LoadMacro(genConfig);
  AliGenerator* gener = genConfig();

  // Go to galice.root
  rl->CdGAFile();

  // Forbid some decays. Do it after gener->Init(0, because
  // the initialization of the generator includes reading of the decay table.
  // ...

  //
  // Event Loop
  //
  
  TStopwatch timer;
  timer.Start();
  for (Int_t iev = 0; iev < nev; iev++) {
    
    cout <<"Event number "<< iev << endl;
    
    // Initialize event
    header->Reset(0,iev);
    rl->SetEventNumber(iev);
    stack->Reset();
    rl->MakeTree("K");
    
    // Generate event
    stack->Reset();
    stack->ConnectTree(rl->TreeK());
    gener->Generate();
    cout << "Number of particles " << stack->GetNprimary() << endl;
    
    // Finish event
    header->SetNprimary(stack->GetNprimary());
    header->SetNtrack(stack->GetNtrack());  
    
    // I/O
    stack->FinishEvent();
    header->SetStack(stack);
    rl->TreeE()->Fill();
    rl->WriteKinematics("OVERWRITE");
    
  } // event loop
  timer.Stop();
  timer.Print();
  
  //                         Termination
  //  Generator
  gener->FinishRun();
  //  Write file
  rl->WriteHeader("OVERWRITE");
  gener->Write();
  rl->Write();
}
