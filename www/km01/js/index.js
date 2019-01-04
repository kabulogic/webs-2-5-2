/*
* @Author: Administrator
* @Date:   2017-07-11 15:15:53
* @Last Modified by:   Administrator
* @Last Modified time: 2017-11-27 11:05:55
*/
'use strict';

//菜单的显示
function menu(thisObj){
  $(thisObj).parent().children("ul").show(0);
  $(thisObj).parent().prevAll().children("ul").hide(0);
  $(thisObj).parent().nextAll().children("ul").hide(0);
}
//菜单的隐藏
function menuDis(thisObj){
  $(thisObj).parent().hide(0);
}

function allMenuDis(){
  $("ul").hide();
}

$(document).ready(function(){
  if (validata() == true ){
    $.ajax({
      async:false,
      type:"get",
      url:"/kinan/SideBar",
      success:function(data){
      var str=data;
      //console.log(str);
     //兼容IE7/8
       if(typeof JSON == 'undefined'){
           $('head').append($("<script type='text/javascript' src='/js/json2.js'>"));
       }  
      var obj=JSON.parse(str);  
      var htmls = template('sideInfo', obj.data);
       $("body").html(htmls);
      }
    })
  }
    //tab栏切换样式
   $(".div-nav ul li").mouseover(function(){
      $(this).addClass('select').siblings().removeClass('select');
    })
   
   /*退出功能
   $("#exit").click(function(){
       $("#exitModal").modal();
    })*/

  //退出模态框
    $("#modalFooter").on("click","button.btnSave",function(){
    if (validata() == true ){
		$.ajax({
			async:"false",
			type:"get",
			url:"/kinan/Quit",
			dataType:"json",
			success:function(info){
       $.cookie('CSESSIONID', null); // 删除cookie：把ncookie的值设为null即可 
				location.href="login.html"

			}
		})
			}
	})
	//帮助的模态框
	$("#help").click(function(){
		$(".bigBox").show();
	})
	$(".btn-confirm").click(function(){
		location.href="login.html"
	})
	$(".btn-cancel").click(function(){
		//location.href="index.html"
		$(".bigBox").hide()
	})
	$("#topButton").click(function(){
		$(".bigBox").hide()
	})
})


