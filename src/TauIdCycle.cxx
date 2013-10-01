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

  Selection* SameSignSelection = new Selection("SameSignSelection");
  SameSignSelection -> addSelectionModule(new SameSignCut());
  
  
  RegisterSelection(JetSelection);
  RegisterSelection(AntibTagSelection);
  RegisterSelection(InvMassSelection);
  RegisterSelection(RealTauSelection);
  RegisterSelection(TauSelection);
  RegisterSelection(OneTauSelection);
  RegisterSelection(SameSignSelection);
    
  // ---------------- set up the histogram collections -------------------- 

  RegisterHistCollection( new JetHists("Jets_ControlPlots"));
  RegisterHistCollection( new EventHists("Events_ControlPlots"));
  RegisterHistCollection( new MuonHists("Muons_ControlPlots"));
  RegisterHistCollection( new TauHists("Taus_ControlPlots"));
  RegisterHistCollection( new ElectronHists("Electrons_ControlPlots"));

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
  
  Double_t bins[5] = {20, 60, 120, 200, 800};
  Book( TH1F( "pT_1_binned", "p_{T} leading tau [GeV]",4, bins));
  Book( TH1F( "real_pT_1_binned", "p_{T} leading tau [GeV]",4, bins));
  Book( TH1F( "fake_pT_1_binned", "p_{T} leading tau [GeV]",4, bins));
  Book( TH1F( "Muons_pT_1_binned", "p_{T} leading tau [GeV]",4, bins));
  Book( TH1F( "Electrons_pT_1_binned", "p_{T} leading tau [GeV]",4, bins));
  Book( TH1F( "pT_1_binned_mediumSelection", "p_{T} leading tau [GeV]",4, bins));
  Book( TH1F( "real_pT_1_binned_mediumSelection", "p_{T} leading tau [GeV]",4, bins));
  Book( TH1F( "fake_pT_1_binned_mediumSelection", "p_{T} leading tau [GeV]",4, bins));
  Book( TH1F( "Muons_pT_1_binned_mediumSelection", "p_{T} leading tau [GeV]",4, bins));
  Book( TH1F( "Electrons_pT_1_binned_mediumSelection", "p_{T} leading tau [GeV]",4, bins));

  Book( TH1F( "eta_1", "#eta leading tau", 100,-3,3 ) );
  Book( TH1F( "real_eta_1", "#eta leading tau", 100,-3,3 ) );
  Book( TH1F( "fake_eta_1", "#eta leading tau", 100,-3,3 ) );
  Book( TH1F( "eta_1_mediumSelection", "#eta leading tau", 100,-3,3 ) );
  Book( TH1F( "real_eta_1_mediumSelection", "#eta leading tau", 100,-3,3 ) );
  Book( TH1F( "fake_eta_1_mediumSelection", "#eta leading tau", 100,-3,3 ) );
  Book( TH1F( "Muons_eta_1_mediumSelection", "#eta leading tau", 100,-3,3 ) );
  Book( TH1F( "Muons_eta_1", "#eta leading tau", 100,-3,3 ) );
  Book( TH1F( "Electrons_eta_1_mediumSelection", "#eta leading tau", 100,-3,3 ) );
  Book( TH1F( "Electrons_eta_1", "#eta leading tau", 100,-3,3 ) );

  
  
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
  static Selection* AntibTagSelection = GetSelection("AntibTagSelection");
  static Selection* InvMassSelection = GetSelection("InvMassSelection");
  static Selection* RealTauSelection = GetSelection("RealTauSelection");
  static Selection* TauSelection = GetSelection("TauSelection");
  static Selection* OneTauSelection = GetSelection("OneTauSelection");
  static Selection* SameSignSelection = GetSelection("SameSignSelection");

  Cleaner cleaner;
  
  EventCalc* calc = EventCalc::Instance();
  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
  bool IsRealData = calc->IsRealData();
  
  weight = calc ->GetWeight();
  
  //if (!OneTauSelection -> passSelection(bcc))  throw SError( SError::SkipEvent ); //exactly one tau!!!!
  
  FillControlHistos("_ControlPlots");
  
  if (bcc->jets) cleaner.JetCleaner(30,2.5,true);
  if (bcc->jets) cleaner.JetLeptonOverlapRemoval(); 
  
   
  if (!JetSelection->passSelection(bcc))  throw SError( SError::SkipEvent );
  FillControlHistos("_oneJetSelection");
  
  if (!AntibTagSelection->passSelection(bcc) && InvMassSelection -> passSelection(bcc) ) 
    {
      // ----------------------- exactly one tau ------------------------------------- 
     
//       FillControlHistos("_AntibTagSelection");
//       if (!IsRealData && RealTauSelection->passSelection(bcc))
// 	{
// 	  FillControlHistos("_RealTauSelection");
// 	}
//       if (!IsRealData && !RealTauSelection->passSelection(bcc))
// 	{
// 	  FillControlHistos("_FakeTauSelection");
// 	}
      
      
      // ----------------------- at least one tau ------------------------------------
      
       for (unsigned int i =0; i< bcc->taus->size(); ++i)
	{
	  Tau tau = bcc->taus->at(i);
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
		      Hist("Electrons_pT_1_binned") -> Fill(tau.pt(),weight);
		      Hist("Electrons_eta_1") -> Fill(tau.eta(),weight);
		      FillControlHistos("_Electrons");
		      break;
		    }
		  if (deltaR < 0.5 && abs(genp.pdgId())==13 && genp.status()==3) 
		    {
		      IsElectronOrMuon =true;
		      Hist("Muons_pT_1_binned") -> Fill(tau.pt(),weight);
		      Hist("Muons_eta_1") -> Fill(tau.eta(),weight);
		      FillControlHistos("_Muons");
		      break;
		    }
 		}
 	      if (!fake && !IsElectronOrMuon) 
		{
		  Hist("real_pT_1_binned") -> Fill(tau.pt(),weight);
		  Hist("real_eta_1") -> Fill(tau.eta(),weight);
		  FillControlHistos("_RealTauSelection");
		}
 	      if (fake && !IsElectronOrMuon) 
		{
		  Hist("fake_pT_1_binned") -> Fill(tau.pt(),weight);
		  Hist("fake_eta_1") -> Fill(tau.eta(),weight);
		  FillControlHistos("_FakeTauSelection");
		}
	    }
	  if (!IsElectronOrMuon)
	    {
	      Hist ("pT_1_binned") -> Fill(tau.pt(),weight);
	      Hist ("eta_1") -> Fill(tau.eta(),weight);
	      FillControlHistos("_AntibTagSelection");
	    }
	}
      //------------------------------------------------------------------------------
      
    }
  
  // if (bcc-> taus) cleaner.TauCleaner_noIso(20, 2.1);
  
  // if (!TauSelection -> passSelection(bcc))  throw SError( SError::SkipEvent );
  
  // if (!AntibTagSelection->passSelection(bcc) && InvMassSelection -> passSelection(bcc) ) 
  //     {
  // 	  FillControlHistos("_AntibTagSelection_MediumTauSelection_noIso");
  // 	  if (!IsRealData && RealTauSelection->passSelection(bcc))
  // 	    {
  // 	      FillControlHistos("_RealTauSelection_MediumTauSelection_noIso");
  // 	    }
  // 	  if (!IsRealData && !RealTauSelection->passSelection(bcc))
  // 	    {
  // 	      FillControlHistos("_FakeTauSelection_MediumTauSelection_noIso");
  // 	    } 
  //     }
  
  if (bcc-> taus) cleaner.TauCleaner(20, 2.1);
  
  if (!TauSelection -> passSelection(bcc))  throw SError( SError::SkipEvent );
  
//if (!IsRealData) calc -> ProduceWeight( m_lsf->GetTauWeight()); //Cross-check
  
  if (!AntibTagSelection->passSelection(bcc) && InvMassSelection -> passSelection(bcc) ) 
    {
      // ----------------------- exactly one tau -------------------------------------      

   //    FillControlHistos("_AntibTagSelection_MediumTauSelection");
//       if (!IsRealData && RealTauSelection->passSelection(bcc))
// 	{
// 	  FillControlHistos("_RealTauSelection_MediumTauSelection");
// 	}
//       if (!IsRealData && !RealTauSelection->passSelection(bcc))
// 	{
// 	  FillControlHistos("_FakeTauSelection_MediumTauSelection");
// 	}
      
      // ----------------------- at least one tau ------------------------------------- 
      
       for (unsigned int i=0; i< bcc->taus->size(); ++i)
	{
	  Tau tau = bcc->taus->at(i);
	  bool IsElectronOrMuon = false;
	  if (!IsRealData)
 	    {
	      bool fake = true;
	      for(unsigned int j=0; j<bcc->genparticles->size(); ++j)
 		{
 		  GenParticle genp = bcc->genparticles->at(j);
 		  double deltaR = genp.deltaR(tau);
 		  if (deltaR < 0.5 && abs(genp.pdgId())==15 ) 
		    {
		      fake = false;
		      break;
		    }
		  if (deltaR < 0.5 && abs(genp.pdgId())==11 && genp.status()==3) 
		    {
		      IsElectronOrMuon =true; 
		      Hist("Electrons_pT_1_binned_mediumSelection") -> Fill(tau.pt(),weight);
		      Hist("Electrons_eta_1_mediumSelection") -> Fill(tau.eta(),weight);
		      FillControlHistos("_Electrons_MediumSelection");
		      break;
		    }
		  if (deltaR < 0.5 && abs(genp.pdgId())==13 && genp.status()==3) 
		    {
		      IsElectronOrMuon =true; 
		      Hist("Muons_pT_1_binned_mediumSelection") -> Fill(tau.pt(),weight);
		      Hist("Muons_eta_1_mediumSelection") -> Fill(tau.eta(),weight);
		      FillControlHistos("_Muons_MediumSelection");
		      break;
		    }
 		}
 	      if (!fake && !IsElectronOrMuon) {
		Hist("real_pT_1_binned_mediumSelection") -> Fill(tau.pt(),weight);
		Hist("real_eta_1_mediumSelection") -> Fill(tau.eta(),weight);
		FillControlHistos("_RealTauSelection_MediumTauSelection");
	      }
 	      if (fake && !IsElectronOrMuon) 
		{
		  Hist("fake_pT_1_binned_mediumSelection") -> Fill(tau.pt(),weight);
		  Hist("fake_eta_1_mediumSelection") -> Fill(tau.eta(),weight);
		  FillControlHistos("_FakeTauSelection_MediumTauSelection");
		}
	    }
	  if (!IsElectronOrMuon)
	    {
	      FillControlHistos("_AntibTagSelection_MediumTauSelection");
	      Hist ("pT_1_binned_mediumSelection") -> Fill(tau.pt(),weight);
	      Hist ("eta_1_mediumSelection") -> Fill(tau.eta(),weight);
	    }
	}
  //----------------------------------------------------------------------------------------
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
