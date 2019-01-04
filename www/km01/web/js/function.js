// JavaScript Document
var DVR_CH = getDVR_CH();
function initOptionChn(objName,content)
{
	var obj=document.getElementById(objName);
	obj.options.length=0;
	var text;
	for(i = 1; i <= DVR_CH; i++)
	{
		if(i<10)
		{
			text = content + "0" + i;
		}
		else
		{
			text = content + i;
		}
		obj.options.add(new Option(text,parseInt(i-1)));
	}
	obj.selectedIndex = 0;
}

function initOptionChnCopy(objName,content,All)
{
	var obj=document.getElementById(objName);
	obj.options.length=0;
	var text;
	for(i = 1; i <= DVR_CH; i++)
	{
		if(i<10)
		{
			text = content + "0" + i;
		}
		else
		{
			text = content + i;
		}
		obj.options.add(new Option(text,parseInt(i-1)));
	}
	obj.options.add(new Option(All,parseInt(DVR_CH + 1)));
	obj.selectedIndex = DVR_CH;
}

function choose(key, values)
{
	var tmp = parseInt(key);
	if(tmp<=values[0]) return values[0];
	else{
		for(i=0;i<values.length-1;i++){
			if(tmp>values[i] && tmp<=values[i+1]){
				middle = (values[i]+values[i+1])/2;
				if(tmp<=middle) return values[i];
				else return values[i+1];
				break;
			}
		}
	}
}

function compare(obj1,obj2)
{
	if(obj1 && obj2){
		if(obj1.value != obj2.value){
			obj2.value = obj1.value;
			return true;
		}
	}
	return false;
}

function compareIndex(obj1,obj2)
{
	if(obj1 && obj2){
		if(obj1.selectedIndex != parseInt(obj2.value)){
			obj2.value = obj1.selectedIndex;
			return true;
		}
	}
}

function checkComp(obj_chk, obj_txt)
{
	if(obj_chk && obj_txt){
		if((obj_chk.disabled) && (obj_txt.value=="1")){
			obj_txt.value = "0";
			return true;
		}
		else if((obj_chk.checked) && (obj_txt.value=="0")){
			obj_txt.value = "1";
			return true;
		}
		else if((!obj_chk.checked) && (obj_txt.value=="1")){
			obj_txt.value = "0";
			return true;
		}
	}
	return false;
}

function setCheckObjValue(obj_chk, obj_txt)
{
	if(obj_chk && obj_txt){
		if(obj_chk.checked) obj_txt.value = "1";
		else obj_txt.value = "0";
	}
}
function MinuteToH(minutes)
{
	m = parseInt(minutes);
	if(m > 0){
		return parseInt(m/60);
	}
	else return 0;
}

function MinuteToM(minutes)
{
	m = parseInt(minutes);
	if(m > 0){
		return parseInt(m%60);
	}
	else return 0;
}

function setObjectByName(name,value)
{
	document.getElementById(name).value = value;
}