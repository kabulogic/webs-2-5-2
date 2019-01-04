// JavaScript Document
var DVR_CH = getDVR_CH();
function getBasicInfo()
{
	try{
		document.ChInfoForm.ChannelName.value = document.ChInfoForm.Local_ChName.value;
		document.ChInfoForm.ChannelPort.value = document.ChInfoForm.Local_lPort.value;
		document.ChInfoForm.ChannelIP.value = document.ChInfoForm.Net_IP.value;
		document.ChInfoForm.ChannelUser.value = document.ChInfoForm.Net_User.value;
		document.ChInfoForm.ChannelPass.value = document.ChInfoForm.Net_Pass.value;
	}catch(e){}
}

function getImage()
{
	try{
		document.ChInfoForm.Color.value = document.ChInfoForm.Image_Color.value;
		document.ChInfoForm.Saturation.value = document.ChInfoForm.Image_Saturation.value;
		document.ChInfoForm.Contrast.value = document.ChInfoForm.Image_Contrast.value;
		document.ChInfoForm.Brightness.value = document.ChInfoForm.Image_Brightness.value;
	}catch(e){}	
}

function getOSD()
{
	//Time Setting
	try{
	if(document.ChInfoForm.OSD1_OnOff.value == "1"){
		document.ChInfoForm.OSD1_State.selectedIndex = 0;
	}
	else{
		document.ChInfoForm.OSD1_State.selectedIndex = 1;
	}
	switch(document.ChInfoForm.OSD1_Format.value){
		case "0":
			document.ChInfoForm.DateFormat.selectedIndex = 0;
			break;
		case "1":
			document.ChInfoForm.DateFormat.selectedIndex = 1;
			break;
		case "2":
			document.ChInfoForm.DateFormat.selectedIndex = 2;
			break;
		case "3":
			document.ChInfoForm.DateFormat.selectedIndex = 3;
			break;
		default:
			document.ChInfoForm.DateFormat.selectedIndex = 0;
			break;
	}
	if(document.ChInfoForm.OSD1_OnWeek.value == "1"){
		document.ChInfoForm.DisplayWeek.selectedIndex = 0;
	}
	else{
		document.ChInfoForm.DisplayWeek.selectedIndex = 1;
	}
	selectTime();
	document.ChInfoForm.OSD1_X.value = document.ChInfoForm.OSD1_X0.value;
	document.ChInfoForm.OSD1_Y.value = document.ChInfoForm.OSD1_Y0.value;
	
	//Show Channel Name
	if(document.ChInfoForm.OSD2_OnOff.value == "1"){
		document.ChInfoForm.OSD2_State.selectedIndex = 0;
	}
	else{
		document.ChInfoForm.OSD2_State.selectedIndex = 1;
	}
	document.ChInfoForm.OSD2_X.value = document.ChInfoForm.OSD2_X0.value;
	document.ChInfoForm.OSD2_Y.value = document.ChInfoForm.OSD2_Y0.value;

	//OSD 1
	if(document.ChInfoForm.OSD3_OnOff.value == "1"){
		document.ChInfoForm.OSD3_State.checked = true;
	}
	else{
		document.ChInfoForm.OSD3_State.checked = false;
	}
	document.ChInfoForm.OSD3_Title.value = document.ChInfoForm.OSD3_Text.value;
	document.ChInfoForm.OSD3_X.value = document.ChInfoForm.OSD3_X0.value;
	document.ChInfoForm.OSD3_Y.value = document.ChInfoForm.OSD3_Y0.value;

	//OSD 2
	if(document.ChInfoForm.OSD4_OnOff.value == "1"){
		document.ChInfoForm.OSD4_State.checked = true;
	}
	else{
		document.ChInfoForm.OSD4_State.checked = false;
	}
	document.ChInfoForm.OSD4_Title.value = document.ChInfoForm.OSD4_Text.value;
	document.ChInfoForm.OSD4_X.value = document.ChInfoForm.OSD4_X0.value;
	document.ChInfoForm.OSD4_Y.value = document.ChInfoForm.OSD4_Y0.value;

	//OSD 3
	/*if(document.ChInfoForm.OSD5_OnOff.value == "1"){
		document.ChInfoForm.OSD5_State.checked = true;
	}
	else{
		document.ChInfoForm.OSD5_State.checked = false;
	}
	document.ChInfoForm.OSD5_Title.value = document.ChInfoForm.OSD5_Text.value;
	document.ChInfoForm.OSD5_X.value = document.ChInfoForm.OSD5_X0.value;
	document.ChInfoForm.OSD5_Y.value = document.ChInfoForm.OSD5_Y0.value;

	//OSD 4
	if(document.ChInfoForm.OSD6_OnOff.value == "1"){
		document.ChInfoForm.OSD6_State.checked = true;
	}
	else{
		document.ChInfoForm.OSD6_State.checked = false;
	}
	document.ChInfoForm.OSD6_Title.value = document.ChInfoForm.OSD6_Text.value;
	document.ChInfoForm.OSD6_X.value = document.ChInfoForm.OSD6_X0.value;
	document.ChInfoForm.OSD6_Y.value = document.ChInfoForm.OSD6_Y0.value;*/
	}catch(e){}
}

/************************Signal Loss*********************************/
function getSigCfg()
{
	getHandleOnOff("Sig");
	getDefendTime('sig')
}
/************************View Obstruct*******************************/
function getObsCfg()
{
	getHandleOnOff("Obs");
	getSenById("Obs");
	getDefendTime('obs')
}

function getMotionCfg()
{
	getHandleOnOff("Motion");
	getSenById("Mo");
	getDefendTime('motion')
}

function getMotionContact()
{
	try{
	HandleMethod("Motion");//Linkage
	//onTriggerRecordChan("MotionRecordChannel",0);//Trigger Record Channel
	SetCheckedByName("MAR_Ch","MotionRecordChannel");
	}catch(e){}
}

function SetCheckedByName(name1,name2)
{
	var i;
	for(i=1;i<=DVR_CH;i++){
		j = i-1;
		if(document.getElementById(name1+j).value == "1"){
			document.getElementById(name2+i).checked = true;
		}
		else document.getElementById(name2+i).checked = false;
	}
}

function onSelectPTZCh()
{
	var channel = document.ChInfoForm.PTZChannel.value;
	getChPTZ(channel);
	document.ChInfoForm.backPTZCh.value = channel;
}

function getChPTZ(channel)
{
	try{
	var method = document.getElementById("MPM_Ch"+channel).value;
	var point = document.getElementById("MPP_Ch"+channel).value;
	switch(method){
		case "1":  //preset
			document.ChInfoForm.preset.checked = true;
			document.ChInfoForm.PresetValue.disabled = false;
			document.ChInfoForm.PresetValue.value = point;
			document.ChInfoForm.cruise.checked = false;
			document.ChInfoForm.CruiseValue.disabled = true;
			break;
		case "3":  //pattern
			document.ChInfoForm.preset.checked = false;
			document.ChInfoForm.PresetValue.disabled = true;
			document.ChInfoForm.cruise.checked = true;
			document.ChInfoForm.CruiseValue.disabled = false;
			document.ChInfoForm.CruiseValue.value = point;
			break;
		default:
			document.ChInfoForm.preset.checked = false;
			document.ChInfoForm.PresetValue.disabled = true;
			document.ChInfoForm.cruise.checked = false;
			document.ChInfoForm.CruiseValue.disabled = true;
			break;
	}
	}catch(e){}
}

function SetbackMDPTZ()
{
	if(isNumMax(document.ChInfoForm.PresetValue,255) && isNumMax(document.ChInfoForm.CruiseValue,4)){
		setObjectByName("isPTZChChange","1");
		backCh = document.ChInfoForm.backPTZCh.value;
		if(document.ChInfoForm.preset.checked){
			document.getElementById("MPM_Ch"+backCh).value = "1";
			document.getElementById("MPP_Ch"+backCh).value = document.ChInfoForm.PresetValue.value;
		} 
		else if(document.ChInfoForm.cruise.checked){
			document.getElementById("MPM_Ch"+backCh).value = "3";
			document.getElementById("MPP_Ch"+backCh).value = document.ChInfoForm.CruiseValue.value;
		}
		else{
			document.getElementById("MPM_Ch"+backCh).value = "0";
			document.getElementById("MPP_Ch"+backCh).value = 0;
		}
	}
}

/******************Set Area of Privacy, Mo Dec., Obs*****************/
function displayArea()
{
	document.getElementById("AreaFrame0").src = "../setArea0.asp";
	document.getElementById("AreaFrame0").style.display ="";	
}

function onObsEnable()
{
	//if(document.ChInfoForm.Channel.selectedIndex<16){
		document.ChInfoForm.ObsLevel.disabled = (document.ChInfoForm.ObsEnable.checked) ? false : true;
		document.ChInfoForm.ObstructDefend.disabled = (document.ChInfoForm.ObsEnable.checked) ? false : true;
		document.ChInfoForm.ObstructMethod.disabled = (document.ChInfoForm.ObsEnable.checked) ? false : true;
		if(!document.ChInfoForm.ObsEnable.checked){
			hideById("ObsDefendTime");	
			hideById("ObsHandleMethod");	
		}
	//}
}
function onSigEnable()
{
	document.ChInfoForm.SigDefend.disabled = (document.ChInfoForm.SigEnable.checked) ? false : true;
	document.ChInfoForm.SigMethod.disabled = (document.ChInfoForm.SigEnable.checked) ? false : true;
	if(!document.ChInfoForm.SigEnable.checked){
		hideById("SigDefendTime");	
		hideById("SigHandleMethod");	
	}
}
function onMoEnable()
{
	document.ChInfoForm.MoLevel.disabled = (document.ChInfoForm.MotionEnable.checked) ? false : true;
	document.ChInfoForm.ckMoSchedule.disabled = (document.ChInfoForm.MotionEnable.checked) ? false : true;
	document.ChInfoForm.MotionHandleContact.disabled = (document.ChInfoForm.MotionEnable.checked) ? false : true;
	if(!document.ChInfoForm.MotionEnable.checked){
		hideById("MotionDefendTime");	
		hideById("MotionAlarmContact");	
	}
}
function initEnable()
{
	onObsEnable();
	onSigEnable();
	onMoEnable();
}
function hideById(id)
{
	if(document.getElementById(id).style.display == "")
		document.getElementById(id).style.display = "none";	
}
function getSenById(id)
{
	if(parseInt(document.getElementById(id+"Sen").value)>2)
	{
		document.getElementById(id+"Level").selectedIndex = 2;	
	}
	else
	{
		document.getElementById(id+"Level").selectedIndex = parseInt(document.getElementById(id+"Sen").value);
	}
}
function selectTime()
{
	if(document.ChInfoForm.OSD1_State.selectedIndex == 0){
		document.ChInfoForm.DisplayWeek.disabled = false;
	}
	else{
		document.ChInfoForm.DisplayWeek.selectedIndex = 1;
		document.ChInfoForm.DisplayWeek.disabled = true;
	}
}

function initChannel()
{
	if(DVR_CH >8)
	{
		document.all.reRow3.style.display = "";
		document.all.reRow4.style.display = "";
	}
	lang = document.getElementById("lang").value;
	if(lang == 'cn')showTips("正在读取通道配置信息，请稍等.....")
	else showTips("Getting channel information,please wait...")
	setTimeout("getchanParameter()",10);
	setTimeout("hideTips()",20);
}

function getchanParameter()
{
	initchanDefendTimetable();
	setOperator();
	getpara();
	InitBtSet();
	GetCh();
	getBasicInfo();
	getImage();
	getOSD();
	getSigCfg();
	HandleMethod('Sig');
	getMotionCfg();
	getMotionContact();
	getObsCfg();
	HandleMethod('Obs');
	initEnable();	
	displayArea();
}