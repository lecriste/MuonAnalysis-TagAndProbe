{
  TFile *outputFile = new TFile("./TnP_yield_Charmonium_PromptReco_50ns_first47ipb.root","RECREATE") ;
  //TFile *inputFile = TFile::Open("/afs/cern.ch/user/m/msharma/public/tnpJPsi_Data_246908-251883_JSON_MuonPhys_v2.root") ;
  TFile *inputFile = TFile::Open("/afs/cern.ch/work/l/lecriste/TnP/recipe_740/CMSSW_7_4_0/src/MuonAnalysis/TagAndProbe/test/jpsi/tnpJPsi_Charmonium_PromptReco_50ns_first47ipb.root") ;
  //
  //TFile *outputFile = new TFile("./TnP_yield_Charmonium_PromptReco_50ns.root","RECREATE") ;
  //TFile *inputFile = TFile::Open("/afs/cern.ch/work/l/lecriste/TnP/recipe_740/CMSSW_7_4_0/src/MuonAnalysis/TagAndProbe/test/jpsi/tnpJPsi_Charmonium_PromptReco_50ns.root") ;

  if (!inputFile) return ;
  TTree *fitter_tree = (TTree*)inputFile->Get("tpTree/fitter_tree");

  TString selection = "pair_drM1>0.5 && pair_probeMultiplicity==1" ;

  TString prefix = "./" ;
  prefix = "/afs/cern.ch/work/l/lecriste/www/TnP/" ;
  TString uploadFile = "index.php" ;


  TString dir = prefix+"plots/data/246908-251883_JSON_MuonPhys_v2/tpTree/Soft2012/pt_abseta/yields/" ;
  //TString dir = prefix+"plots/data/246908-255031_JSON_MuonPhys_v2/tpTree/Soft2012/pt_abseta/yields/" ;

  gSystem->mkdir(dir, false);
  if ( prefix.EqualTo("/afs/cern.ch/work/l/lecriste/www/TnP/") )
    gSystem->CopyFile(prefix+uploadFile, dir+uploadFile, true);

  TString hName = "hMass_total" ;
  fitter_tree->Draw("mass>>"+hName) ;
  TH1F *hMass = (TH1F*)gDirectory->Get( hName );
  Int_t total_tree_events = hMass->GetEntries() ;
  cout <<"hMass->GetEntries() = " <<total_tree_events <<endl ;
  //hMass->SaveAs(dir+hName+".png") ;

  hName = "hMass_sel" ;
  fitter_tree->Draw("mass>>"+hName, selection) ;
  TH1F *hMass_sel = (TH1F*)gDirectory->Get( hName );
  Int_t eventsSel = hMass_sel->GetEntries() ;
  cout <<"hMass_sel->GetEntries() = " <<eventsSel <<endl ;
  //hMass_sel->SaveAs(dir+hName+".png") ;

  Float_t absetaBin[] = {0.0, 0.9, 1.2, 2.1, 2.4};
  Float_t ptBin[] = {2.0, 2.5, 3.0, 3.5, 4.0, 4.75, 5.5, 7.5, 10.0, 20.0, 40.0} ;
  //Float_t ptBin[] = {2.0, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.5, 5.0, 6.0, 8.0, 10.0, 15.0, 20.0, 30.0, 40.0} ;

  Int_t nBinsAbseta = sizeof(absetaBin)/sizeof(absetaBin[0]);
  Int_t nBinsPt = sizeof(ptBin)/sizeof(ptBin[0]);

  vector<TString> ptBinLabel (nBinsPt-1,"ptBinLabel not set!");
  vector<Float_t> ptBinCenter (nBinsPt-1,-1);
  vector<Float_t> ptBinEvts_sel (nBinsPt-1,-1);

  //TString path[] = {"Mu7p5_Track2","Mu7p5_Track3p5","Mu7p5_Track7"} ;
  TString path[] = {"Mu7p5_Track2","Mu7p5_Track7"} ;
  Int_t nPath = sizeof(path)/sizeof(path[0]);
  vector< vector<Float_t> > ptBinEvts_path (nPath);

  ptBinEvts_path.resize(nPath);

  for (Int_t iAbsetaBin = 0; iAbsetaBin < nBinsAbseta-1; ++iAbsetaBin) {
    TString labelAbseta = TString::Format("%.2gto%.2g",absetaBin[iAbsetaBin],absetaBin[iAbsetaBin+1]) ;
    labelAbseta.ReplaceAll(".","p") ;

    for (Int_t iPtBin = 0; iPtBin < nBinsPt-1; ++iPtBin) {
      TString labelPt = TString::Format("%.3gto%.3g",ptBin[iPtBin],ptBin[iPtBin+1]) ;
      labelPt.ReplaceAll(".","p") ;
      ptBinLabel[iPtBin] = labelPt  ;
      
      ptBinCenter[iPtBin] = (ptBin[iPtBin]+ptBin[iPtBin+1])/2  ;
      
      hName = "hMass_sel_pt" ; hName.Append( labelPt ) ;
      hName.Append( "__abseta" ) ; hName.Append( labelAbseta ) ;
      TString cutPt = TString::Format("pt > %.3g  &&  pt < %.3g",ptBin[iPtBin],ptBin[iPtBin+1]) ;
      TString cutAbseta = TString::Format("abseta > %.2g  &&  abseta < %.2g",absetaBin[iAbsetaBin],absetaBin[iAbsetaBin+1]) ;
      fitter_tree->Draw("mass>>"+hName, selection+" && "+cutPt+" && "+cutAbseta) ;
      TH1F *hMass_sel_ptBin_absetaBin = (TH1F*)gDirectory->Get( hName );
      ptBinEvts_sel[iPtBin] = hMass_sel_ptBin_absetaBin->GetEntries() ;
      //hMass_sel_ptBin->SaveAs(dir+hName+".png") ;
      
      for (Int_t iPath = 0; iPath < nPath; ++iPath) {
	hName.Append( "_"+path[iPath] ) ;
	TString cutPath = "tag_"+path[iPath]+"_Jpsi_MU && "+path[iPath]+"_Jpsi_TK" ;
	fitter_tree->Draw("mass>>"+hName, selection+" && "+cutPt+" && "+cutAbseta+" && "+cutPath) ;
	TH1F *hMass_sel_ptBin_absetaBin_path = (TH1F*)gDirectory->Get( hName );
	//ptBinEvts_path[iPath].push_back( hMass_sel_ptBin_absetaBin_path->GetEntries() ) ;
	ptBinEvts_path[iPath].resize(nBinsPt-1);
	ptBinEvts_path[iPath][iPtBin] = hMass_sel_ptBin_absetaBin_path->GetEntries() ;
      }
    }

    outputFile->cd() ;
    
    TGraph* pT_yields = new TGraph( nBinsPt-1, &ptBinCenter[0], &ptBinEvts_sel[0]);
    pT_yields->SetNameTitle("pT_yields__abseta"+labelAbseta,"selection yields for |#eta| from"+labelAbseta+";muon p_{T} [GeV]") ;
    pT_yields->Draw("AL*");
    pT_yields->GetXaxis()->SetMoreLogLabels();
    gPad->SetLogx() ;
    gPad->SetGrid() ; 
    gPad->SaveAs(dir+pT_yields->GetName()+".png") ;
    pT_yields->Write() ;
    
    vector< TGraph* > pT_yields_path (nPath,0);
    for (Int_t iPath = 0; iPath < nPath; ++iPath) {
      pT_yields_path[iPath] = new TGraph( nBinsPt-1, &ptBinCenter[0], &ptBinEvts_path[iPath][0]);
      pT_yields_path[iPath]->SetNameTitle("pT_yields_"+path[iPath]+"__abseta"+labelAbseta,path[iPath]+" yields for |#eta| from"+labelAbseta+";muon p_{T} [GeV]") ;
      pT_yields_path[iPath]->Draw("AL*");
      pT_yields_path[iPath]->GetXaxis()->SetMoreLogLabels();
      gPad->SetLogx() ;
      gPad->SetGrid() ;
      gPad->SaveAs(dir+pT_yields_path[iPath]->GetName()+".png") ;
      pT_yields_path[iPath]->Write() ;
    }

  }

}
