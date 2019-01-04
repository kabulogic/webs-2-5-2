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
		alert("PPPoE passwords do not match!");
		return false;
	}
	return true;
}

function assertIP(obj,name)
{
	if(!isIP(obj)){
		alert(name+" is illegal!");
		window.event.returnValue=false;
		addcookie("seterror=1");
		return false;
	}
	if(name == "Subnet Mask")
	{
		if(!isMask(obj))
		{
			alert(name+" is illegal!");
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
		alert("PPPoE ID includes illegal characters!");
		window.event.returnValue=false;
		return false;
	}
    window.event.returnValue = true;
	return true;
}

function assertPW(obj)
{
	if(!isPasswd(obj)){
		alert("Password is illegal,Please input number!");
		window.event.returnValue=false;
		return false;
	}
    window.event.returnValue = true;
	return true;
}

function alertDHCP()
{
	if((document.getElementById("HasDHCP0").value == "1") || (document.getElementById("HasDHCP1").value == "1")){
		alert("The IP address has been changed by DHCP.\nTo access the web pages, use the new IP address.");
	}
}

function checkPort(obj,Min)
{
	if( (!isPort(obj)) || (obj.value < Min))
	{
		var hint = "Input error! The range of port:"+Min+"~65536.";
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
			document.all.CardType.innerText = "10M/100M/1000M Auto";
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
			document.all.CardType.innerText = "Unknown Type";
			break;
	}
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
<input type="hidden" name="lang" value="en">
  <table cellpadding="0" cellspacing="0" class="bttable" width="840">
  <tr class="menu1">
	  <td colspan="5" height="25"><%NetparaGet();%>
	  &nbsp;Network Basic Configuration</td>
  </tr>
  <tr>
	  <td width="22" height="20"></td>
	  <td width="150">NIC</td>
	  <td width="240"><select name="NetworkCard" class="selectw" onchange="saveChange();getCardInfo();initNetCardTp()">
						<option value="0" selected="selected">1</option>
						<option value="1">2</option>
	    </select><input type="hidden" name="backEth" value="0" /></td>
	  <td colspan="2"></td>
  </tr>
  <tr><td width="22"></td>
		<td colspan="4"><table width="100%" border="0" cellpadding="0" cellspacing="0">
		<tr>
		  <td width="150" height="20">NIC Type:</td>
		  <td width="241"><label id="CardType"></label></td>
		<td width="138">MAC Address:</td>
		<td width="287"><label id="CardMac"></label></td>
		</tr>
		<tr>
		  <td width="150">IP Type:</td>
		  <td colspan="3" height="25">
		    <select name="NetType" class="selectw" onchange="onType()">
				<option value="0" selected="selected">Static IP</option>
				<option value="1">DHCP</option>
				<option value="2">PPPoE</option>
		    </select></td>
		</tr>
		<tr>
		  <td colspan="4"><div id="staticIP">
		  <table width="100%" cellpadding="0" cellspacing="0" border="0">
		  <tr><td width="150" height="20">IP Address:</td>
		  <td width="241"><input name="NetPara1" type="text" value="" onchange="assertIP(this,'IP address')"/></td>
		  <td width="138"><!--Port:--></td>
		  <td width="287"><input name="NetPara2" type="hidden" value="" disabled="disabled" onchange="isPort(this)"/></td>
		  </tr>
		  <tr><td height="20">Subnet Mask:</td>
		  <td><input name="NetPara3" type="text" value="" onchange="assertIP(this,'Subnet Mask')"/></td><td>Gateway:</td>
		  <td><input name="NetPara4" type="text" value="" onchange="assertIP(this,'Gateway')"/></td></tr>
		  <tr><td height="20"><input type="checkbox" name="AutoDNS" onclick="onDNS()"/>Auto DNS</td>
		    <td></td><td></td><td></td></tr>
		  <tr>
		    <td height="20">DNS:</td>
		    <td><input name="DNSIP" type="text" value="" onchange="assertIP(this,'DNS')"/></td><td></td><td></td></tr>
		  </table></div></td>
		</tr>
		<tr>
		  <td colspan="4"><div id="P3oE" style="display:none">
		  <table width="100%" cellpadding="0" cellspacing="0" border="0">
		  <tr><td width="150" height="20">PPPoE Address:</td>
		    <td width="243"><label id="P3oEAddr"></label></td>
		    <td width="136">PPPoE UserName:</td>
		  <td width="287"><input name="PPPoEUn" type="text" value="" maxlength="19" onchange="assertPPPoEID(this)"/></td>
		  </tr>
		  <tr><td height="20">PPPoE Password:</td>
		  <td><input name="PPPoEPw" type="password" class="passw" value="" maxlength="19" /></td><td>Confirm Password: </td>
		  <td><input name="ConfPw" type="password" class="passw" value="" maxlength="19" /></td></tr>
		  </table>
		  </div></td>
		</tr>
		</table></td></tr>

		<tr class="menu1">
	    <td colspan="5" height="25">&nbsp;Network Advanced Configuration</td>
        </tr>
		<tr>
		  <td height="40"></td>
		  <td colspan="2"><strong>Note:</strong>After Setting port,please reboot system. </td>
		  <td>&nbsp;</td>
		  <td>&nbsp;</td>
	  </tr>
		<tr><td width="22" height="19"></td>
		  <td width="150">Default Port: </td>
		<td width="240"><input name="defaultPort" type="text" value="5000" onchange="checkPort(this,1024)" /></td>
		<td width="135"><!--SNMP Port:-->HTTP Port:</td>
		<td width="291"><input name="SnmpPt" type="hidden" value="161" onchange="isPort(this)" disabled="disabled" /><input name="HttpPt" type="text" value="80"  onchange="checkPort(this,1)" /></td></tr>
		<tr><td width="22" height="20"></td>
		<td width="150">Alarm Center :</td>
		<td width="240"><input name="RmIP" type="text" value="" onchange="assertIP(this,'Alarm Center IP')" /></td>
		<td width="135"><!--Alarm Port:--></td>
		<td width="291"><input name="RmPt" type="hidden" value="6791" disabled="disabled" onchange="isPort(this)"/></td></tr>
		<tr><td width="22" height="20"></td>
		<td width="150">NAS Host IP:</td>
		<td width="240"><input name="NFSIP" type="text" value="" onchange="assertIP(this,'NAS host IP')" disabled /></td>
		<td width="135">NAS Path:</td>
		<td width="291"><input name="NFSPath" type="text" maxlength="24" value="" onchange="validateString(this,24)" disabled /></td></tr>
  <tr>
	  <td colspan="5" class="menu1" height="25">&nbsp;Save all the parameters: <input name="button" type="button" class="myButton" value="Set" onclick="setNetCfg();" /></td>
  </tr>
  </table>
</form>
</div>
</body>
</html>
