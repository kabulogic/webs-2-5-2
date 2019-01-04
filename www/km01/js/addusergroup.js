/*
* @Author: Administrator
* @Date:   2017-06-19 10:55:29
* @Last Modified by:   Administrator
* @Last Modified time: 2017-11-14 18:52:33
*/

'use strict';
  function sysView(){
    $("#sysPri").show();
  }
  function disSysView(){
    $("#sysPri").hide();
  } 
  function view(){
    $("#portAuth").show();
    $("#allPortAuth").show();
  }
  function disView(){
    $("#portAuth").hide();
    $("#allPortAuth").hide()
  }
  //去空格
function trim(str){ //删除左右两端的空格
  return str.replace(/(^\s*)|(\s*$)/g, "");
}

//计算字符串的字节数
function getBytes(val) {
  var totalLength = 0;     
  var charCode;
  for (var i = 0; i < val.length; i++) {
    charCode = val.charCodeAt(i); 
    if((charCode<=0x9FA5) && (charCode>=0x4E00)){
      totalLength+=2;
    }else{
      totalLength+=1;
    }
  } 
  return totalLength;
}  
      
function groupName_check(){
  var userGroupName=document.getElementById("userGroupName");
  var errorName= document.getElementById("errorInfo");
  errorName.innerHTML="";
  var reg =/\w/
  var nameValue=trim(userGroupName.value);
  var flag=getBytes(nameValue);//计算字符数  
  if(nameValue==""){
    errorName.innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>请输入用户组名称</b></font>";
	return false;
  }else if(!reg.test(nameValue)){
  	 errorName.innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>用户名由大小写英文字母、数字、任意字符组成</b></font>";
			  return false;
		  }
  else if(flag>64){
	  errorName.innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>用户组名不超过64个字节</b></font>";
	  return false;
  }else{
	  var userGros=document.getElementById("userGroNames").value;
	  var strs= new Array(); //定义一数组 
	  strs=userGros.split(","); //字符分割 
	  for(var i=0;i<strs.length;i++){
		  if(nameValue==strs[i]){
			  errorName.innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>用户组已存在</b></font>";
			  return false;
		  }
	  }
  }
  return true;
}

//设置全选
function setAll(name,select_id,value){
	var accesses=document.getElementsByName(name);
	var flag=document.getElementById(select_id).checked;  

	if(flag){
		for(var i=0;i<accesses.length;i++){
			for(var j=0;j<accesses[i].length;j++){
				if(accesses[i][j].value==value){
					accesses[i].options[j].selected=true;
					accesses[i].value=value;//赋值
				}
			}

		}
	}
}

//提交验证
function check_form() {
	var form=document.getElementById("myForm");
	var flag= groupName_check();
	if(!flag){
		return false;
	}
	var errorInfo=document.getElementById("errorInfo");
	var accesses=document.getElementsByName("accesses");
	var vm_accesses=document.getElementsByName("vm_accesses");
	for(var i=0;i<accesses.length;i++){
		if(accesses[i].value==0 && vm_accesses[i].value!=0 ){
			errorInfo.innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>端口访问为“拒绝”时，虚拟媒体只能为“拒绝”。</b></font>";     
			return false;
		}else if(accesses[i].value==1 && vm_accesses[i].value!=0 ){
			errorInfo.innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>端口访问为“查看”时，虚拟媒体只能为“拒绝”。</b></font>";      
			return false;
		}
	}
	var setSecurityMode = document.getElementById("setSecurityMode").value;
	var desKey = document.getElementById("desKey").value;
	var aes256Key = document.getElementById("aes256Key").value;
	var aes128Key = document.getElementById("aes128Key").value;
	var userGroupName = document.getElementById("userGroupName").value;
	if(setSecurityMode==0){//des加密
		//alert(00000);
		document.getElementById("userGroupName").value = strEnc(userGroupName,desKey,"","");
		//alert(strEnc(userGroupName,desKey,"",""));
	}
	if(setSecurityMode==1){//aes128加密
		//alert(11111);
		// document.getElementById("userGroupName").value = aes_encrypt(str2HexByte(aes128Key),str2HexByte(window.encodeURI(window.encodeURI(userGroupName))));
		//alert( aes_encrypt(str2HexByte(aes128Key),str2HexByte(window.encodeURI(userGroupName))));
	}
	if(setSecurityMode==2){//aes256加密
		//alert(222222);
		//document.getElementById("userGroupName").value = aes_encrypt(str2HexByte(aes256Key),str2HexByte(userGroupName));
		// alert(userGroupName);
	}
	document.getElementById("conf").disabled=true;
	//   return true;
	var data = $("#myForm").serializeArray();
  if (validata() == true ){
	$.ajax({
		type:"post",
		url:"/kinan/AddUserGroup",
		//    dataType:"json",
		data:data,
		success:function(info){
		//	alert("请求成功");
		//	console.log(typeof(info));
			var obj = eval('(' + info + ')');
			 if(obj.status == "true")
			   {
			   window.location.href="/usergrouplist.html";
			   }
		}
	})
}
	return false
}
function goback(){
	window.location.href="/usergrouplist.html";
}
