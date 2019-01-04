// JavaScript Document
var xmlhttp= null;
var timerIDAlarm = null;
var reqTime = 2000;
var browser_IE=false, browser_Netscape=false, browser_FireFox=false;
function SendHttp(url,isAsync,callBack)
{

	isAsync=new Boolean(isAsync);
	xmlhttp=null;
	xmlhttp=InitXHttp();
	if(callBack!=null){
		xmlhttp.onreadystatechange=callBack;
	}
//	else{
//		xmlhttp.onreadystatechange=OnExceptionProcess;
//	}
	try{
		xmlhttp.open("GET",url,isAsync);
		xmlhttp.setRequestHeader("If-Modified-Since","0");
		xmlhttp.send(null);
	}catch(e){};
}
function OnExceptionProcess()
{
	if(xmlhttp.readyState==4){
		if(xmlhttp.status!=200){
			timerIDAlarm=setTimeout("InitPage()",reqTime);
		}
	}
}
function InitXHttp()
{
	var xhttp=null;
	if(IsMozilla()){
		xhttp=new XMLHttpRequest();
		if(xhttp.overrideMimeType){
			xhttp.overrideMimeType('text/xml');
		}
	}
	else if(browser_IE){
		try{
			xhttp=new ActiveXObject("Msxml2.XMLHTTP");
		}catch(e){
			try{
				xhttp=new ActiveXObject("Microsoft.XMLHTTP");
			}catch(e){};
		}
	}
	return xhttp;
}
function IsMozilla()
{
	if(window.ActiveXObject)
	{
		browser_IE=true;
	}
	else if(document.layers)
	{
		browser_Netscape=true;
	}
	else
	{
		browser_FireFox=true;
	}
	return(browser_Netscape||browser_FireFox);
}
function InitPage()
{
	var user = parent.parent.topFrame.document.operator.user.value;
	SendHttp("/infinova/getUserPri?user="+user,false,SendOK);
}
function SendOK()
{
	if(xmlhttp.readyState==4)
	{
		if(xmlhttp.status==200)
		{
			var txt=xmlhttp.responseText;
			var P=txt.indexOf("P=0");
			if(P != -1) document.UserInfo.priP.value = 0;
			else document.UserInfo.priP.value = 1;
			
			var S=txt.indexOf("S=0");
			if(S != -1) document.UserInfo.priS.value = 0;
			else document.UserInfo.priS.value = 1;
			
			var D=txt.indexOf("D=0");
			if(D != -1) document.UserInfo.priD.value = 0;
			else document.UserInfo.priD.value = 1;
			
			var N=txt.indexOf("N=0");
			if(N != -1) document.UserInfo.Chn.value = 8;
			else document.UserInfo.Chn.value = 16;
		}
		else if (xmlhttp.status == 404)
		{
         	alert("Request URL does not exist");
		}
	}
}
