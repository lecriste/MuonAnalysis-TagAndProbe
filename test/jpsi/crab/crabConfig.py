MC = False
#MC = True

Mu8 = False
#Mu8 = True

RunB = True
#RunB = False
RunDv3 = True
RunDv3 = False
RunDv4 = True
RunDv4 = False


from CRABClient.UserUtilities import config
config = config()

config.section_('General')
# MC
if MC:
	#config.General.requestName = 'TnP_fullMC_80X'
        config.General.requestName = 'TnP_fullMC_80X_correctTreeSta'
# Data
else:
	if (RunB):
		#config.General.requestName = 'TnP_RunB_80X'
                config.General.requestName = 'TnP_RunB_80X_correctTreeSta'
		if Mu8:
			config.General.requestName = 'TnP_RunB_Mu8'
	elif (RunDv3):
		#config.General.requestName = 'TnP_RunDv3'
		#config.General.requestName = 'TnP_RunDv3_noPairVtxInfo'
		config.General.requestName = 'TnP_RunDv3_addingMu25'
		if Mu8:
			config.General.requestName = 'TnP_RunDv3_Mu8_v2'
	elif (RunDv4):
		#config.General.requestName = 'TnP_RunDv4'
                #config.General.requestName = 'TnP_RunDv4_noPairVtxInfo'
		config.General.requestName = 'TnP_RunDv4_addingMu25'
		if Mu8:
			config.General.requestName = 'TnP_RunDv4_Mu8'

config.General.transferOutputs = True
config.General.transferLogs = False

config.section_('JobType')
config.JobType.pluginName = 'Analysis'
# MC
if MC:
	config.JobType.psetName = '../tp_from_aod_simple_MC.py'
# Data
else:
	config.JobType.psetName = '../tp_from_aod_simple_Data.py'

#config.JobType.outputFiles = ['tnpJpsi_MC.root']

config.section_('Data')
# MC
if MC:
	config.Data.inputDataset = '/JpsiToMuMu_JpsiPt8_TuneCUEP8M1_13TeV-pythia8/RunIISpring16DR80-PUSpring16_80X_mcRun2_asymptotic_2016_v3-v1/AODSIM' 
# Data
else:
	if (RunB):
		config.Data.inputDataset = '/Charmonium/Run2016B-PromptReco-v2/AOD'
		if Mu8:
			config.Data.inputDataset = '/DoubleMuon/Run2015C_25ns-05Oct2015-v1/AOD'
	elif (RunDv3):
		config.Data.inputDataset = '/Charmonium/Run2015D-PromptReco-v3/AOD'
		if Mu8:
			config.Data.inputDataset = '/DoubleMuon/Run2015D-PromptReco-v3/AOD'
	elif (RunDv4):
		config.Data.inputDataset = '/Charmonium/Run2015D-PromptReco-v4/AOD'
		if Mu8:
			config.Data.inputDataset = '/DoubleMuon/Run2015D-PromptReco-v4/AOD'


config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
if MC:
	config.Data.unitsPerJob = 37 # for full official MC
else:
	config.Data.unitsPerJob = 18
	if (RunDv3):
		config.Data.unitsPerJob = 2
	elif (RunDv4):
		config.Data.unitsPerJob = 3
	# JSON
	config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Cert_271036-274443_13TeV_PromptReco_Collisions16_JSON.txt' # 2.6/fb Golden
        #config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Cert_271036-275125_13TeV_PromptReco_Collisions16_JSON.txt' # 3.99/fb Golden

config.Data.publication = False
#config.Data.outLFNDirBase = '/store/user/lecriste/TnP/'
config.Data.outLFNDirBase = '/store/group/phys_muon/lecriste/TnP/' # for CERN
#config.Data.ignoreLocality = True

config.section_('Site')
#config.Site.blacklist = ['T0', 'T1'] # T0 blacklisted by default
config.Site.blacklist = ['T1*']
#config.Site.blacklist = ['T1*','T2_DE_DESY','T2_CH_CSCS','T1_RU_JINR']

#config.Site.storageSite = 'T2_IT_Bari'
#config.Site.storageSite = 'T2_IT_Legnaro'
config.Site.storageSite = 'T2_CH_CERN'

