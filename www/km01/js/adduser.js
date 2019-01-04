$(document).ready(function (){
  if (validata() == true ){
	 $.ajax({
		type:"get",
		url:"/kinan/AddUserInfo",
		dataType:"json",
		success:function(info){
			var htmls = template("groupInfo",info)
			$("#allgroup").html(htmls)
		}
	})
	}
	$("#user-form").submit(function(){
		var userName = trim($("#userName").val());
		var userErrInfo =$("#errorInfo").html("");
		var reg =/\w/
		if(userName==""){
			$("#errorInfo").html("<font color='red'>提示：</font><font color='#005b96'><b>请输入用户名</b></font>");
			return false;
		}else if(!reg.test(userName)){
			$("#errorInfo").html("<font color='red'>提示：</font><font color='#005b96'><b>用户名由大小写英文字母、数字、任意字符组成</b></font>");
					return false;
		}else if(getLength(userName)<6||getLength(userName)>20){
			$("#errorInfo").html("<font color='red'>提示：</font><font color='#005b96'><b>用户名的长度为6-20个字节</b></font>");
			return false;
		}else{
			var flag_firstpassword = firstpassword_check();
			if(!flag_firstpassword){
				return false;
			}
			var flag_repassword=rpass_check();//重复密码
			if(!flag_repassword){
				return false;
			}
			if(flag_firstpassword&&flag_repassword){
				var firstValue = $("#first_password").val();
				var key = $("#key").val();
				var fResult =strEnc(firstValue,key);
				$("#first_password").prop("value",fResult);
				var password = $("#password").val();
				var pResult = strEnc(password,key);
				$("#password").prop("value",pResult);
				var data = $("#user-form").serializeArray();
				if (validata() == true ){
				$.ajax({
					type:"post",
					url:"/kinan/AddUser",
					//dataType:"json",
					data:data,
					success:function(data){
						window.location.href="/userlist.html";
					}
				})
			}
			}
			return false
		}
	})
})

//去空格
function trim(str){ //删除左右两端的空格
  return str.replace(/(^\s*)|(\s*$)/g, "");
}

//计算字符串的字节数
function getLength(val){
	var length = 0
		for (var i = 0; i < val.length; i++) {
			if (val.charCodeAt(i)>255) {
				length = length + 2;
			}else {
				length++;
			}   
		}   
	return length;
}
//验证密码是否输入空格
function banInputSapce(e){
	var keynum;
	if(window.event) // IE
	{
		keynum = e.keyCode
	}
	else if(e.which) // Netscape/Firefox/Opera
	{
		keynum = e.which
	}
	if(keynum ==32){
		document.getElementById("errorInfo").innerHTML="<font color='red'>不能输入空格</font>";
		//document.getElementById("result").value="false";
		return false;
	}
	return true;
} 

function firstpassword_check(){
	// alert(0)
	var  firstValue = $("#first_password").val();
	//var regNull=/(^\s*)|(\s*$)/g;
	//alert(firstValue);
	var errorInfo= $("#errorInfo"); 
	errorInfo.html("");
	if(firstValue==""){
		errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>请输入新密码</b></font><br/><br/>");  
		return false;
	}else if(firstValue.length<8||firstValue.length>16){
		errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>新密码由8到16位组成</b></font><br/><br/>");
		return false;
	}
	return true; 
}
//重复密码判断
function rpass_check(){
	var  firstValue = $("#first_password").val();
	var  password = $("#password").val();
	var regNull=/(^\s*)|(\s*$)/g;
	var errorInfo= $("#errorInfo"); 
	errorInfo.html("");
	if(password==""){
		errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>请输入设置密码</b></font><br/><br/>");
		return false;
	}else if(password.length<8||password.length>16){
		errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>重复密码由8到16位组成</b></font><br/><br/>");
		return false;
	}else if(firstValue!=password){
		errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>两次密码不一致</b></font><br/><br/>");
		return false;
	}else{
		//原密码写入历史密码
		$("#historyPassword").prop("value",password)
			return true;
	}

}

function goback(){
        window.location.href="/adduser.html";
}

