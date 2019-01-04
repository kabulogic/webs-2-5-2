// JavaScript Document
function major_minor()
{
	var type = document.RecordForm.StreamType.selectedIndex;
	initOption(type);
	switch(type){
		case 0:
			getMajorMinorCfg("major");
			break;
		case 1:
			getMajorMinorCfg("minor");
			break;
		default:break;
	}
}
function initOption(type)
{
	var obj=document.RecordForm.Resolution;
	obj.options.length=0;
	if(type != 0){
		obj.options.add(new Option("QCIF","0"));
		if(document.getElementById("Resolution_major").value != "0")
		{
			obj.options.add(new Option("CIF","1"));
		}
	}
	else{
		obj.options.add(new Option("QCIF","0"));
		obj.options.add(new Option("CIF","1"));
		obj.options.add(new Option("2CIF","2"));
		obj.options.add(new Option("4CIF","3"));
	}
	obj.selectedIndex = 0;
}
function getMajorMinorCfg(type)
{
	var vMode = document.getElementById('VideoMode').value;
	try{
		var key = document.getElementById("VOPRate_"+type).value;//choose(document.getElementById("VOPRate_"+type).value,values);
		switch(parseInt(key))
		{
			case 1:
				document.RecordForm.framerateSelect.selectedIndex = 0;
				break;
			case 2:
				document.RecordForm.framerateSelect.selectedIndex = 1;
				break;
			case 4:
				document.RecordForm.framerateSelect.selectedIndex = 2;
				break;
			case 8:
				document.RecordForm.framerateSelect.selectedIndex = 3;
				break;
			case 15:
				document.RecordForm.framerateSelect.selectedIndex = 4;
				break;
			case 20:
				document.RecordForm.framerateSelect.selectedIndex = 5;
				break;
			case 30:
				document.RecordForm.framerateSelect.selectedIndex = 6;
				break;
			case 25:
			case 26:
			case 27:
			case 28:
			case 29:
				if(vMode == 1)
				{
					document.RecordForm.framerateSelect.selectedIndex = 6;
					break;
				}
			default:
				document.RecordForm.framerateSelect.selectedIndex = 0xff;
				break;
		}		
		
		var VOPRateDisplay = document.getElementById("VOPRate_"+type).value;
		if(((vMode == 1) && (parseInt(VOPRateDisplay) >=25)) || ((vMode == 2) && (parseInt(VOPRateDisplay) == 30)))
		{
			document.RecordForm.VOPRateDisplay.value = "P25/N30";
		}
		else
		{
			document.RecordForm.VOPRateDisplay.value = document.getElementById("VOPRate_"+type).value;
		}
		
		document.RecordForm.IPRate.value = document.getElementById("IPRate_"+type).value;
		
		if(document.getElementById("BitRate_"+type).value == "0"){
			document.RecordForm.BitRateType.selectedIndex = 0;
		}
		else{
			document.RecordForm.BitRateType.selectedIndex = 1;
		}
		
		switch(document.getElementById("Quality_"+type).value)
		{
			case "0":
				document.RecordForm.ImageQuality.selectedIndex = 0;
				break;
			case "1":
				document.RecordForm.ImageQuality.selectedIndex = 1;
				break;
			case "2":
				document.RecordForm.ImageQuality.selectedIndex = 2;
				break;
			case "3":
				document.RecordForm.ImageQuality.selectedIndex = 3;
				break;
			case "4":
				document.RecordForm.ImageQuality.selectedIndex = 4;
				break;
			default:
				document.RecordForm.ImageQuality.selectedIndex = 2;
				break;
		}
		if(type == "major")
		{
			switch(document.getElementById("Resolution_major").value){
				case "3":
					document.RecordForm.Resolution.selectedIndex = 3;
					break;
				case "2":
					document.RecordForm.Resolution.selectedIndex = 2;
					break;
				case "1":
					document.RecordForm.Resolution.selectedIndex = 1;
					break;
				case "0":
					document.RecordForm.Resolution.selectedIndex = 0;
					break;
				default:
					document.RecordForm.Resolution.selectedIndex = 3;
					break;
			}
		}
		else
		{
			if((document.getElementById("Resolution_minor").value == "1") && (document.getElementById("Resolution_major").value != "0"))
			{
				document.RecordForm.Resolution.selectedIndex = 1;
			}
			else
			{
				document.RecordForm.Resolution.selectedIndex = 0;
			}
		}
		values = new Array(256,512,640,768,896,1024,1280,1536,1792,2048,2560); 
		key = choose(document.getElementById("MaxBitRate_"+type).value,values);
		switch(key){
			case 256:
				document.RecordForm.MaxBitRate.selectedIndex = 0;
				break;
			case 512:
				document.RecordForm.MaxBitRate.selectedIndex = 1;
				break;
			case 640:
				document.RecordForm.MaxBitRate.selectedIndex = 2;
				break;
			case 768:
				document.RecordForm.MaxBitRate.selectedIndex = 3;
				break;
			case 896:
				document.RecordForm.MaxBitRate.selectedIndex = 4;
				break;
			case 1024:
				document.RecordForm.MaxBitRate.selectedIndex = 5;
				break;
			case 1280:
				document.RecordForm.MaxBitRate.selectedIndex = 6;
				break;
			case 1536:
				document.RecordForm.MaxBitRate.selectedIndex = 7;
				break;
			case 1792:
				document.RecordForm.MaxBitRate.selectedIndex = 8;
				break;
			case 2048:
				document.RecordForm.MaxBitRate.selectedIndex = 9;
				break;
			case 2560:
				document.RecordForm.MaxBitRate.selectedIndex = 10;
				break;
			default:
				document.RecordForm.MaxBitRate.selectedIndex = 0;
				break;
		}
		if(document.getElementById("MixStream_"+type).value == "1"){
			document.RecordForm.MixStream.selectedIndex = 1;
		}
		else{
			document.RecordForm.MixStream.selectedIndex = 0;
		}
	}catch(e){}
}

function getRecord()
{
	try{
	if(document.RecordForm.Record_OnOff.value == "1"){//on
		document.RecordForm.RecordSetting.selectedIndex = 0;
	}
	else{
		document.RecordForm.RecordSetting.selectedIndex = 1;
	}
	/*switch(document.RecordForm.Record_To.value){
		case "1":
			document.RecordForm.RecordTo.selectedIndex = 0;
			break;
		case "2":
			document.RecordForm.RecordTo.selectedIndex = 1;
			break;
		case "3":
			document.RecordForm.RecordTo.selectedIndex = 2;
			break;
		default:
			document.RecordForm.RecordTo.selectedIndex = 0;
			break;
	}*/
	var values = new Array(0,2,4,6,8,255); 
	var key = choose(document.RecordForm.Record_Prt.value,values);
	switch(key){
		case 0:
			document.RecordForm.PreTime.selectedIndex = 0;
			break;
		//case 1:
			//document.RecordForm.PreTime.selectedIndex = 1;
			//break;
		case 2:
			document.RecordForm.PreTime.selectedIndex = 1;
			break;
		case 4:
			document.RecordForm.PreTime.selectedIndex = 2;
			break;
		case 6:
			document.RecordForm.PreTime.selectedIndex = 3;
			break;
		case 8:
			document.RecordForm.PreTime.selectedIndex = 4;
			break;
		//case 10:
			//document.RecordForm.PreTime.selectedIndex = 6;
			//break;
		default:
			document.RecordForm.PreTime.selectedIndex = 5;
			break;
	}
	values = new Array(0,5,10,30,60,120,300,600); 
	key = choose(document.RecordForm.Record_Drt.value,values);
	switch(key){
		case 0:
			document.RecordForm.PostTime.selectedIndex = 0;
			break;
		case 5:
			document.RecordForm.PostTime.selectedIndex = 1;
			break;
		case 10:
			document.RecordForm.PostTime.selectedIndex = 2;
			break;
		case 30:
			document.RecordForm.PostTime.selectedIndex = 3;
			break;
		case 60:
			document.RecordForm.PostTime.selectedIndex = 4;
			break;
		case 120:
			document.RecordForm.PostTime.selectedIndex = 5;
			break;
		case 300:
			document.RecordForm.PostTime.selectedIndex = 6;
			break;
		case 600:
			document.RecordForm.PostTime.selectedIndex = 7;
			break;
		default:
			document.RecordForm.PostTime.selectedIndex = 0;
			break;
	}
	getRecordPlan();
	}catch(e){}
}

function SetbackRecordDayPlan()
{
	if(period("RecPlan"))
	{
		setObjectByName("isRecordPlanChange","1");
		SetRecordplanByDay(document.RecordForm.RecordBackWeek.value);
	}
}

function CopyRecordPlan()
{
	if(period("RecPlan")){
		setObjectByName("isRecordPlanChange","1");
		switch(document.RecordForm.RecPlanCopy.selectedIndex){
			case 0:
				SetRecordplanByDay("Mon");
				SetRecordplanByDay("Tue");
				SetRecordplanByDay("Wed");
				SetRecordplanByDay("Thu");
				SetRecordplanByDay("Fri");
				SetRecordplanByDay("Sat");
				SetRecordplanByDay("Sun");
				break;
			case 1:
				SetRecordplanByDay("Mon");
				break;
			case 2:
				SetRecordplanByDay("Tue");
				break;
			case 3:
				SetRecordplanByDay("Wed");
				break;
			case 4:
				SetRecordplanByDay("Thu");
				break;
			case 5:
				SetRecordplanByDay("Fri");
				break;
			case 6:
				SetRecordplanByDay("Sat");
				break;
			case 7:
				SetRecordplanByDay("Sun");
				break;
		}
	}
}

function initRecord()
{
	lang = document.getElementById("lang").value;
	if(lang == 'cn')showTips("正在读取录像配置信息，请稍等.....")
	else showTips("Getting record information,please wait...")
	setTimeout("getrecordParameter()",10);
	setTimeout("hideTips()",20);
}

function getrecordParameter()
{
	initrecordPlantable();
	setOperator();
	getpara();
	InitBtSet();
	GetCh();
	major_minor();
	getRecord();
}