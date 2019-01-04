
'use strict';

$(document).ready(function(){
  if (validata() == true ){
  $.ajax({
     type:"get",
     url:"/kinan/PortInfo",
     dataType:"json",
    success:function(info){
      $('#portIn').yhhDataTable({/*分页插件的使用*/
            'paginate':{
            'changeDisplayLen':true,
            'type':'updown',
            'visibleGo': true
            },
           'tbodyRow':{
           'zebra':true,
           'write':function(d){
            return '<tr><td>'+d.sNum+'</td><td><a href=configport.html?portNum='+d.sNum+'>'+d.cName+'</a></td><td><a href="javascript:;" class=" handle btn btn-warning btn-xs">'+d.AccessType+'</a></td><td class="status1">'+d.cStatus+'</td><td>'+d.availability+'</td><td>'+d.broadcast+'</td></tr>';
            }
          },
         'tbodyData':{
            'enabled':true,  /*是否传入表格数据*/
            'source':info /*传入的表格数据*/
          },
         'backDataHandle':function(d){
            if (d.status == 'true'){
              return d.data;
            } else if(d.status == 'false' && d.msg =="登录已过期") {
               alert('登录已过期，请重新登录！');
               window.top.location.href="login.html"
            }
            else{
              alert('出错信息');
             return [];
           }
         }
       });
    }
 })
}
 var num =1;
  window.setInterval(function() {/*每隔3秒请求一次*/
        num++;
         if (validata() == true ){
          $.ajax({
            type:"get",
            url:"/kinan/PortInfo",
            dataType:"json",
            success:function(info){
              for (var i = 0; i<info.data.length; i++) {
                var num1 = info.data[i].AccessType;
                $(".handle").html(num1+num);
                var num2 = info.data[i].cStatus;
                $(".status1").html(num2+num);

              };
 
         }
      })
}
      },3000);
  });




// data-table-top-box
// data-table-bottom-box paginate-containter