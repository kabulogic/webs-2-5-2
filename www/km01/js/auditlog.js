/*
 * @Author: Administrator
 * @Date:   2017-07-12 16:16:33
 * @Last Modified by:   Administrator
 * @Last Modified time: 2017-11-14 18:34:14
 */

'use strict';
var data=[
	["告警1","告警2","告警3","告警4","告警5"],
	["视频丢失","网络断开","网络链接失败","异常访问","硬盘满","硬盘错误","非法关机","ip冲突"],
	["录像配置","端口配置","网络配置","用户配置","硬盘配置","用户组配置"],
	["备份录像操作","备份配置操作","删除录像","删除日志","系统升级","恢复出厂默认","硬盘操作","时间操作","启动","重启","关机"],
	["预览1","预览2","预览3","预览4","预览5","预览6"],
	["定时录像开始","报警录像开始","定时录像停止","报警录像停止"]]
	function getData(){
		//获得主类型下拉框的对象
		var sltmainType=document.form1.mainType;
		//获得子类型下拉框的对象
		var sltsonType=document.form1.sonType;  
		//得到对应的子类型数组
		var mainTypeson=data[sltmainType.selectedIndex - 1];

		//清空子类型下拉框，仅留提示选项
		sltsonType.length=1;

		//将数组中的值填充到子类型下拉框中
		for(var i=0;i<mainTypeson.length;i++){
			sltsonType[i+1]=new Option(mainTypeson[i],i+1);
		}
	}
$(document).ready(function(){
	if (validata() == true ){
	$.ajax({
		async:false,
		type:"get",
		url:"/cgi-bin/auditlog.cgi",
		dataType:"json",
		success:function(info){
			
			var htmls = template("auditIn",info.msg);
			$(".dateChoose").html(htmls);

			$('#logIn').yhhDataTable({
				'paginate':{
					'changeDisplayLen':true,
					'type':'updown',
					'visibleGo': true
				},
				'tbodyRow':{
					'zebra':true,
					'write':function(d){
						return '<tr><td>'+d.number+'</td><td style="text-align:left">'+d.time+'</td><td style="text-align:left">'+d.majorType+'</td><td style="text-align:left">'+d.minorType+'</td><td style="text-align:left">'+d.explain+'</td></tr>';
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
	$(".searchBtn").on("click",function(){

		var startV = $("#startTime").val();
		var starttimeM1=startV.replace(new RegExp("-","gm"),"/");
		var starttimeM2 = (new Date(starttimeM1)).getTime();
		var endV = $("#endTime").val();
		var endtimeM1=endV.replace(new RegExp("-","gm"),"/");
		var endtimeM2 = (new Date(endtimeM1)).getTime();
		if((starttimeM2>endtimeM2)||startV==""||endV==""){
			alert("时间不符合标准");
			return false
		}
		if(starttimeM2<endtimeM2){
			var firstV = starttimeM2/1000;
			var lastV = endtimeM2/1000;
			$("#starttimeM2").prop("value",firstV);
			$("#endtimeM2").prop("value",lastV);
			var data=$("#myForm").serializeArray();
			// console.log(data);
			  if (validata() == true ){
				$.ajax({
					type:"post",
					url:"/cgi-bin/auditlog.cgi",
					dataType:"json",
					data:data,
					success:function(info){
						//var htmls = template("auditIn",info.msg);
									//$(".dateChoose").html(htmls);
					       
							 $(".audit").html("")
							  var $table=$('<table id="log"></table>');
							 var $thead=$("<thead></thead>");
							 var $tbody=$("<tbody></tbody>");
							 var $tr=$("<tr></tr>")
							 $thead.append($tr)
							// $(function(){
							  // var data =["编号","日期","主类型","次类型","说明"]
							   //var ht ="";
								//for(var i = 0;i<data.length;i++){
								   //ht+='<th  width="150px" style="text-align:left;">'+data[i]+"</th>";
								//}
								//$tr.append(ht)
							// })
							 
							 var data = ["编号","日期","主类型","次类型","说明"]
								var $ht = '<th	width="45px" >'+data[0]+'</th><th style="text-align:left;">'+data[1]+'</th><th style="text-align:left;">'+data[2]+'</th><th style="text-align:left;">'+data[3]+'</th><th  style="text-align:left;">'+data[4]+'</th>';
								 $tr.append($ht);
							   $table.append($thead).append($tbody);
							   $(".audit").append($table)
									$('#log').yhhDataTable({
										'paginate':{
											'changeDisplayLen':true,
											'type':'updown',
											'visibleGo': true
										},
										'tbodyRow':{
											'zebra':true,
											'write':function(d){
												return '<tr><td>'+d.number+'</td><td style="text-align:left">'+d.time+'</td><td style="text-align:left">'+d.majorType+'</td><td style="text-align:left">'+d.minorType+'</td><td style="text-align:left">'+d.explain+'</td></tr>';
											}
										},
										'tbodyData':{
											'enabled':true,  /*是否传入表格数据*/
											'source':info /*传入的表格数据*/
										},
										'backDataHandle':function(d){
											if (d.status == 'true'){
												return d.data;
												console.log(d.data);
											} else {
												alert('出错信息');
												return [];
											}
										}
									});
					}
				})
}
		}
	})



})


