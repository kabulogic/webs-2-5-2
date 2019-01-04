<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7">
<title>Channel Info</title>
<link href="css/layout.css" rel="stylesheet" type="text/css" />
<link href="css/defend_recplan.css" rel="stylesheet" type="text/css" />
<script language="javascript" src="js/defend_recplan.js"></script>
<script language="javascript" src="js/cookie.js"></script>
<script language="javascript" src="js/common.js"></script>
<script language="javascript" src="js/alarm.js"></script>
<script language="javascript" src="js/chCtr.js"></script>
<script language="javascript" src="js/DefendTime.js"></script>
<script language="javascript" src="js/schedule.js"></script>
<script language="javascript" src="js/get_cfg.js"></script>
<script language="javascript" src="js/function.js"></script>
<script language="javascript" src="js/set_cfg.js"></script>
<script language="javascript" src="js/validate.js"></script>
<script language="javascript" src="js/control.js"></script>
<script language="JavaScript" type="text/JavaScript">
<!--
MM_reloadPage(true);

function getpara()
{
	var error = hasError();
	if(error == "1"){
		alert("Set channel info failed!");
	}
}

function assertPeriod()
{
	if(!period("MoDefendTime")){
		alert("Schedule of motion detection is illegal!");
		return false;
	}
	if(!period("ObsDefendTime")){
		alert("Schedule of view tampering is illegal!");
		return false;
	}
	if(!period("SigDefendTime")){
		alert("Schedule of signal loss is illegal!");
		return false;
	}
	return true;
}

function assertName(obj,txt)
{
	/*if(!isTrueName(obj)){
		alert(txt+" includes illegal characters.");
		window.event.returnValue=false;
		addcookie("seterror=1");
		return false;
	}*/
    window.event.returnValue = true;
	delcookie("seterror=1");
	return true;
}

function assertPW(obj)
{
	if(!isPasswd(obj)){
		alert("The password of channel is illegal!");
		window.event.returnValue=false;
		addcookie("seterror=1");
		return false;
	}
    window.event.returnValue = true;
	delcookie("seterror=1");
	return true;
}

function assertIP(obj)
{
	if(!isIP(obj)){
		alert("IP address error!");
		window.event.returnValue=false;
		addcookie("seterror=1");
		return false;
	}
    window.event.returnValue = true;
	delcookie("seterror=1");
	return true;
}

function osdHint()
{
	var error = setOsd();
	switch(error)
	{
		case 1:
			alert("Channel Name should not overlap with DateTime!");
			return false;
		case 2:
			alert("DateTime should not overlap with OSD1!");
			return false;
		case 3:
			alert("OSD1 should not overlap with OSD2!");
			return false;
		case 4:
			alert("OSD1 should not overlap with Channel Name!");
			return false;
		case 5:
			alert("OSD2 should not overlap with DateTime!");
			return false;
		case 6:
			alert("OSD2 should not overlap with Channel Name!");
			return false;
		case 0:
		default:
			return true;
			break;
	}
	return true;
}

function Click(){
window.event.returnValue=false;
}
document.oncontextmenu=Click;
//-->
</script>
</head>

<body onload="initOptionChn('Channel','Channel ');initOptionChn('PTZChannel','Channel ');initOptionChnCopy('CopyCh','Channel ','All Channels');initChannel()">
<iframe id="hideframe" name="hideframe" style="display:none;"></iframe>
<div id="mainconfig">
<form name="ChInfoForm" action="/infinova/chanparaCfg" method="post" target="hideframe">
<%chanparaGet("chinfo");chanparaGet("image");chanparaGet("osd");chanparaGet("privacy");chanparaGet("motion");chanparaGet("obstruct");chanparaGet("siglost");chanparaGet("vMode");%>
<input type="hidden" name="flag" value="0" /><input type="hidden" name="operator" value="" /><input type="hidden" name="lang" value="en">
  <table cellpadding="0" cellspacing="0" class="bttable" width="840">
  <tr class="menu1">
    <td colspan="6" height="25">&nbsp;Select Channel</td>
  </tr>
  <tr>
    <td height="25">&nbsp;</td>
    <td height="25">Select Channel:</td>
    <td height="25"><select name="Channel" class="selectw" onchange="SetCh()">
    </select></td>
    <td height="25">&nbsp;</td>
    <td height="25">&nbsp;</td>
    <td height="25">&nbsp;</td>
  </tr>
  <tr class="menu1">
	  <td colspan="6" height="25">&nbsp;Basic Info</td>
  </tr>
  <tr>
	  <td width="22" height="20"></td>
	  <td width="137">Channel Name:</td>
	  <td width="168"><input name="ChannelName"  maxlength="16"  onchange="validateOsdXY('ChannelName',document.getElementById('OSD2_X'),'x','Channel Name OSD_X:');validateOsdXY('ChannelName',document.getElementById('OSD2_Y'),'y','Channel Name OSD_Y:')" /></td>
	  <td width="131"></td>
	  <td width="119">&nbsp;</td>
	  <td width="261"><!--<label id="ChannelName"></label> --></td>
  </tr>
  <tr><td colspan="6"><div id="netChanInfo">
  <table cellpadding="0" cellspacing="0">
  <tr style="display:none">
		<td width="22" height="20"></td>
		<td width="137">IP:</td>
		<td width="168"><input name="ChannelIP" disabled="disabled" type="text" value="" onchange="assertIP(this)"/></td>
		<td width="131"></td>
		<td width="119">Port:</td>
		<td width="259"><input name="ChannelPort" disabled="disabled" type="text" value="0" onchange="isPort(this)"/></td>
  </tr></table></div></td></tr>
  <tr><td colspan="6"><div id="netChanInfo2" style="display:none">
  <table cellpadding="0" cellspacing="0">
  <tr>
		<td width="22" height="20"></td>
		<td width="149">User Name:</td>
		<td width="226"><input name="ChannelUser" type="text" value="" onchange="assertName(this,'User name')" /></td>
		<td width="68"></td>
		<td width="145">Password:</td>
		<td width="226"><input name="ChannelPass" type="password" class="passw" value="" onchange="assertPW(this)"/></td>
  </tr></table>
  </div></td></tr>
  <tr>
	  <td colspan="6"><div id="divColor" style="display:none"><table cellpadding="0" cellspacing="0">
  <tr>
	  <td colspan="6" class="menu1" height="25">&nbsp;Image Configuration</td>
  </tr>
  <tr>
	<td width="22" height="20"></td>
	<td width="149">Color:</td>
	<td width="161"><input name="Color" type="text" class="halfInput" value="0" onchange="validateNum(this,0,255,'Color range: ')"/>(0-255)</td>
	<td width="132"></td>
	<td width="146">Saturation:</td>
	<td width="228"><input name="Saturation" type="text" class="halfInput" value="0" onchange="validateNum(this,0,255,'Saturation range: ')"/>(0-255)</td>
  </tr>
  <tr>
	<td width="22" height="20"></td>
	<td width="149">Contrast:</td>
	<td width="161"><input name="Contrast" type="text" class="halfInput" value="0" onchange="validateNum(this,0,255,'Contrast range: ')"/>(0-255)</td>
	<td width="132"></td>
	<td width="146">Brightness:</td>
	<td width="228"><input name="Brightness" type="text" class="halfInput" value="0" onchange="validateNum(this,0,255,'Brightness range: ')"/>(0-255)</td>
  </tr></table></div></td></tr>
  <tr>
	  <td colspan="6"><div id="divOSD"><table cellpadding="0" cellspacing="0">
  
  <tr>
	  <td width="22" height="30"></td>
	  <td width="137">Channel Name: </td>
	  <td width="168"><select name="OSD2_State" class="selectw">
        <option value="1">Show</option>
        <option value="0">Hide</option>
      </select></td>
	  <td width="131"></td>
	  <td width="119">OSD X/Y: </td>
	  <td width="20">X:&nbsp;</td>
      <td width="239"><input name="OSD2_X" type="text" size="3" onchange="validateOsdXY('ChannelName',this,'x','Channel Name OSD_X:')"/>
&nbsp;&nbsp;Y:
<input name="OSD2_Y" type="text" size="3" onchange="validateOsdXY('ChannelName',this,'y','Channel Name OSD_Y:')"/></td>
  </tr>
  
  <tr>
	  <td width="22" height="30"></td>
	  <td width="137">Time:</td>
	  <td width="168"><select name="OSD1_State" class="selectw" onchange="selectTime()">
				<option value="1">Show</option>
        		<option value="0">Hide</option>
		</select>	  </td>
	  <td width="131"></td>
	  <td width="119">Date Format:</td>
	  <td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<!--<label name="DateFormat">YYYY-MM-DD</label>--></td>
      <td><select name="DateFormat" style="width:134px">
        <option value="0">YYYY-MM-DD</option>
        <option value="1">YYYY MM DD</option>
        <option value="2">YYYY/MM/DD</option>
        <option value="3">MM/DD/YYYY</option>
      </select></td>
  </tr>
  <tr>
	  <td width="22" height="30"></td>
	  <td width="137">Week:</td>
	  <td width="168"><select name="DisplayWeek" class="selectw">
				<option value="1">Show</option>
        <option value="0">Hide</option>
		</select></td>
	  <td width="131"></td>
	  <td width="119">OSD X/Y:</td>
	  <td>X:&nbsp;</td>
      <td><input name="OSD1_X" type="text" size="3" onchange="validateOsdXY('week',this,'x','Time OSD_X:')"/>	    
	    &nbsp;&nbsp;Y:
	    <input name="OSD1_Y" type="text" size="3" onchange="validateOsdXY('week',this,'y','Time OSD_Y:')"/></td>
  </tr>
  <tr>
    <td height="25" colspan="7" class="menu1">&nbsp;OSD  </td>
    </tr>
  <tr>
    <td height="30"></td>
    <td>Display State</td>
    <td>OSD Text</td>
    <td></td>
    <td>OSD Position </td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
  </tr>
  <tr>
    <td height="30"></td>
    <td><input name="OSD3_State" type="checkbox" value="1" />
	  OSD1</td>
    <td><input type="text" name="OSD3_Title" maxlength="16" onchange="validateOsdXY('OSD3_Title',document.getElementById('OSD3_X'),'x','OSD1 OSD_X:');validateOsdXY('OSD3_Title',document.getElementById('OSD3_Y'),'y','OSD1 OSD_Y:')" /></td>
    <td></td>
    <td>OSD X/Y:</td>
    <td>X:&nbsp;</td>
    <td><input name="OSD3_X" type="text" size="3" onchange="validateOsdXY('OSD3_Title',this,'x',' OSD1 OSD_X:')"/>
      &nbsp;&nbsp;Y:
      <input name="OSD3_Y" type="text" size="3" onchange="validateOsdXY('OSD3_Title',this,'y','OSD1 OSD_Y:')"/></td>
  </tr>
  <tr>
    <td height="30"></td>
    <td><input name="OSD4_State" type="checkbox" value="1" /> 
      OSD2 </td>
    <td><input type="text" name="OSD4_Title" maxlength="16" onchange="validateOsdXY('OSD4_Title',document.getElementById('OSD4_X'),'x','OSD2 OSD_X:');validateOsdXY('OSD4_Title',document.getElementById('OSD4_Y'),'y','OSD2 OSD_Y:')" /></td>
    <td></td>
    <td>OSD X/Y:</td>
    <td>X:&nbsp;</td>
    <td><input name="OSD4_X" type="text" size="3" onchange="validateOsdXY('OSD4_Title',this,'x','OSD2 OSD_X:')"/>
      &nbsp;&nbsp;Y:
      <input name="OSD4_Y" type="text" size="3" onchange="validateOsdXY('OSD4_Title',this,'y','OSD2 OSD_Y:')"/></td>
  </tr>
  </table>
	  </div></td></tr>
  <tr>
	  <td colspan="6"><div id="divPri"><table width="840" cellpadding="0" cellspacing="0">
  <tr>
	  <td colspan="6" class="menu1" height="25">&nbsp;Area Settings</td>
  </tr>
  <tr>
	  <td width="21"></td>
	  <td colspan="5">
	  <iframe id="AreaFrame0" src="" style="display:none" frameborder="0" scrolling="no" width="690" height="310"></iframe>	  </td>
  </tr>
  </table></div></td></tr>
  <tr>
	  <td colspan="6" class="menu1" height="25">&nbsp;Video Loss Alarm</td>
  </tr>
  <tr>
	  <td width="22" height="28"><input type="hidden" name="isSigPlanChange" value="1"/></td>
	  <td><input type="checkbox" name="SigEnable" value="1" onclick="onSigEnable()"/>Enable</td>
	  <td><input type="button" class="btChan" name="SigDefend" value="Schedule" onclick="onSigDefend();" /></td>
	  <td><input type="button" class="btChan" name="SigMethod" value="Output" onclick="onSigMethod();" /></td>
	  <td colspan="2">&nbsp;</td>
  </tr>
  <tr>
	  <td></td>
	  <td colspan="5">
  <div id="SigDefendTime" style="display:none">
  <br /><table cellpadding="0" cellspacing="0" border="0" class="tableborder">
		<tr onmouseover="setFlag(0)">
			<td class="cancel"  height="30">&nbsp;</td>
			<td id="time" class="cancel" colspan="48">
				<table id="sigttb" width="518" align="left" cellpadding="0" cellspacing="0" border="0"></table>			</td>
		</tr>
		<tr>
			<td id="week" class="cancel" valign="top" rowspan="9" onmouseover="setFlag(0)">
				<table style="font:12px;" id="sigwtb" height="210" cellpadding="0" cellspacing="0" border="0"></table>			</td>
			<td>
				<table name='sigtb0' id="sigtb0" class="defend" cellpadding="0" cellspacing="0" width="480" ></table>			</td>
			<td height="30" valign="bottom" onmouseover="setFlag(0)">
			<table  name='sigtb0' id="sigviewtime" height="210" cellpadding="0" cellspacing="0" width="48" ></table>			</td>
		</tr>
		<tr onmouseover="setFlag(0)">
		  <td height="25" align="center"><input name="all2" type="button" value="Select All" onclick="selectDefendTime(1,'sig')" onmouseover="setFlag(0)" />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input name="no2" type="button" value="Clear All" onclick="selectDefendTime(0,'sig')" onmouseover="setFlag(0)" /></td>
			<td>&nbsp;</td>
		  </tr>
		<tr onmouseover="setFlag(0)">
			<td height="25" colspan="2"><p>Note:if clean out a part of selecting,please press &quot;Ctrl&quot; key and then drag.</td>
		</tr>
		</table><br /></div>  </td></tr>
  <tr>
	  <td></td>
	  <td colspan="5">
  <div id="SigHandleMethod" style="display:none">
  <table cellpadding="0" cellspacing="0" class="subtable">
  <tr>
	  <td width="142">&nbsp;Handle Method</td>
	  <td width="157"><input type="checkbox" name="SigTriggerVoice" value="1"/>Audible Warning</td>
	  <td width="128"><input type="checkbox" name="SigTriggerCenter" value="1"/>Control Center</td>
	  <td colspan="2"><input type="checkbox" name="SigTriggerMonitor" value="1"/>Alarm Preview</td>
  </tr>
  <tr>
	  <td width="142"></td>
	  <td colspan="4"><input type="checkbox" name="SigTriggerOutput" value="1" onclick="onTriggerOutput('Sig')"/>Trigger Alarm Output</td>
  </tr>
  <tr>
	  <td width="142"></td>
	  <td>&nbsp;&nbsp;&nbsp;&nbsp;<input type="checkbox" name="SigTriggerOutput1" value="1" disabled/>Output 1</td>
	  <td><input type="checkbox" name="SigTriggerOutput2" value="1" disabled/>Output 2</td>
	  <td width="143"><input type="checkbox" name="SigTriggerOutput3" value="1" disabled/>Output 3</td>
	  <td width="208"><input type="checkbox" name="SigTriggerOutput4" value="1" disabled/>Output 4</td>
  </tr>
  </table>
  </div></td></tr>
  <tr>
	  <td colspan="6"><div id="divObs"><table cellpadding="0" cellspacing="0">
  <tr>
	  <td colspan="6" class="menu1" height="25">&nbsp;Video Mask Alarm </td>
  </tr>
  <tr>
	  <td width="22" height="28"></td>
	  <td width="137"><input type="checkbox" name="ObsEnable" value="1" onclick="onObsEnable()"/>Enable</td>
	  <td width="168">Sensitivity:	    
	    <select name="ObsLevel">
          <option value="0">High</option>
          <option value="1">Middle</option>
          <option value="2">Low</option>
        </select></td>
	  <td width="131"><input type="button" class="btChan" name="ObstructDefend" value="Schedule" onclick="onObstructDefend();" /></td>
	  <td width="247"><input type="button" class="btChan" name="ObstructMethod" value="Output" onclick="onObstructMethod();" /></td>
	  <td width="131">&nbsp;</td>
  </tr>
  </table>
	  </div></td></tr>
  <tr>
	  <td width="22"><input type="hidden" name="isObsPlanChange" value="0"/></td>
	  <td colspan="5">
  		<div id="ObsDefendTime" style="display:none">
		<br />
		<table cellpadding="0" cellspacing="0" border="0" class="tableborder">
		<tr onmouseover="setFlag(0)">
			<td class="cancel"  height="30">&nbsp;</td>
			<td id="time" class="cancel" colspan="48">
				<table id="obsttb" width="518" align="left" cellpadding="0" cellspacing="0" border="0"></table>			</td>
		</tr>
		<tr>
			<td id="week" class="cancel" valign="top" rowspan="9" onmouseover="setFlag(0)">
				<table style="font:12px;" id="obswtb" height="210" cellpadding="0" cellspacing="0" border="0"></table>			</td>
			<td>
				<table name='obstb0' id="obstb0" class="defend" cellpadding="0" cellspacing="0" width="480" ></table>			</td>
			<td height="30" valign="bottom" onmouseover="setFlag(0)">
			<table  name='obstb0' id="obsviewtime" height="210" cellpadding="0" cellspacing="0" width="48" ></table>			</td>
		</tr>
		<tr onmouseover="setFlag(0)">
		  <td height="25" align="center"><input name="all2" type="button" value="Selects All" onclick="selectDefendTime(1,'obs')" onmouseover="setFlag(0)" />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input name="no2" type="button" value="Clear All" onclick="selectDefendTime(0,'obs')" onmouseover="setFlag(0)" /></td>
			<td>&nbsp;</td>
		  </tr>
		<tr onmouseover="setFlag(0)">
			<td height="25" colspan="2"><p>Note:if clean out a part of selecting,please press &quot;Ctrl&quot; key and then drag.</td>
		</tr>
		</table> <br />   
		</div>  	  </td>
  </tr>
  <tr>
	  <td></td>
	  <td colspan="5">
  <div id="ObsHandleMethod" style="display:none">
  <table cellpadding="0" cellspacing="0" class="subtable">
  <tr>
	  <td width="142">&nbsp;Handle Method</td>
	  <td width="157"><input type="checkbox" name="ObsTriggerVoice" value="1"/>Audible Warning</td>
	  <td width="128"><input type="checkbox" name="ObsTriggerCenter" value="1"/>Control Center</td>
	  <td colspan="2"><input type="checkbox" name="ObsTriggerMonitor" value="1"/>Alarm Preview</td>
  </tr>
  <tr>
	  <td width="142"></td>
	  <td colspan="4"><input type="checkbox" name="ObsTriggerOutput" value="1" onclick="onTriggerOutput('Obs')"/>Trigger Alarm Output</td>
  </tr>
  <tr>
	  <td width="142"></td>
	  <td>&nbsp;&nbsp;&nbsp;&nbsp;<input type="checkbox" name="ObsTriggerOutput1" value="1" disabled/>Output 1</td>
	  <td><input type="checkbox" name="ObsTriggerOutput2" value="1" disabled/>Output 2</td>
	  <td width="143"><input type="checkbox" name="ObsTriggerOutput3" value="1" disabled/>Output 3</td>
	  <td width="208"><input type="checkbox" name="ObsTriggerOutput4" value="1" disabled/>Output 4</td>
  </tr>
  </table>
  </div></td></tr>
  <tr>
	  <td colspan="6" class="menu1" height="25">&nbsp;Motion Detecion</td>
  </tr>
  <tr><td colspan="6"><div id="div3">
  <table cellpadding="0" cellspacing="0">
  <tr>
	  <td width="22" height="28"></td>
	  <td width="137"><input type="checkbox" name="MotionEnable" value="1" onclick="onMoEnable()"/>Enable</td>
	  <td width="168">Sensitivity:
	    <select name="MoLevel" disabled>
	      <option value="0">High</option>
	      <option value="1">Middle</option>
	      <option value="2">Low</option>
	      </select></td>
	  <td width="131"><input type="button" class="btChan" name="ckMoSchedule" value="Schedule" onclick="onMotionDefend();" /></td>
	  <td width="247"><input type="button" class="btChan" name="MotionHandleContact" value="Linkage" onclick="onMotionContact();onSelectPTZCh();" /></td>
	  <td width="131">&nbsp;</td>
  </tr></table></div></td></tr>
  <tr>
	  <td width="22"><input type="hidden" name="isMotionPlanChange" value="0"/></td>
	  <td colspan="5">
  		<div id="MotionDefendTime" style="display:none">
			<br />
			<table cellpadding="0" cellspacing="0" border="0" class="tableborder">
		<tr onmouseover="setFlag(0)">
			<td class="cancel"  height="30">&nbsp;</td>
			<td id="time" class="cancel" colspan="48">
				<table id="motionttb" width="518" align="left" cellpadding="0" cellspacing="0" border="0"></table>			</td>
		</tr>
		<tr>
			<td id="week" class="cancel" valign="top" rowspan="9" onmouseover="setFlag(0)">
				<table style="font:12px;" id="motionwtb" height="210" cellpadding="0" cellspacing="0" border="0"></table>			</td>
			<td>
				<table name='motiontb0' id="motiontb0" class="defend" cellpadding="0" cellspacing="0" width="480" ></table>			</td>
			<td height="30" valign="bottom" onmouseover="setFlag(0)">
			<table  name='motiontb0' id="motionviewtime" height="210" cellpadding="0" cellspacing="0" width="48" ></table>			</td>
		</tr>
		<tr onmouseover="setFlag(0)">
		  <td height="25" align="center"><input name="all2" type="button" value="Select All" onclick="selectDefendTime(1,'motion')" onmouseover="setFlag(0)" />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input name="no2" type="button" value="Clear All" onclick="selectDefendTime(0,'motion')" onmouseover="setFlag(0)" /></td>
			<td>&nbsp;</td>
		  </tr>
		<tr onmouseover="setFlag(0)">
			<td height="25" colspan="2"><p>Note:if clean out a part of selecting,please press &quot;Ctrl&quot; key and then drag.</td>
		</tr>
		</table> <br />   
		</div>	  </td>
  </tr>
  <tr>
	  <td></td>
	  <td colspan="5">
  <div id="MotionAlarmContact" style="display:none">
  <table cellpadding="0" cellspacing="0" class="subtable">
  <tr id="reRow1">
	  <td width="142">&nbsp;Record Channel</td>
	  <td><input type="checkbox" name="MotionRecordChannel1" value="1"/>Channel 01</td>
	  <td><input type="checkbox" name="MotionRecordChannel2" value="1"/>Channel 02</td>
	  <td><input type="checkbox" name="MotionRecordChannel3" value="1"/>Channel 03</td>
	  <td><input type="checkbox" name="MotionRecordChannel4" value="1"/>Channel 04</td></tr>
  <tr id="reRow2">
	  <td width="142"></td>
	  <td><input type="checkbox" name="MotionRecordChannel5" value="1"/>Channel 05</td>
	  <td><input type="checkbox" name="MotionRecordChannel6" value="1"/>Channel 06</td>
	  <td><input type="checkbox" name="MotionRecordChannel7" value="1"/>Channel 07</td>
	  <td><input type="checkbox" name="MotionRecordChannel8" value="1"/>Channel 08</td></tr>
  <tr id="reRow3" style="display:none">
	  <td width="142"></td>
	  <td><input type="checkbox" name="MotionRecordChannel9" value="1"/>Channel 09</td>
	  <td><input type="checkbox" name="MotionRecordChannel10" value="1"/>Channel 10</td>
	  <td><input type="checkbox" name="MotionRecordChannel11" value="1"/>Channel 11</td>
	  <td><input type="checkbox" name="MotionRecordChannel12" value="1"/>Channel 12</td></tr>
  <tr id="reRow4" style="display:none">
	  <td width="142"></td>
	  <td><input type="checkbox" name="MotionRecordChannel13" value="1"/>Channel 13</td>
	  <td><input type="checkbox" name="MotionRecordChannel14" value="1"/>Channel 14</td>
	  <td><input type="checkbox" name="MotionRecordChannel15" value="1"/>Channel 15</td>
	  <td><input type="checkbox" name="MotionRecordChannel16" value="1"/>Channel 16</td></tr>
	  <td width="142">&nbsp;</td>
	  <td><input type="button" name="AllChannel" value="All" class="myButton" onclick="onTriggerRecordChan('MotionRecordChannel',1);setObjectByName('isMotionPlanChange','1');"/></td>
	  <td colspan="3"><input type="button" name="NoneChannel" value="None" class="myButton" onclick="onTriggerRecordChan('MotionRecordChannel',0);setObjectByName('isMotionPlanChange','1');"/></td>  </tr>
  <tr class="sublist">
	  <td width="142" height="20">&nbsp;PTZ</td>
	  <td>Channel</td>
	  <td colspan="3"><select name="PTZChannel" class="selectw" onchange="SetbackMDPTZ();onSelectPTZCh();">
	  </select><input type="hidden" name="backPTZCh" value="0"/><input type="hidden" name="isPTZChChange" value="0"/></td>
  </tr>
  <tr><td width="142"></td>
  <td><input name="preset" type="checkbox" value="1" onclick="SetPreset();setObjectByName('isPTZChChange','1');"/>Preset</td><td colspan="3"><input type="text" name="PresetValue" disabled onchange="validateNum(this,1,255,'Preset range: ');setObjectByName('isPTZChChange','1');" /></td>
  </tr>
  <tr><td width="142"></td>
  <td><input name="cruise" type="checkbox" value="1" onclick="SetCruise();setObjectByName('isPTZChChange','1');" />Pattern</td><td colspan="3"><input type="text" name="CruiseValue" disabled onchange="validateNum(this,1,4,'Pattern range: ');setObjectByName('isPTZChChange','1');" /></td>
  </tr>
  <tr>
	  <td width="142">&nbsp;Handle Method</td>
	  <td width="157"><input type="checkbox" name="MotionTriggerVoice" value="1"/>Audible Warning</td>
	  <td width="128"><input type="checkbox" name="MotionTriggerCenter" value="1"/>Control Center</td>
	  <td colspan="2"><input type="checkbox" name="MotionTriggerMonitor" value="1"/>Alarm Preview</td>
  </tr>
  <tr>
	  <td width="142"></td>
	  <td colspan="4"><input type="checkbox" name="MotionTriggerOutput" value="1" onclick="onTriggerOutput('Motion')"/>Trigger Alarm Output</td>
  </tr>
  <tr>
	  <td width="142"></td>
	  <td>&nbsp;&nbsp;&nbsp;&nbsp;<input type="checkbox" name="MotionTriggerOutput1" value="1" disabled/>Output 1</td>
	  <td><input type="checkbox" name="MotionTriggerOutput2" value="1" disabled/>Output 2</td>
	  <td width="143"><input type="checkbox" name="MotionTriggerOutput3" value="1" disabled/>Output 3</td>
	  <td width="208"><input type="checkbox" name="MotionTriggerOutput4" value="1" disabled/>Output 4</td>
  </tr>
  </table>
  </div></td></tr>
  <tr>
	  <td colspan="6" class="menu1" height="25">&nbsp;Copy To </td>
  </tr>
  <tr>
	  <td width="22" height="25"></td>
	  <td>Copy To</td>
	  <td><select name="CopyCh" class="selectw">
	  </select></td>
	  <td colspan="3"><input type="button" name="ChCopyBt" value="Copy" class="myButton" onclick="OnChCopy();" />
	    (Basic info、OSD and Area can not be copied)</td>
  </tr>
  <tr>
	  <td colspan="6" class="menu1" height="25">Save all the parameters: <input name="button" type="button" class="myButton" value="Set" onclick="setChCfg()" /></td>
  </tr>
  </table>
</form>
</div>
<div id="light" class="white_content">
<table width="100%" height="100%">
<tr><td width="5%" align="right"><img src="images/tips.gif" width="32" height="32" /></td><td width="95%" align="left"><label id="ctrTip" class="mybold"></label></td></tr>
</table>
</div> 
<iframe id="forShowTip" frameborder="0" class="myIFrame"></iframe>
<div id="fade" class="black_overlay"></div> 
</body>
</html>
