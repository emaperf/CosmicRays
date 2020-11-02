void TimeCalibration() {

	TGraphErrors *g=new TGraphErrors("DownTimeCal.dat"); //nome file
	//g->SetName("Down");

	g->SetMarkerColor(4);
	g->SetMarkerStyle(20);
	g->SetTitle("Time calibration-detector down");
	g->GetXaxis()->SetTitle("Delay [ns]");
  	g->GetXaxis()->SetTitleSize(0.04);
  	g->GetXaxis()->CenterTitle();
  	g->GetYaxis()->SetTitle("#Delta_{channel} [ch]");
  	g->GetYaxis()->SetTitleSize(0.035);
  	g->GetYaxis()->CenterTitle();

	TCanvas *c1 = new TCanvas("c1");

	g->Draw();

	TF1 *f1=new TF1("f1", "[0]*x+[1]", 16800, 24400);

	f1->SetParameters(178,16000);
	f1->SetParNames("m","q");
	
	g->Fit(f1);
	gStyle->SetOptFit(111);

	
	double chi2 =f1->GetChisquare();
	cout<<"chi2= "<<chi2<<endl;
	
 	}
