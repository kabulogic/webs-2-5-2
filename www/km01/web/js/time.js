// JavaScript Document
/*全局变量***************************************************************************/
var SYN_NTP = 0x01;
var SYN_PC  = 0x02;
var SYN_TZ  = 0x03;
var intervalID;
/*************************************************************************************/

/**************************************************************************************
*初始化时间显示页面
**************************************************************************************/
function timeIndex()
{
	TimezoneIndex();
	PCTimeIndex();
	NTPIndex();
}

/**************************************************************************************
*时区设置
**************************************************************************************/
function TimezoneIndex()
{
	var bDayLight = parseInt(document.getElementById("daylightenble").value);
	document.getElementById("tzSelect").selectedIndex = parseInt(document.getElementById("tzvalue").value);
	document.getElementById("cbDaylight").checked = bDayLight ? true : false;
}

function setTimezone()
{
	document.getElementById("flag").value = SYN_TZ;
	document.getElementById("tzvalue").value = document.getElementById("tzSelect").selectedIndex;
	if(document.getElementById("cbDaylight").checked)
	{
		document.getElementById("daylightenble").value = 1;	
	}
	else
	{
		document.getElementById("daylightenble").value = 0;	
	}
	PCTimeIndex();
}

/**************************************************************************************
*NVR对时为PC机时间
**************************************************************************************/
function PCTimeIndex()
{
	document.timeFrame.location.reload();
	intervalID = setInterval("getPCTime()",50);
	//setTimeout("PCTimeIndex()",1000);//由于时刻获取时间底层日志写得过多，故网页只有刷新页面才更新时间
}

function getPCTime()
{
	try
	{
		thistime = document.timeFrame.document.getElementById("timePC").value;
		document.getElementById("PC_Time").value = thistime;
		clearInterval(intervalID);
	}catch(e)
	{}
}

function tzindex(tz)
{
	var reValue = 0;
	switch(tz)
	{
		case -720: reValue = 0;  break;
		case -660: reValue = 1;  break;
		case -600: reValue = 2;  break;
		case -540: reValue = 3;  break;
		case -480: reValue = 4;  break;
		case -420: reValue = 5;  break;
		case -360: reValue = 6;  break;
		case -300: reValue = 7;  break;
		case -240: reValue = 8;  break;
		case -210: reValue = 9;  break;
		case -180: reValue = 10; break;
		case -120: reValue = 11; break;
		case -60:  reValue = 12; break;
		case 0:    reValue = 13; break;
		case 60:   reValue = 14; break;
		case 120:  reValue = 15; break;
		case 180:  reValue = 16; break;
		case 210:  reValue = 17; break;
		case 240:  reValue = 18; break;
		case 270:  reValue = 19; break;
		case 300:  reValue = 20; break;
		case 330:  reValue = 21; break;
		case 345:  reValue = 22; break;
		case 360:  reValue = 23; break;
		case 390:  reValue = 24; break;
		case 420:  reValue = 25; break;
		case 480:  reValue = 26; break;
		case 540:  reValue = 27; break;
		case 570:  reValue = 28; break;
		case 600:  reValue = 29; break;
		case 660:  reValue = 30; break;
		case 720:  reValue = 31; break;
		case 780:  reValue = 32; break;
		default :  reValue = 26; break;
	}	
	return reValue;
}

function setLocalTime()
{
	var now = new Date();
	document.getElementById("localtime").value = parseInt(now.getTime()/1000);
	/*getTimezoneOffset返回的是标准时间与本地时间差(分钟)*/
	//document.getElementById("tzvalue").value = tzindex(0-now.getTimezoneOffset());
	document.getElementById("flag").value = SYN_PC;
	document.timeSetCfg.submit();
	//document.getElementById("tzSelect").selectedIndex = parseInt(document.getElementById("tzvalue").value);
	PCTimeIndex();
}

/**************************************************************************************
*NTP设置
**************************************************************************************/
function checkIP(obj) 
{ 
	var lang = document.getElementById("lang").value;//获取语言类型
	if(!isIP(obj))
	{
		(lang == "cn") ? alert("NTP IP不合法!") : alert("NTP IP is invalid!");
	}
} 

function NTPChecked()
{
	if(document.getElementById("chkntp").checked)
	{
		document.getElementById("NTP_State").value = 1;
		document.getElementById("ntpIP").disabled = false;
	}	
	else
	{
		document.getElementById("NTP_State").value = 0;
		document.getElementById("ntpIP").disabled = true;
	}
}

function NTPIndex()
{
	var state = document.getElementById("NTP_State").value;
	document.getElementById("ntpIP").value = document.getElementById("NTP_IP").value;
	if(state == 1)
	{
		document.getElementById("chkntp").checked = true;
		document.getElementById("ntpIP").disabled = false;
	}
	else
	{
		document.getElementById("chkntp").checked = false;
		document.getElementById("ntpIP").disabled = true;
	}
}

function setNTP()
{
	NTPChecked();
	document.getElementById("flag").value = SYN_NTP;
	document.getElementById("NTP_IP").value = document.getElementById("ntpIP").value;
	document.timeSetCfg.submit();
	PCTimeIndex();
}