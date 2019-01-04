// JavaScript Document
function setMenuBg(no)
{
	for(i=1;i<=11;i++){
		if(i == no)	document.getElementById("set"+i).background = "images/menu0.gif";
		else document.getElementById("set"+i).background = "images/menu_.gif";
	}
}
function config1(lang)
{
	getCurUser();
	setMenuBg(1);
	if(lang == "cn") parent.rightFrame.document.location = "../SystemInfo_c.asp";
	else parent.rightFrame.document.location = "../SystemInfo.asp";
	//getSysCfg();
}
function config2(lang)
{
	getCurUser();
	setMenuBg(2);
	if(lang == "cn") parent.rightFrame.document.location = "../NetInfo_c.asp";
	else parent.rightFrame.document.location = "../NetInfo.asp";
	//getSysCfg();
}
function config3(lang)
{
	getCurUser();
	setMenuBg(3);
	DelCook();
	if(lang == "cn") parent.rightFrame.document.location = "../ChannelInfo_c.asp";
	else parent.rightFrame.document.location = "../ChannelInfo.asp";
	//getSysCfg();
}
function config4(lang)
{
	getCurUser();
	setMenuBg(4);
	DelCook();
	if(lang == "cn") parent.rightFrame.document.location = "../RecordInfo_c.asp";
	else parent.rightFrame.document.location = "../RecordInfo.asp";
	
	//getSysCfg();
}
function config5(lang)
{
	getCurUser();
	setMenuBg(5);
	DelRS422Ch();
	if(lang == "cn") parent.rightFrame.document.location = "../ComInfo_c.asp";
	else parent.rightFrame.document.location = "../ComInfo.asp";
	
	//getSysCfg();
}
function config6(lang)
{
	getCurUser();
	setMenuBg(6);
	DelAIOCook();
	if(lang == "cn") parent.rightFrame.document.location = "../AlarmInfo_c.asp";
	else parent.rightFrame.document.location = "../AlarmInfo.asp";
	//getSysCfg();
}
function config7(lang)
{
	getCurUser();
	setMenuBg(7);
	if(lang == "cn") parent.rightFrame.document.location = "../UserList_c.asp";
	else parent.rightFrame.document.location = "../UserList.asp";
}
function config8(lang)
{
	getCurUser();
	setMenuBg(8);
	//var enable = getSysCfg();
	//if(enable=="0") parent.rightFrame.document.location = "../NoPri.htm";
	//else{
		if(lang == "cn") parent.rightFrame.document.location = "../Advance_c.asp";
		else parent.rightFrame.document.location = "../Advance.asp";
	//}
}
function config9(lang)
{
	getCurUser();
	setMenuBg(9);
	if(lang == "cn") parent.rightFrame.document.location = "../RecSta_c.asp";
	else parent.rightFrame.document.location = "../RecSta.asp";
}
function config10(lang)
{
	getCurUser();
	setMenuBg(10);
	if(lang == "cn") parent.rightFrame.document.location = "../Time_c.asp";
	else parent.rightFrame.document.location = "../Time.asp";
}
function config11(lang)
{
	getCurUser();
	setMenuBg(11);
	if(lang == "cn") parent.rightFrame.document.location = "../AstCtrl_c.asp";
	else parent.rightFrame.document.location = "../AstCtrl.asp";
}
function getCurUser()
{
	var user = parent.parent.topFrame.document.operator.user.value;
	addcookie("user="+user);
}
function DelRS422Ch()
{
	addcookie("RS422Ch=0");
}
function getSysCfg()
{
	/*var ret=0;
	var value = document.UserInfo.pri.value;
	if(value & 0x02) ret=1;
	return ret;*/
}