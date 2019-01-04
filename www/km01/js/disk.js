/*
* @Author: Administrator
* @Date:   2017-09-13 17:40:13
* @Last Modified by:   Administrator
* @Last Modified time: 2017-11-14 19:13:22
*/

'use strict';
validata()
$(document).ready(function(){
     var info ={
      "status":"true",
      "msg":{"start_time":"2017-09-08 00:00:00","end_time":"2017-09-08 10:50:22"},
     "data":[{"diskName":"C","nature":"null","size":"20%","used":"40%","free":"40%","option":"操作"},{"diskName":"D","nature":"null","size":"20%","used":"40%","free":"40%","option":"操作"},{"diskName":"E","nature":"null","size":"20%","used":"40%","free":"40%","option":"操作"}]}
     var htmls = template("diskIn",info);
     $(".dis").html(htmls)
})
   //选中数目
       var checkNum = 0;
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
   function getFormatt(){
      //存放要格式化的checkbox
      var delId = "symbol";
      var delIds="";
      var trs = [];

    // 选中的checkbox
      var $targets = $("input[name='selectFlag']:checked");
      
      //遍历选中的值
      $targets.each(function(i,o){
        trs.push($(this).closest("tr"));
        // delIds.push("delId="+$(this).val());
        delIds+= delId+"="+$(this).val()+";"
      });
      console.log(delIds);
      //console.log(typeof(delIds))
      delIds = delIds.substr(0,delIds.length-1)
       console.log(delIds);
      //ajax的URL传递方式;
      if(checkNum==0){
       alert("请选中用户");
        //layer.msg("请选中用户")
      }else{
        if(confirm("是否要立即格式化?")){
         if (validata() == true ){
           $.ajax({
             type:"get",
             url:"info.php?"+delIds,
             data:{},
             success:function(data){
                 // $(trs).each(function(i,o){
                 //  o.remove();
                  
                 // });
                 alert(0)
                  //window.location.reload()//刷新当前页面.
              },
              error:function(error){
                alert(120);
              }
            })
         }
         }else{
           return false
         }
      }
  
    }
    //取消格式化
    function selectCancel(){
      location.href ="disk.html"
    }