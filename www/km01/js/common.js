

/*
* @Author: Administrator
* @Date:   2017-07-17 16:38:36
* @Last Modified by:   Administrator
* @Last Modified time: 2017-11-27 10:58:15
*/

'use strict';


  function validata(){//每次ajax请求之前检测用户是否登录
     if(!$.cookie("CSESSIONID")&&location.href!="login.html"){
    alert("登录已过期 ，请重新登录！")
    window.top.location.href="login.html"
    return false;
    }else if(
     $.cookie("CSESSIONID")=="null"&&location.href!="login.html"){
       alert("您刚进行了退出操作，请重新登录！")
       window.top.location.href="login.html"
       return false;
    }else{
        return true
    }
   }