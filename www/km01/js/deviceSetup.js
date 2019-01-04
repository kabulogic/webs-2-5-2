/*
* @Author: Administrator
* @Date:   2017-08-30 16:13:20
* @Last Modified by:   Administrator
* @Last Modified time: 2017-11-14 18:20:30
*/

'use strict';
$(document).ready(function(){
var flag = $("#flag").val()
 if (validata() == true ){
  $.ajax({
    type:"get",
    url:"/kinan/DeviceConfig?flag="+flag,
    dataType:"json",
    success:function(info){
       //alert(0);
       var htmls = template("deviceName",info.data)
      $("#devIn").html(htmls)
    }
  })
}
})
 var edit ="edit"
 function checkForm() {
          var value=document.getElementById("deviceName").value;
          var Regx = /^[A-Za-z0-9_]*$/;
          var allRegx = /^[A-Za-z0-9_*/-]*$/;
          var errorName=document.getElementById("errorInfo");
            if(value!=""){
              if(!Regx.test(value.substr(0 ,1))){
                errorName.innerHTML="<font color='red'>提示：</font><font color=#005b96><b>设备名称必须以数字或字母开头</b></font>";
                  return false;
              }
              
              if(value.length>20){
              errorName.innerHTML="<font color='red'>提示：</font><font color=#005b96><b>设备名称的长度应小于等于20个字符</b></font>";
              return false;
            }
            if(!allRegx.test(value))
            {
              errorName.innerHTML="<font color='red'>提示：</font><font color=#005b96><b>设备名称必须由<font color='red'>英文字母</font>、<font color='red'>数字</font>及字符“<font color='red'> - / _ * </font>”组成</b></font>";
              return false;
            }
             
             
                var flagV =$("#flag").prop("value",1);
                var data= $("#myForm").serializeArray();
              if (validata() == true ){
                  $.ajax({
                    type:"post",
                    url:"/kinan/DeviceConfig",
                    dataType:"json",
                    data:data,
                    success:function(info){
                      if(info.msg=="设置成功"){
                         alert(info.msg)    
                        window.top.location.href="index.html"
                      }
                          
                    }
                  })
             }
            }
            else{
              errorName.innerHTML="<font color='red'>提示：</font><font color=#005b96><b>设备名称不可以为空</b></font>";
              return false;
            }
        }
       
