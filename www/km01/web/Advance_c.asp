<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7">
<meta http-equiv="pragma"   content="no-cache" />   
<title>Advance</title>
<link href="css/layout.css" rel="stylesheet" type="text/css" />
<script language="javascript" src="js/control.js"></script>
<script language="javascript" src="js/cookie.js"></script>
<script language="javascript" src="js/common.js"></script>
<script language="JavaScript" type="text/JavaScript">
<!--
MM_reloadPage(true);

function getpara()
{
	hideTips();
	var error = hasError();
	switch(error)
	{
		case "0": 
			alert("升级成功，请关闭网页，待系统重启完毕再重新打开！");
			closewidow();
			break;
		case "1": 
			alert("升级失败！");
			//document.ftpForm.ftpSet.disabled = false;
			break;
		case "2": 
			//if(readcookie("FormatWorkDisk")) alert("请重启系统！");
			break;
		case "3": alert("格式化硬盘失败！");break;
		//case "4": alert("正在录像中,不能格式化该盘!");break;
		case "4":
			alert("配置文件不存在！");break;
		case "5":
			alert("出厂设置失败！");
			document.factoryform.setFac.disabled = false;
			break;
		case "6":
			alert("配置文件导入失败,文件内容错误！");
			break;
		default:break;
	}
}
function FormatDisk()
{
	var num = "";
	var str = "";
	for(i=0;i<8;i++)
	{
		if((document.getElementById("ck"+i).checked)&& (parseInt(document.getElementById("cap"+i).value))>0)
		{
			j=i+65;
			num+=String.fromCharCode(j);
			num+="/";
		}
	}
	if(num == "")
	{
		document.hardisk.DiskNo.value = 0;
		document.hardisk.method.value = document.getElementById("methodIndex").selectedIndex;
		document.hardisk.submit();
		return;
	}
	else
	{
		document.hardisk.DiskNo.value = 0;
		str = num.substring(0,num.length-1);
		document.hardisk.method.value = (document.getElementById("methodIndex").selectedIndex);
		document.hardisk.submit();
	}
	if(window.confirm("是否格式化硬盘 "+str+" ?"))
	{
		for(i=0;i<8;i++)
		{
			if((document.getElementById("ck"+i).checked)&& (parseInt(document.getElementById("cap"+i).value))>0)
			{
				if(document.getElementById("stat"+i).value == "1")
				{
					addcookie("FormatWorkDisk=1");
				}
				document.hardisk.DiskNo.value |= 1<<i;
			}
		}
		document.hardisk.submit();
		showTips("正在格式化");
	}
}

function rebooting()
{
	if((window.confirm("是否重启系统？")))
	{
		document.all.rebootTips1.style.display = "none";
		document.all.rebootTips2.style.display = "";
		if(readcookie("FormatWorkDisk")) delcookie("FormatWorkDisk=1");
		alert("系统即将重启,浏览器将自动关闭.");
		document.RebootForm.submit();
	    document.RebootForm.bootSet.disabled=true;
		setTimeout("closewidow()",10);
	}
}
function update()
{
	var ret = cpFileName("update");
	if(ret == 1)
	{
		alert("请选择升级文件！");
		return;
	}
	else if(ret == 2)
	{
		alert("升级文件路径不正确！");
		return;
	}
	else if(ret == 3)
	{
		alert("上传升级文件错误！ 请选择扩展名为.ifu的升级文件。");
		return;
	}
	else if(ret == 4)
	{
		alert("升级包中包含'(),?{}'等特殊字符！");
		return;
	}
	if((window.confirm("是否进行升级操作？\n升级后系统将自动重启。")))
	{
		//document.ftpForm.ftpSet.disabled = true;
		document.ftpForm.submit();
		showTips("正在升级");
	}
}

function configIn()
{
	var ret = cpFileName("dvr-nvr.cfg");
	if(ret == 1)
	{
		alert("请选择配置文件！");
		return;
	}
	else if(ret == 2)
	{
		alert("配置文件路径不正确！");
		return;
	}
	else if(ret == 3)
	{
		alert("导入配置文件错误！ 请选择扩展名为.cfg的文件。");
		return;
	}
	if((window.confirm("是否导入配置文件操作？\n导入后将自动重启。")))
	{
		//document.ftpForm.ftpSet.disabled = true;
		document.configInForm.submit();
		showTips("正在导入配置文件");
	}
}

function Click()
{
window.event.returnValue=false;
}
document.oncontextmenu=Click;
function factoryset()
{
	if((window.confirm("是否要执行恢复出厂设置？")))
	{
		document.factoryform.setFac.disabled=true;
		alert("即将执行出厂设置，浏览器将自动关闭。");
		window.document.factoryform.submit();
		setTimeout("closewidow()",10); 
	}
}
//-->
</script>
<style type="text/css">
body,td,th {
	font-family: Verdana, Arial, Helvetica, sans-serif;
	font-size: 12px;
}
</style>
</head>

<body onLoad="setOperator();getDiskInfo('cn');getpara();InitAdvanceSet()">
<iframe id="hideframe" name="hideframe" style="display:none ;"></iframe>
<div id="mainconfig">
  <table cellpadding="0" cellspacing="0" class="bttable" width="840">
  <tr class="menu1">
	  <td colspan="2" height="25">&nbsp;远程升级</td>
  </tr>
  <tr>
	  <td colspan="2" height="50">
	  <form name="ftpForm" method="post" action="/infinova/update" enctype="multipart/form-data">
	  <table width="700" cellpadding="0" cellspacing="0">
  	  <tr><td width="21"></td>
	  <td width="77"><input type="hidden" name="lang" value="cn">
	  文件升级：</td>
	  <td width="239"><input name="file" type="file" value=""></td>
	  <td width="243">(选择本地要升级的文件)</td>
	  <td width="118" align="right"><input type="hidden" name="path" /><input type="hidden" name="operator" value="" /><input name="ftpSet" type="button" class="myButton" value="升&nbsp;&nbsp;级" onClick="update()" /></td>
  	  </tr></table></form>
	  </td>
  </tr>
  <tr class="menu1">
	  <td colspan="2" height="25">&nbsp;硬盘管理 </td>
  </tr>
  <tr>
	  <td colspan="2" valign="top" align="center">
	  <form name="hardisk" action="/infinova/diskFormatCfg" method="post">
	  <%diskStatGet();%><input type="hidden" name="operator" value="" /><input type="hidden" name="DiskNo" value="" />
	  <input type="hidden" name="method" value="" /><input type="hidden" name="lang" value="cn">
	  <table width="798" cellpadding="0" cellspacing="0" class="subtable">
	  <tr align="center">
	    <th height="25" align="left">使用策略</th>
	    <th align="left"><select name="methodIndex" id="methodIndex"= style="width:120px">
          <option value="0">覆盖</option>
          <option value="1">不覆盖</option>
        </select></th>
	    <th align="center">&nbsp;</th>
	    <th align="center">&nbsp;</th>
	    <th align="center">&nbsp;</th>
	    </tr>
	  <tr class="sublist" align="left"><th width="74" height="25">&nbsp;</th>
	  <th width="151">容量(GB)</th>
	  <th width="151">剩余(GB)</th>
	  <th width="151">状态</th>
	  <th width="118">格式化</th>
	  </tr>
	  <tr align="left" id="hdformat0">
	    <td>A</td>
	    <td><label id="c1"></label></td><td><label id="f1"></label></td><td><label id="s1"></label></td>
	    <td><input type="checkbox" name="ck0" /></td></tr>
	  <tr class="sublist" align="left" id="hdformat1">
	    <td>B</td>
	    <td><label id="c2"></label></td><td><label id="f2"></label></td><td><label id="s2"></label></td>
	    <td><input type="checkbox" name="ck1" /></td></tr>
	  <tr align="left" id="hdformat2">
	    <td>C</td>
	    <td><label id="c3"></label></td><td><label id="f3"></label></td><td><label id="s3"></label></td>
	    <td><input type="checkbox" name="ck2" /></td></tr>
	  <tr class="sublist" align="left" id="hdformat3">
	    <td>D</td>
	    <td><label id="c4"></label></td><td><label id="f4"></label></td><td><label id="s4"></label></td>
	    <td><input type="checkbox" name="ck3" /></td></tr>
	  <tr align="left" id="hdformat4">
	    <td>E</td>
	    <td><label id="c5"></label></td><td><label id="f5"></label></td><td><label id="s5"></label></td>
	    <td><input type="checkbox" name="ck4" /></td></tr>
	  <tr class="sublist" align="left" id="hdformat5">
	    <td>F</td>
	    <td><label id="c6"></label></td><td><label id="f6"></label></td><td><label id="s6"></label></td>
	    <td><input type="checkbox" name="ck5" /></td></tr>
	  <tr align="left" id="hdformat6">
	    <td>G</td>
	    <td><label id="c7"></label></td><td><label id="f7"></label></td><td><label id="s7"></label></td>
	    <td><input type="checkbox" name="ck6" /></td></tr>
	  <tr class="sublist" align="left" id="hdformat7">
	    <td>H</td>
	    <td><label id="c8"></label></td><td><label id="f8"></label></td><td><label id="s8"></label></td>
	    <td><input type="checkbox" name="ck7" /></td></tr>
		<tr align="left"><td></td><td><input type="button" onClick="FormatAll()" value="全选" class="myButton" /></td><td><input type="button" onClick="FormatNone()" value="全不选" class="myButton" /></td><td><input type="button" name="btformat" onClick="FormatDisk()" value="应用" class="myButton" /></td><td>&nbsp;</td>
		</tr>
	  </table>
	  </form>
	  </td>
  </tr>
  <tr class="menu1">
	  <td colspan="2" height="25">&nbsp;重启系统 </td>
  </tr>
  <tr>
	  <td colspan="2" height="50">
	  <form name="RebootForm" action="/infinova/reboot" method="post" target="hideframe">
	  <table width="700" cellpadding="0" cellspacing="0">
  	  <tr><td width="26"></td>
	  <td width="554"><div id="rebootTips1">按下右边的按钮，系统将重启。</div>
	  <div id="rebootTips2" style="display:none">系统正在重启，请稍候……&nbsp;<!--（<label id="ttt" class="timecolor">30</label>&nbsp;秒）--></div></td>
	  <td width="118" align="right">
	  <input type="hidden" name="operator" value="" /><input name="bootSet" type="button" class="myButton" value="重&nbsp;&nbsp;启" onClick="rebooting()" /></td>
  	  </tr></table></form></td>
  </tr>
  <tr class="menu1">
	  <td width="93" height="25">&nbsp;恢复出厂设置</td>
	  <td width="745"><img src="images/warning.gif" alt="谨慎操作" /></td>
  </tr>
  <tr>
	  <td colspan="2" height="50">
	  <form name="factoryform" action="/infinova/FatorySet" method="post" target="hideframe">
	  <table width="700" cellpadding="0" cellspacing="0">
  		<tr><td width="26"></td>
	    <td width="554">按下右边的按钮，将所有的参数恢复为出厂设置的缺省值。</td>
      <td width="118" align="right"><input type="hidden" name="lang" value="cn"><input type="hidden" name="operator" value="" /><input name="setFac" type="button" class="myButton" onClick="factoryset();" value="应&nbsp;&nbsp;用" /></td>
</tr></table></form></td>
  </tr>
  <tr class="menu1" style="display:">
	  <td colspan="2" height="25">&nbsp;配置文件管理</td>
  </tr>
  <tr style="display:">
	  <td colspan="2" height="50">
	  <table width="840" cellpadding="0" cellspacing="0">
  	  <tr><td width="21"></td>
	  <form name="configInForm" method="post" action="/infinova/configfileIn" enctype="multipart/form-data">
	  <td width="77"><input type="hidden" name="lang" value="cn">文件上传：</td>
	  <td width="239"><input name="file" type="file" value="" >
	    </td>
	  <td width="161">(选择本地要上传的配置文件)<!--<iframe id="fileNameFrame" src="GetFileName.asp" style="display:none"></iframe>--></td>
	  <td width="120"><input type="hidden" name="path" /><input type="hidden" name="operator" value="" /><input name="configInButton" type="button" class="myButton" value="导&nbsp;&nbsp;入" onClick="configIn()" /></td></form>
	  <form name="configOutForm" method="post" action="/infinova/configfileOut" enctype="multipart/form-data">
	    <td width="80" align="right"><input type="hidden" name="lang" value="cn">
	      <input name="configOutButton" type="button" class="myButton" value="导&nbsp;&nbsp;出" onClick="configOut()" /></td>
	  </form>
	  <td width="140"><a href="help/help_c.htm" target="_blank" class="txt" style="color:#000000"><img src="images/hint.gif" alt="帮助文档" width="25" height="25"></a>&nbsp;</td>
  	  </tr>
	  </table>
	  </td>
  </tr>
  </table>
</div>
<div id="light" class="white_content">
<table width="100%" height="100%">
<tr><td width="30%" align="center"><img src="images/tips.gif" width="32" height="32" /></td><td width="70%"><label id="ctrTip" class="mybold"></label><img src="images/dh.gif" width="30" height="15"></td></tr>
</table>
</div> 
<iframe id="forShowTip" frameborder="0" class="myIFrame"></iframe>
<div id="fade" class="black_overlay"></div> 
</body>
</html>
