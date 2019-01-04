// JavaScript Document
var DVR_CH = getDVR_CH();
var bCopy = false;
function setChCfg()
{
	//var err = getCookie("seterror=")
	//if(err == 1) return;
	var flag = document.ChInfoForm.flag.value;
	//basic info change
	if(compare(document.ChInfoForm.ChannelName,document.ChInfoForm.Local_ChName) || compare(document.ChInfoForm.ChannelPort,document.ChInfoForm.Local_lPort) || compare(document.ChInfoForm.ChannelIP,document.ChInfoForm.Net_IP) || compare(document.ChInfoForm.ChannelUser,document.ChInfoForm.Net_User) || compare(document.ChInfoForm.ChannelPass,document.ChInfoForm.Net_Pass) ){  
		flag |= 0x0001;
	}
	//image info change
	if( compare(document.ChInfoForm.Color,document.ChInfoForm.Image_Color) || compare(document.ChInfoForm.Saturation,document.ChInfoForm.Image_Saturation) || compare(document.ChInfoForm.Contrast,document.ChInfoForm.Image_Contrast) || compare(document.ChInfoForm.Brightness,document.ChInfoForm.Image_Brightness) ){  
		flag |= 0x0008;
	}
	//OSD
	/*if( compare(document.ChInfoForm.OSD1_State,document.ChInfoForm.OSD1_OnOff) || compare(document.ChInfoForm.DisplayWeek,document.ChInfoForm.OSD1_OnWeek) || compare(document.ChInfoForm.OSD1_X,document.ChInfoForm.OSD1_X0) || compare(document.ChInfoForm.OSD1_Y,document.ChInfoForm.OSD1_Y0) || compare(document.ChInfoForm.OSD2_State,document.ChInfoForm.OSD2_OnOff) || compare(document.ChInfoForm.OSD2_X,document.ChInfoForm.OSD2_X0) || compare(document.ChInfoForm.OSD2_Y,document.ChInfoForm.OSD2_Y0) || checkComp(document.ChInfoForm.OSD3_State,document.ChInfoForm.OSD3_OnOff) || compare(document.ChInfoForm.OSD3_Title,document.ChInfoForm.OSD3_Text) || compare(document.ChInfoForm.OSD3_X,document.ChInfoForm.OSD3_X0) || compare(document.ChInfoForm.OSD3_Y,document.ChInfoForm.OSD3_Y0) || checkComp(document.ChInfoForm.OSD4_State,document.ChInfoForm.OSD4_OnOff) || compare(document.ChInfoForm.OSD4_Title,document.ChInfoForm.OSD4_Text) || compare(document.ChInfoForm.OSD4_X,document.ChInfoForm.OSD4_X0) || compare(document.ChInfoForm.OSD4_Y,document.ChInfoForm.OSD4_Y0)){  */
	if(osdHint())
	{
		flag |= 0x0010;
	}
	else
	{
		flag = 0;	
		return false;
	}
	//}
	/*privacy area*/
	if( checkComp(document.ChInfoForm.PriEnable,document.ChInfoForm.PriOn) ){
		flag |= 0x0020;
	}
		/*Motion Detection*/
	if(isNumMax(document.ChInfoForm.PresetValue,255) && isNumMax(document.ChInfoForm.CruiseValue,4)){
		if((checkComp(document.ChInfoForm.MotionEnable,document.ChInfoForm.MotionOn)) 
					  || (compareIndex(document.ChInfoForm.MoLevel,document.ChInfoForm.MoSen))
					  || (document.ChInfoForm.isMotionPlanChange.value == "1") 
					  || (document.ChInfoForm.isPTZChChange.value == "1") 
					  || MD_AlarmTr_Change("Motion") || MD_RecordTr_Change()){
			flag |= 0x0040;
			SetDefendTime("motion");
			SetbackMDPTZ();
			setObjectByName("isMotionPlanChange","0");
			setObjectByName("isPTZChChange","0");
		}
	}
	//View Obstruct
	if( (checkComp(document.ChInfoForm.ObsEnable,document.ChInfoForm.ObsOn)) || (compareIndex(document.ChInfoForm.ObsLevel,document.ChInfoForm.ObsSen)) || (document.ChInfoForm.isObsPlanChange.value == "1") || MD_AlarmTr_Change("Obs") ){
		flag |= 0x0080;
		SetDefendTime("obs");
		setObjectByName("isObsPlanChange","0");
	}
	//Signal Loss
	if( (checkComp(document.ChInfoForm.SigEnable,document.ChInfoForm.SigOn)) || (document.ChInfoForm.isSigPlanChange.value == "1") || MD_AlarmTr_Change("Sig") ){
		flag |= 0x0100;
		SetDefendTime("sig");
		setObjectByName("isSigPlanChange","0");
	}
	if(bCopy)
	{
		if(document.ChInfoForm.Channel.selectedIndex != document.ChInfoForm.CopyCh.selectedIndex)
		{
			/* copy channel info to another channel */
			flag |= 0x1000; 
			/* save defend plan to middle variable */
			SetDefendTime("sig");
			SetDefendTime("obs");
			SetDefendTime("motion");
			SetbackMDPTZ();
		}
	}
	document.ChInfoForm.flag.value = flag;
	if(flag != 0){
		document.ChInfoForm.submit();
	}
	
	bCopy = false;
	document.ChInfoForm.flag.value = 0;
}

function MD_AlarmTr_Change(name)
{
	var bol = false;
	bol |= checkComp(document.getElementById(name+"TriggerMonitor"),document.getElementById(name+"Monitor"));
	bol |= checkComp(document.getElementById(name+"TriggerVoice"),document.getElementById(name+"Voice"));
	bol |= checkComp(document.getElementById(name+"TriggerCenter"),document.getElementById(name+"Center"));
	bol |= checkComp(document.getElementById(name+"TriggerOutput1"),document.getElementById(name+"Trigger1"));
	bol |= checkComp(document.getElementById(name+"TriggerOutput2"),document.getElementById(name+"Trigger2"));
	bol |= checkComp(document.getElementById(name+"TriggerOutput3"),document.getElementById(name+"Trigger3"));
	bol |= checkComp(document.getElementById(name+"TriggerOutput4"),document.getElementById(name+"Trigger4"));
	return bol;
}

function MD_RecordTr_Change()
{
	var bol = false;
	for(i=0; i<DVR_CH; i++){
		j = i+1;
		bol |= checkComp(document.getElementById("MotionRecordChannel"+j),document.getElementById("MAR_Ch"+i));
	}
	return bol;
}

function OnChCopy()
{
	bCopy = true;
}