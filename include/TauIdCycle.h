// Dear emacs, this is -*- c++ -*-



#ifndef TauIdCycle_H
#define TauIdCycle_H

// SFrame include(s):
#include "AnalysisCycle.h"
#include "Cleaner.h"
#include "FactorizedJetCorrector.h"
#include "JetCorrectorParameters.h"
#include "JetCorrectionUncertainty.h"
#include "../include/SelectionModules.h" 
#include "../include/EventCalc.h" 

#include "../include/TopJetHists.h" 
#include "../include/EventHists.h" 
#include "../include/JetHists.h" 
#include "../include/TauHists.h" 
#include "../include/ElectronHists.h"
#include "../include/MuonHists.h"

/**
 *   @short Put short description of class here
 *
 *          Put a longer description over here...
 *
 *  @author Put your name here

 * @version $Revision: 1.4 $

 */


class TauIdCycle : public AnalysisCycle {

public:
   /// Default constructor
   TauIdCycle();
   /// Default destructor
   ~TauIdCycle();
   
   /// Function called at the beginning of the cycle
   virtual void BeginCycle() throw( SError );
   /// Function called at the end of the cycle
   virtual void EndCycle() throw( SError );
   
   /// Function called at the beginning of a new input data
   virtual void BeginInputData( const SInputData& ) throw( SError );
   /// Function called after finishing to process an input data
   virtual void EndInputData  ( const SInputData& ) throw( SError );
   
   /// Function called after opening each new input file
   virtual void BeginInputFile( const SInputData& ) throw( SError );
   
   /// Function called for every event
   virtual void ExecuteEvent( const SInputData&, Double_t ) throw( SError );
   
   /// Fill control histograms
   virtual void FillControlHistos(TString postfix="");
   
   virtual int Matching(Tau tau, vector<Jet> jets);

   virtual int GenParticleMatching(Tau tau);
   

private:
   //
   // Put all your private variables here
   //
  JetCorrectionUncertainty* m_jes_unc;
  // Macro adding the functions for dictionary generation
  ClassDef( TauIdCycle, 0 );
  FactorizedJetCorrector* m_corrector;

 
}; // class TauIdCycle


#endif // TauIdCycle_H

