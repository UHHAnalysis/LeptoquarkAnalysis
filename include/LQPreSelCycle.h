// Dear emacs, this is -*- c++ -*-

// $Id: LeptoquarkCycle.h,v 1.4 2012/06/12 13:50:24 rkogler Exp $

#ifndef LQPreSelCycle_H
#define LQPreSelCycle_H

// SFrame include(s):
#include "AnalysisCycle.h"
#include "Cleaner.h"
#include "FactorizedJetCorrector.h"
#include "JetCorrectorParameters.h"
#include "JetCorrectionUncertainty.h"
#include "../include/EventCalc.h" 
#include "../include/SelectionModules.h" 

#include "../include/MuonHists.h" 
#include "../include/TopJetHists.h" 
#include "../include/EventHists.h" 
#include "../include/JetHists.h"  
#include "../include/TauHists.h" 
#include "../include/ElectronHists.h"
/**
 *   @short Put short description of class here
 *
 *          Put a longer description over here...
 *
 *  @author Put your name here

 * @version $Revision: 1.4 $

 */


class LQPreSelCycle : public AnalysisCycle {

public:
   /// Default constructor
   LQPreSelCycle();
   /// Default destructor
   ~LQPreSelCycle();

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
  
        
private:
   //
   // Put all your private variables here
   //
  JetCorrectionUncertainty* m_jes_unc;
  // Macro adding the functions for dictionary generation
  ClassDef( LQPreSelCycle, 0 );
   

}; // class LQPreSelCycle


#endif // LQPreSelCycle_H

