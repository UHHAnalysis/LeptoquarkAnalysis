// $Id: LeptoquarkCycle.cxx,v 1.3 2012/04/24 14:15:28 peiffer Exp $

#include <iostream>

using namespace std;

// Local include(s):
#include "../include/LQPreSelCycle.h"



ClassImp( LQPreSelCycle );


LQPreSelCycle::LQPreSelCycle()
  : AnalysisCycle() 
{
  // constructor, declare additional variables that should be 
  // obtained from the steering-xml file
  
  // set the integrated luminosity per bin for the lumi-yield control plots
  SetIntLumiPerBin(500.); 
  
  m_corrector = NULL;
  m_jes_unc = NULL;
  
  m_sys_var = e_Default;
  m_sys_unc = e_None;
  
}



LQPreSelCycle::~LQPreSelCycle() 
{
  // destructor
}



void LQPreSelCycle::BeginCycle() throw( SError ) 
{  
  // Start of the job, general set-up and definition of 
  // objects are done here
  
  // Important: first call BeginCycle of base class
  AnalysisCycle::BeginCycle();
  
  return;
}



void LQPreSelCycle::EndCycle() throw( SError ) 
{
  // clean-up, info messages and final calculations after the analysis
  
   
  // call the base cycle class for all standard methods
  // and a summary of the made selections
  AnalysisCycle::EndCycle();
  return;
 }



void LQPreSelCycle::BeginInputData( const SInputData& id ) throw( SError ) 
{
  // Important: first call BeginInputData of base class
  AnalysisCycle::BeginInputData( id );
  
  // -------------------- set up the selections ---------------------------
  
  Selection* VertexSelection = new Selection("VertexSelection");
  VertexSelection -> addSelectionModule(new NPrimaryVertexSelection(1)); //at least one good PV
  
  Selection* MuonSelection = new Selection("MuonSelection");
  MuonSelection -> addSelectionModule(new NMuonSelection(1,999,25,2.1));
  
  Selection* JetSelection = new Selection("JetSelection");
  JetSelection -> addSelectionModule(new NJetSelection(2,999,50,3.0));
  
  Selection* TauSelection = new Selection("TauSelection");
  TauSelection -> addSelectionModule(new NTauSelection(1,999,20,2.1));
  
  Selection* HTSelection = new Selection("HTSelection");
  HTSelection -> addSelectionModule(new STCut(350,100000000));

   
  RegisterSelection(VertexSelection);
  RegisterSelection(MuonSelection);
  RegisterSelection(JetSelection);
  RegisterSelection(TauSelection);
  RegisterSelection(HTSelection);
  
  
  
      
  // uncertainty
  TString unc_file = m_JECFileLocation + "/" + m_JECDataGlobalTag + "_Uncertainty_" + m_JECJetCollection + ".txt";
  m_jes_unc = new JetCorrectionUncertainty(unc_file.Data());         
  

  // ---------------- set up the histogram collections --------------------- 
  
  
  // important: initialise histogram collections after their definition
  InitHistos();

  return;  
}



void LQPreSelCycle::EndInputData( const SInputData& id ) throw( SError ) 
{ 
  AnalysisCycle::EndInputData( id );
  return;
}


void LQPreSelCycle::BeginInputFile( const SInputData& id ) throw( SError ) 
{
  // Connect all variables from the Ntuple file with the ones needed for the analysis
  // The variables are commonly stored in the BaseCycleContaincer

  // important: call to base function to connect all variables to Ntuples from the input tree
  AnalysisCycle::BeginInputFile( id );
  return;  
}



void LQPreSelCycle::ExecuteEvent( const SInputData& id, Double_t weight) throw( SError ) 
{ 
  
  // first step: call Execute event of base class to perform basic consistency checks
  // also, the good-run selection is performed there and the calculator is reset
  AnalysisCycle::ExecuteEvent( id, weight);

  // get the selections
  static Selection* VertexSelection = GetSelection("VertexSelection");
  static Selection* MuonSelection = GetSelection("MuonSelection");
  static Selection* JetSelection = GetSelection("JetSelection");
  static Selection* TauSelection = GetSelection("TauSelection");
  static Selection* HTSelection = GetSelection("HTSelection");
 
  
  Cleaner cleaner;
  cleaner.SetJECUncertainty(m_jes_unc);
  
  // settings for jet correction uncertainties
  if (m_sys_unc==e_JEC){
    if (m_sys_var==e_Up) cleaner.ApplyJECVariationUp();
    if (m_sys_var==e_Down) cleaner.ApplyJECVariationDown();
  }
  if (m_sys_unc==e_JER){
    if (m_sys_var==e_Up) cleaner.ApplyJERVariationUp();
    if (m_sys_var==e_Down) cleaner.ApplyJERVariationDown();
  }
  
  EventCalc* calc = EventCalc::Instance();
  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
  bool IsRealData = calc->IsRealData();
  
  if (bcc->jets) cleaner.JetRecorrector(m_corrector,true);
  if (!bcc->isRealData && bcc->jets) cleaner.JetEnergyResolutionShifter();
  if (bcc->jets) cleaner.JetCleaner(30,3.0,true);
  if (bcc->pvs)  cleaner.PrimaryVertexCleaner(4, 24., 2.);
  if (bcc->muons) cleaner.MuonCleaner_Loose(25,2.1);  
  if (bcc->taus) cleaner.TauCleanerDecayModeFinding(20, 2.1);
    
  // at least one good primary vertex
  if (!VertexSelection->passSelection(bcc))  throw SError( SError::SkipEvent );
  
  // at least one loose muon pT > 25 GeV, |eta| < 2.1
  if (!MuonSelection -> passSelection(bcc) ) throw SError( SError::SkipEvent );
    
  // at least two jets pT > 50, |eta| < 3.0
  if (!JetSelection -> passSelection(bcc) ) throw SError( SError::SkipEvent );
    
  // HT > 350 GeV
  if (!HTSelection -> passSelection(bcc))  throw SError( SError::SkipEvent );


  WriteOutputTree();
  
  return;
}



