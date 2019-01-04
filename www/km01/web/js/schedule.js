/*********************
schedule basic function
**********************/
function getDefendTime(obj)
{
	for(i=0;i<7;i++)
	{
		for(j=0;j<48;j++)
		{
			var tmp =i*48+j ;
			if(obj == 'sig' || obj == 'alarmin') tmpbt = tmp
			if(obj == 'obs' || obj == 'alarmout') tmpbt =(i+7)*48+j
			if(obj == 'motion') tmpbt =(i+14)*48+j
			if(document.getElementById(obj+tmp).value != 0)
				document.getElementById(tmpbt).style.background = "green";
			else document.getElementById(tmpbt).style.background = "white";
		}
	}
}

function getRecordPlan()
{
	for(i=0;i<7;i++)
	{
		for(j=0;j<48;j++)
		{
			var tmp =i*48+j ;
			switch(document.getElementById("rec"+tmp).value)
			{
				case '1':
					document.getElementById(tmp).style.background = "green";
					break;
				case '3':
					document.getElementById(tmp).style.background = "red";
					break;
				case '5':
					document.getElementById(tmp).style.background = "blue";
					break;
				default:
					document.getElementById(tmp).style.background = "white";
					break;
			}	
		}
	}
}


function HandleMethod(name)
{
	//Linkage
	try{
	if(document.getElementById(name+"Monitor").value == "1"){
		document.getElementById(name+"TriggerMonitor").checked = true;
	}
	else{
		document.getElementById(name+"TriggerMonitor").checked = false;
	}
	if(document.getElementById(name+"Voice").value == "1"){
		document.getElementById(name+"TriggerVoice").checked = true;
	}
	else{
		document.getElementById(name+"TriggerVoice").checked = false;
	}
	if(document.getElementById(name+"Center").value == "1"){
		document.getElementById(name+"TriggerCenter").checked = true;
	}
	else{
		document.getElementById(name+"TriggerCenter").checked = false;
	}
	if((document.getElementById(name+"Trigger1").value == "1") || (document.getElementById(name+"Trigger2").value == "1") || (document.getElementById(name+"Trigger3").value == "1") || (document.getElementById(name+"Trigger4").value == "1")){
		document.getElementById(name+"TriggerOutput").checked = true;
		if(document.getElementById(name+"Trigger1").value == "1"){
			document.getElementById(name+"TriggerOutput1").checked = true;
		}
		else{
			document.getElementById(name+"TriggerOutput1").checked = false;
		}
		if(document.getElementById(name+"Trigger2").value == "1"){
			document.getElementById(name+"TriggerOutput2").checked = true;
		}
		else{
			document.getElementById(name+"TriggerOutput2").checked = false;
		}
		if(document.getElementById(name+"Trigger3").value == "1"){
			document.getElementById(name+"TriggerOutput3").checked = true;
		}
		else{
			document.getElementById(name+"TriggerOutput3").checked = false;
		}
		if(document.getElementById(name+"Trigger4").value == "1"){
			document.getElementById(name+"TriggerOutput4").checked = true;
		}
		else{
			document.getElementById(name+"TriggerOutput4").checked = false;
		}
	}
	else{
		document.getElementById(name+"TriggerOutput").checked = false;
	}
	onTriggerOutput(name);
	}catch(e){}
}

function SetDefendTime(type)
{
	for(i=0;i<7;i++)
	{
		for(j=0;j<48;j++)
		{
			tmp = i*48+j
			if(type == 'sig' || type == 'alarmin') tmpbt = i*48+j
			if(type == 'obs' || type == 'alarmout') tmpbt =(i+7)*48+j
			if(type == 'motion') tmpbt =(i+14)*48+j
			if(document.getElementById(tmpbt).style.background == "green")
			{
				document.getElementById(type+tmp).value = 1;
			}
			else document.getElementById(type+tmp).value = 0;
		}
	}
}

function SetRecordPlan()
{
	for(i=0;i<7;i++)
	{
		for(j=0;j<48;j++)
		{
			tmp = i*48+j;
			switch(document.getElementById(tmp).style.background)
			{
				case 'green':
					document.getElementById("rec"+tmp).value =1;
					break;
				case 'red':
					document.getElementById("rec"+tmp).value =3;
					break;
				case 'blue':
					document.getElementById("rec"+tmp).value =5;
					break;
				default:
					document.getElementById("rec"+tmp).value =0;
					break;
			}	
		}
	}
}


/********Get On/Off of View Obstruct, Signal Loss, Motion Det.*******/
function getHandleOnOff(name)
{
	if(document.getElementById(name+"On").value == "1"){
		document.getElementById(name+"Enable").checked = true;
	}
	else{
		document.getElementById(name+"Enable").checked = false;
	}
}