// JavaScript Document
var DVR_CH = getDVR_CH();
var bAICopy = false;
var bAOCopy = false;
function setAlarmCfg()
{
	//var err = getCookie("seterror=");
	//alert("err="+err);
	//if(err == 1) return;
	var flag = document.AlarmForm.flag.value;
	var num = document.AlarmForm.AlarmInput.selectedIndex;

	//set alarm input
	if( isNumMax(document.AlarmForm.PresetValue,255) && isNumMax(document.AlarmForm.CruiseValue,4)){ 
		if( AlarmInHasChange() ){
			SetDefendTime("alarmin");
			SetbackAlarmInPTZ();
			setObjectByName("isAlarmInChange","0");
			setObjectByName("isPTZChChange","0");
			flag |= 0x0001;  //save an alarm input
		}
	}
	//set alarm output
	var num1 = document.AlarmForm.AlarmOutput.selectedIndex;
	if( AlarmOutHasChange() ){
		SetDefendTime("alarmout");
		setObjectByName("isAlarmOutChange","0");
		flag |= 0x0010;  //save an alarm output
	}
	//AlarmEx
	var num2 = document.AlarmForm.ExceptionType.value;
	if(AlarmExChange(num2)){
		flag |= 0x0100;
	}
	if(bAICopy)
	{
		var s_num = document.AlarmForm.AlarmInput.value;
		var d_num = document.AlarmForm.AlarmInputCopy.value;
		if(s_num != d_num)
		{
			if(isNumMax(document.AlarmForm.PresetValue,255) && isNumMax(document.AlarmForm.CruiseValue,4)){ 
				SetDefendTime("alarmin");
				SetbackAlarmInPTZ();
				flag |= 0x0002;      //copy alarm input
			}
		}	
	}
	if(bAOCopy)
	{
		var s_num = document.AlarmForm.AlarmOutput.value;
		var d_num = document.AlarmForm.AlarmOutputCopy.value;
		if(s_num != d_num)
		{
			SetDefendTime("alarmout");
			flag |= 0x0020;      //copy alarm output
		}
	}
		document.AlarmForm.flag.value = flag;
		formSubmit();
}

function AlarmInHasChange()
{
	if( (compare(document.AlarmForm.InputName,document.getElementById("InName"))) || (compare(document.AlarmForm.AlarmType,document.getElementById("InType"))) || (document.AlarmForm.isAlarmInChange.value == "1") || (document.AlarmForm.isPTZChChange.value == "1") || AlarmInTr_Change() || AlarmIn_RecordTr_Change() ){
		return true;
	}
	else return false;
}

function AlarmInTr_Change()
{
	//var num = document.AlarmForm.AlarmInput.selectedIndex;
	var bol = false;
	bol |= checkComp(document.AlarmForm.InTriggerMonitor,document.getElementById("AIToMonitor"));
	bol |= checkComp(document.AlarmForm.InTriggerVoice,document.getElementById("AIToVoice"));
	bol |= checkComp(document.AlarmForm.InTriggerCenter,document.getElementById("AIToCenter"));
	bol |= checkComp(document.AlarmForm.InTriggerOutput1,document.getElementById("AIToTrigger1"));
	bol |= checkComp(document.AlarmForm.InTriggerOutput2,document.getElementById("AIToTrigger2"));
	bol |= checkComp(document.AlarmForm.InTriggerOutput3,document.getElementById("AIToTrigger3"));
	bol |= checkComp(document.AlarmForm.InTriggerOutput4,document.getElementById("AIToTrigger4"));
	return bol;
}

function AlarmIn_RecordTr_Change()
{
	//var num = document.AlarmForm.AlarmInput.selectedIndex;
	var bol = false;
	for(i=0; i<DVR_CH; i++){
		j = i+1;
		bol |= checkComp(document.getElementById("RecordChannel"+j),document.getElementById("AIR_Ch"+i));
	}
	return bol;
}

function OnAlarmInCopy()
{
	bAICopy = true;
}

function AlarmOutHasChange()
{
	if( (compare(document.AlarmForm.AlarmOutputPostTime,document.getElementById("DelayTime"))) || (document.AlarmForm.isAlarmOutChange.value == "1")){
		return true;
	}
	else return false;
}

function OnAlarmOutCopy()
{
	bAOCopy = true;
}

function AlarmExChange(num)
{
	var bol = false;
	bol |= checkComp(document.AlarmForm.ExTriggerMonitor,document.getElementById("AEToMonitor_"+num));
	bol |= checkComp(document.AlarmForm.ExTriggerVoice,document.getElementById("AEToVoice_"+num));
	bol |= checkComp(document.AlarmForm.ExTriggerCenter,document.getElementById("AEToCenter_"+num));
	bol |= checkComp(document.AlarmForm.ExTriggerOutput1,document.getElementById("AEToTrigger1_"+num));
	bol |= checkComp(document.AlarmForm.ExTriggerOutput2,document.getElementById("AEToTrigger2_"+num));
	bol |= checkComp(document.AlarmForm.ExTriggerOutput3,document.getElementById("AEToTrigger3_"+num));
	bol |= checkComp(document.AlarmForm.ExTriggerOutput4,document.getElementById("AEToTrigger4_"+num));
	return bol;
}

function OnAlarmExCopy()
{
	/*var s_num = document.AlarmForm.ExceptionType.value;
	var d_num = document.AlarmForm.AlarmExCopy.value;
	if(s_num != d_num){
		document.AlarmForm.flag.value = 0x0200;      //copy alarm exception
		formSubmit();
	}*/
}

function formSubmit()
{
	var flag = document.AlarmForm.flag.value;
	if(flag != 0){
		document.AlarmForm.submit();
		document.AlarmForm.flag.value = 0;
		bAICopy = false;
		bAOCopy = false;
	}
}