// JavaScript Document
var bCopy = false;
function setComCfg()
{
	var flag = document.ComForm.flag.value;
	//COM 232 info change
	if( (compare(document.ComForm.RS232BaudRate,document.ComForm.COM232_BaudRate)) || (compare(document.ComForm.RS232DataBit,document.ComForm.COM232_DataBit)) || (compare(document.ComForm.RS232StopBit,document.ComForm.COM232_StopBit)) || (compare(document.ComForm.RS232ParityCheck,document.ComForm.COM232_Parity)) || (compare(document.ComForm.RS232StreamControl,document.ComForm.COM232_FlowCtrl)) ){  
		flag |= 0x0001;
	}
	//COM 422 info change
	if( Com422HasChange() ){
		flag |= 0x0002;
	}
	if(bCopy)
	{
		var source_ch = parseInt(document.ComForm.RS422Channel.value);
		var des_ch = parseInt(document.ComForm.RS422CopyToChannel.value);
		if(source_ch != des_ch){
			flag |= 0x0004;
		}	
	}
	document.ComForm.flag.value = flag;
	comFormSubmit();
}

function OnCopy422()
{
	bCopy = true;
}

function Com422HasChange()
{
	if( (compare(document.ComForm.RS422BaudRate,document.getElementById("COM422_BaudRate"))) || (compare(document.ComForm.RS422DataBit,document.getElementById("COM422_DataBit"))) || (compare(document.ComForm.RS422StopBit,document.getElementById("COM422_StopBit"))) || (compare(document.ComForm.RS422ParityCheck,document.getElementById("COM422_Parity"))) || (compare(document.ComForm.RS422StreamControl,document.getElementById("COM422_FlowCtrl"))) || (compare(document.ComForm.RS422Protocol,document.getElementById("COM422_Protocol"))) || (compare(document.ComForm.RS422DecodeAddress,document.getElementById("COM422_Addr"))) ){
		return true;
	}
	return false;
}

function comFormSubmit()
{
	flag = document.ComForm.flag.value;
	if(flag != 0){
		document.ComForm.submit();
		document.ComForm.flag.value = 0;
		bCopy = false;
	}
}