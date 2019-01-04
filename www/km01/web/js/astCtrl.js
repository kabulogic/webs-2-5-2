// JavaScript Document
/**************************************************************************************
*保存参数后提示信息
**************************************************************************************/
function getResponse()
{
	var lang = document.getElementById("lang").value;
	var error = hasError();
	switch(error)
	{
		case "1": 
			alert((lang == "cn") ? "辅助设置成功!" : "synchronize local time successfully!");
			break;
		case "-1": 
			alert((lang == "cn") ? "辅助设置失败!" : "synchronize local time failed!");
			break;
		default:
		break;
	}	
}

/**************************************************************************************
*初始化时间显示页面
**************************************************************************************/
function initAstCtrl()
{
	var radio,rad;
	var bOn = parseInt(document.getElementById("On").value);
	document.getElementById("bOn").checked = bOn ? true : false;	

	/*init alarm out Ctrl*/
	for( i = 1; i < 5; i++ )
	{
		ctrType = parseInt(document.getElementById("AOCtrType"+i).value);
		radio = "AORadio" + i;
		rad = document.getElementsByName(radio);
		for( j = 0; j < rad.length; j++ ) 
		{    
			 rad[ctrType].checked = true;
		} 
	}
}

function changeCtrType(no)
{
	if(no == 1)
	{
		document.getElementById("alarmout").style.display = "";	
	}
	else
	{
		document.getElementById("alarmout").style.display = "none";	
	}	
}
/**************************************************************************************
*时区设置
**************************************************************************************/

function setAstCtrl()
{
	document.getElementById("On").value = document.getElementById("bOn").checked ? 1 : 0;
	for( i = 1; i < 5; i++ )
	{
		radio = "AORadio" + i;
		rad = document.getElementsByName(radio);
		for( j = 0; j < rad.length; j++ ) 
		{    
			if(rad[j].checked)
			{
				document.getElementById("AOCtrType"+i).value =  j;
			}
		} 
	}
	document.AstCtrlForm.submit();
}
