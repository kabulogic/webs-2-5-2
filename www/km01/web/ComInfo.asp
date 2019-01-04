<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7">
<title>Com Info</title>
<link href="css/layout.css" rel="stylesheet" type="text/css" />
<script language="javascript" src="js/cookie.js"></script>
<script language="javascript" src="js/common.js"></script>
<script language="javascript" src="js/get_com.js"></script>
<script language="javascript" src="js/function.js"></script>
<script language="javascript" src="js/set_com.js"></script>
<script language="javascript" src="js/validate.js"></script>
<script language="JavaScript" type="text/JavaScript">
<!--
MM_reloadPage(true);

function getpara()
{
	var error = hasError();
	if(error == "1"){
		alert("Set COM info failed!");
	}
}

function ptzaddrHint()
{
	var error = FrameAndIPRate(document.ComForm.RS422DecodeAddress,1,255);
	if(!error)
	{
		alert("PTZ Address:1~255.");
		document.ComForm.RS422DecodeAddress.value = document.ComForm.COM422_Addr.value;
	}
}

function Click(){
window.event.returnValue=false;
}
document.oncontextmenu=Click;
//-->
</script>
</head>

<body onload="initOptionChn('RS422Channel','Channel ');initOptionChnCopy('RS422CopyToChannel','Channel ','All Channels');setOperator();getpara();InitBtSet();GetComCh();getComInfo();">
<iframe id="hideframe" name="hideframe" style="display:none ;"></iframe>
<form name="ComForm" action="/infinova/comparaCfg" method="post" target="hideframe">
<%comparaGet("COM232");comparaGet("COM422");%>
<input type="hidden" name="flag" value="0" /><input type="hidden" name="operator" value="" /><input type="hidden" name="lang" value="en">
  <table cellpadding="0" cellspacing="0" class="bttable" width="840">
  <tr>
	  <td colspan="6" class="menu1" height="25">&nbsp;COM Settings </td>
  </tr>
  <tr>
	  <td width="22" height="20"></td>
	  <td width="147">Baud Rate:</td>
	  <td width="218">
	  		<select name="RS232BaudRate" class="selectw">
				<option value="0">50</option>
				<option value="1">75</option>
				<option value="2">110</option>
				<option value="3">150</option>
				<option value="4">300</option>
				<option value="5">600</option>
				<option value="6">1200</option>
				<option value="7">2400</option>
				<option value="8">4800</option>
				<option value="9">9600</option>
				<option value="10">19200</option>
				<option value="11">38400</option>
				<option value="12">57600</option>
				<option value="13">76800</option>
				<option value="14">115.2k</option>
			</select>	  </td>
	  <td width="70"></td>
	  <td width="158">Data Bits: </td>
	  <td width="223">
			<select name="RS232DataBit" class="selectw">
				<option value="5">5</option>
				<option value="6">6</option>
				<option value="7">7</option>
				<option value="8">8</option>
			</select>	  </td>
  </tr>
  <tr>
	  <td width="22" height="20"></td>
	  <td width="147">Stop Bits :</td>
	  <td width="218">
			<select name="RS232StopBit" class="selectw">
				<option value="1">1</option>
				<option value="2">2</option>
			</select>	  </td>
	  <td width="70"></td>
	  <td width="158">Parity: </td>
	  <td width="223">
			<select name="RS232ParityCheck" class="selectw">
				<option value="0">None</option>
				<option value="1">Odd</option>
				<option value="2">Even</option>
			</select>	  </td>
  </tr>
  <tr>
	  <td width="22" height="20"></td>
	  <td width="147">Flow Control:</td>
	  <td width="218">
	  		<select name="RS232StreamControl" class="selectw">
				<option value="0">None</option>
				<option value="1">Software</option>
				<option value="2">Hardware</option>
			</select>	  </td>
	  <td width="70"></td>
	  <td width="158">&nbsp;</td>
	  <td width="223">&nbsp;</td>
  </tr>
  <tr>
	  <td colspan="6" class="menu1" height="25">&nbsp;PTZ Settings </td>
  </tr>
  <tr>
	  <td width="22" height="20"></td>
	  <td width="147">Channel:</td>
	  <td width="229"><select name="RS422Channel" class="selectw" onchange="setComCh();">
				<!--<option value="0" selected="selected">Channel 01</option>
				<option value="1">Channel 02</option>
				<option value="2">Channel 03</option>
				<option value="3">Channel 04</option>
				<option value="4">Channel 05</option>
				<option value="5">Channel 06</option>
				<option value="6">Channel 07</option>
				<option value="7">Channel 08</option>
				<option value="8">Channel 09</option>
				<option value="9">Channel 10</option>
				<option value="10">Channel 11</option>
				<option value="11">Channel 12</option>
				<option value="12">Channel 13</option>
				<option value="13">Channel 14</option>
				<option value="14">Channel 15</option>
				<option value="15">Channel 16</option>-->
	  </select></td>
	  <td width="59"></td>
	  <td width="147">PTZ Addr.: </td>
	  <td width="234"><input type="text" name="RS422DecodeAddress" class="halfInput" value="" onchange="ptzaddrHint()"/></td>
  </tr>
  <tr>
	  <td width="22" height="20"></td>
	  <td width="147">Baud Rate:</td>
	  <td width="218">
	  		<select name="RS422BaudRate" class="selectw">
				<!--<option value="0">50</option>
				<option value="1">75</option>
				<option value="2">110</option>
				<option value="3">150</option>
				<option value="4">300</option>
				<option value="5">600</option>
				<option value="6">1200</option>-->
				<option value="7">2400</option>
				<option value="8">4800</option>
				<option value="9">9600</option>
				<option value="10">19200</option>
				<option value="11">38400</option>
				<option value="12">57600</option>
				<option value="13">76800</option>
				<option value="14">115.2k</option>
			</select>	  </td>
	  <td width="70"></td>
	  <td width="158">Data Bits: </td>
	  <td width="223">
			<select name="RS422DataBit" class="selectw">
				<option value="5">5</option>
				<option value="6">6</option>
				<option value="7">7</option>
				<option value="8">8</option>
			</select>	  </td>
  </tr>
  <tr>
	  <td width="22" height="20"></td>
	  <td width="147">Stop Bits :</td>
	  <td width="218">
			<select name="RS422StopBit" class="selectw">
				<option value="1">1</option>
				<option value="2">2</option>
			</select>	  </td>
	  <td width="70"></td>
	  <td width="158">Parity: </td>
	  <td width="223">
			<select name="RS422ParityCheck" class="selectw">
				<option value="0">None</option>
				<option value="1">Odd</option>
				<option value="2">Even</option>
			</select>	  </td>
  </tr>
  <tr>
	  <td width="22" height="20"></td>
	  <td width="147">Flow Control:</td>
	  <td width="218">
	  		<select name="RS422StreamControl" class="selectw">
				<option value="0">None</option>
				<option value="1">Software</option>
				<option value="2">Hardware</option>
			</select>	  </td>
	  <td width="70"></td>
	  <td width="158">Protocol:</td>
	  <td width="223"><select name="RS422Protocol" class="selectw">
				<option value="0">Infinova</option>
				<option value="3">Pelco-D</option>
				<option value="4">Pelco-P</option>
			</select></td>
  </tr>
  <tr>
	  <td width="22" height="20"></td>
	  <td width="147">Copy To</td>
	  <td colspan="4">
	  		<select name="RS422CopyToChannel" class="selectw">
				<!--<option value="99">All Channels</option>
				<option value="0">Channel 01</option>
				<option value="1">Channel 02</option>
				<option value="2">Channel 03</option>
				<option value="3">Channel 04</option>
				<option value="4">Channel 05</option>
				<option value="5">Channel 06</option>
				<option value="6">Channel 07</option>
				<option value="7">Channel 08</option>
				<option value="8">Channel 09</option>
				<option value="9">Channel 10</option>
				<option value="10">Channel 11</option>
				<option value="11">Channel 12</option>
				<option value="12">Channel 13</option>
				<option value="13">Channel 14</option>
				<option value="14">Channel 15</option>
				<option value="15">Channel 16</option>-->
			</select>&nbsp;&nbsp;<input type="button" name="ComCopyBt" class="myButton" value="Copy" onclick="OnCopy422();" />	  </td>
  </tr>
  <tr>
	  <td colspan="6" class="menu1" height="25">Save all the parameters: <input name="button" type="button" class="myButton" value="Set" onclick="setComCfg()" /></td>
  </tr>
  </table>
</form>
</body>
</html>
