// JavaScript Document
function MM_preloadImages() { //v3.0
 var d=document; if(d.images){ if(!d.MM_p) d.MM_p=new Array();
   var i,j=d.MM_p.length,a=MM_preloadImages.arguments; for(i=0; i<a.length; i++)
   if (a[i].indexOf("#")!=0){ d.MM_p[j]=new Image; d.MM_p[j++].src=a[i];}}
}

//Menu control
function onConfig(lang)
{
	change1();
	leftbg();
	if(lang == "cn") parent.lFrame.rightFrame.document.location="../SystemInfo_c.asp";
	else parent.lFrame.rightFrame.document.location="../SystemInfo.asp";
	parent.main.cols = "*,0,0";
}
function leftbg()
{
	parent.lFrame.leftFrame.document.all.set1.background = "images/menu0.gif";
	for(i=2; i<=11; i++){
		parent.lFrame.leftFrame.document.getElementById("set"+i).background = "images/menu_.gif";
	}
}
function repRec()
{
	path = parent.lFrame.rightFrame.document.location.href;
	if((path.indexOf("RecSta.asp")!=-1)||(path.indexOf("RecSta_c.asp")!=-1)){
		parent.lFrame.rightFrame.document.getElementById('btnStop').click();
	}
}
function onBrowse()
{
	try{
	//parent.mainFrame.document.location.reload();
	repRec();
	change2();
	parent.mainFrame.document.all.NVRPlayer.focus();
	parent.main.cols = "0,*,0";
	}catch(e){}
}
function onReplay()
{
	repRec();
	change3();
	parent.main.cols = "0,0,*";
}
function change1()
{
	document.all.a1.style.color = "#FF0000";
	document.all.a2.style.color = "#FFFFFF";
	document.all.a3.style.color = "#FFFFFF";
}
function change2()
{
	document.all.a1.style.color = "#FFFFFF";
	document.all.a2.style.color = "#FF0000";
	document.all.a3.style.color = "#FFFFFF";
}
function change3()
{
	document.all.a1.style.color = "#FFFFFF";
	document.all.a2.style.color = "#FFFFFF";
	document.all.a3.style.color = "#FF0000";
}
function getOperator()
{
	if(readcookie("login=")){
		str = getCookie("login");
		key = str.split("&");
		user = key[0];
		pass = key[1];
		document.operator.user.value = user;
		document.operator.pass.value = pass;
		addcookie("user="+user);
		addcookie("pass="+pass);
	}
	else{
		parent.window.close();
	}
}
function onLogout()
{
	delcookie("login="+getCookie("login"));
	user = document.operator.user.value;
	pass = document.operator.pass.value;
	if(readcookie("user="+user)){
		document.operator.submit();
		delcookie("user="+user);
	}
	delcookie("pass="+pass);
}
function exit()
{
	parent.document.location = "http://"+window.location.host;
}