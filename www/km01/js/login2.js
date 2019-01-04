/*
* @Author: Administrator
* @Date:   2017-10-25 15:38:10
* @Last Modified by:   Administrator
* @Last Modified time: 2017-11-14 16:15:42
*/
'use strict';
//前台验证

 $(document).ready(function (){

     $("#loginForm").submit(function(){
      //用户名加密
         // var username =$("#username").val();
        //  var key1 = $("#key1").html();
      // var enResult = strEnc(username,key1);
      // console.log(enResult);
       // $("#username").prop("value",enResult); 
       //检查用户名
       var username =$("#username").val();
       var errorInfo=$("#usernameCheck");
    errorInfo.html("");
    if(username==""){
       errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>用户名不能为空</b></font><br/><br/>");
       return false;
      }else if(username.length<6||username.length>20){
      errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>用户名的长度为6-20个字节</b></font><br/><br/>");
        return false;
    }
       var  password = $("#password").val()
      var errorInfo2= $("#passwordCheck"); 
      errorInfo2.html("");
      if(password==""){
          errorInfo2.html("<font color='red'>提示：</font><font color='#005b96'><b>密码不能为空</b></font><br/><br/>");
          return false;
      }else if( password.length<8|| password.length>16){
         errorInfo2.html("<font color='red'>提示：</font><font color='#005b96'><b>密码由8到16位组成</b></font><br/><br/>");
          return false;
      }
      
       //密码加密
         var password =$("#password").val();
         var key = $("#key").val();
         var pResult = strEnc(password,key);
        $("#password").prop("value",pResult);
         var data = $("#loginForm").serializeArray();
           console.log(data);
             validata();
        $.ajax({
           type:"post",
           url:"/kinan/Login",
       //    dataType:"json",
           data:data,
           success:function(info){
               var str = info;
                console.log(info)
               var obj = JSON.parse(str);
             if(obj.status=="true"){
               //   alert("登录成功")
               var csessionid = $.cookie("CSESSIONID");
                  location.href = "/index.html" 
              }else{
                alert(obj.msg)
             }
          },
           error:function(info){
              alert("请求失败")
             }
         })
         return false;
      })
   
   })
