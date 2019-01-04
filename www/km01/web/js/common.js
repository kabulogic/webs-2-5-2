// JavaScript Document
function setOperator()
{
	try{
	var user = parent.parent.topFrame.document.operator.user.value;
	var len = document.forms.length;
	for(i=0;i<len;i++){
		document.forms[i].operator.value = user;
	}
	}catch(e){}
}

function getWeekday()
{
	var d = new Date();
	var day = d.getDay();
	return day;
}

function MM_reloadPage(init) {  //reloads the window if Nav4 resized
  if (init==true) with (navigator) {if ((appName=="Netscape")&&(parseInt(appVersion)==4)) {
    document.MM_pgW=innerWidth; document.MM_pgH=innerHeight; onresize=MM_reloadPage; }}
  else if (innerWidth!=document.MM_pgW || innerHeight!=document.MM_pgH) location.reload();
}

function getParaPri()
{
	return parent.leftFrame.document.UserInfo.priP.value;
}

function getSysPri()
{
	return parent.leftFrame.document.UserInfo.priS.value;
}
function getDataPri()
{
	return parent.leftFrame.document.UserInfo.priD.value;
}
function getDVR_CH()
{
	try{
	return parent.leftFrame.document.UserInfo.Chn.value;
	}catch(e){}
}
function InitBtSet()
{
	if(getParaPri() == 0){
		if(document.forms[0].button) document.forms[0].button.disabled = true;
		if(document.forms[0].ChCopyBt) document.forms[0].ChCopyBt.disabled = true;
		if(document.forms[0].ReCopyBt) document.forms[0].ReCopyBt.disabled = true;
		if(document.forms[0].ComCopyBt) document.forms[0].ComCopyBt.disabled = true;
		if(document.forms[0].AlarmInputCopyBt) document.forms[0].AlarmInputCopyBt.disabled = true;
		if(document.forms[0].AlarmOutputCopyBt) document.forms[0].AlarmOutputCopyBt.disabled = true;
		if(document.forms[0].AlarmExCopyBt) document.forms[0].AlarmExCopyBt.disabled = true;
		if(document.forms[0].AlarmExCopyBt) document.forms[0].AlarmExCopyBt.disabled = true;
	}
}

function InitAdvanceSet()
{
	if(getSysPri() == 0)
	{
		if(document.forms[0].ftpSet) document.forms[0].ftpSet.disabled = true;
		if(document.forms[2].bootSet) document.forms[2].bootSet.disabled = true;
		if(document.forms[4].configInButton) document.forms[4].configInButton.disabled = true;
		if(document.forms[5].configOutButton) document.forms[5].configOutButton.disabled = true;
	}
	if((getParaPri() == 0) || (getSysPri() == 0))//恢复出厂设置需要用户同时拥有系统管理权限和参数设置权限
	{
		if(document.forms[3].setFac) document.forms[3].setFac.disabled = true;
	}
	if(getDataPri() == 0)
	{
		if(document.forms[1].btformat) document.forms[1].btformat.disabled = true;
	}	
}

function hasError()
{
	var hrefstr,pos,errCode;
	hrefstr=window.location.href;
	pos=hrefstr.indexOf("err=",0);
	if(pos==-1)
		return -1;
	errCode = hrefstr.substring(pos+4,pos+5);
	return errCode;
}

function Init()
{
	document.form1.name.focus();
	var getIP = getCookie("visitedIP=").replace("http://","");
	var curIP = window.location.href.replace("http://","");
	var getvalues = getIP.split("/");
	var curvalues = curIP.split("/");
	if(getvalues[0] == curvalues[0])
	{
		window.location.href = "error.htm";
	}
	/*var getIP = getCookie("visitedIP=").indexOf("http://",0);
	if(getIP != -1)
	{
		window.location.href = "error.htm";
	}*/
}

function cancel()
{
	document.form1.name.value="";
	document.form1.password.value="";
	event.returnValue=false;
}

function getHostIP()
{
	var href,IP,tmp;
	href = window.location.host.replace("http://","");
	tmp = href.split(":");
	for(i=0;i<tmp.length;i++)
	{
		IP	= tmp[0];
	}	
	return IP;
}