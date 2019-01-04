var DVR_CH = getDVR_CH();
//Alarm Input Output Setting
function onDefend()
{
	if(document.AlarmForm.HandleDefend.checked){
		document.AlarmForm.HandleContact.checked = false;
		document.all.DefendTime.style.display = "";
		document.all.AlarmContact.style.display = "none";
	}
	else{
		document.all.DefendTime.style.display = "none";
	}
}
function onAlarmContact()
{
	if(document.AlarmForm.HandleContact.checked){
		document.AlarmForm.HandleDefend.checked = false;
		document.all.DefendTime.style.display = "none";
		document.all.AlarmContact.style.display = "";
	}
	else{
		document.all.AlarmContact.style.display = "none";
	}
}
function onInTriggerOutput()
{
	if(document.AlarmForm.InTriggerOutput.checked){
		document.AlarmForm.InTriggerOutput1.disabled = false;
		document.AlarmForm.InTriggerOutput2.disabled = false;
		document.AlarmForm.InTriggerOutput3.disabled = false;
		document.AlarmForm.InTriggerOutput4.disabled = false;
	}
	else{
		document.AlarmForm.InTriggerOutput1.checked = false;
		document.AlarmForm.InTriggerOutput2.checked = false;
		document.AlarmForm.InTriggerOutput3.checked = false;
		document.AlarmForm.InTriggerOutput4.checked = false;
		document.AlarmForm.InTriggerOutput1.disabled = true;
		document.AlarmForm.InTriggerOutput2.disabled = true;
		document.AlarmForm.InTriggerOutput3.disabled = true;
		document.AlarmForm.InTriggerOutput4.disabled = true;
	}
}
function onTriggerRecordChan(name,key)
{
	var i;
	for(i=1;i<=DVR_CH;i++){
		if(key == 1)
			document.getElementById(name+i).checked = true;
		else if(key == 0)
			document.getElementById(name+i).checked = false;
	}
}

function onExTriggerOutput()
{
	if(document.AlarmForm.ExTriggerOutput.checked){
		document.AlarmForm.ExTriggerOutput1.disabled = false;
		document.AlarmForm.ExTriggerOutput2.disabled = false;
		document.AlarmForm.ExTriggerOutput3.disabled = false;
		document.AlarmForm.ExTriggerOutput4.disabled = false;
	}
	else{
		document.AlarmForm.ExTriggerOutput1.disabled = true;
		document.AlarmForm.ExTriggerOutput2.disabled = true;
		document.AlarmForm.ExTriggerOutput3.disabled = true;
		document.AlarmForm.ExTriggerOutput4.disabled = true;
	}
}

function SetPreset()
{
	if(document.AlarmForm.preset.checked){
		document.AlarmForm.PresetValue.disabled = false;
		if(document.AlarmForm.PresetValue.value == "")
		{
			document.AlarmForm.PresetValue.value = 1;	
		}
		document.AlarmForm.cruise.checked = false;
		document.AlarmForm.CruiseValue.value = "";
		SetCruise();
	}
	else{
		document.AlarmForm.PresetValue.disabled = true;
	}
}

function SetCruise()
{
	if(document.AlarmForm.cruise.checked){
		document.AlarmForm.CruiseValue.disabled = false;
		if(document.AlarmForm.CruiseValue.value == "")
		{
			document.AlarmForm.CruiseValue.value = 1;	
		}
		document.AlarmForm.preset.checked = false;
		document.AlarmForm.PresetValue.value = "";
		SetPreset();
	}
	else{
		document.AlarmForm.CruiseValue.disabled = true;
	}
}