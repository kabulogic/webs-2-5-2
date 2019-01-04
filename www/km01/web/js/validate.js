// JavaScript Document
function validateH(hour,type)
{
	h = hour.value;
	if(isNumber(h)){
		h = parseInt(h);
		if((h > 0) && (h <= 24)){
			saveSign(type);
			event.returnValue = true;
			return;
		}
	}
	hour.value = 0;
	event.returnValue = false;
}

function validateM(minute,type)
{
	m = minute.value;
	if(isNumber(m)){
		m = parseInt(m);
		if((m > 0) && (m < 60)){
			saveSign(type);
			event.returnValue = true;
			return;
		}
	}
	minute.value = 0;
	event.returnValue = false;
}

function saveSign(type)
{
	if(type == "record"){
		setObjectByName("isRecordPlanChange","1");
	}
	if(type == "motion"){
		setObjectByName("isMotionPlanChange","1");
	}
	if(type == "Obs"){
		setObjectByName("isObsPlanChange","1");
	}
	if(type == "Sig"){
		setObjectByName("isSigPlanChange","1");
	}
	if(type == "AlarmIn"){
		setObjectByName("isAlarmInChange","1");
	}
	if(type == "AlarmOut"){
		setObjectByName("isAlarmOutChange","1");
	}
}
function period(name)
{
	var bol = false;
	for(i=1;i<=4;i++){
		bol |= bigger(HourToM(document.getElementById(name+i+"StartH").value,document.getElementById(name+i+"StartM").value), HourToM(document.getElementById(name+i+"EndH").value,document.getElementById(name+i+"EndM").value));
	}
	for(i=1;i<=3;i++){
		j = i+1;
		if(document.getElementById(name+j).checked)
			bol |= bigger(HourToM(document.getElementById(name+i+"EndH").value,document.getElementById(name+i+"EndM").value), HourToM(document.getElementById(name+j+"StartH").value,document.getElementById(name+j+"StartM").value));
	}
	
	if(bol){
		return false;
	}
	return true;
}

function HourToM(h,m)
{
	return parseInt(h)*60+parseInt(m) ;
}

function bigger(a,b)
{
	if(a>24*60 || b>24*60) return true;
	if(a > b) return true;
	else return false;
}

function validateNum(obj,Min,Max,name)
{
	if(obj.value=="")
	{
		alert(name+Min+"-"+Max);
		obj.value = Max;
		window.event.returnValue = false;
		return false;
	}
	if(parseInt(obj.value)<Min)
	{
		alert(name+Min+"-"+Max);
		obj.value = Min;
		window.event.returnValue = false;
		return false;
	}
	if(!isNumMax(obj,Max))
	{
		alert(name+Min+"-"+Max);
		obj.value = Max;
		window.event.returnValue = false;
		return false;
	}
	return true;
}

function validateOsdXY(osd,obj,x_y,hint)
{
	var videoMode = document.getElementById("VideoMode").value;
	var tmp,maxValue,len;
	
	if(x_y == "x")
	{
		if(osd == "week")
		{
			maxValue = (704-32) - 26*17;
		}
		else
		{
			len = (document.getElementById(osd).value).length;
			maxValue = (704-32) - len*32;
		}
	}
	else
	{
		maxValue = (videoMode == 1) ? (576-48) : (480-48);//to N 576 /P 480
	}
	
	tmp =obj.value;
	
	if((tmp == "") || (!isNumber(tmp)) || (parseInt(tmp)>maxValue) || (parseInt(tmp)<0))
	{
		if(x_y == "x") alert(hint+" "+"0-"+maxValue);
		else alert(hint+"0-"+maxValue);
		obj.value = maxValue;
		window.event.returnValue = false;
		return false;
	}
	window.event.returnValue = true;
	return true;
}

function setOsd()
{
	var bCompare1 = (document.getElementById("OSD2_State").selectedIndex == 0) 
				&& (document.getElementById("OSD1_State").selectedIndex == 0) ;
				
	var bCompare2 = (document.getElementById("OSD1_State").selectedIndex == 0) 
				&& (document.getElementById("OSD3_State").checked) ;
				
	var bCompare3 = (document.getElementById("OSD3_State").checked) 
				&& (document.getElementById("OSD4_State").checked) ;
				
	var bCompare4 = (document.getElementById("OSD3_State").checked) 
				&& (document.getElementById("OSD2_State").selectedIndex == 0) ;
				
	var bCompare5 = (document.getElementById("OSD4_State").checked) 
				&& (document.getElementById("OSD1_State").selectedIndex == 0) ;
				
	var bCompare6 = (document.getElementById("OSD4_State").checked) 
				&& (document.getElementById("OSD2_State").selectedIndex == 0) ;
	/*datetime osd*/
	x1 = parseInt(document.ChInfoForm.OSD1_X.value);
	y1 = parseInt(document.ChInfoForm.OSD1_Y.value);
	len1 = 32*12;
	
	/*channel name osd*/
	x2 = parseInt(document.ChInfoForm.OSD2_X.value);
	y2 = parseInt(document.ChInfoForm.OSD2_Y.value);
	len2 = 32*parseInt((document.ChInfoForm.ChannelName.value).length);
	
	/*area1 osd*/
	x3 = parseInt(document.ChInfoForm.OSD3_X.value);
	y3 = parseInt(document.ChInfoForm.OSD3_Y.value);
	len3 = 32*parseInt((document.ChInfoForm.OSD3_Title.value).length);
	
	/*area2 osd*/
	x4 = parseInt(document.ChInfoForm.OSD4_X.value);
	y4 = parseInt(document.ChInfoForm.OSD4_Y.value);
	len4 = 32*parseInt((document.ChInfoForm.OSD4_Title.value).length);
	
	tmp_y = Math.abs(parseInt(y1-y2));
	if((tmp_y < 36) && bCompare1)
	{
		if(((x1<=x2) && ((x2-x1)<len1)) || ((x1>=x2) && ((x1-x2)<len2)))
		{
			return 1;
		}
	}
	
	tmp_y = Math.abs(parseInt(y1-y3));
		
	if((tmp_y < 36) && bCompare2)
	{
		if(((x1<=x3) && ((x3-x1)<len1)) || ((x1>=x3) && ((x1-x3)<len3)))
		{
			return 2;
		}
	}
	
	tmp_y = Math.abs(parseInt(y3-y4));
	if((tmp_y < 36) && bCompare3)
	{
		if(((x3<=x4) && ((x4-x3)<len3)) || ((x3>=x4) && ((x3-x4)<len4)))
		{
			return 3;
		}
	}
	
	tmp_y = Math.abs(parseInt(y3-y2));
	if((tmp_y < 36) && bCompare4)
	{
		if(((x3<=x2) && ((x2-x3)<len3)) || ((x3>=x2) && ((x3-x2)<len2)))
		{
			return 4;
		}
	}
	
	tmp_y = Math.abs(parseInt(y4-y1));
	if((tmp_y < 36) && bCompare5)
	{
		if(((x4<=x1) && ((x1-x4)<len4)) || ((x4>=x1) && ((x4-x1)<len1)))
		{
			return 5;
		}
	}
	tmp_y = Math.abs(parseInt(y4-y2));
	if((tmp_y < 36) && bCompare6)
	{
		if(((x4<=x2) && ((x2-x4)<len4)) || ((x4>=x2) && ((x4-x2)<len2)))
		{
			return 6;
		}
	}
	return 0;
}


function validateString(obj,MaxLen)
{
	if((obj==null)||(obj.value=="")){
		window.event.returnValue = true;
		return true;
	}
	if(!isStr(obj,MaxLen)){
		window.event.returnValue = false;
		addcookie("seterror=1");
		return false;
	}
	delcookie("seterror=1");
}

function isNumMax(obj,Max)
{
	var num = obj.value;
	if(num=="") return true;
	if(isNumber(num)){
		num = parseInt(num);
		if(num>=1 && num<=Max){
			return true;
		}
	}
	return false;
}

function isStr(obj,MaxLen)
{
	var len = obj.value.length;
	if((len>=0)&&(len<=parseInt(MaxLen))){
		return true;
	}
	else return false;
}

function isPort(obj)
{  
	var s = obj.value;
	if(isNumber(s) && s<65536 && s>0){
		window.event.returnValue=true;
		return true;
	}
	window.event.returnValue=false;
	return false;
}

function isTrueName(obj)
{
	var s = obj.value;
	if(s == ""){
		return true;
	}
    var patrn=/^[0-9a-zA-Z]+$/;
    if(!patrn.exec(s)){
		return false;
	}
	return true;
}

function isPasswd(obj)
{
	var s = obj.value;
	if(s == ""){
		return true;
	}
    //var patrn=/^(\w){8,16}$/;
	var patrn=/^[-]{0,1}[0-9]{1,}$/; 
    if(!patrn.exec(s)){
		return false;
	}
	return true;
}
function isMask(obj)
{
	var i = 0,j = 0;
	var mask = obj.value;
	var values = mask.split(".");
	var binary = "";  
	//去掉IP段前的0
	for(i =0;i<4;i++)
	{
		if(values[i].substr(0,1) == "")
		{
			values[i] = 0;
		}
		if(values[i].substr(0,1) == '0')
		{
			values[i] = values[i].substr(1,2);
			if(values[i].substr(0,1) == '0')
			{
				values[i] = values[i].substr(1,1);
			}
			if(values[i] == "")
			{
				values[i] = 0;
			}
		}
	}
	for(i=3;i>=0;i--) 
	{ 
	  if (parseInt(values[i]) >= 2)   
	  {   
			while(parseInt(values[i]) != 0)
			{
				binary = Math.abs(parseInt(values[i])%2) + binary;
				values[i] = parseInt(parseInt(values[i])/2);
			}
			//alert(binary+"----len="+binary.length);
			if(binary.length<8)
			{
				for(j=0;j<8-binary.length;j++)
				{
					binary = "0" + binary;	
				}
			}
		}
		else
		{
			binary = "0000000"+parseInt(values[i]) + binary;
		}
	} 
	
	pos1 = binary.indexOf("0");
	if(pos1 != -1)
	{
		pos2 = binary.indexOf("1",pos1+1);
		if((pos2 != -1) || (parseInt(binary) == 0))
		{
			return false;
		}
	}
	return true;
}

function isIP(obj)
{
	var patrn=/^(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$/;
	var ipaddr = obj.value;
	var sum = 0;
	if(ipaddr == "")
	{
		obj.value = "0.0.0.0";	
		ipaddr = obj.value;
	}
	tmp=ipaddr.split("");
	for(i=0;i<tmp.length;i++)
    { 
		code=tmp[i].charCodeAt();
		if(code == 46) 
		{
			sum ++;
		}
   }
   if(sum != 3)
   {
		if(!patrn.exec(obj.value))
		{
			return false;  //当输入IP未通过验证时，清空输入框并返回-2
		}   
   }
	
	var values = ipaddr.split(".");
	for(i =0;i<4;i++)
	{
		if(values[i].substr(0,1) == '0')
		{
			values[i] = values[i].substr(1,2);
			if(values[i].substr(0,1) == '0')
			{
				values[i] = values[i].substr(1,1);
			}
			if(values[i] == "")
			{
				values[i] = 0;
			}
		}
	}
	obj.value = values[0] + "." + values[1] + "." + values[2] + "." +values[3];
	if(!patrn.exec(obj.value)){
		//obj.value = "";
		return false;  //当输入IP未通过验证时，清空输入框并返回-2
	} 
	return true;//输入值正确时返回真
  
	/*else
	{
		var patrn=/^(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$/;
		if(!patrn.exec(s)){
			return false;
		}
	}*/
}

function hasChinese(obj)
{
	var reg = /[^\u4E00-\u9FA5\uf900-\ufa2d]/g; 
	//匹配非中文的正则表达式 
	var temp = obj.replace(reg,'');
	return temp.length;
}

function isEmail(str)
{
	if(str.length > 19){
		window.event.returnValue=false;
		return false;
	}
	var myReg = /^[-_A-Za-z0-9]+@([_A-Za-z0-9]+\.)+[A-Za-z0-9]{2,3}$/; 
	if((str == "") || (myReg.test(str))){
		window.event.returnValue=true;
		return true; 
	}
	window.event.returnValue=false;
	return false; 
} 

function isNumber(s)
{   
	var regu;
	if(s != 0){
		regu = "^[1-9][0-9]*$"; 
	}
	else{
		regu = "^[0]{1}$";
	}
	var re = new RegExp(regu); 
	if(s.search(re) != -1){ 
		return true; 
	} else { 
		return false; 
	}
}
//FrameRate && IP Rate
function FrameAndIPRate(obj,Min,Max)
{
	num = obj.value;
	if(isNumber(num)){
		if(num>=Min && num<=Max){
			window.event.returnValue=true;
			return true;
		}
	}
	//alert("Input error.");
	window.event.returnValue=false;
	return false;
}