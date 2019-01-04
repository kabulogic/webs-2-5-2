// JavaScript Document
function getComInfo()
{
	try{
		/****************************************** RS232 ***********************************************/
		switch(document.ComForm.COM232_BaudRate.value){
			case '0':
				document.ComForm.RS232BaudRate.selectedIndex = 0;
				break;
			case '1':
				document.ComForm.RS232BaudRate.selectedIndex = 1;
				break;
			case '2':
				document.ComForm.RS232BaudRate.selectedIndex = 2;
				break;
			case '3':
				document.ComForm.RS232BaudRate.selectedIndex = 3;
				break;
			case '4':
				document.ComForm.RS232BaudRate.selectedIndex = 4;
				break;
			case '5':
				document.ComForm.RS232BaudRate.selectedIndex = 5;
				break;
			case '6':
				document.ComForm.RS232BaudRate.selectedIndex = 6;
				break;
			case '7':
				document.ComForm.RS232BaudRate.selectedIndex = 7;
				break;
			case '8':
				document.ComForm.RS232BaudRate.selectedIndex = 8;
				break;
			case '9':
				document.ComForm.RS232BaudRate.selectedIndex = 9;
				break;
			case '10':
				document.ComForm.RS232BaudRate.selectedIndex = 10;
				break;
			case '11':
				document.ComForm.RS232BaudRate.selectedIndex = 11;
				break;
			case '12':
				document.ComForm.RS232BaudRate.selectedIndex = 12;
				break;
			case '13':
				document.ComForm.RS232BaudRate.selectedIndex = 13;
				break;
			case '14':
				document.ComForm.RS232BaudRate.selectedIndex = 14;
				break;
			default:
				document.ComForm.RS232BaudRate.selectedIndex = 14;
				break;
		}
		switch(document.ComForm.COM232_DataBit.value){
			case "5":
				document.ComForm.RS232DataBit.selectedIndex = 0;
				break;
			case "6":
				document.ComForm.RS232DataBit.selectedIndex = 1;
				break;
			case "7":
				document.ComForm.RS232DataBit.selectedIndex = 2;
				break;
			case "8":
				document.ComForm.RS232DataBit.selectedIndex = 3;
				break;
			default:
				document.ComForm.RS232DataBit.selectedIndex = 0;
				break;
		}
		switch(document.ComForm.COM232_StopBit.value){
			case "1":
				document.ComForm.RS232StopBit.selectedIndex = 0;
				break;
			case "2":
				document.ComForm.RS232StopBit.selectedIndex = 1;
				break;
			default:
				document.ComForm.RS232StopBit.selectedIndex = 0;
				break;
		}
		switch(document.ComForm.COM232_Parity.value){
			case "0":
				document.ComForm.RS232ParityCheck.selectedIndex = 0;
				break;
			case "1":
				document.ComForm.RS232ParityCheck.selectedIndex = 1;
				break;
			case "2":
				document.ComForm.RS232ParityCheck.selectedIndex = 2;
				break;
			default:
				document.ComForm.RS232ParityCheck.selectedIndex = 0;
				break;
		}
		switch(document.ComForm.COM232_FlowCtrl.value){
			case "0":
				document.ComForm.RS232StreamControl.selectedIndex = 0;
				break;
			case "1":
				document.ComForm.RS232StreamControl.selectedIndex = 1;
				break;
			case "2":
				document.ComForm.RS232StreamControl.selectedIndex = 2;
				break;
			default:
				document.ComForm.RS232StreamControl.selectedIndex = 0;
				break;
		}
		/****************************************** RS422 channel ***************************************/
		switch(document.ComForm.COM422_BaudRate.value){
			/*case '0':
				document.ComForm.RS422BaudRate.selectedIndex = 0;
				break;
			case '1':
				document.ComForm.RS422BaudRate.selectedIndex = 1;
				break;
			case '2':
				document.ComForm.RS422BaudRate.selectedIndex = 2;
				break;
			case '3':
				document.ComForm.RS422BaudRate.selectedIndex = 3;
				break;
			case '4':
				document.ComForm.RS422BaudRate.selectedIndex = 4;
				break;
			case '5':
				document.ComForm.RS422BaudRate.selectedIndex = 5;
				break;
			case '6':
				document.ComForm.RS422BaudRate.selectedIndex = 6;
				break;*/
			case '7':
				document.ComForm.RS422BaudRate.selectedIndex = 0;
				break;
			case '8':
				document.ComForm.RS422BaudRate.selectedIndex = 1;
				break;
			case '9':
				document.ComForm.RS422BaudRate.selectedIndex = 2;
				break;
			case '10':
				document.ComForm.RS422BaudRate.selectedIndex = 3;
				break;
			case '11':
				document.ComForm.RS422BaudRate.selectedIndex = 4;
				break;
			case '12':
				document.ComForm.RS422BaudRate.selectedIndex = 5;
				break;
			case '13':
				document.ComForm.RS422BaudRate.selectedIndex = 6;
				break;
			case '14':
				document.ComForm.RS422BaudRate.selectedIndex = 7;
				break;
			default:
				document.ComForm.RS422BaudRate.selectedIndex = 0;
				break;
		}
		switch(document.ComForm.COM422_DataBit.value){
			case "5":
				document.ComForm.RS422DataBit.selectedIndex = 0;
				break;
			case "6":
				document.ComForm.RS422DataBit.selectedIndex = 1;
				break;
			case "7":
				document.ComForm.RS422DataBit.selectedIndex = 2;
				break;
			case "8":
				document.ComForm.RS422DataBit.selectedIndex = 3;
				break;
			default:
				document.ComForm.RS422DataBit.selectedIndex = 0;
				break;
		}
		switch(document.ComForm.COM422_StopBit.value){
			case "1":
				document.ComForm.RS422StopBit.selectedIndex = 0;
				break;
			case "2":
				document.ComForm.RS422StopBit.selectedIndex = 1;
				break;
			default:
				document.ComForm.RS422StopBit.selectedIndex = 0;
				break;
		}
		switch(document.ComForm.COM422_Parity.value){
			case "0":
				document.ComForm.RS422ParityCheck.selectedIndex = 0;
				break;
			case "1":
				document.ComForm.RS422ParityCheck.selectedIndex = 1;
				break;
			case "2":
				document.ComForm.RS422ParityCheck.selectedIndex = 2;
				break;
			default:
				document.ComForm.RS422ParityCheck.selectedIndex = 0;
				break;
		}
		switch(document.ComForm.COM422_FlowCtrl.value){
			case "0":
				document.ComForm.RS422StreamControl.selectedIndex = 0;
				break;
			case "1":
				document.ComForm.RS422StreamControl.selectedIndex = 1;
				break;
			case "2":
				document.ComForm.RS422StreamControl.selectedIndex = 2;
				break;
			default:
				document.ComForm.RS422StreamControl.selectedIndex = 0;
				break;
		}
		switch(document.ComForm.COM422_Protocol.value){
			case "0":
				document.ComForm.RS422Protocol.selectedIndex = 0;
				break;
			case "3":
				document.ComForm.RS422Protocol.selectedIndex = 1;
				break;
			case "4":
				document.ComForm.RS422Protocol.selectedIndex = 2;
				break;
			default:
				document.ComForm.RS422Protocol.selectedIndex = 0;
				break;
		}
		document.ComForm.RS422DecodeAddress.value = document.ComForm.COM422_Addr.value;
	}catch(e){}
}

function GetComCh()
{
	if(readcookie("RS422Ch")){
		ch = parseInt(getCookie("RS422Ch"));
		document.forms[0].RS422Channel.selectedIndex = ch;
	}
	else{
		document.forms[0].RS422Channel.selectedIndex = 0;	
	}
}

function setComCh()
{
	addcookie("RS422Ch="+document.forms[0].RS422Channel.selectedIndex);
	parent.rightFrame.document.location.reload();
}