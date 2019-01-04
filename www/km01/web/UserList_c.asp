<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7">
<title>用户管理</title>
<link href="css/layout.css" rel="stylesheet" type="text/css" />
<script language="javascript" src="js/cookie.js"></script>
<script language="javascript" src="js/common.js"></script>
<script language="javascript" src="js/get_user.js"></script>
<script language="javascript" src="js/set_user.js"></script>
<script language="javascript" src="js/validate.js"></script>
<script language="javascript" src="js/function.js"></script>
<script language="JavaScript" type="text/JavaScript">
<!--
MM_reloadPage(true);
function checkInfo()
{
	if(document.UserListForm.radiobutton[1].checked){//add user
		if(parseInt(document.getUser.document.getElementById("UserNum").value)>=16){
			alert("用户总数不能超过16！");
			window.event.returnValue=false;
			return false;
		}
		if(document.UserListForm.NewUserName.value == ""){
			alert("添加用户：用户名不能为空！");
			window.event.returnValue=false;
			return false;
		}
		if(!assertName(document.UserListForm.NewUserName)){
			window.event.returnValue=false;
			return false;
		}
		if(document.UserListForm.NewUserPswd.value == ""){
			alert("添加用户：密码不能为空！");
			window.event.returnValue=false;
			return false;
		}
		if(!assertPW(document.UserListForm.NewUserPswd)){
			window.event.returnValue=false;
			return false;
		}
		if(!isStr(document.UserListForm.NewUserName,15) || !isStr(document.UserListForm.NewUserPswd,15) || !isStr(document.UserListForm.NewConfPswd,15)){
			return false;
		}
		if(!checkPass(document.UserListForm.NewUserPswd,document.UserListForm.NewConfPswd)){
			alert("添加用户：两次密码输入不一致！");
			window.event.returnValue=false;
			return false;
		}
	}
	if(document.UserListForm.radiobutton[0].checked)
	{//edit user
		if(!((document.UserListForm.userinfo14.value=="") && (document.UserListForm.userinfo15.value=="")))
		{
			if(!isPasswd(document.UserListForm.userinfo14) || !assertPW(document.UserListForm.userinfo14))
			{
				return false;
			}
		}
		var userNo = document.getElementById("UserNameList").selectedIndex;
		var oldpass = getCookie("loginpass=");
		//var oldpass = getCookie("UseroldPass"+userNo+"=");
		var userOn = getCookie("loginname=");
		if((document.getElementById("UserNameList").value == "admin") || (userOn != "admin"))
		{
			if(document.getElementById("userinfo16").value != oldpass)
			{
				alert("编辑用户：原密码输入错误！");
				window.event.returnValue=false;
				return false;
			}
		}
		if(document.UserListForm.userinfo14.value=="")
		{
			alert("编辑用户：密码不能为空！");
			window.event.returnValue=false;
			return false;
		}
		if(!checkPass(document.UserListForm.userinfo14,document.UserListForm.userinfo15))
		{
			alert("编辑用户：两次密码输入不一致！");
			window.event.returnValue=false;
			return false;
		}
	}
	
	if(document.UserListForm.radiobutton[2].checked){//delete user
		if((document.getElementById("UserNameList").value == "admin"))
		{
			alert("不能删除该用户！");
			return false;
		}
		if(window.confirm("是否删除此用户？"))
		{
			return true;
		}
		else return false;
	}
	return true;
}

function assertName(obj)
{
	if(obj.value.length>15){
		alert("用户名长度：1~15！");
		window.event.returnValue=false;
		return false;
	}
	if(!isTrueName(obj)){
		alert("用户名仅支持数字和字母！");
		window.event.returnValue=false;
		return false;
	}
    window.event.returnValue = true;
	return true;
}

function assertPW(obj)
{
	if(obj.value.length<8 || obj.value.length>15){
		alert("密码长度：8~15！");
		window.event.returnValue=false;
		return false;
	}
	if(!isPasswd(obj)){
		alert("密码不合法,请输入数字！");
		window.event.returnValue=false;
		return false;
	}
    window.event.returnValue = true;
	return true;
}

function getpara()
{
	var error = hasError();
	switch(error){
		case "1":
			alert("操作失败！");
			break;
		case "2":
			alert("对不起，此用户名已存在！");
			break;
		case "3":
			alert("密码修改成功，请重新登录！");
			parent.parent.parent.document.location = "http://"+window.location.host;
			break;
	}
}
//-->
</script>
</head>

<body onload="setOperator();getpara();InitUserList();initOpDiv();">
<iframe id="hideframe" name="hideframe" style="display:none ;"></iframe>
<form name="UserListForm" action="/infinova/userparaCfg" method="post" target="hideframe">
<input type="hidden" name="operator" value="" />
  <table cellpadding="0" cellspacing="0" class="bttable" width="840">
  <tr class="menu1">
	  <td width="838" height="30">&nbsp;用户管理</td>
  </tr>
  <tr>
	  <td width="838" align="center">
		<table cellpadding="0" cellspacing="0" class="utable" width="800">
		<tr><td colspan="6"><div id="opDiv" style="display:none">
		  <table width="798" cellpadding="0" cellspacing="0">
			<tr class="sublist">
		  	<th width="87" height="29">操作选择</th>
		  <td colspan="5">&nbsp;</td>
		</tr>
		  <tr>
		  	<td height="25">&nbsp;</td>
		  	<td width="114"><input type="radio" name="radiobutton" value="0" checked onclick="ShowOrHide('editDiv','addDiv');" /><img src="images/edit.gif" alt="编辑" /></td>
		  	<td width="115"><input type="radio" name="radiobutton" value="1" onclick="ShowOrHide('addDiv','editDiv');" /><img src="images/add.gif" alt="添加" /></td>
		 	<td width="480"><input type="radio" name="radiobutton" value="2" onclick="ShowOrHide('editDiv','addDiv');" /><img src="images/del.gif" alt="删除" /></td>
		</tr></table></div></td></tr>
		<tr><td colspan="6"><div id="addDiv" style="display:none">
		  <table cellpadding="0" cellspacing="0">
		  <tr class="sublist">
			  <th colspan="6" height="29" align="left">添加用户</th>
		  </tr>
		  <tr>
		    <td width="91" height="25" align="center"><img src="images/bit_1.gif" /></td>
		    <td width="71">用户名：</td>
		    <td colspan="4"><input name="NewUserName" type="text" class="passw" maxlength="15" onchange="assertName(this)" /></td>
		  </tr>
		  <tr>
		    <td height="25" align="center"><img src="images/bit_1.gif" /></td>
		    <td>类型： </td>
		    <td colspan="4">普通用户<input name="NewUserPri" value="200" type="text" style="display:none"/></td>
		  </tr>
		  <tr>
		    <td width="91" height="25" align="center"><img src="images/bit_1.gif" /></td>
		    <td width="71">密码： </td>
		    <td><input name="NewUserPswd" type="password" class="passw" maxlength="15" onchange="assertPW(this)" /></td>
			<td align="center">确认密码：</td>
			<td colspan="2"><input name="NewConfPswd" type="password" maxlength="15" class="passw" /></td>
		  </tr>
		  <tr>
		    <td height="25" align="center">&nbsp;</td>
		    <td>权限设置：</td>
		    <td><input name="Addcheckallpri" type="checkbox" value="1" onclick="AddcheckAllPri()"/>
全选</td>
		    <td>&nbsp;</td>
		    <td>&nbsp;</td>
		    <td>&nbsp;</td>
		    </tr>
		  <tr>
		    <td height="25" align="center"><img src="images/bit_1.gif" /></td>
		    <td width="71">预览权限：</td>
		    <td width="154"><input type="checkbox" name="NewNetPrev" value="1" checked/> 
		    网络预览</td>
  			<td width="154"><input type="checkbox" name="NewNetPlay" value="1" checked /> 
  			网络回放</td>
			<td width="154"><input type="checkbox" name="NewLocPlay" value="1" checked /> 
			本地播放</td>
			<td width="172"><input type="checkbox" name="NewLogView" value="1" checked /> 
			日志查看 </td>
		  </tr>
		  <tr><td>&nbsp;</td><td>控制权限：</td>
		    <td><input type="checkbox" name="NewPTZ" value="1" /> 
		    云台控制</td>
  			<td><input type="checkbox" name="NewAlarm" value="1" /> 
  			报警控制</td>
			<td><input type="checkbox" name="NewTalk" value="1" /> 
			语音对讲</td>
			<td><input type="checkbox" name="NewRecord" value="1" /> 
			录像控制 </td>
		  </tr><tr>
		  <td>&nbsp;</td><td>管理权限：</td>
		    <td><input type="checkbox" name="NewCfg" value="1" /> 
		    参数设置 </td>
  			<td><input type="checkbox" name="NewSys" value="1" /> 
  			系统管理</td>
			<td><input type="checkbox" name="NewUser" value="1" disabled /> 
			用户管理</td>
			<td><input type="checkbox" name="NewData" value="1" /> 
			数据管理</td>
		</tr></table>
		</div></td></tr>
		<tr><td colspan="6"><div id="editDiv" style="display:">
		  <table cellpadding="0" cellspacing="0">
		  <tr id="editTitle"  class="sublist">
			  <th height="29">编辑用户信息 </th>
			  <td colspan="5"><iframe src="getUser.asp" name="getUser" style="display:none"></iframe> <input type="hidden" name="flag" value="0" /></td>
		  </tr>
		  <tr id="delTitle" style="display:none"  class="sublist">
			  <th height="29" colspan="6">删除用户 </th>
		  </tr>
		  <tr>
		    <td width="91" height="25" align="center"><img src="images/bit_1.gif" /></td>
		    <td width="71">用户名：</td>
		    <td colspan="4"><select name="UserNameList" class="selectw" onchange="getUserByNum(this.selectedIndex)"></select></td>
		  </tr>
		  <tr>
		    <td height="25" align="center"><img src="images/bit_1.gif" /></td>
		    <td>类型：</td>
		    <td colspan="4"><select name="userinfo0" class="selectw" disabled>
              <option value="0">管理员</option>
              <option value="1">普通用户</option>
            </select><input name="userinfo1" value="255" type="text" style="display:none"/></td>
		  </tr>
		  <tr id="oldpwd">
		    <td height="25" align="center"><img src="images/bit_1.gif" /></td>
		    <td>原密码</td>
		    <td><input name="userinfo16" type="password" class="passw" maxlength="15" /></td>
		    <td align="center">&nbsp;</td>
		    <td colspan="2">&nbsp;</td>
		    </tr>
		  <tr id="pwd">
		    <td width="91" height="25" align="center"><img src="images/bit_1.gif" /></td>
		    <td width="71">密码： </td>
		    <td><input name="userinfo14" type="password" class="passw" maxlength="15" onchange="assertPW(this)" /></td>
			<td align="center">确认密码：</td>
			<td colspan="2"><input name="userinfo15" type="password" class="passw" maxlength="15" /></td>
		  </tr>
		  <tr>
		    <td height="25" align="center">&nbsp;</td>
		    <td>权限设置：</td>
		    <td><input name="checkallpri" type="checkbox" value="1" onclick="checkAllPri()"/>		      
		      全选</td>
		    <td>&nbsp;</td>
		    <td>&nbsp;</td>
		    <td>&nbsp;</td>
		    </tr>
		  <tr>
		    <td height="25" align="center"><img src="images/bit_1.gif" /></td>
		    <td width="71">浏览：</td>
		    <td width="154"><input name="userinfo2" type="checkbox" value="1"/> 
		    网络预览</td>
  			<td width="154"><input type="checkbox" name="userinfo3" value="1" /> 
  			网络回放</td>
			<td width="154"><input type="checkbox" name="userinfo4" value="1" /> 
			本地播放</td>
			<td width="172"><input type="checkbox" name="userinfo5" value="1" /> 
			日志查看 </td>
		  </tr>
		  <tr><td>&nbsp;</td>
		  <td>控制：</td>
		    <td><input type="checkbox" name="userinfo6" value="1" />
		    云台控制</td>
  			<td><input type="checkbox" name="userinfo7" value="1" /> 
  			报警控制</td>
			<td><input type="checkbox" name="userinfo8" value="1" />	
			语音对讲</td>
			<td><input type="checkbox" name="userinfo9" value="1" /> 
			录像控制</td>
		  </tr><tr>
		  <td>&nbsp;</td>
		  <td>管理：</td>
		    <td><input type="checkbox" name="userinfo10" value="1" /> 
		    参数设置</td>
  			<td><input type="checkbox" name="userinfo11" value="1" /> 
  			系统管理</td>
			<td><input type="checkbox" name="userinfo12" value="1" disabled /> 
			用户管理</td>
			<td><input type="checkbox" name="userinfo13" value="1" /> 
			数据管理</td>
		    </tr></table>
		</div></td></tr>
  		<tr>
	  		<td width="88" height="25" class="menu1">保存设置</td>
			<td width="710" colspan="4" class="menu1"><input name="button" type="button" class="myButton" value="应&nbsp;&nbsp;用" onclick="setUserCfg()" /><input type="hidden" name="lang" value="cn"></td>
  		</tr>
		</table></td>
		  </tr>
		  </table>
	  </td>
  </tr>
  </table>
</form>
</body>
</html>
