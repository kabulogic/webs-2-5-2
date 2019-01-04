// JavaScript Document
var DVR_CH = getDVR_CH();
function initVideoTable(content)
{
	for(i=1;i<=DVR_CH;i++)
	{
		id1 = "v" + i;
		id2 = "r" + i;
		id3 = "a" + i;
		
		R = Page1.insertRow();
		R.style.cssText="height:25px;";
		C1=R.insertCell(); 
		C1.style.cssText="width:164px;font-weight: bold;";  
		if(i<10)
		{
			C1.innerText = content+"0" + i;
		}
		else
		{
			C1.innerText = content + i;
		}
		
		C2 = R.insertCell();
		C2.style.cssText="width:210px;";  
		C2.innerHTML="<label id='"+id1+"' ></label>" ;
		
		C3 = R.insertCell();
		C3.style.cssText="width:232px;";  
		C3.innerHTML="<label id='"+id2+"' ></label>" ;
		
		C4 = R.insertCell();
		C4.style.cssText="width:232px;";  
		C4.innerHTML="<label id='"+id3+"' ></label>" ;
	}
}

function initDVRInfo()
{
	try{
		document.all.ServerName.innerText = document.dvrInfo.Name.value;
		document.all.ServerID.innerText = document.dvrInfo.ID.value;
		document.all.SerialId.innerText = document.dvrInfo.SN.value;
		if(document.dvrInfo.DecVer.value)
			document.all.DecodeVer.innerText = document.dvrInfo.DecVer.value;
		if(document.dvrInfo.HWVer.value)
			document.all.HardwareVer.innerText = document.dvrInfo.HWVer.value;
		if(document.dvrInfo.SWVer.value)
			document.all.SoftwareVer.innerText = document.dvrInfo.SWVer.value;
		document.all.ChanNum.innerText = document.dvrInfo.ChNum.value;
		document.all.HardiskNum.innerText = document.dvrInfo.HDNum.value;
	}catch(e){}
}
function onPageUp()
{
	if(tb1.style.display == ""){
		return;
	}
	if(tb2.style.display == ""){
		tb2.style.display = "none";
		tb1.style.display = "";
	}
}
function onPageDown()
{
	if(tb2.style.display == ""){
		return;
	}
	if(tb1.style.display == ""){
		tb1.style.display = "none";
		tb2.style.display = "";
	}
}

var timeID = null;
function startGet()
{
	initRecSta();
}
function stopGet()
{
	clearTimeout(timeID);
}
function initRecSta()
{
	var lang = document.RecSta.lang.value;
	try{
	initVideo(lang);
	initRecord(lang);
	initAlarm(lang);
	document.status.location.reload();
	}catch(e){}
	timeID = setTimeout("initRecSta()",5000);
}
function initVideo(lang)
{
	for(i=0;i<DVR_CH;i++){
		j = i+1;
		vlost = document.status.document.getElementById("vlost"+i).value;
		if(lang == "cn"){
			if(vlost == "0") document.getElementById("v"+j).innerText = "正常";
			else document.getElementById("v"+j).innerText = "无"; //=="1"
		}
		else{//lang == "en"
			if(vlost == "0") document.getElementById("v"+j).innerText = "OK";
			else document.getElementById("v"+j).innerText = "No";
		}
	}
}
function initRecord(lang)
{
	for(i=0;i<DVR_CH;i++){
		j = i+1;
		vsta = document.status.document.getElementById("vsta"+i).value;
		if(lang == "cn"){
			if(vsta == "1") document.getElementById("r"+j).innerText = "定时";
			else if(vsta == "2") document.getElementById("r"+j).innerText = "手动";
			else if(vsta == "3") document.getElementById("r"+j).innerText = "报警";
			else document.getElementById("r"+j).innerText = "无"; //== "0"
		}
		else{
			if(vsta == "1") document.getElementById("r"+j).innerText = "Time";
			else if(vsta == "2") document.getElementById("r"+j).innerText = "Manual";
			else if(vsta == "3") document.getElementById("r"+j).innerText = "Alarm";
			else document.getElementById("r"+j).innerText = "No";
		}
	}
}
function initAlarm(lang)
{
	for(i=0;i<DVR_CH;i++){
		j = i+1;
		ala = document.status.document.getElementById("ala"+i).value;
		if(lang == "cn"){
			if(ala == "1") document.getElementById("a"+j).innerText = "视频丢失";
			else if(ala == "2") document.getElementById("a"+j).innerText = "移动侦测";
			else if(ala == "4") document.getElementById("a"+j).innerText = "遮挡报警";
			else if(ala == "8") document.getElementById("a"+j).innerText = "输入量";
			else document.getElementById("a"+j).innerText = "无"; //== "0"
		}
		else{
			if(ala == "1") document.getElementById("a"+j).innerText = "Lost";
			else if(ala == "2") document.getElementById("a"+j).innerText = "Motion";
			else if(ala == "4") document.getElementById("a"+j).innerText = "Obstruct";
			else if(ala == "8") document.getElementById("a"+j).innerText = "Alarm Input";
			else document.getElementById("a"+j).innerText = "No";
		}
	}
}