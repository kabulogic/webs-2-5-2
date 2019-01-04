/*
* @Author: Administrator
* @Date:   2017-07-12 15:47:20
* @Last Modified by:   Administrator
* @Last Modified time: 2017-11-14 18:46:45
*/

'use strict';
$(document).ready(function(){
    if (validata() == true ) {
	   	$.ajax({                   //填充默认设置
	        async:false,
	      	type:"get",
	      	url:"/kinan/SafeSetInfo",
	      	dataType:"json",
	      	success:function(info) {
	        	var htmls = template("safeInfo",info.data)
	        	$(".firstpage_1").html(htmls);
	        	var flagV = info.data.LockStyle
	        	$("#setLockStyle").prop("value",flagV)
	  		}
		})
	}
})
//取消按钮设置  
function cancel(){
  if (validate() == true){
  $.ajax({
      async:false,
      type:"get",
      url:"/kinan/SafeSetInfo",
      dataType:"json",
      success:function(info){
        var htmls = template("safeInfo",info.data)
        $(".firstpage_1").html(htmls);
        var flagV = info.data.LockStyle
        $("#setLockStyle").prop("value",flagV)
      }
    })
}
}
function trim(str){//去掉空白开头和空白结尾
  return str.replace(/(^\s*)|(\s*$)/g,"")
}
 //在复选框选中时，text无效
 //登录限制的选框的选择

 function conditionDisabled(sth1,sth2,sth3){//sth1多选框id；
	//console.log(typeof(sth1));
   var box=document.getElementById(''+sth1);
	
   var text1=document.getElementById(''+sth2);
   var text2=document.getElementById(''+sth3);//sth转换成字符串
   if(sth2!=null && sth2!=""){
     if(box.checked==false ){
         text1.disabled="disabled";
       }else{
         text1.disabled="";
       }
   }
   
   if(sth3!=null && sth3!=""){
     if(box.checked==false ){
         text2.disabled="disabled";
       }else{
         text2.disabled="";
       }
   }
        
 }

//强密码
function getStrongDisabled(){
  var isStrongPassword=document.getElementById("isStrongPassword");
        var minLength=document.getElementById("minLength");
        var maxLength=document.getElementById("maxLength");
        var isLowerCase=document.getElementById("isLowerCase");
        var isUpperCase=document.getElementById("isUpperCase");
        var isFigure=document.getElementById("isFigure");
        var isSymbol=document.getElementById("isSymbol");
        var historyDepth=document.getElementById("historyDepth");
        if(isStrongPassword.checked==false){
          isLowerCase.checked=false;
          isUpperCase.checked=false;
          isFigure.checked=false;
          isSymbol.checked=false;
          minLength.disabled="disabled";
          maxLength.disabled="disabled";
          isLowerCase.disabled="disabled";
          isUpperCase.disabled="disabled";
          isFigure.disabled="disabled";
          isSymbol.disabled="disabled";
          historyDepth.disabled="disabled";
        }else{
          minLength.disabled="";
          maxLength.disabled="";
          isLowerCase.disabled="";
          isUpperCase.disabled="";
          isFigure.disabled="";
          isSymbol.disabled="";
          historyDepth.disabled="";
        }
}
//box 选中text就有效
//锁定模式
//登录锁定
function getLockStyle(){
   // setLockStyle属于隐藏域里的标签
    var flag=document.getElementById("setLockStyle").value;
    if(flag==0){
      document.getElementById('maxErrorCount_timer').disabled = "disabled";
      document.getElementById('lockTime').disabled = "disabled";
      document.getElementById('maxErrorCount_stopLogin').disabled = "disabled";
      
    }else if(flag==1){
      document.getElementById('maxErrorCount_timer').disabled = "disabled";
      document.getElementById('lockTime').disabled = "disabled";
     
    }else{
       document.getElementById('maxErrorCount_stopLogin').disabled = "disabled";
    }
  }
function getEditContent(){
    var forbidden=document.getElementById('forbidden');
    var timer_lock=document.getElementById('timer_lock');
    var stopUser=document.getElementById('stopUser');
    if(forbidden.checked==true){
      document.getElementById('maxErrorCount_timer').disabled = "disabled";
      document.getElementById('lockTime').disabled = "disabled";
      document.getElementById('maxErrorCount_stopLogin').disabled = "disabled";
    }else if(timer_lock.checked==true){
      document.getElementById('maxErrorCount_stopLogin').disabled = "disabled";
      document.getElementById('maxErrorCount_timer').disabled = "";
      document.getElementById('lockTime').disabled = "";
    }else{
      document.getElementById('maxErrorCount_timer').disabled = "disabled";
      document.getElementById('lockTime').disabled = "disabled";
      document.getElementById('maxErrorCount_stopLogin').disabled = "";
    }
        
}
window.onload=function(){
   conditionDisabled("isPasswordOverdue","day",'');//登录限制
   conditionDisabled("isCancellationFreeUser","setLayOutTime",'');//登录限制
   getStrongDisabled();//强密码设置有效性
   getLockStyle();//锁定状态
 
 }
function setAction(flag){
  document.getElementById("flag").value = flag;
 }
function day_check(){
  //启用密码过期时间
  var isPasswordOverdue=document.getElementById("isPasswordOverdue");
  var day=document.getElementById("day");
  var errorDay=document.getElementById("errorInfo");
      errorDay.innerHTML="";
  var dayValue=trim(day.value);//去除两边的空格
  var reg=/^(0|[1-9][0-9]*)$/; // 可以为0，第一个数字不能为0，数字中可以有0
     if(isPasswordOverdue.checked==true){
          if(!reg.test(dayValue)){
          errorDay.innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>密码过期的有效间隔天数无效</b></font>";
          return  false;
          }else{
              if(dayValue<1|| dayValue>365){
                errorDay.innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>密码过期的有效间隔天数范围为1~365</b></font>";
                return  false;
               }else{
               return true;
              } 
         }
     }else{
        document.getElementById("day").value=day.value;
       // alert(day.value);
        return true;
     }
        
    }
    // 注销空闲用户
 var reg_f=/^[0-9]*$/;
 function setMaxFreeTime(){
 var minLayOutTime= document.getElementById("minLayOutTime").value;//空闲时间范围
 var maxLayOutTime= document.getElementById("maxLayOutTime").value;
 
 var setLayOutTime=document.getElementById("setLayOutTime");
 var errorSetLayOutTime=document.getElementById("errorInfo");
 var isCancellationFreeUser=document.getElementById("isCancellationFreeUser");
 errorSetLayOutTime.innerHTML="";
 var value=trim(setLayOutTime.value);
 var value_sub=value.substring(0,1);//开头不能为0 这句话没有起作用
 var reg=/^(0|[1-9][0-9]*)$/;
if(isCancellationFreeUser.checked==true){
    if(!reg.test(value)){
       errorSetLayOutTime.innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>注销空闲用户的时间无效</b></font>";
     return false;
    }else{
       if(value<Number(minLayOutTime) || value>Number(maxLayOutTime) ){
        errorSetLayOutTime.innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>注销空闲用户的时间只能输入"+minLayOutTime+"~"+maxLayOutTime+"分钟</b></font>"
        return false;
       }else{
        return true;
       } 
    }
 }else{
   return true;
 }
}
 // 登录锁定 设置尝试次数
var minCounts, maxCounts
function check_maxErrorCount_timer(timer,errorTime){
    minCounts=document.getElementById("minCounts").value;
    maxCounts=document.getElementById("maxCounts").value;
    
    var maxErrorCount_timer=document.getElementById(timer);
    var errorMaxErrorCount_timer=document.getElementById(errorTime);
    var errorInfo=document.getElementById("errorInfo");
    var timer_lock=document.getElementById("timer_lock");
    errorMaxErrorCount_timer.innerHTML="";
    var value=trim(maxErrorCount_timer.value);
    var value_sub=value.substring(0,1);
    var reg=/^(0|[1-9][0-9]*)$/;
    //alert("value"+value+"minCounts"+minCounts+"maxCounts"+maxCounts);
    //alert(value<minCounts || value>maxCounts);
    if(timer_lock.checked==true){
      //判断是否是符合正则的数字
        if(!reg.test(value)){
           errorMaxErrorCount_timer.innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>限时锁定尝试次数无效</b></font>";
         return false;
        }else{
          if((value<Number(minCounts) || value>Number(maxCounts)) ){
            errorMaxErrorCount_timer.innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>限时锁定尝试次数只能输入"+minCounts+"~"+maxCounts+"</b></font>";
            return false;
          }else{
          return true;
          }
        }
     
    }else{
      return true;
    }
 }

 function check_maxErrorCount_stop(timer,errorTime){
    minCounts=document.getElementById("minCounts").value;
    maxCounts=document.getElementById("maxCounts").value;
    var maxErrorCount_timer=document.getElementById(timer);
    var errorMaxErrorCount_timer=document.getElementById(errorTime);
    var errorInfo=document.getElementById("errorInfo");
    var stopUser=document.getElementById("stopUser");
    var reg=/^(0|[1-9][0-9]*)$/;
    errorMaxErrorCount_timer.innerHTML="";
    var value=trim(maxErrorCount_timer.value);
    var value_sub=value.substring(0,1);
    if(stopUser.checked==true){
       if(!reg.test(value)){
          errorInfo.innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>锁定账号次数无效</b></font>";
        return false;
       }else{
           if((value<Number(minCounts) || value>Number(maxCounts)) ){
            errorInfo.innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>锁定账号次数只能输入"+minCounts+"~"+maxCounts+"</b></font>";
            return false;
           }else{
            return true;
           }
       }
      
    }else{
      return true;
    }
          
}
 //设置锁定时间
  function check_maxtimer(timer,errorTime){
      var minLockTime=document.getElementById("minLockTime").value;
      var maxLockTime=document.getElementById("maxLockTime").value;
       
      var maxErrorCount_timer=document.getElementById(timer);
      var errorMaxErrorCount_timer=document.getElementById(errorTime);
      errorMaxErrorCount_timer.innerHTML="";
      var value=trim(maxErrorCount_timer.value);
      var value_sub=value.substring(0,1);
      var reg=/^(0|[1-9][0-9]*)$/; 
      var timer_lock=document.getElementById("timer_lock");
      if(timer_lock.checked==true){
        if(!reg.test(value)){
          errorMaxErrorCount_timer.innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>限时锁定锁定时间无效</b></font>";
        return false;
        }else{
           if((value<Number(minLockTime) || value>Number(maxLockTime))){
            errorMaxErrorCount_timer.innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>限时锁定锁定时间只能输入"+minLockTime+"~"+maxLockTime+"分钟</b></font>";
            return false;
           }else{
            return true;
           } 
        }
        
      }else{
          return true;
      }                     
    }

 //设置密码最小长度
//var oldminLength,oldmaxLength,qMaxLength;//默认强密码的最小、最大长度，以及最大范围长度
function check_passwordLen(){//注意数据类型
    var oldminLength=document.getElementById("oldminLength").value;  
    var oldmaxLength=document.getElementById("oldmaxLength").value; 
    var qMaxLength=document.getElementById("qMaxLength").value; 
    var qMinLength = document.getElementById("qMinLength").value;
    var minLength=document.getElementById("minLength");
    var maxLength=document.getElementById("maxLength");
    var errorLength=document.getElementById("errorInfo");
  
    errorLength.innerHTML="";
    var minvalue=parseInt(trim(minLength.value));
    var max=parseInt(trim(maxLength.value));//最大长度
    var minvalue_sub=trim(minLength.value).substring(0,1);//提取第一个数
    
    var maxvalue=parseInt(trim(maxLength.value));
    var min=parseInt(trim(minLength.value));//最小长度
    var maxvalue_sub=trim(maxLength.value).substring(0,1);
    var isStrongPassword=document.getElementById("isStrongPassword");
    var reg=/^(0|[1-9][0-9]*)$/;
    if(isStrongPassword.checked==true){
      if(!reg.test(minvalue)||!reg.test(maxvalue)){
        errorLength.innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>最小或最大密码长度无效</b></font>";
      return false;
    
      }else{
        
         if(minvalue<Number(oldminLength) || minvalue>=Number(qMaxLength) || minvalue_sub==0){
          errorLength.innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>最小密码长度只能输入"+oldminLength+"~"+(qMaxLength-1)+"</b></font>";
          return false;
         }else if(maxvalue<Number(oldminLength) || maxvalue>Number(qMaxLength) || maxvalue_sub==0){
           errorLength.innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>最大密码长度只能输入"+oldminLength+"~"+qMaxLength+"</b></font>";
           return false;
         }else if(min>=maxvalue){
           errorLength.innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>最大密码长度小于最小密码长度</b></font>";
           return false;
         }else if(maxvalue<Number(qMinLength)){
          errorLength.innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>最大密码长度只能为"+qMinLength+"~"+qMaxLength+"</b></font>";
        return false;
         } 
        return true;
      }
    }else{
      return true;
    }
  }
   //设置密码最大长度
  function check_maxlength(){
       //var oldminLength=document.getElementById("oldminLength").value;  
       var oldmaxLength=document.getElementById("oldmaxLength").value; 
       var qMaxLength=document.getElementById("qMaxLength").value;
       
       var minLength=document.getElementById("minLength");
       var maxLength=document.getElementById("maxLength");
       var errorLength=document.getElementById("errorLength");
     //   console.log(0)
      // errorLength.innerHTML="";
       var value=parseInt(trim(maxLength.value));
       var min=parseInt(trim(minLength.value));//最小长度
       var value_sub=trim(maxLength.value).substring(0,1);
       var reg=/^(0|[1-9][0-9]*)$/;
       if(value<Number(oldmaxLength) || value>Number(qMaxLength) || value_sub==0){
         errorLength.innerHTML="<font color='red'>只能输入"+oldmaxLength+"~"+qMaxLength+"</font>";
         return false;
       }else if(min>=value && !reg.test(value)){
         errorLength.innerHTML="<font color='red'>最大长度必须大于最小长度</font>";
         return false;
       } 
       return true;
  }
      //设置密码深度
  function setHistoryPassword(){
      var minHistoryDepth=document.getElementById("minHistoryDepth").value;
      var maxHistoryDepth=document.getElementById("maxHistoryDepth").value;
      
      var setLayOutTime=document.getElementById("historyDepth");
      var errorSetLayOutTime=document.getElementById("errorInfo");
      errorSetLayOutTime.innerHTML="";
      var value=trim(setLayOutTime.value);
      var value_sub=value.substring(0,1);
      var isStrongPassword=document.getElementById("isStrongPassword");
      var reg=/^(0|[1-9][0-9]*)$/;
      if(isStrongPassword.checked==true){
        //判断数字是否符合正则（可以为0，第一个数字不能为0，数字中可以有0）
         if(!reg.test(value)){
           errorSetLayOutTime.innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>强密码历史深度无效</b></font>";
       return false;
         }else{
            if(value<Number(minHistoryDepth) || value>Number(maxHistoryDepth)  || value_sub==0){
             errorSetLayOutTime.innerHTML="<font color='red'>提示：</font><font color='#005b96'><b>强密码历史深度只能输入"+minHistoryDepth+"~"+maxHistoryDepth+"</b></font>";
           return false;
            }else{
               return true;
            }
         }
      }else{ 
        return true;  
    }
       
  }

  //确认检查
function check_form(){

  var flag=document.getElementById("flag").value;
  
  if(flag=="default"){
    //alert("设置成功!");
    return true;
  }else{
    var flag_day= day_check();//有效期
    if(!flag_day){
      return false;
    }
    var flag_MaxFreeTime= setMaxFreeTime();//最大空闲时间
    if(!flag_MaxFreeTime){
      return false; 
    }
    var flag_maxErrorCount_timer= check_maxErrorCount_timer('maxErrorCount_timer','errorInfo');//定时输错次数
    if(!flag_maxErrorCount_timer){
      return false;
    }
    var flag_maxErrorCount_stop= check_maxErrorCount_stop('maxErrorCount_stopLogin','errorInfo');//直接锁定输错次数
    if(!flag_maxErrorCount_stop){
       return false;
    }
    var flag_maxtimer= check_maxtimer('lockTime','errorInfo');
    if(!flag_maxtimer){
        return false;
    }
    var flag_HistoryPassword= setHistoryPassword();
    if(!flag_HistoryPassword){
      return false;
    }
    var flag_maxlength = check_maxlength();
     if(!flag_maxlength){
      return false;
    }
    var flag_minlength= check_passwordLen();
    if(!flag_minlength){
      return false;
    }
    
    var flag_submited=false;
	
    if(!flag_submited&&flag_day && flag_MaxFreeTime && flag_maxErrorCount_timer && flag_maxErrorCount_stop && flag_maxtimer && flag_maxlength && flag_minlength && flag_HistoryPassword){
      var inputTag=document.getElementsByTagName("input");
      for(var i=0;i<inputTag.length;i++){
        inputTag[i].disabled="";
      
      }
      var data =$("#setForm").serializeArray();
      console.log(data)
      if (validata() == true ){
      $.ajax({
       async:false,
        type:"post",
        url:"/kinan/SafeSet",
        dataType:"json",
        data:data,
        success:function(info){
          alert(info.msg);
		  flag_submited=!flag_submited;
		 window.location.href="safesetting.html";
        }
      })
}
     //alert("设置成功!");
    }
    //alert("设置失败!");

  }
 
}
