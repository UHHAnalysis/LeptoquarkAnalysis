// $Id: LQCycle.cxx,v 1.3 2012/04/24 14:15:28 peiffer Exp $

#include <iostream>

using namespace std;

// Local include(s):
#include "../include/LQCycle.h"

                                                                  


ClassImp( LQCycle );


LQCycle::LQCycle(): AnalysisCycle() 
{
  // constructor, declare additional variables that should be 
  // obtained from the steering-xml file
  
  // set the integrated luminosity per bin for the lumi-yield control plots
  SetIntLumiPerBin(500.); 
}



LQCycle::~LQCycle() 
{
  // destructor
}



void LQCycle::BeginCycle() throw( SError ) 
{  
  // Start of the job, general set-up and definition of 
  // objects are done here
  
  // Important: first call BeginCycle of base class
  AnalysisCycle::BeginCycle();
  
  return;
}



void LQCycle::EndCycle() throw( SError ) 
{
  // clean-up, info messages and final calculations after the analysis
  
   
  // call the base cycle class for all standard methods
  // and a summary of the made selections
  AnalysisCycle::EndCycle();
  return;
 }



void LQCycle::BeginInputData( const SInputData& id ) throw( SError ) 
{
   // declaration of histograms and selections

  // Important: first call BeginInputData of base class
  
  AnalysisCycle::BeginInputData( id );

  // -------------------- set up the selections ---------------------------
 
  Selection* Trigger = new Selection("Trigger");
  Trigger -> addSelectionModule(new TriggerSelection("HLT_IsoMu24_eta2p1_v"));
  
  Selection* TauSelection = new Selection("TauSelection");
  TauSelection -> addSelectionModule(new NTauSelection(1,999,20,2.1));
 
  Selection* MuonSelection = new Selection("MuonSelection");
  MuonSelection -> addSelectionModule(new NMuonSelection(1,999,30,2.1));
  
  Selection* JetPreSelection = new Selection("JetPreSelection");
  JetPreSelection -> addSelectionModule(new NJetSelection(2,999,50,2.5));

  Selection* JetSelection = new Selection("JetSelection");
  JetSelection -> addSelectionModule(new NJetSelection(3,999,30,2.5));

  Selection* LeadingJetSelection = new Selection("LeadingJetSelection");
  LeadingJetSelection -> addSelectionModule(new NJetSelection(1,999,100,2.5));

  Selection* MET50Selection = new Selection("MET50Selection");
  MET50Selection -> addSelectionModule(new METCut(50,100000000));

  Selection* HT350Selection = new Selection("HT350Selection");
  HT350Selection -> addSelectionModule(new STCut(350,100000000));

  Selection* HT400Selection = new Selection("HT400Selection");
  HT400Selection -> addSelectionModule(new STCut(400,100000000));

  Selection* HT700Selection = new Selection("HT700Selection");
  HT700Selection -> addSelectionModule(new STCut(700,100000000));

  Selection* SameSignSelection = new Selection("SameSignSelection");
  SameSignSelection -> addSelectionModule(new SameSignCutHalil());

  Selection* OnebTagSelection = new Selection("OnebTagSelection");
  OnebTagSelection -> addSelectionModule(new NBTagSelection(1,999,e_CSVT));

  Selection* TwobTagSelection = new Selection("TwobTagSelection");
  TwobTagSelection -> addSelectionModule(new NBTagSelection(2,999,e_CSVT));

  Selection* LeadingJet150Selection = new Selection("LeadingJet150Selection"); 
  LeadingJet150Selection -> addSelectionModule(new NJetSelection(1,999,150,2.5));

  Selection* ThirdJet50Selection = new Selection("ThirdJet50Selection");
  ThirdJet50Selection -> addSelectionModule(new NJetSelection(3,999,50,2.5));

  Selection* MET100Selection = new Selection("MET100Selection");
  MET100Selection -> addSelectionModule(new METCut(100,100000000));

  Selection* RealTauSelection  = new Selection("RealTauSelection");
  RealTauSelection -> addSelectionModule(new GenTauSelection());

  Selection* FakeTausSelectionElectron  = new Selection("FakeTausSelectionElectron");
  FakeTausSelectionElectron -> addSelectionModule(new FakeTauSelectionElectron());
  
  Selection* MuonInvMass  = new Selection("MuonInvMass");
  MuonInvMass -> addSelectionModule(new MuonInvMassCut(80,100));

  Selection* HalilSelection  = new Selection("HalilSelection");
  HalilSelection -> addSelectionModule(new NMuonSelection(1,999,25,2.1));
  HalilSelection -> addSelectionModule(new NTauSelection(1,999,35,2.1));
  HalilSelection -> addSelectionModule(new SameSignCutHalil());
  
    
  RegisterSelection(Trigger);
  RegisterSelection(TauSelection);
  RegisterSelection(MuonSelection);
  RegisterSelection(MET50Selection);
  RegisterSelection(HT350Selection);  
  RegisterSelection(HT400Selection);
  RegisterSelection(HT700Selection);
  RegisterSelection(JetPreSelection);
  RegisterSelection(JetSelection);
  RegisterSelection(LeadingJetSelection);
  RegisterSelection(SameSignSelection);  
  RegisterSelection(OnebTagSelection);
  RegisterSelection(TwobTagSelection);
  RegisterSelection(LeadingJet150Selection);
  RegisterSelection(ThirdJet50Selection);
  RegisterSelection(MET100Selection);
  RegisterSelection(RealTauSelection);
  RegisterSelection(FakeTausSelectionElectron);
  RegisterSelection(HalilSelection);
  RegisterSelection(MuonInvMass);
  


  //---------------- set up the histogram collections -------------------- 

 RegisterHistCollection( new JetHists("Jets_PreSelection"));
 RegisterHistCollection( new TauHists("Taus_PreSelection"));
 RegisterHistCollection( new ElectronHists("Electrons_PreSelection"));
 RegisterHistCollection( new MuonHists("Muons_PreSelection"));
 RegisterHistCollection( new EventHists("Events_PreSelection"));

 RegisterHistCollection( new JetHists("Jets_Trigger"));
 RegisterHistCollection( new TauHists("Taus_Trigger"));
 RegisterHistCollection( new ElectronHists("Electrons_Trigger"));
 RegisterHistCollection( new MuonHists("Muons_Trigger"));
 RegisterHistCollection( new EventHists("Events_Trigger"));

 RegisterHistCollection( new JetHists("Jets_OneTauDecayModeFinding"));
 RegisterHistCollection( new TauHists("Taus_OneTauDecayModeFinding"));
 RegisterHistCollection( new ElectronHists("Electrons_OneTauDecayModeFinding"));
 RegisterHistCollection( new MuonHists("Muons_OneTauDecayModeFinding"));
 RegisterHistCollection( new EventHists("Events_OneTauDecayModeFinding"));

 RegisterHistCollection( new JetHists("Jets_OneTightTau"));
 RegisterHistCollection( new TauHists("Taus_OneTightTau"));
 RegisterHistCollection( new ElectronHists("Electrons_OneTightTau"));
 RegisterHistCollection( new MuonHists("Muons_OneTightTau"));
 RegisterHistCollection( new EventHists("Events_OneTightTau"));

 RegisterHistCollection( new JetHists("Jets_OneTightTau_WithoutCorrection"));
 RegisterHistCollection( new TauHists("Taus_OneTightTau_WithoutCorrection"));
 RegisterHistCollection( new ElectronHists("Electrons_OneTightTau_WithoutCorrection"));
 RegisterHistCollection( new MuonHists("Muons_OneTightTau_WithoutCorrection"));
 RegisterHistCollection( new EventHists("Events_OneTightTau_WithoutCorrection"));

 RegisterHistCollection( new JetHists("Jets_MET50"));
 RegisterHistCollection( new TauHists("Taus_MET50"));
 RegisterHistCollection( new ElectronHists("Electrons_MET50"));
 RegisterHistCollection( new MuonHists("Muons_MET50"));
 RegisterHistCollection( new EventHists("Events_MET50"));

 RegisterHistCollection( new JetHists("Jets_MediumSelection"));
 RegisterHistCollection( new TauHists("Taus_MediumSelection"));
 RegisterHistCollection( new ElectronHists("Electrons_MediumSelection"));
 RegisterHistCollection( new MuonHists("Muons_MediumSelection"));
 RegisterHistCollection( new EventHists("Events_MediumSelection"));

 RegisterHistCollection( new JetHists("Jets_MediumSelection_RealTauSelection"));
 RegisterHistCollection( new TauHists("Taus_MediumSelection_RealTauSelection"));
 RegisterHistCollection( new ElectronHists("Electrons_MediumSelection_RealTauSelection"));
 RegisterHistCollection( new MuonHists("Muons_MediumSelection_RealTauSelection"));
 RegisterHistCollection( new EventHists("Events_MediumSelection_RealTauSelection"));

 RegisterHistCollection( new JetHists("Jets_MediumSelection_FakeTauSelection"));
 RegisterHistCollection( new TauHists("Taus_MediumSelection_FakeTauSelection"));
 RegisterHistCollection( new ElectronHists("Electrons_MediumSelection_FakeTauSelection"));
 RegisterHistCollection( new MuonHists("Muons_MediumSelection_FakeTauSelection"));
 RegisterHistCollection( new EventHists("Events_MediumSelection_FakeTauSelection"));

 RegisterHistCollection( new JetHists("Jets_HT700"));
 RegisterHistCollection( new TauHists("Taus_HT700"));
 RegisterHistCollection( new ElectronHists("Electrons_HT700"));
 RegisterHistCollection( new MuonHists("Muons_HT700"));
 RegisterHistCollection( new EventHists("Events_HT700"));

 RegisterHistCollection( new JetHists("Jets_MediumSelection_HT700"));
 RegisterHistCollection( new TauHists("Taus_MediumSelection_HT700"));
 RegisterHistCollection( new ElectronHists("Electrons_MediumSelection_HT700"));
 RegisterHistCollection( new MuonHists("Muons_MediumSelection_HT700"));
 RegisterHistCollection( new EventHists("Events_MediumSelection_HT700"));

 RegisterHistCollection( new JetHists("Jets_LeadingJet100"));
 RegisterHistCollection( new TauHists("Taus_LeadingJet100"));
 RegisterHistCollection( new ElectronHists("Electrons_LeadingJet100"));
 RegisterHistCollection( new MuonHists("Muons_LeadingJet100"));
 RegisterHistCollection( new EventHists("Events_LeadingJet100"));

 RegisterHistCollection( new JetHists("Jets_LeadingJet150"));
 RegisterHistCollection( new TauHists("Taus_LeadingJet150"));
 RegisterHistCollection( new ElectronHists("Electrons_LeadingJet150"));
 RegisterHistCollection( new MuonHists("Muons_LeadingJet150"));
 RegisterHistCollection( new EventHists("Events_LeadingJet150"));

 RegisterHistCollection( new JetHists("Jets_ThirdJet30"));
 RegisterHistCollection( new TauHists("Taus_ThirdJet30"));
 RegisterHistCollection( new ElectronHists("Electrons_ThirdJet30"));
 RegisterHistCollection( new MuonHists("Muons_ThirdJet30"));
 RegisterHistCollection( new EventHists("Events_ThirdJet30"));

 RegisterHistCollection( new JetHists("Jets_ThirdJet50"));
 RegisterHistCollection( new TauHists("Taus_ThirdJet50"));
 RegisterHistCollection( new ElectronHists("Electrons_ThirdJet50"));
 RegisterHistCollection( new MuonHists("Muons_ThirdJet50"));
 RegisterHistCollection( new EventHists("Events_ThirdJet50"));

 RegisterHistCollection( new JetHists("Jets_MediumSelection_SameSignCut"));
 RegisterHistCollection( new TauHists("Taus_MediumSelection_SameSignCut"));
 RegisterHistCollection( new ElectronHists("Electrons_MediumSelection_SameSignCut"));
 RegisterHistCollection( new MuonHists("Muons_MediumSelection_SameSignCut"));
 RegisterHistCollection( new EventHists("Events_MediumSelection_SameSignCut"));

 RegisterHistCollection( new JetHists("Jets_MediumSelection_OnebTag"));
 RegisterHistCollection( new TauHists("Taus_MediumSelection_OnebTag"));
 RegisterHistCollection( new ElectronHists("Electrons_MediumSelection_OnebTag"));
 RegisterHistCollection( new MuonHists("Muons_MediumSelection_OnebTag"));
 RegisterHistCollection( new EventHists("Events_MediumSelection_OnebTag"));

 RegisterHistCollection( new JetHists("Jets_MediumSelection_TwobTags"));
 RegisterHistCollection( new TauHists("Taus_MediumSelection_TwobTags"));
 RegisterHistCollection( new ElectronHists("Electrons_MediumSelection_TwobTags"));
 RegisterHistCollection( new MuonHists("Muons_MediumSelection_TwobTags"));
 RegisterHistCollection( new EventHists("Events_MediumSelection_TwobTags"));

 RegisterHistCollection( new JetHists("Jets_HardSelection_SameSignCut"));
 RegisterHistCollection( new TauHists("Taus_HardSelection_SameSignCut"));
 RegisterHistCollection( new ElectronHists("Electrons_HardSelection_SameSignCut"));
 RegisterHistCollection( new MuonHists("Muons_HardSelection_SameSignCut"));
 RegisterHistCollection( new EventHists("Events_HardSelection_SameSignCut"));

 RegisterHistCollection( new JetHists("Jets_HardSelection"));
 RegisterHistCollection( new TauHists("Taus_HardSelection"));
 RegisterHistCollection( new ElectronHists("Electrons_HardSelection"));
 RegisterHistCollection( new MuonHists("Muons_HardSelection"));
 RegisterHistCollection( new EventHists("Events_HardSelection"));

 RegisterHistCollection( new JetHists("Jets_MediumSelection700_RealTauSelection"));
 RegisterHistCollection( new TauHists("Taus_MediumSelection700_RealTauSelection"));
 RegisterHistCollection( new ElectronHists("Electrons_MediumSelection700_RealTauSelection"));
 RegisterHistCollection( new MuonHists("Muons_MediumSelection700_RealTauSelection"));
 RegisterHistCollection( new EventHists("Events_MediumSelection700_RealTauSelection"));

 RegisterHistCollection( new JetHists("Jets_MediumSelection700_FakeTauSelection"));
 RegisterHistCollection( new TauHists("Taus_MediumSelection700_FakeTauSelection"));
 RegisterHistCollection( new ElectronHists("Electrons_MediumSelection700_FakeTauSelection"));
 RegisterHistCollection( new MuonHists("Muons_MediumSelection700_FakeTauSelection"));
 RegisterHistCollection( new EventHists("Events_MediumSelection700_FakeTauSelection"));

 RegisterHistCollection( new JetHists("Jets_SoftSelection"));
 RegisterHistCollection( new TauHists("Taus_SoftSelection"));
 RegisterHistCollection( new ElectronHists("Electrons_SoftSelection"));
 RegisterHistCollection( new MuonHists("Muons_SoftSelection"));
 RegisterHistCollection( new EventHists("Events_SoftSelection"));

 RegisterHistCollection( new JetHists("Jets_SoftSelection_SameSignCut"));
 RegisterHistCollection( new TauHists("Taus_SoftSelection_SameSignCut"));
 RegisterHistCollection( new ElectronHists("Electrons_SoftSelection_SameSignCut"));
 RegisterHistCollection( new MuonHists("Muons_SoftSelection_SameSignCut"));
 RegisterHistCollection( new EventHists("Events_SoftSelection_SameSignCut"));

 RegisterHistCollection( new JetHists("Jets_FakeTausElectrons"));
 RegisterHistCollection( new TauHists("Taus_FakeTausElectrons"));
 RegisterHistCollection( new ElectronHists("Electrons_FakeTausElectrons"));
 RegisterHistCollection( new MuonHists("Muons_FakeTausElectrons"));
 RegisterHistCollection( new EventHists("Events_FakeTausElectrons"));

 RegisterHistCollection( new JetHists("Jets_OverlapWithHalil_MediumSelection700"));
 RegisterHistCollection( new TauHists("Taus_OverlapWithHalil_MediumSelection700"));
 RegisterHistCollection( new ElectronHists("Electrons_OverlapWithHalil_MediumSelection700"));
 RegisterHistCollection( new MuonHists("Muons_OverlapWithHalil_MediumSelection700"));
 RegisterHistCollection( new EventHists("Events_OverlapWithHalil_MediumSelection700"));

 RegisterHistCollection( new JetHists("Jets_OverlapWithHalil_MediumSelection"));
 RegisterHistCollection( new TauHists("Taus_OverlapWithHalil_MediumSelection"));
 RegisterHistCollection( new ElectronHists("Electrons_OverlapWithHalil_MediumSelection"));
 RegisterHistCollection( new MuonHists("Muons_OverlapWithHalil_MediumSelection"));
 RegisterHistCollection( new EventHists("Events_OverlapWithHalil_MediumSelection"));

 RegisterHistCollection( new JetHists("Jets_NoOverlapWithHalil_MediumSelection700"));
 RegisterHistCollection( new TauHists("Taus_NoOverlapWithHalil_MediumSelection700"));
 RegisterHistCollection( new ElectronHists("Electrons_NoOverlapWithHalil_MediumSelection700"));
 RegisterHistCollection( new MuonHists("Muons_NoOverlapWithHalil_MediumSelection700"));
 RegisterHistCollection( new EventHists("Events_NoOverlapWithHalil_MediumSelection700"));

 RegisterHistCollection( new JetHists("Jets_NoOverlapWithHalil_MediumSelection"));
 RegisterHistCollection( new TauHists("Taus_NoOverlapWithHalil_MediumSelection"));
 RegisterHistCollection( new ElectronHists("Electrons_NoOverlapWithHalil_MediumSelection"));
 RegisterHistCollection( new MuonHists("Muons_NoOverlapWithHalil_MediumSelection"));
 RegisterHistCollection( new EventHists("Events_NoOverlapWithHalil_MediumSelection"));

 RegisterHistCollection( new JetHists("Jets_MuonInvMass"));
 RegisterHistCollection( new TauHists("Taus_MuonInvMass"));
 RegisterHistCollection( new ElectronHists("Electrons_MuonInvMass"));
 RegisterHistCollection( new MuonHists("Muons_MuonInvMass"));
 RegisterHistCollection( new EventHists("Events_MuonInvMass"));

 RegisterHistCollection( new JetHists("Jets_SameSignSelection_NoOverlap"));
 RegisterHistCollection( new TauHists("Taus_SameSignSelection_NoOverlap"));
 RegisterHistCollection( new ElectronHists("Electrons_SameSignSelection_NoOverlap"));
 RegisterHistCollection( new MuonHists("Muons_SameSignSelection_NoOverlap"));
 RegisterHistCollection( new EventHists("Events_SameSignSelection_NoOverlap"));

 RegisterHistCollection( new JetHists("Jets_OppositeSignSelection_NoOverlap"));
 RegisterHistCollection( new TauHists("Taus_OppositeSignSelection_NoOverlap"));
 RegisterHistCollection( new ElectronHists("Electrons_OppositeSignSelection_NoOverlap"));
 RegisterHistCollection( new MuonHists("Muons_OppositeSignSelection_NoOverlap"));
 RegisterHistCollection( new EventHists("Events_OppositeSignSelection_NoOverlap"));

  Double_t bins[5] = {20, 60, 120, 200, 800};
 Book( TH1F( "Gluon_pT_Tau","Gluon_pT_Tau",4,bins));
 Book( TH1F( "Gluon_pT_Tau_Halil","Gluon_pT_Tau_Halil",4,bins));
 
 Book( TH1F( "Up_SS_pT_Tau","Up_SS_pT_Tau",4,bins));
 Book( TH1F( "Up_SS_pT_Tau_Halil","Up_SS_pT_Tau_Halil",4,bins));
 
 Book( TH1F( "Down_SS_pT_Tau","Down_SS_pT_Tau",4,bins));
 Book( TH1F( "Down_SS_pT_Tau_Halil","Down_SS_pT_Tau_Halil",4,bins));
 
 Book( TH1F( "ChargeFlip_pT_Tau","ChargeFlip_pT_Tau",4,bins));
 Book( TH1F( "ChargeFlip_pT_Tau_Halil","ChargeFlip_pT_Tau_Halil",4,bins));




  // important: initialise histogram collections after their definition
  InitHistos();

  return;  
}



void LQCycle::EndInputData( const SInputData& id ) throw( SError ) 
{
  //LumiHandler()->PrintUsedSetup();
  
  AnalysisCycle::EndInputData( id );
  return;
}


void LQCycle::BeginInputFile( const SInputData& id ) throw( SError ) 
{
  // Connect all variables from the Ntuple file with the ones needed for the analysis
  // The variables are commonly stored in the BaseCycleContaincer
  
  // important: call to base function to connect all variables to Ntuples from the input tree
  AnalysisCycle::BeginInputFile( id );
  return;  
}



void LQCycle::ExecuteEvent( const SInputData& id, Double_t weight) throw( SError ) 
{ 
  
  // first step: call Execute event of base class to perform basic consistency checks
  // also, the good-run selection is performed there and the calculator is reset
  AnalysisCycle::ExecuteEvent( id, weight);
  
  // get the selections
  
  static Selection* Trigger = GetSelection("Trigger");
  static Selection* TauSelection = GetSelection("TauSelection");
  static Selection* MuonSelection = GetSelection("MuonSelection");
  static Selection* JetSelection = GetSelection("JetSelection");
  static Selection* JetPreSelection = GetSelection("JetPreSelection");
  static Selection* LeadingJetSelection = GetSelection("LeadingJetSelection");
  static Selection* MET50Selection = GetSelection("MET50Selection");
  static Selection* HT400Selection = GetSelection("HT400Selection");
  static Selection* HT700Selection = GetSelection("HT700Selection");
  static Selection* HT350Selection = GetSelection("HT350Selection");
  static Selection* SameSignSelection = GetSelection("SameSignSelection");
  static Selection* OnebTagSelection = GetSelection("OnebTagSelection");
  static Selection* TwobTagSelection = GetSelection("TwobTagSelection");
  static Selection* LeadingJet150Selection = GetSelection("LeadingJet150Selection");
  static Selection* ThirdJet50Selection = GetSelection("ThirdJet50Selection");
  static Selection* MET100Selection = GetSelection("MET100Selection");
  static Selection* RealTauSelection = GetSelection("RealTauSelection");
  static Selection* FakeTausSelectionElectron = GetSelection("FakeTausSelectionElectron");
  static Selection* HalilSelection = GetSelection("HalilSelection");
  static Selection* MuonInvMass = GetSelection("MuonInvMass");
  
  
  Cleaner cleaner;
  EventCalc* calc = EventCalc::Instance();
  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
  bool IsRealData = calc->IsRealData();
  
  TString samplename(id.GetVersion());
  if (samplename.Contains("W1Jets", TString::kIgnoreCase) || samplename.Contains("W2Jets", TString::kIgnoreCase) || samplename.Contains("W3Jets", TString::kIgnoreCase) || samplename.Contains("W4Jets", TString::kIgnoreCase)){
    calc -> ProduceWeight(m_jsf->GetWeight());
  }
  if (m_sys_unc==e_TER){
     if (m_sys_var==e_Up) cleaner.ApplyTERVariationUp();
     if (m_sys_var==e_Down) cleaner.ApplyTERVariationDown();
  }
  if (!bcc->isRealData && bcc->taus) cleaner.TauEnergyResolutionShifter();

  if (bcc->taus) cleaner.TauCleanerDecayModeFinding(20, 2.1);
  
  // trigger requirement
  if (!Trigger -> passSelection(bcc))  throw SError( SError::SkipEvent );
   FillControlHistos("_Trigger");
  
  std::vector<Muon> uncleaned_muons;
  for(unsigned int i=0; i<bcc->muons->size(); ++i) {
    uncleaned_muons.push_back(bcc->muons->at(i));
  }
  std::vector<Tau> uncleaned_taus;
  for(unsigned int i=0; i<bcc->taus->size(); ++i) {
    uncleaned_taus.push_back(bcc->taus->at(i));
  }

  // all muons tight, pT > 30 GeV 
  if (bcc-> muons) cleaner.MuonCleaner(30, 2.1,0.12); 

  // all jets loose PFId pT > 30GeV, eta < 2.5
  if (bcc->jets) cleaner.JetCleaner(30,2.5,true); 
  
  //HT >350 GeV
  if (!HT350Selection -> passSelection(bcc))  throw SError( SError::SkipEvent );  
  
  //at least two jets with pT> 50 GeV, eta < 2.5
  if (!JetPreSelection -> passSelection(bcc))  throw SError( SError::SkipEvent );  
  
  // at least one tight muon
  if (!MuonSelection -> passSelection(bcc))  throw SError( SError::SkipEvent ); 
  
  //PreSelection
  FillControlHistos("_PreSelection");

  // at least one tau decay mode finding pT>20 eta<2.1
  if (!TauSelection -> passSelection(bcc))  throw SError( SError::SkipEvent ); 
 
  
  if (!HT350Selection -> passSelection(bcc))  throw SError( SError::SkipEvent );  
  FillControlHistos("_OneTauDecayModeFinding");


  //if (MuonInvMass -> passSelection(bcc))  throw SError( SError::SkipEvent ); 
  FillControlHistos("_MuonInvMass");

  //------------------------------------Study of different selection----------------------------------------------------
  
   //all taus medium
  if (bcc-> taus) cleaner.TauCleaner(20, 2.1);   
  
   // at least one medium tau
  if (!TauSelection -> passSelection(bcc))  throw SError( SError::SkipEvent ); 
  
  //throw away all jets which have a distance smaller than DeltaR = 0.5 to a tau 
  if (bcc->jets) cleaner.JetLeptonOverlapRemoval(); 
  FillControlHistos("_OneTightTau_WithoutCorrection");

  // correction fake rate
  if (!IsRealData) calc -> ProduceWeight( m_lsf->GetTauWeight()); 

  // correction efficiency
  if (!IsRealData) calc -> ProduceWeight( m_lsf->GetTauEffUnc());    
  FillControlHistos("_OneTightTau");

  if (!IsRealData && FakeTausSelectionElectron -> passSelection(bcc)) FillControlHistos("_FakeTausElectrons");

  // at least three jets with pT > 30 GeV, eta < 2.5
  if (!JetSelection -> passSelection(bcc))  throw SError( SError::SkipEvent ); 
  FillControlHistos("_ThirdJet30");

  //MET > 50 GeV 
  if (!MET50Selection -> passSelection(bcc))  throw SError( SError::SkipEvent ); 
  FillControlHistos("_MET50");

  // at least one bTag 
  if (OnebTagSelection -> passSelection(bcc)) 
    {
      // soft selection
      FillControlHistos("_SoftSelection");
  
      if (SameSignSelection-> passSelection(bcc))
	{
	  // soft selection with same sign cut
      FillControlHistos("_SoftSelection_SameSignCut");
	}
    }

  // at least one jet with pT > 100 GeV, eta < 2.5
  if (!LeadingJetSelection -> passSelection(bcc))  throw SError( SError::SkipEvent ); 
   FillControlHistos("_LeadingJet100");


  // HT > 400 GeV
  if (!HT400Selection -> passSelection(bcc))  throw SError( SError::SkipEvent );

  // medium selection without bTag
  FillControlHistos("_MediumSelection");
  
  if (!IsRealData)
     {
        for (unsigned int i =0; i< bcc->taus->size(); ++i)
           {
              Tau tau = bcc->taus->at(i);
              bool IsElectronOrMuon = false;
        
              bool fake = true;
              for(unsigned int j=0; j<bcc->genparticles->size(); ++j)
                 {
                    GenParticle genp = bcc->genparticles->at(j);
                    double deltaR = genp.deltaR(tau);
                    if (deltaR < 0.5 && abs(genp.pdgId())==15) 
                       {
                          fake = false;
                          break;
                       }
                    if (deltaR < 0.5 && abs(genp.pdgId())==11 && genp.status()==3) 
                       {
                          IsElectronOrMuon =true; 
                          break;
                        }
                     if (deltaR < 0.5 && abs(genp.pdgId())==13 && genp.status()==3) 
                        {
                           IsElectronOrMuon =true;
                           break;
                        }
                  }
              if (fake && !IsElectronOrMuon) 
                  {
                     int PdgId_new = GenParticleMatching(tau);
                     if (PdgId_new ==21 || abs(PdgId_new) ==99)   Hist("Gluon_pT_Tau")->Fill(tau.pt(), weight);
                                          
                     if (((PdgId_new == 2 || PdgId_new == 4)&& tau.charge()==1)||((PdgId_new ==-2 || PdgId_new==-4)&& tau.charge()==-1))   Hist("Up_SS_pT_Tau")->Fill(tau.pt(), weight);
                                          
                     if (((PdgId_new ==1 || PdgId_new ==3 || PdgId_new ==5) && tau.charge()==1) || ((PdgId_new ==-1 || PdgId_new ==-3 || PdgId_new ==-5) && tau.charge()==-1)) Hist("Down_SS_pT_Tau")->Fill(tau.pt(), weight);
    
                     if (((PdgId_new ==1 || PdgId_new ==3 || PdgId_new ==5) && tau.charge()==-1) || ((PdgId_new ==-1 || PdgId_new ==-3 || PdgId_new ==-5) && tau.charge()==1) || ((PdgId_new ==2 || PdgId_new ==4) && tau.charge()==-1) || ((PdgId_new ==-2 || PdgId_new ==-4) && tau.charge()==1)) Hist("ChargeFlip_pT_Tau")->Fill(4, weight);   
                  }
           }
     }

  
  if (!IsRealData){
     if ( !RealTauSelection -> passSelection(bcc)) FillControlHistos("_MediumSelection_FakeTauSelection");
  }
  std::vector<Muon> muons_TightMareike;
  for(unsigned int i=0; i<bcc->muons->size(); ++i) {
     muons_TightMareike.push_back(bcc->muons->at(i));
  }
  std::vector<Tau> taus_MediumMareike;
  for(unsigned int i=0; i<bcc->taus->size(); ++i) {
     taus_MediumMareike.push_back(bcc->taus->at(i));
  }
  bcc->taus->clear();
  for(unsigned int i=0; i<uncleaned_taus.size(); ++i) 
    {
      bcc->taus->push_back(uncleaned_taus.at(i));
    }
  bcc->muons->clear();
  for(unsigned int i=0; i<uncleaned_muons.size(); ++i) 
    {
      bcc->muons->push_back(uncleaned_muons.at(i));
    }
  if (bcc-> taus) cleaner.TauCleanerHalil(20, 2.1);
  if (bcc-> muons) cleaner.MuonCleanerHalil(25, 2.1, 0.12);
  if (HalilSelection->passSelection(bcc))
    {
         FillControlHistos("_OverlapWithHalil_MediumSelection");
    }
  else 
     {
        FillControlHistos("_NoOverlapWithHalil_MediumSelection");

        for(unsigned int i=0; i<taus_MediumMareike.size(); ++i) 
           {
              bcc->taus->push_back(taus_MediumMareike.at(i));
           }
        bcc->muons->clear();
        for(unsigned int i=0; i<muons_TightMareike.size(); ++i) 
           {
              bcc->muons->push_back(muons_TightMareike.at(i));
           }
        if (SameSignSelection-> passSelection(bcc))  FillControlHistos("_SameSignSelection_NoOverlap");
        else  FillControlHistos("_OppositeSignSelection_NoOverlap");
        //if (IsRealData) cout <<"Medium selection: event number: "<<calc->GetEventNum()<<"run number: "<<calc->GetRunNum()<<"lumi section: "<<calc->GetLumiBlock()<<endl;

        if (!IsRealData)
           {
              for (unsigned int i =0; i< bcc->taus->size(); ++i)
                 {
                    Tau tau = bcc->taus->at(i);
                    bool IsElectronOrMuon = false;
                    
                    bool fake = true;
                    for(unsigned int j=0; j<bcc->genparticles->size(); ++j)
                       {
                          GenParticle genp = bcc->genparticles->at(j);
                          double deltaR = genp.deltaR(tau);
                          if (deltaR < 0.5 && abs(genp.pdgId())==15) 
                             {
                                fake = false;
                                break;
                             }
                          if (deltaR < 0.5 && abs(genp.pdgId())==11 && genp.status()==3) 
                             {
                                IsElectronOrMuon =true; 
                                break;
                             }
                          if (deltaR < 0.5 && abs(genp.pdgId())==13 && genp.status()==3) 
                             {
                                IsElectronOrMuon =true;
                                break;
                             }
                       }
                    if (fake && !IsElectronOrMuon) 
                       {
                          int PdgId_new = GenParticleMatching(tau);
                          if (PdgId_new ==21)   Hist("Gluon_pT_Tau_Halil")->Fill(tau.pt(), weight);
                                          
                          if (((PdgId_new == 2 || PdgId_new == 4)&& tau.charge()==1)||((PdgId_new ==-2 || PdgId_new==-4)&& tau.charge()==-1))   Hist("Up_SS_pT_Tau_Halil")->Fill(tau.pt(), weight);
                          
                          if (((PdgId_new ==1 || PdgId_new ==3 || PdgId_new ==5) && tau.charge()==1) || ((PdgId_new ==-1 || PdgId_new ==-3 || PdgId_new ==-5) && tau.charge()==-1)) Hist("Down_SS_pT_Tau_Halil")->Fill(tau.pt(), weight);
    
                          if (((PdgId_new ==1 || PdgId_new ==3 || PdgId_new ==5) && tau.charge()==-1) || ((PdgId_new ==-1 || PdgId_new ==-3 || PdgId_new ==-5) && tau.charge()==1) || ((PdgId_new ==2 || PdgId_new ==4) && tau.charge()==-1) || ((PdgId_new ==-2 || PdgId_new ==-4) && tau.charge()==1)) Hist("ChargeFlip_pT_Tau_Halil")->Fill(4, weight);   
                       }
                    
                 }
           }
        
        
        
     }
  for(unsigned int i=0; i<taus_MediumMareike.size(); ++i) 
     {
      bcc->taus->push_back(taus_MediumMareike.at(i));
    }
  bcc->muons->clear();
  for(unsigned int i=0; i<muons_TightMareike.size(); ++i) 
    {
      bcc->muons->push_back(muons_TightMareike.at(i));
    }
  if (HT700Selection -> passSelection(bcc)) 
    {
      // HT > 700 GeV
        FillControlHistos("_HT700");
   
      if (LeadingJet150Selection-> passSelection(bcc)) 
	{
	  // leading jet pT > 150 GeV
        FillControlHistos("_LeadingJet150");
	  
	  if (ThirdJet50Selection-> passSelection(bcc)) 
	    {
          FillControlHistos("_ThirdJet50");
	      
	      if (MET100Selection-> passSelection(bcc)) 
		{
		  // MET > 100 GeV
		  FillControlHistos("_HardSelection");
		  
      }
	    }
	}
    }

  // medium selection with at least one bTag                  
  if (OnebTagSelection -> passSelection(bcc)) FillControlHistos("_MediumSelection_OnebTag");
 
  // medium selection with same sign cut
    if (SameSignSelection-> passSelection(bcc) ) FillControlHistos("_MediumSelection_SameSignCut"); 

  // HT > 700 GeV, medium selection, without same sign but with b-tag
  if (HT700Selection -> passSelection(bcc)) 
     {
        FillControlHistos("_MediumSelection_HT700"); 
        bcc->taus->clear();
		  for(unsigned int i=0; i<uncleaned_taus.size(); ++i) 
           {
              bcc->taus->push_back(uncleaned_taus.at(i));
           }
		  bcc->muons->clear();
		  for(unsigned int i=0; i<uncleaned_muons.size(); ++i) 
		    {
             bcc->muons->push_back(uncleaned_muons.at(i));
		    }
		  if (bcc-> taus) cleaner.TauCleanerHalil(20, 2.1);
		  if (bcc-> muons) cleaner.MuonCleanerHalil(25, 2.1, 0.12);
		  if (HalilSelection->passSelection(bcc))
           {
                 FillControlHistos("_OverlapWithHalil_MediumSelection700");
           }
		  else 
           {
              FillControlHistos("_NoOverlapWithHalil_MediumSelection700");
              //if (IsRealData) cout <<"Medium HT700 selection: event number: "<<calc->GetEventNum()<<"run number: "<<calc->GetRunNum()<<"lumi section: "<<calc->GetLumiBlock()<<endl;
           }
		  for(unsigned int i=0; i<taus_MediumMareike.size(); ++i) 
           {
              bcc->taus->push_back(taus_MediumMareike.at(i));
           }
		  bcc->muons->clear();
		  for(unsigned int i=0; i<muons_TightMareike.size(); ++i) 
           {
              bcc->muons->push_back(muons_TightMareike.at(i));
           }
		  
		  if (!IsRealData && RealTauSelection->passSelection(bcc))
           {
                  FillControlHistos("_MediumSelection700_RealTauSelection");
           }
		  if (!IsRealData && !RealTauSelection->passSelection(bcc))
           {
                  FillControlHistos("_MediumSelection700_FakeTauSelection");
           }
		  
		}

  // medium selection with at least two btags
   if (TwobTagSelection -> passSelection(bcc))  FillControlHistos("_MediumSelection_TwobTags"); 
  
  
  return; 
 }



void LQCycle::FillControlHistos(TString postfix)
{
    // fill some control histograms, need to be defined in BeginInputData

    BaseHists* eventhists = GetHistCollection((std::string)("Events"+postfix));
    BaseHists* jethists = GetHistCollection((std::string)("Jets"+postfix));
    BaseHists* elehists = GetHistCollection((std::string)("Electrons"+postfix));
    BaseHists* muonhists = GetHistCollection((std::string)("Muons"+postfix));
    BaseHists* tauhists = GetHistCollection((std::string)("Taus"+postfix));
    
    eventhists->Fill();
    jethists->Fill();
    elehists->Fill();
    muonhists->Fill();
    tauhists->Fill();
}

int LQCycle::GenParticleMatching(Tau tau)
{
   EventCalc* calc = EventCalc::Instance();
   BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
   
   GenParticle genp_matched;
   double pT_max = 0;
   for (unsigned int i=0; i < bcc->genparticles->size(); ++i)
      {
         GenParticle genp = bcc->genparticles->at(i);
         double deltaR = tau.deltaR(genp);
         if (deltaR < 0.5 && genp.status() == 3) 
            {
               if (genp.pt() > pT_max)
                  {
                     if (abs(genp.pdgId())==1 || abs(genp.pdgId())==2 || abs(genp.pdgId())==3 || abs(genp.pdgId())==4 || abs(genp.pdgId())==5 || abs(genp.pdgId())==6 || abs(genp.pdgId())==21) 
                        {
                           genp_matched = genp;
                           pT_max = genp.pt();   
                        }
                  }
            }
      }
   if (pT_max > 0 ) return genp_matched.pdgId();
   else return 99;
}

