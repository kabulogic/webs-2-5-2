/*
* @Author: Administrator
* @Date:   2017-07-12 16:41:12
* @Last Modified by:   Administrator
* @Last Modified time: 2017-11-14 19:07:46
*/

'use strict';
 validata();
function check(){

    if(confirm("是否要立即重启设备?")) {

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
		         document.getElementById("errorInfo").innerHTML="<font color='red'>正在重启中,稍后请重新登录.....</font>"   
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


