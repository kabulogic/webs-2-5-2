/*
 * @Author: Administrator
 * @Date:   2017-07-12 15:12:04
 * @Last Modified by:   Administrator
 * @Last Modified time: 2017-11-14 18:39:27
 */

'use strict';

$(document).ready(function(){
	  validata();
	   $("#myForm").submit(function(){
	   	 
	      var sysLogFoward=document.getElementById("enableSysLogFoward").checked;
		  var fowardIpAddress=document.getElementById("fowardIpAddress").value;
		   
				   /*判断转发地址*/
				   if(sysLogFoward){
					
					   if(document.getElementById("fowardIpAddress").value == ""){
						   document.getElementById("errorInfo").innerHTML="<font color='red' >提示：</font><font color=#005b96><b>请输入日志服务器的ip地址</b></font>";
						   return false;
					   }else if(!check_IP(document.getElementById("fowardIpAddress"))){
						   document.getElementById("errorInfo").innerHTML="<font color='red' >提示：</font><font color=#005b96><b>请输入有效的日志服务器ip地址</b></font>";
						   return false;
					   }
					   var data  = $("#myForm").serializeArray();
					   if (validata() == true ){
					   $.ajax({
						   type:"post",
						   url:"/kinan/EventManage",
						   dataType:"json",
						   data:data,
						   success:function(info){
							   alert(info.msg)
						   }
					   })
					   }
					
				    return false;
	   	 }
	    return false;
				   
	  })
})

		
			

function isFoward(){
	var flag=document.getElementById("enableSysLogFoward").checked;
	if(flag){
		document.getElementById("fowardIpAddress").disabled='';
	}else{
		document.getElementById("fowardIpAddress").value="";
		document.getElementById("fowardIpAddress").disabled='true';
	}
}
function check_IP(obj){
	var ip=obj.value;
	var exp=/^(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$/;
	var flag = ip.match(exp);
	if((flag != undefined && flag!="")|| (ip=="localhost")){
		return true;
	}else{
		return false;
	}
}

