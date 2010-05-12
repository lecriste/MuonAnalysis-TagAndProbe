import FWCore.ParameterSet.Config as cms

FILEPREFIX = "signal_"
#FILEPREFIX = "withbg_"
CONSTRAINTS = cms.PSet(
    Glb        = cms.vstring("true"),
    tag_HLTMu3 = cms.vstring("pass"),
)
PT_ETA_BINS = cms.PSet(
    CONSTRAINTS,
    pt = cms.vdouble( 2, 3, 4.5, 6, 20),
    eta = cms.vdouble(-2.1, -1.1, 1.1, 2.1)
)

process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')

process.source = cms.Source("EmptySource")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

Template = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    NumCPU = cms.uint32(1),
    SaveWorkspace = cms.bool(False),

    Variables = cms.PSet(
        mass = cms.vstring("Tag-Probe Mass", "2.0", "4.3", "GeV/c^{2}"),
        pt = cms.vstring("Probe p_{T}", "0", "1000", "GeV/c"),
        p = cms.vstring("Probe p", "0", "1000", "GeV/c"),
        eta = cms.vstring("Probe #eta", "-2.5", "2.5", ""),
        phi = cms.vstring("Probe #phi", "-3.1416", "3.1416", ""),
        tag_pt = cms.vstring("Tag p_{T}", "2.6", "1000", "GeV/c"),
    ),

    Categories = cms.PSet(
        mcTrue = cms.vstring("MC true", "dummy[true=1,false=0]"),
        Glb    = cms.vstring("GlobalMu","dummy[true=1,false=0]"),
        HLTMu3     = cms.vstring("HLTMu3", "dummy[pass=1,fail=0]"),
        L1DiMuOpen = cms.vstring("HLTMu3", "dummy[pass=1,fail=0]"),
        tag_HLTMu3 = cms.vstring("tag_HLTMu3", "dummy[pass=1,fail=0]"),
    ),

    PDFs = cms.PSet(
        gaussPlusExpo = cms.vstring(
            "Gaussian::signal(mass, mean[3.1,3.0,3.2], sigma[0.2,0.05,0.5])",
            "Exponential::backgroundPass(mass, lp[0,-1,1])",
            "Exponential::backgroundFail(mass, lp)",  # same slope, they're both muons
            #"Exponential::backgroundFail(mass, lf[0,-1,1])",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        )
    )
)

process.TnP_Trigger = Template.clone(
    InputFileNames = cms.vstring(
        #"tnpJPsi_JPsiMuMu_Spring10_0.5pb.root",
        "tnpJPsi_JPsiMuMu_Spring10_0.1pb.root",
        #"tnpJPsi_ppMuX_Spring10_0.1pb.root"
    ),
    InputDirectoryName = cms.string("histoTrigger"),
    InputTreeName = cms.string("fitter_tree"),
    #OutputFileName = cms.string(FILEPREFIX+"TnP_Trigger_0.5pb.root"),
    OutputFileName = cms.string(FILEPREFIX+"TnP_Trigger_0.1pb.root"),
    Efficiencies = cms.PSet(),
)

for T in [ "HLTMu3", "L1DiMuOpen" ]:
    setattr(process.TnP_Trigger.Efficiencies, T+"_pt_eta", cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(T,"pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = PT_ETA_BINS,
            BinToPDFmap = cms.vstring("gaussPlusExpo")
    ))
    setattr(process.TnP_Trigger.Efficiencies, T+"_pt_eta_mcTrue", cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(T,"pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = PT_ETA_BINS.clone(
                mcTrue = cms.vstring("true")
            )
    ))
    
if False:
    process.TnP_Trigger.InputFileNames = [ "tnpJPsi_Data.root" ]
    process.TnP_Trigger.OutputFileName = "data_TnP_Trigger_1nb.root"
    process.TnP_Trigger.Efficiencies = cms.PSet()
    process.TnP_Trigger.Variables.tag_pt[1] = "0.0"; # don't cut on tag pt
    process.TnP_Trigger.Variables.run       = cms.vstring("Run number", "0", "9999999", "");
    for T in [ "HLTMu3", "L1DiMuOpen" ]:
        setattr(process.TnP_Trigger.Efficiencies, T+"_pt_eta", cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(T,"pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                Glb = cms.vstring("true"),
                pt  = cms.vdouble( 2, 3, 15 ),
                eta = cms.vdouble(-2.1,-1.0,1.0, 2.1),
                run = cms.vdouble(0,9999999),
            ),
            BinToPDFmap = cms.vstring("gaussPlusExpo")
        ))
        setattr(process.TnP_Trigger.Efficiencies, T+"_pt", cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(T,"pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                Glb = cms.vstring("true"),
                pt  = cms.vdouble( 2, 3, 15 ),
                eta = cms.vdouble(-2.1, 2.1),
                run = cms.vdouble(0,9999999),
            ),
            BinToPDFmap = cms.vstring("gaussPlusExpo")
        ))
        if T.find("HLT") != -1:
            getattr(process.TnP_Trigger.Efficiencies, T+"_pt_eta").BinnedVariables.run = cms.vdouble(133443,9999999)
            getattr(process.TnP_Trigger.Efficiencies, T+"_pt"    ).BinnedVariables.run = cms.vdouble(133443,9999999)


process.p = cms.Path(
    process.TnP_Trigger
)

