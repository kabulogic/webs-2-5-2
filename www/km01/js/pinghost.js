/*
* @Author: Administrator
* @Date:   2017-07-12 16:36:52
* @Last Modified by:   Administrator
* @Last Modified time: 2017-11-14 19:11:23
*/

'use strict';
/*
function check_form(){
  var ipValue=$("#ip").val();
  
   console.log(ip)
  var ipAddressV = $("#ipAddress").prop("value",ipValue);
   console.log(ipAddressV);
   var result = $("#result");
   result.html("正在 ping "+ipValue+"...");
  $("#myForm").submit(function(){
    var data = $("#myForm").serializeArray();
       $.ajax({
		 async:false,
         type:"post",
         url:"/cgi-bin/ping.cgi",
         dataType:"json",
         data:data,
         success:function(info){
             
		   result.html(info.data);
		
         	}
      })
       return false;
  })
 
}
*/
validata();
	function check_form(){
		
	  	var ipValue=$("#ip").val();
	   	console.log(ipValue);
	  	var errorName=document.getElementById("errorInfo");
	 	$("#ipAddress").prop("value",ipValue);
	   	var result =$("#result");
	   	result.html("正在 ping "+ipValue+"...");
	   		
		$("#myForm").ajaxForm({
			  success:processJson
			 })
			function processJson(info){
			 // alert(22)
			  	var obj = JSON.parse(info);
			  	console.log(obj.data)
			  result.html(obj.data);
			}
		
	}


