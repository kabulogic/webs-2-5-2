<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7">
<title>User manage</title>
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
			alert("The number of users is more than the maximum(16)!");
			return false;
		}
		if(document.UserListForm.NewUserName.value == ""){
			alert("User name can not be null!");
			window.event.returnValue=false;
			return false;
		}
		if(!assertName(document.UserListForm.NewUserName)){
			window.event.returnValue=false;
			return false;
		}
		if(document.UserListForm.NewUserPswd.value == ""){
			alert("Password can not be null!");
			return false;
		}
		if(!assertPW(document.UserListForm.NewUserPswd)){
			window.event.returnValue=false;
			return false;
		}
		if(!isStr(document.UserListForm.NewUserName,20) || !isStr(document.UserListForm.NewUserPswd,20) || !isStr(document.UserListForm.NewConfPswd,20)){
			return false;
		}
		if(!checkPass(document.UserListForm.NewUserPswd,document.UserListForm.NewConfPswd)){
			alert("Passwords do not match!");
			window.event.returnValue=false;
			return false;
		}
	}
	if(document.UserListForm.radiobutton[0].checked){//edit user
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
				alert("Old password is wrong!");
				window.event.returnValue=false;
				return false;
			}
		}
		if(document.UserListForm.userinfo14.value=="")
		{
			alert("Password can not be null!");
			window.event.returnValue=false;
			return false;
		}
		if(!checkPass(document.UserListForm.userinfo14,document.UserListForm.userinfo15)){
			alert("Passwords do not match!");
			window.event.returnValue=false;
			return false;
		}
	}
	if(document.UserListForm.radiobutton[2].checked)
	{//delete user
		if((document.getElementById("UserNameList").value == "admin"))
		{
			alert("You can not delete this user!");
			return false;
		}
		if(window.confirm("Are you sure to delete this user?"))
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
		alert("User name length: 1~15!");
		window.event.returnValue=false;
		return false;
	}
	if(!isTrueName(obj)){
		alert("User name includes illegal characters or chinese!");
		window.event.returnValue=false;
		return false;
	}
    window.event.returnValue = true;
	return true;
}

function assertPW(obj)
{
	if(obj.value.length<8 || obj.value.length>15){
		alert("Password length: 8~15!");
		window.event.returnValue=false;
		return false;
	}
	if(!isPasswd(obj)){
		alert("Password is illegal,Please input number!");
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
			alert("Operation is failed!");
			break;
		case "2":
			alert("The user's name has been used!");
			break;
		case "3":
			alert("Modify password successfully,please login again!");
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
	  <td width="838" height="30">&nbsp;User Manage</td>
  </tr>
  <tr>
	  <td width="838" align="center">
		<table cellpadding="0" cellspacing="0" class="utable" width="800">
		<tr><td colspan="6"><div id="opDiv" style="display:none">
		  <table width="798" cellpadding="0" cellspacing="0">
			<tr class="sublist">
		  	<th width="91" height="29">Operation </th>
		 	<td colspan="6">&nbsp;</td></tr>
		 	<tr>
		  	<td height="25">&nbsp;</td>
		  	<td width="124"><input type="radio" name="radiobutton" value="0" checked onclick="ShowOrHide('editDiv','addDiv');" /><img src="images/edit.gif" alt="Edit" /></td>
		  	<td width="126"><input type="radio" name="radiobutton" value="1" onclick="ShowOrHide('addDiv','editDiv');" /><img src="images/add.gif" alt="Add" /></td>
		 	<td width="455"><input type="radio" name="radiobutton" value="2" onclick="ShowOrHide('editDiv','addDiv');" /><img src="images/del.gif" alt="Del" /></td>
		 	</tr></table>
		</div></td></tr>
		<tr><td colspan="6"><div id="addDiv" style="display:none">
		  <table cellpadding="0" cellspacing="0">
		  <tr class="sublist">
			  <th colspan="6" height="29" align="left">New User Info</th>
		  </tr>
		  <tr>
		    <td width="92" height="25" align="center"><img src="images/bit_1.gif" /></td>
		    <td width="109">User Name: </td>
		    <td colspan="4"><input name="NewUserName" type="text" class="passw" maxlength="15" onchange="assertName(this)" /></td>
		  </tr>
		  <tr>
		    <td height="25" align="center"><img src="images/bit_1.gif" /></td>
		    <td>User Type: </td>
		    <td colspan="4">CommonUser<input name="NewUserPri" value="200" type="text" style="display:none"/></td>
		  </tr>
		  <tr>
		    <td width="92" height="25" align="center"><img src="images/bit_1.gif" /></td>
		    <td width="109">User Password: </td>
		    <td><input name="NewUserPswd" type="password" class="passw" maxlength="15" onchange="assertPW(this)" /></td>
			<td align="center">Confirm:</td>
			<td colspan="2"><input name="NewConfPswd" type="password" maxlength="15" class="passw" /></td>
		  </tr>
		  <tr>
		    <td height="25" align="center">&nbsp;</td>
		    <td>User Privilege:</td>
		    <td><input name="Addcheckallpri" type="checkbox" value="1" onclick="AddcheckAllPri()"/>
Select All</td>
		    <td>&nbsp;</td>
		    <td>&nbsp;</td>
		    <td>&nbsp;</td>
		    </tr>
		  <tr>
		    <td height="25" align="center"><img src="images/bit_1.gif" /></td>
		    <td width="109">View:</td>
		    <td width="152"><input type="checkbox" name="NewNetPrev" value="1" checked/> Remote Live View</td>
  			<td width="143"><input type="checkbox" name="NewNetPlay" value="1" checked /> Remote Playback</td>
			<td width="147"><input type="checkbox" name="NewLocPlay" value="1" checked /> Local Playback</td>
			<td width="153"><input type="checkbox" name="NewLogView" value="1" checked /> View Log</td>
		  </tr>
		  <tr><td>&nbsp;</td><td>Control:</td>
		    <td><input type="checkbox" name="NewPTZ" value="1"/> PTZ</td>
  			<td><input type="checkbox" name="NewAlarm" value="1"/> Alarm</td>
			<td><input type="checkbox" name="NewTalk" value="1" disabled /> Voice Talking</td>
			<td><input type="checkbox" name="NewRecord" value="1" /> Manual Recording</td>
		  </tr><tr>
		  <td>&nbsp;</td><td>Management:</td>
		    <td><input type="checkbox" name="NewCfg" value="1" /> Parameter </td>
  			<td><input type="checkbox" name="NewSys" value="1" /> System</td>
			<td><input type="checkbox" name="NewUser" value="1" disabled /> User</td>
			<td><input type="checkbox" name="NewData" value="1" /> Data</td>
		</tr></table></div></td></tr>
		<tr><td colspan="6"><div id="editDiv" style="display:">
		  <table cellpadding="0" cellspacing="0">
		  <tr id="editTitle" class="sublist">
			  <th height="29">Edit User Info </th>
			  <td colspan="5"><iframe src="getUser.asp" name="getUser" style="display:none"></iframe><input type="hidden" name="flag" value="0" /></td>
		  </tr>
		  <tr id="delTitle" style="display:none"  class="sublist">
			  <th height="29" colspan="6">Delete User </th>
		  </tr>
		  <tr>
		    <td width="92" height="25" align="center"><img src="images/bit_1.gif" /></td>
		    <td width="109">User Select: </td>
		    <td colspan="4"><select name="UserNameList" class="selectw" onchange="getUserByNum(this.selectedIndex)"></select></td>
		  </tr>
		  <tr>
		    <td height="25" align="center"><img src="images/bit_1.gif" /></td>
		    <td>User Type: </td>
		    <td colspan="4"><select name="userinfo0" class="selectw" disabled>
              <option value="0">Admin</option>
              <option value="1">CommonUser</option>
            </select><input name="userinfo1" value="255" type="text" style="display:none"/></td>
		  </tr>
		  <tr id="oldpwd">
		    <td height="25" align="center"><img src="images/bit_1.gif" /></td>
		    <td>Old Password: </td>
		    <td><input name="userinfo16" type="password" class="passw" maxlength="15" /></td>
		    <td align="center">&nbsp;</td>
		    <td colspan="2">&nbsp;</td>
		    </tr>
		  <tr id="pwd">
		    <td width="92" height="25" align="center"><img src="images/bit_1.gif" /></td>
		    <td width="109">New Password: </td>
		    <td><input name="userinfo14" type="password" class="passw" maxlength="15" onchange="assertPW(this)" /></td>
			<td align="center">Confirm:</td>
			<td colspan="2"><input name="userinfo15" type="password" maxlength="15" class="passw" /></td>
		  </tr>
		  <tr>
		    <td height="25" align="center">&nbsp;</td>
		    <td>User Privilege:</td>
		    <td><input name="checkallpri" type="checkbox" value="1" onclick="checkAllPri()"/>		      
		      Select All </td>
		    <td>&nbsp;</td>
		    <td>&nbsp;</td>
		    <td>&nbsp;</td>
		    </tr>
		  <tr>
		    <td height="25" align="center"><img src="images/bit_1.gif" /></td>
		    <td width="109">View:</td>
		    <td width="152"><input name="userinfo2" type="checkbox" value="1"/> 
		    Remote Live View </td>
  			<td width="143"><input type="checkbox" name="userinfo3" value="1" /> 
  			Remote Playback</td>
			<td width="147"><input type="checkbox" name="userinfo4" value="1" /> 
			Local Playback</td>
			<td width="153"><input type="checkbox" name="userinfo5" value="1" /> 
			View Log </td>
		  </tr>
		  <tr><td>&nbsp;</td>
		  <td>Control:</td>
		    <td><input type="checkbox" name="userinfo6" value="1" /> 
		    PTZ </td>
  			<td><input type="checkbox" name="userinfo7" value="1" /> 
  			Alarm </td>
			<td><input type="checkbox" name="userinfo8" value="1" />
			  Voice Talking</td>
			<td><input type="checkbox" name="userinfo9" value="1" /> 
			Manual Recording </td>
		  </tr><tr>
		  <td>&nbsp;</td>
		  <td>Management:</td>
		    <td><input type="checkbox" name="userinfo10" value="1" /> Parameter</td>
  			<td><input type="checkbox" name="userinfo11" value="1" /> System</td>
			<td><input type="checkbox" name="userinfo12" value="1" disabled /> 
			User </td>
			<td><input type="checkbox" name="userinfo13" value="1" /> 
			Data </td>
		    </tr></table>
		</div></td></tr>
  		<tr>
	  		<td colspan="6" class="menu1" height="25">Save all the parameters: <input name="button" type="button" class="myButton" value="Set" onclick="setUserCfg()" /><input type="hidden" name="lang" value="en"></td>
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
