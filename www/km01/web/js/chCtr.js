// JavaScript Document
//Set Network channel IP address
function GetCh()
{
	if(readcookie("channel")){
		ch = parseInt(getCookie("channel"));
		document.forms[0].Channel.selectedIndex = ch;
	}
	else{
		document.forms[0].Channel.selectedIndex = 0;	
	}
}
function SetCh()
{
	addcookie("channel="+document.forms[0].Channel.selectedIndex);
	parent.rightFrame.document.location.reload();
}
function DelCook()
{
	addcookie("channel=0");
}

//Motion Detection Setting
function onMotionDefend()
{
	setS_H("MotionDefendTime","MotionAlarmContact");
}
function onMotionContact()
{
	setS_H("MotionAlarmContact","MotionDefendTime");
}
function onTriggerOutput(name)
{
	if(!document.getElementById(name+"TriggerOutput").checked){
		for(i=1;i<=4;i++){
			document.getElementById(name+"TriggerOutput"+i).checked = false;
		}
	}
	for(i=1;i<=4;i++){
		document.getElementById(name+"TriggerOutput"+i).disabled = (document.getElementById(name+"TriggerOutput").checked)?false:true;	
	}
}

function SetPreset()
{
	if(document.ChInfoForm.preset.checked){
		document.ChInfoForm.PresetValue.disabled = false;
		if(document.ChInfoForm.PresetValue.value == "")
		{
			document.ChInfoForm.PresetValue.value = 1;	
		}
		document.ChInfoForm.cruise.checked = false;
		document.ChInfoForm.CruiseValue.value = "";
		SetCruise();
	}
	else{
		document.ChInfoForm.PresetValue.disabled = true;
	}
}

function SetCruise()
{
	if(document.ChInfoForm.cruise.checked){
		document.ChInfoForm.CruiseValue.disabled = false;
		if(document.ChInfoForm.CruiseValue.value == "")
		{
			document.ChInfoForm.CruiseValue.value = 1;	
		}
		document.ChInfoForm.preset.checked = false;
		document.ChInfoForm.PresetValue.value = "";
		SetPreset();
	}
	else{
		document.ChInfoForm.CruiseValue.disabled = true;
	}
}

//View obstruct control
function onObstructDefend()
{
	setS_H("ObsDefendTime","ObsHandleMethod");
}
function onObstructMethod()
{
	setS_H("ObsHandleMethod","ObsDefendTime");
}

//Sinal loss control
function onSigDefend()
{
	setS_H("SigDefendTime","SigHandleMethod");
}
function onSigMethod()
{
	setS_H("SigHandleMethod","SigDefendTime");
}
function setS_H(showId,hideId)
{
	document.getElementById(hideId).style.display = "none";
	document.getElementById(showId).style.display = (document.getElementById(showId).style.display=="none")?"":"none";
}
