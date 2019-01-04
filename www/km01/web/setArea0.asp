<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>SetArea</title>
<script language="javascript" src="js/cookie.js"></script>
<script language="javascript" src="js/common.js"></script>
<script language="JavaScript" type="text/JavaScript">
<!--
function setArea()
{
	try{
		var defaultPort = 5000;
		if(document.getElementById("Net_defaultPort0"))
		{
			defaultPort = document.getElementById("Net_defaultPort0").value;
			if(defaultPort == 0)
			{
				defaultPort = getCookie("port=");
			}
		}
	
		IP = getHostIP();
		ch = parseInt(getCookie("channel"));
		if(ch == "") ch = 0;
		str = getCookie("login=");
		key = str.split("&");
		if(str != "")
		{
			user = key[0];
			pass = key[1];
		}
		else
		{
			user = document.getElementById("loginUser").value;
			pass = document.getElementById("loginPass").value;
		}
		document.all.AreaControl.SetServerParamEx(IP,user,"",pass,0,ch+1,defaultPort,defaultPort);
	}catch(e){}
}
//-->
</script>
</head>

<body bgcolor="#ffffff" onload="setArea()" leftmargin="0" topmargin="0">
<%NetparaGet("getPort");%>
<div align="center">
<script language="javascript" src="js/areaEm.js"></script>
</div>
</body>
</html>
