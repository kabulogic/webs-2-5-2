/*
 * @Author: Administrator
 * @Date:   2017-08-18 13:56:30
 * @Last Modified by:   Administrator
 * @Last Modified time: 2017-11-14 18:38:49
 */

//'use strict';
$(document).ready(function(){
	var search = location.search.slice(1);
	//console.log(search);
if (validata() == true ){
	$.ajax({
		async:false,
		type:"get",
		url:"/kinan/EditUserGroupInfo?"+search,
		//dataType:"json",
		success:function(info){
		 // var obj = JSON.parse(info);
		  var obj = eval("("+info+")");
			var htmls = template("editGinfo",obj.data)
			$(".firstpage").html(htmls);   	
			$("#myForm").submit(function(){
				var data = $("#myForm").serializeArray();
				$.ajax({
          async:false,
					type:"post",
					url:"/kinan/EditUserGroup?"+search,
					dataType:"json",
					data:data,
					success:function(info){
						if(info.status == "true")
						{
							alert(info.msg);
							window.location.href="usergrouplist.html";
						}
						else
						{
							alert(info.msg);
							window.location.href="editusergroup.html?"+search;
						}					
					}
				})
				return false;
			})
     	}
	})
}
})
function goback(){
	window.location.href="usergrouplist.html";
  }
 function sysView(){
    $("#sysPri").show();
  }
  function disSysView(){
    $("#sysPri").hide();
  } 
  function view(){
    $("#portAuth").show();
    $("#allPortAuth").show();
  }
  function disView(){
    $("#portAuth").hide();
    $("#allPortAuth").hide()
  }
