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
	switch(error){
		case "0": 
			alert("Upload successfully!\nThe browser will be closed.");
			closewidow(); 
			break;
		case "1": 
			alert("Upload failed!");
			//document.ftpForm.ftpSet.disabled = false;
			break;
		case "2": 
			//if(readcookie("FormatWorkDisk")) alert("Reboot the system please.");
			break;
		case "3": alert("Format harddisk failed!");break;
		//case "4": alert("Recording,you can't format it!");break;
		case "4":
			alert("config file is inexistence!");break;
		case "5":
			alert("Factory settings is failed!");
			document.factoryform.setFac.disabled = false;
			break;
		case "6":
			alert("Config in file failed, file error!");
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
	if(window.confirm("Are you sure to format the harddisk "+str+" ?"))
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
		showTips("Wait for formatting");
	}
}

function rebooting()
{
	if((window.confirm("Are you sure to reboot the system?")))
	{
		document.all.rebootTips1.style.display = "none";
		document.all.rebootTips2.style.display = "";
		if(readcookie("FormatWorkDisk")) delcookie("FormatWorkDisk=1");
		alert("System will be rebooted.\nThe browser will be closed.");
		document.RebootForm.submit();
	    document.RebootForm.bootSet.disabled=true;
		setTimeout("closewidow()",10);
	}
}
function update()
{
	var ret = cpFileName("update");
	if(ret == 1){
		alert("No file!");
		return;
	}
	else if(ret == 2)
	{
		alert("File path error!");
		return;
	}
	else if(ret == 3){
		alert("File error! Please select the file ending with '.ifu'.");
		return;
	}
	else if(ret == 4)
	{
		alert("File Name include invalid characters!");
		return;
	}
	if((window.confirm("Are you sure to update?\nThe system will reboot after updating.")))
	{
		//document.ftpForm.ftpSet.disabled = true;
		document.ftpForm.submit();
		showTips("Wait for updating");
	}
}

function configIn()
{
	var ret = cpFileName("dvr-nvr.cfg");
	if(ret == 1)
	{
		alert("No file!");
		return;
	}
	else if(ret == 2)
	{
		alert("File path error!");
		return;
	}
	else if(ret == 3)
	{
		alert("File error! Please select the file ending with '.cfg'.");
		return;
	}
	if((window.confirm("Are you sure to load config file?\nThe system will reboot after loading.")))
	{
		//document.ftpForm.ftpSet.disabled = true;
		document.configInForm.submit();
		showTips("Wait for loading config file");
	}
}

function Click(){
window.event.returnValue=false;
}
document.oncontextmenu=Click;
function factoryset()
{
	if((window.confirm("Are you sure to reset all the parameters \n to the factory default settings?")))
	{
		document.factoryform.setFac.disabled=true;
		alert("Factory settings will be executed.\nThe browser will be closed.");
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

<body onLoad="setOperator();getDiskInfo('en');getpara();InitAdvanceSet()">
<iframe id="hideframe" name="hideframe" style="display:none ;"></iframe>
<div id="mainconfig">
  <table cellpadding="0" cellspacing="0" class="bttable" width="840">
  <tr class="menu1">
	  <td colspan="2" height="25">&nbsp;Upgrade</td>
  </tr>
  <tr>
	  <td colspan="2" height="50">
	  <form name="ftpForm" method="post" action="/infinova/update" enctype="multipart/form-data">
	  <table width="700" cellpadding="0" cellspacing="0">
  	  <tr><td width="19"></td>
	  <td width="561">
		<input type="hidden" name="lang" value="en">Software Upload:&nbsp;<input name="file" type="file" value="">(Select A Local File) </td><td width="118" align="right"><input type="hidden" name="path" /><input type="hidden" name="operator" value="" /><input name="ftpSet" type="button" class="myButton" value="Upgrade" onClick="update()" /></td>
  	  </tr></table></form>
	  </td>
  </tr>
  <tr class="menu1">
	  <td colspan="2" height="25">&nbsp;HD Management </td>
  </tr>
  <tr>
	  <td colspan="2" valign="top" align="center"><br/>
	  <form name="hardisk" action="/infinova/diskFormatCfg" method="post">
	  <%diskStatGet();%><input type="hidden" name="operator" value="" /><input type="hidden" name="DiskNo" value="" />
	  <input type="hidden" name="method" value="" /><input type="hidden" name="lang" value="en">
	  <table width="798" height="100" cellpadding="0" cellspacing="0" class="subtable">
	  <tr align="center">
	    <th height="25" align="left">Method</th>
	    <th align="left"><select name="methodIndex" id="methodIndex"= style="width:120px">
          <option value="0">Overwrite</option>
          <option value="1">Unoverwrite</option>
        </select></th>
	    <th align="center">&nbsp;</th>
	    <th align="center">&nbsp;</th>
	    </tr>
	  <tr class="sublist" align="left"><th width="91" height="25">&nbsp;</th>
	  <th width="170">Capacity(GB)</th>
	  <th width="170">Free(GB)</th>
	  <th width="170">Status</th>
	  <th width="195">Formating</th>
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
		<tr align="left"><td></td><td><input type="button" onClick="FormatAll()" value="Select All" class="myButton" /></td><td><input type="button" onClick="FormatNone()" value="Clear All" class="myButton" /></td><td><input type="button" name="btformat" onClick="FormatDisk()" value="Set" class="myButton" /></td>
		  <td></td></tr>
	  </table>
	  </form>
	  </td>
  </tr>
  <tr class="menu1">
	  <td colspan="2" height="25">&nbsp;Reboot </td>
  </tr>
  <tr>
	  <td colspan="2" height="50">
	  <form name="RebootForm" action="/infinova/reboot" method="post" target="hideframe">
	  <table width="700" cellpadding="0" cellspacing="0">
  	  <tr><td width="19"></td>
	  <td width="561"><div id="rebootTips1">Press the button to reboot the system.</div>
	    <div id="rebootTips2" style="display:none">System rebooting...&nbsp;&nbsp;<!--(<label id="ttt" class="timecolor">30</label>
	  &nbsp;s)--></div></td><td width="118" align="right"><input type="hidden" name="operator" value="" /><input name="bootSet" type="button" class="myButton" value="Reboot" onClick="rebooting()" /></td>
  	  </tr></table></form></td>
  </tr>
  <tr class="menu1">
	  <td width="119" height="25">&nbsp;Default Settings</td>
	  <td width="719"><img src="images/warning.gif" width="16" height="18" alt="Take care" /></td>
  </tr>
  <tr>
	  <td colspan="2" height="80">
	  <form name="factoryform" action="/infinova/FatorySet" method="post" target="hideframe">
	  <table width="700" cellpadding="0" cellspacing="0">
  		<tr><td width="19"></td>
	    <td width="561">
        Press the button to reset all the parameters to the factory default settings.</td>
      <td width="118" align="right"><input type="hidden" name="operator" value="" /><input type="hidden" name="lang" value="en"><input name="setFac" type="button" class="myButton" onClick="factoryset();" value=" Set " /></td>
</tr></table></form></td>
  </tr>
  <tr class="menu1" style="display:">
	  <td colspan="2" height="25">&nbsp;config file management </td>
  </tr>
  <tr style="display:">
	  <td colspan="2" height="50">
	  <table width="840" cellpadding="0" cellspacing="0">
  	  <tr><td width="21"></td>
	  <form name="configInForm" method="post" action="/infinova/configfileIn" enctype="multipart/form-data">
	  <td width="77"><input type="hidden" name="lang" value="en">
	  Upload:</td>
	  <td width="239"><input name="file" type="file" value=""></td>
	  <td width="161">(Select A Local File)</td>
	  <td width="120"><input type="hidden" name="path" /><input type="hidden" name="operator" value="" /><input name="configInButton" type="button" class="myButton" value="Upload" onClick="configIn()" /></td></form>
	  <form name="configOutForm" method="post" action="/infinova/configfileOut" enctype="multipart/form-data">
	    <td width="80" align="right"><input type="hidden" name="lang" value="en">
	      <input name="configOutButton" type="button" class="myButton" value="Download" onClick="configOut()" /></td>
	  </form>
	  <td width="140"><a href="help/help.htm" target="_blank" class="txt" style="color:#000000"><img src="images/hint.gif" alt="help document" width="25" height="25"></a></td>
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
