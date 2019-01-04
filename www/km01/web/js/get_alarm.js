// JavaScript Document
var DVR_CH = getDVR_CH();
function GetAIO()
{
	if(readcookie("AI")){
		ch = parseInt(getCookie("AI"));
		document.forms[0].AlarmInput.selectedIndex = ch;
	}
	else{
		document.forms[0].AlarmInput.selectedIndex = 0;	
	}
	if(readcookie("AO")){
		ch = parseInt(getCookie("AO"));
		document.forms[0].AlarmOutput.selectedIndex = ch;
	}
	else{
		document.forms[0].AlarmOutput.selectedIndex = 0;	
	}
	if(readcookie("AE")){
		ch = parseInt(getCookie("AE"));
		//document.forms[0].ExceptionType.selectedIndex = ch;
		
		switch(ch){
			case 0:
			case 1:
			case 3:
				document.all.Center.style.display = "";	
				break;
			case 2:
			case 4:
				document.all.Center.style.display = "none";	
				break;
		}
		document.forms[0].ExceptionType.selectedIndex = ch;
	}
	else{
		document.forms[0].ExceptionType.selectedIndex = 0;	
	}
}
function SetAI()
{
	addcookie("AI="+document.forms[0].AlarmInput.selectedIndex);
	parent.rightFrame.document.location.reload();
}
function DelAIOCook()
{
	addcookie("AI=0");
	addcookie("AO=0");
	addcookie("AE=0");
}
function SetAO()
{
	addcookie("AO="+document.forms[0].AlarmOutput.selectedIndex);
	parent.rightFrame.document.location.reload();
}
function SetAE()
{
	addcookie("AE="+document.forms[0].ExceptionType.value);
	parent.rightFrame.document.location.reload();
}

function getAlarmInput()
{
	//AlarmInNum = document.AlarmForm.AlarmInput.selectedIndex;
	try{
	document.AlarmForm.InputName.value = document.getElementById("InName").value;
	if(document.getElementById("InType").value == "0"){
		document.AlarmForm.AlarmType.selectedIndex = 0;
	}
	else{
		document.AlarmForm.AlarmType.selectedIndex = 1;
	}
	//document.AlarmForm.DefendTimeWeekAlarmIn.selectedIndex = getWeekday();
	getDefendTime('alarmin');
	getAlarmInContact();
	onSelectPTZCh();
	}catch(e){}
}

function getAlarmInContact()
{
	//Linkage
	//AlarmInNum = document.AlarmForm.AlarmInput.selectedIndex;
	try{
	if(document.getElementById("AIToMonitor").value == "1"){
		document.AlarmForm.InTriggerMonitor.checked = true;
	}
	else{
		document.AlarmForm.InTriggerMonitor.checked = false;
	}
	if(document.getElementById("AIToVoice").value == "1"){
		document.AlarmForm.InTriggerVoice.checked = true;
	}
	else{
		document.AlarmForm.InTriggerVoice.checked = false;
	}
	if(document.getElementById("AIToCenter").value == "1"){
		document.AlarmForm.InTriggerCenter.checked = true;
	}
	else{
		document.AlarmForm.InTriggerCenter.checked = false;
	}
	if((document.getElementById("AIToTrigger1").value == "1") || (document.getElementById("AIToTrigger2").value == "1") || (document.getElementById("AIToTrigger3").value == "1") || (document.getElementById("AIToTrigger4").value == "1")){
		document.AlarmForm.InTriggerOutput.checked = true;
		if(document.getElementById("AIToTrigger1").value == "1"){
			document.AlarmForm.InTriggerOutput1.checked = true;
		}
		else{
			document.AlarmForm.InTriggerOutput1.checked = false;
		}
		if(document.getElementById("AIToTrigger2").value == "1"){
			document.AlarmForm.InTriggerOutput2.checked = true;
		}
		else{
			document.AlarmForm.InTriggerOutput2.checked = false;
		}
		if(document.getElementById("AIToTrigger3").value == "1"){
			document.AlarmForm.InTriggerOutput3.checked = true;
		}
		else{
			document.AlarmForm.InTriggerOutput3.checked = false;
		}
		if(document.getElementById("AIToTrigger4").value == "1"){
			document.AlarmForm.InTriggerOutput4.checked = true;
		}
		else{
			document.AlarmForm.InTriggerOutput4.checked = false;
		}
	}
	else{
		document.AlarmForm.InTriggerOutput.checked = false;
	}
	onInTriggerOutput();
	//Trigger Record Channel
	SetCheckedByName("AIR_Ch","RecordChannel");
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
	var channel = document.AlarmForm.ContactPTZChannel.value;
	//AlarmInNum = document.AlarmForm.AlarmInput.selectedIndex;
	getChPTZ(channel);
	document.AlarmForm.backPTZCh.value = channel;
}

function getChPTZ(channel)
{
	//try{
	var method = document.getElementById("AIPM_Ch"+channel).value;
	var point = document.getElementById("AIPP_Ch"+channel).value;
	switch(method){
		case "1":  //preset
			document.AlarmForm.preset.checked = true;
			document.AlarmForm.PresetValue.disabled = false;
			document.AlarmForm.PresetValue.value = point;
			document.AlarmForm.cruise.checked = false;
			document.AlarmForm.CruiseValue.disabled = true;
			break;
		case "3":  //pattern
			document.AlarmForm.preset.checked = false;
			document.AlarmForm.PresetValue.disabled = true;
			document.AlarmForm.cruise.checked = true;
			document.AlarmForm.CruiseValue.disabled = false;
			document.AlarmForm.CruiseValue.value = point;
			break;
		default:
			document.AlarmForm.preset.checked = false;
			document.AlarmForm.PresetValue.disabled = true;
			document.AlarmForm.cruise.checked = false;
			document.AlarmForm.CruiseValue.disabled = true;
			break;
	}
	//}catch(e){}
}

function getAlarmOutput()
{
	//var AlarmOutNum = document.AlarmForm.AlarmOutput.selectedIndex;
	try{
	var delay = document.getElementById("DelayTime").value;
	switch(delay){
		case "5":
			document.AlarmForm.AlarmOutputPostTime.selectedIndex = 0;
			break;
		case "10":
			document.AlarmForm.AlarmOutputPostTime.selectedIndex = 1;
			break;
		case "30":
			document.AlarmForm.AlarmOutputPostTime.selectedIndex = 2;
			break;
		case "60":
			document.AlarmForm.AlarmOutputPostTime.selectedIndex = 3;
			break;
		case "120":
			document.AlarmForm.AlarmOutputPostTime.selectedIndex = 4;
			break;
		case "300":
			document.AlarmForm.AlarmOutputPostTime.selectedIndex = 5;
			break;
		case "600":
			document.AlarmForm.AlarmOutputPostTime.selectedIndex = 6;
			break;
		default:
			document.AlarmForm.AlarmOutputPostTime.selectedIndex = 0;
			break;
	}
	getAlarmOutDefendTime();
	}catch(e){}
}

function getAlarmOutDefendTime()
{
	getDefendTime('alarmout')
}

function getAlarmEx()
{
	//Linkage
	var AlarmENum = document.AlarmForm.ExceptionType.value;
	try{
	if(document.getElementById("AEToMonitor_"+AlarmENum).value == "1"){
		document.AlarmForm.ExTriggerMonitor.checked = true;
	}
	else{
		document.AlarmForm.ExTriggerMonitor.checked = false;
	}
	if(document.getElementById("AEToVoice_"+AlarmENum).value == "1"){
		document.AlarmForm.ExTriggerVoice.checked = true;
	}
	else{
		document.AlarmForm.ExTriggerVoice.checked = false;
	}
	if(document.getElementById("AEToCenter_"+AlarmENum).value == "1"){
		document.AlarmForm.ExTriggerCenter.checked = true;
	}
	else{
		document.AlarmForm.ExTriggerCenter.checked = false;
	}
	if((document.getElementById("AEToTrigger1_"+AlarmENum).value=="1") || (document.getElementById("AEToTrigger2_"+AlarmENum).value=="1") || (document.getElementById("AEToTrigger3_"+AlarmENum).value=="1") ||(document.getElementById("AEToTrigger4_"+AlarmENum).value=="1")){
		document.AlarmForm.ExTriggerOutput.checked = true;
		if(document.getElementById("AEToTrigger1_"+AlarmENum).value == "1"){
			document.AlarmForm.ExTriggerOutput1.checked = true;
		}
		else{
			document.AlarmForm.ExTriggerOutput1.checked = false;
		}
		if(document.getElementById("AEToTrigger2_"+AlarmENum).value == "1"){
			document.AlarmForm.ExTriggerOutput2.checked = true;
		}
		else{
			document.AlarmForm.ExTriggerOutput2.checked = false;
		}
		if(document.getElementById("AEToTrigger3_"+AlarmENum).value == "1"){
			document.AlarmForm.ExTriggerOutput3.checked = true;
		}
		else{
			document.AlarmForm.ExTriggerOutput3.checked = false;
		}
		if(document.getElementById("AEToTrigger4_"+AlarmENum).value == "1"){
			document.AlarmForm.ExTriggerOutput4.checked = true;
		}
		else{
			document.AlarmForm.ExTriggerOutput4.checked = false;
		}
	}
	else{
		document.AlarmForm.ExTriggerOutput.checked = false;
		document.AlarmForm.ExTriggerOutput1.checked = false;
		document.AlarmForm.ExTriggerOutput2.checked = false;
		document.AlarmForm.ExTriggerOutput3.checked = false;
		document.AlarmForm.ExTriggerOutput4.checked = false;
	}
	onExTriggerOutput();
	}catch(e){}
}

function SetbackAlarmInPTZ()
{
	if(isNumMax(document.AlarmForm.PresetValue,255) && isNumMax(document.AlarmForm.CruiseValue,4)){
		setObjectByName("isPTZChChange","1");
		var backCh = document.AlarmForm.backPTZCh.value;
		//var num = document.AlarmForm.AlarmInput.selectedIndex;
		SetPTZByNum(backCh);
	}
}

function SetPTZByNum(chNum)
{
	if(document.AlarmForm.preset.checked){
		document.getElementById("AIPM_Ch"+chNum).value = "1";
		document.getElementById("AIPP_Ch"+chNum).value = document.AlarmForm.PresetValue.value;
	} 
	else if(document.AlarmForm.cruise.checked){
		document.getElementById("AIPM_Ch"+chNum).value = "3";
		document.getElementById("AIPP_Ch"+chNum).value = document.AlarmForm.CruiseValue.value;
	}
	else{
		document.getElementById("AIPM_Ch"+chNum).value = "0";
		document.getElementById("AIPP_Ch"+chNum).value = 0;
	}
}

function SetbackOutDefendTime()
{
	//var num = document.AlarmForm.AlarmOutput.selectedIndex;
	if(period("OutDefendTime"))
	{
		setObjectByName("isAlarmOutChange","1");
		SetDefendTime("alarmout");
	}
}
function initAlarm()
{
	if(DVR_CH >8)
	{
		document.all.reRow3.style.display = "";
		document.all.reRow4.style.display = "";
	}
	lang = document.getElementById("lang").value;
	if(lang == 'cn')showTips("正在读取报警配置信息，请稍等.....")
	else showTips("Getting alarm information,please wait...")
	setTimeout("getalarmParameter()",10);
	setTimeout("hideTips()",20);	
}
function getalarmParameter()
{
	initalarmDefendTimetable();
	setOperator();
	getpara();
	InitBtSet();
	GetAIO();
	getAlarmInput();
	getAlarmOutput();
	getAlarmEx();	
}