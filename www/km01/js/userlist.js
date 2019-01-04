/*
 * @Author: Administrator
 * @Date:   2017-06-07 10:00:43
 * @Last Modified by:   Administrator
 * @Last Modified time: 2017-11-14 18:17:49
 */
$(document).ready(function(){
//判断浏览器是否支持placeholder属性
  supportPlaceholder='placeholder'in document.createElement('input'),
  placeholder=function(input){
    var text = input.attr('placeholder'),
    defaultValue = input.defaultValue;
    if(!defaultValue){
      input.val(text).addClass("phcolor");
    }
    input.focus(function(){
      if(input.val() == text){
        $(this).val("");
      }
    });
    input.blur(function(){
      if(input.val() == ""){ 
        $(this).val(text).addClass("phcolor");
      }
    });
    //输入的字符不为灰色
    input.keydown(function(){
      $(this).removeClass("phcolor");
    });
  };
  //当浏览器不支持placeholder属性时，调用placeholder函数
  if(!supportPlaceholder){
    $('input').each(function(){
      text = $(this).attr("placeholder");
      if($(this).attr("type") == "text"){
        placeholder($(this));
      }
    });
  }
  if (validata() == true ){
  //console.log(validata());
	$.ajax({ /*获取用户列表*/
		type:"get",
		url:"/kinan/UserList",
		dataType:"json",
		success:function(info){
			$('#userIn').yhhDataTable({
				'paginate':{
					'changeDisplayLen':true,
					'type':'updown',
					'visibleGo': true
				},
				'tbodyRow':{
					'zebra':true,
					'write':function(d){
						return '<tr><td><input type="checkbox" value='+d.userName+'  name="selectFlag" onclick="checkBox(this)"/></td><td><a href=edituser.html?userN='+d.userName+'&userG='+d.userGroupName+'>'+d.userName+'</a></td><td>'+d.userStatus+'</td><td>'+d.userGroupName+'</td></tr>';
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

//跳转到编辑页面
function getEditUser(userid){
	location.href ="/edituser.html"
}

//跳转到添加页面
function getAddUser(){
	location.href="adduser.html"
}
//选中数目
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
	for(var i=0;i<sels.length;i++){
		if(sels[i].checked){
			checkNum++;
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
function selectDelete(){
	//存放删除checkbox
	var delId = "userN";
	var delIds="";
	var trs = [];
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
        validata();
        console.log("ixxixi")
        if(validata() == true ){
		    $.ajax({
			  type:"get",
			  async:"false",
			  url:"/kinan/DelUser?"+delIds,
			  data:{},
			  success:function(data){
				alert("删除成功");
				window.location.href="userlist.html";
			   }
		    })
    }
		 }else{
		   return false
		 	}
	}
}
//ajax请求数据
function SearchUser(value){
    
    if (validata() == true ){
$.ajax({
		type:"get",
		url:"/kinan/SearchUser?userN="+value,
		dataType:"json",
		success:function(info){
			var uName = info.data.userName;
			if(uName)
			{
				$(".form_top_th").html("")
					var $table=$('<table id="userI" width="100%" border="0" cellpadding="0" cellspacing="0"></table>');
				var $thead=$("<thead></thead>");
				var $tbody=$("<tbody></tbody>");
				var $tr=$("<tr></tr>")
					$thead.append($tr)
					var data = ["用户名","用户状态","用户组"]
					var $ht = '<th width="5%" style="padding:10px; "> <input type="checkbox" name="checkbox" id="ifAll" onclick="checkAll();"/></th><th width="10%" style="padding:10px;">'+data[0]+'</th> <th width="20%" style="padding:10px;">'+data[1]+'</th><th width="30%" style="padding:10px;">'+data[2]+'</th>';
				$tr.append($ht);
				$tbody = '<tr style="background:#fff"><td width="5%" style="padding:10px;text-align:center"><input type="checkbox" value='+info.data.userName+'  name="selectFlag" onclick="checkBox(this)"/></td><td width="10%" style="padding:10px;text-align:center"><a href=edituser.html?userN='+info.data.userName+'&userG='+info.data.userGroupName+'>'+info.data.userName+'</a></td><td width="20%" style="padding:10px;text-align:center">'+info.data.userStatus+'</td><td width="30%" style="padding:10px;text-align:center">'+info.data.userGroupName+'</td></tr>';
				$table.append($thead).append($tbody);
				$(".form_top_th").append($table)	
		}
		else
		{
			alert(info.msg);
		}
	}
})
}
}
//查找功能
function search(){
	/*	$('#search_button').click(function(){
		console.log(value);*/
	  var userName =$("#userName")
		var value = $("#userName").val();
	  SearchUser(value);
}
//回车键查找
function enterSumbit(){
	var event=arguments.callee.caller.arguments[0]||window.event;//消除浏览器差异  
	if (event.keyCode == 13){  
		var value = $("#userName").val();
    SearchUser(value);
	}   
}

