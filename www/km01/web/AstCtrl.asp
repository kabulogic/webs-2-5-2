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
<input type="hidden" name="lang" value="en">
  <table cellpadding="0" cellspacing="0" class="bttable" width="840">
  <tr class="menu1">
	  <td colspan="4" height="25"><%astCtrlGet();%>
	  &nbsp;Net AUX. Settings</td>
  </tr>
  
  <tr><td colspan="4"><table width="100%" border="0" cellpadding="0" cellspacing="0">
		<tr>
		  <td height="10" colspan="3">		  </td>
		  </tr>
		<tr>
		  <td height="20" colspan="3">&nbsp;<input type="checkbox" id="bOn" name="bOn"  />
		  Enable Net AUX. </td>
		  </tr>
		<tr>
		  <td height="20" colspan="3">&nbsp;&nbsp;Alarm Out Settings</td>
		</tr>
		<tr  id="alarmout" style="display:">
		  <td width="10" height="25">&nbsp;</td>
		  <td width="828" height="25"><table width="93%" border="0" cellspacing="0" cellpadding="0" class="utable">
            <tr>
              <td width="18%">&nbsp;</td>
              <td width="16%">Alarm Out 1</td>
              <td width="15%">Alarm Out 2</td>
              <td width="16%">Alarm Out 3</td>
              <td width="35%">Alarm Out 4</td>
            </tr>
            <tr>
              <td>None</td>
              <td><input type="radio" id="radio" name="AORadio1" /></td>
              <td><input type="radio" id="radio2" name="AORadio2" /></td>
              <td><input type="radio" id="radio3" name="AORadio3" /></td>
              <td><input type="radio" id="radio4" name="AORadio4" /></td>
            </tr>
            <tr>
              <td>Brush</td>
              <td><input type="radio" id="AORadio1" name="AORadio1" /></td>
              <td><input type="radio" id="AORadio2" name="AORadio2" /></td>
              <td><input type="radio" id="AORadio3" name="AORadio3" /></td>
              <td><input type="radio" id="AORadio4" name="AORadio4" /></td>
            </tr>
            <tr>
              <td>Llighting</td>
              <td><input type="radio" id="AORadio1" name="AORadio1" /></td>
              <td><input type="radio" id="AORadio2" name="AORadio2" /></td>
              <td><input type="radio" id="AORadio3" name="AORadio3" /></td>
              <td><input type="radio" id="AORadio4" name="AORadio4" /></td>
            </tr>
            <tr>
              <td>Other</td>
              <td><input type="radio" id="AORadio1" name="AORadio1" /></td>
              <td><input type="radio" id="AORadio2" name="AORadio2" /></td>
              <td><input type="radio" id="AORadio3" name="AORadio3" /></td>
              <td><input type="radio" id="AORadio4" name="AORadio4" /></td>
            </tr>
          </table></td>
		</tr>
		<tr>
		  <td height="10" colspan="3">		  </td>
		  </tr>
		<tr>
		  <td colspan="3"></td>
		</tr>
		</table></td>
  <tr>
	  <td width="176" height="25" class="menu1">&nbsp;Save all the parameters: </td>
	  <td width="662" colspan="3" class="menu1"><input name="button" type="button" class="myButton" value="Set" onclick="setAstCtrl();" /></td>
  </tr>
  </table>
</form>
</div>
</body>
</html>
