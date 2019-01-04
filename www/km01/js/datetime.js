/*
* @Author: Administrator
* @Date:   2017-07-12 15:04:39
* @Last Modified by:   Administrator
* @Last Modified time: 2017-11-14 18:22:21
*/

'use strict';
function userSet(){
  document.getElementById("hostTimeServer").disabled='true';
  document.getElementById("currentDate").disabled='';
  document.getElementById("currentTime").disabled='';
}
function useNtp(){
  document.getElementById("hostTimeServer").disabled='';
  document.getElementById("currentDate").disabled='true';
  document.getElementById("currentTime").disabled='true';
}
 
$(document).ready(function(){
if (validata() == true ){
$.ajax({
    type:"get",
   url:"/kinan/DateTimeInfo",
   dataType:"json",
   success:function(info){
var htmls = template("dataInfo",info.data);
$(".firstpage").html(htmls);
      
   //if($("#userSetTime").val()==0){
	   //alert(12)
	 //  $("input.timeR").disabled=""
	  // $("input.timeS").attr("disabled","disabled")
	// }else{
		//$("input.timeS").disabled=""
	 //  $("input.timeR").attr("disabled","disabled")
	 //}
	 
	 var d = new Date();
   console.log(d)
	 // var  nowTime = d.toISOString().slice(0,10)
  //  console.log(nowTime)
  var year = d.getFullYear();
   if(year<10){
    year ="0"+year;
   }
   var month = d.getMonth()+1;
   if(month<10){
    month = "0"+month;
   }
   var day = d.getDate()
   if(day<10){
     day ="0"+day;
   }
   var  nowTime = year +"-"+month+"-"+day;
// if(d.getHours()<10&&d.getMinutes()<10){
//   var nowTimeH = "0"+d.getHours()+":"+"0"+d.getMinutes() 
// }else if(d.getHours()>=10&&d.getMinutes()<10){
//   var nowTimeH=d.getHours() + ':' +"0"+ d.getMinutes();
// }else if(d.getHours()<10&&d.getMinutes()>=10){
//    var nowTimeH = "0"+d.getHours()+":"+d.getMinutes();
// }else{
//   var nowTimeH=d.getHours() + ':' + d.getMinutes() 
// }
	 var hours = d.getHours();
   if(hours<10){
    hours="0"+hours;
   }
   var minutes = d.getMinutes();
   if(minutes<10){
    minutes = "0"+minutes;
   }
   var nowTimeH  = hours+":"+minutes
	 $("#currentDate").prop("value",nowTime)
	 $("#currentTime").prop("value",nowTimeH)
   }
 })
}   
})

function setDate(){
  $("#myForm").submit(function(){
  var exp=/^(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$/;
  var currentDate = document.getElementById("currentDate").value;
  var currentTime = document.getElementById("currentTime").value;
  var hostTimeServer = document.getElementById("hostTimeServer").value;
  var useNtpServer=document.getElementById("useNtpServer").checked;
  var userSetTime=document.getElementById("userSetTime").checked;
  var error=document.getElementById("errorInfo");
  if(useNtpServer){
    var ishostTimeServer=hostTimeServer.match(exp);
    if(hostTimeServer==""){
      error.innerHTML="<font color='red' >提示：</font><font color=#005b96><b>请输入时间服务器</b></font>";
      return false;
    }
    else if(!ishostTimeServer){
      error.innerHTML="<font color='red' >提示：</font><font color=#005b96><b>请输入有效的时间服务器IP</b></font>";
      return false;
    }
    
  }else if(userSetTime){
    if(currentDate==""){
      error.innerHTML="<font color='red' >提示：</font><font color=#005b96><b>请设置日期</b></font>";
      return false;
    }
    else if(currentTime==""){
      error.innerHTML="<font color='red' >提示：</font><font color=#005b96><b>请设置时间</b></font>";
      return false;
    }
    
  }else{
    error.innerHTML="<font color='red' >提示：</font><font color=#005b96><b>请选择设置时间方式</b></font>";
    return false;
  }
   
   var data = $("#myForm").serializeArray();
   console.log(data);
   if (validate() == true ){
  $.ajax({
	async:"false",
   type:"post",
   url:"/kinan/DateTime",
   dataType:"json",
   data:data,
   success:function(info){
      alert(info.msg)
 //document.getElementById("errorInfo").innerHTML="<font color='red' >提示：</font><font color=#005b96><b>"+info.msg+"</b></font>";
window.location.href="datetime.html";

   }
 })
}
   return false;

})


}

  


