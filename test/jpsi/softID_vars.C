{
  //gStyle->SetTitleSize(0.5,"t"); // put the title inside the histogram! 
  //gStyle->SetTitleSize(0.5); // not working 
  //TGaxis::SetMoreLogLabels() ;

  TString scenario[4] ;
  scenario[0] = "data2015" ;
  scenario[1] = "mc2015" ;
  scenario[2] = "mc2015_Mu8" ;
  scenario[3] = "mc2012" ;
  const Int_t nScenarios = sizeof(scenario)/sizeof(scenario[0]);

  TFile *file[nScenarios] = {0} ;
  file[0] = TFile::Open("/afs/cern.ch/user/m/msharma/public/tnpJPsi_Data_246908-251883_JSON_MuonPhys_v2.root") ;
  file[1] = TFile::Open("/afs/cern.ch/work/l/lecriste/TnP/recipe_740/CMSSW_7_4_0/src/MuonAnalysis/TagAndProbe/test/jpsi/tnpJPsi_MC_total.root") ;
  file[2] = TFile::Open("/afs/cern.ch/work/l/lecriste/TnP/recipe_740/CMSSW_7_4_0/src/MuonAnalysis/TagAndProbe/test/jpsi/crab/tnpJPsi_officialBPHMC.root") ;
  file[3] = TFile::Open("/afs/cern.ch/work/l/lecriste/TnP/Ilse/CMSSW_5_3_22/test/tnpJPsi_MC53X.root") ;

  TString path[nScenarios] ;
  path[0] = "Mu7p5_Track2" ; //{"Mu7p5_Track2","Mu7p5_Track3p5","Mu7p5_Track7"} ;
  path[1] = "Mu7p5_Track2" ; //{"Mu7p5_Track2","Mu7p5_Track3p5","Mu7p5_Track7"} ;
  path[2] = "Mu8" ;
  path[3] = "Mu5_Track2" ; //{"Mu5_Track2","Mu5_Track7"} ;

  TString baseSelection = "pair_drM1>0.5 && pair_probeMultiplicity==1" ;
  baseSelection.Append( " && pt>6 && pt<11" ) ; // for plateau study
  //
  TString selection[nScenarios] ;
  
  TString prefix = "./" ;
  prefix = "/afs/cern.ch/work/l/lecriste/www/TnP/" ;
  TString uploadFile = "index.php" ;
  
  TString dir[nScenarios] ;
  dir[0] = prefix+"plots/data/246908-251883_JSON_MuonPhys_v2/tpTree/Soft2012/pt_abseta/"+path[0]+"_Jpsi/"+"ID_vars/maxPtCut/" ;
  dir[1] = prefix+"plots/mc/tpTree/Soft2012/pt_abseta/"+path[1]+"_Jpsi/"+"ID_vars/maxPtCut/" ;
  dir[2] = prefix+"plots/mc/"+path[2]+"/tpTree/Soft2012/pt_abseta/"+path[2]+"/"+"ID_vars/maxPtCut/" ;
  dir[3] = prefix+"plots/mc/mc2012/tpTree/newSoft2012/pt_abseta/"+path[3]+"/"+"ID_vars/maxPtCut/" ;
  
  TString var[] = {"l2pt"};
  //TString var[] = {"l2pt","pt","eta","tkTrackerLay","tkPixelLay","dzPV","dB","Track_HP","TMOST","TM","TMA","TMOSL","numberOfMatchedStations","numberOfMatches","segmentCompatibility","tkChi2"};
  TString binsVar[] = {"(100,0,50)"} ;
  //TString binsVar[] = {"(100,0,50)","(100,0,50)","(96,-2.4,2.4)","(19,-0.5,18.5)","(6,-0.5,5.5)","(90,-45,45)","(160,0,2)","(2,-0.5,1.5)","(2,-0.5,1.5)","(2,-0.5,1.5)","(2,-0.5,1.5)","(2,-0.5,1.5)","(7,-1.5,5.5)","(10,-1.5,8.5)","(100,0,1)","(90,0,30)"} ;
  const Int_t nVars = sizeof(var)/sizeof(var[0]);

  TH1F *hVar_sel[nScenarios][nVars] ;
  
  Float_t etaBin[] = {0.0, 0.9, 1.2, 2.1, 2.4} ;
  Int_t nBinsEta = sizeof(etaBin)/sizeof(etaBin[0]);
  vector<TString> etaBinLabel (nBinsEta-1,"etaBinLabel not set!");

  for (Int_t iEtaBin = 0; iEtaBin < nBinsEta-1; ++iEtaBin) {
    TString label = TString::Format("%.3gto%.3g",etaBin[iEtaBin],etaBin[iEtaBin+1]) ;
    label.ReplaceAll(".","p") ;
    //ptBinLabel.push_back( label ) ;
    etaBinLabel[iEtaBin] = label  ;
  }

  vector< vector< vector<TH1F*> > > etaBinHist (nScenarios);
  etaBinHist.resize(nScenarios) ;

  for (Int_t iScenario = 0; iScenario < nScenarios; ++iScenario) {
    etaBinHist[iScenario].resize( nVars ) ;

    TTree *fitter_tree = (TTree*)file[iScenario]->Get("tpTree/fitter_tree");
    if (iScenario != 2)
      selection[iScenario] = baseSelection+" && "+"tag_"+path[iScenario]+"_Jpsi_MU && "+path[iScenario]+"_Jpsi_TK" ;
    else 
      selection[iScenario] = baseSelection+" && "+"tag_"+path[iScenario] ;
    
    gSystem->mkdir(dir[iScenario], false);
    if ( prefix.EqualTo("/afs/cern.ch/work/l/lecriste/www/TnP/") )
      gSystem->CopyFile(prefix+uploadFile, dir[iScenario]+uploadFile, true);
    
    for (Int_t iVar = 0; iVar < nVars; ++iVar) {
      TString hName = var[iVar]+"_"+scenario[iScenario] ;
      fitter_tree->Draw(var[iVar]+">>"+hName+binsVar[iVar], selection[iScenario]) ;
      hVar_sel[iScenario][iVar] = (TH1F*)gDirectory->Get( hName );
      hVar_sel[iScenario][iVar]->Draw() ; hVar_sel[iScenario][iVar]->Draw("text45 same") ;
      hVar_sel[iScenario][iVar]->SetMinimum( 0.1 ) ;
      if ( var[iVar].EqualTo("tkTrackerLay") )
	gPad->SetLogy(0) ;
      else
	gPad->SetLogy(1) ;
      
      hVar_sel[iScenario][iVar]->SetLineColor( iScenario+1 ) ;
      gPad->SaveAs(dir[iScenario]+(hVar_sel[iScenario][iVar]->GetName())+"_etaIntegrated.png") ;


      // eta bins
      for (Int_t iEtaBin = 0; iEtaBin < nBinsEta-1; ++iEtaBin) {
	etaBinHist[iScenario][iVar].resize(nBinsEta-1) ;

	TString hName_eta = hName ;
	hName_eta.Append( "__eta_"+etaBinLabel[iEtaBin] ) ;
	TString cut = TString::Format("fabs(eta) > %.3g  &&  fabs(eta) < %.3g",etaBin[iEtaBin],etaBin[iEtaBin+1]) ;
	fitter_tree->Draw(var[iVar]+">>"+hName_eta+binsVar[iVar], selection[iScenario]+" && "+cut) ;
	etaBinHist[iScenario][iVar][iEtaBin] = (TH1F*)gDirectory->Get( hName_eta ) ;
	etaBinHist[iScenario][iVar][iEtaBin]->Draw() ; etaBinHist[iScenario][iVar][iEtaBin]->Draw("text45 same") ;
	etaBinHist[iScenario][iVar][iEtaBin]->SetMinimum( 0.1 ) ;
	if ( var[iVar].EqualTo("tkTrackerLay") )
	  gPad->SetLogy(0) ;
	else
	  gPad->SetLogy(1) ;
      
	etaBinHist[iScenario][iVar][iEtaBin]->SetLineColor( iScenario+1 ) ;
	gPad->SaveAs(dir[iScenario]+(etaBinHist[iScenario][iVar][iEtaBin]->GetName())+".png") ;
      }

    }
    
  }


  // overlay

  Bool_t isNormalized = kFALSE ;

  for (Int_t iScenario = 0; iScenario < nScenarios; ++iScenario) {
    if (iScenario == 1) {
      isNormalized = kTRUE ; // normalized in iScenario = 0 loop
      continue ;
    }
    for (Int_t iVar = 0; iVar < nVars; ++iVar) {
      for (Int_t iEtaBin = 0; iEtaBin < nBinsEta-1; ++iEtaBin) {

	TString dirVS = dir[1]+"VS_"+scenario[iScenario]+"/" ;
	gSystem->mkdir(dirVS, false);
	if ( prefix.EqualTo("/afs/cern.ch/work/l/lecriste/www/TnP/") )
	  gSystem->CopyFile(prefix+uploadFile, dirVS+uploadFile, true);

	if ( etaBinHist[1][iVar][iEtaBin]->GetEntries() && !isNormalized )
	  etaBinHist[1][iVar][iEtaBin]->Scale( 1. / etaBinHist[1][iVar][iEtaBin]->GetEntries() ) ;
	if ( etaBinHist[iScenario][iVar][iEtaBin]->GetEntries() )
	  etaBinHist[iScenario][iVar][iEtaBin]->Scale( 1. / etaBinHist[iScenario][iVar][iEtaBin]->GetEntries() ) ;

	if (etaBinHist[1][iVar][iEtaBin]->GetMaximum() > etaBinHist[iScenario][iVar][iEtaBin]->GetMaximum()) {
	  etaBinHist[1][iVar][iEtaBin]->Draw() ;
	  etaBinHist[iScenario][iVar][iEtaBin]->Draw("same") ;
	} else {
	  etaBinHist[iScenario][iVar][iEtaBin]->Draw() ;
	  etaBinHist[1][iVar][iEtaBin]->Draw("same") ;
	}
	//
	if ( var[iVar].EqualTo("tkTrackerLay") )
	  gPad->SetLogy(0) ;
	else
	  gPad->SetLogy(1) ;

	gPad->SaveAs(dirVS+(etaBinHist[1][iVar][iEtaBin]->GetName())+".png") ;
	
      }
    }
  }

  /*
  Float_t ptBin[] = {2.0, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.5, 5.0, 6.0, 8.0, 10.0, 15.0, 20.0, 30.0, 40.0} ;
  Int_t nBinsPt = sizeof(ptBin)/sizeof(ptBin[0]);

  vector<TString> ptBinLabel (nBinsPt-1,"ptBinLabel not set!");
  vector<Float_t> ptBinCenter (nBinsPt-1,-1);
  vector<Float_t> ptBinEvts_sel (nBinsPt-1,-1);

  Int_t nPath = sizeof(path)/sizeof(path[0]);
  //vector< vector<Float_t> > ptBinEvts_path (nPath, (nBinsPt-1,-1) );
  vector< vector<Float_t> > ptBinEvts_path (nPath);
  //for (Int_t iPath = 0; iPath < nPath; ++iPath)
    //ptBinEvts_path[iPath](nBinsPt-1,-1) ;

  ptBinEvts_path.resize(nPath);

  for (Int_t iPtBin = 0; iPtBin < nBinsPt-1; ++iPtBin) {
    TString label = TString::Format("%.3gto%.3g",ptBin[iPtBin],ptBin[iPtBin+1]) ;
    label.ReplaceAll(".","p") ;
    //ptBinLabel.push_back( label ) ;
    ptBinLabel[iPtBin] = label  ;

    //ptBinCenter.push_back( (ptBin[iPtBin+1]+ptBin[iPtBin])/2 ) ;
    ptBinCenter[iPtBin] = (ptBin[iPtBin]+ptBin[iPtBin+1])/2  ;

    hName = "hMass_sel_pt" ; hName.Append( label ) ;
    TString cut = TString::Format("pt > %.3g  &&  pt < %.3g",ptBin[iPtBin],ptBin[iPtBin+1]) ;
    fitter_tree->Draw("mass>>"+hName, baseSelection+" && "+cut) ;
    TH1F *hMass_sel_ptBin = (TH1F*)gDirectory->Get( hName );
    //ptBinEvts_sel.push_back( hMass_sel_ptBin->GetEntries() ) ;
    ptBinEvts_sel[iPtBin] = hMass_sel_ptBin->GetEntries() ;
    //hMass_sel_ptBin->SaveAs(dir+hName+".png") ;

    for (Int_t iPath = 0; iPath < nPath; ++iPath) {
      hName.Append( "_"+path[iPath] ) ;
      TString cutPath = "tag_"+path[iPath]+"_Jpsi_MU && "+path[iPath]+"_Jpsi_TK" ;
      fitter_tree->Draw("mass>>"+hName, baseSelection+" && "+cut+" && "+cutPath) ;
      TH1F *hMass_sel_ptBin_path = (TH1F*)gDirectory->Get( hName );
      //ptBinEvts_path[iPath][iPtBin] = hMass_sel_ptBin_path->GetEntries() ;
      ptBinEvts_path[iPath].push_back( hMass_sel_ptBin_path->GetEntries() ) ;
    }
  }

  TGraph* pT_yields = new TGraph( nBinsPt-1, &ptBinCenter[0], &ptBinEvts_sel[0]);
  pT_yields->SetNameTitle("pT_yields","selection yields;muon p_{T} [GeV]") ;
  pT_yields->Draw("AL*");
  gPad->SetGrid() ; 
  gPad->SaveAs(dir+pT_yields->GetName()+".png") ;

  vector< TGraph* > pT_yields_path (nPath,0);
  for (Int_t iPath = 0; iPath < nPath; ++iPath) {
    pT_yields_path[iPath] = new TGraph( nBinsPt-1, &ptBinCenter[0], &ptBinEvts_path[iPath][0]);
    pT_yields_path[iPath]->SetNameTitle("pT_yields_"+path[iPath],path[iPath]+" yields;muon p_{T} [GeV]") ;
    pT_yields_path[iPath]->Draw("AL*");
    gPad->SetGrid() ;
    gPad->SaveAs(dir+pT_yields_path[iPath]->GetName()+".png") ;
  }
  */

}
