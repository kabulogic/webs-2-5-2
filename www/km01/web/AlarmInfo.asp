<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7">
<title>Alarm Info</title>
<link href="css/layout.css" rel="stylesheet" type="text/css" />
<link href="css/defend_recplan.css" rel="stylesheet" type="text/css" />
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
		alert("Set alarm info failed!");
	}
}

function assertPeriod()
{
	if(!period("InDefendTime")){
		alert("Schedule of alarm input is illegal!");
		return false;
	}
	if(!period("OutDefendTime")){
		alert("Schedule of alarm output is illegal!");
		return false;
	}
	return true;
}

function assertName(obj)
{
	if(!isTrueName(obj)){
		alert("The name of alarm input is illegal!");
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

<body onload="initOptionChn('ContactPTZChannel','Channel ');initAlarm()">
<iframe id="hideframe" name="hideframe" style="display:none ;"></iframe>
<form name="AlarmForm" action="/infinova/alarmparaCfg" method="post" target="hideframe">
<%alarmparaGet("AlarmInput",0);%><%alarmparaGet("AlarmOutput",0);%><%alarmparaGet("AlarmEx",0);%>
<input type="hidden" name="flag" value="0" /><input type="hidden" name="operator" value="" /><input type="hidden" name="lang" value="en">
  <table cellpadding="0" cellspacing="0" class="bttable" width="840">
  <tr>
	  <td colspan="6" height="25" class="menu1">&nbsp;Alarm Input</td>
  </tr>
  <tr>
	  <td width="20" height="25"></td>
	  <td width="133">Alarm Input </td>
	  <td width="170">
	  		<select name="AlarmInput" class="selectw" onchange="SetAI();">
				<option value="0" selected="selected">Alarm Input 01</option>
				<option value="1">Alarm Input 02</option>
				<option value="2">Alarm Input 03</option>
				<option value="3">Alarm Input 04</option>
				<option value="4">Alarm Input 05</option>
				<option value="5">Alarm Input 06</option>
				<option value="6">Alarm Input 07</option>
				<option value="7">Alarm Input 08</option>
				<option value="8">Alarm Input 09</option>
				<option value="9">Alarm Input 10</option>
				<option value="10">Alarm Input 11</option>
				<option value="11">Alarm Input 12</option>
				<option value="12">Alarm Input 13</option>
				<option value="13">Alarm Input 14</option>
				<option value="14">Alarm Input 15</option>
				<option value="15">Alarm Input 16</option>
	  </select></td>
	  <td width="261">Name&nbsp; 
      <input type="text" name="InputName" maxlength="16"/></td>
	  <td width="254">Type&nbsp; 
	    <select name="AlarmType" class="selectw">
				<option value="0">N.O.</option>
				<option value="1">N.C.</option>
	  </select></td>
  </tr>
  <tr>
	  <td width="20" height="25"><input type="hidden" name="isAlarmInChange" value="1"/></td>
	  <td width="133"><input type="checkbox" name="HandleDefend" value="1" onclick="onDefend();"/>Schedule</td>
	  <td width="170"><input type="checkbox" name="HandleContact" value="1" onclick="onAlarmContact();"/>Linkage</td>
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
		  <td height="25" align="center"><input name="all2" type="button" value="Select All" onclick="selectDefendTime(1,'alarmin')" onmouseover="setFlag(0)" />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input name="no2" type="button" value="Clear All" onclick="selectDefendTime(0,'alarmin')" onmouseover="setFlag(0)" />
		  </td>
			<td>&nbsp;</td>
		  </tr>
		<tr onmouseover="setFlag(0)">
			<td height="25" colspan="2"><p>Note:if clean out a part of selecting,please press &quot;Ctrl&quot; key and then drag.</td>
		</tr>
		</table><br/>     
  </div></td></tr>
  <tr>
  <td></td>
  <td colspan="4">
  <div id="AlarmContact" style="display:none">
  <table cellpadding="0" cellspacing="0" class="subtable">
  <tr>
	  <td width="127">&nbsp;Output</td>
	  <td width="174"><input type="checkbox" name="InTriggerVoice" value="1"/>Audible Warning</td>
	  <td width="163"><input type="checkbox" name="InTriggerCenter" value="1"/>Center</td>
	  <td colspan="2"><input type="checkbox" name="InTriggerMonitor" value="1"/>Alarm Preview</td>
  </tr>
  <tr>
	  <td width="127"></td>
	  <td colspan="4"><input type="checkbox" name="InTriggerOutput" value="1" onclick="onInTriggerOutput()"/>Trigger Alarm Output</td>
  </tr>
  <tr>
	  <td width="127"></td>
	  <td>&nbsp;&nbsp;&nbsp;&nbsp;<input type="checkbox" name="InTriggerOutput1" value="1" disabled/>Output 1</td>
	  <td><input type="checkbox" name="InTriggerOutput2" value="1" disabled/>Output 2</td>
	  <td width="150"><input type="checkbox" name="InTriggerOutput3" value="1" disabled/>Output 3</td>
	  <td width="127"><input type="checkbox" name="InTriggerOutput4" value="1" disabled/>Output 4</td>
  </tr>
  <tr id="reRow1">
	  <td width="127">&nbsp;Record Channel</td>
	  <td><input type="checkbox" name="RecordChannel1" value="1"/>Channel 01</td>
	  <td><input type="checkbox" name="RecordChannel2" value="1"/>Channel 02</td>
	  <td><input type="checkbox" name="RecordChannel3" value="1"/>Channel 03</td>
	  <td><input type="checkbox" name="RecordChannel4" value="1"/>Channel 04</td></tr>
  <tr id="reRow2">
	  <td width="127"></td>
	  <td><input type="checkbox" name="RecordChannel5" value="1"/>Channel 05</td>
	  <td><input type="checkbox" name="RecordChannel6" value="1"/>Channel 06</td>
	  <td><input type="checkbox" name="RecordChannel7" value="1"/>Channel 07</td>
	  <td><input type="checkbox" name="RecordChannel8" value="1"/>Channel 08</td></tr>
  <tr id="reRow3" style="display:none">
	  <td width="127"></td>
	  <td><input type="checkbox" name="RecordChannel9" value="1"/>Channel 09</td>
	  <td><input type="checkbox" name="RecordChannel10" value="1"/>Channel 10</td>
	  <td><input type="checkbox" name="RecordChannel11" value="1"/>Channel 11</td>
	  <td><input type="checkbox" name="RecordChannel12" value="1"/>Channel 12</td></tr>
  <tr id="reRow4" style="display:none">
	  <td width="127"></td>
	  <td><input type="checkbox" name="RecordChannel13" value="1"/>Channel 13</td>
	  <td><input type="checkbox" name="RecordChannel14" value="1"/>Channel 14</td>
	  <td><input type="checkbox" name="RecordChannel15" value="1"/>Channel 15</td>
	  <td><input type="checkbox" name="RecordChannel16" value="1"/>Channel 16</td></tr>
  <tr>
	  <td width="127">&nbsp;</td>
	  <td><input type="button" name="AllChannel" value="All" class="myButton" onclick="onTriggerRecordChan('RecordChannel',1);setObjectByName('isAlarmInChange','1');"/></td>
	  <td colspan="3">&nbsp;<input type="button" name="NoneChannel" value="None" class="myButton" onclick="onTriggerRecordChan('RecordChannel',0);setObjectByName('isAlarmInChange','1');"/></td></tr>
  <tr>
	  <td width="127">&nbsp;PTZ</td>
	  <td colspan="4"><select name="ContactPTZChannel" onchange="SetbackAlarmInPTZ();onSelectPTZCh();">
	</select><input type="hidden" name="backPTZCh" value="0"/><input type="hidden" name="isPTZChChange" value="0"/></td>
	  </tr>
  <tr>
	  <td width="127">&nbsp;</td>
	  <td colspan="2"><input name="preset" type="checkbox" value="1" onclick="SetPreset();setObjectByName('isPTZChChange','1');"/>Preset&nbsp;&nbsp;<input type="text" name="PresetValue" disabled onchange="validateNum(this,1,255,'Preset range: ');setObjectByName('isPTZChChange','1');" /></td>
	  <td></td>
	  <td></td>
  </tr>
  <tr>
	  <td width="127">&nbsp;</td>
	  <td colspan="2"><input name="cruise" type="checkbox" value="1" onclick="SetCruise();setObjectByName('isPTZChChange','1');" />Pattern&nbsp;<input type="text" name="CruiseValue" disabled onchange="validateNum(this,1,4,'Pattern range: ');setObjectByName('isPTZChChange','1');" /></td>
	  <td></td>
	  <td></td>
  </tr>
  </table>
  </div></td></tr>
  <tr>
	  <td width="20" height="25"></td>
	  <td width="133">Copy To </td>
	  <td width="170">
	  		<select name="AlarmInputCopy" class="selectw">
				<option value="99">All Alarm Input</option>
				<option value="0">Alarm Input 01</option>
				<option value="1">Alarm Input 02</option>
				<option value="2">Alarm Input 03</option>
				<option value="3">Alarm Input 04</option>
				<option value="4">Alarm Input 05</option>
				<option value="5">Alarm Input 06</option>
				<option value="6">Alarm Input 07</option>
				<option value="7">Alarm Input 08</option>
				<option value="8">Alarm Input 09</option>
				<option value="9">Alarm Input 10</option>
				<option value="10">Alarm Input 11</option>
				<option value="11">Alarm Input 12</option>
				<option value="12">Alarm Input 13</option>
				<option value="13">Alarm Input 14</option>
				<option value="14">Alarm Input 15</option>
				<option value="15">Alarm Input 16</option>
	  </select>	  </td>
	  <td width="261"><input type="button" name="AlarmInputCopyBt" value="Copy" class="myButton" onclick="OnAlarmInCopy();" />
      (Name can not be copied)</td>
	  <td width="254">&nbsp;</td>
  </tr>
  <tr>
	  <td colspan="6" height="25" class="menu1">&nbsp;Alarm Output</td>
  </tr>
  <tr>
	  <td width="20" height="25"></td>
	  <td width="133">Alarm Output </td>
	  <td width="170">
	  		<select name="AlarmOutput" class="selectw" onchange="SetAO();">
				<option value="0">Alarm Output 01</option>
				<option value="1">Alarm Output 02</option>
				<option value="2">Alarm Output 03</option>
				<option value="3">Alarm Output 04</option>
	  </select><input type="hidden" name="AlarmOutBackNum" value="0"/></td>
	  <td colspan="2">Output Delay &nbsp;<select name="AlarmOutputPostTime" class="inputw">
				<option value="5">5s</option>
				<option value="10">10s</option>
				<option value="30">30s</option>
				<option value="60">1m</option>
				<option value="120">2m</option>
				<option value="300">5m</option>
				<option value="600">10m</option>
	  </select></td>
    </tr>
  <tr>
		<td>&nbsp;<input type="hidden" name="isAlarmOutChange" value="1"/></td>
		<td>Schedule</td>
		<td colspan="3">
			</br> <table cellpadding="0" cellspacing="0" border="0" class="tableborder">
		<tr onmouseover="setFlag(0)">
			<td class="cancel"  height="30">&nbsp;</td>
			<td id="time" class="cancel" colspan="48">
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
		  <td height="25" align="center"><input name="all2" type="button" value="Select All" onclick="selectDefendTime(1,'alarmout')" onmouseover="setFlag(0)" />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input name="no2" type="button" value="Clear All" onclick="selectDefendTime(0,'alarmout')" onmouseover="setFlag(0)" /></td>
			<td>&nbsp;</td>
		  </tr>
		<tr onmouseover="setFlag(0)">
			<td height="25" colspan="2"><p>Note:if clean out a part of selecting,please press &quot;Ctrl&quot; key and then drag.</td>
		</tr>
		</table><br/>    
		</td>
	</tr>
  <tr>
	  <td width="20" height="25"></td>
	  <td width="133">Copy To </td>
	  <td width="170">
	  		<select name="AlarmOutputCopy" class="selectw">
				<option value="99">All Alarm Output</option>
				<option value="0">Alarm Output 01</option>
				<option value="1">Alarm Output 02</option>
				<option value="2">Alarm Output 03</option>
				<option value="3">Alarm Output 04</option>
	  </select>	  </td>
	  <td width="261"><input type="button" name="AlarmOutputCopyBt" value="Copy" class="myButton" onclick="OnAlarmOutCopy();" /></td>
	  <td width="254">&nbsp;</td>
  </tr>
  <tr>
	  <td colspan="6" height="25" class="menu1">&nbsp;Exception Configuration</td>
  </tr>
  <tr>
	  <td colspan="5">
	  <table cellpadding="0" cellspacing="0" border="0">
	      <tr>
			  <td width="20" height="25"></td>
			  <td width="134">Exception Type  </td>
			  <td width="170"><select name="ExceptionType" class="selectw"  onchange="SetAE();">
						<option value="0">HD Full</option>
						<option value="1">HD Error</option>
						<option value="2">Network Disconnect</option>
						<option value="3">Unauthorized Access</option>
						<option value="4">Network Conflict</option>
			</select></td>
		    <td colspan="3">&nbsp;</td>
		  </tr>
		  <tr>
			<td width="20" height="25">&nbsp;</td>
			<td width="134">Handle Method </td>
		    <td width="170"><input type="checkbox" name="ExTriggerVoice" value="1"/>Audible Warning</td>
		    <td width="158"><label id = "Center"><input type="checkbox" name="ExTriggerCenter" value="1"/>Control Center</label></td>
		    <td width="158"><label style="display:none"><input type="checkbox" name="ExTriggerMonitor" value="1"/>Alarm Preview</label></td>
		    <td width="139"></td>
		  </tr>
		  <tr>
			  <td colspan="2"></td>
			  <td colspan="4"><input type="checkbox" name="ExTriggerOutput" value="1" onclick="onExTriggerOutput()"/>Trigger Alarm Output</td>
		  </tr>
		  <tr>
			  <td colspan="2"></td>
			  <td>&nbsp;&nbsp;&nbsp;&nbsp;<input type="checkbox" name="ExTriggerOutput1" value="1" disabled/>Output 1</td>
			  <td><input type="checkbox" name="ExTriggerOutput2" value="1" disabled/>Output 2</td>
			  <td><input type="checkbox" name="ExTriggerOutput3" value="1" disabled/>Output 3</td>
			  <td><input type="checkbox" name="ExTriggerOutput4" value="1" disabled/>Output 4</td>
		  </tr>
		  <tr style="display:none">
			<td width="20" height="25">&nbsp;</td>
			<td width="134">Copy To </td>
		    <td width="170"><select name="AlarmExCopy" class="selectw">
						<option value="99">All </option>
						<option value="0">Harddisk Full</option>
						<option value="1">Harddisk Error</option>
						<option value="2">Network Failure</option>
						<option value="3">Illegal Access</option>
						<option value="4">Network Conflict</option>
			</select></td>
		    <td colspan="3"><input type="button" name="AlarmExCopyBt" value="Copy" class="myButton" onclick="OnAlarmExCopy();" /></td>
	      </tr>
	  </table>
	 </td>
  </tr>
  <tr>
	  <td colspan="6" class="menu1" height="25">&nbsp;Save all the parameters: <input name="button" type="button" class="myButton" value="Set" onclick="setAlarmCfg();" /></td>
  </tr>
  </table></form>
</body>
<div id="light" class="white_content">
<table width="100%" height="100%">
<tr><td width="5%" align="right"><img src="images/tips.gif" width="32" height="32" /></td><td width="95%" align="left"><label id="ctrTip" class="mybold"></label></td></tr>
</table>
</div> 
<iframe id="forShowTip" frameborder="0" class="myIFrame"></iframe>
<div id="fade" class="black_overlay"></div> 
</html>
