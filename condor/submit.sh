#!/bin/sh

#Initiate Valid Grid Cert

voms-proxy-init -valid 240:00

####### MC Signal

if [ "$1" == true ]; 
then

python singletPrimeSubmit.py --useMC True --sample TpBW --fileList TprimeToBW_750_Madgraph.txt --submit True --local True
python singletPrimeSubmit.py --useMC True --sample TpTH --fileList TprimeToTH_750_Madgraph.txt --submit True --local True
python singletPrimeSubmit.py --useMC True --sample TpTZ --fileList TprimeToTZ_750_Madgraph.txt --submit True --local True

fi

####### MC Background

if [ "$2" == true ]; 
then

python singletPrimeSubmit.py --useMC True --sample WJets --fileList WJets_Madgraph.txt --submit True --local True
python singletPrimeSubmit.py --useMC True --sample W1Jets --fileList W1Jets_Madgraph.txt --submit True --local True
python singletPrimeSubmit.py --useMC True --sample W2Jets --fileList W2Jets_Madgraph.txt --submit True --local True
python singletPrimeSubmit.py --useMC True --sample W3Jets --fileList W3Jets_Madgraph.txt --submit True --local True
python singletPrimeSubmit.py --useMC True --sample W4Jets --fileList W4Jets_Madgraph.txt --submit True --local True
python singletPrimeSubmit.py --useMC True --sample TT_LH --fileList TTJETS_SemiLeptonic_Madgraph.txt --submit True --local True
python singletPrimeSubmit.py --useMC True --sample TT_LL --fileList TTJETS_Leptonic_Madgraph.txt --submit True --local True
python singletPrimeSubmit.py --useMC True --sample TT_HH --fileList TTJETS_Hadronic_Madgraph.txt --submit True --local True
python singletPrimeSubmit.py --useMC True --sample T_SChn --fileList T_SChannel_Powheg.txt --submit True --local True
python singletPrimeSubmit.py --useMC True --sample T_TChn --fileList T_TChannel_Powheg.txt --submit True --local True
python singletPrimeSubmit.py --useMC True --sample T_tWChn --fileList T_tWChannel_Powheg.txt --submit True --local True
python singletPrimeSubmit.py --useMC True --sample Tb_SChn --fileList TBar_SChannel_Powheg.txt --submit True --local True
python singletPrimeSubmit.py --useMC True --sample Tb_TChn --fileList TBar_TChannel_Powheg.txt --submit True --local True
python singletPrimeSubmit.py --useMC True --sample Tb_tWChn --fileList TBar_tWChannel_Powheg.txt --submit True --local True
python singletPrimeSubmit.py --useMC True --sample WW --fileList WW_Pythia.txt --submit True --local True
python singletPrimeSubmit.py --useMC True --sample WZ --fileList WZ_Pythia.txt --submit True --local True
python singletPrimeSubmit.py --useMC True --sample ZZ --fileList ZZ_Pythia.txt --submit True --local True
python singletPrimeSubmit.py --useMC True --sample ZJets --fileList DYJets_Madgraph.txt --submit True --local True
python singletPrimeSubmit.py --useMC True --sample QCDEM20 --fileList QCDEM20-30_Pythia.txt --submit True --local True
python singletPrimeSubmit.py --useMC True --sample QCDEM30 --fileList QCDEM30-80_Pythia.txt --submit True --local True
python singletPrimeSubmit.py --useMC True --sample QCDEM80 --fileList QCDEM80-170_Pythia.txt --submit True --local True
python singletPrimeSubmit.py --useMC True --sample QCDEM170 --fileList QCDEM170-250_Pythia.txt --submit True --local True
python singletPrimeSubmit.py --useMC True --sample QCDEM250 --fileList QCDEM250-350_Pythia.txt --submit True --local True
python singletPrimeSubmit.py --useMC True --sample QCDEM350 --fileList QCDEM350_Pythia.txt --submit True --local True

fi

####### Data

if [ "$3" == true ]; 
then

python singletPrimeSubmit.py --useMC False --sample Mu2012A --fileList singleMu2012A_22Jan2013.txt --json Jan222013ReReco_json.txt --submit True --local True
python singletPrimeSubmit.py --useMC False --sample Mu2012B --fileList singleMu2012B_22Jan2013.txt --json Jan222013ReReco_json.txt --submit True --local True
python singletPrimeSubmit.py --useMC False --sample Mu2012C --fileList singleMu2012C_22Jan2013.txt --json Jan222013ReReco_json.txt --submit True --local True
python singletPrimeSubmit.py --useMC False --sample Mu2012D --fileList singleMu2012D_22Jan2013.txt --json Jan222013ReReco_json.txt --submit True --local True

python singletPrimeSubmit.py --useMC False --sample Ele2012A --fileList singleEle2012A_22Jan2013.txt --json Jan222013ReReco_json.txt --submit True --local True
python singletPrimeSubmit.py --useMC False --sample Ele2012B --fileList singleEle2012B_22Jan2013.txt --json Jan222013ReReco_json.txt --submit True --local True
#I might be missing some 2012C Electron Data?
python singletPrimeSubmit.py --useMC False --sample Ele2012C --fileList singleEle2012C_22Jan2013.txt --json Jan222013ReReco_json.txt --submit True --local True
python singletPrimeSubmit.py --useMC False --sample Ele2012D --fileList singleEle2012D_22Jan2013.txt --json Jan222013ReReco_json.txt --submit True --local True

fi