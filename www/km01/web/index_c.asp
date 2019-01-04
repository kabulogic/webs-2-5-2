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
	if(document.form1.name.value=="" ){
			alert("用户名不能为空！");
			document.form1.name.focus();
			event.returnValue= false;
			return;
	}
	if(document.form1.password.value==""){
			alert("密码不能为空！");
			document.form1.password.value="";
			document.form1.password.focus();
			event.returnValue= false;
			return;
	}
	if(document.form1.port.value==""){
			alert("端口不能为空！");
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
		var hint = "输入错误，端口号范围:1~65536.";
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
		alert("用户名与密码不匹配");
		/*if(validate())
			alert("用户名与密码不匹配");
		else{
			alert("非法用户");
			document.form1.login.disabled=true;
		}*/
	}
}

//-->
</script>
<style type="text/css">
<!--
.STYLE3 {
	font-size: 12px;
	color: #FFFFFF;
}
-->
</style>
</head>

<body onLoad="Init();Response();" bgcolor="#ffffff">
<table width="100%" height="100%" border="0" cellpadding="0" cellspacing="0">
<tr><td height="59">
  <table width="100%" border="0" cellpadding="0" cellspacing="0">
  <tr>
    <td height="40" align="center" class="topbk"><img src="images/top.jpg" width="466" height="40" border="0"></td>
  </tr>
  <tr>
    <td height="19" align="center" valign="bottom" bgcolor="#800000" class="wxHint" >温馨提示：未连接互联网的客户端首次登录访问网页时，请<a href="NoCrl.reg">点击此处</a>并运行文件，否则加载控件会比较慢。</td>
  </tr>
</table></td></tr>
<tr><td height="89%">
<table width="100%" border="0" cellpadding="0" cellspacing="0">
  <tr>
    <td align="center"><form  name="form1" action="/infinova/UserLogin" method="post">
      <table width="368" height="245" cellspacing="0" border="0" background="images/loginbg.gif">
        <tr><td height="42"></td>
          <td height="42" colspan="3" class="txt">&nbsp;</td>
          <td height="42"></td>
        </tr>
        <tr><td width="78" height="30"></td>
			<td width="77"><span class="txt">用户名：</span></td>
			<td colspan="2"><input type="text" name="name" size=20 tabindex="1" class="inputw"></td>
			<td width="84"></td>
        </tr>
        <tr><td height="30"></td>
			<td><span class="txt">密&nbsp;&nbsp;&nbsp;码：</span></td>
			<td colspan="2"><input type="password" name="password" size=20 tabindex="2" class="inputw"></td>
			<td></td></tr>
        <tr>
          <td height="30"></td>
          <td><span class="txt">端口号：</span></td>
          <td colspan="2"><input type="text" name="port" size=20 tabindex="2" class="inputw" value="5000"></td>
          <td></td>
        </tr>
        <tr><td height="30"><input type="hidden" name="lang" value="cn"></td><td align="right"></td>
			<td width="62" align="left"><input type="submit" class="txt" value="登&nbsp;&nbsp;录" name="login" onClick="ok()"></td>
			<td width="57" align="right"><input type="reset" class="txt" value="取&nbsp;&nbsp;消" name="reset" onClick="cancel()"></td><td></td></tr>
        <tr>
          <td height="62" colspan="5"><span class="wxhint">&nbsp;&nbsp;</span></td>
	  </table>
    </form></td></tr></table>
</td></tr>
<tr><td height="54">
<table width="100%" border="0" cellpadding="0" cellspacing="0">
<tr>
  <td class="btbk" align="center" height="54">版权所有 Infinova<br>
  <br>
<!--Version: Network DVR <%versionGet();%>--></td>
</tr></table>
</td></tr></table>
</body>
</html>
