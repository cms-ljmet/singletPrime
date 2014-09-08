makePlot(std::string var, std::string decay, int bins, float min, float max, std::string cut, std::string lumi, std::string chn,TString labelX,TString units = "GeV",bool left=false,bool log = false,bool dndm=false,bool doRatio = false, std::string folder_name)
{

  makeDataCard(var, "tmp.root", bins, min, max, cut, lumi, chn, decay);
	if(log){
	  makeStackPlot(TString(var)+"_"+TString(chn)+"_LOG",TString(decay),"tmp.root",labelX,TString(chn),units,left,log,dndm,doRatio, folder_name);
	}
	else{
	  makeStackPlot(TString(var)+"_"+TString(chn),TString(decay),"tmp.root",labelX,TString(chn),units,left,log,dndm,doRatio, folder_name);
	}

}


makeStackPlot(TString name,TString decay,TString file,TString labelX,TString chn,TString units = "GeV",bool left=false,bool log = false,bool dndm=false,bool doRatio = false, TString folder_name, TString parent_folder="Plots")
{

  setStyle();

  float xR=0.55;
  if(left)
    xR=0.2;

  TString SigLeg = "";
	if(decay == "TH"){
		SigLeg = "T`#rightarrow TH";
	}
	else if(decay == "TZ"){
		SigLeg = "T`#rightarrow TZ";
	}
	else if(decay == "BW"){
		SigLeg = "T`#rightarrow BW";
	}
	else if(decay == "TH_TZ"){
		SigLeg = "Will Plot TH and TZ";
	}
	else if(decay == "ALL"){
		SigLeg = "Will Plot All";
	}
	else{
		std::cout << "Signal decay is undefined, not plotting signal" << std::endl;
	} 
	
	
  if(doRatio){
  	TCanvas * c = new TCanvas(name,name,600,600);
  }
  else{
  	TCanvas * c = new TCanvas(name,name,600,600);
    c->SetLeftMargin     (0.18);
    c->SetRightMargin    (0.05);
    c->SetTopMargin      (0.08);
    c->SetBottomMargin   (0.15);
  }

  c->cd();
  
  if(doRatio){
  	TPad * plotPad = new TPad("pad1","",0.0,0.3,1.0,1.0);
  	plotPad->SetLeftMargin  (0.18);
    plotPad->SetTopMargin   (0.10);
    plotPad->SetRightMargin (0.07);
    plotPad->SetBottomMargin(0.03); 
    TPad * ratioPad = new TPad("pad2","",0.0,0.0,1.0,0.3);
    ratioPad->SetLeftMargin  (0.18);
    ratioPad->SetTopMargin   (0.00);
    ratioPad->SetRightMargin (0.07);
    ratioPad->SetBottomMargin(0.30);
    ratioPad->SetGridy(1);
  }
  else{
  	TPad * plotPad = new TPad("pad1","",0.0,0.0,1.0,1.0);
  	plotPad->SetLeftMargin     (0.18);
    plotPad->SetRightMargin    (0.05);
    plotPad->SetTopMargin      (0.08);
    plotPad->SetBottomMargin   (0.15);
  }
  
  plotPad->Draw();
  plotPad->cd();
    
  TFile *f = new TFile(file);

  TH1F * data = (TH1F*)(f->Get("data"));
  if (dndm) convertToDNDM(data);
  applyDATAStyle(data);

  if(chn != "mu"){
  	TH1F * QCD = (TH1F*)(f->Get("QCD"));
  	if (dndm) convertToDNDM(QCD);
  	applyStyle(QCD,kMagenta-10,1,1001);
  }

  TH1F * ttbar = (TH1F*)(f->Get("ttbar"));
  if (dndm) convertToDNDM(ttbar);
  applyStyle(ttbar,kOrange-4,1,1001);

  TH1F * stop = (TH1F*)(f->Get("singletop"));
  if (dndm) convertToDNDM(stop);
  applyStyle(singletop,kAzure+2,1,1001);


  TH1F * EWK = (TH1F*)(f->Get("wjets"));
  EWK->Add((TH1F*)(f->Get("VV")));
  EWK->Add((TH1F*)(f->Get("zjets")));
  if (dndm) convertToDNDM(EWK);
  applyStyle(EWK,kRed+2,1,1001);

  if(decay == "TH"){
	  TH1F *signal = (TH1F*)(f->Get("TH_750"));
	  if (dndm) convertToDNDM(signal);
	  applySignalStyle(signal);
  }
  else if(decay == "TZ"){
	  TH1F *signal = (TH1F*)(f->Get("TZ_750"));
	  if (dndm) convertToDNDM(signal);
	  applySignalStyle2(signal);  
  }
  else if(decay == "BW"){
	  TH1F *signal = (TH1F*)(f->Get("BW_750"));
	  if (dndm) convertToDNDM(signal);
	  applySignalStyle3(signal);  
  }
  else if(decay == "TH_TZ"){
	  TH1F *signal = (TH1F*)(f->Get("TH_750"));
	  TH1F *signal2 = (TH1F*)(f->Get("TZ_750"));
	  if (dndm){ convertToDNDM(signal); convertToDNDM(signal2);}
  	  applySignalStyle(signal);
	  applySignalStyle2(signal2);  
  }
  else if(decay == "ALL"){
	  TH1F *signal = (TH1F*)(f->Get("TH_750"));
	  TH1F *signal2 = (TH1F*)(f->Get("TZ_750"));
	  TH1F *signal3 = (TH1F*)(f->Get("BW_750"));
	  if (dndm){ convertToDNDM(signal); convertToDNDM(signal2); convertToDNDM(signal3);}
  	  applySignalStyle(signal);
	  applySignalStyle2(signal2);  
	  applySignalStyle3(signal3);
  }
  
  
  THStack *hs = new THStack("hs","");
  TLegend *l = new TLegend(xR,0.6,xR+0.5,0.9);

  l->AddEntry(data,"Observed","P");

  l->AddEntry(EWK,"EWK","F");
  if(chn != "mu")
  	l->AddEntry(QCD,"QCD","F");  
  l->AddEntry(ttbar,"t#bar{t}","F");
  l->AddEntry(stop,"Single t","F");

  if(decay == "TH" || decay == "TZ" || decay == "BW"){
	  if(log){
		l->AddEntry(signal,SigLeg,"L");
	  }
	  else{
		l->AddEntry(signal,SigLeg,"F");
	  }
  }
  else if(decay == "TH_TZ"){
	  if(log){
		l->AddEntry(signal,"T`#rightarrow TH","L");
		l->AddEntry(signal2,"T`#rightarrow TZ","L");
	  }
	  else{
		l->AddEntry(signal,"T`#rightarrow TH","F");
		l->AddEntry(signal2,"T`#rightarrow TZ","F");
	  }  
  }
  else if(SigLeg != ""){
	  if(log){
		l->AddEntry(signal,"T`#rightarrow TH","L");
		l->AddEntry(signal2,"T`#rightarrow TZ","L");
		l->AddEntry(signal3,"T`#rightarrow BW","L");
	  }
	  else{
		l->AddEntry(signal,"T`#rightarrow TH","F");
		l->AddEntry(signal2,"T`#rightarrow TZ","F");
		l->AddEntry(signal3,"T`#rightarrow BW","F");
	  }  
  }
  if(chn != "mu")
  	hs->Add(QCD);
  hs->Add(EWK);
  hs->Add(stop);
  hs->Add(ttbar);

  if(!log){
	if(decay == "TH" || decay == "TZ" || decay == "BW"){
		hs->Add(signal);
	}
	else if(decay == "TH_TZ"){
		hs->Add(signal);
		hs->Add(signal2);
	}
	else if(SigLeg != ""){
		hs->Add(signal);
		hs->Add(signal2);
		hs->Add(signal3);
	}
  }
  
  hs->Draw("HIST");
  if(data->GetMaximum()*1.2+sqrt(data->GetMaximum())>hs->GetMaximum()) {
    float max=0.0;
    if(data->GetMaximum()>hs->GetMaximum())
      max=data->GetMaximum();
    else
      max=hs->GetMaximum();

    if(log) {
      max*=10;
      hs->SetMinimum(0.5);
    }
    hs->SetMaximum(max*1.5+sqrt(data->GetMaximum()));
  }

  if(dndm)       hs->SetMinimum(0.001);

  //Draw the error for MC unc and systematics if needed
  TH1F* errorBand = (TH1F*)EWK->Clone();
  
  //Systematic values if needed
  float w  = 0;
  float tt = 0;
  float t  = 0;
  float q  = 0;
	
  errorBand->Add(ttbar);
  errorBand->Add(stop);
  if(chn != "mu")
  	errorBand->Add(QCD);
  
  errorBand  ->SetMarkerSize(0);
  errorBand  ->SetFillColor(1);
  errorBand  ->SetFillStyle(3013);
  errorBand  ->SetLineWidth(1);
  
  l->AddEntry(errorBand, "bkg. uncertainty" , "F" );
  float wErr = 0;
  float ttErr = 0;
  float tErr = 0;
  float qErr = 0;
  
  for(int i=1;i<errorBand->GetNbinsX();++i){
		wErr = EWK->GetBinContent(i)*w + EWK->GetBinError(i);
		ttErr = ttbar->GetBinContent(i)*tt + ttbar->GetBinError(i);
		tErr = stop->GetBinContent(i)*t + stop->GetBinError(i);
		if(chn != "mu")
			qErr = QCD->GetBinContent(i)*q + QCD->GetBinError(i);
		errorBand->SetBinError(i,wErr+ttErr+tErr+qErr);
  }  
  
    
  
  hs->Draw("HIST");
  errorBand->Draw("e2same");
  if(doRatio){
  	hs->GetXaxis()->SetLabelSize(0);
  }
  else
  {
	  if(units!="")
		hs->GetXaxis()->SetTitle(labelX+" ["+units+"]");
	  else
		hs->GetXaxis()->SetTitle(labelX);
  }

  hs->GetYaxis()->SetTitle("Events");
  if(dndm)
    hs->GetYaxis()->SetTitle("dN/d"+labelX);

  if(log){
	if(decay == "TH" || decay == "TZ" || decay == "BW"){
		signal->Draw("HIST,SAME");
	}
	else if(decay == "TH_TZ"){
		signal->Draw("HIST,SAME");
		signal2->Draw("HIST,SAME");
	}
	else if(SigLeg != ""){
		signal->Draw("HIST,SAME");
		signal2->Draw("HIST,SAME");
		signal3->Draw("HIST,SAME");
	}
  }
  
  data->Draw("e,SAME");
  
  c->cd();
  
  if(doRatio){
    
    TH1F * data2 = (TH1F*)data->Clone("data");
    TH1F * mc = (TH1F*)(ttbar);
    if(chn != "mu")
    	mc->Add(QCD);
    mc->Add(EWK);
    mc->Add(stop);
    
    double xmin = mc->GetXaxis()->GetXmin();
    double xmax = mc->GetXaxis()->GetXmax();
    TLine *line = new TLine(xmin,1.0,xmax,1.0);
    line->SetLineWidth(3);
    line->SetLineColor(kBlack);    
    ratioPad->Draw();
  	ratioPad->cd();
  	
  	data2->Divide(data2,mc);
    data2->SetMarkerStyle(20);
    data2->SetTitleSize  (0.12,"Y");
    data2->SetTitleOffset(0.60,"Y");
    data2->SetTitleSize  (0.12,"X");
    data2->SetLabelSize  (0.10,"X");
    data2->SetLabelSize  (0.08,"Y");
    data2->GetYaxis()->SetTitleFont(42);
    data2->GetYaxis()->CenterTitle(kTRUE);
    data2->GetXaxis()->SetTitleFont(42);
    data2->GetYaxis()->SetRangeUser(0.8,1.2);
    data2->GetYaxis()->SetNdivisions(305);
    data2->GetYaxis()->SetTitle("Data/MC");
    data2->SetMarkerSize(1);
    gStyle->SetOptTitle(0);

    if(units!="")
	  data2->GetXaxis()->SetTitle(labelX+" ["+units+"]");
    else
	  data2->GetXaxis()->SetTitle(labelX);
	  
    data2->Draw("P");
    line->Draw();
        
  }
  
  c->cd();
  plotPad->cd();  

  l->SetBorderSize(0);
  l->SetFillColor(0);
  l->SetFillStyle (0);
  l->Draw();

  float factor=0.0;
  if(left) factor = 1./2.2;
  else factor = 1.05;

  float xL = hs->GetXaxis()->GetXmin()+(hs->GetXaxis()->GetXmax()-hs->GetXaxis()->GetXmin())*xR*factor;
  float yL = hs->GetMaximum()*0.35;

  if(log)
  	yL = hs->GetMaximum()*0.35;

  float offsetF=yL-0.1*hs->GetMaximum();
  float offsetFF=yL-0.2*hs->GetMaximum();

  if(log) {
    offsetF=yL/2.;
    offsetFF=yL/5.;
  }
  
  TLatex latex;
  latex.SetNDC();
  if(doRatio)
  	latex.SetTextSize(0.05);
  else
  	latex.SetTextSize(0.04);
  	
  latex.SetTextAlign(11);

  latex.SetTextFont(42);
  if(chn == "mu"){
  	latex.DrawLatex(0.20,0.94,"CMS Preliminary 2012, 19.3 fb^{-1}, #sqrt{s} = 8 TeV, #mu^{#pm}");
  }
  else{
  	latex.DrawLatex(0.20,0.94,"CMS Preliminary 2012, 19.3 fb^{-1}, #sqrt{s} = 8 TeV, e^{#pm}");  
  }

 if(log)
   plotPad->SetLogy();

 // c->RedrawAxis(); 
  c->SaveAs(folder_name+"/"+name+".png");
  //c->SaveAs(folder_name+"/"+name+".pdf");
  //c->SaveAs(folder_name+"/"+name+".root");
  
  f->Close();

}



void makeDataCard(std::string var, std::string outfile, int bins, float min, float max, std::string cut, std::string lumi, std::string chn, std::string decay) {

	TFile *f = new TFile(outfile.c_str(),"Recreate");
	TFile *d;
	TFile *s;
	TFile *s2;
	TFile *s3;
	float data;
	float sig;
	float sig2;
	float sig3;
	float ttbar;
	float wjets;
	float singletop;
	float qcd;
	float vv;
	float zjets;
	
	std::string weight = "__WEIGHT__*"+lumi;
	
	if(chn == "mu"){
		d = new TFile("mu2012.root");
		data = makeHistogram("data",d,f,var,cut,bins,min,max);
		weight = "__WEIGHT__*weight_MuonEff_singleLepCalc*"+lumi;
		d->Close();
	}
	else if(chn == "ele"){
		d = new TFile("ele2012.root");
		data = makeHistogram("data",d,f,var,cut,bins,min,max);
		weight = "__WEIGHT__*weight_ElectronEff_53x_singleLepCalc*"+lumi;
		d->Close();
		TFile *q = new TFile("QCDEM.root");
		qcd = makeHistogram("QCD",q,f,var,"("+cut+")*"+weight,bins,min,max);
		q->Close();
	}
	else{
		std::cout << "Undefined Channel!! Bad things are about to happen" << std::endl;
	}
	
	if(decay == "TH"){
		s = new TFile("TpJTH750.root");
		sig = makeHistogram("TH_750",s,f,var,"("+cut+")*"+weight,bins,min,max);
		s->Close();
	}
	else if(decay == "TZ"){
		s = new TFile("TpTZ750.root");
		sig = makeHistogram("TZ_750",s,f,var,"("+cut+")*"+weight,bins,min,max);
		s->Close();
	}
	else if(decay == "BW"){
		s = new TFile("TpBW750.root");
		sig = makeHistogram("BW_750",s,f,var,"("+cut+")*"+weight,bins,min,max);
		s->Close();
	}
	else if(decay =="TH_TZ"){
		s = new TFile("TpJTH750.root");
		sig = makeHistogram("TH_750",s,f,var,"("+cut+")*"+weight,bins,min,max);
		s->Close();
		s2 = new TFile("TpTZ750.root");
		sig2 = makeHistogram("TZ_750",s2,f,var,"("+cut+")*"+weight,bins,min,max);
		s2->Close();
	}  
	else if(decay == "ALL"){
		s = new TFile("TpJTH750.root");
		sig = makeHistogram("TH_750",s,f,var,"("+cut+")*"+weight,bins,min,max);
		s->Close();
		s2 = new TFile("TpTZ750.root");
		sig2 = makeHistogram("TZ_750",s2,f,var,"("+cut+")*"+weight,bins,min,max);
		s2->Close();
		s3 = new TFile("TpBW750.root");
		sig3 = makeHistogram("BW_750",s3,f,var,"("+cut+")*"+weight,bins,min,max);
		s3->Close();
	}
	else{
		std::cout << "Signal decay is undefined, what stupid thing have you done" << std::endl;
	}
	TFile *w = new TFile("WJets.root");
	wjets = makeHistogram("wjets",w,f,var,"("+cut+")*"+weight,bins,min,max);
	TFile *tt = new TFile("TT.root");
	ttbar = makeHistogram("ttbar",tt,f,var,"("+cut+")*"+weight,bins,min,max);
	TFile *t = new TFile("STOP.root");
	singletop = makeHistogram("singletop",t,f,var,"("+cut+")*"+weight,bins,min,max);
	TFile *v = new TFile("VV.root");
	vv = makeHistogram("VV",v,f,var,"("+cut+")*"+weight,bins,min,max);
	TFile *z = new TFile("ZJets.root");
	zjets = makeHistogram("zjets",z,f,var,"("+cut+")*"+weight,bins,min,max);
	f->Close();
	w->Close();
	tt->Close();
	t->Close();
	//q->Close();
	v->Close();
	z->Close();

}

void makeThetaCard(std::string var, std::string outfile, int bins, float min, float max, std::string cut, std::string lumi, std::string chn, std::string cat) {

	TFile *f = new TFile(outfile.c_str(),"Recreate");
	TFile *d;
	TFile *s;
	TFile *s2;
	TFile *s3;
	float data;
	float sig;
	float sig2;
	float sig3;
	float ttbar;
	float wjets;
	float singletop;
	float qcd;
	float vv;
	float zjets;

	std::string weight = "__WEIGHT__*"+lumi;
	
	if(chn == "mu"){
		d = new TFile("mu2012.root");
		data = makeHistogram(chn+"_"+cat+"__DATA",d,f,var,cut,bins,min,max);
		weight = "__WEIGHT__*weight_MuonEff_singleLepCalc*"+lumi;
		d->Close();
	}
	else if(chn == "ele"){
		d = new TFile("ele2012.root");
		data = makeHistogram(chn+"_"+cat+"__DATA",d,f,var,cut,bins,min,max);
		weight = "__WEIGHT__*weight_ElectronEff_53x_singleLepCalc*"+lumi;
		d->Close();
		TFile *q = new TFile("QCDEM.root");
		qcd = makeHistogram(chn+"_"+cat+"__qcd",q,f,var,"("+cut+")*"+weight,bins,min,max);
		q->Close();
	}
	else{
		std::cout << "Undefined Channel!! Bad things are about to happen" << std::endl;
	}

	//for loop for different masses eventually goes here:
			s = new TFile("TpTH750.root");
			sig = makeHistogram(chn+"_"+cat+"__th750",s,f,var,"("+cut+")*"+weight,bins,min,max);
			s->Close();
// 			s2 = new TFile("TpTZ750.root");
// 			sig2 = makeHistogram(chn+"_"+cat+"__tz750",s2,f,var,"("+cut+")*"+weight,bins,min,max);
// 			s2->Close();
// 			s3 = new TFile("TpBW750.root");
// 			sig3 = makeHistogram(chn+"_"+cat+"__bw750",s3,f,var,"("+cut+")*"+weight,bins,min,max);
// 			s3->Close();


	

	TFile *e = new TFile("EWK.root");
	wjets = makeHistogram(chn+"_"+cat+"__ewk",e,f,var,"("+cut+")*"+weight,bins,min,max);
	TFile *tt = new TFile("TT.root");
	ttbar = makeHistogram(chn+"_"+cat+"__ttbar",tt,f,var,"("+cut+")*"+weight,bins,min,max);
	TFile *t = new TFile("STOP.root");
	singletop = makeHistogram(chn+"_"+cat+"__stop",t,f,var,"("+cut+")*"+weight,bins,min,max);
	f->Close();
	e->Close();
	tt->Close();
	t->Close();

	
}


float makeHistogram(std::string name, TFile* fIn, TFile* fOut, std::string var, std::string cut, int bins, float min, float max, float scaleFactor = 1.) {

	 TTree* tree = fIn->Get("ljmet");
	 
     TH1F *h = new TH1F(name.c_str(),name.c_str(),bins,min,max);
	 h->Sumw2();
     tree->Draw((var+">>"+name).c_str(),cut.c_str());

     h->Scale(scaleFactor);
     
     fOut->cd();

     Double_t error=0.0;
     float yield = h->IntegralAndError(1,h->GetNbinsX(),error,"");
     if(yield == 0){
     	h->SetBinContent(1,0.00001);
     }
     h->Write(h->GetName(),TObject::kOverwrite);
     //std::cout << "Yield for " << h->GetName() << " = " << yield << " +/- " << error << std::endl;

     return yield;
     
}

void applyStyle(TH1F* h, Color_t fill, Color_t line,int fillStyle)
{
  h->SetFillColor(fill);
  h->SetLineColor(line);
  h->SetLineWidth(2);
  h->SetFillStyle(fillStyle);
}


void applySignalStyle(TH1F* h)
{
  h->SetFillStyle(0);
  h->SetLineWidth(3);
  h->SetLineColor(kBlue+3);
  h->SetLineStyle(11);
}

void applySignalStyle2(TH1F* h)
{
  h->SetFillStyle(0);
  h->SetLineWidth(3);
  h->SetLineColor(kAzure+1);
  h->SetLineStyle(11);
}

void applySignalStyle3(TH1F* h)
{
  h->SetFillStyle(0);
  h->SetLineWidth(3);
  h->SetLineColor(kGreen+2);
  h->SetLineStyle(11);
}

void applyDATAStyle(TH1F* h)
{
  h->SetMarkerStyle(20.);
  h->SetMarkerSize (1.3);
  h->SetLineWidth  ( 3.);

}

void convertToDNDM(TH1F* histo) {
  for(int i=1;i<=histo->GetNbinsX();++i) {
    histo->SetBinContent(i,histo->GetBinContent(i)/histo->GetXaxis()->GetBinWidth(i));
    histo->SetBinError(i,histo->GetBinError(i)/histo->GetXaxis()->GetBinWidth(i));
  }
}



void scaleHistogram(TFile* fOut, std::string histo, float scaleFactor){
    TH1F * h =(TH1F*) fOut->Get((histo).c_str());
    h->Scale(scaleFactor);
    h->Write(h->GetName(),TObject::kOverwrite);
}

// 
// 
// void mergeHistogram(std::string folder, std::string histo1, std::string histo2, std::string newName)
//   {
//     TH1F * h1 =(TH1F*) fout_->Get((folder+"/"+histo1).c_str());
//     TH1F * h2 =(TH1F*) fout_->Get((folder+"/"+histo2).c_str());
//   	TH1F *hNew =(TH1F*) h1->Clone(TString(newName));
//     hNew->Add(h2,1.);
// 
//     for(int i=1;i<h1->GetNbinsX();++i){
//       if(h1->GetBinContent(i)<0){
// 		h1->SetBinContent(i,0.00001);
// 		h1->SetBinError(i,1.0);
// 	  }
// 	}
// 
//     fout_->cd(folder.c_str());
//     hNew->Write(TString(newName),TObject::kOverwrite);
// }
//  
// 
// void subtractHistogram(std::string folder, std::string histo1, std::string histo2)
//   {
//     TH1F * h1 =(TH1F*) fout_->Get((folder+"/"+histo1).c_str());
//     TH1F * h2 =(TH1F*) fout_->Get((folder+"/"+histo2).c_str());
//     h1->Add(h2,-1.);
// 
//     for(int i=1;i<h1->GetNbinsX();++i){
//       if(h1->GetBinContent(i)<0){
// 		h1->SetBinContent(i,0.00001);
// 		h1->SetBinError(i,1.0);
// 	  }
// 	}
// 
//     fout_->cd(folder.c_str());
//     h1->Write(h1->GetName(),TObject::kOverwrite);
// }
//   
// void addHistogram(std::string folder, std::string histo1, std::string histo2)
//   {
//     TH1F * h1 =(TH1F*) fout_->Get((folder+"/"+histo1).c_str());
//     TH1F * h2 =(TH1F*) fout_->Get((folder+"/"+histo2).c_str());
//     h1->Add(h2,1.);
// 
//     fout_->cd(folder.c_str());
//     h1->Write(h1->GetName(),TObject::kOverwrite);
// }


setStyle()
{
  TStyle *tdrStyle = new TStyle("tdrStyle", "Style for P-TDR");

  // Canvas
  tdrStyle->SetCanvasColor     (0);
  tdrStyle->SetCanvasBorderSize(10);
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasDefH      (700);
  tdrStyle->SetCanvasDefW      (700);
  tdrStyle->SetCanvasDefX      (100);
  tdrStyle->SetCanvasDefY      (100);

  // color palette for 2D temperature plots
  tdrStyle->SetPalette(1,0);
  
  // Pads
  tdrStyle->SetPadColor       (0);
  tdrStyle->SetPadBorderSize  (10);
  tdrStyle->SetPadBorderMode  (0);
  tdrStyle->SetPadBottomMargin(0.15);
  tdrStyle->SetPadTopMargin   (0.05);
  tdrStyle->SetPadLeftMargin  (0.18);
  tdrStyle->SetPadRightMargin (0.07);
  tdrStyle->SetPadGridX       (0);
  tdrStyle->SetPadGridY       (0);
  tdrStyle->SetPadTickX       (1);
  tdrStyle->SetPadTickY       (1);

  // Frames
  tdrStyle->SetLineWidth(3);
  tdrStyle->SetFrameFillStyle ( 0);
  tdrStyle->SetFrameFillColor ( 0);
  tdrStyle->SetFrameLineColor ( 1);
  tdrStyle->SetFrameLineStyle ( 0);
  tdrStyle->SetFrameLineWidth ( 2);
  tdrStyle->SetFrameBorderSize(10);
  tdrStyle->SetFrameBorderMode( 0);

  // Histograms
  tdrStyle->SetHistFillColor(2);
  tdrStyle->SetHistFillStyle(0);
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(3);
  tdrStyle->SetNdivisions(505);

  // Functions
  tdrStyle->SetFuncColor(1);
  tdrStyle->SetFuncStyle(0);
  tdrStyle->SetFuncWidth(2);

  // Various
  tdrStyle->SetMarkerStyle(20);
  tdrStyle->SetMarkerColor(kBlack);
  tdrStyle->SetMarkerSize (1.4);

  tdrStyle->SetTitleBorderSize(0);
  tdrStyle->SetTitleFillColor (0);
  tdrStyle->SetTitleX         (0.2);

  tdrStyle->SetTitleSize  (0.055,"X");
  tdrStyle->SetTitleOffset(1.200,"X");
  tdrStyle->SetLabelOffset(0.005,"X");
  tdrStyle->SetLabelSize  (0.050,"X");
  tdrStyle->SetLabelFont  (42   ,"X");

  tdrStyle->SetStripDecimals(kFALSE);

  tdrStyle->SetTitleSize  (0.055,"Y");
  tdrStyle->SetTitleOffset(1.600,"Y");
  tdrStyle->SetLabelOffset(0.010,"Y");
  tdrStyle->SetLabelSize  (0.050,"Y");
  tdrStyle->SetLabelFont  (42   ,"Y");

  tdrStyle->SetTextSize   (0.055);
  tdrStyle->SetTextFont   (42);

  tdrStyle->SetStatFont   (42);
  tdrStyle->SetTitleFont  (42);
  tdrStyle->SetTitleFont  (42,"X");
  tdrStyle->SetTitleFont  (42,"Y");

  tdrStyle->SetOptStat    (0);
  tdrStyle->SetLineStyleString(11,"20 10");


  tdrStyle->cd();
}
