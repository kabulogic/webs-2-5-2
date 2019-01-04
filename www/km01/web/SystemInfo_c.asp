<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7">
<link href="css/layout.css" rel="stylesheet" type="text/css" />
<title>System Info</title>
<script language="javascript" src="js/common.js"></script>
<script language="javascript" src="js/cookie.js"></script>
<script language="javascript" src="js/validate.js"></script>
<script language="javascript" src="js/dvrStat.js"></script>
<script language="JavaScript" type="text/JavaScript">
<!--
MM_reloadPage(true);

function Click(){
window.event.returnValue=false;
}
document.oncontextmenu=Click;

function setDvrCfg()
{
	var name = document.dvrInfo.ServerName.value;
	if(name == "" || name.length > 14){
		alert("设备名称不正确！");
		event.returnValue = false;
		return;
	}
	var id = document.dvrInfo.ServerID.value;
	if(id == "" || !isNumber(id) || parseInt(id) > 255){
		alert("设备号不正确！");
		event.returnValue = false;
		return;
	}
	document.dvrInfo.submit();
}
function assertName(obj)
{
	if(!isTrueName(obj)){
		alert("设备名称不正确！");
		//document.dvrInfo.ServerName.value = document.dvrInfo.Name.value;
		window.event.returnValue=false;
		return false;
	}
    window.event.returnValue = true;
	return true;
}
//-->
</script>
</head>

<body onload="setOperator();initDVRInfo()">
<iframe id="hideframe" name="hideframe" style="display:none ;"></iframe>
<div id="mainconfig">
<form name="dvrInfo" action="/infinova/dvrStatCfg" method="post" target="hideframe">
<input type="hidden" name="operator" value="" /><input type="hidden" name="lang" value="cn"><%dvrStatGet();%>
  <table cellpadding="0" cellspacing="0" class="bttable" width="840">
  <tr class="menu1">
	  <td colspan="3" height="25">&nbsp;DVR基本信息</td>
  </tr>
  <tr>
	  <td width="22" height="20"></td>
	  <td width="147">设备名称：</td>
	  <td><label id="ServerName">Infinova DVR</label></td>
	  </tr>
  <tr>
	  <td width="22" height="20"></td>
	  <td width="147">设备号：</td>
	  <td><label id="ServerID">1</label></td>
	  </tr>
  <tr>
    <td height="20"></td>
    <td>序列号： </td>
    <td><label id="SerialId">--</label></td>
    </tr>
 <tr>
	  <td width="22" height="20"></td>
	  <td width="147">通道个数：</td>
	  <td><label id="ChanNum">--</label></td>
	  </tr>
 <tr>
   <td height="20"></td>
   <td>硬盘个数：</td>
   <td><label id="HardiskNum">--</label></td>
   </tr>
  <tr class="menu1">
	  <td colspan="3" height="25">&nbsp;DVR版本信息</td>
  </tr>
  <tr>
	  <td width="22" height="20"></td>
	  <td width="147">主控版本：</td>
	  <td><label id="SoftwareVer">--</label></td>
	  </tr>
  <tr>
    <td height="20"></td>
    <td>编码版本：</td>
    <td><label id="DecodeVer">--</label></td>
    </tr>
  <tr>
	  <td width="22" height="20"></td>
	  <td width="147">硬件版本：</td>
	  <td><label id="HardwareVer">--</label></td>
	  </tr>
  <tr style="display:none">
	  <td colspan="2" class="menu1" height="25">&nbsp;保存设置</td>
	  <td class="menu1"><input name="button" type="button" class="myButton" value="应&nbsp;&nbsp;用" onclick="setDvrCfg();" /></td>
  </tr>
  </table>
</form>
</div>
</body>
</html>
