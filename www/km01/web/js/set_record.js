// JavaScript Document
var bCopy = false;
function setRecordCfg()
{
	//var err = getCookie("seterror=")
	//if(err == 1) return;
	var flag = document.RecordForm.flag.value;
	
	setRecordParaIndex(document.RecordForm.StreamType.selectedIndex);
	//major info change
	if(document.RecordForm.StreamType.selectedIndex == 0)
	{
		document.getElementById("Stream_major").value = "0";
		flag |= 0x0002;
	}
	else
	{//minor info change  
		document.getElementById("Stream_minor").value = "1";
		flag |= 0x0004;
	}
	//Record
	if( compare(document.RecordForm.RecordSetting,document.getElementById("Record_OnOff")) || compare(document.RecordForm.PreTime,document.getElementById("Record_Prt")) || compare(document.RecordForm.PostTime,document.getElementById("Record_Drt")) ||(document.RecordForm.isRecordPlanChange.value == "1") )
	{
		flag |= 0x0400;
		SetRecordPlan();
		setObjectByName("isRecordPlanChange","0");
	}
	if(bCopy)
	{
		if(document.RecordForm.Channel.selectedIndex != document.RecordForm.CopyRe.selectedIndex)
		{
			//copy record info to another channel
			flag |= 0x2000;
			//save record plan to middle variable
			SetRecordPlan();
		}
	}
	document.RecordForm.flag.value = flag;
	if(flag != 0){
		document.RecordForm.submit();
	}
	document.RecordForm.flag.value = 0;
	bCopy = false;
}

function OnReCopy()
{
	bCopy = true;
}

function FrameRateSwitch()
{
	var index = document.getElementById("framerateSelect").selectedIndex;
	switch(index)
	{
		case 0:
			document.getElementById('VOPRateDisplay').value = 1;
			break;
		case 1:
			document.getElementById('VOPRateDisplay').value = 2;
			break;
		case 2:
			document.getElementById('VOPRateDisplay').value = 4;
			break;
		case 3:
			document.getElementById('VOPRateDisplay').value = 8;
			break;
		case 4:
			document.getElementById('VOPRateDisplay').value = 15;
			break;
		case 5:
			document.getElementById('VOPRateDisplay').value = 20;
			break;
		case 6:
		default:
			document.getElementById('VOPRateDisplay').value = "P25/N30";
			break;
	}
	if(document.getElementById("VOPRateDisplay").value == "P25/N30")
	{
		 document.getElementById('VOPRate').value = "30";
	}
	else
	{
		document.getElementById('VOPRate').value = document.getElementById("VOPRateDisplay").value;
	}
}
		
function setRecordParaIndex(Mtype)
{
	if(Mtype == 0) type = "major";
	else type = "minor";
	if(type == "major"){
			switch(document.RecordForm.Resolution.selectedIndex){
				case 3:
					document.getElementById("Resolution_major").value = "3";
					break;
				case 2:
					document.getElementById("Resolution_major").value = "2";
					break;
				case 1:
					document.getElementById("Resolution_major").value = "1";
					break;
				case 0:
					document.getElementById("Resolution_major").value = "0";
					break;
				default:
					document.getElementById("Resolution_major").value = "3";
					break;
			}
		}
		else{
			if(document.RecordForm.Resolution.selectedIndex == 0)
			{
				document.getElementById("Resolution_minor").value = "0";
			}
			else
			{
				document.getElementById("Resolution_minor").value = "1";
			}
		}

	if(document.RecordForm.MixStream.selectedIndex == 1)
	{
		document.getElementById("MixStream_"+type).value = "1";
	}
	else
	{
		document.getElementById("MixStream_"+type).value = "0";
	}
		
	if(document.RecordForm.BitRateType.selectedIndex == 0)
	{	
		document.getElementById("BitRate_"+type).value = "0";
	}
	else
	{
		document.getElementById("BitRate_"+type).value = "1";
	}
		
	switch(document.RecordForm.ImageQuality.selectedIndex)
	{
		case 0:
			document.getElementById("Quality_"+type).value = "0";
			break;
		case 1:
			document.getElementById("Quality_"+type).value = "1";
			break;
		case 2:
			document.getElementById("Quality_"+type).value = "2";
			break;
		case 3:
			document.getElementById("Quality_"+type).value = "3";
			break;
		case 4:
			document.getElementById("Quality_"+type).value = "4";
			break;
		default:
			document.getElementById("Quality_"+type).value = "2";
			break;
	}
		
	switch(document.getElementById("MaxBitRate").selectedIndex)
	{
		case 0:
			document.getElementById("MaxBitRate_"+type).value = "256";
			break;
		case 1:
			document.getElementById("MaxBitRate_"+type).value = "512";
			break;
		case 2:
			document.getElementById("MaxBitRate_"+type).value = "640";
			break;
		case 3:
			document.getElementById("MaxBitRate_"+type).value = "768";
			break;
		case 4:
			document.getElementById("MaxBitRate_"+type).value = "896";
			break;
		case 5:
			document.getElementById("MaxBitRate_"+type).value = "1024";
			break;
		case 6:
			document.getElementById("MaxBitRate_"+type).value = "1280";
			break;
		case 7:
			document.getElementById("MaxBitRate_"+type).value = "1536";
			break;
		case 8:
			document.getElementById("MaxBitRate_"+type).value = "1792";
			break;
		case 9:
			document.getElementById("MaxBitRate_"+type).value = "2048";
			break;
		case 10:
			document.getElementById("MaxBitRate_"+type).value = "2560";
			break;
		default:
			document.getElementById("MaxBitRate_"+type).value = "256";
			break;
	}
		
		if(document.getElementById("VOPRateDisplay").value == "P25/N30")
		{
			document.RecordForm.VOPRate.value = 30;	
		}
		else
		{
			document.RecordForm.VOPRate.value = document.getElementById("VOPRateDisplay").value;
		}
		document.getElementById("VOPRate_"+type).value = document.RecordForm.VOPRate.value;
		document.getElementById("IPRate_"+type).value = document.RecordForm.IPRate.value ;
}