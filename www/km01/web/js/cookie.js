// JavaScript Document
function addcookie(cookiestring)
{
	var expireDate = new Date();
	expireDate.setTime(expireDate.getTime() + 365*24*60*60*1000);
	document.cookie = cookiestring + ";expires=" + expireDate.toGMTString() + ";path=/";
}
function delcookie(cookiestring)
{
	var expireDate = new Date();
	expireDate.setTime(expireDate.getTime() - 1);
	document.cookie = cookiestring + ";expires=" + expireDate.toGMTString() + ";path=/";
}
function readcookie(cookiestring) 
{ 
	var mycookie = document.cookie;
	pos = mycookie.indexOf(cookiestring,0);
	if(pos==-1)
		return false;
	else return true;
} 
function getCookie(cookiestring)
{
	var res = "";
	var mycookie = document.cookie;
	tmp = mycookie.split(";");
	for(i=0;i<tmp.length;i++){
		if((tmp[i].indexOf(cookiestring,0)) != -1){
			array = tmp[i].split("=");
			res = array[1];
		}
	}
	return res;
}
function validate()
{
	var num = 1;
	if(readcookie("ErrLog")){
		num = parseInt(getCookie("ErrLog"));
		if(num < 2)
		{
			num++;
		}
		else return false;
	}
	addcookie("ErrLog="+num);
	return true;
}
function clearVal()
{
	if(readcookie("ErrLog")){
		num = parseInt(getCookie("ErrLog"));
		delcookie("ErrLog="+num);
	}
}

function addVisitedIP()
{
	addcookie("visitedIP="+window.location.href);
}

function deleteVisitedIP()
{
	delcookie("visitedIP="+window.location.href);
}