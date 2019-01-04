<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7">
<title>Alarm Info</title>
<link href="css/layout.css" rel="stylesheet" type="text/css" />
<link href="css/defend_recplan.css" rel="stylesheet" type="text/css" />
<script language="javascript" src="js/setConfigMenu.js"></script>
<script language="javascript" src="js/defend_recplan.js"></script>
<script language="javascript" src="js/cookie.js"></script>
<script language="javascript" src="js/common.js"></script>
<script language="javascript" src="js/alarm.js"></script>
<script language="javascript" src="js/schedule.js"></script>
<script language="javascript" src="js/DefendTime.js"></script>
<script language="javascript" src="js/function.js"></script>
<script language="javascript" src="js/validate.js"></script>
<script language="javascript" src="js/control.js"></script>
<script language="javascript" src="js/get_alarm.js"></script>
<script language="javascript" src="js/set_alarm.js"></script>
<script language="JavaScript" type="text/JavaScript">
<!--
MM_reloadPage(true);

function getpara()
{
	var error = hasError();
	if(error == "1"){
		alert("报警设置不成功！");
	}
}

function assertPeriod()
{
	if(!period("InDefendTime")){
		alert("报警输入的布防时间不正确！");
		return false;
	}
	if(!period("OutDefendTime")){
		alert("报警输出的布防时间不正确！");
		return false;
	}
	return true;
}

function assertName(obj)
{
	if(!isTrueName(obj)){
		alert("报警输入名称包含特殊字符！");
		window.event.returnValue=false;
		//document.getElementById("InputName").value = document.getElementById("InName").value;
		addcookie("seterror=1");
		return false;
	}
    window.event.returnValue = true;
	delcookie("seterror=1");
	return true;
}

function Click(){
window.event.returnValue=false;
}
document.oncontextmenu=Click;
//-->
</script>
</head>

<body onload="initOptionChn('ContactPTZChannel','通道');initAlarm()">
<iframe id="hideframe" name="hideframe" style="display:none ;"></iframe>
<form name="AlarmForm" action="/infinova/alarmparaCfg" method="post" target="hideframe">
<%alarmparaGet("AlarmInput",0);%><%alarmparaGet("AlarmOutput",0);%><%alarmparaGet("AlarmEx",0);%>
<input type="hidden" name="flag" value="0" /><input type="hidden" name="operator" value="" /><input type="hidden" name="lang" value="cn">
  <table cellpadding="0" cellspacing="0" class="bttable" width="840">
  <tr>
	  <td colspan="6" height="25" class="menu1">&nbsp;报警输入</td>
  </tr>
  <tr>
	  <td width="20" height="25"></td>
	  <td width="133">报警输入 </td>
	  <td width="170">
	  		<select name="AlarmInput" class="selectw" onchange="SetAI();">
				<option value="0" selected="selected">报警输入 01</option>
				<option value="1">报警输入 02</option>
				<option value="2">报警输入 03</option>
				<option value="3">报警输入 04</option>
				<option value="4">报警输入 05</option>
				<option value="5">报警输入 06</option>
				<option value="6">报警输入 07</option>
				<option value="7">报警输入 08</option>
				<option value="8">报警输入 09</option>
				<option value="9">报警输入 10</option>
				<option value="10">报警输入 11</option>
				<option value="11">报警输入 12</option>
				<option value="12">报警输入 13</option>
				<option value="13">报警输入 14</option>
				<option value="14">报警输入 15</option>
				<option value="15">报警输入 16</option>
	  </select></td>
	  <td width="261">名称&nbsp;&nbsp;<input type="text"  maxlength="16" name="InputName"/></td>
	  <td width="254">类型&nbsp;&nbsp;<select name="AlarmType" class="selectw">
				<option value="0">常开</option>
				<option value="1">常闭</option>
	  </select></td>
  </tr>
  <tr>
	  <td width="20" height="25"></td>
	  <td width="133" align="left"><input type="checkbox" name="HandleDefend" value="1" onclick="onDefend();"/>布防
      <input type="hidden" name="isAlarmInChange" value="1"/></td>
	  <td width="170"><input type="checkbox" name="HandleContact" value="1" onclick="onAlarmContact();"/>联动</td>
	  <td width="261"></td>
	  <td width="254">&nbsp;</td>
  </tr>
  <tr>
  <td colspan="2">&nbsp;</td>
  <td colspan="3">
  <div id="DefendTime" style="display:none">
  </br><table cellpadding="0" cellspacing="0" border="0" class="tableborder">
		<tr onmouseover="setFlag(0)">
			<td class="cancel"  height="30">&nbsp;</td>
			<td id="time" class="cancel" colspan="48">
				<table id="alarminttb" width="518" align="left" cellpadding="0" cellspacing="0" border="0"></table>				
			</td>
		</tr>
		<tr>
			<td id="week" class="cancel" valign="top" rowspan="9" onmouseover="setFlag(0)">
				<table style="font:12px;" id="alarminwtb" height="210" cellpadding="0" cellspacing="0" border="0"></table>			
			</td>
			<td>
				<table  name='alarmintb0' id="alarmintb0" class="defend" cellpadding="0" cellspacing="0" width="480" ></table>			
			</td>
			<td height="30" valign="bottom" onmouseover="setFlag(0)">
			<table  name='alarmintb0' id="alarminviewtime" height="210" cellpadding="0" cellspacing="0" width="48" ></table>
			</td>
		</tr>
		<tr onmouseover="setFlag(0)">
		  <td height="25" align="center"><input name="all2" type="button" value="全选" onclick="selectDefendTime(1,'alarmin')" onmouseover="setFlag(0)" />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input name="no2" type="button" value="清除" onclick="selectDefendTime(0,'alarmin')" onmouseover="setFlag(0)" />
		  </td>
			<td>&nbsp;</td>
		  </tr>
		<tr onmouseover="setFlag(0)">
			<td height="25" colspan="2">说明：若要取消选择，请按住Ctrl键再拖选。</td>
		  </tr>
		</table><br/>     
  </div></td></tr>
  <tr>
  <td></td>
  <td colspan="4">
  <div id="AlarmContact" style="display:none">
  <table cellpadding="0" cellspacing="0" class="subtable">
  <tr>
	  <td width="127">&nbsp;报警触发方式</td>
	  <td width="174"><input type="checkbox" name="InTriggerVoice" value="1"/>声音警告</td>
	  <td width="163"><input type="checkbox" name="InTriggerCenter" value="1"/>控制中心</td>
	  <td colspan="2"><input type="checkbox" name="InTriggerMonitor" value="1"/>报警预览</td>
  </tr>
  <tr>
	  <td width="127"></td>
	  <td colspan="4"><input type="checkbox" name="InTriggerOutput" value="1" onclick="onInTriggerOutput()"/>触发报警输出</td>
  </tr>
  <tr>
	  <td width="127"></td>
	  <td>&nbsp;&nbsp;&nbsp;&nbsp;<input type="checkbox" name="InTriggerOutput1" value="1" disabled/>输出1</td>
	  <td><input type="checkbox" name="InTriggerOutput2" value="1" disabled/>输出2</td>
	  <td width="150"><input type="checkbox" name="InTriggerOutput3" value="1" disabled/>输出3</td>
	  <td width="127"><input type="checkbox" name="InTriggerOutput4" value="1" disabled/>输出4</td>
  </tr>
  <tr id="reRow1">
	  <td width="127">&nbsp;触发录像通道</td>
	  <td><input type="checkbox" name="RecordChannel1" value="1"/>通道01</td>
	  <td><input type="checkbox" name="RecordChannel2" value="1"/>通道02</td>
	  <td><input type="checkbox" name="RecordChannel3" value="1"/>通道03</td>
	  <td><input type="checkbox" name="RecordChannel4" value="1"/>通道04</td></tr>
  <tr id="reRow2">
	  <td width="127"></td>
	  <td><input type="checkbox" name="RecordChannel5" value="1"/>通道05</td>
	  <td><input type="checkbox" name="RecordChannel6" value="1"/>通道06</td>
	  <td><input type="checkbox" name="RecordChannel7" value="1"/>通道07</td>
	  <td><input type="checkbox" name="RecordChannel8" value="1"/>通道08</td></tr>
  <tr id="reRow3" style="display:none">
	  <td width="127"></td>
	  <td><input type="checkbox" name="RecordChannel9" value="1"/>通道09</td>
	  <td><input type="checkbox" name="RecordChannel10" value="1"/>通道10</td>
	  <td><input type="checkbox" name="RecordChannel11" value="1"/>通道11</td>
	  <td><input type="checkbox" name="RecordChannel12" value="1"/>通道12</td></tr>
  <tr id="reRow4" style="display:none">
	  <td width="127"></td>
	  <td><input type="checkbox" name="RecordChannel13" value="1"/>通道13</td>
	  <td><input type="checkbox" name="RecordChannel14" value="1"/>通道14</td>
	  <td><input type="checkbox" name="RecordChannel15" value="1"/>通道15</td>
	  <td><input type="checkbox" name="RecordChannel16" value="1"/>通道16</td></tr>
 
  <tr>
	  <td width="127">&nbsp;</td>
	  <td><input type="button" name="AllChannel" value="全选" class="myButton" onclick="onTriggerRecordChan('RecordChannel',1);setObjectByName('isAlarmInChange','1');"/></td>
	  <td colspan="3">&nbsp;<input type="button" name="NoneChannel" value="全不选" class="myButton" onclick="onTriggerRecordChan('RecordChannel',0);setObjectByName('isAlarmInChange','1');"/></td></tr>
  <tr>
	  <td width="127">&nbsp;PTZ联动</td>
	  <td colspan="4"><select name="ContactPTZChannel" onchange="onSelectPTZCh();SetbackAlarmInPTZ();">
		</select><input type="hidden" name="backPTZCh" value="0"/><input type="hidden" name="isPTZChChange" value="0"/></td>
	  </tr>
  <tr>
	  <td width="127">&nbsp;</td>
	  <td colspan="2"><input name="preset" type="checkbox" value="1" onclick="SetPreset();setObjectByName('isPTZChChange','1');"/>预置位&nbsp;<input type="text" name="PresetValue" disabled onchange="validateNum(this,1,255,'预置位范围: ');setObjectByName('isPTZChChange','1');" /></td>
	  <td></td>
	  <td></td>
  </tr>
  <tr>
	  <td width="127">&nbsp;</td>
	  <td colspan="2"><input name="cruise" type="checkbox" value="1" onclick="SetCruise();setObjectByName('isPTZChChange','1');" />花&nbsp;&nbsp;样&nbsp;&nbsp;<input type="text" name="CruiseValue" disabled onchange="validateNum(this,1,4,'花样范围: ');setObjectByName('isPTZChChange','1');" /></td>
	  <td></td>
	  <td></td>
  </tr>
  </table>
  </div></td></tr>
  <tr>
	  <td width="20" height="25"></td>
	  <td width="133">复制到 </td>
	  <td width="170"><select name="AlarmInputCopy" class="selectw">
				<option value="99">全部报警输入</option>
				<option value="0">报警输入01</option>
				<option value="1">报警输入02</option>
				<option value="2">报警输入03</option>
				<option value="3">报警输入04</option>
				<option value="4">报警输入05</option>
				<option value="5">报警输入06</option>
				<option value="6">报警输入07</option>
				<option value="7">报警输入08</option>
				<option value="8">报警输入09</option>
				<option value="9">报警输入10</option>
				<option value="10">报警输入11</option>
				<option value="11">报警输入12</option>
				<option value="12">报警输入13</option>
				<option value="13">报警输入14</option>
				<option value="14">报警输入15</option>
				<option value="15">报警输入16</option></select></td>
	  <td width="261"><input type="button" name="AlarmInputCopyBt" value="复&nbsp;&nbsp;制" class="myButton" onclick="OnAlarmInCopy();" />
(名称不能被复制)</td>
	  <td width="254">&nbsp;</td>
  </tr>
  <tr>
	  <td colspan="6" height="25" class="menu1">&nbsp;报警输出</td>
  </tr>
  <tr>
	  <td width="20" height="25"></td>
	  <td width="133">报警输出</td>
	  <td width="170">
	  		<select name="AlarmOutput" class="selectw" onchange="SetAO();">
				<option value="0">报警输出01</option>
				<option value="1">报警输出02</option>
				<option value="2">报警输出03</option>
				<option value="3">报警输出04</option>
	  </select><input type="hidden" name="AlarmOutBackNum" value="0"/></td>
	  <td colspan="2">延时&nbsp;&nbsp; <select name="AlarmOutputPostTime" class="inputw">
				<option value="5">5秒</option>
				<option value="10">10秒</option>
				<option value="30">30秒</option>
				<option value="60">1分钟</option>
				<option value="120">2分钟</option>
				<option value="300">5分钟</option>
				<option value="600">10分钟</option>
	  </select></td>
    </tr>
  	<tr>
		<td>&nbsp;<input type="hidden" name="isAlarmOutChange" value="1"/></td>
		<td>布防</td>
		<td colspan="3">
			</br> 
		<table cellpadding="0" cellspacing="0" border="0" class="tableborder">
		<tr onmouseover="setFlag(0)">
			<td class="cancel"  height="30">&nbsp;</td>
			<td id="time" class="cancel" colspan="2">
				<table id="alarmoutttb" width="518" align="left" cellpadding="0" cellspacing="0" border="0"></table>				
			</td>
		</tr>
		<tr>
			<td id="week" class="cancel" valign="top" rowspan="9" onmouseover="setFlag(0)">
				<table style="font:12px;" id="alarmoutwtb" height="210" cellpadding="0" cellspacing="0" border="0"></table>			
			</td>
			<td>
				<table name='alarmouttb0' id="alarmouttb0" class="defend" cellpadding="0" cellspacing="0" width="480" ></table>			
			</td>
			<td height="30" valign="bottom" onmouseover="setFlag(0)">
			<table  name='alarmouttb0' id="alarmoutviewtime" height="210" cellpadding="0" cellspacing="0" width="48" ></table>
			</td>
		</tr>
		<tr onmouseover="setFlag(0)">
		  <td height="25" align="center"><input name="all2" type="button" value="全选" onclick="selectDefendTime(1,'alarmout')" onmouseover="setFlag(0)" />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input name="no2" type="button" value="清除" onclick="selectDefendTime(0,'alarmout')" onmouseover="setFlag(0)" /></td>
			<td>&nbsp;</td>
		  </tr>
		<tr onmouseover="setFlag(0)">
			<td height="25" colspan="2">说明：若要取消选择，请按住Ctrl键再拖选。</td>
		  </tr>
		</table>
		<br/>		</td>
	</tr>
  <tr>
	  <td width="20" height="25"></td>
	  <td width="133">复制到</td>
	  <td width="170">
	  		<select name="AlarmOutputCopy" class="selectw">
				<option value="99">全部报警输出</option>
				<option value="0">报警输出01</option>
				<option value="1">报警输出02</option>
				<option value="2">报警输出03</option>
				<option value="3">报警输出04</option>
	  </select>	  </td>
	  <td width="261"><input type="button" name="AlarmOutputCopyBt" value="复&nbsp;&nbsp;制" class="myButton" onclick="OnAlarmOutCopy();" /></td>
	  <td width="254">&nbsp;</td>
  </tr>
  <tr>
	  <td colspan="6" height="25" class="menu1">&nbsp;异常报警</td>
  </tr>
  <tr >
	  <td colspan="6" ><table cellpadding="0" cellspacing="0" border="0" width="100%">
        <tr>
          <td width="19" height="25"></td>
          <td width="127">异常类型 </td>
          <td width="168"><select name="ExceptionType" class="selectw" onchange="SetAE();">
              <option value="0">硬盘满</option>
              <option value="1">硬盘出错</option>
              <option value="2">网络断开</option>
              <option value="3">非法访问</option>
              <option value="4">网络冲突</option>
          </select></td>
          <td colspan="3"></td>
        </tr>
        <tr>
          <td width="19" height="25">&nbsp;</td>
          <td width="127">报警触发方式</td>
          <td><input type="checkbox" name="ExTriggerVoice" value="1"/>声音警告</td>
          <td width="156">&nbsp;
            <label id = "Center"><input type="checkbox" name="ExTriggerCenter" value="1"/>控制中心</label></td>
          <td width="156">&nbsp;
            <input type="checkbox" name="ExTriggerMonitor" value="1" style="display:none"/>
            <label id="labelMonitor" style="display:none">报警预览</label></td>
          <td width="212"></td>
        </tr>
        <tr>
          <td colspan="2"></td>
          <td colspan="4"><input type="checkbox" name="ExTriggerOutput" value="1" onclick="onExTriggerOutput()"/>触发报警输出</td>
        </tr>
        <tr>
          <td colspan="6" ><table width="100%" border="0" cellpadding="0" cellspacing="0">
              <tr>
                <td width="146"></td>
                <td width="168">&nbsp;&nbsp;&nbsp;&nbsp;
                    <input type="checkbox" name="ExTriggerOutput1" value="1" disabled/>输出1</td>
                <td width="156">&nbsp;
                  <input type="checkbox" name="ExTriggerOutput2" value="1" disabled/>输出2</td>
                <td width="158"><input type="checkbox" name="ExTriggerOutput3" value="1" disabled/>输出3</td>
                <td width="210"><input type="checkbox" name="ExTriggerOutput4" value="1" disabled/>输出4</td>
              </tr>
          </table></td>
        </tr>
        <tr style="display:none">
          <td width="19" height="25">&nbsp;</td>
          <td width="127">复制到 </td>
          <td><select name="AlarmExCopy" class="selectw">
              <option value="99">全部</option>
              <option value="0">硬盘满</option>
              <option value="1">硬盘出错</option>
              <option value="2">网络断开</option>
              <option value="3">非法访问</option>
              <option value="4">网络冲突</option>
          </select></td>
          <td colspan="3"><input type="button" name="AlarmExCopyBt" value="复&nbsp;&nbsp;制" class="myButton" onclick="OnAlarmExCopy();" /></td>
        </tr>
      </table></td>
  </tr>
  <tr>
	  <td colspan="2" class="menu1" height="25">&nbsp;保存设置</td>
	  <td colspan="4" class="menu1"> <input name="button" type="button" class="myButton" value="应&nbsp;&nbsp;用" onclick="setAlarmCfg();" /></td>
  </tr>
  </table>
</form>
</body>
<div id="light" class="white_content">
<table width="100%" height="100%">
<tr><td width="5%" align="right"><img src="images/tips.gif" width="32" height="32" /></td><td width="95%" align="left"><label id="ctrTip" class="mybold"></label></td></tr>
</table>
</div> 
<iframe id="forShowTip" frameborder="0" class="myIFrame"></iframe>
<div id="fade" class="black_overlay"></div> 
</html>
