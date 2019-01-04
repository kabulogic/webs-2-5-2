// JavaScript Document
var flagalarm;
k=0; 
flag=0;
time="00:00";
var CC;
var objFlag;
preNo = 0;
preRow = 0;

//var curNo;
function  insertRow(type,obj)
{   
	for(i=0;i<7;i++)   
	{ 
		flagalarm = obj;
		switch(obj)
		{
			case 'sig':
				R=sigtb0.insertRow(); 
				objFlag = 1;
				break;
			case 'obs':
				R=obstb0.insertRow();
				objFlag = 2;
				break;
			case 'motion':
				R=motiontb0.insertRow();
				objFlag = 3;
				break;
			case 'alarmin':
				R=alarmintb0.insertRow();
				objFlag = 4;
				break;
			case 'alarmout':
				R=alarmouttb0.insertRow();
				objFlag = 5;
				break;
			case 'rec':
				R=rectb0.insertRow();
				objFlag = 6;
				break;
			default:break;
		}
		for(j=0;j<48;j++)  
		{  
			C=R.insertCell()  
			C.innerText = " " 
			if(obj == 'sig' || obj == 'alarmin' || obj == 'rec') tmp = i*48+j
			if(obj == 'obs' || obj == 'alarmout') tmp =(i+7)*48+j
			if(obj == 'motion') tmp =(i+14)*48+j
			if(type=="defend")
			{
				C.innerHTML="<input type='button' id='"+tmp+"' class='button' onMouseOver='changeDefendColor("+tmp+","+i+");displayTime("+objFlag+","+j+","+i+");' onMouseDown='setFlag(1),changeDefendColor("+tmp+","+i+")' onMouseUp='setFlag(0);' onMouseOut = 'hideTime("+objFlag+","+i+")' />" // 
			}
			else
				C.innerHTML="<input type='button' id='"+tmp+"' class='button' onMouseOver='changeRecordColor("+tmp+","+i+");displayTime("+objFlag+","+j+","+i+")' onMouseDown='setFlag(1),changeRecordColor("+tmp+","+i+")' onMouseUp='setFlag(0)' onMouseOut = 'hideTime("+objFlag+","+i+")' />" 
		}   
	}
} 

function fullSetColor(curNum,curRow,color)
{
	var absValue = (Math.abs(parseInt(curNum-preNo)));
	maxNo = (curNum>preNo) ? curNum : preNo; 
	minNo = (curNum<preNo) ? curNum : preNo;
	if((absValue >= 2) && (curRow == preRow))
	{
		for( i = minNo; i < maxNo; i++)
		{
			document.getElementById(i).style.background = color;
		}
	}
	document.getElementById(curNum).style.background = color;
}

function changeDefendColor(m,curRow)
{
	if(flag==1)
	{
		if(event.ctrlKey)
		{
			fullSetColor(m,curRow,"white");
		}
		else
		{
			fullSetColor(m,curRow,"green");
		}
	}
	
	preNo = m;
	preRow = curRow;
	
	if(m<336) 
	{
		if(flagalarm == 'alarmout') setObjectByName("isAlarmInChange","1");
		else setObjectByName("isSigPlanChange","1");
	}
	if((m>=336) && (m<672)) 
	{
		if(flagalarm == 'alarmout') setObjectByName("isAlarmOutChange","1");
		else setObjectByName("isObsPlanChange","1");
	}
	if(m>=672) setObjectByName("isMotionPlanChange","1");
}

function changeRecordColor(m,curRow)
{
	var maxNo,minNo;
	if(flag==1)
	{
		switch(document.getElementById("alarmType").selectedIndex)
		{
			case 0:
				if(event.ctrlKey)
				{
					fullSetColor(m,curRow,"white");
				}
				else
				{
					fullSetColor(m,curRow,"green");
				}
				break;
			case 1:
				if(event.ctrlKey)
				{
					fullSetColor(m,curRow,"white");
				}
				else
				{
					fullSetColor(m,curRow,"red");
				}
				break;
			case 2:
				if(event.ctrlKey)
				{
					fullSetColor(m,curRow,"white");
				}
				else
				{
					fullSetColor(m,curRow,"blue");
				}
				break;
		}		
	}
	
	preNo = m;
	preRow = curRow;
	
	setObjectByName("isRecordPlanChange","1");
}

function setFlag(m)
{
	flag = m;
}

function selectDefendTime(n,obj)
{
	for(i=0;i<7;i++)   
	{ 
		for(j=0;j<48;j++)  
		{  
			if(obj == 'sig' || obj == 'alarmin' || obj == 'rec') tmp = i*48+j
			if(obj == 'obs'|| obj == 'alarmout') tmp =(i+7)*48+j
			if(obj == 'motion') tmp =(i+14)*48+j
			if(n == 0)
			{
				document.getElementById(tmp).style.background = "white";
			}
			else 
			{
				document.getElementById(tmp).style.background = "green";
			}
		}   
	}
	if(tmp<336) 
	{
		if(flagalarm == 'alarmout') setObjectByName("isAlarmInChange","1");
		else setObjectByName("isSigPlanChange","1");
	}
	if((tmp>=336) && (tmp<672)) 
	{
		if(flagalarm == 'alarmout') setObjectByName("isAlarmOutChange","1");
		else setObjectByName("isObsPlanChange","1");
	}
	if(tmp>=672) setObjectByName("isMotionPlanChange","1");
}

function selectRecordTime(n)
{
	for(i=0;i<7;i++)   
	{ 
		for(j=0;j<48;j++)  
		{  
			var tmp = (i*48)+j ;
			if(n == 0) document.getElementById(tmp).style.background = "white";
			else
			{
				switch(document.getElementById("alarmType").selectedIndex)
				{
					case 0:
						document.getElementById(tmp).style.background = "green";
						break;
					case 1:
						document.getElementById(tmp).style.background = "red";
						break;
					case 2:
						document.getElementById(tmp).style.background = "blue";
						break;
					default:
						document.getElementById(tmp).style.background = "white";
						break;
				}	
			}
		}   
	}
	setObjectByName("isRecordPlanChange","1");
}

/*init defend title text*/
function initTitle(obj)
{
	var rowTextcn = ["星期日","星期一","星期二","星期三","星期四","星期五","星期六"]
	var rowTexten = ["Sun","Mon","Tue","Wed","Thu","Fri","Sat"]
	lang = document.getElementById("lang").value;
	for(i=0;i<7;i++)
	{
		switch(obj)
		{
			case 'sig':
				R=sigwtb.insertRow();
				RR=sigviewtime.insertRow();
				RRR=sigttb.insertRow();
				//RRRR=sigttb.insertRow();
				objFlag = 1;
				break;
			case 'obs':
				R=obswtb.insertRow();
				RR=obsviewtime.insertRow();
				RRR=obsttb.insertRow();
				//RRRR=obsttb.insertRow();
				objFlag = 2;
				break;
			case 'motion':
				R=motionwtb.insertRow();
				RR=motionviewtime.insertRow();
				RRR=motionttb.insertRow();
				//RRRR=motionttb.insertRow();
				objFlag = 3;
				break;
			case 'alarmin':
				R=alarminwtb.insertRow();
				RR=alarminviewtime.insertRow();
				RRR=alarminttb.insertRow();
				//RRRR=alarminttb.insertRow();
				objFlag = 4;
				break;
			case 'alarmout':
				R=alarmoutwtb.insertRow();
				RR=alarmoutviewtime.insertRow();
				RRR=alarmoutttb.insertRow();
				//RRRR=alarmoutttb.insertRow();
				objFlag = 5;
				break;
			case 'rec':
				R=recwtb.insertRow();
				RR=recviewtime.insertRow();
				RRR=recttb.insertRow();
				//RRRR=recttb.insertRow();
				objFlag = 6;
				break;
			default:break;
		}
		//display week
		C=R.insertCell()
		if(lang == 'cn') C.innerHTML = "&nbsp;"+rowTextcn[i]+ "&nbsp;";
		else C.innerHTML = "&nbsp;"+rowTexten[i]+ "&nbsp;";
		
		//display select time
		CC=RR.insertCell()
		CC.innerHTML = "&nbsp;"+"<label id = '"+objFlag+'tRow'+i+"' style='color:red' ></label>"+ "&nbsp;";
	}
	
	//display time schedule
	for(i=0;i<13;i++)
	{
		CCC=RRR.insertCell()
		if(i<5)
		{
			CCC.innerHTML += "0"+ i*2+ "<br>|";
		}
		else
		{
			CCC.innerHTML +=  i*2 + "<br>|";
		}
	}
}

function displayTime(obj,id,rowNo)
{
	var hour = parseInt((id+1)/2);
	var minute = parseInt((id+1)%2)*30;
	if(minute == 0)
	{
		minute = "00";
	}
	if(hour <10)
	{
		time = "0"+hour +":"+ minute;
	}
	else
	{
		time = hour +":"+ minute;
	}
	document.getElementById(obj+"tRow"+rowNo).innerText = time;
}

function hideTime(obj,rowNo)
{
	document.getElementById(obj+"tRow"+rowNo).innerText = "";
}

function initchanDefendTimetable()
{
	initTitle('sig');
	initTitle('obs');
	initTitle('motion');
	insertRow('defend','sig');
	insertRow('defend','obs');
	insertRow('defend','motion');
}

function initalarmDefendTimetable()
{
	initTitle('alarmin');
	initTitle('alarmout');
	flagalarm = 'alarmin';
	insertRow('defend','alarmin');
	flagalarm = 'alarmout';
	insertRow('defend','alarmout');
	
}

function initrecordPlantable()
{
	initTitle('rec');
	insertRow('record','rec');
}