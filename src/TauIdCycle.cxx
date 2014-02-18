#include <iostream>

using namespace std;

// Local include(s):
#include "../include/TauIdCycle.h"


ClassImp( TauIdCycle );


TauIdCycle::TauIdCycle()
  : AnalysisCycle() 
{
  // constructor, declare additional variables that should be 
  // obtained from the steering-xml file
  
  // set the integrated luminosity per bin for the lumi-yield control plots
  SetIntLumiPerBin(500.); 
  
}



TauIdCycle::~TauIdCycle() 
{
  // destructor
}



void TauIdCycle::BeginCycle() throw( SError ) 
{  
  // Start of the job, general set-up and definition of 
  // objects are done here
  
  // Important: first call BeginCycle of base class
  AnalysisCycle::BeginCycle();
  return;
}



void TauIdCycle::EndCycle() throw( SError ) 
{
  // clean-up, info messages and final calculations after the analysis
  
  // call the base cycle class for all standard methods
  // and a summary of the made selections
  AnalysisCycle::EndCycle();
  return;
 }



void TauIdCycle::BeginInputData( const SInputData& id ) throw( SError ) 
{
  // Important: first call BeginInputData of base class
  AnalysisCycle::BeginInputData( id );
  // -------------------- set up the selections ---------------------------
  
  Selection* JetSelection =  new Selection("JetSelection");
  JetSelection -> addSelectionModule(new NJetSelection(1,999,30,2.5)); 

  Selection* AntibTagSelection = new Selection("AntibTagSelection");
  AntibTagSelection -> addSelectionModule(new NBTagSelection(1,999,e_CSVL));

  Selection* InvMassSelection  = new Selection("InvMassSelection");
  InvMassSelection -> addSelectionModule(new TauMuonInvMassCut(80,100));

  Selection* RealTauSelection  = new Selection("RealTauSelection");
  RealTauSelection -> addSelectionModule(new GenTauSelection());

  Selection* TauSelection = new Selection("TauSelection");
  TauSelection -> addSelectionModule(new NTauSelection(1,999,20,2.1));

  Selection* OneTauSelection = new Selection("OneTauSelection");
  OneTauSelection -> addSelectionModule(new NTauSelection(1,1,20,2.1));

  Selection* OneJetSelection =  new Selection("OneJetSelection");
  OneJetSelection -> addSelectionModule(new NJetSelection(1,1,30,2.1)); 

  Selection* METSelection = new Selection("METSelection");
  METSelection -> addSelectionModule(new METCut(40,10000000));

  Selection* SameSignSelection = new Selection("SameSignSelection");
  SameSignSelection -> addSelectionModule(new SameSignCut());
  
  Selection* HalilSelection  = new Selection("HalilSelection");
  HalilSelection -> addSelectionModule(new NMuonSelection(1,999,25,2.1));
  HalilSelection -> addSelectionModule(new NTauSelection(1,999,35,2.1));
  HalilSelection -> addSelectionModule(new SameSignCut());
  

  RegisterSelection(JetSelection);
  RegisterSelection(AntibTagSelection);
  RegisterSelection(InvMassSelection);
  RegisterSelection(RealTauSelection);
  RegisterSelection(TauSelection);
  RegisterSelection(OneTauSelection);
  RegisterSelection(METSelection);
  RegisterSelection(SameSignSelection);
  RegisterSelection(OneJetSelection);
  RegisterSelection(HalilSelection);

    
  // ---------------- set up the histogram collections -------------------- 

  RegisterHistCollection( new JetHists("Jets_ControlPlots"));
  RegisterHistCollection( new EventHists("Events_ControlPlots"));
  RegisterHistCollection( new MuonHists("Muons_ControlPlots"));
  RegisterHistCollection( new TauHists("Taus_ControlPlots"));
  RegisterHistCollection( new ElectronHists("Electrons_ControlPlots"));

  RegisterHistCollection( new JetHists("Jets_ControlPlots2"));
  RegisterHistCollection( new EventHists("Events_ControlPlots2"));
  RegisterHistCollection( new MuonHists("Muons_ControlPlots2"));
  RegisterHistCollection( new TauHists("Taus_ControlPlots2"));
  RegisterHistCollection( new ElectronHists("Electrons_ControlPlots2"));

  RegisterHistCollection( new JetHists("Jets_oneJetSelection"));
  RegisterHistCollection( new EventHists("Events_oneJetSelection"));
  RegisterHistCollection( new MuonHists("Muons_oneJetSelection"));
  RegisterHistCollection( new TauHists("Taus_oneJetSelection"));
  RegisterHistCollection( new ElectronHists("Electrons_oneJetSelection"));

  RegisterHistCollection( new JetHists("Jets_AntibTagSelection"));
  RegisterHistCollection( new EventHists("Events_AntibTagSelection"));
  RegisterHistCollection( new MuonHists("Muons_AntibTagSelection"));
  RegisterHistCollection( new TauHists("Taus_AntibTagSelection"));
  RegisterHistCollection( new ElectronHists("Electrons_AntibTagSelection"));

  RegisterHistCollection( new JetHists("Jets_RealTauSelection"));
  RegisterHistCollection( new EventHists("Events_RealTauSelection"));
  RegisterHistCollection( new MuonHists("Muons_RealTauSelection"));
  RegisterHistCollection( new TauHists("Taus_RealTauSelection"));
  RegisterHistCollection( new ElectronHists("Electrons_RealTauSelection"));

  RegisterHistCollection( new JetHists("Jets_FakeTauSelection"));
  RegisterHistCollection( new EventHists("Events_FakeTauSelection"));
  RegisterHistCollection( new MuonHists("Muons_FakeTauSelection"));
  RegisterHistCollection( new TauHists("Taus_FakeTauSelection"));
  RegisterHistCollection( new ElectronHists("Electrons_FakeTauSelection"));

  RegisterHistCollection( new JetHists("Jets_Electrons"));
  RegisterHistCollection( new EventHists("Events_Electrons"));
  RegisterHistCollection( new MuonHists("Muons_Electrons"));
  RegisterHistCollection( new TauHists("Taus_Electrons"));
  RegisterHistCollection( new ElectronHists("Electrons_Electrons"));

  RegisterHistCollection( new JetHists("Jets_Muons"));
  RegisterHistCollection( new EventHists("Events_Muons"));
  RegisterHistCollection( new MuonHists("Muons_Muons"));
  RegisterHistCollection( new TauHists("Taus_Muons"));
  RegisterHistCollection( new ElectronHists("Electrons_Muons"));

  RegisterHistCollection( new JetHists("Jets_DecayModeEfficiency_1"));
  RegisterHistCollection( new EventHists("Events_DecayModeEfficiency_1"));
  RegisterHistCollection( new MuonHists("Muons_DecayModeEfficiency_1"));
  RegisterHistCollection( new TauHists("Taus_DecayModeEfficiency_1"));
  RegisterHistCollection( new ElectronHists("Electrons_DecayModeEfficiency_1"));

  RegisterHistCollection( new JetHists("Jets_DecayModeEfficiency_2"));
  RegisterHistCollection( new EventHists("Events_DecayModeEfficiency_2"));
  RegisterHistCollection( new MuonHists("Muons_DecayModeEfficiency_2"));
  RegisterHistCollection( new TauHists("Taus_DecayModeEfficiency_2"));
  RegisterHistCollection( new ElectronHists("Electrons_DecayModeEfficiency_2"));


  RegisterHistCollection( new JetHists("Jets_Electrons_MediumSelection"));
  RegisterHistCollection( new EventHists("Events_Electrons_MediumSelection"));
  RegisterHistCollection( new MuonHists("Muons_Electrons_MediumSelection"));
  RegisterHistCollection( new TauHists("Taus_Electrons_MediumSelection"));
  RegisterHistCollection( new ElectronHists("Electrons_Electrons_MediumSelection"));

  RegisterHistCollection( new JetHists("Jets_Muons_MediumSelection"));
  RegisterHistCollection( new EventHists("Events_Muons_MediumSelection"));
  RegisterHistCollection( new MuonHists("Muons_Muons_MediumSelection"));
  RegisterHistCollection( new TauHists("Taus_Muons_MediumSelection"));
  RegisterHistCollection( new ElectronHists("Electrons_Muons_MediumSelection"));
                                            
  RegisterHistCollection( new JetHists("Jets_AntibTagSelection_MediumTauSelection"));
  RegisterHistCollection( new EventHists("Events_AntibTagSelection_MediumTauSelection"));
  RegisterHistCollection( new MuonHists("Muons_AntibTagSelection_MediumTauSelection"));
  RegisterHistCollection( new TauHists("Taus_AntibTagSelection_MediumTauSelection"));
  RegisterHistCollection( new ElectronHists("Electrons_AntibTagSelection_MediumTauSelection"));

  RegisterHistCollection( new JetHists("Jets_RealTauSelection_MediumTauSelection"));
  RegisterHistCollection( new EventHists("Events_RealTauSelection_MediumTauSelection"));
  RegisterHistCollection( new MuonHists("Muons_RealTauSelection_MediumTauSelection"));
  RegisterHistCollection( new TauHists("Taus_RealTauSelection_MediumTauSelection"));
  RegisterHistCollection( new ElectronHists("Electrons_RealTauSelection_MediumTauSelection"));

  RegisterHistCollection( new JetHists("Jets_FakeTauSelection_MediumTauSelection"));
  RegisterHistCollection( new EventHists("Events_FakeTauSelection_MediumTauSelection"));
  RegisterHistCollection( new MuonHists("Muons_FakeTauSelection_MediumTauSelection"));
  RegisterHistCollection( new TauHists("Taus_FakeTauSelection_MediumTauSelection"));
  RegisterHistCollection( new ElectronHists("Electrons_FakeTauSelection_MediumTauSelection"));

  RegisterHistCollection( new JetHists("Jets_AntibTagSelection_MediumTauSelection_noIso"));
  RegisterHistCollection( new EventHists("Events_AntibTagSelection_MediumTauSelection_noIso"));
  RegisterHistCollection( new MuonHists("Muons_AntibTagSelection_MediumTauSelection_noIso"));
  RegisterHistCollection( new TauHists("Taus_AntibTagSelection_MediumTauSelection_noIso"));
  RegisterHistCollection( new ElectronHists("Electrons_AntibTagSelection_MediumTauSelection_noIso"));

  RegisterHistCollection( new JetHists("Jets_RealTauSelection_MediumTauSelection_noIso"));
  RegisterHistCollection( new EventHists("Events_RealTauSelection_MediumTauSelection_noIso"));
  RegisterHistCollection( new MuonHists("Muons_RealTauSelection_MediumTauSelection_noIso"));
  RegisterHistCollection( new TauHists("Taus_RealTauSelection_MediumTauSelection_noIso"));
  RegisterHistCollection( new ElectronHists("Electrons_RealTauSelection_MediumTauSelection_noIso"));

  RegisterHistCollection( new JetHists("Jets_FakeTauSelection_MediumTauSelection_noIso"));
  RegisterHistCollection( new EventHists("Events_FakeTauSelection_MediumTauSelection_noIso"));
  RegisterHistCollection( new MuonHists("Muons_FakeTauSelection_MediumTauSelection_noIso"));
  RegisterHistCollection( new TauHists("Taus_FakeTauSelection_MediumTauSelection_noIso"));
  RegisterHistCollection( new ElectronHists("Electrons_FakeTauSelection_MediumTauSelection_noIso"));

  RegisterHistCollection( new JetHists("Jets_SameSignSelection"));
  RegisterHistCollection( new EventHists("Events_SameSignSelection"));
  RegisterHistCollection( new MuonHists("Muons_SameSignSelection"));
  RegisterHistCollection( new TauHists("Taus_SameSignSelection"));
  RegisterHistCollection( new ElectronHists("Electrons_SameSignSelection"));

  RegisterHistCollection( new JetHists("Jets_OppositeSignSelection"));
  RegisterHistCollection( new EventHists("Events_OppositeSignSelection"));
  RegisterHistCollection( new MuonHists("Muons_OppositeSignSelection"));
  RegisterHistCollection( new TauHists("Taus_OppositeSignSelection"));
  RegisterHistCollection( new ElectronHists("Electrons_OppositeSignSelection"));

  RegisterHistCollection( new JetHists("Jets_SameSignSelection_HalilEvent"));
  RegisterHistCollection( new EventHists("Events_SameSignSelection_HalilEvent"));
  RegisterHistCollection( new MuonHists("Muons_SameSignSelection_HalilEvent"));
  RegisterHistCollection( new TauHists("Taus_SameSignSelection_HalilEvent"));
  RegisterHistCollection( new ElectronHists("Electrons_SameSignSelection_HalilEvent"));

  RegisterHistCollection( new JetHists("Jets_OppositeSignSelection_HalilEvent"));
  RegisterHistCollection( new EventHists("Events_OppositeSignSelection_HalilEvent"));
  RegisterHistCollection( new MuonHists("Muons_OppositeSignSelection_HalilEvent"));
  RegisterHistCollection( new TauHists("Taus_OppositeSignSelection_HalilEvent"));
  RegisterHistCollection( new ElectronHists("Electrons_OppositeSignSelection_HalilEvent"));

  RegisterHistCollection( new JetHists("Jets_SameSignSelection_MediumSelection"));
  RegisterHistCollection( new EventHists("Events_SameSignSelection_MediumSelection"));
  RegisterHistCollection( new MuonHists("Muons_SameSignSelection_MediumSelection"));
  RegisterHistCollection( new TauHists("Taus_SameSignSelection_MediumSelection"));
  RegisterHistCollection( new ElectronHists("Electrons_SameSignSelection_MediumSelection"));

  RegisterHistCollection( new JetHists("Jets_OppositeSignSelection_MediumSelection"));
  RegisterHistCollection( new EventHists("Events_OppositeSignSelection_MediumSelection"));
  RegisterHistCollection( new MuonHists("Muons_OppositeSignSelection_MediumSelection"));
  RegisterHistCollection( new TauHists("Taus_OppositeSignSelection_MediumSelection"));
  RegisterHistCollection( new ElectronHists("Electrons_OppositeSignSelection_MediumSelection"));

  RegisterHistCollection( new JetHists("Jets_SameSignSelection_MediumSelection_HalilEvent"));
  RegisterHistCollection( new EventHists("Events_SameSignSelection_MediumSelection_HalilEvent"));
  RegisterHistCollection( new MuonHists("Muons_SameSignSelection_MediumSelection_HalilEvent"));
  RegisterHistCollection( new TauHists("Taus_SameSignSelection_MediumSelection_HalilEvent"));
  RegisterHistCollection( new ElectronHists("Electrons_SameSignSelection_MediumSelection_HalilEvent"));

  RegisterHistCollection( new JetHists("Jets_OppositeSignSelection_MediumSelection_HalilEvent"));
  RegisterHistCollection( new EventHists("Events_OppositeSignSelection_MediumSelection_HalilEvent"));
  RegisterHistCollection( new MuonHists("Muons_OppositeSignSelection_MediumSelection_HalilEvent"));
  RegisterHistCollection( new TauHists("Taus_OppositeSignSelection_MediumSelection_HalilEvent"));
  RegisterHistCollection( new ElectronHists("Electrons_OppositeSignSelection_MediumSelection_HalilEvent"));

  
  
  Double_t bins[5] = {20, 60, 120, 200, 800};
  Book( TH1F( "pT_1_binned", "p_{T} tau [GeV]",4, bins));
  Book( TH1F( "real_pT_1_binned", "p_{T} real tau [GeV]",4, bins));
  Book( TH1F( "fake_pT_1_binned", "p_{T} fake tau [GeV]",4, bins));
  Book( TH1F( "Muons_pT_1_binned", "p_{T} fake tau from muon[GeV]",4, bins));
  Book( TH1F( "Electrons_pT_1_binned", "p_{T} fake tau from electrons[GeV]",4, bins));
  Book( TH1F( "pT_1_binned_mediumSelection", "p_{T} medium tau [GeV]",4, bins));
  Book( TH1F( "real_pT_1_binned_mediumSelection", "p_{T} medium real tau [GeV]",4, bins));
  Book( TH1F( "fake_pT_1_binned_mediumSelection", "p_{T} medium fake tau [GeV]",4, bins));
  Book( TH1F( "Muons_pT_1_binned_mediumSelection", "p_{T} medium fake tau from muons[GeV]",4, bins));
  Book( TH1F( "Electrons_pT_1_binned_mediumSelection", "p_{T} medium fake tau from electrons[GeV]",4, bins));

  Book( TH1F( "eta_1", "#eta tau", 100,-3,3 ) );
  Book( TH1F( "real_eta_1", "#eta real tau", 100,-3,3 ) );
  Book( TH1F( "fake_eta_1", "#eta fake tau", 100,-3,3 ) );
  Book( TH1F( "eta_1_mediumSelection", "#eta medium tau", 100,-3,3 ) );
  Book( TH1F( "real_eta_1_mediumSelection", "#eta medium real tau", 100,-3,3 ) );
  Book( TH1F( "fake_eta_1_mediumSelection", "#eta medium fake tau", 100,-3,3 ) );
  Book( TH1F( "Muons_eta_1_mediumSelection", "#eta medium fake tau from muons", 100,-3,3 ) );
  Book( TH1F( "Muons_eta_1", "#eta fake tau from muons", 100,-3,3 ) );
  Book( TH1F( "Electrons_eta_1_mediumSelection", "#eta medium fake tau from electrons", 100,-3,3 ) );
  Book( TH1F( "Electrons_eta_1", "#eta fake tau from electrons", 100,-3,3 ) );

  Book( TH1F( "NJets", "number of jets", 13, -0.5, 12.5 ) );
  Book( TH1F( "real_NJets", "number of jets (real taus)", 13, -0.5, 12.5 ) );
  Book( TH1F( "fake_NJets", "number of jets (fake taus)", 13, -0.5, 12.5 ) );
  Book( TH1F( "Muons_NJets", "number of jets (fake taus from muons)", 13, -0.5, 12.5 ) );
  Book( TH1F( "Electrons_NJets", "number of jets (fake taus from electrons)", 13, -0.5, 12.5 ) );
  Book( TH1F( "NJets_mediumSelection", "number of jets (medium taus)", 13, -0.5, 12.5 ) );
  Book( TH1F( "real_NJets_mediumSelection", "number of jets (medium real tau)", 13, -0.5, 12.5 ) );
  Book( TH1F( "fake_NJets_mediumSelection", "number of jets (medium fake tau)", 13, -0.5, 12.5 ) );
  Book( TH1F( "Muons_NJets_mediumSelection", "number of jets (medium fake tau from muons)", 13, -0.5, 12.5 ) );
  Book( TH1F( "Electrons_NJets_mediumSelection", "number of jets (medium fake tau from electrons)", 13, -0.5, 12.5 ) );
  
  Book( TH1F( "HT", "H_{T}", 100,0,5000 ) );
  Book( TH1F( "real_HT", "H_{T} (real taus)", 100,0,5000 ) );
  Book( TH1F( "fake_HT", "H_{T} (fake taus)", 100,0,5000 ) );
  Book( TH1F( "Muons_HT", "H_{T} (fake taus from muons)", 100,0,5000 ) );
  Book( TH1F( "Electrons_HT", "H_{T} (fake taus from electrons)", 100,0,5000 ) );
  Book( TH1F( "HT_mediumSelection", "H_{T} (medium taus)", 100,0,5000 ) );
  Book( TH1F( "real_HT_mediumSelection", "H_{T} (medium real tau)", 100,0,5000 ) );
  Book( TH1F( "fake_HT_mediumSelection", "H_{T} (medium fake tau)", 100,0,5000 ) );
  Book( TH1F( "Muons_HT_mediumSelection", "H_{T} (medium fake tau from muons) ", 100,0,5000 ) );
  Book( TH1F( "Electrons_HT_mediumSelection", "H_{T}(medium fake tau from electrons) ", 100,0,5000 ) );

  Book( TH1F( "DeltaR", "#Deltar tau, next jet  ", 50, 0,5));
  Book( TH1F( "real_DeltaR", "#Deltar real tau, next jet  ", 50, 0,5));
  Book( TH1F( "fake_DeltaR", "#Deltar fake tau, next jet  ", 50, 0,5));
  Book( TH1F( "Muons_DeltaR", "#Deltar fake tau from muons, next jet  ", 50, 0,5));
  Book( TH1F( "Electrons_DeltaR", "#Deltar fake tau from electrons, next jet  ", 50, 0,5));
  Book( TH1F( "DeltaR_mediumSelection", "#Deltar medium tau, next jet  ", 50, 0,5));
  Book( TH1F( "real_DeltaR_mediumSelection", "#Deltar medium real tau, next jet  ", 50, 0,5));
  Book( TH1F( "fake_DeltaR_mediumSelection", "#Deltar medium fake tau, next jet  ", 50, 0,5));
  Book( TH1F( "Muons_DeltaR_mediumSelection", "#Deltar medium fake tau from  muons, next jet  ", 50, 0,5));
  Book( TH1F( "Electrons_DeltaR_mediumSelection", "#Deltar medium fake tau from electrons, next jet  ", 50, 0,5));

  Book( TH1F( "SameSign", "p_{T} tau [GeV] (same sign)",4, bins));
  Book( TH1F( "real_SameSign", "p_{T} real tau [GeV]] (same sign)",4, bins));
  Book( TH1F( "fake_SameSign", "p_{T} fake tau [GeV]] (same sign)",4, bins));
  Book( TH1F( "Muons_SameSign", "p_{T} fake tau from muons [GeV]] (same sign)",4, bins));
  Book( TH1F( "Electrons_SameSign", "p_{T} fake tau from electrons[GeV]] (same sign)",4, bins));
  Book( TH1F( "SameSign_mediumSelection", "p_{T} medium tau [GeV]] (same sign)",4, bins));
  Book( TH1F( "real_SameSign_mediumSelection", "p_{T} medium real tau [GeV]] (same sign)",4, bins));
  Book( TH1F( "fake_SameSign_mediumSelection", "p_{T} medium fake tau [GeV]] (same sign)",4, bins));
  Book( TH1F( "Muons_SameSign_mediumSelection", "p_{T} medium fake tau from muons[GeV]] (same sign)",4, bins));
  Book( TH1F( "Electrons_SameSign_mediumSelection", "p_{T} medium fake tau from electrons[GeV]] (same sign)",4, bins));

  Book( TH1F( "OppositeSign", "p_{T} tau [GeV]] (opposite sign)",4, bins));
  Book( TH1F( "real_OppositeSign", "p_{T} real tau [GeV] (opposite sign)",4, bins));
  Book( TH1F( "fake_OppositeSign", "p_{T} fake tau [GeV] (opposite sign)",4, bins));
  Book( TH1F( "Muons_OppositeSign", "p_{T} fake tau from muons[GeV] (opposite sign)",4, bins));
  Book( TH1F( "Electrons_OppositeSign", "p_{T} fake tau from electrons[GeV] (opposite sign)",4, bins));
  Book( TH1F( "OppositeSign_mediumSelection", "p_{T} medium tau [GeV] (opposite sign)",4, bins));
  Book( TH1F( "real_OppositeSign_mediumSelection", "p_{T} medium real tau [GeV] (opposite sign)",4, bins));
  Book( TH1F( "fake_OppositeSign_mediumSelection", "p_{T} medium fake tau [GeV] (opposite sign)",4, bins));
  Book( TH1F( "Muons_OppositeSign_mediumSelection", "p_{T} medium fake tau from muons[GeV] (opposite sign)",4, bins));
  Book( TH1F( "Electrons_OppositeSign_mediumSelection", "p_{T} medium fake tau from electrons[GeV] (opposite sign)",4, bins));

  Book( TH1F( "SameSign_HalilEvent", "p_{T} tau [GeV] (same sign)",4, bins));
  Book( TH1F( "real_SameSign_HalilEvent", "p_{T} real tau [GeV]] (same sign)",4, bins));
  Book( TH1F( "fake_SameSign_HalilEvent", "p_{T} fake tau [GeV]] (same sign)",4, bins));
  Book( TH1F( "Muons_SameSign_HalilEvent", "p_{T} fake tau from muons [GeV]] (same sign)",4, bins));
  Book( TH1F( "Electrons_SameSign_HalilEvent", "p_{T} fake tau from electrons[GeV]] (same sign)",4, bins));
  Book( TH1F( "SameSign_mediumSelection_HalilEvent", "p_{T} medium tau [GeV]] (same sign)",4, bins));
  Book( TH1F( "real_SameSign_mediumSelection_HalilEvent", "p_{T} medium real tau [GeV]] (same sign)",4, bins));
  Book( TH1F( "fake_SameSign_mediumSelection_HalilEvent", "p_{T} medium fake tau [GeV]] (same sign)",4, bins));
  Book( TH1F( "Muons_SameSign_mediumSelection_HalilEvent", "p_{T} medium fake tau from muons[GeV]] (same sign)",4, bins));
  Book( TH1F( "Electrons_SameSign_mediumSelection_HalilEvent", "p_{T} medium fake tau from electrons[GeV]] (same sign)",4, bins));

  Book( TH1F( "OppositeSign_HalilEvent", "p_{T} tau [GeV]] (opposite sign)",4, bins));
  Book( TH1F( "real_OppositeSign_HalilEvent", "p_{T} real tau [GeV] (opposite sign)",4, bins));
  Book( TH1F( "fake_OppositeSign_HalilEvent", "p_{T} fake tau [GeV] (opposite sign)",4, bins));
  Book( TH1F( "Muons_OppositeSign_HalilEvent", "p_{T} fake tau from muons[GeV] (opposite sign)",4, bins));
  Book( TH1F( "Electrons_OppositeSign_HalilEvent", "p_{T} fake tau from electrons[GeV] (opposite sign)",4, bins));
  Book( TH1F( "OppositeSign_mediumSelection_HalilEvent", "p_{T} medium tau [GeV] (opposite sign)",4, bins));
  Book( TH1F( "real_OppositeSign_mediumSelection_HalilEvent", "p_{T} medium real tau [GeV] (opposite sign)",4, bins));
  Book( TH1F( "fake_OppositeSign_mediumSelection_HalilEvent", "p_{T} medium fake tau [GeV] (opposite sign)",4, bins));
  Book( TH1F( "Muons_OppositeSign_mediumSelection_HalilEvent", "p_{T} medium fake tau from muons[GeV] (opposite sign)",4, bins));
  Book( TH1F( "Electrons_OppositeSign_mediumSelection_HalilEvent", "p_{T} medium fake tau from electrons[GeV] (opposite sign)",4, bins));


  Book( TH1F( "GluonJet","p_{T} tau [GeV] (gluon jet)",4, bins));
  Book( TH1F( "GluonJet_mediumSelection","p_{T} medium tau [GeV] (gluon jet)",4, bins));
  Book( TH1F( "real_GluonJet", "p_{T} real tau [GeV] (opposite sign, gluon jet)",4, bins));
  Book( TH1F( "fake_GluonJet", "p_{T} fake tau [GeV] (opposite sign, gluon jet)",4, bins));
  Book( TH1F( "Muons_GluonJet", "p_{T} fake tau from muons[GeV] (opposite sign, gluon jet)",4, bins));
  Book( TH1F( "Electrons_GluonJet", "p_{T} fake tau from electrons[GeV] (opposite sign, gluon jet)",4, bins));
  Book( TH1F( "real_GluonJet_mediumSelection", "p_{T} medium real tau [GeV] (opposite sign, gluon jet)",4, bins));
  Book( TH1F( "fake_GluonJet_mediumSelection", "p_{T} medium fake tau [GeV] (opposite sign, gluon jet)",4, bins));
  Book( TH1F( "Muons_GluonJet_mediumSelection", "p_{T} medium fake tau from muons[GeV] (opposite sign, gluon jet)",4, bins));
  Book( TH1F( "Electrons_GluonJet_mediumSelection", "p_{T} medium fake tau from electrons[GeV] (opposite sign, gluon jet)",4, bins));

  Book( TH1F( "QuarkJet","p_{T} tau [GeV] (quark jet)",4, bins));
  Book( TH1F( "QuarkJet_mediumSelection","p_{T} medium tau [GeV] (quark jet)",4, bins));
  Book( TH1F( "real_QuarkJet", "p_{T} real tau [GeV] (opposite sign, quark jet)",4, bins));
  Book( TH1F( "fake_QuarkJet", "p_{T} fake tau [GeV] (opposite sign, quark jet)",4, bins));
  Book( TH1F( "Muons_QuarkJet", "p_{T} fake tau from muons[GeV] (opposite sign, quark jet)",4, bins));
  Book( TH1F( "Electrons_QuarkJet", "p_{T} fake tau from electrons[GeV] (opposite sign, quark jet)",4, bins));
  Book( TH1F( "real_QuarkJet_mediumSelection", "p_{T} medium real tau [GeV] (opposite sign, quark jet)",4, bins));
  Book( TH1F( "fake_QuarkJet_mediumSelection", "p_{T} medium fake tau [GeV] (opposite sign, quark jet)",4, bins));
  Book( TH1F( "Muons_QuarkJet_mediumSelection", "p_{T} medium fake tau from muons[GeV] (opposite sign, quark jet)",4, bins));
  Book( TH1F( "Electrons_QuarkJet_mediumSelection", "p_{T} medium fake tau from electrons[GeV] (opposite sign, quark jet)",4, bins));

  Book( TH1F( "GluonJet_SameSign","p_{T} tau [GeV] (gluon jet, same sign)",4, bins));
  Book( TH1F( "GluonJet_SameSign_mediumSelection","p_{T} medium tau [GeV] (gluon jet, same sign)",4, bins));
  Book( TH1F( "real_GluonJet_SameSign", "p_{T} real tau [GeV] (same sign, gluon jet)",4, bins));
  Book( TH1F( "fake_GluonJet_SameSign", "p_{T} fake tau [GeV] (same sign, gluon jet)",4, bins));
  Book( TH1F( "Muons_GluonJet_SameSign", "p_{T} fake tau from muons[GeV] (same sign, gluon jet)",4, bins));
  Book( TH1F( "Electrons_GluonJet_SameSign", "p_{T} fake tau from electrons[GeV] (same sign, gluon jet)",4, bins));
  Book( TH1F( "real_GluonJet_SameSign_mediumSelection", "p_{T} medium real tau [GeV] (same sign, gluon jet)",4, bins));
  Book( TH1F( "fake_GluonJet_SameSign_mediumSelection", "p_{T} medium fake tau [GeV] (same sign, gluon jet)",4, bins));
  Book( TH1F( "Muons_GluonJet_SameSign_mediumSelection", "p_{T} medium fake tau from muons[GeV] (same sign, gluon jet)",4, bins));
  Book( TH1F( "Electrons_GluonJet_SameSign_mediumSelection", "p_{T} medium fake tau from electrons[GeV] (same sign, gluon jet)",4, bins));
  
  Book( TH1F( "GluonJet_OppositeSign","p_{T} tau [GeV] (gluon jet, opposite sign)",4, bins));
  Book( TH1F( "GluonJet_OppositeSign_mediumSelection","p_{T} medium tau [GeV] (gluon jet, opposite sign)",4, bins));
  Book( TH1F( "real_GluonJet_OppositeSign", "p_{T} real tau [GeV] (opposite sign, gluon jet)",4, bins));
  Book( TH1F( "fake_GluonJet_OppositeSign", "p_{T} fake tau [GeV] (opposite sign, gluon jet)",4, bins));
  Book( TH1F( "Muons_GluonJet_OppositeSign", "p_{T} fake tau from muons[GeV] (opposite sign, gluon jet)",4, bins));
  Book( TH1F( "Electrons_GluonJet_OppositeSign", "p_{T} fake tau from electrons[GeV] (opposite sign, gluon jet)",4, bins));
  Book( TH1F( "real_GluonJet_OppositeSign_mediumSelection", "p_{T} medium real tau [GeV] (opposite sign, gluon jet)",4, bins));
  Book( TH1F( "fake_GluonJet_OppositeSign_mediumSelection", "p_{T} medium fake tau [GeV] (opposite sign, gluon jet)",4, bins));
  Book( TH1F( "Muons_GluonJet_OppositeSign_mediumSelection", "p_{T} medium fake tau from muons[GeV] (opposite sign, gluon jet)",4, bins));
  Book( TH1F( "Electrons_GluonJet_OppositeSign_mediumSelection", "p_{T} medium fake tau from electrons[GeV] (opposite sign, gluon jet)",4, bins));
  
  Book( TH1F( "QuarkJet_SameSign","p_{T} tau [GeV] (quark jet, same sign)",4, bins)); 
  Book( TH1F( "QuarkJet_SameSign_mediumSelection","p_{T} medium tau [GeV] (quark jet, same sign)",4, bins));
  Book( TH1F( "real_QuarkJet_SameSign", "p_{T} real tau [GeV] (same sign, quark jet)",4, bins));
  Book( TH1F( "fake_QuarkJet_SameSign", "p_{T} fake tau [GeV] (same sign, quark jet)",4, bins));
  Book( TH1F( "Muons_QuarkJet_SameSign", "p_{T} fake tau from muons[GeV] (same sign, quark jet)",4, bins));
  Book( TH1F( "Electrons_QuarkJet_SameSign", "p_{T} fake tau from electrons[GeV] (same sign, quark jet)",4, bins));
  Book( TH1F( "real_QuarkJet_SameSign_mediumSelection", "p_{T} medium real tau [GeV] (same sign, quark jet)",4, bins));
  Book( TH1F( "fake_QuarkJet_SameSign_mediumSelection", "p_{T} medium fake tau [GeV] (same sign, quark jet)",4, bins));
  Book( TH1F( "Muons_QuarkJet_SameSign_mediumSelection", "p_{T} medium fake tau from muons[GeV] (same sign, quark jet)",4, bins));
  Book( TH1F( "Electrons_QuarkJet_SameSign_mediumSelection", "p_{T} medium fake tau from electrons[GeV] (same sign, quark jet)",4, bins));

  Book( TH1F( "QuarkJet_OppositeSign","p_{T} tau [GeV] (quark jet, opposite sign)",4, bins)); 
  Book( TH1F( "QuarkJet_OppositeSign_mediumSelection","p_{T} medium tau [GeV] (quark jet, opposite sign)",4, bins));
  Book( TH1F( "real_QuarkJet_OppositeSign", "p_{T} real tau [GeV] (opposite sign, quark jet)",4, bins));
  Book( TH1F( "fake_QuarkJet_OppositeSign", "p_{T} fake tau [GeV] (opposite sign, quark jet)",4, bins));
  Book( TH1F( "Muons_QuarkJet_OppositeSign", "p_{T} fake tau from muons[GeV] (opposite sign, quark jet)",4, bins));
  Book( TH1F( "Electrons_QuarkJet_OppositeSign", "p_{T} fake tau from electrons[GeV] (opposite sign, quark jet)",4, bins));
  Book( TH1F( "real_QuarkJet_OppositeSign_mediumSelection", "p_{T} medium real tau [GeV] (opposite sign, quark jet)",4, bins));
  Book( TH1F( "fake_QuarkJet_OppositeSign_mediumSelection", "p_{T} medium fake tau [GeV] (opposite sign, quark jet)",4, bins));
  Book( TH1F( "Muons_QuarkJet_OppositeSign_mediumSelection", "p_{T} medium fake tau from muons[GeV] (opposite sign, quark jet)",4, bins));
  Book( TH1F( "Electrons_QuarkJet_OppositeSign_mediumSelection", "p_{T} medium fake tau from electrons[GeV] (opposite sign, quark jet)",4, bins));
  Book( TH1F( "GenParticleMatching","GenParticleMatching",50,-25,25));
  Book( TH1F( "GenParticleMatching_SameSign_Plus","GenParticleMatching_SameSign_Plus",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_OppositeSign_Plus","GenParticleMatching_OppositeSign_Plus",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_SameSign_Minus","GenParticleMatching_SameSign_Minus",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_OppositeSign_Minus","GenParticleMatching_OppositeSign_Minus",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_SameSign_1","GenParticleMatching_SameSign_1",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_OppositeSign_1","GenParticleMatching_OppositeSign_1",50,-25,25));       
  Book( TH1F( "GenParticleMatching_SameSign_2","GenParticleMatching_SameSign_2",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_OppositeSign_2","GenParticleMatching_OppositeSign_2",50,-25,25));       
  Book( TH1F( "GenParticleMatching_SameSign_3","GenParticleMatching_SameSign_3",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_OppositeSign_3","GenParticleMatching_OppositeSign_3",50,-25,25));       
  Book( TH1F( "GenParticleMatching_SameSign_4","GenParticleMatching_SameSign_4",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_OppositeSign_4","GenParticleMatching_OppositeSign_4",50,-25,25));  
  
  Book( TH1F( "GenParticleMatching_Medium","GenParticleMatching_Medium",50,-25,25));
  Book( TH1F( "GenParticleMatching_SameSign_Plus_Medium","GenParticleMatching_SameSign_Plus_Medium",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_OppositeSign_Plus_Medium","GenParticleMatching_OppositeSign_Plus_Medium",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_SameSign_Minus_Medium","GenParticleMatching_SameSign_Minus_Medium",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_OppositeSign_Minus_Medium","GenParticleMatching_OppositeSign_Minus_Medium",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_SameSign_1_Medium","GenParticleMatching_SameSign_1_Medium",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_OppositeSign_1_Medium","GenParticleMatching_OppositeSign_1_Medium",50,-25,25));       
  Book( TH1F( "GenParticleMatching_SameSign_2_Medium","GenParticleMatching_SameSign_2_Medium",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_OppositeSign_2_Medium","GenParticleMatching_OppositeSign_2_Medium",50,-25,25));       
  Book( TH1F( "GenParticleMatching_SameSign_3_Medium","GenParticleMatching_SameSign_3_Medium",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_OppositeSign_3_Medium","GenParticleMatching_OppositeSign_3_Medium",50,-25,25));       
  Book( TH1F( "GenParticleMatching_SameSign_4_Medium","GenParticleMatching_SameSign_4_Medium",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_OppositeSign_4_Medium","GenParticleMatching_OppositeSign_4_Medium",50,-25,25));       

  Book( TH1F( "GenParticleMatching_SameSign_Plus_1","GenParticleMatching_SameSign_Plus_1",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_OppositeSign_Plus_1","GenParticleMatching_OppositeSign_Plus_1",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_SameSign_Minus_1","GenParticleMatching_SameSign_Minus_1",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_OppositeSign_Minus_1","GenParticleMatching_OppositeSign_Minus_1",50,-25,25)); 

  Book( TH1F( "GenParticleMatching_SameSign_Plus_2","GenParticleMatching_SameSign_Plus_2",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_OppositeSign_Plus_2","GenParticleMatching_OppositeSign_Plus_2",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_SameSign_Minus_2","GenParticleMatching_SameSign_Minus_2",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_OppositeSign_Minus_2","GenParticleMatching_OppositeSign_Minus_2",50,-25,25)); 

  Book( TH1F( "GenParticleMatching_SameSign_Plus_3","GenParticleMatching_SameSign_Plus_3",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_OppositeSign_Plus_3","GenParticleMatching_OppositeSign_Plus_3",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_SameSign_Minus_3","GenParticleMatching_SameSign_Minus_3",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_OppositeSign_Minus_3","GenParticleMatching_OppositeSign_Minus_3",50,-25,25)); 

  Book( TH1F( "GenParticleMatching_SameSign_Plus_4","GenParticleMatching_SameSign_Plus_4",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_OppositeSign_Plus_4","GenParticleMatching_OppositeSign_Plus_4",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_SameSign_Minus_4","GenParticleMatching_SameSign_Minus_4",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_OppositeSign_Minus_4","GenParticleMatching_OppositeSign_Minus_4",50,-25,25)); 

  Book( TH1F( "GenParticleMatching_SameSign_Plus_1_Medium","GenParticleMatching_SameSign_Plus_1_Medium",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_OppositeSign_Plus_1_Medium","GenParticleMatching_OppositeSign_Plus_1_Medium",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_SameSign_Minus_1_Medium","GenParticleMatching_SameSign_Minus_1_Medium",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_OppositeSign_Minus_1_Medium","GenParticleMatching_OppositeSign_Minus_1_Medium",50,-25,25)); 

  Book( TH1F( "GenParticleMatching_SameSign_Plus_2_Medium","GenParticleMatching_SameSign_Plus_2_Medium",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_OppositeSign_Plus_2_Medium","GenParticleMatching_OppositeSign_Plus_2_Medium",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_SameSign_Minus_2_Medium","GenParticleMatching_SameSign_Minus_2_Medium",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_OppositeSign_Minus_2_Medium","GenParticleMatching_OppositeSign_Minus_2_Medium",50,-25,25)); 

  Book( TH1F( "GenParticleMatching_SameSign_Plus_3_Medium","GenParticleMatching_SameSign_Plus_3_Medium",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_OppositeSign_Plus_3_Medium","GenParticleMatching_OppositeSign_Plus_3_Medium",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_SameSign_Minus_3_Medium","GenParticleMatching_SameSign_Minus_3_Medium",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_OppositeSign_Minus_3_Medium","GenParticleMatching_OppositeSign_Minus_3_Medium",50,-25,25)); 

  Book( TH1F( "GenParticleMatching_SameSign_Plus_4_Medium","GenParticleMatching_SameSign_Plus_4_Medium",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_OppositeSign_Plus_4_Medium","GenParticleMatching_OppositeSign_Plus_4_Medium",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_SameSign_Minus_4_Medium","GenParticleMatching_SameSign_Minus_4_Medium",50,-25,25)); 
  Book( TH1F( "GenParticleMatching_OppositeSign_Minus_4_Medium","GenParticleMatching_OppositeSign_Minus_4_Medium",50,-25,25)); 


  Book( TH1F( "pT_Tau_1","pT_Tau_1",4,0.5,4.5));
  Book( TH1F( "pT_Tau_2","pT_Tau_2",4,0.5,4.5));
  Book( TH1F( "pT_Tau_3", "pT_Tau_3",4,0.5,4.5));
  Book( TH1F( "pT_Tau_4","pT_Tau_4",4,0.5,4.5));
  Book( TH1F( "pT_Tau_1_Medium","pT_Tau_1_Medium",4,0.5,4.5));
  Book( TH1F( "pT_Tau_2_Medium","pT_Tau_2_Medium",4,0.5,4.5));
  Book( TH1F( "pT_Tau_3_Medium","pT_Tau_3_Medium",4,0.5,4.5));
  Book( TH1F( "pT_Tau_4_Medium","pT_Tau_4_Medium",4,0.5,4.5));
  
  Book( TH1F( "fake_pT_Tau_1","fake_pT_Tau_1",4,0.5,4.5));
  Book( TH1F( "fake_pT_Tau_2","fake_pT_Tau_2",4,0.5,4.5));
  Book( TH1F( "fake_pT_Tau_3", "fake_pT_Tau_3",4,0.5,4.5));
  Book( TH1F( "fake_pT_Tau_4","fake_pT_Tau_4",4,0.5,4.5));
  Book( TH1F( "fake_pT_Tau_1_Medium","fake_pT_Tau_1_Medium",4,0.5,4.5));
  Book( TH1F( "fake_pT_Tau_2_Medium","fake_pT_Tau_2_Medium",4,0.5,4.5));
  Book( TH1F( "fake_pT_Tau_3_Medium","fake_pT_Tau_3_Medium",4,0.5,4.5));
  Book( TH1F( "fake_pT_Tau_4_Medium","fake_pT_Tau_4_Medium",4,0.5,4.5));

  Book( TH1F( "real_pT_Tau_1","real_pT_Tau_1",4,0.5,4.5));
  Book( TH1F( "real_pT_Tau_2","real_pT_Tau_2",4,0.5,4.5));
  Book( TH1F( "real_pT_Tau_3", "real_pT_Tau_3",4,0.5,4.5));
  Book( TH1F( "real_pT_Tau_4","real_pT_Tau_4",4,0.5,4.5));
  Book( TH1F( "real_pT_Tau_1_Medium","real_pT_Tau_1_Medium",4,0.5,4.5));
  Book( TH1F( "real_pT_Tau_2_Medium","real_pT_Tau_2_Medium",4,0.5,4.5));
  Book( TH1F( "real_pT_Tau_3_Medium","real_pT_Tau_3_Medium",4,0.5,4.5));
  Book( TH1F( "real_pT_Tau_4_Medium","real_pT_Tau_4_Medium",4,0.5,4.5));
  
  Book( TH1F( "Electrons_pT_Tau_1","Electrons_pT_Tau_1",4,0.5,4.5));
  Book( TH1F( "Electrons_pT_Tau_2","Electrons_pT_Tau_2",4,0.5,4.5));
  Book( TH1F( "Electrons_pT_Tau_3", "Electrons_pT_Tau_3",4,0.5,4.5));
  Book( TH1F( "Electrons_pT_Tau_4","Electrons_pT_Tau_4",4,0.5,4.5));
  Book( TH1F( "Electrons_pT_Tau_1_Medium","Electrons_pT_Tau_1_Medium",4,0.5,4.5));
  Book( TH1F( "Electrons_pT_Tau_2_Medium","Electrons_pT_Tau_2_Medium",4,0.5,4.5));
  Book( TH1F( "Electrons_pT_Tau_3_Medium","Electrons_pT_Tau_3_Medium",4,0.5,4.5));
  Book( TH1F( "Electrons_pT_Tau_4_Medium","Electrons_pT_Tau_4_Medium",4,0.5,4.5));

  Book( TH1F( "Muons_pT_Tau_1","Muons_pT_Tau_1",4,0.5,4.5));
  Book( TH1F( "Muons_pT_Tau_2","Muons_pT_Tau_2",4,0.5,4.5));
  Book( TH1F( "Muons_pT_Tau_3", "Muons_pT_Tau_3",4,0.5,4.5));
  Book( TH1F( "Muons_pT_Tau_4","Muons_pT_Tau_4",4,0.5,4.5));
  Book( TH1F( "Muons_pT_Tau_1_Medium","Muons_pT_Tau_1_Medium",4,0.5,4.5));
  Book( TH1F( "Muons_pT_Tau_2_Medium","Muons_pT_Tau_2_Medium",4,0.5,4.5));
  Book( TH1F( "Muons_pT_Tau_3_Medium","Muons_pT_Tau_3_Medium",4,0.5,4.5));
  Book( TH1F( "Muons_pT_Tau_4_Medium","Muons_pT_Tau_4_Medium",4,0.5,4.5));

  Book( TH1F( "Gluon_pT_Tau_1","Gluon_pT_Tau_1",4,0.5,4.5));
  Book( TH1F( "Gluon_pT_Tau_2","Gluon_pT_Tau_2",4,0.5,4.5));
  Book( TH1F( "Gluon_pT_Tau_3","Gluon_pT_Tau_3",4,0.5,4.5));
  Book( TH1F( "Gluon_pT_Tau_4","Gluon_pT_Tau_4",4,0.5,4.5));
  Book( TH1F( "Gluon_pT_Tau_1_Medium","Gluon_pT_Tau_1_Medium",4,0.5,4.5));
  Book( TH1F( "Gluon_pT_Tau_2_Medium","Gluon_pT_Tau_2_Medium",4,0.5,4.5));
  Book( TH1F( "Gluon_pT_Tau_3_Medium","Gluon_pT_Tau_3_Medium",4,0.5,4.5));
  Book( TH1F( "Gluon_pT_Tau_4_Medium","Gluon_pT_Tau_4_Medium",4,0.5,4.5));

  Book( TH1F( "Up_SS_pT_Tau_1","Up_SS_pT_Tau_1",4,0.5,4.5));
  Book( TH1F( "Up_SS_pT_Tau_2","Up_SS_pT_Tau_2",4,0.5,4.5));
  Book( TH1F( "Up_SS_pT_Tau_3","Up_SS_pT_Tau_3",4,0.5,4.5));
  Book( TH1F( "Up_SS_pT_Tau_4","Up_SS_pT_Tau_4",4,0.5,4.5));
  Book( TH1F( "Up_SS_pT_Tau_1_Medium","Up_SS_pT_Tau_1_Medium",4,0.5,4.5));
  Book( TH1F( "Up_SS_pT_Tau_2_Medium","Up_SS_pT_Tau_2_Medium",4,0.5,4.5));
  Book( TH1F( "Up_SS_pT_Tau_3_Medium","Up_SS_pT_Tau_3_Medium",4,0.5,4.5));
  Book( TH1F( "Up_SS_pT_Tau_4_Medium","Up_SS_pT_Tau_4_Medium",4,0.5,4.5));

  Book( TH1F( "Down_SS_pT_Tau_1","Down_SS_pT_Tau_1",4,0.5,4.5));
  Book( TH1F( "Down_SS_pT_Tau_2","Down_SS_pT_Tau_2",4,0.5,4.5));
  Book( TH1F( "Down_SS_pT_Tau_3","Down_SS_pT_Tau_3",4,0.5,4.5));
  Book( TH1F( "Down_SS_pT_Tau_4","Down_SS_pT_Tau_4",4,0.5,4.5));
  Book( TH1F( "Down_SS_pT_Tau_1_Medium","Down_SS_pT_Tau_1_Medium",4,0.5,4.5));
  Book( TH1F( "Down_SS_pT_Tau_2_Medium","Down_SS_pT_Tau_2_Medium",4,0.5,4.5));
  Book( TH1F( "Down_SS_pT_Tau_3_Medium","Down_SS_pT_Tau_3_Medium",4,0.5,4.5));
  Book( TH1F( "Down_SS_pT_Tau_4_Medium","Down_SS_pT_Tau_4_Medium",4,0.5,4.5));
  
  Book( TH1F( "ChargeFlip_pT_Tau_1","ChargeFlip_pT_Tau_1",4,0.5,4.5));
  Book( TH1F( "ChargeFlip_pT_Tau_2","ChargeFlip_pT_Tau_2",4,0.5,4.5));
  Book( TH1F( "ChargeFlip_pT_Tau_3","ChargeFlip_pT_Tau_3",4,0.5,4.5));
  Book( TH1F( "ChargeFlip_pT_Tau_4","ChargeFlip_pT_Tau_4",4,0.5,4.5));
  Book( TH1F( "ChargeFlip_pT_Tau_1_Medium","ChargeFlip_pT_Tau_1_Medium",4,0.5,4.5));
  Book( TH1F( "ChargeFlip_pT_Tau_2_Medium","ChargeFlip_pT_Tau_2_Medium",4,0.5,4.5));
  Book( TH1F( "ChargeFlip_pT_Tau_3_Medium","ChargeFlip_pT_Tau_3_Medium",4,0.5,4.5));
  Book( TH1F( "ChargeFlip_pT_Tau_4_Medium","ChargeFlip_pT_Tau_4_Medium",4,0.5,4.5));

  // important: initialise histogram collections after their definition
  InitHistos();

  return;  
}



void TauIdCycle::EndInputData( const SInputData& id ) throw( SError ) 
{
   //LumiHandler()->PrintUsedSetup();
  
   AnalysisCycle::EndInputData( id );
   return;
}


void TauIdCycle::BeginInputFile( const SInputData& id ) throw( SError ) 
{
   // Connect all variables from the Ntuple file with the ones needed for the analysis
   // The variables are commonly stored in the BaseCycleContaincer

   // important: call to base function to connect all variables to Ntuples from the input tree
   AnalysisCycle::BeginInputFile( id );
   return;  
}



void TauIdCycle::ExecuteEvent( const SInputData& id, Double_t weight) throw( SError ) 
{ 
  
   // first step: call Execute event of base class to perform basic consistency checks
   // also, the good-run selection is performed there and the calculator is reset
   AnalysisCycle::ExecuteEvent( id, weight);

   
   // get the selections
   static Selection* JetSelection = GetSelection("JetSelection");
   static Selection* OneJetSelection = GetSelection("OneJetSelection");
   static Selection* AntibTagSelection = GetSelection("AntibTagSelection");
   static Selection* InvMassSelection = GetSelection("InvMassSelection");
   static Selection* RealTauSelection = GetSelection("RealTauSelection");
   static Selection* TauSelection = GetSelection("TauSelection");
   static Selection* OneTauSelection = GetSelection("OneTauSelection");
   static Selection* METSelection = GetSelection("METSelection");
   static Selection* SameSignSelection = GetSelection("SameSignSelection");
   static Selection* HalilSelection = GetSelection("HalilSelection");


   EventCalc* calc = EventCalc::Instance();
   BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
   bool IsRealData = calc->IsRealData();
  
   Cleaner cleaner;
   if (bcc->electrons) cleaner.ElectronCleaner(30,2.5,0.1,false,false);
  
   weight = calc ->GetWeight();
 
   TString samplename(id.GetVersion());
   if (samplename.Contains("W1Jets", TString::kIgnoreCase) || samplename.Contains("W2Jets", TString::kIgnoreCase) || samplename.Contains("W3Jets", TString::kIgnoreCase) || samplename.Contains("W4Jets", TString::kIgnoreCase)){
      calc -> ProduceWeight(m_jsf->GetWeight());
   }
  
   bool HalilEvent =false;
    
   cleaner.TauCleanerDecayModeFinding(20,2.1);

   std::vector<Tau> uncleaned_taus;
   for(unsigned int i=0; i<bcc->taus->size(); ++i) {
      uncleaned_taus.push_back(bcc->taus->at(i));
   }
   std::vector<Muon> uncleaned_muons;
   for(unsigned int i=0; i<bcc->muons->size(); ++i) {
      uncleaned_muons.push_back(bcc->muons->at(i));
   }
   if (bcc-> taus) cleaner.TauCleanerHalil(20, 2.1);
   if (bcc-> muons) cleaner.MuonCleanerHalil(25, 2.1, 0.12);
   if (HalilSelection->passSelection(bcc)) HalilEvent = true;

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


   //if (!OneTauSelection -> passSelection(bcc))  throw SError( SError::SkipEvent ); //exactly one tau!!!!
   if (bcc->jets) cleaner.JetCleaner(30,2.5,true);
  
   if (!JetSelection->passSelection(bcc))  throw SError( SError::SkipEvent );
   //if (!OneJetSelection->passSelection(bcc))  throw SError( SError::SkipEvent );
   FillControlHistos("_oneJetSelection");
  
   if (!METSelection->passSelection(bcc))  throw SError( SError::SkipEvent );

   if (AntibTagSelection->passSelection(bcc))  throw SError( SError::SkipEvent );
   FillControlHistos("_ControlPlots");
  
   if (OneJetSelection->passSelection(bcc)) FillControlHistos("_DecayModeEfficiency_1");

   if (!TauSelection -> passSelection(bcc)) throw SError( SError::SkipEvent );
   FillControlHistos("_ControlPlots2");
  
   if (OneJetSelection->passSelection(bcc) && OneTauSelection->passSelection(bcc)) FillControlHistos("_DecayModeEfficiency_2");

   weight = calc ->GetWeight();
   if (!InvMassSelection -> passSelection(bcc)) throw SError( SError::SkipEvent );
     
   // ----------------------------------------------------------------------------- 
   std::vector<Jet> jets_NoLeptonOverlapRemoval;
   for(unsigned int i=0; i<bcc->jets->size(); ++i) {
      jets_NoLeptonOverlapRemoval.push_back(bcc->jets->at(i));
   }  	
  
   if (bcc->jets) cleaner.JetLeptonOverlapRemoval();
   if (!JetSelection->passSelection(bcc))  throw SError( SError::SkipEvent );

  
   FillControlHistos("_AntibTagSelection");
 
   if (SameSignSelection->passSelection(bcc)) FillControlHistos("_SameSignSelection");
   else FillControlHistos("_OppositeSignSelection");

   if (HalilEvent) FillControlHistos("_SameSignSelection_HalilEvent");
   else FillControlHistos("_OppositeSignSelection_HalilEvent");
  

   if (!IsRealData && RealTauSelection->passSelection(bcc))
      {
         FillControlHistos("_RealTauSelection");
      }
   if (!IsRealData && !RealTauSelection->passSelection(bcc))
      {
         FillControlHistos("_FakeTauSelection");
      }
      
  
   // // ----------------------- at least one tau ------------------------------------
  
   // int NJets = bcc->jets->size();
   // double HT = calc->GetHT();
  
   // Muon muon = bcc->muons->at(0);
  
   // for (unsigned int i =0; i< bcc->taus->size(); ++i)
   //    {
   //       Tau tau = bcc->taus->at(i);
   //       std::vector<Jet> *jets = calc->GetJets();
   //       double DeltaR = deltaRmin(&tau, jets);
   //       bool IsElectronOrMuon = false;
   //       if (!IsRealData)
   //          {
   //             bool fake = true;
   //             for(unsigned int j=0; j<bcc->genparticles->size(); ++j)
   //                {
   //                   GenParticle genp = bcc->genparticles->at(j);
   //                   double deltaR = genp.deltaR(tau);
   //                   if (deltaR < 0.5 && abs(genp.pdgId())==15) 
   //                      {
   //                         fake = false;
   //                         break;
   //                      }
   //                   if (deltaR < 0.5 && abs(genp.pdgId())==11 && genp.status()==3) 
   //                      {
   //                         IsElectronOrMuon =true; 
   //                         Hist("Electrons_pT_1_binned") -> Fill(tau.pt(),weight);
   //                         Hist("Electrons_eta_1") -> Fill(tau.eta(),weight);
   //                         Hist("Electrons_NJets") -> Fill(NJets,weight);
   //                         Hist("Electrons_HT") -> Fill(HT,weight);
   //                         Hist("Electrons_DeltaR") -> Fill(DeltaR,weight);
   //                         //if (SameSignSelection->passSelection(bcc)) Hist("Electrons_SameSign") -> Fill(tau.pt(),weight);
   //                         //else Hist("Electrons_OppositeSign") -> Fill(tau.pt(),weight);
   //                         if (HalilEvent) Hist("Electrons_SameSign_HalilEvent") -> Fill(tau.pt(),weight);
   //                         else Hist("Electrons_OppositeSign_HalilEvent") -> Fill(tau.pt(),weight);
   //                         //if (HalilEvent) Hist("Electrons_SameSign") -> Fill(tau.pt(),weight);
   //                         //else Hist("Electrons_OppositeSign") -> Fill(tau.pt(),weight);
   //                         FillControlHistos("_Electrons");
   //                         break;
   //                      }
   //                   if (deltaR < 0.5 && abs(genp.pdgId())==13 && genp.status()==3) 
   //                      {
   //                         IsElectronOrMuon =true;
   //                         Hist("Muons_pT_1_binned") -> Fill(tau.pt(),weight);
   //                         Hist("Muons_eta_1") -> Fill(tau.eta(),weight);
   //                         Hist("Muons_NJets") -> Fill(NJets,weight);
   //                         Hist("Muons_HT") -> Fill(HT,weight);
   //                         Hist("Muons_DeltaR") -> Fill(DeltaR,weight);
   //                         //if (SameSignSelection->passSelection(bcc)) Hist("Muons_SameSign") -> Fill(tau.pt(),weight);
   //                         //else Hist("Muons_OppositeSign") -> Fill(tau.pt(),weight);
   //                         if (HalilEvent) Hist("Muons_SameSign_HalilEvent") -> Fill(tau.pt(),weight);
   //                         else Hist("Muons_OppositeSign_HalilEvent") -> Fill(tau.pt(),weight);
   //                         // if (HalilEvent) Hist("Muons_SameSign") -> Fill(tau.pt(),weight);
   //                         //else Hist("Muons_OppositeSign") -> Fill(tau.pt(),weight);
   //                         FillControlHistos("_Muons");
   //                         break;
   //                      }
   //                }
   //             if (!fake && !IsElectronOrMuon) 
   //                {
   //                   Hist("real_pT_1_binned") -> Fill(tau.pt(),weight);
   //                   Hist("real_eta_1") -> Fill(tau.eta(),weight);
   //                   Hist("real_NJets") -> Fill(NJets,weight);
   //                   Hist("real_HT") -> Fill(HT,weight);
   //                   Hist("real_DeltaR") -> Fill(DeltaR,weight);
   //                   //if (SameSignSelection->passSelection(bcc)) Hist("real_SameSign") -> Fill(tau.pt(),weight);
   //                   //else Hist("real_OppositeSign") -> Fill(tau.pt(),weight);
   //                   if (HalilEvent) Hist("real_SameSign_HalilEvent") -> Fill(tau.pt(),weight);
   //                   else Hist("real_OppositeSign_HalilEvent") -> Fill(tau.pt(),weight);
   //                   //if (HalilEvent) Hist("real_SameSign") -> Fill(tau.pt(),weight);
   //                   //else Hist("real_OppositeSign") -> Fill(tau.pt(),weight);
   //                }
   //             if (fake && !IsElectronOrMuon) 
   //                {
   //                   Hist("fake_pT_1_binned") -> Fill(tau.pt(),weight);
   //                   Hist("fake_eta_1") -> Fill(tau.eta(),weight);
   //                   Hist("fake_NJets") -> Fill(NJets,weight);
   //                   Hist("fake_HT") -> Fill(HT,weight);
   //                   Hist("fake_DeltaR") -> Fill(DeltaR,weight);
   //                   //if (SameSignSelection->passSelection(bcc)) Hist("fake_SameSign") -> Fill(tau.pt(),weight);
   //                   //else Hist("fake_OppositeSign") -> Fill(tau.pt(),weight);
   //                   if (HalilEvent) Hist("fake_SameSign_HalilEvent") -> Fill(tau.pt(),weight);
   //                   else Hist("fake_OppositeSign_HalilEvent") -> Fill(tau.pt(),weight);
   //                   int pdgId = Matching(tau, jets_NoLeptonOverlapRemoval);
   //                   if (pdgId == 21) 
   //                      {
   //                         Hist("GluonJet") -> Fill(tau.pt(),weight);
   //                         //if (SameSignSelection->passSelection(bcc)) Hist("GluonJet_SameSign") -> Fill(tau.pt(),weight);
   //                         //else Hist("GluonJet_OppositeSign") -> Fill(tau.pt(),weight);
   //                         // if (HalilEvent) Hist("GluonJet_SameSign_HalilEvent") -> Fill(tau.pt(),weight);
   //                         //else Hist("GluonJet_OppositeSign_HalilEvent") -> Fill(tau.pt(),weight);
   //                      }
   //                   if (abs(pdgId) == 1 || abs(pdgId) == 2 || abs(pdgId) == 3 || abs(pdgId) == 4 || abs(pdgId) == 5 || abs(pdgId) == 6) Hist("QuarkJet") -> Fill(tau.pt(),weight);
   //                   {
   //                      Hist("QuarkJet") -> Fill(tau.pt(),weight);
   //                      //if (SameSignSelection->passSelection(bcc)) Hist("QuarkJet_SameSign") -> Fill(tau.pt(),weight);
   //                      //else Hist("QuarkJet_OppositeSign") -> Fill(tau.pt(),weight);
   //                      //if (HalilEvent) Hist("QuarkJet_SameSign_HalilEvent") -> Fill(tau.pt(),weight);
   //                      //else Hist("QuarkJet_OppositeSign_HalilEvent") -> Fill(tau.pt(),weight);
   //                   }
   //                }
   //          }
   //       if (!IsElectronOrMuon)
   //          {
   //             Hist ("pT_1_binned") -> Fill(tau.pt(),weight);
   //             Hist ("eta_1") -> Fill(tau.eta(),weight);
   //             Hist ("NJets") -> Fill(NJets,weight);
   //             Hist ("HT") -> Fill(HT,weight);
   //             Hist ("DeltaR") -> Fill(DeltaR,weight);
   //             // if (SameSignSelection->passSelection(bcc)) Hist ("SameSign") -> Fill(tau.pt(),weight);
   //             //else Hist ("OppositeSign") -> Fill(tau.pt(),weight);
   //             if (HalilEvent) Hist ("SameSign_HalilEvent") -> Fill(tau.pt(),weight);
   //             else Hist ("OppositeSign_HalilEvent") -> Fill(tau.pt(),weight);
   //          }
   //    }
   // //------------------------------------------------------------------------------
  

  
   // // if (bcc-> taus) cleaner.TauCleaner_noIso(20, 2.1);
  
   // // if (!TauSelection -> passSelection(bcc))  throw SError( SError::SkipEvent );
  
   // // if (!AntibTagSelection->passSelection(bcc) && InvMassSelection -> passSelection(bcc) ) 
   // //     {
   // // 	  FillControlHistos("_AntibTagSelection_MediumTauSelection_noIso");
   // // 	  if (!IsRealData && RealTauSelection->passSelection(bcc))
   // // 	    {
   // // 	      FillControlHistos("_RealTauSelection_MediumTauSelection_noIso");
   // // 	    }
   // // 	  if (!IsRealData && !RealTauSelection->passSelection(bcc))
   // // 	    {
   // // 	      FillControlHistos("_FakeTauSelection_MediumTauSelection_noIso");
   // // 	    } 
   // //     }
  
   // if (bcc-> taus) cleaner.TauCleaner(20, 2.1);
   // if (bcc->jets) cleaner.JetLeptonOverlapRemoval(); 
  
   // if (!TauSelection -> passSelection(bcc))  throw SError( SError::SkipEvent );
  
   // //if (!IsRealData) calc -> ProduceWeight( m_lsf->GetTauWeight()); //Cross-check
   // //weight = calc ->GetWeight();
   // // ------------------------------------------------------------------------------      
  
   // FillControlHistos("_AntibTagSelection_MediumTauSelection");

   // // if (SameSignSelection->passSelection(bcc)) FillControlHistos("_SameSignSelection_MediumSelection");
   // //else FillControlHistos("_OppositeSignSelection_MediumSelection");
   // if (HalilEvent)FillControlHistos("_SameSignSelection_MediumSelection_HalilEvent");
   // else FillControlHistos("_OppositeSignSelection_MediumSelection_HalilEvent");

   // if (!IsRealData && RealTauSelection->passSelection(bcc))
   //    {
   //       FillControlHistos("_RealTauSelection_MediumTauSelection");
   //    }
   // if (!IsRealData && !RealTauSelection->passSelection(bcc))
   //    {
   //       FillControlHistos("_FakeTauSelection_MediumTauSelection");
   //    }
  
   // // ----------------------- at least one tau ------------------------------------- 
  
   // NJets = bcc->jets->size();
   // HT = calc->GetHT();
  
   // for (unsigned int i=0; i< bcc->taus->size(); ++i)
   //    {
   //       Tau tau = bcc->taus->at(i);
   //       std::vector<Jet> *jets = calc->GetJets();
   //       double DeltaR = deltaRmin(&tau, jets);
   //       bool IsElectronOrMuon = false;
   //       if (!IsRealData)
   //          {
   //             bool fake = true;
   //             for(unsigned int j=0; j<bcc->genparticles->size(); ++j)
   //                {
   //                   GenParticle genp = bcc->genparticles->at(j);
   //                   double deltaR = genp.deltaR(tau);
   //                   if (deltaR < 0.5 && abs(genp.pdgId())==15 ) 
   //                      {
   //                         fake = false;
   //                         break;
   //                      }
   //                   if (deltaR < 0.5 && abs(genp.pdgId())==11 && genp.status()==3) 
   //                      {
   //                         IsElectronOrMuon =true; 
   //                         Hist("Electrons_pT_1_binned_mediumSelection") -> Fill(tau.pt(),weight);
   //                         Hist("Electrons_eta_1_mediumSelection") -> Fill(tau.eta(),weight);
   //                         Hist("Electrons_NJets_mediumSelection") -> Fill(NJets,weight);
   //                         Hist("Electrons_HT_mediumSelection") -> Fill(HT,weight);
   //                         Hist("Electrons_DeltaR_mediumSelection") -> Fill(DeltaR,weight);
   //                         //if (SameSignSelection->passSelection(bcc)) Hist("Electrons_SameSign_mediumSelection") -> Fill(tau.pt(),weight);
   //                         //else Hist("Electrons_OppositeSign_mediumSelection") -> Fill(tau.pt(),weight);
   //                         if (HalilEvent) Hist("Electrons_SameSign_mediumSelection_HalilEvent") -> Fill(tau.pt(),weight);
   //                         else Hist("Electrons_OppositeSign_mediumSelection_HalilEvent") -> Fill(tau.pt(),weight);
   //                         FillControlHistos("_Electrons_MediumSelection");
   //                         break;
   //                      }
   //                   if (deltaR < 0.5 && abs(genp.pdgId())==13 && genp.status()==3) 
   //                      {
   //                         IsElectronOrMuon =true; 
   //                         Hist("Muons_pT_1_binned_mediumSelection") -> Fill(tau.pt(),weight);
   //                         Hist("Muons_eta_1_mediumSelection") -> Fill(tau.eta(),weight);
   //                         Hist("Muons_NJets_mediumSelection") -> Fill(NJets,weight);
   //                         Hist("Muons_HT_mediumSelection") -> Fill(HT,weight);
   //                         Hist("Muons_DeltaR_mediumSelection") -> Fill(DeltaR,weight);
   //                         //if (SameSignSelection->passSelection(bcc)) Hist("Muons_SameSign_mediumSelection") -> Fill(tau.pt(),weight);
   //                         //else Hist("Muons_OppositeSign_mediumSelection") -> Fill(tau.pt(),weight);
   //                         if (HalilEvent) Hist("Muons_SameSign_mediumSelection_HalilEvent") -> Fill(tau.pt(),weight);
   //                         else Hist("Muons_OppositeSign_mediumSelection_HalilEvent") -> Fill(tau.pt(),weight);
      
   //                         FillControlHistos("_Muons_MediumSelection");
   //                         break;
   //                      }
   //                }
   //             if (!fake && !IsElectronOrMuon) {
   //                Hist("real_pT_1_binned_mediumSelection") -> Fill(tau.pt(),weight);
   //                Hist("real_eta_1_mediumSelection") -> Fill(tau.eta(),weight);
   //                Hist("real_NJets_mediumSelection") -> Fill(NJets,weight);
   //                Hist("real_HT_mediumSelection") -> Fill(HT,weight);
   //                Hist("real_DeltaR_mediumSelection") -> Fill(DeltaR,weight);
   //                //if (SameSignSelection->passSelection(bcc)) Hist("real_SameSign_mediumSelection") -> Fill(tau.pt(),weight);
   //                //else Hist("real_OppositeSign_mediumSelection") -> Fill(tau.pt(),weight);
   //                if (HalilEvent) Hist("real_SameSign_mediumSelection_HalilEvent") -> Fill(tau.pt(),weight);
   //                else Hist("real_OppositeSign_mediumSelection_HalilEvent") -> Fill(tau.pt(),weight);
   //             }
   //             if (fake && !IsElectronOrMuon) 
   //                {
   //                   Hist("fake_pT_1_binned_mediumSelection") -> Fill(tau.pt(),weight);
   //                   Hist("fake_eta_1_mediumSelection") -> Fill(tau.eta(),weight);
   //                   Hist("fake_NJets_mediumSelection") -> Fill(NJets,weight);
   //                   Hist("fake_HT_mediumSelection") -> Fill(HT,weight);
   //                   Hist("fake_DeltaR_mediumSelection") -> Fill(DeltaR,weight);
   //                   //if (SameSignSelection->passSelection(bcc)) Hist("fake_SameSign_mediumSelection") -> Fill(tau.pt(),weight);
   //                   //else Hist("fake_OppositeSign_mediumSelection") -> Fill(tau.pt(),weight);
   //                   if (HalilEvent) Hist("fake_SameSign_mediumSelection_HalilEvent") -> Fill(tau.pt(),weight);
   //                   else Hist("fake_OppositeSign_mediumSelection_HalilEvent") -> Fill(tau.pt(),weight);
	      
	      
   //                   int pdgId = Matching(tau, jets_NoLeptonOverlapRemoval);
   //                   if (pdgId == 21) 
   //                      {
   //                         Hist("GluonJet_mediumSelection") -> Fill(tau.pt(),weight);
   //                         //if (SameSignSelection->passSelection(bcc))  Hist("GluonJet_SameSign_mediumSelection") -> Fill(tau.pt(),weight);
   //                         //else Hist("GluonJet_OppositeSign_mediumSelection") -> Fill(tau.pt(),weight);
   //                         //if (HalilEvent)  Hist("GluonJet_SameSign_mediumSelection_HalilEvent") -> Fill(tau.pt(),weight);
   //                         //else Hist("GluonJet_OppositeSign_mediumSelection_HalilEvent") -> Fill(tau.pt(),weight);
   //                      }
   //                   if (abs(pdgId) == 1 || abs(pdgId) == 2 || abs(pdgId) == 3 || abs(pdgId) == 4 || abs(pdgId) == 5 || abs(pdgId) == 6) 
   //                      {
   //                         Hist("QuarkJet_mediumSelection") -> Fill(tau.pt(),weight);
   //                         // if (SameSignSelection->passSelection(bcc))  Hist("QuarkJet_SameSign_mediumSelection") -> Fill(tau.pt(),weight);
   //                         //else Hist("QuarkJet_OppositeSign_mediumSelection") -> Fill(tau.pt(),weight);
   //                         //if (HalilEvent)  Hist("QuarkJet_SameSign_mediumSelection_HalilEvent") -> Fill(tau.pt(),weight);
   //                         //else Hist("QuarkJet_OppositeSign_mediumSelection_HalilEvent") -> Fill(tau.pt(),weight);
   //                      }
   //                }
   //          }
   //       if (!IsElectronOrMuon)
   //          {
   //             Hist ("pT_1_binned_mediumSelection") -> Fill(tau.pt(),weight);
   //             Hist ("eta_1_mediumSelection") -> Fill(tau.eta(),weight);
   //             Hist ("NJets_mediumSelection") -> Fill(NJets,weight);
   //             Hist ("HT_mediumSelection") -> Fill(HT,weight);
   //             Hist ("DeltaR_mediumSelection") -> Fill(DeltaR,weight);
   //             //if (SameSignSelection->passSelection(bcc)) Hist ("SameSign_mediumSelection") -> Fill(tau.pt(),weight);
   //             //else Hist ("OppositeSign_mediumSelection") -> Fill(tau.pt(),weight);
   //             if (HalilEvent) Hist ("SameSign_mediumSelection_HalilEvent") -> Fill(tau.pt(),weight);
   //             else Hist ("OppositeSign_mediumSelection_HalilEvent") -> Fill(tau.pt(),weight);
   //          }
   //    }
   //----------------------------------------------------------------------------------------
   Muon muon = bcc->muons->at(0);
   bcc->taus->clear();
   for(unsigned int i=0; i<uncleaned_taus.size(); ++i) 
      {
         bcc->taus->push_back(uncleaned_taus.at(i));
      }
  
   for (unsigned int i =0; i< bcc->taus->size(); ++i)
      {
         Tau tau = bcc->taus->at(i);
         // cout << "vor medium tau: "<< tau.againstElectronTightMVA3() << tau.againstMuonTight2() << tau.byMediumCombinedIsolationDeltaBetaCorr() <<endl; 
         bool IsElectronOrMuon = false;
         if (!IsRealData)
            {
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
                           if (muon.charge()==tau.charge()) Hist("Electrons_SameSign") -> Fill(tau.pt(),weight);
                           else Hist("Electrons_OppositeSign") -> Fill(tau.pt(),weight);
                           
                           if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() < 60) Hist("Electrons_pT_Tau_1")->Fill(1, weight);
                           if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() < 60) Hist("Electrons_pT_Tau_1")->Fill(2, weight);
                           if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() < 60) Hist("Electrons_pT_Tau_1")->Fill(3, weight);
                           if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() < 60) Hist("Electrons_pT_Tau_1")->Fill(4, weight);
                           
                           if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("Electrons_pT_Tau_2")->Fill(1, weight);
                           if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("Electrons_pT_Tau_2")->Fill(2, weight);
                           if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("Electrons_pT_Tau_2")->Fill(3, weight);
                           if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("Electrons_pT_Tau_2")->Fill(4, weight);
                           
                           if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 120 && tau.pt()< 200) Hist("Electrons_pT_Tau_3")->Fill(1, weight);
                           if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("Electrons_pT_Tau_3")->Fill(2, weight);
                           if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("Electrons_pT_Tau_3")->Fill(3, weight);
                           if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("Electrons_pT_Tau_3")->Fill(4, weight);
                           
                           if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 200) Hist("Electrons_pT_Tau_4")->Fill(1, weight);
                           if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 200) Hist("Electrons_pT_Tau_4")->Fill(2, weight);
                           if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 200) Hist("Electrons_pT_Tau_4")->Fill(3, weight);
                           if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 200) Hist("Electrons_pT_Tau_4")->Fill(4, weight);
                           
                           break;
                        }
                     if (deltaR < 0.5 && abs(genp.pdgId())==13 && genp.status()==3) 
                        {
                           IsElectronOrMuon =true;
                           if (muon.charge()==tau.charge()) Hist("Muons_SameSign") -> Fill(tau.pt(),weight);
                           else Hist("Muons_OppositeSign") -> Fill(tau.pt(),weight);

                           if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() < 60) Hist("Muons_pT_Tau_1")->Fill(1, weight);
                           if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() < 60) Hist("Muons_pT_Tau_1")->Fill(2, weight);
                           if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() < 60) Hist("Muons_pT_Tau_1")->Fill(3, weight);
                           if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() < 60) Hist("Muons_pT_Tau_1")->Fill(4, weight);
                           
                           if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("Muons_pT_Tau_2")->Fill(1, weight);
                           if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("Muons_pT_Tau_2")->Fill(2, weight);
                           if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("Muons_pT_Tau_2")->Fill(3, weight);
                           if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("Muons_pT_Tau_2")->Fill(4, weight);
                           
                           if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 120 && tau.pt()< 200) Hist("Muons_pT_Tau_3")->Fill(1, weight);
                           if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("Muons_pT_Tau_3")->Fill(2, weight);
                           if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("Muons_pT_Tau_3")->Fill(3, weight);
                           if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("Muons_pT_Tau_3")->Fill(4, weight);
                           
                           if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 200) Hist("Muons_pT_Tau_4")->Fill(1, weight);
                           if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 200) Hist("Muons_pT_Tau_4")->Fill(2, weight);
                           if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 200) Hist("Muons_pT_Tau_4")->Fill(3, weight);
                           if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 200) Hist("Muons_pT_Tau_4")->Fill(4, weight);

                           break;
                        }
                  }
               if (!fake && !IsElectronOrMuon) 
                  {
                     if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() < 60) Hist("real_pT_Tau_1")->Fill(1, weight);
                     if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() < 60) Hist("real_pT_Tau_1")->Fill(2, weight);
                     if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() < 60) Hist("real_pT_Tau_1")->Fill(3, weight);
                     if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() < 60) Hist("real_pT_Tau_1")->Fill(4, weight);
                     
                     if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("real_pT_Tau_2")->Fill(1, weight);
                     if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("real_pT_Tau_2")->Fill(2, weight);
                     if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("real_pT_Tau_2")->Fill(3, weight);
                     if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("real_pT_Tau_2")->Fill(4, weight);
                     
                     if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 120 && tau.pt()< 200) Hist("real_pT_Tau_3")->Fill(1, weight);
                     if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("real_pT_Tau_3")->Fill(2, weight);
                     if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("real_pT_Tau_3")->Fill(3, weight);
                     if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("real_pT_Tau_3")->Fill(4, weight);
                     
                     if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 200) Hist("real_pT_Tau_4")->Fill(1, weight);
                     if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 200) Hist("real_pT_Tau_4")->Fill(2, weight);
                     if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 200) Hist("real_pT_Tau_4")->Fill(3, weight);
                     if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 200) Hist("real_pT_Tau_4")->Fill(4, weight);

                     if (muon.charge()==tau.charge()) Hist("real_SameSign") -> Fill(tau.pt(),weight);
                     else Hist("real_OppositeSign") -> Fill(tau.pt(),weight);
                  }
               if (fake && !IsElectronOrMuon) 
                  {
                     if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() < 60) Hist("fake_pT_Tau_1")->Fill(1, weight);
                     if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() < 60) Hist("fake_pT_Tau_1")->Fill(2, weight);
                     if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() < 60) Hist("fake_pT_Tau_1")->Fill(3, weight);
                     if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() < 60) Hist("fake_pT_Tau_1")->Fill(4, weight);
                     
                     if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("fake_pT_Tau_2")->Fill(1, weight);
                     if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("fake_pT_Tau_2")->Fill(2, weight);
                     if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("fake_pT_Tau_2")->Fill(3, weight);
                     if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("fake_pT_Tau_2")->Fill(4, weight);
                     
                     if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 120 && tau.pt()< 200) Hist("fake_pT_Tau_3")->Fill(1, weight);
                     if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("fake_pT_Tau_3")->Fill(2, weight);
                     if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("fake_pT_Tau_3")->Fill(3, weight);
                     if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("fake_pT_Tau_3")->Fill(4, weight);
                     
                     if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 200) Hist("fake_pT_Tau_4")->Fill(1, weight);
                     if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 200) Hist("fake_pT_Tau_4")->Fill(2, weight);
                     if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 200) Hist("fake_pT_Tau_4")->Fill(3, weight);
                     if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 200) Hist("fake_pT_Tau_4")->Fill(4, weight);

                     int PdgId_new = GenParticleMatching(tau);
                     if (PdgId_new ==21 && tau.pt() < 60 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("Gluon_pT_Tau_1")->Fill(1, weight);
                     if (PdgId_new ==21 && tau.pt() < 60 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("Gluon_pT_Tau_1")->Fill(2, weight);
                     if (PdgId_new ==21 && tau.pt() < 60 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("Gluon_pT_Tau_1")->Fill(3, weight);
                     if (PdgId_new ==21 && tau.pt() < 60 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("Gluon_pT_Tau_1")->Fill(4, weight);   
                     
                     if (PdgId_new ==21 && tau.pt() >= 60 && tau.pt()<120 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("Gluon_pT_Tau_2")->Fill(1, weight);
                     if (PdgId_new ==21 && tau.pt() >= 60 && tau.pt()<120 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("Gluon_pT_Tau_2")->Fill(2, weight);
                     if (PdgId_new ==21 && tau.pt() >= 60 && tau.pt()<120 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("Gluon_pT_Tau_2")->Fill(3, weight);
                     if (PdgId_new ==21 && tau.pt() >= 60 && tau.pt()<120 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("Gluon_pT_Tau_2")->Fill(4, weight);   
                     
                     if (PdgId_new ==21 && tau.pt() >= 120 && tau.pt()<200 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("Gluon_pT_Tau_3")->Fill(1, weight);
                     if (PdgId_new ==21 && tau.pt() >= 120 && tau.pt()<200 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("Gluon_pT_Tau_3")->Fill(2, weight);
                     if (PdgId_new ==21 && tau.pt() >= 120 && tau.pt()<200 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("Gluon_pT_Tau_3")->Fill(3, weight);
                     if (PdgId_new ==21 && tau.pt() >= 120 && tau.pt()<200 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("Gluon_pT_Tau_3")->Fill(4, weight);   
                     
                     if (PdgId_new ==21 && tau.pt() >= 200 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("Gluon_pT_Tau_4")->Fill(1, weight);
                     if (PdgId_new ==21 && tau.pt() >= 200 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("Gluon_pT_Tau_4")->Fill(2, weight);
                     if (PdgId_new ==21 && tau.pt() >= 200 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("Gluon_pT_Tau_4")->Fill(3, weight);
                     if (PdgId_new ==21 && tau.pt() >= 200 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("Gluon_pT_Tau_4")->Fill(4, weight);   
                     
                     if (((PdgId_new ==2 || PdgId_new ==4) && tau.charge()==1) || ((PdgId_new ==-2 || PdgId_new ==-4) && tau.charge()==-1))
                        {
                           //Kategorie gruen
                           if (tau.pt() < 60 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("Up_SS_pT_Tau_1")->Fill(1, weight);
                           if (tau.pt() < 60 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("Up_SS_pT_Tau_1")->Fill(2, weight);
                           if (tau.pt() < 60 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("Up_SS_pT_Tau_1")->Fill(3, weight);
                           if (tau.pt() < 60 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("Up_SS_pT_Tau_1")->Fill(4, weight);   
                           
                           if (tau.pt() >= 60 && tau.pt()<120 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("Up_SS_pT_Tau_2")->Fill(1, weight);
                           if (tau.pt() >= 60 && tau.pt()<120 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("Up_SS_pT_Tau_2")->Fill(2, weight);
                           if (tau.pt() >= 60 && tau.pt()<120 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("Up_SS_pT_Tau_2")->Fill(3, weight);
                           if (tau.pt() >= 60 && tau.pt()<120 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("Up_SS_pT_Tau_2")->Fill(4, weight);   
                           
                           if (tau.pt() >= 120 && tau.pt()<200 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("Up_SS_pT_Tau_3")->Fill(1, weight);
                           if (tau.pt() >= 120 && tau.pt()<200 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("Up_SS_pT_Tau_3")->Fill(2, weight);
                           if (tau.pt() >= 120 && tau.pt()<200 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("Up_SS_pT_Tau_3")->Fill(3, weight);
                           if (tau.pt() >= 120 && tau.pt()<200 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("Up_SS_pT_Tau_3")->Fill(4, weight);   
                           
                           if (tau.pt() >= 200 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("Up_SS_pT_Tau_4")->Fill(1, weight);
                           if (tau.pt() >= 200 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("Up_SS_pT_Tau_4")->Fill(2, weight);
                           if (tau.pt() >= 200 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("Up_SS_pT_Tau_4")->Fill(3, weight);
                           if (tau.pt() >= 200 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("Up_SS_pT_Tau_4")->Fill(4, weight);   
                        }
                     
                     if (((PdgId_new ==1 || PdgId_new ==3 || PdgId_new ==5) && tau.charge()==1) || ((PdgId_new ==-1 || PdgId_new ==-3 || PdgId_new ==-5) && tau.charge()==-1))
                        {
                           //Kategorie pink
                           if (tau.pt() < 60 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("Down_SS_pT_Tau_1")->Fill(1, weight);
                           if (tau.pt() < 60 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("Down_SS_pT_Tau_1")->Fill(2, weight);
                           if (tau.pt() < 60 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("Down_SS_pT_Tau_1")->Fill(3, weight);
                           if (tau.pt() < 60 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("Down_SS_pT_Tau_1")->Fill(4, weight);   
                           
                           if (tau.pt() >= 60 && tau.pt()<120 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("Down_SS_pT_Tau_2")->Fill(1, weight);
                           if (tau.pt() >= 60 && tau.pt()<120 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("Down_SS_pT_Tau_2")->Fill(2, weight);
                           if (tau.pt() >= 60 && tau.pt()<120 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("Down_SS_pT_Tau_2")->Fill(3, weight);
                           if (tau.pt() >= 60 && tau.pt()<120 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("Down_SS_pT_Tau_2")->Fill(4, weight);   
                           
                           if (tau.pt() >= 120 && tau.pt()<200 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("Down_SS_pT_Tau_3")->Fill(1, weight);
                           if (tau.pt() >= 120 && tau.pt()<200 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("Down_SS_pT_Tau_3")->Fill(2, weight);
                           if (tau.pt() >= 120 && tau.pt()<200 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("Down_SS_pT_Tau_3")->Fill(3, weight);
                           if (tau.pt() >= 120 && tau.pt()<200 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("Down_SS_pT_Tau_3")->Fill(4, weight);   
                           
                           if (tau.pt() >= 200 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("Down_SS_pT_Tau_4")->Fill(1, weight);
                           if (tau.pt() >= 200 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("Down_SS_pT_Tau_4")->Fill(2, weight);
                           if (tau.pt() >= 200 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("Down_SS_pT_Tau_4")->Fill(3, weight);
                           if (tau.pt() >= 200 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("Down_SS_pT_Tau_4")->Fill(4, weight);   
                        }
                     if (((PdgId_new ==1 || PdgId_new ==3 || PdgId_new ==5) && tau.charge()==-1) || ((PdgId_new ==-1 || PdgId_new ==-3 || PdgId_new ==-5) && tau.charge()==1) || ((PdgId_new ==2 || PdgId_new ==4) && tau.charge()==-1) || ((PdgId_new ==-2 || PdgId_new ==-4) && tau.charge()==1))
                        {
                           //Kategorie weiss und gelb
                           if (tau.pt() < 60 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("ChargeFlip_pT_Tau_1")->Fill(1, weight);
                           if (tau.pt() < 60 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("ChargeFlip_pT_Tau_1")->Fill(2, weight);
                           if (tau.pt() < 60 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("ChargeFlip_pT_Tau_1")->Fill(3, weight);
                           if (tau.pt() < 60 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("ChargeFlip_pT_Tau_1")->Fill(4, weight);   
                           
                           if (tau.pt() >= 60 && tau.pt()<120 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("ChargeFlip_pT_Tau_2")->Fill(1, weight);
                           if (tau.pt() >= 60 && tau.pt()<120 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("ChargeFlip_pT_Tau_2")->Fill(2, weight);
                           if (tau.pt() >= 60 && tau.pt()<120 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("ChargeFlip_pT_Tau_2")->Fill(3, weight);
                           if (tau.pt() >= 60 && tau.pt()<120 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("ChargeFlip_pT_Tau_2")->Fill(4, weight);   
                           
                           if (tau.pt() >= 120 && tau.pt()<200 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("ChargeFlip_pT_Tau_3")->Fill(1, weight);
                           if (tau.pt() >= 120 && tau.pt()<200 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("ChargeFlip_pT_Tau_3")->Fill(2, weight);
                           if (tau.pt() >= 120 && tau.pt()<200 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("ChargeFlip_pT_Tau_3")->Fill(3, weight);
                           if (tau.pt() >= 120 && tau.pt()<200 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("ChargeFlip_pT_Tau_3")->Fill(4, weight);   
                           
                           if (tau.pt() >= 200 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("ChargeFlip_pT_Tau_4")->Fill(1, weight);
                           if (tau.pt() >= 200 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("ChargeFlip_pT_Tau_4")->Fill(2, weight);
                           if (tau.pt() >= 200 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("ChargeFlip_pT_Tau_4")->Fill(3, weight);
                           if (tau.pt() >= 200 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("ChargeFlip_pT_Tau_4")->Fill(4, weight);   
                        }

                     int PdgId_GenParticleMatching = GenParticleMatching(tau); 
                     Hist("GenParticleMatching") -> Fill(PdgId_GenParticleMatching, weight);
                     if (muon.charge()==tau.charge()) 
                        {
                           Hist("fake_SameSign") -> Fill(tau.pt(),weight);
                           if (muon.charge()==1) 
                              {
                                 Hist("GenParticleMatching_SameSign_Plus") -> Fill(PdgId_GenParticleMatching, weight);
                                 if (tau.pt() < 60) Hist("GenParticleMatching_SameSign_Plus_1") -> Fill(PdgId_GenParticleMatching, weight);
                                 if (tau.pt() >= 60 && tau.pt()<120) Hist("GenParticleMatching_SameSign_Plus_2") -> Fill(PdgId_GenParticleMatching, weight);
                                 if (tau.pt() >= 120 && tau.pt()<200) Hist("GenParticleMatching_SameSign_Plus_3") -> Fill(PdgId_GenParticleMatching, weight);
                                 if (tau.pt() >= 200) Hist("GenParticleMatching_SameSign_Plus_4") -> Fill(PdgId_GenParticleMatching, weight);
                              }
                           else 
                              {
                                 Hist("GenParticleMatching_SameSign_Minus") -> Fill(PdgId_GenParticleMatching, weight);
                                 if (tau.pt() < 60) Hist("GenParticleMatching_SameSign_Minus_1") -> Fill(PdgId_GenParticleMatching, weight);
                                 if (tau.pt() >= 60 && tau.pt()<120) Hist("GenParticleMatching_SameSign_Minus_2") -> Fill(PdgId_GenParticleMatching, weight);
                                 if (tau.pt() >= 120 && tau.pt()<200) Hist("GenParticleMatching_SameSign_Minus_3") -> Fill(PdgId_GenParticleMatching, weight);
                                 if (tau.pt() >= 200) Hist("GenParticleMatching_SameSign_Minus_4") -> Fill(PdgId_GenParticleMatching, weight);
                              }
                           if (tau.pt() < 60) Hist("GenParticleMatching_SameSign_1") -> Fill(PdgId_GenParticleMatching, weight);
                           if (tau.pt() >= 60 && tau.pt()<120) Hist("GenParticleMatching_SameSign_2") -> Fill(PdgId_GenParticleMatching, weight);
                           if (tau.pt() >= 120 && tau.pt()<200) Hist("GenParticleMatching_SameSign_3") -> Fill(PdgId_GenParticleMatching, weight);
                           if (tau.pt() >= 200) Hist("GenParticleMatching_SameSign_4") -> Fill(PdgId_GenParticleMatching, weight);
                        }
                     else 
                        {
                           Hist("fake_OppositeSign") -> Fill(tau.pt(),weight);
                           if (muon.charge()==1) 
                              {
                                 Hist("GenParticleMatching_OppositeSign_Plus") -> Fill(PdgId_GenParticleMatching, weight);
                                 if (tau.pt() < 60) Hist("GenParticleMatching_OppositeSign_Plus_1") -> Fill(PdgId_GenParticleMatching, weight);
                                 if (tau.pt() >= 60 && tau.pt()<120) Hist("GenParticleMatching_OppositeSign_Plus_2") -> Fill(PdgId_GenParticleMatching, weight);
                                 if (tau.pt() >= 120 && tau.pt()<200) Hist("GenParticleMatching_OppositeSign_Plus_3") -> Fill(PdgId_GenParticleMatching, weight);
                                 if (tau.pt() >= 200) Hist("GenParticleMatching_OppositeSign_Plus_4") -> Fill(PdgId_GenParticleMatching, weight);
                              }
                           else 
                              {
                                 Hist("GenParticleMatching_OppositeSign_Minus") -> Fill(PdgId_GenParticleMatching, weight);
                                 if (tau.pt() < 60) Hist("GenParticleMatching_OppositeSign_Minus_1") -> Fill(PdgId_GenParticleMatching, weight);
                                 if (tau.pt() >= 60 && tau.pt()<120) Hist("GenParticleMatching_OppositeSign_Minus_2") -> Fill(PdgId_GenParticleMatching, weight);
                                 if (tau.pt() >= 120 && tau.pt()<200) Hist("GenParticleMatching_OppositeSign_Minus_3") -> Fill(PdgId_GenParticleMatching, weight);
                                 if (tau.pt() >= 200) Hist("GenParticleMatching_OppositeSign_Minus_4") -> Fill(PdgId_GenParticleMatching, weight);
                              }
                           if (tau.pt() < 60) Hist("GenParticleMatching_OppositeSign_1") -> Fill(PdgId_GenParticleMatching, weight);
                           if (tau.pt() >= 60 && tau.pt()<120) Hist("GenParticleMatching_OppositeSign_2") -> Fill(PdgId_GenParticleMatching, weight);
                           if (tau.pt() >= 120 && tau.pt()<200) Hist("GenParticleMatching_OppositeSign_3") -> Fill(PdgId_GenParticleMatching, weight);
                           if (tau.pt() >= 200) Hist("GenParticleMatching_OppositeSign_4") -> Fill(PdgId_GenParticleMatching, weight);
                        }
                     int pdgId = Matching(tau, jets_NoLeptonOverlapRemoval);
                     if (pdgId == 21) 
                        {
                           if (muon.charge()==tau.charge()) Hist("GluonJet_SameSign") -> Fill(tau.pt(),weight);
                           else Hist("GluonJet_OppositeSign") -> Fill(tau.pt(),weight);
                        }
                     if (abs(pdgId) == 1 || abs(pdgId) == 2 || abs(pdgId) == 3 || abs(pdgId) == 4 || abs(pdgId) == 5 || abs(pdgId) == 6) Hist("QuarkJet") -> Fill(tau.pt(),weight);
                     {
                        if (muon.charge()==tau.charge()) Hist("QuarkJet_SameSign") -> Fill(tau.pt(),weight);
                        else Hist("QuarkJet_OppositeSign") -> Fill(tau.pt(),weight);
                     }
                  }
            }
         if (!IsElectronOrMuon)
            {
               if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() < 60) Hist("pT_Tau_1")->Fill(1, weight);
               if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() < 60) Hist("pT_Tau_1")->Fill(2, weight);
               if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() < 60) Hist("pT_Tau_1")->Fill(3, weight);
               if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() < 60) Hist("pT_Tau_1")->Fill(4, weight);
               
               if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("pT_Tau_2")->Fill(1, weight);
               if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("pT_Tau_2")->Fill(2, weight);
               if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("pT_Tau_2")->Fill(3, weight);
               if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("pT_Tau_2")->Fill(4, weight);

               if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 120 && tau.pt()< 200) Hist("pT_Tau_3")->Fill(1, weight);
               if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("pT_Tau_3")->Fill(2, weight);
               if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("pT_Tau_3")->Fill(3, weight);
               if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("pT_Tau_3")->Fill(4, weight);

               if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 200) Hist("pT_Tau_4")->Fill(1, weight);
               if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 200) Hist("pT_Tau_4")->Fill(2, weight);
               if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 200) Hist("pT_Tau_4")->Fill(3, weight);
               if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 200) Hist("pT_Tau_4")->Fill(4, weight);

               if (muon.charge()==tau.charge()) Hist ("SameSign") -> Fill(tau.pt(),weight);
               else Hist ("OppositeSign") -> Fill(tau.pt(),weight);
            }
  
         if(tau.againstElectronTightMVA3() && tau.againstMuonTight2() && tau.byMediumCombinedIsolationDeltaBetaCorr()) 
            {
               //cout << "nach medium tau: "<< tau.againstElectronTightMVA3() << tau.againstMuonTight2() << tau.byMediumCombinedIsolationDeltaBetaCorr() <<endl; 
               bool IsElectronOrMuon = false;
               if (!IsRealData)
                  {
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
                                 if (muon.charge()==tau.charge()) Hist("Electrons_SameSign_mediumSelection") -> Fill(tau.pt(),weight);
                                 else Hist("Electrons_OppositeSign_mediumSelection") -> Fill(tau.pt(),weight);
                                 
                                 if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() < 60) Hist("Electrons_pT_Tau_1_Medium")->Fill(1, weight);
                                 if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() < 60) Hist("Electrons_pT_Tau_1_Medium")->Fill(2, weight);
                                 if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() < 60) Hist("Electrons_pT_Tau_1_Medium")->Fill(3, weight);
                                 if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() < 60) Hist("Electrons_pT_Tau_1_Medium")->Fill(4, weight);
                           
                                 if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("Electrons_pT_Tau_2_Medium")->Fill(1, weight);
                                 if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("Electrons_pT_Tau_2_Medium")->Fill(2, weight);
                                 if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("Electrons_pT_Tau_2_Medium")->Fill(3, weight);
                                 if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("Electrons_pT_Tau_2_Medium")->Fill(4, weight);
                                 
                                 if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 120 && tau.pt()< 200) Hist("Electrons_pT_Tau_3_Medium")->Fill(1, weight);
                                 if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("Electrons_pT_Tau_3_Medium")->Fill(2, weight);
                                 if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("Electrons_pT_Tau_3_Medium")->Fill(3, weight);
                                 if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("Electrons_pT_Tau_3_Medium")->Fill(4, weight);
                                 
                                 if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 200) Hist("Electrons_pT_Tau_4_Medium")->Fill(1, weight);
                                 if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 200) Hist("Electrons_pT_Tau_4_Medium")->Fill(2, weight);
                                 if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 200) Hist("Electrons_pT_Tau_4_Medium")->Fill(3, weight);
                                 if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 200) Hist("Electrons_pT_Tau_4_Medium")->Fill(4, weight);

                                 break;
                              }
                           if (deltaR < 0.5 && abs(genp.pdgId())==13 && genp.status()==3) 
                              {
                                 IsElectronOrMuon =true;
                                 if (muon.charge()==tau.charge()) Hist("Muons_SameSign_mediumSelection") -> Fill(tau.pt(),weight);
                                 else Hist("Muons_OppositeSign_mediumSelection") -> Fill(tau.pt(),weight);
                                 
                                 if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() < 60) Hist("Muons_pT_Tau_1_Medium")->Fill(1, weight);
                                 if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() < 60) Hist("Muons_pT_Tau_1_Medium")->Fill(2, weight);
                                 if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() < 60) Hist("Muons_pT_Tau_1_Medium")->Fill(3, weight);
                                 if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() < 60) Hist("Muons_pT_Tau_1_Medium")->Fill(4, weight);
                           
                                 if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("Muons_pT_Tau_2_Medium")->Fill(1, weight);
                                 if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("Muons_pT_Tau_2_Medium")->Fill(2, weight);
                                 if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("Muons_pT_Tau_2_Medium")->Fill(3, weight);
                                 if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("Muons_pT_Tau_2_Medium")->Fill(4, weight);
                                 
                                 if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 120 && tau.pt()< 200) Hist("Muons_pT_Tau_3_Medium")->Fill(1, weight);
                                 if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("Muons_pT_Tau_3_Medium")->Fill(2, weight);
                                 if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("Muons_pT_Tau_3_Medium")->Fill(3, weight);
                                 if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("Muons_pT_Tau_3_Medium")->Fill(4, weight);
                                 
                                 if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 200) Hist("Muons_pT_Tau_4_Medium")->Fill(1, weight);
                                 if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 200) Hist("Muons_pT_Tau_4_Medium")->Fill(2, weight);
                                 if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 200) Hist("Muons_pT_Tau_4_Medium")->Fill(3, weight);
                                 if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 200) Hist("Muons_pT_Tau_4_Medium")->Fill(4, weight);

                                 break;
                              }
                        }
                  
                     if (!fake && !IsElectronOrMuon) {

                        if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() < 60) Hist("real_pT_Tau_1_Medium")->Fill(1, weight);
                        if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() < 60) Hist("real_pT_Tau_1_Medium")->Fill(2, weight);
                        if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() < 60) Hist("real_pT_Tau_1_Medium")->Fill(3, weight);
                        if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() < 60) Hist("real_pT_Tau_1_Medium")->Fill(4, weight);
                        
                        if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("real_pT_Tau_2_Medium")->Fill(1, weight);
                        if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("real_pT_Tau_2_Medium")->Fill(2, weight);
                        if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("real_pT_Tau_2_Medium")->Fill(3, weight);
                        if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("real_pT_Tau_2_Medium")->Fill(4, weight);
                        
                        if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 120 && tau.pt()< 200) Hist("real_pT_Tau_3_Medium")->Fill(1, weight);
                        if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("real_pT_Tau_3_Medium")->Fill(2, weight);
                        if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("real_pT_Tau_3_Medium")->Fill(3, weight);
                        if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("real_pT_Tau_3_Medium")->Fill(4, weight);
                        
                        if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 200) Hist("real_pT_Tau_4_Medium")->Fill(1, weight);
                        if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 200) Hist("real_pT_Tau_4_Medium")->Fill(2, weight);
                        if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 200) Hist("real_pT_Tau_4_Medium")->Fill(3, weight);
                        if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 200) Hist("real_pT_Tau_4_Medium")->Fill(4, weight);
                        
                        if (muon.charge()==tau.charge()) Hist("real_SameSign_mediumSelection") -> Fill(tau.pt(),weight);
                        else Hist("real_OppositeSign_mediumSelection") -> Fill(tau.pt(),weight);
                     }
                     if (fake && !IsElectronOrMuon) 
                        {
                           if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() < 60) Hist("fake_pT_Tau_1_Medium")->Fill(1, weight);
                           if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() < 60) Hist("fake_pT_Tau_1_Medium")->Fill(2, weight);
                           if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() < 60) Hist("fake_pT_Tau_1_Medium")->Fill(3, weight);
                           if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() < 60) Hist("fake_pT_Tau_1_Medium")->Fill(4, weight);
                           
                           if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("fake_pT_Tau_2_Medium")->Fill(1, weight);
                           if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("fake_pT_Tau_2_Medium")->Fill(2, weight);
                           if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("fake_pT_Tau_2_Medium")->Fill(3, weight);
                           if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("fake_pT_Tau_2_Medium")->Fill(4, weight);
                           
                           if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 120 && tau.pt()< 200) Hist("fake_pT_Tau_3_Medium")->Fill(1, weight);
                           if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("fake_pT_Tau_3_Medium")->Fill(2, weight);
                           if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("fake_pT_Tau_3_Medium")->Fill(3, weight);
                           if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("fake_pT_Tau_3_Medium")->Fill(4, weight);
                           
                           if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 200) Hist("fake_pT_Tau_4_Medium")->Fill(1, weight);
                           if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 200) Hist("fake_pT_Tau_4_Medium")->Fill(2, weight);
                           if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 200) Hist("fake_pT_Tau_4_Medium")->Fill(3, weight);
                           if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 200) Hist("fake_pT_Tau_4_Medium")->Fill(4, weight);
                           
                           int PdgId_new = GenParticleMatching(tau);
                           if (PdgId_new ==21 && tau.pt() < 60 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("Gluon_pT_Tau_1_Medium")->Fill(1, weight);
                           if (PdgId_new ==21 && tau.pt() < 60 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("Gluon_pT_Tau_1_Medium")->Fill(2, weight);
                           if (PdgId_new ==21 && tau.pt() < 60 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("Gluon_pT_Tau_1_Medium")->Fill(3, weight);
                           if (PdgId_new ==21 && tau.pt() < 60 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("Gluon_pT_Tau_1_Medium")->Fill(4, weight);   
                           
                           if (PdgId_new ==21 && tau.pt() >= 60 && tau.pt()<120 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("Gluon_pT_Tau_2_Medium")->Fill(1, weight);
                           if (PdgId_new ==21 && tau.pt() >= 60 && tau.pt()<120 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("Gluon_pT_Tau_2_Medium")->Fill(2, weight);
                           if (PdgId_new ==21 && tau.pt() >= 60 && tau.pt()<120 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("Gluon_pT_Tau_2_Medium")->Fill(3, weight);
                           if (PdgId_new ==21 && tau.pt() >= 60 && tau.pt()<120 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("Gluon_pT_Tau_2_Medium")->Fill(4, weight);   
                           
                           if (PdgId_new ==21 && tau.pt() >= 120 && tau.pt()<200 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("Gluon_pT_Tau_3_Medium")->Fill(1, weight);
                           if (PdgId_new ==21 && tau.pt() >= 120 && tau.pt()<200 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("Gluon_pT_Tau_3_Medium")->Fill(2, weight);
                           if (PdgId_new ==21 && tau.pt() >= 120 && tau.pt()<200 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("Gluon_pT_Tau_3_Medium")->Fill(3, weight);
                           if (PdgId_new ==21 && tau.pt() >= 120 && tau.pt()<200 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("Gluon_pT_Tau_3_Medium")->Fill(4, weight);   
                           
                           if (PdgId_new ==21 && tau.pt() >= 200 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("Gluon_pT_Tau_4_Medium")->Fill(1, weight);
                           if (PdgId_new ==21 && tau.pt() >= 200 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("Gluon_pT_Tau_4_Medium")->Fill(2, weight);
                           if (PdgId_new ==21 && tau.pt() >= 200 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("Gluon_pT_Tau_4_Medium")->Fill(3, weight);
                           if (PdgId_new ==21 && tau.pt() >= 200 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("Gluon_pT_Tau_4_Medium")->Fill(4, weight);   
                           
                           
                           if (((PdgId_new ==2 || PdgId_new ==4) && tau.charge()==1) || ((PdgId_new ==-2 || PdgId_new ==-4) && tau.charge()==-1))
                              {
                                 //Kategorie gruen
                                 if (tau.pt() < 60 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("Up_SS_pT_Tau_1_Medium")->Fill(1, weight);
                                 if (tau.pt() < 60 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("Up_SS_pT_Tau_1_Medium")->Fill(2, weight);
                                 if (tau.pt() < 60 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("Up_SS_pT_Tau_1_Medium")->Fill(3, weight);
                                 if (tau.pt() < 60 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("Up_SS_pT_Tau_1_Medium")->Fill(4, weight);   
                                 
                                 if (tau.pt() >= 60 && tau.pt()<120 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("Up_SS_pT_Tau_2_Medium")->Fill(1, weight);
                                 if (tau.pt() >= 60 && tau.pt()<120 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("Up_SS_pT_Tau_2_Medium")->Fill(2, weight);
                                 if (tau.pt() >= 60 && tau.pt()<120 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("Up_SS_pT_Tau_2_Medium")->Fill(3, weight);
                                 if (tau.pt() >= 60 && tau.pt()<120 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("Up_SS_pT_Tau_2_Medium")->Fill(4, weight);   
                                 
                                 if (tau.pt() >= 120 && tau.pt()<200 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("Up_SS_pT_Tau_3_Medium")->Fill(1, weight);
                                 if (tau.pt() >= 120 && tau.pt()<200 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("Up_SS_pT_Tau_3_Medium")->Fill(2, weight);
                                 if (tau.pt() >= 120 && tau.pt()<200 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("Up_SS_pT_Tau_3_Medium")->Fill(3, weight);
                                 if (tau.pt() >= 120 && tau.pt()<200 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("Up_SS_pT_Tau_3_Medium")->Fill(4, weight);   
                                 
                                 if (tau.pt() >= 200 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("Up_SS_pT_Tau_4_Medium")->Fill(1, weight);
                                 if (tau.pt() >= 200 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("Up_SS_pT_Tau_4_Medium")->Fill(2, weight);
                                 if (tau.pt() >= 200 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("Up_SS_pT_Tau_4_Medium")->Fill(3, weight);
                                 if (tau.pt() >= 200 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("Up_SS_pT_Tau_4_Medium")->Fill(4, weight);   
                              }
                           
                           if (((PdgId_new ==1 || PdgId_new ==3 || PdgId_new ==5) && tau.charge()==1) || ((PdgId_new ==-1 || PdgId_new ==-3 || PdgId_new ==-5) && tau.charge()==-1))
                              {
                                 //Kategorie pink
                                 if (tau.pt() < 60 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("Down_SS_pT_Tau_1_Medium")->Fill(1, weight);
                                 if (tau.pt() < 60 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("Down_SS_pT_Tau_1_Medium")->Fill(2, weight);
                                 if (tau.pt() < 60 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("Down_SS_pT_Tau_1_Medium")->Fill(3, weight);
                                 if (tau.pt() < 60 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("Down_SS_pT_Tau_1_Medium")->Fill(4, weight);   
                                 
                                 if (tau.pt() >= 60 && tau.pt()<120 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("Down_SS_pT_Tau_2_Medium")->Fill(1, weight);
                                 if (tau.pt() >= 60 && tau.pt()<120 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("Down_SS_pT_Tau_2_Medium")->Fill(2, weight);
                                 if (tau.pt() >= 60 && tau.pt()<120 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("Down_SS_pT_Tau_2_Medium")->Fill(3, weight);
                                 if (tau.pt() >= 60 && tau.pt()<120 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("Down_SS_pT_Tau_2_Medium")->Fill(4, weight);   
                                 
                                 if (tau.pt() >= 120 && tau.pt()<200 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("Down_SS_pT_Tau_3_Medium")->Fill(1, weight);
                                 if (tau.pt() >= 120 && tau.pt()<200 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("Down_SS_pT_Tau_3_Medium")->Fill(2, weight);
                                 if (tau.pt() >= 120 && tau.pt()<200 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("Down_SS_pT_Tau_3_Medium")->Fill(3, weight);
                                 if (tau.pt() >= 120 && tau.pt()<200 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("Down_SS_pT_Tau_3_Medium")->Fill(4, weight);   
                                 
                                 if (tau.pt() >= 200 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("Down_SS_pT_Tau_4_Medium")->Fill(1, weight);
                                 if (tau.pt() >= 200 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("Down_SS_pT_Tau_4_Medium")->Fill(2, weight);
                                 if (tau.pt() >= 200 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("Down_SS_pT_Tau_4_Medium")->Fill(3, weight);
                                 if (tau.pt() >= 200 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("Down_SS_pT_Tau_4_Medium")->Fill(4, weight);   
                              }
                           if (((PdgId_new ==1 || PdgId_new ==3 || PdgId_new ==5) && tau.charge()==-1) || ((PdgId_new ==-1 || PdgId_new ==-3 || PdgId_new ==-5) && tau.charge()==1) || ((PdgId_new ==2 || PdgId_new ==4) && tau.charge()==-1) || ((PdgId_new ==-2 || PdgId_new ==-4) && tau.charge()==1))
                              {
                                 //Kategorie weiss und gelb
                                 if (tau.pt() < 60 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("ChargeFlip_pT_Tau_1_Medium")->Fill(1, weight);
                                 if (tau.pt() < 60 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("ChargeFlip_pT_Tau_1_Medium")->Fill(2, weight);
                                 if (tau.pt() < 60 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("ChargeFlip_pT_Tau_1_Medium")->Fill(3, weight);
                                 if (tau.pt() < 60 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("ChargeFlip_pT_Tau_1_Medium")->Fill(4, weight);   
                                 
                                 if (tau.pt() >= 60 && tau.pt()<120 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("ChargeFlip_pT_Tau_2_Medium")->Fill(1, weight);
                                 if (tau.pt() >= 60 && tau.pt()<120 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("ChargeFlip_pT_Tau_2_Medium")->Fill(2, weight);
                                 if (tau.pt() >= 60 && tau.pt()<120 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("ChargeFlip_pT_Tau_2_Medium")->Fill(3, weight);
                                 if (tau.pt() >= 60 && tau.pt()<120 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("ChargeFlip_pT_Tau_2_Medium")->Fill(4, weight);   
                                 
                                 if (tau.pt() >= 120 && tau.pt()<200 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("ChargeFlip_pT_Tau_3_Medium")->Fill(1, weight);
                                 if (tau.pt() >= 120 && tau.pt()<200 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("ChargeFlip_pT_Tau_3_Medium")->Fill(2, weight);
                                 if (tau.pt() >= 120 && tau.pt()<200 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("ChargeFlip_pT_Tau_3_Medium")->Fill(3, weight);
                                 if (tau.pt() >= 120 && tau.pt()<200 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("ChargeFlip_pT_Tau_3_Medium")->Fill(4, weight);   
                                 
                                 if (tau.pt() >= 200 && muon.charge()==1 && muon.charge()==tau.charge())   Hist("ChargeFlip_pT_Tau_4_Medium")->Fill(1, weight);
                                 if (tau.pt() >= 200 && muon.charge()==-1 && muon.charge()==tau.charge())   Hist("ChargeFlip_pT_Tau_4_Medium")->Fill(2, weight);
                                 if (tau.pt() >= 200 && muon.charge()==1 && muon.charge()!=tau.charge())   Hist("ChargeFlip_pT_Tau_4_Medium")->Fill(3, weight);
                                 if (tau.pt() >= 200 && muon.charge()==-1 && muon.charge()!=tau.charge())   Hist("ChargeFlip_pT_Tau_4_Medium")->Fill(4, weight);   
                              }

                           int PdgId_GenParticleMatching = GenParticleMatching(tau); 
                           Hist("GenParticleMatching_Medium") -> Fill(abs(PdgId_GenParticleMatching), weight);
                           if (muon.charge()==tau.charge()) 
                              {
                                 Hist("fake_SameSign_mediumSelection") -> Fill(tau.pt(),weight);
                                 if (muon.charge()==1) 
                                    {
                                       Hist("GenParticleMatching_SameSign_Plus_Medium") -> Fill(PdgId_GenParticleMatching, weight);
                                       if (tau.pt() < 60) Hist("GenParticleMatching_SameSign_Plus_1_Medium") -> Fill(PdgId_GenParticleMatching, weight);
                                       if (tau.pt() >= 60 && tau.pt()<120) Hist("GenParticleMatching_SameSign_Plus_2_Medium") -> Fill(PdgId_GenParticleMatching, weight);
                                       if (tau.pt() >= 120 && tau.pt()<200) Hist("GenParticleMatching_SameSign_Plus_3_Medium") -> Fill(PdgId_GenParticleMatching, weight);
                                       if (tau.pt() >= 200) Hist("GenParticleMatching_SameSign_Plus_4_Medium") -> Fill(PdgId_GenParticleMatching, weight);
                                    }
                                 else 
                                    {
                                       Hist("GenParticleMatching_SameSign_Minus_Medium") -> Fill(PdgId_GenParticleMatching, weight);
                                       if (tau.pt() < 60) Hist("GenParticleMatching_SameSign_Minus_1_Medium") -> Fill(PdgId_GenParticleMatching, weight);
                                       if (tau.pt() >= 60 && tau.pt()<120) Hist("GenParticleMatching_SameSign_Minus_2_Medium") -> Fill(PdgId_GenParticleMatching, weight);
                                       if (tau.pt() >= 120 && tau.pt()<200) Hist("GenParticleMatching_SameSign_Minus_3_Medium") -> Fill(PdgId_GenParticleMatching, weight);
                                       if (tau.pt() >= 200) Hist("GenParticleMatching_SameSign_Minus_4_Medium") -> Fill(PdgId_GenParticleMatching, weight);
                                    }
                                 if (tau.pt() < 60) Hist("GenParticleMatching_SameSign_1_Medium") -> Fill(PdgId_GenParticleMatching, weight);
                                 if (tau.pt() >= 60 && tau.pt()<120) Hist("GenParticleMatching_SameSign_2_Medium") -> Fill(PdgId_GenParticleMatching, weight);
                                 if (tau.pt() >= 120 && tau.pt()<200) Hist("GenParticleMatching_SameSign_3_Medium") -> Fill(PdgId_GenParticleMatching, weight);
                                 if (tau.pt() >= 200) Hist("GenParticleMatching_SameSign_4_Medium") -> Fill(PdgId_GenParticleMatching, weight);
                              }
                           else 
                              {
                                 Hist("fake_OppositeSign_mediumSelection") -> Fill(tau.pt(),weight);
                                 if (muon.charge()==1) {
                                    Hist("GenParticleMatching_OppositeSign_Plus_Medium") -> Fill(PdgId_GenParticleMatching, weight);
                                    if (tau.pt() < 60) Hist("GenParticleMatching_OppositeSign_Plus_1_Medium") -> Fill(PdgId_GenParticleMatching, weight);
                                    if (tau.pt() >= 60 && tau.pt()<120) Hist("GenParticleMatching_OppositeSign_Plus_2_Medium") -> Fill(PdgId_GenParticleMatching, weight);
                                    if (tau.pt() >= 120 && tau.pt()<200) Hist("GenParticleMatching_OppositeSign_Plus_3_Medium") -> Fill(PdgId_GenParticleMatching, weight);
                                    if (tau.pt() >= 200) Hist("GenParticleMatching_OppositeSign_Plus_4_Medium") -> Fill(PdgId_GenParticleMatching, weight);
                                 }
                                 else 
                                    {
                                       Hist("GenParticleMatching_OppositeSign_Minus_Medium") -> Fill(PdgId_GenParticleMatching, weight);
                                       if (tau.pt() < 60) Hist("GenParticleMatching_OppositeSign_Minus_1_Medium") -> Fill(PdgId_GenParticleMatching, weight);
                                       if (tau.pt() >= 60 && tau.pt()<120) Hist("GenParticleMatching_OppositeSign_Minus_2_Medium") -> Fill(PdgId_GenParticleMatching, weight);
                                       if (tau.pt() >= 120 && tau.pt()<200) Hist("GenParticleMatching_OppositeSign_Minus_3_Medium") -> Fill(PdgId_GenParticleMatching, weight);
                                       if (tau.pt() >= 200) Hist("GenParticleMatching_OppositeSign_Minus_4_Medium") -> Fill(PdgId_GenParticleMatching, weight);
                                    }
                                 if (tau.pt() < 60) Hist("GenParticleMatching_OppositeSign_1_Medium") -> Fill(PdgId_GenParticleMatching, weight);
                                 if (tau.pt() >= 60 && tau.pt()<120) Hist("GenParticleMatching_OppositeSign_2_Medium") -> Fill(PdgId_GenParticleMatching, weight);
                                 if (tau.pt() >= 120 && tau.pt()<200) Hist("GenParticleMatching_OppositeSign_3_Medium") -> Fill(PdgId_GenParticleMatching, weight);
                                 if (tau.pt() >= 200) Hist("GenParticleMatching_OppositeSign_4_Medium") -> Fill(PdgId_GenParticleMatching, weight);
                              }
                           
                           int pdgId = Matching(tau, jets_NoLeptonOverlapRemoval);
                           if (pdgId == 21) 
                              {
                                 if (muon.charge()==tau.charge())  Hist("GluonJet_SameSign_mediumSelection") -> Fill(tau.pt(),weight);
                                 else Hist("GluonJet_OppositeSign_mediumSelection") -> Fill(tau.pt(),weight);
                              }
                           if (abs(pdgId) == 1 || abs(pdgId) == 2 || abs(pdgId) == 3 || abs(pdgId) == 4 || abs(pdgId) == 5 || abs(pdgId) == 6) 
                              {
                                 if (muon.charge()==tau.charge())  Hist("QuarkJet_SameSign_mediumSelection") -> Fill(tau.pt(),weight);
                                 else Hist("QuarkJet_OppositeSign_mediumSelection") -> Fill(tau.pt(),weight);
                              }
                        }
                  }
               if (!IsElectronOrMuon)
                  {
                     if (muon.charge()==tau.charge()) Hist ("SameSign_mediumSelection") -> Fill(tau.pt(),weight);
                     else Hist ("OppositeSign_mediumSelection") -> Fill(tau.pt(),weight);

                     if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() < 60) Hist("pT_Tau_1_Medium")->Fill(1, weight);
                     if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() < 60) Hist("pT_Tau_1_Medium")->Fill(2, weight);
                     if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() < 60) Hist("pT_Tau_1_Medium")->Fill(3, weight);
                     if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() < 60) Hist("pT_Tau_1_Medium")->Fill(4, weight);
                     
                     if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("pT_Tau_2_Medium")->Fill(1, weight);
                     if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("pT_Tau_2_Medium")->Fill(2, weight);
                     if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("pT_Tau_2_Medium")->Fill(3, weight);
                     if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 60 && tau.pt()<120) Hist("pT_Tau_2_Medium")->Fill(4, weight);
                     
                     if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 120 && tau.pt()< 200) Hist("pT_Tau_3_Medium")->Fill(1, weight);
                     if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("pT_Tau_3_Medium")->Fill(2, weight);
                     if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("pT_Tau_3_Medium")->Fill(3, weight);
                     if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 120 && tau.pt() < 200) Hist("pT_Tau_3_Medium")->Fill(4, weight);
                     
                     if (muon.charge()==1 && muon.charge()==tau.charge() && tau.pt() >= 200) Hist("pT_Tau_4_Medium")->Fill(1, weight);
                     if (muon.charge()==-1 && muon.charge()==tau.charge() && tau.pt() >= 200) Hist("pT_Tau_4_Medium")->Fill(2, weight);
                     if (muon.charge()==1 && muon.charge()!=tau.charge() && tau.pt() >= 200) Hist("pT_Tau_4_Medium")->Fill(3, weight);
                     if (muon.charge()==-1 && muon.charge()!=tau.charge() && tau.pt() >= 200) Hist("pT_Tau_4_Medium")->Fill(4, weight);
                  }
               
            }
      }
}
         
         

void TauIdCycle::FillControlHistos(TString postfix)
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


int TauIdCycle::Matching(Tau tau, vector<Jet> jets)
{
   for (unsigned int i=0; i < jets.size(); ++i)
      {
         Jet jet =  jets.at(i);
         double deltaR = tau.deltaR(jet);
         if (deltaR < 0.5) return jet.flavor();
      }
   return 15;
}

int TauIdCycle::GenParticleMatching(Tau tau)
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

