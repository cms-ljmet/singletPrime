{

   gSystem->cd( "../tmvaTX" );
   gROOT->ProcessLine(".L TMVAClassificationApplication_TX.C");

//    TMVAClassificationApplication_TX("BDT","TpTH750.root","../sandbox","../sandbox_BDTOut");
//    TMVAClassificationApplication_TX("BDT","TpTZ750.root","../sandbox","../sandbox_BDTOut");
//    TMVAClassificationApplication_TX("BDT","TpBW750.root","../sandbox","../sandbox_BDTOut");
//    TMVAClassificationApplication_TX("BDT","STOP.root","../sandbox","../sandbox_BDTOut");
//    TMVAClassificationApplication_TX("BDT","TT.root","../sandbox","../sandbox_BDTOut");
//    TMVAClassificationApplication_TX("BDT","VV.root","../sandbox","../sandbox_BDTOut");
//    TMVAClassificationApplication_TX("BDT","WJets.root","../sandbox","../sandbox_BDTOut");
//    TMVAClassificationApplication_TX("BDT","ZJets.root","../sandbox","../sandbox_BDTOut");
//    TMVAClassificationApplication_TX("BDT","mu2012.root","../sandbox","../sandbox_BDTOut");
   TMVAClassificationApplication_TX("BDT","QCDEM.root","../sandbox","../sandbox_BDTOut");
//    TMVAClassificationApplication_TX("BDT","ele2012.root","../sandbox","../sandbox_BDTOut");
   
   gSystem->cd( "../tmvaBW" );
   
   gROOT->ProcessLine(".L TMVAClassificationApplication_BW.C");

//    TMVAClassificationApplication_BW("BDT","TpTH750.root","../sandbox_BDTOut","../sandbox_BDTOut");
//    TMVAClassificationApplication_BW("BDT","TpTZ750.root","../sandbox_BDTOut","../sandbox_BDTOut");
//    TMVAClassificationApplication_BW("BDT","TpBW750.root","../sandbox_BDTOut","../sandbox_BDTOut");
//    TMVAClassificationApplication_BW("BDT","STOP.root","../sandbox_BDTOut","../sandbox_BDTOut");
//    TMVAClassificationApplication_BW("BDT","TT.root","../sandbox_BDTOut","../sandbox_BDTOut");
//    TMVAClassificationApplication_BW("BDT","VV.root","../sandbox_BDTOut","../sandbox_BDTOut");
//    TMVAClassificationApplication_BW("BDT","WJets.root","../sandbox_BDTOut","../sandbox_BDTOut");
//    TMVAClassificationApplication_BW("BDT","ZJets.root","../sandbox_BDTOut","../sandbox_BDTOut");
//    TMVAClassificationApplication_BW("BDT","mu2012.root","../sandbox_BDTOut","../sandbox_BDTOut");
   TMVAClassificationApplication_BW("BDT","QCDEM.root","../sandbox_BDTOut","../sandbox_BDTOut");
//    TMVAClassificationApplication_BW("BDT","ele2012.root","../sandbox_BDTOut","../sandbox_BDTOut");

   gSystem->cd( "../sandbox_BDTOut" );
   gROOT->ProcessLine(".L ../sandbox/scripts/Plotter.C");
   
//   makePlot("__BDT_TX__","TH_TZ",25,-0.8,0.2,"Alt$(bJetPt_CATopoCalc[0],0)>50&&nTightMuons_CommonCalc==1&&nSelJets_CommonCalc>1&&CA8Tau21_JetSubCalc[0]<0.5&&CA8JetPt_JetSubCalc>200&&CAWCSVMSubJets_JetSubCalc[0]<2","19300.","mu","BDT TX","",false,false,false,true,"Plots");
//   makePlot("__BDT_TX__","TH_TZ",30,-0.5,-0.1,"Alt$(bJetPt_CATopoCalc[0],0)>50&&nTightMuons_CommonCalc==1&&nSelJets_CommonCalc>1&&CA8Tau21_JetSubCalc[0]<0.5&&CA8JetPt_JetSubCalc>200&&CAWCSVMSubJets_JetSubCalc[0]<2","19300.","mu","BDT TX","",false,true,false,true,"Plots");
//    makePlot("__BDT_BW__","BW",50,-1,1,"nTightMuons_CommonCalc==1&&nSelJets_CommonCalc>0&&Alt$(bjet_pt_singleLepCalc[0],0)>200&&!(CA8Tau21_JetSubCalc[0]<0.5&&CA8JetPt_JetSubCalc[0]>200)","19300.","mu","BDT BW","",false,false,false,true,"Plots");
//    makePlot("__BDT_BW__","BW",50,-1,1,"nTightMuons_CommonCalc==1&&nSelJets_CommonCalc>0&&Alt$(bjet_pt_singleLepCalc[0],0)>200&&!(CA8Tau21_JetSubCalc[0]<0.5&&CA8JetPt_JetSubCalc[0]>200)","19300.","mu","BDT BW","",false,true,false,true,"Plots");


}