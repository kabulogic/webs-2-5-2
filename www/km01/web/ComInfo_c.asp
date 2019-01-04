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
		alert("串口信息设置不成功！");
	}
}

function ptzaddrHint()
{
	var error = FrameAndIPRate(document.ComForm.RS422DecodeAddress,1,255);
	if(!error)
	{
		alert("PTZ地址范围是1~255.");
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

<body onload="initOptionChn('RS422Channel','通道');initOptionChnCopy('RS422CopyToChannel','通道','全部通道');setOperator();getpara();InitBtSet();GetComCh();getComInfo();">
<iframe id="hideframe" name="hideframe" style="display:none ;"></iframe>
<form name="ComForm" action="/infinova/comparaCfg" method="post" target="hideframe">
<%comparaGet("COM232");comparaGet("COM422");%>
<input type="hidden" name="flag" value="0" /><input type="hidden" name="operator" value="" /><input type="hidden" name="lang" value="cn">
  <table cellpadding="0" cellspacing="0" class="bttable" width="840" height="300">
  <tr>
	  <td colspan="6" class="menu1" height="25">&nbsp;串口设置 </td>
  </tr>
  <tr>
	  <td width="22" height="20"></td>
	  <td width="147">波特率：</td>
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
	  <td width="158">数据位：</td>
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
	  <td width="147">停止位：</td>
	  <td width="218">
			<select name="RS232StopBit" class="selectw">
				<option value="1">1</option>
				<option value="2">2</option>
			</select>	  </td>
	  <td width="70"></td>
	  <td width="158">校&nbsp;&nbsp;&nbsp;验： </td>
	  <td width="223">
			<select name="RS232ParityCheck" class="selectw">
				<option value="0">无校验</option>
				<option value="1">奇校验</option>
				<option value="2">偶校验</option>
			</select>	  </td>
  </tr>
  <tr>
	  <td width="22" height="20"></td>
	  <td width="147">流&nbsp;&nbsp;&nbsp;控：</td>
	  <td width="218">
	  		<select name="RS232StreamControl" class="selectw">
				<option value="0">无流控</option>
				<option value="1">软流控</option>
				<option value="2">硬流控</option>
			</select>	  </td>
	  <td width="70"></td>
	  <td width="158">&nbsp;</td>
	  <td width="223">&nbsp;</td>
  </tr>
  <tr>
	  <td colspan="6" class="menu1" height="25">&nbsp;PTZ设置</td>
  </tr>
  <tr>
	  <td width="22" height="20"></td>
	  <td width="147">通道号：</td>
	  <td width="229"><select name="RS422Channel" class="selectw" onchange="setComCh();">
				<!--<option value="0" selected="selected">通道01</option>
				<option value="1">通道02</option>
				<option value="2">通道03</option>
				<option value="3">通道04</option>
				<option value="4">通道05</option>
				<option value="5">通道06</option>
				<option value="6">通道07</option>
				<option value="7">通道08</option>
				<option value="8">通道09</option>
				<option value="9">通道10</option>
				<option value="10">通道11</option>
				<option value="11">通道12</option>
				<option value="12">通道13</option>
				<option value="13">通道14</option>
				<option value="14">通道15</option>
				<option value="15">通道16</option>-->
	  </select></td>
	  <td width="59"></td>
	  <td width="147">PTZ地址： </td>
	  <td width="234"><input type="text" name="RS422DecodeAddress" class="halfInput" value="" onchange="ptzaddrHint()"/></td>
  </tr>
  <tr>
	  <td width="22" height="20"></td>
	  <td width="147">波特率：</td>
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
	  <td width="158">数据位：</td>
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
	  <td width="147">停止位：</td>
	  <td width="218">
			<select name="RS422StopBit" class="selectw">
				<option value="1">1</option>
				<option value="2">2</option>
			</select>	  </td>
	  <td width="70"></td>
	  <td width="158">校&nbsp;&nbsp;&nbsp;验： </td>
	  <td width="223">
			<select name="RS422ParityCheck" class="selectw">
				<option value="0">无校验</option>
				<option value="1">奇校验</option>
				<option value="2">偶校验</option>
			</select>	  </td>
  </tr>
  <tr>
	  <td width="22" height="20"></td>
	  <td width="147">流&nbsp;&nbsp;&nbsp;控：</td>
	  <td width="218">
	  		<select name="RS422StreamControl" class="selectw">
				<option value="0">无流控</option>
				<option value="1">软流控</option>
				<option value="2">硬流控</option>
			</select>	  </td>
	  <td width="70"></td>
	  <td width="158">协&nbsp;&nbsp;&nbsp;议：</td>
	  <td width="223"><select name="RS422Protocol" class="selectw">
				<option value="0">Infinova</option>
				<option value="3">Pelco-D</option>
				<option value="4">Pelco-P</option>
			</select></td>
  </tr>
  <tr>
	  <td width="22" height="20"></td>
	  <td width="147">复制到</td>
	  <td colspan="4">
	  		<select name="RS422CopyToChannel" class="selectw">
				<!--<option value="99">全部通道</option>
				<option value="0">通道01</option>
				<option value="1">通道02</option>
				<option value="2">通道03</option>
				<option value="3">通道04</option>
				<option value="4">通道05</option>
				<option value="5">通道06</option>
				<option value="6">通道07</option>
				<option value="7">通道08</option>
				<option value="8">通道09</option>
				<option value="9">通道10</option>
				<option value="10">通道11</option>
				<option value="11">通道12</option>
				<option value="12">通道13</option>
				<option value="13">通道14</option>
				<option value="14">通道15</option>
				<option value="15">通道16</option>-->
			</select>&nbsp;&nbsp;<input type="button" name="ComCopyBt" class="myButton" value="复&nbsp;&nbsp;制" onclick="OnCopy422();" />	  </td>
  </tr>
  <tr>
	  <td colspan="2" class="menu1" height="25">保存设置</td>
	  <td colspan="4" class="menu1"><input name="button" type="button" class="myButton" value="应&nbsp;&nbsp;用" onclick="setComCfg()" /></td>
  </tr>
  </table>
</form>
</body>
</html>
