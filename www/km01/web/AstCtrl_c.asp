<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7">
<title>Assistant Ctrl Settings</title>
<link href="css/layout.css" rel="stylesheet" type="text/css" />
<script language="javascript" src="js/cookie.js"></script>
<script language="javascript" src="js/common.js"></script>
<script language="javascript" src="js/function.js"></script>
<script language="javascript" src="js/astCtrl.js"></script>
</head>

<body onload="initAstCtrl()">
<div id="mainconfig">
<iframe id="hideframe" name="hideframe" style="display:none ;"></iframe>
<form name="AstCtrlForm" action="/infinova/astCtrlCfg" method="post" target="hideframe">
<input type="hidden" name="lang" value="cn">
  <table cellpadding="0" cellspacing="0" class="bttable" width="840">
  <tr class="menu1">
	  <td colspan="4" height="25"><%astCtrlGet();%>
	  &nbsp;网络辅助开关设置</td>
  </tr>
  
  <tr><td colspan="4"><table width="100%" border="0" cellpadding="0" cellspacing="0">
		<tr>
		  <td height="10" colspan="3">		  </td>
		  </tr>
		<tr>
		  <td height="20" colspan="3">&nbsp;<input type="checkbox" id="bOn" name="bOn"  />
		  开启网络辅助开关</td>
		  </tr>
		<tr>
		  <td height="20" colspan="3">&nbsp;&nbsp;报警输出控制</td>
		</tr>
		<tr  id="alarmout" style="display:">
		  <td width="1%" height="25">&nbsp;</td>
		  <td width="99%" height="25"><table width="78%" border="0" cellspacing="0" cellpadding="0" class="utable">
            <tr>
              <td width="12%">&nbsp;</td>
              <td width="18%">报警输出1</td>
              <td width="19%">报警输出2</td>
              <td width="16%">报警输出3</td>
              <td width="35%">报警输出4</td>
            </tr>
            <tr>
              <td>无</td>
              <td><input type="radio" id="radio" name="AORadio1" /></td>
              <td><input type="radio" id="radio2" name="AORadio2" /></td>
              <td><input type="radio" id="radio3" name="AORadio3" /></td>
              <td><input type="radio" id="radio4" name="AORadio4" /></td>
            </tr>
            <tr>
              <td>雨刷</td>
              <td><input type="radio" id="AORadio1" name="AORadio1" /></td>
              <td><input type="radio" id="AORadio2" name="AORadio2" /></td>
              <td><input type="radio" id="AORadio3" name="AORadio3"></td>
              <td><input type="radio" id="AORadio4" name="AORadio4"></td>
            </tr>
            <tr>
              <td>灯光</td>
              <td><input type="radio" id="AORadio1" name="AORadio1" /></td>
              <td><input type="radio" id="AORadio2" name="AORadio2" /></td>
              <td><input type="radio" id="AORadio3" name="AORadio3" /></td>
              <td><input type="radio" id="AORadio4" name="AORadio4" /></td>
            </tr>
            <tr>
              <td>自定义</td>
              <td><input type="radio" id="AORadio1" name="AORadio1" /></td>
              <td><input type="radio" id="AORadio2" name="AORadio2" /></td>
              <td><input type="radio" id="AORadio3" name="AORadio3" /></td>
              <td><input type="radio" id="AORadio4" name="AORadio4" /></td>
            </tr>
          </table></td>
		</tr>
		<tr>
		  <td colspan="3"></td>
		</tr>
		</table></td>
  <tr>
	  <td width="111" height="25" class="menu1">&nbsp;保存设置 </td>
	  <td width="727" colspan="3" class="menu1"><input name="button" type="button" class="myButton" value="应&nbsp;&nbsp;用" onclick="setAstCtrl();" /></td>
  </tr>
  </table>
</form>
</div>
</body>
</html>
