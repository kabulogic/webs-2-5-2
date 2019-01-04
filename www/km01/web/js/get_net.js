// JavaScript Document
function getNetCfg()
{
	try{
	getCardInfo();
	document.NetForm.NFSIP.value = document.NetForm.Net_NfsHost.value;
	document.NetForm.NFSPath.value = document.NetForm.Net_NfsPath.value;
	document.NetForm.HttpPt.value = document.NetForm.Net_HTTPPort.value;
	document.NetForm.SnmpPt.value = document.NetForm.Net_SNMPPort.value;
	document.NetForm.RmIP.value = document.NetForm.Net_RHostIP.value;
	document.NetForm.RmPt.value = document.NetForm.Net_RHostPort.value;
	}catch(e){}
}

function getCardInfo()
{
	try{
	var no = document.NetForm.NetworkCard.selectedIndex;
	document.NetForm.backEth.value = no;
	initPara(no);
	onType();
	}catch(e){}
}

function initPara(no)
{
	document.all.CardMac.innerText = document.getElementById("Net_Mac"+no).value;
	switch(document.getElementById("Net_Type"+no).value){
		case "0":
			document.NetForm.NetType.selectedIndex = 0;
			break;
		case "16":
			document.NetForm.NetType.selectedIndex = 1;
			break;
		case "32":
			document.NetForm.NetType.selectedIndex = 2;
			break;
		default:
			break;
	}
	if(document.getElementById("Net_AutoD"+no).value == "1"){
		document.NetForm.AutoDNS.checked = true;
	}
	else{
		document.NetForm.AutoDNS.checked = false;
	}
	document.NetForm.DNSIP.value = document.getElementById("Net_DnsIP"+no).value;

	document.NetForm.NetPara1.value = document.getElementById("Net_IP"+no).value;
	document.NetForm.NetPara2.value = document.getElementById("Net_Port"+no).value;
	document.NetForm.NetPara3.value = document.getElementById("Net_Mask"+no).value;
	document.NetForm.NetPara4.value = document.getElementById("Net_Gw"+no).value;
	document.NetForm.defaultPort.value = document.getElementById("Net_defaultPort"+no).value;

	//P3oE
	document.all.P3oEAddr.innerText = document.getElementById("Net_P3IP"+no).value;
	document.NetForm.PPPoEUn.value = document.getElementById("Net_P3Un"+no).value;
	document.NetForm.PPPoEPw.value = document.getElementById("Net_P3Pw"+no).value;
	document.NetForm.ConfPw.value = document.getElementById("Net_P3Pw"+no).value;
}

function onDNS()
{
	if(document.NetForm.AutoDNS.checked){
		document.NetForm.DNSIP.disabled = true;
	}
	else{
		document.NetForm.DNSIP.disabled = false;
	}
}


function DHCP(bool)
{
	for(i=1;i<=4;i++){
		document.getElementById("NetPara"+i).disabled = bool;
	}
	document.getElementById("NetPara2").disabled = true;
}

function hasChange(no)
{
	var bool = false;
	if(document.NetForm.NetType.selectedIndex==0){
		bool |= compare(document.NetForm.NetPara1,document.getElementById("Net_IP"+no));
		bool |= compare(document.NetForm.NetPara2,document.getElementById("Net_Port"+no));
		bool |= compare(document.NetForm.NetPara3,document.getElementById("Net_Mask"+no));
		bool |= compare(document.NetForm.NetPara4,document.getElementById("Net_Gw"+no));
		bool |= compare(document.NetForm.defaultPort,document.getElementById("Net_defaultPort"+no));
	}
	if(!document.NetForm.AutoDNS.checked){
		bool |= compare(document.NetForm.DNSIP, document.getElementById("Net_DnsIP"+no));
	}
	if(document.NetForm.NetType.selectedIndex==2){
		bool |= compare(document.NetForm.PPPoEUn, document.getElementById("Net_P3Un"+no));
		bool |= compare(document.NetForm.PPPoEPw, document.getElementById("Net_P3Pw"+no));
	}
	return bool;
}

function saveChange()
{
	var no = document.NetForm.backEth.value;
	var bool = false;
	bool = compare(document.NetForm.NetPara1,document.getElementById("Net_IP"+no));
	if(bool) document.getElementById("IPChange").value = "1";
	
	if(hasChange(no)){
		document.getElementById("Net_IP"+no).value = document.NetForm.NetPara1.value;
		document.getElementById("Net_Port"+no).value = document.NetForm.NetPara2.value;
		document.getElementById("Net_Mask"+no).value = document.NetForm.NetPara3.value;
		document.getElementById("Net_Gw"+no).value = document.NetForm.NetPara4.value;
		document.getElementById("Net_DnsIP"+no).value = document.NetForm.DNSIP.value;
		document.getElementById("Net_P3Un"+no).value = document.NetForm.PPPoEUn.value;
		document.getElementById("Net_P3Pw"+no).value = document.NetForm.PPPoEPw.value;
		document.getElementById("Net_defaultPort"+no).value = document.NetForm.defaultPort.value;
	}
	var has_dhcp=0;
	switch(document.NetForm.NetType.selectedIndex){
		case 0:
			document.getElementById("Net_Type"+no).value = 0x00;
			break;
		case 1:
			if(document.getElementById("Net_Type"+no).value != 0x10) has_dhcp=1;
			document.getElementById("Net_Type"+no).value = 0x10;
			break;
		case 2:
			document.getElementById("Net_Type"+no).value = 0x20;
			break;
	}
	document.getElementById("HasDHCP"+no).value = has_dhcp;
	if(document.NetForm.AutoDNS.checked){
		document.getElementById("Net_AutoD"+no).value = "1";
	}
	else{
		document.getElementById("Net_AutoD"+no).value = "0";
	}
}

function checkAllIP()
{
	if((!assertIP(document.getElementById("NetPara1"),'IP address'))
	  || (!assertIP(document.getElementById("NetPara3"),'Subnet Mask') )
	  || (!assertIP(document.getElementById("NetPara4"),'Gateway'))
	  || (!assertIP(document.getElementById("DNSIP"),'DNS')) 
	  || (!assertIP(document.getElementById("RmIP"),'Alarm Center IP')))
	{
		return false;
	}
	return true;
}

function setNetCfg()
{
	if( (!checkAllIP()) || (!checkPort(document.getElementById("defaultPort"),1024)) 
        || (!checkPort(document.getElementById("HttpPt"),1))) return;
	var err = getCookie("seterror=")
	if(err == 1) return;
	if(ConfirmPw()){
		saveChange();
		alertDHCP();
		document.NetForm.submit();
	}
}

function onType()
{
	switch(document.NetForm.NetType.selectedIndex){
		case 0:
			DHCP(false);
			document.all.staticIP.style.display = "";	
			document.all.P3oE.style.display = "none";
			document.NetForm.AutoDNS.checked = false;
			document.NetForm.AutoDNS.disabled = true;
			document.NetForm.DNSIP.disabled = false;
			break;
		case 1:
			DHCP(true);
			document.all.staticIP.style.display = "";	
			document.all.P3oE.style.display = "none";
			document.NetForm.AutoDNS.disabled = false;
			if(document.getElementById("Net_AutoD"+document.NetForm.NetType.selectedIndex).value == "1")
			{
				document.NetForm.AutoDNS.checked = true;
				document.NetForm.DNSIP.disabled = true;
				
			}
			else{
				document.NetForm.AutoDNS.checked = false;
				document.NetForm.DNSIP.disabled = false;
			}
			break;
		case 2:
			DHCP(false);
			document.all.staticIP.style.display = "none";	
			document.all.P3oE.style.display = "";	
			break;
		default:break;
	}	
}