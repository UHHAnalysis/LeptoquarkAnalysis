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
  SetIntLumiPerBin(25.); 
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
  JetSelection -> addSelectionModule(new NJetSelection(2,999,30,2.5)); 

  Selection* AntibTagSelection = new Selection("AntibTagSelection");
  AntibTagSelection -> addSelectionModule(new NBTagSelection(1,999,e_CSVL));

  Selection* InvMassSelection  = new Selection("InvMassSelection");
  InvMassSelection -> addSelectionModule(new TauMuonInvMassCut(80,100));

  Selection* RealTauSelection  = new Selection("RealTauSelection");
  RealTauSelection -> addSelectionModule(new GenTauSelection());

  Selection* TauSelection = new Selection("TauSelection");
  TauSelection -> addSelectionModule(new NTauSelection(1,999,20,2.1));

  Selection* SameSignSelection = new Selection("SameSignSelection");
  SameSignSelection -> addSelectionModule(new SameSignCut());
  
  RegisterSelection(JetSelection);
  RegisterSelection(AntibTagSelection);
  RegisterSelection(InvMassSelection);
  RegisterSelection(RealTauSelection);
  RegisterSelection(TauSelection);
  RegisterSelection(SameSignSelection);
  
  // ---------------- set up the histogram collections -------------------- 

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

  RegisterHistCollection( new JetHists("Jets_AntibTagSel_MediumTauSelection"));
  RegisterHistCollection( new EventHists("Events_AntibTagSel_MediumTauSelection"));
  RegisterHistCollection( new MuonHists("Muons_AntibTagSel_MediumTauSelection"));
  RegisterHistCollection( new TauHists("Taus_AntibTagSel_MediumTauSelection"));
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
  static Selection* SameSignSelection = GetSelection("SameSignSelection");

      
  Cleaner cleaner;
  
  EventCalc* calc = EventCalc::Instance();
  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
  bool IsRealData = calc->IsRealData();

  if (calc ->GetRunNum() == 201191) throw SError( SError::SkipEvent );

  if (bcc->jets) cleaner.JetCleaner(30,2.5,true);
  if (!JetSelection->passSelection(bcc))  throw SError( SError::SkipEvent );

  if (!AntibTagSelection->passSelection(bcc) && InvMassSelection -> passSelection(bcc) ) 
    {
      FillControlHistos("_AntibTagSelection");
      if (!IsRealData && RealTauSelection->passSelection(bcc))
	{
	  FillControlHistos("_RealTauSelection");
	}
       if (!IsRealData && !RealTauSelection->passSelection(bcc))
	{
	  FillControlHistos("_FakeTauSelection");
	}
      
    }

  if (bcc-> taus) cleaner.TauCleaner(20, 2.1);
  if (bcc->jets) cleaner.JetLeptonOverlapRemoval();

  if (!TauSelection -> passSelection(bcc))  throw SError( SError::SkipEvent );
  
  // if (!IsRealData) calc -> ProduceWeight( m_lsf->GetTauWeight()); //Cross-check
  
  if (!AntibTagSelection->passSelection(bcc) && InvMassSelection -> passSelection(bcc) ) 
    {
      FillControlHistos("_AntibTagSelection_MediumTauSelection");
      if (!IsRealData && RealTauSelection->passSelection(bcc))
	{
	  FillControlHistos("_RealTauSelection_MediumTauSelection");
	}
       if (!IsRealData && !RealTauSelection->passSelection(bcc))
	{
	  FillControlHistos("_FakeTauSelection_MediumTauSelection");
	} 
    }
  return;

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
