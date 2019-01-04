/*
 * @Author: Administrator
 * @Date:   2017-07-27 10:40:58
 * @Last Modified by:   Administrator
 * @Last Modified time: 2017-11-14 18:44:20
 */

// 'use strict';
$(document).ready(function(){
	if (validata() == true ){
 $.ajax({
   type:"get",
   url:"/kinan/UserGroupList",
   dataType:"json",
  success:function(info){
   $('#userGIn').yhhDataTable({
			  'paginate':{
			  'changeDisplayLen':true,
			  'type':'updown',
			  'visibleGo': true
			  },
			 'tbodyRow':{
			 'zebra':true,
			 'write':function(d){
				 return '<tr><td><input type="checkbox" value='+d.userGroupName+'  name="selectFlag" onclick="checkBox(this)"/></td><td >'+d.userGroupID+'</td><td><a href=editusergroup.html?userG='+d.userGroupName+'>'+d.userGroupName+'</a></td></tr>';
			  }
			},
		   'tbodyData':{
			  'enabled':true,  /*是否传入表格数据*/
			  'source':info /*传入的表格数据*/
			},
		   'backDataHandle':function(d){
			  if (d.status == 'true'){
				return d.data;
			  } else {
				alert('出错信息');
			   return [];
			 }
		   }
		 });
		}
    })
}
})
//查找
function search(){
	var value = $("#groupName").val();
	console.log(value);
	if (validata() == true ){
	$.ajax({
		type:"get",
		url:"/kinan/SearchUserGroup?userG="+value,
		dataType:"json",
		success:function(info){
			var uGroup = info.data.userGroupName;
			if(uGroup)
			{
				$('	tbody tr').each(function(){
					if($(this).html().indexOf(uGroup) != -1){
						$(this).show();
					} else{
						$(this).hide();
					}

				});
				$(this).parent().append($('tbody tr').sort(function(a,b){
					return $(a).html().indexOf(uGroup) < $(b).html().indexOf(uGroup);
				}));

			}else{
				alert(info.msg);
			}
		}
	})
}
}
//回车键查找
function enterSumbit(){
	var event=arguments.callee.caller.arguments[0]||window.event;//消除浏览器差异  
	if (event.keyCode == 13){  
		var value = $("#groupName").val();
		console.log(value);
		//userNameValue=trim(value.value);
		if (validata() == true ){
		$.ajax({
			type:"get",
			url:"/kinan/SearchUserGroup?userG="+value,
			dataType:"json",
			success:function(info){
				var uGroup = info.data.userGroupName;
				if(uGroup)
				{
					$('tbody tr').each(function(){
						if($(this).html().indexOf(uGroup) != -1){
							$(this).show();
						} else{
							$(this).hide();
						}

					});
					$(this).parent().append($('tbody tr').sort(function(a,b){
						return $(a).html().indexOf(uGroup) < $(b).html().indexOf(uGroup);
					}));

				}else{
					alert(info.msg);
				}
			}
		})
	}
	}   
}
//全选
function checkAll(){
	var ischecked=document.getElementById("ifAll").checked;
	var sel=document.getElementsByName("selectFlag");
	if(ischecked){
		for(var i=0;i<sel.length;i++){
			sel[i].checked=true;
		}
		checkNum=sel.length;
	}else{
		for(var i=0;i<sel.length;i++){
			sel[i].checked=false;
		}
		checkNum=0;
	}
}
//   //选中数目
var checkNum = 0;
var userIds="";
//单选
function checkBox(obj){
	checkNum=0;
	var checked=obj.checked;
	if(checked){
	}else{
		document.getElementById("ifAll").checked=false;
	}
	var sels=document.getElementsByName("selectFlag");
	console.log(sels);
	for(var i=0;i<sels.length;i++){
		if(sels[i].checked){
			checkNum++;
		}
	}
	console.log(checkNum)
}
//跳转到添加页面
function getAddGroup(){
	location.href = "addusergroup.html"
}
//删除
function getDeleteeUser(){
	//存放要删除的checkbox
	var delId = "userG";
	var delIds="";
	var trs = [] ;
	// 选中的checkbox
	$targets = $("input[name='selectFlag']:checked");
	//遍历选中的值
	$targets.each(function(i,o){
		trs.push($(this).closest("table"));
		//delIds.push("delId="+$(this).val());
		delIds+=delId+"="+$(this).val()+"&"
	});
	console.log(delIds);
	 delIds = delIds.substr(0,delIds.length-1)		
	 
	 if(checkNum==0){
		   alert("请选中用户");
			//layer.msg("请选中用户")
		  }else{
            
		  if(confirm("是否要立即删除?")){
		  	  //ajax的URL传递方式;
		  	   if (validata() == true ){
	         $.ajax({
		        type:"get",
		        url:"/kinan/DeleteUserGroup?"+delIds,
		        success:function(info){
       /*	     $(trs).each(function(i,o){
				   o.remove();
			      });*/
			     var obj=eval("("+info+")")
			     alert(obj.msg);
			     window.location.href="usergrouplist.html";
			     console.log(data);
		        },
		       error:function(error){
			     alert(120);
		        }
	         })
}
		  }else{
             
		    return false;
		     
		  	}

		  }
	
}
