{

   gROOT->ProcessLine(".L ../sandbox/scripts/Plotter.C");
   std::string muSel = "nTightMuons_CommonCalc==1&&";
   std::string eleSel = "nTightMuons_CommonCalc==0&&";
   std::string THSel = "nSelJets_CommonCalc>1&&CA8Tau21_JetSubCalc[0]<0.5&&CA8JetPt_JetSubCalc>200&&CAWCSVMSubJets_JetSubCalc[0]==2&&CAWJetMass_JetSubCalc[0]>85&&CAWJetMass_JetSubCalc[0]<145";
   std::string TZSel = "Alt$(bJetPt_CATopoCalc[0],0)>50&&nSelJets_CommonCalc>1&&CA8Tau21_JetSubCalc[0]<0.5&&CA8JetPt_JetSubCalc>200&&CAWCSVMSubJets_JetSubCalc[0]<2&&__BDT_TX__>-0.2";
   std::string BWSel = "nSelJets_CommonCalc>0&&Alt$(bjet_pt_singleLepCalc[0],0)>200&&!(CA8Tau21_JetSubCalc[0]<0.5&&CA8JetPt_JetSubCalc[0]>200)&&__BDT_BW__>-0.1";
   std::string BWLSel = "nSelJets_CommonCalc>0&&Alt$(bjet_pt_singleLepCalc[0],0)>200&&!(CA8Tau21_JetSubCalc[0]<0.5&&CA8JetPt_JetSubCalc[0]>200)&&__BDT_BW__>-0.25&&__BDT_BW__<-0.1";
   std::string TXSel = "CA8Tau21_JetSubCalc[0]<0.5&&CA8JetPt_JetSubCalc>200&&CAWCSVMSubJets_JetSubCalc[0]==0&&n_btags_singleLepCalc==2";

   makeThetaCard("tPrimeMassBestTop_CATopoCalc","ThetaTH.root",15,0,1500,muSel+THSel,"19300","mu","TH");
   makeThetaCard("tPrimeMassBestTop_CATopoCalc","ThetaTZ.root",15,0,1500,muSel+TZSel,"19300","mu","TZ");
   makeThetaCard("BTagTopMass_LjetsTopoCalcNew","ThetaBW.root",15,0,1500,muSel+BWSel,"19300","mu","BW");   
   makeThetaCard("BTagTopMass_LjetsTopoCalcNew","ThetaBWL.root",15,0,1500,muSel+BWLSel,"19300","mu","BWL");   
   makeThetaCard("tPrimeMassBestTop_CATopoCalc","ThetaTX.root",15,0,1500,muSel+TXSel,"19300","mu","TX");

   makeThetaCard("tPrimeMassBestTop_CATopoCalc","ThetaTH_ele.root",15,0,1500,eleSel+THSel,"19300","ele","TH");
   makeThetaCard("tPrimeMassBestTop_CATopoCalc","ThetaTZ_ele.root",15,0,1500,eleSel+TZSel,"19300","ele","TZ");
   makeThetaCard("BTagTopMass_LjetsTopoCalcNew","ThetaBW_ele.root",15,0,1500,eleSel+BWSel,"19300","ele","BW");   
   makeThetaCard("BTagTopMass_LjetsTopoCalcNew","ThetaBWL_ele.root",15,0,1500,eleSel+BWLSel,"19300","ele","BWL");   
   makeThetaCard("tPrimeMassBestTop_CATopoCalc","ThetaTX_ele.root",15,0,1500,eleSel+TXSel,"19300","ele","TX");
   
   
   gSystem->Exec("mkdir -p Plots/TX");
   gSystem->Exec("mkdir -p Plots/TZ");
   gSystem->Exec("mkdir -p Plots/TH");
   gSystem->Exec("mkdir -p Plots/BW");
   gSystem->Exec("mkdir -p Plots/BWL");
   
   makePlot("tPrimeMassBestTop_CATopoCalc","TH_TZ",20,0,2000,eleSel+TXSel,"19300.","ele","T` Mass (Best Top)","",false,false,false,true,"Plots/TX");
   makePlot("tPrimeMassBestTop_CATopoCalc","TH_TZ",20,0,2000,muSel+TXSel,"19300.","mu","T` Mass (Best Top)","",false,false,false,true,"Plots/TX");
   makePlot("tPrimeMassBestTop_CATopoCalc","TH_TZ",20,0,2000,eleSel+TZSel,"19300.","ele","T` Mass (Best Top)","",false,false,false,true,"Plots/TZ");
   makePlot("tPrimeMassBestTop_CATopoCalc","TH_TZ",20,0,2000,muSel+TZSel,"19300.","mu","T` Mass (Best Top)","",false,false,false,true,"Plots/TZ");
   makePlot("tPrimeMassBestTop_CATopoCalc","TH_TZ",10,0,2000,eleSel+THSel,"19300.","ele","T` Mass (Best Top)","",false,false,false,true,"Plots/TH");
   makePlot("tPrimeMassBestTop_CATopoCalc","TH_TZ",10,0,2000,muSel+THSel,"19300.","mu","T` Mass (Best Top)","",false,false,false,true,"Plots/TH");
   makePlot("BTagTopMass_LjetsTopoCalcNew","BW",20,0,2000,eleSel+BWSel,"19300.","ele","T` Mass (l,nu,b)","",false,false,false,true,"Plots/BW");
   makePlot("BTagTopMass_LjetsTopoCalcNew","BW",20,0,2000,muSel+BWSel,"19300.","mu","T` Mass (l,nu,b)","",false,false,false,true,"Plots/BW");
   makePlot("BTagTopMass_LjetsTopoCalcNew","BW",20,0,2000,eleSel+BWLSel,"19300.","ele","T` Mass (l,nu,b)","",false,false,false,true,"Plots/BWL");
   makePlot("BTagTopMass_LjetsTopoCalcNew","BW",20,0,2000,muSel+BWLSel,"19300.","mu","T` Mass (l,nu,b)","",false,false,false,true,"Plots/BWL");

}