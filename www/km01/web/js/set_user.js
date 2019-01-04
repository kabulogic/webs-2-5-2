// JavaScript Document
function setUserCfg()
{
	var flag = document.UserListForm.flag.value;
	var useid = document.UserListForm.UserNameList.selectedIndex;
	if(document.UserListForm.radiobutton[1].checked){//add user
		if(checkInfo())
		{
			flag = 0x0001;
		}
		else return;
	}
	else if(document.UserListForm.radiobutton[0].checked){//edit user
		if(flag == 0x0002){
			if(!checkInfo()) return;
/*			bool = checkComp(document.UserListForm.userinfo2, document.getElementById("NetPrev_"+useid));
			bool |= checkComp(document.UserListForm.userinfo3, document.getElementById("NetPlay_"+useid));
			bool |= checkComp(document.UserListForm.userinfo4, document.getElementById("LocPlay_"+useid));
			bool |= checkComp(document.UserListForm.userinfo5, document.getElementById("LogView_"+useid));
			bool |= checkComp(document.UserListForm.userinfo6, document.getElementById("UserPTZ_"+useid));
			bool |= checkComp(document.UserListForm.userinfo7, document.getElementById("UserAlar_"+useid));
			bool |= checkComp(document.UserListForm.userinfo9, document.getElementById("UserRecd_"+useid));
			bool |= checkComp(document.UserListForm.userinfo10, document.getElementById("CfgMan_"+useid));
			bool |= checkComp(document.UserListForm.userinfo11, document.getElementById("SysMan_"+useid));
			bool |= checkComp(document.UserListForm.userinfo12, document.getElementById("UserMan_"+useid));
			bool |= checkComp(document.UserListForm.userinfo13, document.getElementById("DataMan_"+useid));
			if(!bool) return;
*/		}
		else if(flag == 0x0004){
			if(!checkInfo()) return;
		}
		if((document.getElementById("UserNameList").value == "admin") || (getCookie("loginname=") != "admin"))
		{
			addcookie("loginpass="+document.UserListForm.userinfo14.value);
		}
	}
	else if(document.UserListForm.radiobutton[2].checked){//delete user
		if(checkInfo()) flag = 0x0008;
		else return;
	}
	if(flag != 0){
		document.UserListForm.flag.value = flag;
		document.UserListForm.submit();
		document.getUser.location.reload();
		setTimeout("InitUserList()",1000);
	}
}

function checkPass(obj1,obj2)
{
	if(obj1 && obj2){
		if(obj1.value == obj2.value) return true;	
	}
	return false;
}
