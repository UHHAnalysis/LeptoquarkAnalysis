#include <iostream>

using namespace std;

// Local include(s):
#include "../include/TauIdPreSelCycle.h"


ClassImp( TauIdPreSelCycle );


TauIdPreSelCycle::TauIdPreSelCycle()
  : AnalysisCycle() 
{
  // constructor, declare additional variables that should be 
  // obtained from the steering-xml file
  
  // set the integrated luminosity per bin for the lumi-yield control plots
  SetIntLumiPerBin(25.); 

  m_corrector = NULL;
  m_jes_unc = NULL;
  
  m_sys_var = e_Default;
  m_sys_unc = e_None;
  
}


TauIdPreSelCycle::~TauIdPreSelCycle() 
{
  // destructor
}



void TauIdPreSelCycle::BeginCycle() throw( SError ) 
{  
  // Start of the job, general set-up and definition of 
  // objects are done here
  
  // Important: first call BeginCycle of base class
  AnalysisCycle::BeginCycle();
  return;
}



void TauIdPreSelCycle::EndCycle() throw( SError ) 
{
  // clean-up, info messages and final calculations after the analysis
     
  // call the base cycle class for all standard methods
  // and a summary of the made selections
  AnalysisCycle::EndCycle();
  return;
 }



void TauIdPreSelCycle::BeginInputData( const SInputData& id ) throw( SError ) 
{
  // Important: first call BeginInputData of base class
  AnalysisCycle::BeginInputData( id );
    
  
  std::vector<JetCorrectorParameters> pars;
  
  //    //see https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetEnergyCorrections#GetTxtFiles how to get the txt files with jet energy corrections from the database
  if(!addGenInfo()) {
    pars.push_back(JetCorrectorParameters(m_JECFileLocation + "/" + m_JECDataGlobalTag + "_L1FastJet_" + m_JECJetCollection + ".txt"));
    pars.push_back(JetCorrectorParameters(m_JECFileLocation + "/" + m_JECDataGlobalTag + "_L2Relative_" + m_JECJetCollection + ".txt"));
    pars.push_back(JetCorrectorParameters(m_JECFileLocation + "/" + m_JECDataGlobalTag + "_L3Absolute_" + m_JECJetCollection + ".txt"));
    pars.push_back(JetCorrectorParameters(m_JECFileLocation + "/" + m_JECDataGlobalTag + "_L2L3Residual_" + m_JECJetCollection + ".txt"));
  } else {
    pars.push_back(JetCorrectorParameters(m_JECFileLocation + "/" + m_JECMCGlobalTag + "_L1FastJet_" + m_JECJetCollection + ".txt"));
    pars.push_back(JetCorrectorParameters(m_JECFileLocation + "/" + m_JECMCGlobalTag + "_L2Relative_" + m_JECJetCollection + ".txt"));
    pars.push_back(JetCorrectorParameters(m_JECFileLocation + "/" + m_JECMCGlobalTag + "_L3Absolute_" + m_JECJetCollection + ".txt"));
  }
  
  m_corrector = new FactorizedJetCorrector(pars);
  
  // uncertainty
  TString unc_file = m_JECFileLocation + "/" + m_JECDataGlobalTag + "_Uncertainty_" + m_JECJetCollection + ".txt";
  m_jes_unc = new JetCorrectionUncertainty(unc_file.Data());
  
  if (GetSysUncName()=="JEC" || GetSysUncName()=="jec") m_sys_unc = e_JEC; 
  if (GetSysUncName()=="JER" || GetSysUncName()=="jer") m_sys_unc = e_JER;
  if (m_sys_unc != e_None){
    if (GetSysShiftName()=="UP" || GetSysShiftName()=="up" || GetSysShiftName()=="Up") m_sys_var = e_Up; 
    if (GetSysShiftName()=="DOWN" || GetSysShiftName()=="down" || GetSysShiftName()=="Down") m_sys_var = e_Down; 
  }       
  
  Selection* PreSelection = new Selection("PreSelection");

  PreSelection -> addSelectionModule(new NPrimaryVertexSelection(1)); //at least one good PV
  PreSelection -> addSelectionModule(new NMuonSelection(1,1,30,2.1));
  PreSelection -> addSelectionModule(new NJetSelection(2,999,30,3.5));
  PreSelection -> addSelectionModule(new NTauSelection(1,1,20,2.1));
  PreSelection -> addSelectionModule(new METCut(40,10000000));
  PreSelection -> addSelectionModule(new TriggerSelection("HLT_IsoMu24_eta2p1_v"));
    
  RegisterSelection(PreSelection);
  
  
  // ---------------- set up the histogram collections -------------------- 
  
  RegisterHistCollection( new JetHists("Jets"));
  RegisterHistCollection( new TopJetHists("TopJets"));
  RegisterHistCollection( new EventHists("Events"));
  RegisterHistCollection( new MuonHists("Muons"));
  RegisterHistCollection( new TauHists("Taus"));
  RegisterHistCollection( new ElectronHists("Electrons"));
  
  // important: initialise histogram collections after their definition
  InitHistos();
  
  return;  
}



void TauIdPreSelCycle::EndInputData( const SInputData& id ) throw( SError ) 
{ 
  AnalysisCycle::EndInputData( id );
  return;
}


void TauIdPreSelCycle::BeginInputFile( const SInputData& id ) throw( SError ) 
{
  // Connect all variables from the Ntuple file with the ones needed for the analysis
  // The variables are commonly stored in the BaseCycleContaincer

  // important: call to base function to connect all variables to Ntuples from the input tree
  AnalysisCycle::BeginInputFile( id );
  return;  
}



void TauIdPreSelCycle::ExecuteEvent( const SInputData& id, Double_t weight) throw( SError ) 
{ 
  
  // first step: call Execute event of base class to perform basic consistency checks
  // also, the good-run selection is performed there and the calculator is reset
  AnalysisCycle::ExecuteEvent( id, weight);
   
  // get the selections
  
  static Selection* PreSelection = GetSelection("PreSelection");
  
   
  // get the histogram collections
  
  
  BaseHists* HistsJets = GetHistCollection("Jets");
  BaseHists* HistsTopJets = GetHistCollection("TopJets");
  BaseHists* HistsHT = GetHistCollection("Events");
  BaseHists* HistsMuons = GetHistCollection("Muons");
  BaseHists* HistsTaus = GetHistCollection("Taus");
  BaseHists* HistsElectrons = GetHistCollection("Electrons");

  
  Cleaner cleaner;
  
  EventCalc* calc = EventCalc::Instance();
  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
  bool IsRealData = calc->IsRealData();
 
  if (bcc->jets) cleaner.JetRecorrector(m_corrector,true);
  if (!bcc->isRealData && bcc->jets) cleaner.JetEnergyResolutionShifter();
  if (bcc->pvs)  cleaner.PrimaryVertexCleaner(4, 24., 2.);
  if (bcc->electrons) cleaner.ElectronCleaner(15,2.5,0.1);
  if (bcc->muons) cleaner.MuonCleaner(30,2.1);  
  if (bcc-> taus) cleaner.TauCleanerDecayModeFinding(20, 2.1);
  
  if (!PreSelection->passSelection(bcc))  throw SError( SError::SkipEvent );
  
  HistsJets -> Fill();
  HistsTopJets -> Fill();
  HistsMuons -> Fill();
  HistsTaus -> Fill();
  HistsElectrons  -> Fill();
  HistsEvents -> Fill();
  
  WriteOutputTree();

  return;

}

