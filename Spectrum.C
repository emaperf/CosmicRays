void Spectrum(){

struct slimport_data_t {
	ULong64_t	timetag; //time stamp
	UInt_t		baseline;
	UShort_t	qshort; //integration with shorter time
	UShort_t	qlong; //integration with longer time
	UShort_t	pur;
	UShort_t	samples[4096];
};

	// variables
	slimport_data_t indata;
	TFile *infile = new TFile("downd5.root");
	TTree *intree = (TTree*)infile->Get("acq_tree_0");
	short chan=2;
	TBranch *inbranch = intree->GetBranch(Form("acq_ch%d", chan));
	inbranch->SetAddress(&indata.timetag);
	
	
	
	TH1F *h_spectrum = new TH1F("h_spectrum","Total spectrum",25000,0,50000);
	// histogram filling
	for (int i=0; i<inbranch->GetEntries(); i++) {
		inbranch->GetEntry(i);
		h_spectrum->Fill(indata.qlong);
	}
	
	double mean=h_spectrum->GetMean();
	double sigma=h_spectrum->GetStdDev();
	double MinX=mean-3.*sigma;
	double MaxX=mean+3.*sigma;

	int binmax=h_spectrum->GetMaximumBin();
	double x=h_spectrum->GetXaxis()->GetBinCenter(binmax);
	cout<<"x = "<<x<<endl;

	
	//TF1 *fit= new TF1 ("fit", "[0]*exp(-0.5*((x-[1])/[2])**2)", x-10, x+10);
	//fit->SetParName(0, "Constant");
	//fit->SetParName(1, "Centroid");
	//fit->SetParName(2, "Sigma");
	
	//fit->SetParameter(0, 10.);
	//fit->SetParameter(1, x);
	//fit->SetParameter(2,1.);
	
	
	TCanvas *c1=new TCanvas ("c1", "c1", 400,300);

	gStyle->SetOptStat("emr");
	
	h_spectrum->GetXaxis()->SetRangeUser(MinX, MaxX);
	h_spectrum->Fit("gaus","R","",x-30,x+30);
	
	h_spectrum->Draw();
	

}

	
