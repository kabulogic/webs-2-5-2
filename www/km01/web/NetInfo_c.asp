<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7">
<title>Network Info</title>
<link href="css/layout.css" rel="stylesheet" type="text/css" />
<script language="javascript" src="js/cookie.js"></script>
<script language="javascript" src="js/common.js"></script>
<script language="javascript" src="js/function.js"></script>
<script language="javascript" src="js/get_net.js"></script>
<script language="javascript" src="js/validate.js"></script>
<script language="JavaScript" type="text/JavaScript">
<!--
MM_reloadPage(true);

function ConfirmPw()
{
	if(document.NetForm.PPPoEPw.value != document.NetForm.ConfPw.value){
		alert("两次输入的PPPoE密码不一致！");
		return false;
	}
	return true;
}

function assertIP(obj,name)
{
	if(!isIP(obj)){
		alert(name+"不正确！");
		window.event.returnValue=false;
		addcookie("seterror=1");
		return false;
	}
	if(name == "子网掩码")
	{
		if(!isMask(obj))
		{
			alert(name+"不合法！");
			window.event.returnValue=false;
			addcookie("seterror=1");
			return false;
		}
	}
    window.event.returnValue = true;
	delcookie("seterror=1");
	return true;
}

function assertPPPoEID(obj)
{
	if(hasChinese(obj.value)){
		alert("PPPoE ID包含中文字符！");
		window.event.returnValue=false;
		return false;
	}
    window.event.returnValue = true;
	return true;
}

function assertPW(obj)
{
	if(!isPasswd(obj)){
		alert("密码不合法,请输入数字！");
		window.event.returnValue=false;
		return false;
	}
    window.event.returnValue = true;
	return true;
}

function alertDHCP()
{
	if((document.getElementById("HasDHCP0").value == "1") || (document.getElementById("HasDHCP1").value == "1")){
		alert("DHCP设置成功，IP地址已经更改。\n请使用新的IP地址访问web页面。");
	}
}

function checkPort(obj,Min)
{
	if( (!isPort(obj)) || (obj.value < Min))
	{
		var hint = "输入错误，端口号范围:"+Min+"~65536.";
		alert(hint);
		obj.value = Min;
		return false;
	}
	return true;
}

function initNetCardTp()
{
	var no = document.NetForm.NetworkCard.selectedIndex;
	document.NetForm.backEth.value = no;
	switch(document.getElementById("Net_CdTp"+no).value){
		case "0":
			document.all.CardType.innerText = "10M/100M/1000M 自适应";
			break;
		case "1":
			document.all.CardType.innerText = "1000M";
			break;
		case "2":
			document.all.CardType.innerText = "100M";
			break;
		case "3":
			document.all.CardType.innerText = "10M";
			break;
		default:
			document.all.CardType.innerText = "未知类型";
			break;
	}
}

function checkAllIP()
{
	if(!(assertIP(document.getElementById("NetPara1"),'IP地址') 
	  && assertIP(document.getElementById("NetPara3"),'子网掩码') 
	  && assertIP(document.getElementById("NetPara4"),'网关')
	  && assertIP(document.getElementById("DNSIP"),'DNS服务器') 
	  && assertIP(document.getElementById("RmIP"),'报警中心IP')))
	{
		return false;
	}
	return true;
}
//-->
</script>
</head>

<body onload="setOperator();getNetCfg();InitBtSet();initNetCardTp()">
<div id="mainconfig">
<iframe id="hideframe" name="hideframe" style="display:none ;"></iframe>
<form name="NetForm" action="/infinova/netparaCfg" method="post" target="hideframe">
<input type="hidden" name="operator" value="" /><input type="hidden" name="IPChange" value="0" />
<input type="hidden" name="HasDHCP0" value="0" /><input type="hidden" name="HasDHCP1" value="0" />
<input type="hidden" name="lang" value="cn">
  <table cellpadding="0" cellspacing="0" class="bttable" width="840">
  <tr class="menu1">
	  <td colspan="5" height="25"><%NetparaGet();%>
	  &nbsp;网络基本配置</td>
  </tr>
  <tr>
	  <td width="6" height="20"></td>
	  <td width="145">网口</td>
	  <td width="256"><select name="NetworkCard" class="selectw" onchange="saveChange();getCardInfo();initNetCardTp()">
						<option value="0" selected="selected">1</option>
						<option value="1">2</option>
	    </select><input type="hidden" name="backEth" value="0" /></td>
	  <td colspan="2"></td>
  </tr>
  <tr><td width="6"></td>
		<td colspan="4"><table width="100%" border="0" cellpadding="0" cellspacing="0">
		<tr>
		  <td width="145" height="20">网卡类型：</td>
		  <td width="256"><label id="CardType"></label></td>
		<td width="150">MAC地址：</td>
		<td width="281"><label id="CardMac"></label></td>
		</tr>
		<tr>
		  <td width="145">IP类型：</td>
		  <td colspan="3" height="25">
		    <select name="NetType" class="selectw" onchange="onType()">
				<option value="0" selected="selected">静态IP</option>
				<option value="1">动态IP</option>
				<option value="2">PPPoE</option>
		    </select></td>
		</tr>
		<tr>
		  <td colspan="4"><div id="staticIP">
		  <table width="100%" border="0" cellpadding="0" cellspacing="0">
		  <tr><td width="145" height="20">IP地址：</td>
		  <td width="256"><input name="NetPara1" type="text" value="" onchange="assertIP(this,'IP地址')"/></td>
		  <td width="150"><!--端口：--></td>
		  <td width="281"><input name="NetPara2" type="text" value="" disabled="disabled" onchange="checkPort(this)" style="display:none"/></td>
		  </tr>
		  <tr><td height="20">子网掩码：</td>
		  <td><input name="NetPara3" type="text" value="" onchange="assertIP(this,'子网掩码')"/></td><td>网关：</td>
		  <td><input name="NetPara4" type="text" value="" onchange="assertIP(this,'网关')"/></td></tr>
		  <tr><td height="20"><input type="checkbox" name="AutoDNS" onclick="onDNS()" />自动DNS</td>
		  <td></td><td></td><td></td></tr>
		  <tr><td height="20">DNS服务器：</td>
		  <td><input name="DNSIP" type="text" value="" onchange="assertIP(this,'DNS服务器')"/></td><td></td><td></td></tr>
		  </table></div></td>
		</tr>
		<tr>
		  <td colspan="4"><div id="P3oE" style="display:none">
		  <table width="100%" border="0" cellpadding="0" cellspacing="0">
		  <tr><td width="145" height="20">PPPoE地址：</td>
		    <td width="256"><label id="P3oEAddr"></label></td>
		    <td width="150">PPPoE帐号：</td>
		  <td width="281"><input name="PPPoEUn" type="text" value="" maxlength="19" onchange="assertPPPoEID(this)"/></td>
		  </tr>
		  <tr><td height="20">PPPoE口令：</td>
		  <td><input name="PPPoEPw" type="password" class="passw" value="" maxlength="19" /></td><td>确认口令：</td>
		  <td><input name="ConfPw" type="password" class="passw" value="" maxlength="19" /></td></tr>
		  </table>
		  </div></td>
		</tr>
		</table></td></tr>
		<tr class="menu1">
		<td colspan="5" height="25">&nbsp;网络高级配置</td>
		</tr>
		<tr>
		  <td>&nbsp;</td>
	      <td height="40" colspan="2"><strong>注：</strong>修改端口后，重启系统方可生效</td>
	      <td>&nbsp;</td>
	      <td>&nbsp;</td>
	  </tr>
		<tr>
		  <td colspan="5"></td>
		</tr>
		
		<tr><td width="6" height="19"></td>
		  <td width="145">默认端口：</td>
		<td width="256"><input name="defaultPort" type="text" value="5000" onchange="checkPort(this,1024)" /></td>
		<td width="150">HTTP端口：</td>
		<td width="281"><input name="HttpPt" type="text" value="80" onchange="checkPort(this,1)" /></td>
		<!--<td width="26">SNMP端口：</td>-->
		<input name="SnmpPt" type="hidden" value="161" onchange="checkPort(this)" disabled="disabled" />
		<!--<td width="27"></td>-->
		</tr>
		<tr><td width="6" height="20"></td>
		<td width="145">报警中心：</td>
		<td width="256"><input name="RmIP" type="text" value="" onchange="assertIP(this,'报警中心IP')" /></td>
		<td width="150"><!--报警端口：--></td>
		<td width="281"><input name="RmPt" type="text" value="6791" disabled="disabled" onchange="checkPort(this)" style="display:none"/></td></tr>
		<tr><td width="6" height="20"></td>
		<td width="145">NAS主机地址：</td>
		<td width="256"><input name="NFSIP" type="text" value="" onchange="assertIP(this,'NAS主机地址')" disabled/></td>
		<td width="150">NAS路径：</td>
		<td width="281"><input name="NFSPath" type="text" maxlength="24" value="0" onchange="validateString(this,24)" disabled /></td></tr>
  <tr>
	  <td colspan="2" class="menu1" height="25">&nbsp;保存设置 </td>
	  <td colspan="3" class="menu1"><input name="button" type="button" class="myButton" value="应&nbsp;&nbsp;用" onclick="setNetCfg();" /></td>
  </tr>
  </table>
</form>
</div>
</body>
</html>
