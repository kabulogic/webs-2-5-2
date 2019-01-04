/*
* @Author: Administrator
* @Date:   2017-07-12 15:53:22
* @Last Modified by:   Administrator
* @Last Modified time: 2017-11-14 18:47:31
*/
'use strict';
 $(document).ready(function(){
   if (validata() == true ){
 $.ajax({
    async:false,
    type:"get",
	  url:"/kinan/ConfirmSetInfo",
	  dataType:"json",
	 success:function(info){
	   var htmls = template("confirmIn",info.data);
      $(".firstpage_1").html(htmls);
	 	}
 	})
}
 
  if($("#checkType").val()==1){
    $('input.radius').attr("disabled","disabled");
  }else if($("#checkType").val()==2){
    $('input.ldap').attr("disabled","disabled");
    $('input.kkkke').attr("disabled","disabled");
  }else{
    $('input:text').attr("disabled","disabled");
    $('input:password').attr("disabled","disabled");
  }
  
  $("#local_verification").click(function(){
    $('input:text').attr("disabled","disabled");
    $('input:password').attr("disabled","disabled");
  });
  $("#LDAP_verification").click(function(){
    $('input.ldap').removeAttr("disabled");
    $('input.kkkke').removeAttr("disabled");
    $('input.radius').attr("disabled","disabled");
  });
  $("#RADIUS_verification").click(function(){
    $('input.radius').removeAttr("disabled");
    $('input.ldap').attr("disabled","disabled");
    $('input.kkkke').attr("disabled","disabled");
  });
 })
//计算字符串的字节数
function getLenth(val){
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

//验证ipv4地址 检查LDAP服务器地址
function check_IP(){
  var ip=document.getElementById("primaryLDAPServer").value;

  var exp=/^(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$/;
  var flag = ip.match(exp);
  if(ip=="localhost" || (flag != undefined && flag!=null && flag!="")){
    document.getElementById("errorInfo").innerHTML="";
    return true;
  }else if(ip==""){
    document.getElementById("errorInfo").innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>主LDAP服务器的ip不能为空</b></font><br/>";
    return false;
  }else{
    document.getElementById("errorInfo").innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>请输入有效的主LDAP服务器ip地址</b></font><br/>";
    return false;
  }
}

//检查测试登录名
function check_TestName(){
  var obj=document.getElementById("testLDAPName").value;
  var test = /^[a-zA-Z0-9_]{4,16}$/; 
  if(obj==""){
    document.getElementById("errorInfo").innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>请输入测试名</b></font><br/>";
    return false;
  }else{
    if(test.exec(obj)){
      document.getElementById("errorInfo").innerHTML="<font color='red'></font>";
      return true;
    }else{
      document.getElementById("errorInfo").innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>测试名要求由4-16位英文字母、数字和下划线组成</b></font><br/>";
      return false;
    }
  }
  
}
//检查测试密码
function check_TestPwd(){
  var obj=document.getElementById("testLDAPPwd").value;
  var test = /^[a-zA-Z0-9_@&#!$.]{6,16}$/;
  if(obj==""){
    document.getElementById("errorInfo").innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>测试密码不能为空</b></font><br/>";
    return false;
  }else{
//    if(test.exec(obj)){
//      document.getElementById("errorTestPwd").innerHTML="<font color='red'></font>";
//      return true;
//    }else{
//      document.getElementById("errorTestPwd").innerHTML="<font color='red'>密码要求由5-20位英文字母、数字和下划线组成</font>";
//      return false;
//    }
    document.getElementById("errorInfo").innerHTML="<font color='red'></font>";
    return true;
  }
}

function check_subPwd(){
  var managerDn=document.getElementById("ldapManagerDn").value;
  var pwd=document.getElementById("ldapManagerPwd").value;
  var subpwd=document.getElementById("ldapManaherPwdTo").value;
  if(managerDn==""){
    document.getElementById("errorInfo").innerHTML="<font color='red'></font>"; 
    return true;
  }else{
    if(subpwd!=""){
      if(pwd==subpwd){
        document.getElementById("errorInfo").innerHTML="<font color='red'></font>";
        return true;
      }else{
        document.getElementById("ldapManaherPwdTo").value="";
        document.getElementById("errorInfo").innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>两次密码不一致</b></font><br/>";
        return false;
      }
    }else{
      document.getElementById("errorInfo").innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>确认密码不能为空</b></font><br/>";
      return false;
    }
  }
}
 // 验 证用 户 搜 索 DN：
function check_search(){
  var searchDn=document.getElementById("searchDn").value;
  var Regx=/^[\u0391-\uFFE5]+$/ ;
  if(searchDn==null || searchDn==""){
    document.getElementById("errorInfo").innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>用户搜索DN不允许为空</b></font><br/>";
    return false;
  }else{
    if(getLenth(searchDn)>64){
      document.getElementById("errorInfo").innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>用户搜索DN不能超过64个字节</b></font><br/>";
      return false;
    }
    if(Regx.test(searchDn)){
      document.getElementById("errorInfo").innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>用户搜索DN不能含有汉字</b></font><br/>";
      return false;
    }
  }
  document.getElementById("errorInfo").innerHTML="<font color='red'></font>";
  return true;
}
//验证radius服务器的IP
function check_radiusIP(){
  var radiusIp=document.getElementById("radiusServer").value;
  var exp=/^(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$/;
  var flag = radiusIp.match(exp);
  if( radiusIp=="localhost"||(flag != undefined && flag!=null && flag!="")){
    return true;
  }else if(radiusIp==""){
    document.getElementById("errorInfo").innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>Radius服务器的ip不能为空</b></font><br/>";
    return false;
  }else{
    document.getElementById("errorInfo").innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>请输入有效radius服务器ip地址</b></font><br/>";
    return false;
  }
}
//验证radius共享密码
function check_sharedSecret(){
  var sharedSecret=document.getElementById("radiusShareSecret").value;
   if(sharedSecret!= null && sharedSecret!=""){
     if(getLenth(sharedSecret)>64){
       document.getElementById("errorInfo").innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>radius秘钥不能超过64个字节</b></font><br/>"; 
       return false;
     }
     return true;
   }else{
      document.getElementById("errorInfo").innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>radius秘钥不能为空</b></font><br/>";
      return false;
    }
}
//验证radius通信端口
function check_port(){
  var radiusPort=document.getElementById("radiusPort").value;
  var Regx = /^[0-9]*$/;
  
  if(radiusPort!=null && radiusPort!=""){
    if(!Regx.test(radiusPort)){
      document.getElementById("errorInfo").innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>radius的通信port只能由数字组成</b></font><br/>"; 
      return false;
    }
    if(getLenth(radiusPort)>4){
      document.getElementById("errorInfo").innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>radius的通信port不能超过4个字节</b></font><br/>";  
      return false; 
    }
     return true;
   }else{
      document.getElementById("errorInfo").innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>radius的通信port不能为空</b></font><br/>";
      return false;
    }
}

//验证超时
function check_timeout(){
  var timeout=document.getElementById("radiusTimeout").value;
  var Regx = /^[0-9]*$/;
  if(timeout != null &&timeout !=""){
    /*正则验证*/
    if(!Regx.test(timeout)){        
      document.getElementById("errorInfo").innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>radius的通信超时值只能由数字组成</b></font><br/>";  
      return false;
    /*超时次数不能大于10*/
    }else if (timeout > 100 || timeout < 1){
      document.getElementById("errorInfo").innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>radius的通信超时的范围为1~100秒</b></font><br/>";  
      return false;
      }
    return true;
  }else{
    document.getElementById("errorInfo").innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>radius的通信超时不能为空</b></font><br/>";  
    return false;
  }
}
//验证radius的尝试次数
function check_retires(){
  var retires=document.getElementById("radiusRetires").value;
  var Regx = /^[0-9]*$/;
  if(retires!=null && retires!=""){
    if(!Regx.test(retires)){
      document.getElementById("errorInfo").innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>radius的通信尝试次数只能由数字组成</b></font><br/>"; 
      return false;
    }else if(retires>100 || retires<1){
      document.getElementById("errorInfo").innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>radius的通信尝试次数的范围为1~100次</b></font><br/>";  
      return false; 
    }
    return true;
   }else{
     document.getElementById("errorInfo").innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>radius的通信尝试次数不能为空</b></font><br/>"; 
     return false;
   }
 }
function checkForm(){
  var checkLDAP=document.getElementById("LDAP_verification");
  var myForm=document.getElementById("myForm");
  var checkRADIUS=document.getElementById("RADIUS_verification");
  var checkLocal=document.getElementById("local_verification");
  var checkdFlag = true;
  if(checkdFlag == checkLDAP.checked){
    var Ip=check_IP();
    if(!Ip){
      return false;
    }
    var searchDn=check_search();
    if(!searchDn){
      return false;
    }

   // myForm.action="verificationSetting";
    //myForm.submit();
       var data = $("#myForm").serializeArray();
         if (validata() == true ){
          $.ajax({
            type:"post",
            url:"/kinan/ConfirmSet",
            dataType:"json",
            data:data,
            success:function(info){
              alert(info.msg)
           }
          })
        }
     
   }else if(checkdFlag == checkRADIUS.checked){
   // myForm.action="radiusClient";
    var radiusIP = check_radiusIP();
    if(!radiusIP){
      return false;
    }
    
    var sharedaSecret = check_sharedSecret();
    if(!sharedaSecret){
      return false;
    }
    
    var port=check_port();
    if(!port){
      return false;
    }
    
    var timeout=check_timeout();
    if(!timeout){
      return false;
    }
    
    var retires=check_retires();
    if(!retires){
      return false;
    }
  
   // myForm.submit();
          var data = $("#myForm").serializeArray();
            if (validata() == true ){
          $.ajax({
            type:"post",
            url:"/kinan/ConfirmSet",
            dataType:"json",
            data:data,
            success:function(info){
               alert(info.msg)
           }
          })
         } 
      
  }else{
    if(checkdFlag == checkLocal.checked){
      //myForm.action="verificationSetting";
      //myForm.submit();
         var data = $("#myForm").serializeArray();
          if (validata() == true ){
          $.ajax({
            type:"post",
            url:"/kinan/ConfirmSet",
            dataType:"json",
            data:data,
            success:function(info){
              alert(info.msg)
           }
          })
        }
     
    }else{
      document.getElementById("errorInfo").innerHTML="<font color='red'>提示：</font><font color='#005b96'>请选择验证类型</b></font><br/>";
      return false;
    }
  }
}
function doTest(){
  var checkLDAP=document.getElementById("LDAP_verification");
 // var myForm=document.getElementById("myForm");
  
  if(checkLDAP.checked){
    var Ip=check_IP();
    if(!Ip){
      return false;
    }

    var searchDn=check_search();
    if(!searchDn){
      return false;
    }

    var testName=check_TestName();
    if(!testName){
      return false;
    }
    var testPwd=check_TestPwd();
    if(!testPwd){
      return false;
    }
    if(Ip && testName && searchDn && testPwd){
     // myForm.action="testLDAP";
     // myForm.submit();
          var data = $("#myForm").serializeArray();
           if (validata() == true ){
          $.ajax({
            type:"post",
            url:"/kinan/ConfirmSet",
            dataType:"json",
            data:data,
            success:function(info){
            	alert(info.msg);
           }
          })
        }
    }
  }else{
    document.getElementById("errorInfo").innerHTML="<font color='red'>提示：</font><font color='#005b96'>请选择LDAP验证</b></font><br/>";
    return false;
  }
}

// function defValue(){
//   //var myForm=document.getElementById("myForm");
//   //myForm.action="defaultCheckUser";
//   //myForm.submit();
//   $("#myForm").submit(function(){
//           $.ajax({
//             type:"post",
//             url:"",
//             dataType:"",
//             success:function(){
//            }
//           })
//       }) 
// }

window.onload=function(){
  var message=document.getElementById("message").value;
  if(message!=null && message!=""){
    document.getElementById("errorInfo").innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>"+message+"</b></font><br/><br/>";
  }
}
