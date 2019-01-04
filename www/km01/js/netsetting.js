/*
* @Author: Administrator
* @Date:   2017-07-12 14:58:34
* @Last Modified by:   Administrator
* @Last Modified time: 2017-11-14 18:41:06
*/

'use strict';
$(document).ready(function() {
    if (validata() == true ){
	$.ajax({
		type:"get",
		url:"/kinan/NetDefaultInfo",
		dataType:"json",
		success:function(info){
			
			var htmls = template("netS",info.data)
				$(".usergroup").html(htmls)
		}

	})
}
});
function  optionChange(){
	if($("#select_id").val()==1){
		var checkValue = $("#select_id").val();
    if (validata() == true ){
    	$.ajax({
			type:"get",
       	 	url:"/kinan/NetDefaultInfo?network="+checkValue,
        	dataType:"json",
        	success:function(info){
        		var htmls = template("netS",info.data)
				$(".usergroup").html(htmls)
       		}
    	})
    }
    }
    if($("#select_id").val()==0){
		var checkValue = $("#select_id").val();
    	//alert(22);
       if (validata() == true ){
    	$.ajax({
			type:"get",
       	 	url:"/kinan/NetDefaultInfo?network="+checkValue,
        	dataType:"json",
        	success:function(info){
        		var htmls = template("netS",info.data)
				$(".usergroup").html(htmls)
       		}
    	})
    }
   }
}

//验证ipv4地址
function check_IP(obj){
   var ip=obj.value;
   var exp=/^(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$/;
   var flag = ip.match(exp);
   var errorIP=document.getElementById("errorInfo");
      if(flag != undefined && flag!=null && flag!=""){
         return true;
      }else{
        errorIP.innerHTML="<font color='red'>提示：</font><font color=#005b96><b>请输入正确的地址格式</b></font></font>";
        return false;
      }
}
//验证子网掩码
  function subnet(){
      var subnetmask=document.getElementById("subnetmask").value;
      var deviceIpv4=document.getElementById("deviceIpv4").value;
      var subnet;   
      if(subnetmask==null||subnetmask==""){
             var ipSplit=deviceIpv4.split(".");
             for(var i=0;i<ipSplit.length;i++){
                     var sum=ipSplit[0];
                     if(1<=sum&&sum<=127){
                       subnet="255.0.0.0";
                     }else if(128<=sum&&sum<=191){
                       subnet="255.255.0.0";
                    }else if(192<=sum&&sum<=255){
                      subnet="255.255.255.0";
                    }   
              }
            document.getElementById("subnetmask").value=subnet;
          }else{
            return true;
          }      
   }
function check_GW(ipvalue){
   var tag=false;
   var exp=/^(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$/;
   var flag=ipvalue.match(exp);
   var errorGW=document.getElementById("errorInfo");
   if(/::/.test(ipvalue)?/^([\da-f]{1,4}(:|::)){1,6}[\da-f]{1,4}$/i.test(ipvalue):/^([\da-f]{1,4}:){7}[\da-f]{1,4}$/i.test(ipvalue) && ((ipvalue.split(':')).length<=8)){
          tag = true;
      }else{
        if(flag !=null && flag!=undefined && flag!=""){
          tag = true;
        }
        else{
          tag = false;
        }
      }
        if(tag){
        
      }else{
        errorGW.innerHTML="<font color='red'>提示：</font><font color=#005b96><b>请输入正确的网关地址</b></font>";
      }
      }
 function checkForm(){
        
          $("#myForm").submit(function(){
              var errorForm=document.getElementById("errorInfo");
          var exp=/^(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$/;
//          var autoConfig=document.getElementById("autoConfigIp").value;
          var autoConfig=0;
          var Ipv4=document.getElementById("deviceIpv4").value;
          var isIpv4=Ipv4.match(exp);
          if(autoConfig==0 && (!isIpv4)){
            errorForm.innerHTML="<font color='red'>提示：</font><font color=#005b96><b>请输入有效的ipv4地址</b></font>";
            return false;
          }
          var subnetmask=document.getElementById("subnetmask").value;
          var isSubnetmask=subnetmask.match(exp);
          if(autoConfig==0 && subnetmask!="" && (!isSubnetmask)){
            errorForm.innerHTML="<font color='red'>提示：</font><font color=#005b96><b>请输入有效的子网掩码</b></font>";
            return false;
          }
          var defaultGateway=document.getElementById("defaultGateway").value;
          var isGateway=defaultGateway.match(exp);
          if(autoConfig==0 && (!isGateway)){
            errorForm.innerHTML="<font color='red'>提示：</font><font color=#005b96><b>请输入有效的默认网关地址</b></font>";
            return false;
          }
              var data = $("#myForm").serializeArray();
         //    alert(33);
         if (validata() == true ){
              $.ajax({
                type:"post",
                url:"/kinan/NetSetting",
                dataType:"json",
                data:data,
                success:function(info){
					if(info.status == "true")
					{
                 		alert(info.msg);
				 		window.top.location.href = "index.html";
					}
					if(info.status == "false")
					{
						alert(info.msg);
						window.location.href = "netsetting.html";
					}
                }
				
              })
            }
				return false;
          })
          
   }

