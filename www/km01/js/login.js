/*
* @Author: Administrator
* @Date:   2017-06-05 14:11:22
* @Last Modified by:   Administrator
* @Last Modified time: 2017-11-14 16:44:28
*/

'use strict';
//前台验证
   function checkUser(){
          var user = $("#username").val();
           if(user==""){
            document.getElementById("usernameCheck").style.display=""
              //$("#usernameCheck").show();
                return false;
           }
        }
   function checkPassword(){
        var psd = $("#password").val();
        if(psd==""){
           document.getElementById("passwordCheck").style.display=""
           //$("#passwordCheck").show();
           return false;
          }
   }
 $(document).ready(function (){
     $("#loginForm").submit(function(){
   //    //用户名加密
	  // //  var username =$("#username").val();
   //      //  var key1 = $("#key1").html();
   //    // var enResult = strEnc(username,key1);
   //    // console.log(enResult);在
   //     // $("#username").prop("value",enResult); 
   //     //密码加密
         var password =$("#password").val();
         var key = $("#key").val();
         var pResult = strEnc(password,key); //加密公式
        $("#password").prop("value",pResult);
         var data = $("#loginForm").serializeArray();
            console.log(data);
        $.ajax({
           type:"post",
           url:"/kinan/Login",
       //    dataType:"json",
           data:data,
		       success:function(info){
               var str = info;
               // console.log(info)
               var obj = JSON.parse(str);
             if(obj.status=="true"){
                  alert("登录成功")
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
