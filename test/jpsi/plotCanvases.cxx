// Macro to loop on the directories and subdirectories in a file and plot all canvases
// Usage:
// root -l
// .L plotCanvases.cxx
// plotCanvases("scenrario") where scenario = mc/data
//

#include "TROOT.h"
#include "TStyle.h" 
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TString.h"
#include "TH1.h"
#include "TH2.h"
#include "TGraphAsymmErrors.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TList.h"
#include "TKey.h"
#include "TDirectory.h"
#include <iostream>



void plotCanvases(TString scenario) {
  /*
  gROOT->SetStyle("Plain");
  gStyle->SetTitleFillColor(0);
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);
  //
  gStyle->SetTitleSize(0.01,"t"); // not working
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleOffset(1.25,"X") ;
  gStyle->SetTitleOffset(1.2,"Y") ;
  */
  gStyle->SetPaintTextFormat(".3f");
  TString fileName = "TnP_Muon_ID_Simple.root" ;

  TString binnedVariables = "";
  TString scenarioFile = "" ;
  if ( scenario.Contains("mc") ) {
    scenario = "mc/" ; scenarioFile = "signal_mc" ;
    fileName = "TnP_MuonID_signal_mc_newSoft2012_pt_abseta.root" ; binnedVariables = "pt_abseta";
    fileName = "TnP_MuonID_signal_mc_Soft2012_pt_abseta_noFilter.root" ; binnedVariables = "pt_abseta";
    fileName = "TnP_MuonID_signal_mc_Soft2012_pt_abseta_benchmark10k.root" ; binnedVariables = "pt_abseta";
    fileName = "TnP_MuonID_signal_mc_Soft2012_pt_abseta_fullMC.root" ; binnedVariables = "pt_abseta";
    fileName = "TnP_MuonID_signal_mc_Soft2012_pt_abseta_etaIntegrated.root" ; binnedVariables = "pt_abseta";
    //fileName = "TnP_MuonID_signal_mc_newSoft2012_noTMOST_pt_abseta0p9to1p2.root" ;
    fileName = "TnP_MuonID__signal_mc__newSoft2012_pt_abseta0p9to1p2.root" ; binnedVariables = "pt_abseta";
    fileName = "TnP_MuonID__signal_mc__Soft2012_pt_abseta_Mu8.root" ; binnedVariables = "pt_abseta";
    fileName = "TnP_MuonID__signal_mc__Soft2012_pt_abseta.root" ; binnedVariables = "pt_abseta";
    fileName = "TnP_MuonID__signal_mc__Soft2012_ptTurnOn_abseta_30M.root" ; binnedVariables = "ptTurnOn_abseta";
    fileName = "TnP_MuonID__signal_mc__Soft2012_ptTurnOn_abseta_Mu8.root" ; binnedVariables = "ptTurnOn_abseta";
    fileName = "TnP_MuonID__signal_mc__Soft2012_vtx_30M.root" ; binnedVariables = "vtx";
    fileName = "TnP_MuonID__signal_mc__Soft2012_pt_abseta_30M.root" ; binnedVariables = "pt_abseta";
    fileName = "TnP_MuonID__signal_mc__Soft2012_pt_abseta.root" ; binnedVariables = "pt_abseta";
    //fileName = "TnP_MuonID__signal_mc__Soft2012_pt_abseta_allPairs_30M.root" ;
    //fileName = "TnP_MuonID__signal_mc__Soft2012_pt_eta_30M.root" ;
    //fileName = "TnP_MuonID__signal_mc__Soft2012_pt_abseta_notSeparated_30M.root" ; binnedVariables = "pt_abseta_notSeparated";
    fileName = "TnP_MuonID__signal_mc__Soft2012_pt_abseta.root" ; binnedVariables = "pt_abseta";
    fileName = "TnP_Vertexing__signal_mc__pt_abseta.root" ; binnedVariables = "pt_abseta";
    fileName = "TnP_MuonID__signal_mc__Soft2012_pt_abseta_seagull.root" ; binnedVariables = "pt_abseta_seagull";
    //fileName = "TnP_MuonID__signal_mc__Soft2012_pt_abseta_cowboy.root" ; binnedVariables = "pt_abseta_cowboy";
    fileName = "TnP_MuonID__signal_mc__Soft2012_pt_abseta_notSeparated.root" ; binnedVariables = "pt_abseta_notSeparated";
    // 25ns
    //fileName = "TnP_MuonID__signal_mc_25ns__Soft2012_pt_abseta_notSeparated.root" ; binnedVariables = "pt_abseta_notSeparated";
    fileName = "TnP_Vertexing__signal_mc_25ns__pt_absrapidity_notSeparated.root" ; binnedVariables = "pt_absrapidity_notSeparated";
    //
    //fileName = "TnP_MuonID__signal_mc_25ns__Loose2015_pt_abseta_notSeparated.root" ; binnedVariables = "pt_abseta_notSeparated";
    //fileName = "TnP_MuonID__signal_mc_25ns__Medium2015_pt_abseta_notSeparated.root" ; binnedVariables = "pt_abseta_notSeparated";
    //fileName = "TnP_MuonID__signal_mc_25ns__Tight2012_zIPCut_pt_abseta_notSeparated.root" ; binnedVariables = "pt_abseta_notSeparated";
    //
    //fileName = "TnP_MuonID__signal_mc_25ns__Loose2015_pt_abseta.root" ; binnedVariables = "pt_abseta";
    //fileName = "TnP_MuonID__signal_mc_25ns__Medium2015_pt_abseta.root" ; binnedVariables = "pt_abseta";
    //fileName = "TnP_MuonID__signal_mc_25ns__Tight2012_zIPCut_pt_abseta.root" ; binnedVariables = "pt_abseta";
    //
    //fileName = "TnP_MuonID__signal_mc_25ns__Loose2015_pt_abseta2p4.root" ; binnedVariables = "pt_abseta2p4";
    //fileName = "TnP_MuonID__signal_mc_25ns__Medium2015_pt_abseta2p4.root" ; binnedVariables = "pt_abseta2p4";
    //fileName = "TnP_MuonID__signal_mc_25ns__Tight2012_zIPCut_pt_abseta2p4.root" ; binnedVariables = "pt_abseta2p4";
    //
    //fileName = "TnP_MuonID__signal_mc_25ns__Loose2015_ptPlateau_eta.root" ; binnedVariables = "ptPlateau_eta";
    //fileName = "TnP_MuonID__signal_mc_25ns__Medium2015_ptPlateau_eta.root" ; binnedVariables = "ptPlateau_eta";
    //fileName = "TnP_MuonID__signal_mc_25ns__Tight2012_zIPCut_ptPlateau_eta.root" ; binnedVariables = "ptPlateau_eta";
    //
    //fileName = "TnP_MuonID__signal_mc_25ns__Loose2015_vtx.root" ; binnedVariables = "vtx";
    //fileName = "TnP_MuonID__signal_mc_25ns__Medium2015_vtx.root" ; binnedVariables = "vtx";
    //fileName = "TnP_MuonID__signal_mc_25ns__Tight2012_zIPCut_vtx.root" ; binnedVariables = "vtx";
  }
  else if ( scenario.Contains("data") ) {
    scenario = "data/" ; scenarioFile = "data" ;
    fileName = "TnP_MuonID_data_all_Soft2012_pt_abseta.root" ; binnedVariables = "pt_abseta";
    fileName = "TnP_MuonID__data_246908-255031_JSON_MuonPhys_v2__Soft2012_pt_abseta.root" ; binnedVariables = "pt_abseta";
    fileName = "TnP_MuonID__data_246908-251883_JSON_MuonPhys_v2__Soft2012_vtx.root" ; binnedVariables = "vtx";
    fileName = "TnP_MuonID__data_246908-251883_JSON_MuonPhys_v2__Soft2012_pt_abseta.root" ; binnedVariables = "pt_abseta";
    fileName = "TnP_Vertexing__data_246908-251883_JSON_MuonPhys_v2__pt_abseta.root" ; binnedVariables = "pt_abseta";
    //fileName = "TnP_MuonID__data_246908-251883_JSON_MuonPhys_v2__Soft2012_pt_abseta_allPairs.root" ; binnedVariables = "pt_abseta_allPairs";
    //fileName = "TnP_MuonID__data_246908-251883_JSON_MuonPhys_v2__Soft2012_pt_eta.root" ; binnedVariables = "pt_eta";
    //fileName = "TnP_MuonID__data_246908-251883_JSON_MuonPhys_v2__Soft2012_pt_abseta_notSeparated.root" ; binnedVariables = "pt_abseta_notSeparated";
    //fileName = "TnP_MuonID__data_246908-251883_JSON_MuonPhys_v2__Soft2012_pt_abseta_seagull.root" ; binnedVariables = "pt_abseta_seagull";
    //fileName = "TnP_MuonID__data_246908-251883_JSON_MuonPhys_v2__Soft2012_pt_abseta_cowboy.root" ; binnedVariables = "pt_abseta_cowboy";
    fileName = "TnP_MuonID__data_all__Soft2012_pt_abseta_notSeparated.root" ; binnedVariables = "pt_abseta_notSeparated";
    // 25ns
    // Soft2012
    fileName = "TnP_MuonID__data_25ns__Soft2012_pt_abseta.root" ; binnedVariables = "pt_abseta";
    //fileName = "TnP_MuonID__data_25ns__Soft2012_pt_abseta2p4.root" ; binnedVariables = "pt_abseta2p4";
    //fileName = "TnP_MuonID__data_25ns__Soft2012_ptPlateau_eta.root" ; binnedVariables = "ptPlateau_eta";
    //fileName = "TnP_MuonID__data_25ns__Soft2012_vtx.root" ; binnedVariables = "vtx";
    //fileName = "TnP_MuonID__data_all_25ns__Soft2012_pt_abseta_Mu8.root" ; binnedVariables = "pt_abseta";
    //
    //fileName = "TnP_MuonID__data_all_25ns__Loose2015_pt_abseta_notSeparated.root" ; binnedVariables = "pt_abseta_notSeparated";
    //fileName = "TnP_MuonID__data_all_25ns__Medium2015_pt_abseta_notSeparated.root" ; binnedVariables = "pt_abseta_notSeparated";
    //fileName = "TnP_MuonID__data_all_25ns__Tight2012_zIPCut_pt_abseta_notSeparated.root" ; binnedVariables = "pt_abseta_notSeparated";
    //
    //fileName = "TnP_MuonID__data_25ns__Loose2015_pt_abseta.root" ; binnedVariables = "pt_abseta";
    //fileName = "TnP_MuonID__data_25ns__Medium2015_pt_abseta.root" ; binnedVariables = "pt_abseta";
    //fileName = "TnP_MuonID__data_25ns__Tight2012_zIPCut_pt_abseta.root" ; binnedVariables = "pt_abseta";
    //
    //fileName = "TnP_MuonID__data_25ns__Loose2015_pt_abseta2p4.root" ; binnedVariables = "pt_abseta2p4";
    //fileName = "TnP_MuonID__data_25ns__Medium2015_pt_abseta2p4.root" ; binnedVariables = "pt_abseta2p4";
    //fileName = "TnP_MuonID__data_25ns__Tight2012_zIPCut_pt_abseta2p4.root" ; binnedVariables = "pt_abseta2p4";
    //
    //fileName = "TnP_MuonID__data_25ns__Loose2015_ptPlateau_eta.root" ; binnedVariables = "ptPlateau_eta";
    //fileName = "TnP_MuonID__data_25ns__Medium2015_ptPlateau_eta.root" ; binnedVariables = "ptPlateau_eta";
    //fileName = "TnP_MuonID__data_25ns__Tight2012_zIPCut_ptPlateau_eta.root" ; binnedVariables = "ptPlateau_eta";
    //
    //fileName = "TnP_MuonID__data_25ns__Loose2015_vtx.root" ; binnedVariables = "vtx";
    //fileName = "TnP_MuonID__data_25ns__Medium2015_vtx.root" ; binnedVariables = "vtx";
    //fileName = "TnP_MuonID__data_25ns__Tight2012_zIPCut_vtx.root" ; binnedVariables = "vtx";
    // Mu8
    //fileName = "TnP_MuonID__data_all_25ns__Loose2015_pt_abseta_Mu8.root" ; binnedVariables = "pt_abseta";
    //fileName = "TnP_MuonID__data_all_25ns__Medium2015_pt_abseta_Mu8.root" ; binnedVariables = "pt_abseta";
    //fileName = "TnP_MuonID__data_all_25ns__Tight2012_zIPCut_pt_abseta_Mu8.root" ; binnedVariables = "pt_abseta";
  }
  else {
    cout <<"Argument not valid!\nRun with \"plotCanvases(\"mc\") or plotCanvases(\"data\")" <<endl ;
    return ; 
  }

  TString mode = "50ns/";
  if (fileName.Contains("25ns"))
    mode = "25ns/" ;

  vector<TString> tree = {"tpTree"} ;
  //vector<TString> tree = {"tpTree", "tpTreeSta"} ;
  if (fileName.Contains("Vertexing"))
    tree = {"tpTreeOnePair"} ;

  //vector<TString> ids = {"newSoft2012"} ;
  vector<TString> ids = {"Soft2012"/*,"Dimuon10_L1L2","Dimuon16_L1L2","L3_wrt_Dimuon10_L1L2","L3_wrt_Dimuon16_L1L2","Dimuon16_Jpsi_wrt_Dimuon6_Jpsi_NoVertexing","Dimuon10_Jpsi_Barrel_wrt_Dimuon0er16_Jpsi_NoVertexing"*/} ;
  //vector<TString> ids = {"newSoft2012_noTMOST"} ;
  //vector<TString> ids = {"Loose2015", "Soft2012", "Medium2015", "Tight2012_zIPCut"} ;

  //vector<TString> triggers = {"Mu7p5_L2Mu2_Jpsi", "Mu7p5_Track2_Jpsi", "Mu7p5_Track3p5_Jpsi", "Mu7p5_Track7_Jpsi"} ;
  ////vector<TString> triggers = {"Mu7p5_Track2_Jpsi"} ;
  vector<TString> triggers = {"_Mu7p5_Track2_Jpsi"} ;
  //vector<TString> triggers = {"Mu7p5_Track2_Jpsi", "Mu7p5_Track7_Jpsi"} ;
  //vector<TString> triggers = {"Mu5_Track2"} ;
  if ( fileName.Contains("Mu8") )
    triggers = {"_Mu8"} ;
  //"L1_DoubleMu0_Eta1p6_WdEta18"
  vector<TString> trigL3 = {""} ;
  vector<TString> triggersNoVtx = {"_Dimuon6_Jpsi_NoVertexing"} ;
  vector<TString> triggersNoVtx_barrel = {"_Dimuon0er16_Jpsi_NoVertexing"} ;
  vector<TString> trigNoSoft = {""} ;

  vector< pair<TString, vector<TString>> > ids_triggers ;

  for (uint iId=0; iId<ids.size(); ++iId)
    if (!ids[iId].Contains("L3") && !ids[iId].Contains("Vertexing")) // i.e. "Soft2012","Dimuon10_L1L2","Dimuon16_L1L2"
      ids_triggers.push_back( make_pair(ids[iId],triggers) ) ;
    else if (!ids[iId].Contains("Vertexing"))
      ids_triggers.push_back( make_pair(ids[iId],trigL3) ) ;
    else if (!ids[iId].Contains("Barrel"))
      ids_triggers.push_back( make_pair(ids[iId],triggersNoVtx) ) ;
    else
      ids_triggers.push_back( make_pair(ids[iId],triggersNoVtx_barrel) ) ;

  vector<TString> notToPlot = {"distributions_canvas"} ;

  // See the directory names from the files
  //const vector<TString> folders = {
  vector<TString> folders = {
    //"Tight2012_pt_eta_fine",
    //"Tight2012_pt",
    //"Tight2012_pt_eta_fine",
    //"Tight2012_nVtx",
    //"Tight2012_nJets30",
    //"Tight2012_eta_truth",
    //"Tight2012_pt",
    //"Tight2012_pt_truth",
    //"Tight2012_pt_eta",
    //"Tight2012_pt_eta_truth"
  };
  /*
  if ( fileName.Contains("pt_abseta_notSeparated") )
    folders.push_back("pt_abseta_notSeparated") ;
  else if ( fileName.Contains("pt_abseta_allPairs") )
    folders.push_back("pt_abseta_allPairs") ;
  else if ( fileName.Contains("pt_abseta") )
    folders.push_back("pt_abseta") ;

  if ( fileName.Contains("ptTurnOn_abseta") )
    folders.push_back("ptTurnOn_abseta") ;
  if ( fileName.Contains("vtx") )
    folders.push_back("vtx") ;
  else if ( fileName.Contains("pt_eta") )
    folders.push_back("pt_eta") ;
  */
  folders.push_back( binnedVariables ) ;

  TString prefix = "./" ;
  prefix = "/afs/cern.ch/work/l/lecriste/www/TnP/" ; // https://lecriste.web.cern.ch/lecriste/TnP

  TString uploadFile = "index.php" ;
  TString dirPlace = prefix+"plots/" ;
  if ( prefix.EqualTo("/afs/cern.ch/work/l/lecriste/www/TnP/") )
    gSystem->CopyFile(prefix+uploadFile, dirPlace+uploadFile, true);

  // scenario dir
  //dirPlace = prefix+"plots/"+scenario ;
  dirPlace.Append( scenario );
  gSystem->mkdir(dirPlace, true);
  if ( prefix.EqualTo("/afs/cern.ch/work/l/lecriste/www/TnP/") )
    gSystem->CopyFile(prefix+uploadFile, dirPlace+uploadFile, true);
  
  TString test = "" ; // remember to put a slash '/' at the end if it's not ""
  //test = "mc2012/" ;
  //test = "noProbeFilter/" ;
  //test = "etaIntegrated/" ;
  if ( fileName.Contains("246908-251883_JSON_MuonPhys_v2") || fileName.Contains("data") ) {
    test = "246908-251883_JSON_MuonPhys_v2/" ;
    //test = "246908-255031_JSON_MuonPhys_v2/" ;
    if ( mode.Contains("25ns") ) {
      //test = "246908-260627_JSON_MuonPhys/" ;
      test = "246908-260627_JSON_Golden_v2/" ;
    }
  }
  if ( fileName.Contains("30M") ) test = "30M/" ;
  //if ( fileName.Contains("Mu8") ) test = "Mu8/" ;

  dirPlace.Append( test );
  gSystem->mkdir(dirPlace, true);
  if ( prefix.EqualTo("/afs/cern.ch/work/l/lecriste/www/TnP/") )
    gSystem->CopyFile(prefix+uploadFile, dirPlace+uploadFile, true);
  TString testFile = "_" ;
  //testFile = "_246908-251883_JSON_MuonPhys_v2_" ;
  //
  //fileName = "TnP_MuonID__"+scenarioFile+testFile+"_"+ids[0]+"_"+folders[0]+".root" ;
  TFile *f1 = 0 ;
  if ( (f1 = TFile::Open( fileName.Data() )) )
    cout <<"Successfully opened file " <<fileName <<endl ;
  else {
    //cout <<"Error: file " <<fileName <<" does not exist!" <<endl ;
    return ;
  }
  //

  //loop on trees
  for (uint iTree=0; iTree<tree.size(); ++iTree) {
    //dirPlace = prefix+"plots/"+scenario+test ;
    dirPlace = prefix+"plots/"+scenario+mode+test ;
    dirPlace.Append( tree[iTree]+"/" );
    cout <<"Making dir " <<dirPlace <<endl ;
    gSystem->mkdir(dirPlace, true);
    if ( prefix.EqualTo("/afs/cern.ch/work/l/lecriste/www/TnP/") )
      gSystem->CopyFile(prefix+uploadFile, dirPlace+uploadFile, true);

    //loop on ids
    //for (uint iId=0; iId<ids.size(); ++iId) {
    for (uint iId=0; iId<ids_triggers.size(); ++iId) {
      //dirPlace = prefix+"plots/"+scenario+test+tree[iTree]+"/" ;
      dirPlace = prefix+"plots/"+scenario+mode+test+tree[iTree]+"/" ;
      //dirPlace.Append( ids[iId]+"/" );
      dirPlace.Append( ids_triggers[iId].first+"/" );
      cout <<"\nMaking dir " <<dirPlace <<endl ;
      gSystem->mkdir(dirPlace, true);
      if ( prefix.EqualTo("/afs/cern.ch/work/l/lecriste/www/TnP/") )
	gSystem->CopyFile(prefix+uploadFile, dirPlace+uploadFile, true);

      //loop on directory names
      for (uint kk=0; kk<folders.size(); ++kk) {
	dirPlace.Append( folders[kk]+"/" );
	gSystem->mkdir(dirPlace, true);
	if ( prefix.EqualTo("/afs/cern.ch/work/l/lecriste/www/TnP/") )
	  gSystem->CopyFile(prefix+uploadFile, dirPlace+uploadFile, true);

	//loop on triggers
	//for (uint iTrig=0; iTrig<triggers.size(); ++iTrig) {
	for (uint iTrig=0; iTrig<ids_triggers[iId].second.size(); ++iTrig) {
	  //dirPlace.Append( triggers[iTrig]+"/" );
	  TString trig = ids_triggers[iId].second[iTrig] ;
	  dirPlace.Append( trig+"/" ); dirPlace.ReplaceAll("/_","/") ;
	  gSystem->mkdir(dirPlace, true);
	  if ( prefix.EqualTo("/afs/cern.ch/work/l/lecriste/www/TnP/") )
	    gSystem->CopyFile(prefix+uploadFile, dirPlace+uploadFile, true);
	  

	  //TString dirName = tree[iTree]+"/"+ids[iId]+"_"+folders[kk]+"_"+triggers[iTrig] ;
	  TString dirName = tree[iTree]+"/"+ids[iId]+"_"+folders[kk]+trig ;
	  if (ids[iId].Contains("Vertexing"))
	    dirName = tree[iTree]+"/"+ids[iId] ;
	  TDirectory *direc = f1->GetDirectory( dirName.Data() );
	  if (direc == 0) {
	    cout <<"\nNo TDirectory called \"" <<dirName.Data() <<"\" found in file " <<f1->GetName() <<endl ;
	    continue; }
	  TIter next( direc->GetListOfKeys() );
	  TKey *key;
      
	  //loop on subDirectories
	  while ( (key = (TKey*)next()) ) {
	    TClass *cl = gROOT->GetClass( key->GetClassName() );
	    if ( !cl->InheritsFrom("TDirectoryFile") ) continue;
	    TString name = key->GetTitle() ;
	    //cout <<key->GetTitle() <<endl ;    
	    TDirectory *direc2 = f1->GetDirectory( dirName+"/"+name );
	    if (direc2 == 0) {
	      cout <<"\nNo TDirectory called \"" <<name.Data() <<"\" found in TDirectory " <<dirName.Data() <<endl ;
	      continue; }
	    TIter next2( direc2->GetListOfKeys() );
	    TKey *key2;
	    
	    //loop on Canvases
	    while( (key2 = (TKey*)next2()) ) {
	      TClass *cl2 = gROOT->GetClass( key2->GetClassName() );
	      if ( !cl2->InheritsFrom("TCanvas") ) continue;
	      //cout <<key2->GetName() <<endl ;
	      TString name2 = key2->GetName() ;
	      for (uint i=0; i<notToPlot.size(); ++i) {
		//if ( key2->GetName() != notToPlot[i].Data() ) {
		if ( !notToPlot[i].EqualTo( name2 ) ) { 
		  TCanvas *c1 = (TCanvas*) key2->ReadObj() ;
		  //TCanvas *c1 = dynamic_cast<TCanvas*>( key2->ReadObj() ) ;
		  //c1->Update() ;
		  c1->SetGrid() ;
		  c1->Draw() ; //c1->UseCurrentStyle() ;

		  if ( name2.Contains("eta_pt") || name2.Contains("absrapidity_pair_pt_PLOT"))
		    gPad->SetLogy() ;
		  else if ( name2.Contains("pt_eta") || name2.Contains("pt_abseta") || name2.Contains("pt_PLOT") || name2.Contains("pt_pair_absrapidity_PLOT"))
		    gPad->SetLogx() ;


		  gSystem->mkdir(dirPlace, true);

		  if ( !trig.Contains("Mu8") ) {
		    name.ReplaceAll(trig+"_TK_pass_","").ReplaceAll("_tag"+trig+"_MU_pass_","") ;
		    name2.ReplaceAll("_and"+trig+"_TK_pass","").ReplaceAll("_and_tag"+trig+"_MU_pass","") ;
		  } else {	
		    name.ReplaceAll(trig+"_pass_","").ReplaceAll("_tag"+trig+"_pass_","") ;
		    name2.ReplaceAll("_and"+trig+"_pass","").ReplaceAll("_and_tag"+trig+"_pass","") ;
		  }	
	  	  c1->SaveAs(dirPlace+name+"_"+name2+".png");

		  //c1->SaveAs("plots/"+folders[kk]+"_"+key->GetTitle()+"_"+key2->GetName()+".eps");
		  //c1->SaveAs("plots/"+folders[kk]+"_"+key->GetTitle()+".eps");
		  //c1->SaveAs("plots/"+folders[kk]+"_"+key->GetTitle()+"_"+key2->GetName()+".pdf");

		}
		
	      }//end of loop on notToPlot canvases
	      
	    }//end of loop on canvases
	
	  }//end of loop on subdirectories 
      
	}//end of loop on directories
    
      }//end of loop on triggers

    }//end of loop on ids
    
  }//end of loop on trees
  
}

