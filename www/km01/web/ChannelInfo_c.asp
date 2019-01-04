<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7">
<title>通道设置</title>
<link href="css/layout.css" rel="stylesheet" type="text/css" />
<link href="css/defend_recplan.css" rel="stylesheet" type="text/css" />
<script language="javascript" src="js/defend_recplan.js"></script>
<script language="javascript" src="js/cookie.js"></script>
<script language="javascript" src="js/common.js"></script>
<script language="javascript" src="js/alarm.js"></script>
<script language="javascript" src="js/chCtr.js"></script>
<script language="javascript" src="js/schedule.js"></script>
<script language="javascript" src="js/get_cfg.js"></script>
<script language="javascript" src="js/function.js"></script>
<script language="javascript" src="js/validate.js"></script>
<script language="javascript" src="js/set_cfg.js"></script>
<script language="javascript" src="js/control.js"></script>
<script language="JavaScript" type="text/JavaScript">
<!--
MM_reloadPage(true);

function getpara()
{
	var error = hasError();
	if(error == "1"){
		alert("通道参数设置不成功！");
	}
}

function assertName(obj,txt)
{
	/*if(!isTrueName(obj)){
		alert(txt+"包含特殊字符.");
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
		alert("通道密码不正确！");
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
		alert("IP地址格式不正确！");
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
			alert("通道名称与日期时间位置不能重叠交错显示！");
			return false;
		case 2:
			alert("日期时间与OSD1位置不能重叠交错显示！");
			return false;
		case 3:
			alert("OSD1与OSD2位置不能重叠交错显示！");
			return false;
		case 4:
			alert("OSD1与通道名称位置不能重叠交错显示！");
			return false;
		case 5:
			alert("OSD2与日期时间位置不能重叠交错显示！");
			return false;
		case 6:
			alert("OSD2与通道名称位置不能重叠交错显示！");
			return false;
		case 0:
		default:
			return true;
			break;
	}
	return true;
}

function osdTips()
{
	alert("OSD X坐标设置规则:每个OSD位置不能交叉,\n\nX坐标可设范围(0,672),Y坐标可设范围(0,P540/N444),\n\n根据每个OSD宽度占32*字符长度,高度占36规则计算");
}

function Click(){
window.event.returnValue=false;
}
document.oncontextmenu=Click;
//-->
</script>
</head>

<body onload="initOptionChn('Channel','通道');initOptionChn('PTZChannel','通道');initOptionChnCopy('CopyCh','通道','全部通道');initChannel();delcookie('seterror=1')">
<iframe id="hideframe" name="hideframe" style="display:none ;"></iframe>
<div id="mainconfig">
<form name="ChInfoForm" action="/infinova/chanparaCfg" method="post" target="hideframe">
<%chanparaGet("chinfo");chanparaGet("image");chanparaGet("osd");chanparaGet("privacy");chanparaGet("motion");chanparaGet("obstruct");chanparaGet("siglost");chanparaGet("vMode");%>
<input type="hidden" name="flag" value="0" /><input type="hidden" name="operator" value="" /><input type="hidden" name="lang" value="cn">
  <table cellpadding="0" cellspacing="0" class="bttable" width="840">
  <tr class="menu1">
    <td colspan="6" height="25">&nbsp;通道选择</td>
  </tr>
  <tr>
    <td width="22" height="20">&nbsp;</td>
    <td width="137" height="25">通道号：</td>
    <td height="25"><select name="Channel" class="selectw" onchange="SetCh()">
    </select></td>
    <td width="460" height="25">&nbsp;</td>
    <td width="27" height="25">&nbsp;</td>
    <td width="26" height="25">&nbsp;</td>
  </tr>
  <tr class="menu1">
	  <td colspan="6" height="25">&nbsp;基本信息 </td>
  </tr>
  <tr><td colspan="6"><div id="div1">
  <table cellpadding="0" cellspacing="0">
  <tr>
	  <td width="22" height="20"></td>
	  <td width="137">通道名称：</td>
	  <td width="170"><input name="ChannelName" maxlength="16" onchange="validateOsdXY('ChannelName',document.getElementById('OSD2_X'),'x','通道名称OSD_X范围是：');validateOsdXY('ChannelName',document.getElementById('OSD2_Y'),'y','通道名称OSD_Y范围是：')" /></td>
	  <td width="132"></td> 
	  <td width="120">&nbsp;</td>
	  <td width="257"><!--<label id="ChannelName"></label>--></td>
  </tr></table></div></td></tr>
  <tr><td colspan="6"><div id="netChanInfo">
  <table cellpadding="0" cellspacing="0">
  <tr style="display:none;">
		<td width="22" height="20"></td>
		<td width="137">IP地址：</td>
		<td width="170"><input name="ChannelIP" disabled="disabled" type="text" value="" onchange="assertIP(this)"/></td>
		<td width="132"></td>
		<td width="120">端&nbsp;&nbsp;&nbsp;口：</td>
		<td width="255"><input name="ChannelPort" disabled="disabled" type="text" value="0" onchange="isPort(this)"/></td>
  </tr></table></div></td></tr>
  <tr><td colspan="6"><div id="netChanInfo2" style="display:none">
  <table cellpadding="0" cellspacing="0">
  <tr>
		<td width="22" height="20"></td>
		<td width="149">用户名：</td>
		<td width="226"><input name="ChannelUser" type="text" value="" onchange="assertName(this,'通道用户名')" /></td>
		<td width="68"></td>
		<td width="145">密&nbsp;&nbsp;&nbsp;码：</td>
		<td width="226"><input name="ChannelPass" type="password" class="passw" value="" onchange="assertPW(this)"/></td>
  </tr></table>
  </div></td></tr>
  <tr>
	  <td colspan="6"><div id="divColor" style="display:none"><table cellpadding="0" cellspacing="0">
  <tr>
	  <td colspan="6" class="menu1" height="25">&nbsp;图像参数设置</td>
  </tr>
  <tr>
	<td width="23" height="20"></td>
	<td width="137">色&nbsp;&nbsp;&nbsp;度：</td>
	<td width="170"><input name="Color" type="text" class="halfInput" value="0" onchange="validateNum(this,0,255,'色度范围: ')"/>(0-255)</td>
	<td width="132"></td>
	<td width="144">饱和度：</td>
	<td width="233"><input name="Saturation" type="text" class="halfInput" value="0" onchange="validateNum(this,0,255,'饱和度范围: ')"/>(0-255)</td>
  </tr>
  <tr>
	<td width="23" height="20"></td>
	<td width="137">对比度：</td>
	<td width="170"><input name="Contrast" type="text" class="halfInput" value="0" onchange="validateNum(this,0,255,'对比度范围: ')"/>(0-255)</td>
	<td width="132"></td>
	<td width="144">亮&nbsp;&nbsp;&nbsp;度：</td>
	<td width="233"><input name="Brightness" type="text" class="halfInput" value="0" onchange="validateNum(this,0,255,'亮度范围： ')"/>(0-255)</td>
  </tr></table></div></td></tr>
  <tr>
	  <td colspan="6"><div id="divOSD" ><table cellpadding="0" cellspacing="0">
  
  
  <tr>
	  <td width="23" height="30"></td>
	  <td width="137">名称： </td>
	  <td width="170"><select name="OSD2_State" class="selectw">
        <option value="1">显示</option>
        <option value="0">隐藏</option>
      </select></td>
	  <td width="132"></td>
	  <td width="120">OSD X/Y： </td>
	  <td width="20">X:&nbsp;</td>
      <td width="236"><input name="OSD2_X" type="text" size="3" onchange="validateOsdXY('ChannelName',this,'x','通道名称OSD_X范围是：')"/>        &nbsp;&nbsp;Y:
  <input name="OSD2_Y" type="text" size="3" onchange="validateOsdXY('ChannelName',this,'y','通道名称OSD_Y范围是：')"/></td></tr>
  
  <tr>
	  <td width="23" height="30"></td>
	  <td width="137">时间：</td>
	  <td width="170">
			<select name="OSD1_State" class="selectw" onchange="selectTime()">
				<option value="1">显示</option>
				<option value="0">隐藏</option>
		</select>	  </td>
	  <td width="132"></td>
	  <td width="120">日期格式：</td>
	  <td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<!--<label name="DateFormat">YYYY-MM-DD</label>--></td>
      <td><select name="DateFormat" style="width:134px">
        <option value="0">YYYY-MM-DD</option>
        <option value="1">YYYY MM DD</option>
        <option value="2">YYYY/MM/DD</option>
        <option value="3">MM/DD/YYYY</option>
      </select></td>
  </tr>
  <tr>
	  <td width="23" height="30"></td>
	  <td width="137">星期：</td>
	  <td width="170"><select name="DisplayWeek" class="selectw">
				<option value="1">显示</option>
				<option value="0">隐藏</option>
		</select></td>
	  <td width="132"></td>
	  <td width="120">OSD X/Y：</td>
	  <td>X:&nbsp;</td>
      <td><input name="OSD1_X" type="text" size="3" onchange="validateOsdXY('week',this,'x','日期时间OSD_X范围是：')"/>	    
	    &nbsp;&nbsp;Y:
	    <input name="OSD1_Y" type="text" size="3" onchange="validateOsdXY('week',this,'y','日期时间OSD_Y范围是：')"/></td>
  </tr>
  
  <tr>
    <td height="25" colspan="7" class="menu1">&nbsp;字符叠加</td>
    </tr>
  <tr>
    <td height="30"></td>
    <td>显示状态</td>
    <td>叠加内容</td>
    <td></td>
    <td>显示位置</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
  </tr>
  <tr>
    <td height="30"></td>
    <td><input name="OSD3_State" type="checkbox" value="1" />
	  OSD1</td>
    <td><input type="text" name="OSD3_Title" maxlength="16" onchange="validateOsdXY('OSD3_Title',getElementById('OSD3_X'),'x','OSD1的OSD_X范围是：');validateOsdXY('OSD3_Title',getElementById('OSD3_Y'),'y','OSD1的OSD_Y范围是：')" /></td>
    <td></td>
    <td>OSD X/Y：</td>
    <td>X:&nbsp;</td>
    <td><input name="OSD3_X" type="text" size="3" onchange="validateOsdXY('OSD3_Title',this,'x','OSD1的OSD_X范围是：')"/>
      &nbsp;&nbsp;Y:
      <input name="OSD3_Y" type="text" size="3" onchange="validateOsdXY('OSD3_Title',this,'y','OSD1的OSD_Y范围是：')"/></td>
  </tr>
  <tr>
    <td height="30"></td>
    <td><input name="OSD4_State" type="checkbox" value="1" />
OSD2 </td>
    <td><input type="text" name="OSD4_Title" maxlength="16" onchange="validateOsdXY('OSD4_Title',getElementById('OSD4_X'),'x','OSD2的OSD_X范围是：');alidateOsdXY('OSD4_Title',getElementById('OSD4_Y'),'y','OSD2的OSD_Y范围是：')" /></td>
    <td></td>
    <td>OSD X/Y：</td>
    <td>X:&nbsp;</td>
    <td><input name="OSD4_X" type="text" size="3" onchange="validateOsdXY('OSD4_Title',this,'x','OSD2的OSD_X范围是：')"/>
      &nbsp;&nbsp;Y:
      <input name="OSD4_Y" type="text" size="3" onchange="validateOsdXY('OSD4_Title',this,'y','OSD2的OSD_Y范围是：')"/></td>
  </tr>
  
  </table>
	  </div></td></tr>
  <tr>
	  <td colspan="6"><div id="divPri"><table width="840" cellpadding="0" cellspacing="0">
  <tr>
	  <td colspan="6" class="menu1" height="25">&nbsp;区域设置</td>
  </tr>
   <tr>
	  <td width="23"></td><td colspan="5">
	  <iframe id="AreaFrame0" src="" style="display:none" frameborder="0" scrolling="no" width="690" height="310"></iframe>
	  </td>
  </tr>
</table></div></td></tr>
  <tr>
	  <td colspan="6" class="menu1" height="25">&nbsp;视频丢失报警 </td>
  </tr>
  <tr><td colspan="6"><div id="div2">
  <table cellpadding="0" cellspacing="0">
  <tr>
	  <td width="22" height="28"></td>
	  <td width="136"><input type="checkbox" name="SigEnable" value="1" onclick="onSigEnable()"/>启用</td>
	  <td width="169"><input type="button" class="btChan" name="SigDefend" value="布防" onclick="onSigDefend();" /></td>
	  <td width="131"><input type="button" class="btChan" name="SigMethod" value="输出" onclick="onSigMethod();" /></td>
	  <td width="131"></td>
	  <td width="249"></td>
  </tr></table>
  </div></td></tr>
  <tr>
	  <td width="22"><input type="hidden" name="isSigPlanChange" value="1"/></td>
	  <td colspan="5">
  	  	<div id="SigDefendTime" style="display:none">
			<br />
		<table cellpadding="0" cellspacing="0" border="0" class="tableborder">
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
		  <td height="25" align="center"><input name="all2" type="button" value="全选" onclick="selectDefendTime(1,'sig')" onmouseover="setFlag(0)" />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input name="no2" type="button" value="清除" onclick="selectDefendTime(0,'sig')" onmouseover="setFlag(0)" /></td>
			<td>&nbsp;</td>
		  </tr>
		<tr onmouseover="setFlag(0)">
			<td height="25" colspan="2">说明：若要取消选择，请按住Ctrl键再拖选。</td>
		  </tr>
		</table><br />    
		</div>  	  </td>
  </tr>
  <tr>
	  <td></td>
	  <td colspan="5">
  <div id="SigHandleMethod" style="display:none">
  <table cellpadding="0" cellspacing="0" class="subtable">
  <tr>
	  <td width="142">&nbsp;报警触发方式</td>
	  <td width="157"><input type="checkbox" name="SigTriggerVoice" value="1"/>
	  声音警告</td>
	  <td width="128"><input type="checkbox" name="SigTriggerCenter" value="1"/>
	  控制中心</td>
	  <td colspan="2"><input type="checkbox" name="SigTriggerMonitor" value="1"/>
	  报警预览</td>
  </tr>
  <tr>
	  <td width="142"></td>
	  <td colspan="4"><input type="checkbox" name="SigTriggerOutput" value="1" onclick="onTriggerOutput('Sig')"/>
	  触发报警输出</td>
  </tr>
  <tr>
	  <td width="142"></td>
	  <td>&nbsp;&nbsp;&nbsp;&nbsp;<input type="checkbox" name="SigTriggerOutput1" value="1" disabled/>
	    输出1</td>
	  <td><input type="checkbox" name="SigTriggerOutput2" value="1" disabled/>
	    输出2</td>
	  <td width="143"><input type="checkbox" name="SigTriggerOutput3" value="1" disabled/>
	    输出3</td>
	  <td width="208"><input type="checkbox" name="SigTriggerOutput4" value="1" disabled/>
	    输出4</td>
  </tr>
  </table>
  </div></td></tr>
  <tr>
	  <td colspan="6"><div id="divObs"><table cellpadding="0" cellspacing="0">
  <tr>
	  <td colspan="6" class="menu1" height="25">&nbsp;视频遮挡报警</td>
  </tr>
  <tr>
	  <td width="22" height="28"></td>
	  <td width="136"><input type="checkbox" name="ObsEnable" value="1" onclick="onObsEnable()"/>启用</td>
	  <td width="169">灵敏度：
	    <select name="ObsLevel">
        <option value="0">高</option>
        <option value="1">中</option>
        <option value="2">低</option>
      </select></td>
	  <td width="131"><input type="button" class="btChan" name="ObstructDefend" value="布防" onclick="onObstructDefend();" /></td>
	  <td width="249"><input type="button" class="btChan" name="ObstructMethod" value="输出" onclick="onObstructMethod();" /></td>
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
		  <td height="25" align="center"><input name="all2" type="button" value="全选" onclick="selectDefendTime(1,'obs')" onmouseover="setFlag(0)" />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input name="no2" type="button" value="清除" onclick="selectDefendTime(0,'obs')" onmouseover="setFlag(0)" /></td>
			<td>&nbsp;</td>
		  </tr>
		<tr onmouseover="setFlag(0)">
			<td height="25" colspan="2">说明：若要取消选择，请按住Ctrl键再拖选。</td>
		  </tr>
		</table>
		 <br />   
		</div>  	  
		</td>
  </tr>
  <tr>
	  <td></td>
	  <td colspan="5">
  <div id="ObsHandleMethod" style="display:none">
  <table cellpadding="0" cellspacing="0" class="subtable">
  <tr>
	  <td width="142">&nbsp;报警触发方式</td>
	  <td width="157"><input type="checkbox" name="ObsTriggerVoice" value="1"/>声音警告</td>
	  <td width="128"><input type="checkbox" name="ObsTriggerCenter" value="1"/>控制中心</td>
	  <td colspan="2"><input type="checkbox" name="ObsTriggerMonitor" value="1"/>报警预览</td>
  </tr>
  <tr>
	  <td width="142"></td>
	  <td colspan="4"><input type="checkbox" name="ObsTriggerOutput" value="1" onclick="onTriggerOutput('Obs')"/>触发报警输出</td>
  </tr>
  <tr>
	  <td width="142"></td>
	  <td>&nbsp;&nbsp;&nbsp;&nbsp;<input type="checkbox" name="ObsTriggerOutput1" value="1" disabled/>报警输出1</td>
	  <td><input type="checkbox" name="ObsTriggerOutput2" value="1" disabled/>报警输出2</td>
	  <td width="143"><input type="checkbox" name="ObsTriggerOutput3" value="1" disabled/>报警输出3</td>
	  <td width="208"><input type="checkbox" name="ObsTriggerOutput4" value="1" disabled/>报警输出4</td>
  </tr>
  </table>
  </div></td></tr>
  <tr>
	  <td colspan="6" class="menu1" height="25">&nbsp;视频移动侦测</td>
  </tr>
  <tr><td colspan="6"><div id="div3">
  <table cellpadding="0" cellspacing="0">
  <tr>
	  <td width="22" height="28"></td>
	  <td width="136"><input type="checkbox" name="MotionEnable" value="1" onclick="onMoEnable()"/>启用</td>
	  <td width="169">灵敏度：
	  <select name="MoLevel" disabled>
        <option value="0">高</option>
        <option value="1">中</option>
        <option value="2">低</option>
      </select></td>
	  <td width="131"><input type="button" class="btChan" name="ckMoSchedule" value="布防" onclick="onMotionDefend();" /></td>
	  <td width="249"><input type="button" class="btChan" name="MotionHandleContact" value="联动" onclick="onMotionContact();onSelectPTZCh();" /></td>
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
		  <td height="25" align="center"><input name="all2" type="button" value="全选" onclick="selectDefendTime(1,'motion')" onmouseover="setFlag(0)" />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input name="no2" type="button" value="清除" onclick="selectDefendTime(0,'motion')" onmouseover="setFlag(0)" /></td>
			<td>&nbsp;</td>
		  </tr>
		<tr onmouseover="setFlag(0)">
			<td height="25" colspan="2">说明：若要取消选择，请按住Ctrl键再拖选。</td>
		  </tr>
		</table>
		<br />   
		</div>	  </td>
  </tr>
  <tr>
	  <td width="22"></td>
	  <td colspan="5">
  <div id="MotionAlarmContact" style="display:none">
  <table cellpadding="0" cellspacing="0" class="subtable">
  <tr id="reRow1">
	  <td width="142">&nbsp;触发录像通道</td>
	  <td><input type="checkbox" name="MotionRecordChannel1" value="1"/>通道01</td>
	  <td><input type="checkbox" name="MotionRecordChannel2" value="1"/>通道02</td>
	  <td><input type="checkbox" name="MotionRecordChannel3" value="1"/>通道03</td>
	  <td><input type="checkbox" name="MotionRecordChannel4" value="1"/>通道04</td></tr>
  <tr id="reRow2">
	  <td width="142"></td>
	  <td><input type="checkbox" name="MotionRecordChannel5" value="1"/>通道05</td>
	  <td><input type="checkbox" name="MotionRecordChannel6" value="1"/>通道06</td>
	  <td><input type="checkbox" name="MotionRecordChannel7" value="1"/>通道07</td>
	  <td><input type="checkbox" name="MotionRecordChannel8" value="1"/>通道08</td></tr>
  <tr id="reRow3" style="display:none">
	  <td width="142"></td>
	  <td><input type="checkbox" name="MotionRecordChannel9" value="1"/>通道09</td>
	  <td><input type="checkbox" name="MotionRecordChannel10" value="1"/>通道10</td>
	  <td><input type="checkbox" name="MotionRecordChannel11" value="1"/>通道11</td>
	  <td><input type="checkbox" name="MotionRecordChannel12" value="1"/>通道12</td></tr>
  <tr id="reRow4" style="display:none">
	  <td width="142"></td>
	  <td><input type="checkbox" name="MotionRecordChannel13" value="1"/>通道13</td>
	  <td><input type="checkbox" name="MotionRecordChannel14" value="1"/>通道14</td>
	  <td><input type="checkbox" name="MotionRecordChannel15" value="1"/>通道15</td>
	  <td><input type="checkbox" name="MotionRecordChannel16" value="1"/>通道16</td></tr>
  <tr>
	  <td width="142">&nbsp;</td>
	  <td><input type="button" name="AllChannel" value="全选" class="myButton" onclick="onTriggerRecordChan('MotionRecordChannel',1);setObjectByName('isMotionPlanChange','1');"/></td>
	  <td colspan="3"><input type="button" name="NoneChannel" value="全不选" class="myButton" onclick="onTriggerRecordChan('MotionRecordChannel',0);setObjectByName('isMotionPlanChange','1');"/></td>  </tr>
  <tr class="sublist">
	  <td width="142" height="20">&nbsp;PTZ联动</td>
	  <td>通道号</td>
	  <td colspan="3"><select name="PTZChannel" class="selectw" onchange="SetbackMDPTZ();onSelectPTZCh();">
	  </select><input type="hidden" name="backPTZCh" value="0"/><input type="hidden" name="isPTZChChange" value="0"/></td>
  </tr>
  <tr><td width="142"></td>
  <td><input name="preset" type="checkbox" value="1" onclick="SetPreset();setObjectByName('isPTZChChange','1');"/>预置位</td><td colspan="3"><input type="text" name="PresetValue" disabled onchange="validateNum(this,1,255,'预置位范围: ');setObjectByName('isPTZChChange','1');" /></td>
  </tr>
  <tr><td width="142"></td>
  <td><input name="cruise" type="checkbox" value="1" onclick="SetCruise();setObjectByName('isPTZChChange','1');" />花&nbsp;&nbsp;&nbsp;样</td><td colspan="3"><input type="text" name="CruiseValue" disabled onchange="validateNum(this,1,4,'花样范围: ');setObjectByName('isPTZChChange','1');" /></td>
  </tr>
  <tr >
	  <td width="142">&nbsp;报警触发方式</td>
	  <td width="157"><input type="checkbox" name="MotionTriggerVoice" value="1"/>声音警告</td>
	  <td width="128"><input type="checkbox" name="MotionTriggerCenter" value="1"/>控制中心</td>
	  <td colspan="2"><input type="checkbox" name="MotionTriggerMonitor" value="1"/>报警预览</td>
  </tr>
  <tr>
	  <td width="142"></td>
	  <td colspan="4"><input type="checkbox" name="MotionTriggerOutput" value="1" onclick="onTriggerOutput('Motion')"/>触发报警输出</td>
  </tr>
  <tr>
	  <td width="142"></td>
	  <td>&nbsp;&nbsp;&nbsp;&nbsp;<input type="checkbox" name="MotionTriggerOutput1" value="1" disabled/>报警输出1</td>
	  <td><input type="checkbox" name="MotionTriggerOutput2" value="1" disabled/>报警输出2</td>
	  <td width="143"><input type="checkbox" name="MotionTriggerOutput3" value="1" disabled/>报警输出3</td>
	  <td width="208"><input type="checkbox" name="MotionTriggerOutput4" value="1" disabled/>报警输出4</td>
  </tr>
  </table>
  </div></td></tr>
  <tr>
	  <td colspan="6" class="menu1" height="26">&nbsp;复制 </td>
  </tr>
  <tr>
	  <td width="22" height="25"></td>
	  <td width="137">复制到</td>
	  <td width="168"><select name="CopyCh" class="selectw">
	  </select></td>
	  <td colspan="3"><input type="button" name="ChCopyBt" value="复&nbsp;&nbsp;制" class="myButton" onclick="OnChCopy();" />
	  (通道基本信息、OSD及区域不能被复制)</td>
  </tr>
  <tr>
	  <td colspan="2" class="menu1" height="25">&nbsp;保存设置</td>
	  <td colspan="4" class="menu1"><input name="button" type="button" class="myButton" value="应&nbsp;&nbsp;用" onclick="setChCfg()" /></td>
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
