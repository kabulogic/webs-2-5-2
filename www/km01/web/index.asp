<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7">
<link href="css/layout.css" rel="stylesheet" type="text/css" />
<title>Infinova DVR</title>
<script language="javascript" src="js/cookie.js"></script>
<script language="javascript" src="js/common.js"></script>
<script language="javascript" src="js/validate.js"></script>
<script language="JavaScript" type="text/JavaScript">
<!--
MM_reloadPage(true);

function ok()
{
	if(document.form1.name.value==""){
			alert("Username can't be null!");
			document.form1.name.focus();
			event.returnValue= false;
			return;
	}
	if(document.form1.password.value==""){
			alert("Password can't be null!");
			document.form1.password.value="";
			document.form1.password.focus();
			event.returnValue= false;
			return;
	}
	if(document.form1.port.value==""){
			alert("Port can not be null!");
			document.form1.port.focus();
			event.returnValue= false;
			return;
	}
	if(!checkPort(document.form1.port))
	{
		return;
	}
	addcookie("loginname="+document.form1.name.value);
	addcookie("loginpass="+document.form1.password.value);
	addcookie("port="+document.form1.port.value);
}
function checkPort(obj)
{
	if( (!isPort(obj)) || (obj.value < 1) || (obj.value > 65536))
	{
		var hint = "Input error!The range of port:1~65536.";
		alert(hint);
		obj.value = "";
		return false;
	}
	return true;
}
function Response()
{
	var hrefstr,pos,strtemp;	
	hrefstr = window.location.href;
	pos = hrefstr.indexOf("=");	
	strtemp=(hrefstr.substring(pos+1,pos+2));
	if(strtemp=="1")
	{
		alert("Wrong user name or password.");
		/*if(validate())
			alert("Wrong user name or password.");
		else{
			alert("Your client doesnot have permission.");
			document.form1.login.disabled=true;
		}*/
	}
}
//-->
</script>
</head>

<body onLoad="Init();Response();" bgcolor="#ffffff">
<table width="100%" height="100%" border="0" cellpadding="0" cellspacing="0">
<tr><td height="59">
  <table width="100%" border="0" cellpadding="0" cellspacing="0">
  <tr>
    <td height="40" align="center" class="topbk"><img src="images/top.jpg" width="466" height="40" border="0"></td>
  </tr>
  <tr>
    <td height="19" align="center" valign="bottom" bgcolor="#800000"><span class="wxHint">Note: For initial visit with network not connected, <a href="NoCrl.reg">click here</a> to run the file to log on the webpage. Otherwise, the ActiveX Control loading will be very slow.</span></td>
  </tr>
</table></td></tr>
<tr><td height="89%">
<table width="100%" border="0" cellpadding="0" cellspacing="0">
  <tr>
    <td align="center"><form  name="form1" action="/infinova/UserLogin" method="post">
      <table width="368" height="245" cellspacing="0" border="0" background="images/loginbg.gif">
        <tr><td colspan="5" height="42"></td>
        </tr>
        <tr><td width="69" height="30"></td>
			<td width="91"><span class="txt">User&nbsp;:</span></td>
			<td colspan="2"><input type="text" name="name" size=20 tabindex="1" class="inputw"></td>
			<td width="78"></td>
        </tr>
        <tr><td height="30"></td>
			<td><span class="txt">Password&nbsp;:</span></td>
			<td colspan="2"><input type="password" name="password" size=20 tabindex="2" class="inputw"></td>
			<td></td></tr>
		<tr>
          <td height="30"></td>
          <td><span class="txt">Port :</span></td>
          <td colspan="2"><input type="text" name="port" size=20 tabindex="2" class="inputw" value="5000"></td>
          <td></td>
        </tr>
        <tr><td height="30"><input type="hidden" name="lang" value="en"></td><td></td>
			<td width="60" align="left"><input type="submit" class="txt" value="Login" name="login" onClick="ok()"></td>
			<td width="60" align="right"><input type="reset" class="txt" value="Reset" name="reset" onClick="cancel()"></td><td></td></tr>
        <tr><td colspan="5" height="62"></td>
	  </table></form></td></tr></table>
</td></tr>
<tr><td height="54">
<table width="100%" border="0" cellpadding="0" cellspacing="0">
<tr>
  <td class="btbk" align="center" height="54">
Copyright&copy;1993-2011 Infinova. All Rights Reserved.<br>
<!--Version: Network DVR <%versionGet();%>--></td>
</tr></table>
</td></tr></table>
</body>
</html>
