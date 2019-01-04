/*
* @Author: Administrator
* @Date:   2017-07-12 15:24:42
* @Last Modified by:   Administrator
* @Last Modified time: 2017-11-14 19:11:57
*/

'use strict';
validata()
 $(document).ready(function(){
 	var info ={
    status:true,
    msg:{hotKey:[{"opt":"双击Scroll Lock"},{"opt":"双击Num Lock"},{"opt":"双击Caps Lock"},{"opt":"双击Caps Lock"},{"opt":"双击左Shift键"}],
    linkKey:[{"opt":"左Alt键"},{"opt":"左Shift键"},{"opt":"左Ctrl键"},{"opt":"禁用"},{"opt":"双击左Alt键"}]},
    data:{portHotKey:"双击左Shift键",portLinkKey:"双击左Alt键"}}
	
	var htmls = template("hotKeyset",info)
	   $("#myForm").html(htmls);
})

