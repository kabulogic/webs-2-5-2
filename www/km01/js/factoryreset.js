/*
* @Author: Administrator
* @Date:   2017-07-12 16:45:22
* @Last Modified by:   Administrator
* @Last Modified time: 2017-11-14 19:12:12
*/

'use strict';
validata();
function check(){

    if(confirm("是否要立即恢复出厂设置?")) {

	$("#myForm").submit(function(){
		var data = $("#myForm").serializeArray();
		console.log(data);
     if (validata() == true ){
		$.ajax({
		    type:"post",
		    url:"/kinan/SystemCtrl",
		    dataType:"json",
		    data:data,
		    success:function(){
		         document.getElementById("errorInfo").innerHTML="<font color='red'>正在恢复出厂设置，稍后请重新登录.....</font>"   
		    }
		})
  }
		return false;
	})
	return true;
    }else{
    	return false;
    }
}