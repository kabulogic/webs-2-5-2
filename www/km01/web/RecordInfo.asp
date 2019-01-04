<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7">
<title>Record Info</title>
<link href="css/layout.css" rel="stylesheet" type="text/css" />
<link href="css/defend_recplan.css" rel="stylesheet" type="text/css" />
<script language="javascript" src="js/defend_recplan.js"></script>
<script language="javascript" src="js/cookie.js"></script>
<script language="javascript" src="js/common.js"></script>
<script language="javascript" src="js/alarm.js"></script>
<script language="javascript" src="js/chCtr.js"></script>
<script language="javascript" src="js/schedule.js"></script>
<script language="javascript" src="js/get_record.js"></script>
<script language="javascript" src="js/function.js"></script>
<script language="javascript" src="js/set_record.js"></script>
<script language="javascript" src="js/validate.js"></script>
<script language="javascript" src="js/control.js"></script>
<script language="JavaScript" type="text/JavaScript">
<!--
MM_reloadPage(true);

function getpara()
{
	var error = hasError();
	if(error == "1"){
		alert("Set record failed!");
	}
}

function assertPeriod()
{
	if(!period("RecPlan")){
		alert("Schedule of record is illegal!");
		return false;
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

<body onload="initOptionChn('Channel','Channel ');initOptionChnCopy('CopyRe','Channel ','All Channels');initRecord()">
<iframe id="hideframe" name="hideframe" style="display:none ;"></iframe>
<div id="mainconfig">
<%chanparaGet("vMode");%>
<form name="RecordForm" action="/infinova/recparaCfg" method="post" target="hideframe">
<input type="hidden" name="flag" value="0" /><input type="hidden" name="operator" value="" /><input type="hidden" name="lang" value="en">
  <table cellpadding="0" cellspacing="0" class="bttable" width="840">
  <tr class="menu1">
	  <td colspan="6" height="25">&nbsp;Channels</td>
  </tr>
  <tr>
	  <td width="22" height="20"></td>
	  <td width="147">Select Channel:</td>
	  <td width="229"><select name="Channel" class="selectw" onchange="SetCh();">
	  </select></td>
	  <td width="59"><%chanparaGet("major");chanparaGet("minor");chanparaGet("record");%></td>
	  <td width="147">&nbsp;</td>
	  <td width="234">&nbsp;</td>
  </tr>
  <tr><td colspan="6"><div id="VideoPara"><table cellpadding="0" cellspacing="0">
  <tr>
	  <td colspan="6" class="menu1" height="25">&nbsp;Video Configuration</td>
  </tr>
  <tr>
	  <td width="20" height="20"></td>
	  <td width="142">Stream Type:</td>
	  <td width="233">			
	  		<select name="StreamType" class="selectw" onchange="major_minor()">
				<option value="0" selected="selected">Major Stream</option>
				<option value="1">Minor Stream</option>
			</select><input type="hidden" name="backStreamType" value="major" /></td>
	  <td width="71"></td>
	  <td width="142">Stream:</td>
	  <td width="228"><select name="MixStream" class="selectw">
        <option value="0">Video</option>
        <option value="1">Composite Stream</option>
      </select></td>
  </tr>
  <tr>
	  <td width="20" height="20"></td>
	  <td width="142">Resolution:</td>
	  <td width="233"><select name="Resolution" class="selectw"></select></td>
	  <td width="71"></td>
	  <td width="142">Frame Rate: </td>
	  <td width="228" valign="top"><input type="text" name="VOPRateDisplay" onchange="validateNum(this,1,(document.getElementById('VideoMode').value == 1)?25:30,'IP Rate range: ')" style="width:139px;position: absolute"/>
	    <input type="hidden" name="VOPRate" value = "30"/>
	    <select name="framerateSelect" onchange="FrameRateSwitch()" style="width:155px; clip: rect(auto auto auto 138px); position: absolute;">
          <option value="1">1</option>
          <option value="2">2</option>
          <option value="4">4</option>
          <option value="8">8</option>
          <option value="15">15</option>
          <option value="20">20</option>
          <option value="30">P25/N30</option>
        </select>
	  <!--<select name="VOPRate" class="selectw">
				<option value="15">15</option>
				<option value="20">20</option>
				<option value="30">P25/N30</option>
			</select>--></td>
  </tr>
  <tr>
	  <td width="20" height="20"></td>
	  <td width="142">Bit Rate Type: </td>
	  <td width="233"><select name="BitRateType" class="selectw">
				<option value="0">Variable</option>
				<option value="1">Constant</option>
			</select></td>
	  <td width="71"></td>
	  <td width="142">Max BitRate:</td>
	  <td width="228"><select name="MaxBitRate" class="selectw">
	  	<option value="256">256Kps</option>
        <option value="512">512Kps</option>
        <option value="640">640Kps</option>
        <option value="768">768Kps</option>
        <option value="896">896Kps</option>
        <option value="1024">1024Kps</option>
        <option value="1280">1280Kps</option>
        <option value="1536">1536Kps</option>
        <option value="1792">1792Kps</option>
        <option value="2048">2048Kps</option>
		<option value="2560">2560Kps</option>
      </select></td>
  </tr>
  <tr>
	  <td width="20" height="20"></td>
	  <td width="142">Quality:</td>
	  <td width="233">
	  		<select name="ImageQuality" class="selectw">
				<option value="0">Bad</option>
				<option value="1">Low</option>
				<option value="2">Normal</option>
				<option value="3">Medium</option>
				<option value="4">High</option>
			</select>	  </td>
	  <td width="71"></td>
	  <td width="142">IP Rate :</td>
	  <td width="228"><input name ="IPRate" type="text" value ="10" width="154" onchange="validateNum(this,10,255,'IP Rate range: ')" /><!--<select name="IPRate" class="selectw">
						  <option value="2">2</option>
						  <option value="4">4</option>
						  <option value="8">8</option>
						  <option value="15">15</option>
						  <option value="20">20</option>
						  <option value="25">25</option>
						  <option value="30">30</option>
			    </select>--></td>
  </tr>
  </table></div></td></tr>
  <tr>
	  <td colspan="6" class="menu1" height="25">&nbsp;Record Plan</td>
  </tr>
  <tr>
	  <td width="22" height="20"></td>
	  <td width="147">Recording: </td>
	  <td width="229">
	  		<select name="RecordSetting" class="selectw">
				<option value="1">ON</option>
				<option value="0">OFF</option>
			</select>	  </td>
	  <td width="59"></td>
	  <td width="147">Recording To: </td>
	  <td width="234"><label>Harddisk</label>
	  		<!--<select name="RecordTo" class="selectw">
				<option value="1">Local</option>
				<option value="2">Network</option>
				<option value="3">Local & Network</option>
			</select>--></td>
  </tr>
  <tr>
	  <td width="22" height="20"></td>
	  <td width="147">Pre-recording: </td>
	  <td width="229">
	  		<select name="PreTime" class="selectw">
				<option value="0">No Pre-Recording</option>
				<!--<option value="1">1 s</option>-->
				<option value="2">2 s</option>
				<option value="4">4 s</option>
				<option value="6">6 s</option>
				<option value="8">8 s</option>
				<!--<option value="10">10 s</option>-->
				<option value="255">Maximum</option>
			</select>	  </td>
	  <td width="59"></td>
	  <td width="147">Delay Time: </td>
	  <td width="234">
	  		<select name="PostTime" class="selectw">
				<option value="0">No Delay Time</option>
				<option value="5">5 s</option>
				<option value="10">10 s</option>
				<option value="30">30 s</option>
				<option value="60">1 min</option>
				<option value="120">2 min</option>
				<option value="300">5 min</option>
				<option value="600">10 min</option>
			</select>	  </td>
  </tr>
  <tr>
	  <td width="21" height="20"><input type="hidden" name="isRecordPlanChange" value="1"/></td>
	  <td colspan="5">
	  	<br /><table cellpadding="0" cellspacing="0" border="0" class="tableborder">
	<tr onmouseover="setFlag(0)">
			<td class="cancel"  height="30">&nbsp;</td>
			<td id="time" class="cancel" colspan="48">
				<table id="recttb" width="518" align="left" cellpadding="0" cellspacing="0" border="0"></table>				
			</td>
		</tr>
		<tr>
			<td id="week" class="cancel" valign="top" rowspan="9" onmouseover="setFlag(0)">
				<table style="font:12px;" id="recwtb" height="210" cellpadding="0" cellspacing="0" border="0"></table>			
			</td>
			<td>
				<table name='rectb0' id="rectb0" class="defend" cellpadding="0" cellspacing="0" width="480" ></table>			
			</td>
			<td height="30" valign="bottom" onmouseover="setFlag(0)">
			<table  name='rectb0' id="recviewtime" height="210" cellpadding="0" cellspacing="0" width="48" ></table>
			</td>
		</tr>
	<tr onmouseover="setFlag(0)">
		<td height="30" align="center"><input type="text" readonly="readonly" style="width:40px;height:12px;background:green; border:1px solid #dddddd" />Time Recording  
			<input type="text" readonly="readonly" style="width:40px;height:12px;background:red; border:1px solid #dddddd" />Alarm Recording  
			<input type="text" readonly="readonly" style="width:40px;height:12px;background:blue; border:1px solid #dddddd" />Time or Alarm Recording	</td>
	</tr>
	<tr>
		<td height="30" align="center">
			Recording Type &nbsp;
			<select name="alarmType" class="selectw">
				<option value="0">Time Recording</option>
				<option value="1">Alarm Recording</option>
				<option value="2">Time or Alarm Recording</option></select>&nbsp;
			<input name="all" type="button" value="Select All" onClick="selectRecordTime(1)" />&nbsp;<input name="no" type="button" value="Clear All" onClick="selectRecordTime(0)" />
		</td>
	</tr>
	<tr onmouseover="setFlag(0)">
		<td height="25" colspan="2"><p>Note:if clean out a part of selecting,please press &quot;Ctrl&quot; key and then drag.</td>
	</tr>
</table><br />    
	  </td>
  </tr>
  
  <tr>
	  <td colspan="6" class="menu1" height="25">&nbsp;Copy To </td>
  </tr>
  <tr>
	  <td width="22" height="25"></td>
	  <td>Copy To</td>
	  <td><select name="CopyRe" class="selectw">
	  </select></td>
	  <td><input type="button" name="ReCopyBt" value="Copy" class="myButton" onclick="OnReCopy();" /></td>
	  <td colspan="2"></td>
  </tr>
  <tr>
	  <td colspan="6" class="menu1" height="25">Save all the parameters: <input name="button" type="button" class="myButton" value="Set" onclick="setRecordCfg()" /></td>
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
