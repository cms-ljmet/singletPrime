#!/bin/sh

mkdir sandbox
cd sandbox

hadd WJets.root ../WJets/*.root
hadd W1Jets.root ../W1Jets/*.root
hadd W2Jets_1.root ../W2Jets/W2Jets*_[1,5,6]*.root
hadd W2Jets_2.root ../W2Jets/W2Jets*_[2,7,8]*.root
hadd W2Jets_3.root ../W2Jets/W2Jets*_[3,4,9]*.root
hadd W2Jets.root W2Jets_1.root W2Jets_2.root W2Jets_3.root
hadd W3Jets_1.root ../W3Jets/W3Jets*_[1,3,4,5]*.root
hadd W3Jets_2.root ../W3Jets/W3Jets*_[2,6,7,8,9]*.root
hadd W3Jets.root W3Jets_1.root W3Jets_2.root
hadd W4Jets.root ../W4Jets/*.root
hadd TT_LH.root ../TT_LH/*.root
hadd TT_LL.root ../TT_LL/*.root
hadd TT_HH.root ../TT_HH/*.root
hadd Ts.root ../T_SChn/*.root
hadd Tt.root ../T_TChn/*.root
hadd Ttw.root ../T_tWChn/*.root
hadd Tbs.root ../Tb_SChn/*.root
hadd Tbt.root ../Tb_TChn/*.root
hadd Tbtw.root ../Tb_tWChn/*.root
hadd WW.root ../WW/*.root
hadd WZ.root ../WZ/*.root
hadd ZZ.root ../ZZ/*.root
hadd ZJets.root ../ZJets/*.root

hadd TpBW750.root ../TpBW/*.root 
hadd TpTZ750.root ../TpTZ/*.root 
hadd TpTH750.root ../TpTH/*.root

hadd Mu2012A.root ../Mu2012A/*.root
hadd Mu2012B.root ../Mu2012B/*.root
hadd Mu2012C_1.root ../Mu2012C/Mu2012C_[1,2,3,4]*.root
hadd Mu2012C_2.root ../Mu2012C/Mu2012C_[5,6,7,8,9]*.root
hadd Mu2012D_1.root ../Mu2012D/Mu2012D_[1,2,3,4]*.root
hadd Mu2012D_2.root ../Mu2012D/Mu2012D_[5,6,7,8,9]*.root
hadd mu2012.root Mu2012*.root

hadd Ele2012A.root ../Ele2012A/*.root
hadd Ele2012B.root ../Ele2012B/*.root
hadd Ele2012C_1.root ../Ele2012C/Ele2012C_[1,2,3,4]*.root
hadd Ele2012C_2.root ../Ele2012C/Ele2012C_[5,6,7,8,9]*.root
hadd Ele2012D_1.root ../Ele2012D/Ele2012D_[1,2,3,4]*.root
hadd Ele2012D_2.root ../Ele2012D/Ele2012D_[5,6,7,8,9]*.root
hadd ele2012.root Ele2012*.root

#find ../QCDEM20/*.root -size +20 | xargs hadd QCDEM_20.root
#find ../QCDEM30/*.root -size +20 | xargs hadd QCDEM_30.root
find ../QCDEM80/*.root -size +20 | xargs hadd QCDEM_80.root
find ../QCDEM170/*.root -size +20 | xargs hadd QCDEM_170.root
hadd QCDEM_250.root ../QCDEM250/QCDEM250*.root
hadd QCDEM_350.root ../QCDEM350/QCDEM350*.root



EventWeightsIterative outputFile='TpTH750.root'      doOneD=1   weight=1.0   events=199988     histoName='histos/nevents'
EventWeightsIterative outputFile='TpTZ750.root'      doOneD=1   weight=1.0   events=199976     histoName='histos/nevents'
EventWeightsIterative outputFile='TpBW750.root'      doOneD=1   weight=1.0   events=199987     histoName='histos/nevents'

EventWeightsIterative outputFile='TT_LH.root'        doOneD=1   weight=104.7   events=25424818	  histoName='histos/nevents'
EventWeightsIterative outputFile='TT_LL.root'        doOneD=1   weight=25.1    events=4246444	  histoName='histos/nevents'
EventWeightsIterative outputFile='TT_HH.root'        doOneD=1   weight=109.2     events=10537444	  histoName='histos/nevents'
hadd TT.root TT_LH.root TT_LL.root TT_HH.root

EventWeightsIterative outputFile='Ttw.root'  	     doOneD=1   weight=11.1    events=497658	  histoName='histos/nevents' 
EventWeightsIterative outputFile='Tbtw.root'  	     doOneD=1   weight=11.1    events=493460	  histoName='histos/nevents' 
EventWeightsIterative outputFile='Ts.root'  	     doOneD=1   weight=3.79    events=259961	  histoName='histos/nevents' 
EventWeightsIterative outputFile='Tbs.root'  	     doOneD=1   weight=1.76    events=139974	  histoName='histos/nevents' 
EventWeightsIterative outputFile='Tt.root'  	     doOneD=1   weight=56.4    events=3758227	  histoName='histos/nevents' 
EventWeightsIterative outputFile='Tbt.root'  	     doOneD=1   weight=30.7    events=1935072	  histoName='histos/nevents' 
hadd STOP.root Ttw.root Tbtw.root Ts.root Tbs.root Tt.root Tbt.root

EventWeightsIterative outputFile='WJets.root'        doOneD=1   weight=36703   events=76102995	  histoName='histos/nevents'
EventWeightsIterative outputFile='W1Jets.root'        doOneD=1   weight=6460   events=23141598	  histoName='histos/nevents'
EventWeightsIterative outputFile='W2Jets.root'        doOneD=1   weight=2065   events=34044921	  histoName='histos/nevents'
EventWeightsIterative outputFile='W3Jets.root'        doOneD=1   weight=620   events=15539503	  histoName='histos/nevents'
EventWeightsIterative outputFile='W4Jets.root'        doOneD=1   weight=254   events=13382803	  histoName='histos/nevents'
EventWeightsIterative outputFile='ZJets.root'        doOneD=1   weight=3504   events=30459503	  histoName='histos/nevents'

EventWeightsIterative outputFile='WW.root'        	 doOneD=1   weight=56     events=10000431	  histoName='histos/nevents'
EventWeightsIterative outputFile='ZZ.root'        	 doOneD=1   weight=17     events=9799908	  histoName='histos/nevents'
EventWeightsIterative outputFile='WZ.root'        	 doOneD=1   weight=33.6   events=10000283	  histoName='histos/nevents'
hadd VV.root WW.root WZ.root ZZ.root

#EventWeightsIterative outputFile='QCDEM20.root'        	 doOneD=1   weight=2914860   events=35040695	  histoName='histos/nevents'
#EventWeightsIterative outputFile='QCDEM30.root'        	 doOneD=1   weight=4615893   events=33088888	  histoName='histos/nevents'
EventWeightsIterative outputFile='QCDEM_80.root'        	 doOneD=1   weight=183294.9   events=34542763	  histoName='histos/nevents'
EventWeightsIterative outputFile='QCDEM_170.root'         doOneD=1   weight=4586.52   events=31697066	  histoName='histos/nevents'
EventWeightsIterative outputFile='QCDEM_250.root'         doOneD=1   weight=556.75   events=34611322	  histoName='histos/nevents'
EventWeightsIterative outputFile='QCDEM_350.root'         doOneD=1   weight=89.1   events=34080562	  histoName='histos/nevents'
hadd QCDEM.root QCDEM*.root

rm Mu2012*.root Ele2012*.root W*Jets_*.root TT_LH.root TT_HH.root TT_LL.root Ttw.root Tbtw.root Ts.root Tbs.root Tt.root Tbt.root WW.root WZ.root ZZ.root QCDEM_*.root
