/*
* @Author: Administrator
* @Date:   2017-07-12 16:50:20
* @Last Modified by:   Administrator
* @Last Modified time: 2017-11-14 18:42:52
*/

'use strict';
  validata();
function checkFile()
{
    var fileUrl = document.getElementById("fileUrl").value;
    console.log(fileUrl);
    var reg = fileUrl.substr(fileUrl.length-23);
    console.log(reg);
    var exp = /^kvm-\d{8}-\d{6}.kfu$/;
    var errorInfo = document.getElementById("errorInfo");
    if(fileUrl==null || fileUrl==""){
        errorInfo.innerHTML="请先选择需要上传的文件";
        return false;
    }
  if(!exp.test(reg)){
        errorInfo.innerHTML="请选择正确的升级文件";
		
        return false;
    }
	var files = $("#fileUrl").prop("files");
	console.log(files)
//	if(files>10){

  //    return false;
//	}
    errorInfo.innerHTML="正在上传请稍候...";
    //文件的大小
 
    //获取文件列表
    //var reader = new FileReader();
    //新建一个FileReader
    if (validata() == true ){
	$('#myForm').ajaxForm({ 
	               url:"/kinan/RemoteUpgrade",
				   //dataType: 'json',	
				  success: processJson	
	});  
}
	function processJson(info){ 
		var obj = JSON.parse(info);
		console.log(typeof(obj));
		//alert(obj.status); 
		if(obj.status=="true"){
			var errorInfo = document.getElementById("errorInfo");
			errorInfo.innerHTML="上传成功";
			alert("是否升级")
				
			//window.location.reload()//刷新当前页面.
			}
	}	
          
}




