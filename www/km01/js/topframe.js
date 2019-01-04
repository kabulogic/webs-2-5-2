/*
* @Author: Administrator
* @Date:   2017-11-08 15:04:30
* @Last Modified by:   Administrator
* @Last Modified time: 2017-11-14 19:09:52
*/

'use strict';
if(!$.cookie("CSESSIONID")&&location.href!="login.html"){
    window.top.location.href="login.html"
}
