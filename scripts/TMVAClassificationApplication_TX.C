/**********************************************************************************
 * Project   : TMVA - a Root-integrated toolkit for multivariate data analysis    *
 * Package   : TMVA                                                               *
 * Exectuable: TMVAClassificationApplication                                      *
 *                                                                                *
 * This macro provides a simple example on how to use the trained classifiers     *
 * within an analysis module                                                      *
 **********************************************************************************/

#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"

#include "/Users/joshua/Research/root/tmva/test/TMVAGui.C"

#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#endif

using namespace TMVA;

void TMVAClassificationApplication_TX(TString myMethodList = "" , TString iFileName = "", TString sampleLocation = "", TString outputLocation = "") 
{   
#ifdef __CINT__
   gROOT->ProcessLine( ".O0" ); // turn off optimization in CINT
#endif

   //---------------------------------------------------------------

   // This loads the library
   TMVA::Tools::Instance();

   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;

   // --- Cut optimisation
   Use["Cuts"]            = 0;
   Use["CutsD"]           = 0;
   Use["CutsPCA"]         = 0;
   Use["CutsGA"]          = 0;
   Use["CutsSA"]          = 0;
   // 
   // 
   // --- Boosted Decision Trees
   Use["BDT"]             = 1; // uses Adaptive Boost
   std::cout << std::endl;
   std::cout << "==> Start TMVAClassificationApplication" << std::endl;

   // Select methods (don't look at this code - not of interest)
   if (myMethodList != "") {
      for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

      std::vector<TString> mlist = gTools().SplitString( myMethodList, ',' );
      for (UInt_t i=0; i<mlist.size(); i++) {
         std::string regMethod(mlist[i]);

         if (Use.find(regMethod) == Use.end()) {
            std::cout << "Method \"" << regMethod 
                      << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
            for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
               std::cout << it->first << " ";
            }
            std::cout << std::endl;
            return;
         }
         Use[regMethod] = 1;
      }
   }

   // --------------------------------------------------------------------------------------------------

   // --- Create the Reader object

   TMVA::Reader *reader = new TMVA::Reader("!Color:!Silent" );    
   // Create a set of variables and declare them to the reader
   // - the variable names MUST corresponds in name and type to those given in the weight file(s) used
   Float_t var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22, var23, var24, var25, var26, var27, var28, var29;
   //reader->AddVariable( "Alt$(jet_pt_singleLepCalc[0],0)", &var1);
   //reader->AddVariable( "Alt$(jet_pt_singleLepCalc[1],0)", &var2 );
   //reader->AddVariable( "Alt$(jet_pt_singleLepCalc[2],0)", &var3 );
   reader->AddVariable( "Alt$(bJetPt_CATopoCalc[0],0)", &var4 );
   reader->AddVariable( "Alt$(bJetPt_CATopoCalc[1],0)", &var5 );
   //reader->AddVariable( "corr_met_singleLepCalc", &var6 );
   //reader->AddVariable( "muon_1_pt_singleLepCalc", &var7 );
   //reader->AddVariable( "nBJets_CATopoCalc", &var8 );
   //reader->AddVariable( "nSelJets_CommonCalc", &var9 );
   //reader->AddVariable( "LeptonJet_DeltaR_LjetsTopoCalcNew", &var10);
   reader->AddVariable( "Mevent_LjetsTopoCalcNew", &var11);
   //reader->AddVariable( "W_Pt_LjetsTopoCalcNew", &var12 );
   reader->AddVariable( "Jet1Jet2_Pt_LjetsTopoCalcNew", &var13 );
   //reader->AddVariable( "BestTop_LjetsTopoCalcNew", &var14 );
   //reader->AddVariable( "BTagTopMass_LjetsTopoCalcNew", &var15 );
   //reader->AddVariable( "Alt$(CAHEPTopJetMass_JetSubCalc[0],0)", &var16 );
   //reader->AddVariable( "Alt$(CAWCSVMSubJets_JetSubCalc[0],0)", &var17 );
   //reader->AddVariable( "Alt$(CAWCSVLSubJets_JetSubCalc[0],0)", &var18 );
   reader->AddVariable( "Alt$(CAWJetPt_JetSubCalc[0],0)", &var19 );
   reader->AddVariable( "Alt$(CAWJetMass_JetSubCalc[0],0)", &var20 );
   //reader->AddVariable( "Alt$(CAHEPTopJetMass_JetSubCalc[1],0)", &var21 );
   //reader->AddVariable( "Hz_LjetsTopoCalcNew", &var22 );
   //reader->AddVariable( "Centrality_LjetsTopoCalcNew", &var23 );
   reader->AddVariable( "SqrtsT_LjetsTopoCalcNew", &var24 );
   reader->AddVariable( "CAMindrBMass_CATopoCalc", &var28 );
   reader->AddVariable( "minDRCAtoB_CATopoCalc",  &var29 );
   //reader->AddVariable( "HT2prime_LjetsTopoCalcNew", &var25 );
   reader->AddVariable( "HT2_LjetsTopoCalcNew", &var26 );
   //reader->AddVariable( "dphiLepMet_LjetsTopoCalcNew", &var27 );
     


   // Spectator variables declared in the training have to be added to the reader, too
//    Float_t spec1,spec2;
//    reader->AddSpectator( "spec1 := var1*2",   &spec1 );
//    reader->AddSpectator( "spec2 := var1*3",   &spec2 );

//    Float_t Category_cat1, Category_cat2, Category_cat3;
//    if (Use["Category"]){
//       // Add artificial spectators for distinguishing categories
//       reader->AddSpectator( "Category_cat1 := var3<=0",             &Category_cat1 );
//       reader->AddSpectator( "Category_cat2 := (var3>0)&&(var4<0)",  &Category_cat2 );
//       reader->AddSpectator( "Category_cat3 := (var3>0)&&(var4>=0)", &Category_cat3 );
//    }

   // --- Book the MVA methods
   // Book method(s)
  TString weightFileName = "weights/TMVAClassification_BDT.weights";
  reader->BookMVA("BDT method", weightFileName+".xml" ); 

   
   // Book output histograms
   UInt_t nbin = 100;
   TH1F   *histBdt(0);
   histBdt = new TH1F( "MVA_BDT_TX",  "MVA_BDT_TX", nbin, -1.0, 1.0);

   // Prepare input tree (this must be replaced by your data source)
   // in this example, there is a toy tree with signal and one with background events
   // we'll later on use only the "signal" events for the test in this example.
   //   
   TFile *input(0);
   TString fileName = iFileName;
   TString fname = sampleLocation+"/";
   fname += fileName;
   TString oFileName = fileName;

   if (!gSystem->AccessPathName( fname )) 
      input = TFile::Open( fname ); // check if file in local directory exists
   if (!input) {
      std::cout << "ERROR: could not open data file" << std::endl;
      exit(1);
   }
   std::cout << "--- TMVAClassificationApp    : Using input file: " << input->GetName() << std::endl;

   // --- Event loop

   // Prepare the event tree
   // - here the variable names have to corresponds to your tree
   // - you can use the same variables as above which is slightly faster,
   //   but of course you can use different ones and copy the values inside the event loop
   //
   std::cout << "--- Select signal sample" << std::endl;
   TTree* theTree = (TTree*)input->Get("ljmet");
   gSystem->mkdir( outputLocation );
   TFile *target  = new TFile( outputLocation+"/"+oFileName,"RECREATE" );
   TTree *newTree = theTree->CloneTree();
   Float_t BDT;
   TBranch *branchBDT = newTree->Branch("__BDT_TX__",&BDT,"__BDT_TX__/F");
   std::vector<Double_t> *vecVar1;
   std::vector<Double_t> *vecVar4;
   std::vector<Double_t> *vecVar16;
   std::vector<Int_t> *vecVar17;
   std::vector<Int_t> *vecVar18;
   std::vector<Double_t> *vecVar19;
   std::vector<Double_t> *vecVar20;
   Int_t *intVar5, *intVar8, *intVar9;
   Double_t *dVar2, *dVar3, *dVar6, *dVar7, *dVar10, *dVar11, *dVar12, *dVar13, *dVar14, *dVar15, *dVar22, *dVar23, *dVar24, dVar25, *dVar26, *dVar27, *dVar28, *dVar29;
   theTree->SetBranchAddress( "jet_pt_singleLepCalc", &vecVar1);
   theTree->SetBranchAddress( "bJetPt_CATopoCalc", &vecVar4 );
   theTree->SetBranchAddress( "corr_met_singleLepCalc", &dVar6 );
   theTree->SetBranchAddress( "muon_1_pt_singleLepCalc", &dVar7 );
   theTree->SetBranchAddress( "nBJets_CATopoCalc", &intVar8 );
   theTree->SetBranchAddress( "nSelJets_CommonCalc", &intVar9 );
   theTree->SetBranchAddress( "LeptonJet_DeltaR_LjetsTopoCalcNew", &dVar10);
   theTree->SetBranchAddress( "Mevent_LjetsTopoCalcNew", &dVar11);
   theTree->SetBranchAddress( "W_Pt_LjetsTopoCalcNew", &dVar12 );
   theTree->SetBranchAddress( "Jet1Jet2_Pt_LjetsTopoCalcNew", &dVar13 );
   theTree->SetBranchAddress( "BestTop_LjetsTopoCalcNew", &dVar14 );
   theTree->SetBranchAddress( "BTagTopMass_LjetsTopoCalcNew", &dVar15 );
   theTree->SetBranchAddress( "CAHEPTopJetMass_JetSubCalc", &vecVar16 );
   theTree->SetBranchAddress( "CAWCSVMSubJets_JetSubCalc", &vecVar17 );
   theTree->SetBranchAddress( "CAWCSVLSubJets_JetSubCalc", &vecVar18 );
   theTree->SetBranchAddress( "CAWJetPt_JetSubCalc", &vecVar19 );
   theTree->SetBranchAddress( "CAWJetMass_JetSubCalc", &vecVar20 );
   theTree->SetBranchAddress( "Hz_LjetsTopoCalcNew", &dVar22 );
   theTree->SetBranchAddress( "Centrality_LjetsTopoCalcNew", &dVar23 );
   theTree->SetBranchAddress( "SqrtsT_LjetsTopoCalcNew", &dVar24 );
   theTree->SetBranchAddress( "HT2prime_LjetsTopoCalcNew", &dVar25 );
   theTree->SetBranchAddress( "HT2_LjetsTopoCalcNew", &dVar26 );
   theTree->SetBranchAddress( "dphiLepMet_LjetsTopoCalcNew", &dVar27 );
   theTree->SetBranchAddress( "CAMindrBMass_CATopoCalc", &dVar28 );
   theTree->SetBranchAddress( "minDRCAtoB_CATopoCalc", &dVar29 );


   // Efficiency calculator for cut method
   Int_t    nSelCutsGA = 0;
   Double_t effS       = 0.7;

   std::vector<Float_t> vecVar(4); // vector for EvaluateMVA tests

   std::cout << "--- Processing: " << theTree->GetEntries() << " events" << std::endl;
   TStopwatch sw;
   sw.Start();
   for (Long64_t ievt=0; ievt<theTree->GetEntries();ievt++) {

      if (ievt%1000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;
      theTree->GetEntry(ievt);
      if(vecVar1->size()>0){
      	var1 = vecVar1->at(0);
      }
      if(vecVar1->size()>1){
      	var2 = vecVar1->at(1);
      }
      if(vecVar1->size()>2){
      	var3 = vecVar1->at(2);
      }
      if(vecVar4->size()>0){
      	var4 = vecVar4->at(0);
      }
      if(vecVar4->size()>1){
      	var5 = vecVar4->at(1);
      }      
      var6 = dVar6;
      var7 = dVar7;
      var8 = intVar8;
      var9 = intVar9;
      var10 = dVar10;
      var11 = dVar11;
      var12 = dVar12;
      var13 = dVar13;
      var14 = dVar14;
      var15 = dVar15;
      if(vecVar16->size()>0){
      	var16 = vecVar16->at(0);
      }
      else{
      	var16 = 0;
      }
      if(vecVar17->size()>0){
      	var17 = vecVar17->at(0);
      }
      else{
      	var18 = 0;
      }
      if(vecVar19->size()>0){
      	var19 = vecVar19->at(0);
      }
      else{
      	var19 = 0;
      }     
      if(vecVar20->size()>0){
      	var20 = vecVar20->at(0);
      }
      else{
      	var20 = 0;
      }
      if(vecVar16->size()>1){
	  	var21 = vecVar16->at(1);
	  }
	  else{
	  	var21 = 0;
	  }
	  var22 = dVar22;
	  var23 = dVar23;
	  var24 = dVar24;
	  var25 = dVar25;
	  var26 = dVar26;
	  var27 = dVar27;
	  var28 = dVar28;
	  var29 = dVar29;      // --- Return the MVA outputs and fill into histograms

      if (Use["CutsGA"]) {
         // Cuts is a special case: give the desired signal efficienciy
         Bool_t passed = reader->EvaluateMVA( "CutsGA method", effS );
         if (passed) nSelCutsGA++;
      }
      BDT = reader->EvaluateMVA( "BDT method");
      histBdt->Fill(BDT);
      branchBDT->Fill();
   }

   // Get elapsed time
   sw.Stop();
   std::cout << "--- End of event loop: "; sw.Print();

   // Get efficiency for cuts classifier
   if (Use["CutsGA"]) std::cout << "--- Efficiency for CutsGA method: " << double(nSelCutsGA)/theTree->GetEntries()
                                << " (for a required signal efficiency of " << effS << ")" << std::endl;

   if (Use["CutsGA"]) {

      // test: retrieve cuts for particular signal efficiency
      // CINT ignores dynamic_casts so we have to use a cuts-secific Reader function to acces the pointer  
      TMVA::MethodCuts* mcuts = reader->FindCutsMVA( "CutsGA method" ) ;

      if (mcuts) {      
         std::vector<Double_t> cutsMin;
         std::vector<Double_t> cutsMax;
         mcuts->GetCuts( 0.7, cutsMin, cutsMax );
         std::cout << "--- -------------------------------------------------------------" << std::endl;
         std::cout << "--- Retrieve cut values for signal efficiency of 0.7 from Reader" << std::endl;
         for (UInt_t ivar=0; ivar<cutsMin.size(); ivar++) {
            std::cout << "... Cut: " 
                      << cutsMin[ivar] 
                      << " < \"" 
                      << mcuts->GetInputVar(ivar)
                      << "\" <= " 
                      << cutsMax[ivar] << std::endl;
         }
         std::cout << "--- -------------------------------------------------------------" << std::endl;
      }
   }

   // --- Write histograms

   newTree->Write("",TObject::kOverwrite);
   target->Close();

   std::cout << "--- Created root file: \""<<oFileName<<"\" containing the MVA output histograms" << std::endl;
  
   delete reader;
    
   std::cout << "==> TMVAClassificationApplication is done!" << endl << std::endl;
} 
