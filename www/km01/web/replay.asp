<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7">
<title>Replay</title>
<style type="text/css">
body {
	margin: 0px;
}
</style>
<script language="javascript" src="js/cookie.js"></script>
<script language="javascript" src="js/common.js"></script>
<script language="JavaScript" type="text/JavaScript">
<!--
MM_reloadPage(true);

function Click(){
    document.all.NVRPlayer.focus();
	window.event.returnValue=false;
}
document.oncontextmenu=Click;

function runPlay()
{
	try{
		var defaultPort = 5000;
		if(document.getElementById("Net_defaultPort0"))
		{
			defaultPort = document.getElementById("Net_defaultPort0").value;
		}
		var IP = getHostIP();
		str = getCookie("login=");
		key = str.split("&");
		user = key[0];
		pass = key[1];
		if( (user == "") || (pass == ""))
		{
			user = document.getElementById("loginUser").value;
			pass = document.getElementById("loginPass").value;
		}
		document.all.NVRReplayer.SetServerSnmpParamEx(IP,user,"",pass,defaultPort,defaultPort);
		document.all.NVRPlayer.focus();
	}catch(e){}
}
//-->
</script>
</head>

<body bgcolor="#ffffff" onload="runPlay()">
<%NetparaGet("getPort");%>
<div align="center" onclick="document.all.NVRPlayer.focus();">
<script language="javascript" src="js/replayEm.js"></script>
</div>
</body>
</html>
