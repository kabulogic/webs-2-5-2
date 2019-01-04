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
		alert("录像参数设置不成功！");
	}
}

function assertPeriod()
{
	if(!period("RecPlan")){
		alert("录像计划表时间不正确！");
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

<body onload="initOptionChn('Channel','通道');initOptionChnCopy('CopyRe','通道','全部通道');initRecord()">
<iframe id="hideframe" name="hideframe" style="display:none ;"></iframe>
<div id="mainconfig">
<%chanparaGet("vMode");%>
<form name="RecordForm" action="/infinova/recparaCfg" method="post" target="hideframe">
<input type="hidden" name="flag" value="0" /><input type="hidden" name="operator" value="" /><input type="hidden" name="lang" value="cn">
  <table cellpadding="0" cellspacing="0" class="bttable" width="840">
  <tr class="menu1">
	  <td colspan="6" height="25">&nbsp;通道选择</td>
  </tr>
  <tr>
	  <td width="21" height="20"></td>
	  <td width="136">通道号：</td>
	  <td width="229"><select name="Channel" class="selectw" onchange="SetCh();">
	  </select></td>
	  <td width="80"><%chanparaGet("major");chanparaGet("minor");chanparaGet("record");%></td>
	  <td width="142">&nbsp;</td>
	  <td width="230">&nbsp;</td>
  </tr>
  <tr><td colspan="6"><div id="VideoPara"><table cellpadding="0" cellspacing="0">
  <tr>
	  <td colspan="6" class="menu1" height="25">&nbsp;录像设置</td>
  </tr>
  <tr>
	  <td width="20" height="20"></td>
	  <td width="136">类型：</td>
	  <td width="229">			
	  		<select name="StreamType" class="selectw" onchange="major_minor()">
				<option value="0" selected="selected">主码流</option>
				<option value="1">子码流</option>
			</select><input type="hidden" name="backStreamType" value="major" /></td>
	  <td width="80"></td>
	  <td width="141">码流类型：</td>
	  <td width="230"><select name="MixStream" class="selectw">
        <option value="0">视频流</option>
        <option value="1">复合流</option>
      </select></td>
  </tr>
  <tr>
	  <td width="20" height="20"></td>
	  <td width="136">分辨率：</td>
	  <td width="229"><select name="Resolution" class="selectw"></select></td>
	  <td width="80"></td>
	  <td width="141">帧率：</td>
	  <td width="230" valign="top"><input type="text" name="VOPRateDisplay" onchange="validateNum(this,1,(document.getElementById('VideoMode').value == 1)?25:30,'帧率范围:')" style="width:139px;position: absolute"/>
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
	  <td width="136">位率类型： </td>
	  <td width="229"><select name="BitRateType" class="selectw">
				<option value="0">变码率</option>
				<option value="1">定码率</option>
			</select></td>
	  <td width="80"></td>
	  <td width="141">位率上限：</td>
	  <td width="230"><select name="MaxBitRate" class="selectw">
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
	  <td width="136">质量：</td>
	  <td width="229">
	  		<select name="ImageQuality" class="selectw">
				<option value="0">差</option>
				<option value="1">较差</option>
				<option value="2">一般</option>
				<option value="3">较好</option>
				<option value="4">好</option>
			</select>	  </td>
	  <td width="80"></td>
	  <td width="141">IP比率：</td>
	  <td width="230"><input name ="IPRate" type="text" value ="10" width="154" onchange="validateNum(this,10,255,'IP比率范围:')" />
<!--<select name="IPRate" class="selectw">
						  <option value="2">2</option>
						  <option value="4">4</option>
						  <option value="8">8</option>
						  <option value="15">15</option>
						  <option value="20">20</option>
						  <option value="25">25</option>
						  <option value="30">30</option>
			    </select>--></td>
  </tr></table>
  </div></td></tr>
  <tr>
	  <td colspan="6" class="menu1" height="25">&nbsp;录像计划</td>
  </tr>
  <tr>
	  <td width="21" height="20"></td>
	  <td width="136">录像计划： </td>
	  <td width="229">
	  		<select name="RecordSetting" class="selectw">
				<option value="1">打开</option>
				<option value="0">关闭</option>
			</select>	  </td>
	  <td width="80"></td>
	  <td width="142">保存至： </td>
	  <td width="230"><label>硬盘</label>
  		<!--<select name="RecordTo" class="selectw">
				<option value="1">本地</option>
				<option value="2">网络</option>
				<option value="3">本地&amp;网络</option>
			</select>--></td>
  </tr>
  <tr>
	  <td width="21" height="20"></td>
	  <td width="136">预录时间： </td>
	  <td width="229">
	  		<select name="PreTime" class="selectw">
				<option value="0">不预录</option>
				<!--<option value="1">1秒</option>-->
				<option value="2">2秒</option>
				<option value="4">4秒</option>
				<option value="6">6秒</option>
				<option value="8">8秒</option>
				<!--<option value="10">10秒</option>-->
				<option value="255">最大限度</option>
			</select>	  </td>
	  <td width="80"></td>
	  <td width="142">录像延时： </td>
	  <td width="230">
	  		<select name="PostTime" class="selectw">
				<option value="0">无延时</option>
				<option value="5">5秒</option>
				<option value="10">10秒</option>
				<option value="30">30秒</option>
				<option value="60">1分钟</option>
				<option value="120">2分钟</option>
				<option value="300">5分钟</option>
				<option value="600">10分钟</option>
		</select>	  </td>
  </tr>
  <tr>
	  <td width="21" height="20"><input type="hidden" name="isRecordPlanChange" value="1"/></td>
	  <td colspan="5">
	  	<br />
		<table cellpadding="0" cellspacing="0" border="0" class="tableborder">
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
		<td height="30" align="center">
			<input type="text" readonly="readonly" style="width:40px;height:12px;background:green; border:1px solid #dddddd" />&nbsp;定时录像 
			<input type="text" readonly="readonly" style="width:40px;height:12px;background:red; border:1px solid #dddddd"  />&nbsp;报警录像 
			<input type="text" readonly="readonly" style="width:40px;height:12px;background:blue; border:1px solid #dddddd"  />
			&nbsp;定时或报警录像
		</td>
	</tr>
	<tr>
		<td height="30" align="center">录像类型&nbsp;
			<select name="alarmType" class="selectw">
				<option value="0">定时录像</option>
				<option value="1">报警录像</option>
				<option value="2">定时或报警录像</option></select>&nbsp;
			<input name="all" type="button" value="全选" onClick="selectRecordTime(1)" />&nbsp;<input name="no" type="button" value="清除" onClick="selectRecordTime(0)" />
		</td>
	</tr>
	<tr>
			<td height="25" colspan="2">说明：若要取消选择，请按住Ctrl键再拖选。</td>
	</tr>
</table><br />    
	  </td>
  </tr>
  <tr>
	  <td colspan="6" class="menu1" height="25">&nbsp;复制 </td>
  </tr>
  <tr>
	  <td width="21" height="25"></td>
	  <td>复制到</td>
	  <td><select name="CopyRe" class="selectw">
	  </select></td>
	  <td><input type="button" name="ReCopyBt" value="复&nbsp;&nbsp;制" class="myButton" onclick="OnReCopy();" /></td>
	  <td colspan="2"></td>
  </tr>
  <tr>
	  <td colspan="2" class="menu1" height="25">保存设置</td>
	  <td colspan="4" class="menu1"><input name="button" type="button" class="myButton" value="应&nbsp;&nbsp;用" onclick="setRecordCfg()" /></td>
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
