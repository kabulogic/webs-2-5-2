function cpFileName(name)
{
	if(name == "update")
	{
		filename = document.ftpForm.file.value;
	}
	else
	{
		filename = document.configInForm.file.value;
	}
	if(filename == "") return 1;
	pos1 = filename.indexOf(":");
	pos2 = filename.indexOf("\\");
	if((pos1 == -1) || (pos2 == -1)) return 2;
	pos = filename.lastIndexOf("\\",filename.length-1);
	key = filename.substring(pos+1,filename.length);
	var containSpecial = /^[^\|"'<>()\[\]{},?~!#%&@*]*$/;
	if(!containSpecial.test(key))
	{
		return	4;
	}
	if(name == "update")
	{
		if(key.lastIndexOf(".ifu") == (key.length -4))
		{
			document.ftpForm.path.value = filename;
			return 0;
		}
	}
	else
	{
		if(key.lastIndexOf(".cfg") == (key.length -4))
		{
			document.configInForm.path.value = filename;
			return 0;
		}
	}
	return 3;	
}

function closewidow() 
{
	parent.parent.window.opener=null;
	parent.parent.window.open("","_self"); 
	parent.parent.window.close();
}

function showtext0(){
	sm = document.getElementById("ttt").innerText;
	if(sm>0) sm--;
	document.getElementById("ttt").innerText = sm;
}
function getDiskInfo(lang)
{
	for(i=0;i<8;i++){
		j = i+1;
		switch(document.getElementById("stat"+i).value){
			case "0": 
				if(lang == 'cn') document.getElementById("s"+j).innerText = "空闲";
				else document.getElementById("s"+j).innerText = "Idle";
				break;
			case "1": 
				if(lang == 'cn') document.getElementById("s"+j).innerText = "工作"; 
				else document.getElementById("s"+j).innerText = "Work"; 
				break;
			case "2": 
				if(lang == 'cn') document.getElementById("s"+j).innerText = "满"; 
				else document.getElementById("s"+j).innerText = "Full"; 
				break;
			case "3": 
				if(lang == 'cn') document.getElementById("s"+j).innerText = "出错"; 
				else document.getElementById("s"+j).innerText = "Error"; 
				break;
			case "4":
				if(lang == 'cn') document.getElementById("s"+j).innerText = "无硬盘"; 
				else document.getElementById("s"+j).innerText = "No disk"; 
				break;
			case "6":
				if(lang == 'cn') document.getElementById("s"+j).innerText = "正在格式化"; 
				else document.getElementById("s"+j).innerText = "Formatting"; 
				break;
			case "7":
				if(lang == 'cn') document.getElementById("s"+j).innerText = "未格式化"; 
				else document.getElementById("s"+j).innerText = "Not Format…"; 
				break;
			default:  
				if(lang == 'cn') document.getElementById("s"+j).innerText = "无"; 
				else document.getElementById("s"+j).innerText = "No"; 
				break;
		}
		if(document.getElementById("stat"+i).value == "4")
		{
			document.getElementById("c"+j).innerText = "--";
			document.getElementById("f"+j).innerText = "--";
			document.getElementById("ck"+i).disabled = true;
		}
		else
		{
			var f = parseFloat(document.getElementById("cap"+i).value/(1000*1000));
			document.getElementById("c"+j).innerText = parseInt(f);      
			f = parseFloat(document.getElementById("free"+i).value/(1000*1000));
			//document.getElementById("f"+j).innerText = f.toFixed( 2 );//reserved 2 decimal fraction     
			document.getElementById("f"+j).innerText = parseInt(f);
			document.getElementById("ck"+i).disabled = false;
		}
	}
	switch(document.getElementById("mtd0").value)
	{
		case "0": 
			document.getElementById("methodIndex").selectedIndex = 0; 
			break;
		case "1": 
			document.getElementById("methodIndex").selectedIndex = 1; 
			break;
		default: break;
	}
}

function FormatAll()
{
	for(i=0;i<8;i++)
	{
		if(parseFloat(document.getElementById("cap"+i).value)>0)
		{
			document.getElementById("ck"+i).checked = true;
		}
	}
}
function FormatNone()
{
	for(i=0;i<8;i++){
		document.getElementById("ck"+i).checked = false;
	}
}
function showTips(value)
{
	document.getElementById('ctrTip').innerText=value; 
	document.getElementById('light').style.display='inline'; 
	document.getElementById('fade').style.display='inline';
	document.getElementById('forShowTip').style.display='inline';
}
function hideTips()
{
	document.getElementById('light').style.display='none'; 
	document.getElementById('fade').style.display='none';
	document.getElementById('forShowTip').style.display='none';
}
/*download config file*/
function configOut()
{
	//document.fileNameFrame.document.location.reload();
	//var configFile  = document.getElementById("configFileName").value;
	document.configOutForm.submit();
	var href = window.location.href.replace("http://","");
	var pos = href.split("/");
	//var src = "http://"+pos[0]+ '/' + configFile;// configFile;//"/dvr-nvr.cfg";
	var src = "http://"+pos[0] + "/dvr-nvr.cfg";
	path=window.open(src,"hideframe");
}
