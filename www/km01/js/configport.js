/*
 * @Author: Administrator
 * @Date:   2017-09-04 15:35:36
 * @Last Modified by:   Administrator
 * @Last Modified time: 2017-11-14 18:35:52
 */

'use strict';
$(document).ready(function() {
	var portNum= location.search.slice(1);
    //console.log(search);
    if (validata() == true ){
      $.ajax({
        type:"get",
        url:"/kinan/ConfigPortInfo?"+portNum,
        dataType:"json",
        success:function(info){
          //alert("请求成功");
           var htmls = template("editPortInfo",info.data)
           $("#myForm").html(htmls) 
         }
       })
    }
   // var info ={
      //"status":"true",
      //"msg":"验证通过",
     // "data":{"portType":"usb","portName":"port1","resolution":"1920X1080","refresh":"60"}}
     // var htmls = template("editPortInfo",info.data)
      //$("#myForm").html(htmls)
      $("#myForm").submit(function(){
          var portName =$("#portName").val();
          var error =$("#errorInfo")
          var Regx = /^[A-Za-z0-9_]*$/;
       if(portName!=""){
          if(!Regx.test(portName.substr(0 ,1))){
             error.html("<font color='red'>提示:</font> <font color=#005b96><b>端口名称必须以数字或字母开头</b></font>");
            return false;
          }
         if(portName.length>64){
          error.html("<font color='red'>提示:</font><font color=#005b96><b>端口名称的长度应小于等于64个字符</b></font>");
          return false;
         }
         if(portName.indexOf(")")>=0 || portName.indexOf("(")>=0 || portName.indexOf(" ")>=0){
           error.html("<font color='red'>提示:</font> <font color=#005b96><b>端口名称中不能含有‘(’、‘)’和空格</b></font>");
           return false;
        }
        var data = $("#myForm").serializeArray();
          if (validata() == true ){
          $.ajax({
            type:"post",
            url:"/kinan/ModifyPort",
            dataType:"json",
            data:data,
            success:function(info){
             alert("编辑成功");
           }
          })
        }
       }else{
        error.html("<font color='red'>提示:</font><font color=#005b96><b>端口名称不可以为空</b></font>");
       return false;
      }
          return false;
      })
   })


      
