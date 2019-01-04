// JavaScript Document
function initOpDiv()
{
	if(document.getElementById("operator").value == "admin"){
		document.all.opDiv.style.display = "";
	}	
}

function setPriReadonly(bool)
{
	for(i=2;i<=13;i++){
		if(bool == "1")
		{
			document.getElementById("checkallpri").disabled = true;
			document.getElementById("userinfo"+i).disabled = true;
		}
		else
		{
			document.getElementById("checkallpri").disabled = false;
			document.getElementById("userinfo"+i).disabled = false;
		}
	}
	//document.getElementById("userinfo8").disabled = true;
	document.getElementById("userinfo12").disabled = true;
}

function setPwReadonly(bool)
{
	if(bool == "1"){
		document.getElementById("userinfo14").disabled = true;
		document.getElementById("userinfo15").disabled = true;
	}
	else{
		document.getElementById("userinfo14").disabled = false;
		document.getElementById("userinfo15").disabled = false;
	}
}
	
function InitUserList()
{
	try{
		userNum = parseInt(document.getUser.document.getElementById("UserNum").value);

		var userOn = getCookie("loginname=");
		if((document.getElementById("UserNameList").value == "admin") || (userOn != "admin"))
		{
			document.getElementById("userinfo16").disabled = false;
			document.getElementById("userinfo14").value = "";
			document.getElementById("userinfo15").value = "";
			document.getElementById("userinfo16").value = "";
			document.getElementById("userinfo16").value = "";
		}
		else
		{
			document.getElementById("userinfo16").disabled = true;
			document.getElementById("userinfo16").value = "11111111";
		}
		
		for(i=userNum; i>=0;i--)
		{ 
			document.UserListForm.UserNameList.remove(i); 
		} 
		
		username = document.getUser.document.getElementById("UserName_"+(userNum-1)).value;
		passws = document.getUser.document.getElementById("UserPass_"+(userNum-1)).value;
		addcookie("UseroldPass0="+passws);
		document.UserListForm.UserNameList.options.add(new Option(username,username));
		for(i=0;i<userNum-1;i++){
			passNo = i + 1;
			username = document.getUser.document.getElementById("UserName_"+i).value;
			passws = document.getUser.document.getElementById("UserPass_"+passNo).value;
			addcookie("UseroldPass"+passNo+"="+passws);
			document.UserListForm.UserNameList.options.add(new Option(username,username));
		}
		getUserByNum(userNum);
	}catch(e){}	
}

function checkAllPri()
{
	if(document.getElementById("checkallpri").checked)	
	{
		for(i=2;i<=13;i++){
			document.getElementById("userinfo"+i).checked = true;
		}
	}
	else
	{
		for(i=2;i<=13;i++){
			document.getElementById("userinfo"+i).checked = false;
		}
	}
	//document.getElementById("userinfo8").checked = true;
	document.getElementById("userinfo12").checked = false;
}

function AddcheckAllPri()
{
	var checkstat;
	if(document.getElementById("Addcheckallpri").checked)	
	{
		checkstat = true;
	}
	else
	{
		checkstat = false;
	}
	document.getElementById("NewNetPrev").checked = checkstat;
	document.getElementById("NewNetPlay").checked = checkstat;
	document.getElementById("NewLocPlay").checked = checkstat;
	document.getElementById("NewLogView").checked = checkstat;
	document.getElementById("NewPTZ").checked = checkstat;
	document.getElementById("NewAlarm").checked = checkstat;
	document.getElementById("NewTalk").checked = checkstat;
	document.getElementById("NewRecord").checked = checkstat;
	document.getElementById("NewCfg").checked = checkstat;
	document.getElementById("NewSys").checked = checkstat;
	document.getElementById("NewUser").checked = false;
	document.getElementById("NewData").checked = checkstat;
}

function getUserByNum(num)
{
	userNum = parseInt(document.getUser.document.getElementById("UserNum").value);
	if(num == 0)
	{
		num = userNum - 1;
	}
	else
	{
		num = num -1;	
	}
	switch(document.getUser.document.getElementById("UserType_"+num).value){
		case "0":
			document.UserListForm.userinfo0.selectedIndex = 0;
			break;
		case "1":
			document.UserListForm.userinfo0.selectedIndex = 1;
			break;
		default:break;
	}
	document.UserListForm.userinfo1.value = document.getUser.document.getElementById("UserPrio_"+num).value;
	
	getPrivilege(document.UserListForm.userinfo2, document.getUser.document.getElementById("NetPrev_"+num));
	getPrivilege(document.UserListForm.userinfo3, document.getUser.document.getElementById("NetPlay_"+num));
	getPrivilege(document.UserListForm.userinfo4, document.getUser.document.getElementById("LocPlay_"+num));
	getPrivilege(document.UserListForm.userinfo5, document.getUser.document.getElementById("LogView_"+num));
	getPrivilege(document.UserListForm.userinfo6, document.getUser.document.getElementById("UserPTZ_"+num));
	getPrivilege(document.UserListForm.userinfo7, document.getUser.document.getElementById("UserAlar_"+num));
	//document.UserListForm.userinfo8.checked = true;
	getPrivilege(document.UserListForm.userinfo8, document.getUser.document.getElementById("UserTalk_"+num));
	getPrivilege(document.UserListForm.userinfo9, document.getUser.document.getElementById("UserRecd_"+num));
	getPrivilege(document.UserListForm.userinfo10, document.getUser.document.getElementById("CfgMan_"+num));
	getPrivilege(document.UserListForm.userinfo11, document.getUser.document.getElementById("SysMan_"+num));
	getPrivilege(document.UserListForm.userinfo12, document.getUser.document.getElementById("UserMan_"+num));
	getPrivilege(document.UserListForm.userinfo13, document.getUser.document.getElementById("DataMan_"+num));
	if(document.getElementById("UserNameList").value == document.getElementById("operator").value){
		setPriReadonly("1");
		setPwReadonly("0");	
		document.UserListForm.flag.value = 0x0004;
	}
	else{
		setPriReadonly("0");
		setPwReadonly("0");	
		document.UserListForm.flag.value = 0x0002;
	}
	var userOn = getCookie("loginname=");
	if((document.getElementById("UserNameList").value == "admin") || (userOn != "admin"))
	{
		document.getElementById("userinfo16").disabled = false;
		document.getElementById("userinfo14").value = "";
		document.getElementById("userinfo15").value = "";
		document.getElementById("userinfo16").value = "";
	}
	else
	{
		document.getElementById("userinfo16").disabled = true;	
		document.getElementById("userinfo16").value = "11111111";
	}
}

function getPrivilege(chk_obj, txt_obj)
{
	if(txt_obj.value == "1"){
		chk_obj.checked = true;
	}
	else{
		chk_obj.checked = false;
	}
}

function disableDiv(bOn)
{
	document.getElementById("oldpwd").style.display = bOn;
	document.getElementById("pwd").style.display = bOn;
	//document.getElementById("userinfo16").style.display = bOn;
}
	
function ShowOrHide(div1,div2)
{
	if(document.UserListForm.radiobutton[0].checked)
	{//edit user
		document.getElementById("editTitle").style.display = "";
		document.getElementById("delTitle").style.display = "none";
	}
	if(document.UserListForm.radiobutton[2].checked)
	{//delete user
		document.getElementById("editTitle").style.display = "none";
		document.getElementById("delTitle").style.display = "";
	}
	if(div1 == "editDiv")
	{
		document.getElementById("NewUserName").value = "";
		document.getElementById("NewUserPswd").value = "";
		document.getElementById("NewConfPswd").value = "";
		document.getElementById("oldpwd").style.display = "";
		if(document.UserListForm.radiobutton[2].checked)
		{
			disableDiv("none");
		}
		else
		{
			disableDiv("");
		}
	}
	else
	{
		document.getElementById("oldpwd").style.display = "none";
	}

	document.getElementById(div1).style.display = "";
	document.getElementById(div2).style.display = "none";
	
}