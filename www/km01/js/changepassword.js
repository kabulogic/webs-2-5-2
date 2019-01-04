/*
 * @Author: Administrator
 * @Date:   2017-06-21 17:59:12
 * @Last Modified by:   Administrator
 * @Last Modified time: 2017-11-14 18:35:16
 */

// 'use strict';
$(document).ready(function(){
   if (validata() == true ){
    $.ajax({
        async: false,
        type: "get",
        url: "/kinan/SafeSetInfo",
        dataType: "json",
        success: function(info) {
            var htmls = template("changeIn",info.data)
            $(".clear").html(htmls)
             $("#sub").on("click",function(){
                var  oldpassword = $("#oldPassword_check").val()
                var firstValue = $("#first_password").val();
                var password = $("#password").val();
                var key =$("#key").val();
                var flag_oldPassword = oldpassword_check() //检查老密码
                if(!flag_oldPassword){
                   return false;
                }
               //检查第一次密码
               var flag_firstpassword = firstpassword_check();
               if(!flag_firstpassword){
                 return false;
               }
               var flag_repassword=rpass_check();//重复密码
               if(flag_oldPassword&&flag_repassword){
                 var oResult = strEnc(oldpassword,key);
                 $("#oldPassword_check").prop("value",oResult);
                 var nResult = strEnc(firstValue,key);
                 $("#first_password").prop("value",nResult);
                 var pResult = strEnc(password,key);
                 $("#password").prop("value",pResult);
                 var data = $("#changeForm").serializeArray();
                  validata();
                 $.ajax({
                   async:false,
                   type:"post",
                   url:"/kinan/ChangePasswd",
                   dataType:"json",
                   data:data,
                   success:function(){
                   //  window.top.location.href ="login.html"
                   }
                 })
               }
               return false;
             })
          }
     })
}
	
  })
  var message="";
        function getMessage(){  //启用强密码原则
          var strongPassword=document.getElementById("strongPassword").value;
          var minLength=document.getElementById("minLength").value;
          var maxLength_set=document.getElementById("maxLength_set").value;
          var lowerCase=document.getElementById("lowerCase").value;
          var upperCase=document.getElementById("upperCase").value;
          var symbol=document.getElementById("symbol").value;
          var figure=document.getElementById("figure").value;
          var historyDept=document.getElementById("historyDept").value;
          var rMinLength=document.getElementById("rMinLength").value;//弱密码规则
          var rMaxLength=document.getElementById("rMaxLength").value;
          var head="密码至少包含";
          
          
          if(strongPassword==1){
          
            if(lowerCase==1){
              message+="1个小写字母、";
            }
            if(upperCase==1){
              message+="1个大写字母、";
            }
            if(figure==1){
              message+="1个数字、";
            }
            if(symbol==1){
              message+="1个特殊字符(-@.$!_)、";
            }
          
            if(lowerCase==0 && upperCase==0 && figure==0 && symbol==0){
              message="密码只能由"+minLength+"-"+maxLength_set+"位的字母、数字或特殊符号(-@.$!_)组成";
            }else{
              message=message.substring(0, message.length-1);
              message=head+message+",且由"+minLength+"-"+maxLength_set+"位组成";
            }
          }else{
            message="密码只能由"+rMinLength+"-"+rMaxLength+"位的字母、数字或特殊字符(-@.$!_)组成";
            document.getElementById("first_password").placeholder="由"+rMinLength+"-"+rMaxLength+"位的字母、数字或特殊字符(-@.$!_)组成";//密码提示信息
          }
           errorInfo.innerHTML = "<font color='gray'>" + message + "</font>";
        } 
    

  //原密码判断
    function oldpassword_check(){
      var  oldpassword = $("#oldPassword_check").val()
      var errorInfo= $("#errorInfo"); 
      errorInfo.html("");
      if(oldpassword==""){
          errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>请输入原密码</b></font><br/><br/>");
          return false;
      }else if(oldpassword.length<8||oldpassword.length>16){
         errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>原密码由8到16位组成</b></font><br/><br/>");
          return false;
      }
      return true;
     }
    //新密码判断
      function firstpassword_check(){
        var  firstValue = $("#first_password").val();
        var errorInfo= $("#errorInfo"); 
        var strongPassword = $("#strongPassword").val();
        var lowerCase =$("#lowerCase").val();
        var upperCase = $("#upperCase").val();
        var symbol = $("#symbol").val();
        var figure = $("#figure").val();
        var head = "密码至少包含";
        errorInfo.html("");
        if(firstValue==""){
            errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>请输入新密码</b></font><br/><br/>");  
            return false;
         } else if(firstValue.length<8||firstValue.length>16){
            errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>新密码由8到16位组成</b></font><br/><br/>");
            //  $("#result").prop("value","false");
            // return;
            return false;
           } else if (strongPassword == 1) {
        if (lowerCase == 1) {
            //判断是否有个小写字母，正则匹配
            var reg  = /[a-z]/
            if(!reg.test(firstValue)){
                errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>"+message+"</b></font>");
                return false;
            }
           
        }
        if (upperCase == 1) {
             //判断是否有个大写字母，正则匹配
              var reg  = /[A-Z]/
             if(!reg.test(firstValue)){
                errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>"+message+"</b></font>");
                 return false;
            }
        }
        if (figure == 1) {
              //判断是否有个数字，正则匹配
                var reg  = /[0-9]/
             if(!reg.test(firstValue)){
                errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>"+message+"</b></font>");
                 return false;
            }
        }
        if (symbol == 1) {
              //判断是否有个特殊字符，正则匹配(-@.$!_)
              var reg =/[-@.$!_]/
            if(!reg.test(firstValue)){
                errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>"+message+"</b></font>");
                 return false;
            }
        }

        if (lowerCase == 0 && upperCase == 0 && figure == 0 && symbol == 0) {
            message = "密码只能由" + minLength + "-" + maxLength_set + "位的字母、数字或特殊符号(-@.$!_)组成";
        } else {
            message = message.substring(0, message.length - 1);
            message = head + message + ",且由" + minLength + "-" + maxLength_set + "位组成";
        }
        return true;
      } 
            return true; 
      }
       //重复密码判断
      function rpass_check(){
          var  oldpassword = $("#oldPassword_check").val()
          var  firstValue = $("#first_password").val();
          var  password = $("#password").val();
          var errorInfo= $("#errorInfo"); 
          errorInfo.html("");
           if(password==""){
                errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>请输入重复密码</b></font><br/><br/>");
                 return false;
             }else if(password.length<8||password.length>16){
                errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>重复密码由8到16位组成</b></font><br/><br/>");
                 return false;
            }else if(firstValue!=password){
               errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>两次密码不一致</b></font><br/><br/>");
                 return false;
            }else{
              //原密码写入历史密码
              $("#historyPassword").prop("value",oldpassword)
                return true;
            }
          
       }
        
       
	   //去空格
	   function trim(str){ //删除左右两端的空格
		 return str.replace(/(^\s*)|(\s*$)/g, "");
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
        document.getElementById("result").value="false";
        return false;
      }
      return true;
    } 
    window.onload=function(){
        getMessage();
    }
           
        
        
        
       
