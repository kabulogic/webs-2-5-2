/*
* @Author: Administrator
* @Date:   2017-07-12 16:27:01
* @Last Modified by:   Administrator
* @Last Modified time: 2017-11-14 18:34:52
*/

'use strict';
$(document).ready(function(){ 
   if (validata() == true ){
   $.ajax({
     type:"get",
     url:"/kinan/BackupInfo",
     dataType:"json",
     success:function(info){
	    var htmls=template("backUp",info.data)
	    $(".firstpage_1").html(htmls)
     }
  })
 }
})
function backsetting(){
    var backsetting=document.getElementById("backModel").value;
          if(backsetting==0){
              document.getElementById('oneTime').disabled = 'true';
              document.getElementById('twoTime').disabled = 'true';
              document.getElementById('threeTime').disabled = 'true';
          }else if(backsetting==1){
               document.getElementById('oneTime').disabled = '';
               document.getElementById('twoTime').disabled = '';
              document.getElementById('threeTime').disabled = '';
          }
      }
function setBackup(){
    var oneTime=document.getElementById("oneTime").value;
    var twoTime=document.getElementById("twoTime").value;
    var threeTime=document.getElementById("threeTime").value;
    var manual=document.getElementById("manual");
    var manualV = manual.value;
    var auto=document.getElementById("auto");
    var message=document.getElementById("message");
//    var Regx=/^(?!0+(\.0+)?$)\d+(\.\d+)?$/;
    if (manual.checked){
      if(confirm("是否要备份设备数据?")) {
      //  document.getElementById('flag').value = flag;
          var data =$("#myForm").serializeArray()
          console.log(data)
          if (validata() == true ){
          $.ajax({
            type:"post",
            url:"/kinan/Backup",
            dataType:"json",
            data:data,
            success:function(info){
                  alert(info.msg)
            }
          })
        }
        return true;
      }else{
        return false;
      }
    }
    if (auto.checked){
      if((oneTime!=null && oneTime!="")&&(twoTime!=null && twoTime!="")&&(threeTime!=null && threeTime!="")){
        if(confirm("是否要备份设备数据?")) {
          //document.getElementById('flag').value = flag;
         var data =$("#myForm").serializeArray();
           if (validata() == true ){
          $.ajax({
            type:"post",
            url:"/kinan/Backup",
            dataType:"json",
            data:data,
            success:function(info){
                  alert(info.msg)
            }
          })
        }
          return true;
        }else{
          return false;
        }
      }else{
        message.innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>备份时间都不能为空</b></font>";
        return false; 
      }
    }
}
function setRestore(){
  if(confirm("是否要立即恢复,设备将会重新启动?")) {
     document.getElementById('doFlag').value = 7;
          var data =$("#myForm").serializeArray();
        if (validata() == true ){
          $.ajax({
            type:"post",
            url:"/kinan/SystemCtrl",
            dataType:"json",
            data:data,
            success:function(info){
			        alert(info.msg)
            }
          })
        }
         return true;
    }else{
          return false;
      }
}