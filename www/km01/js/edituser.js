/*
 * @Author: Administrator
 * @Date:   2017-07-31 14:43:12
 * @Last Modified by:   Administrator
 * @Last Modified time: 2017-11-14 18:38:09
 */

'use strict';
$(document).ready(function() {
        var search = location.search.slice(1);
        var searchArr = search.split("&");
        var obj = {};
        for (var i = 0; i < searchArr.length; i++) {
            var temp = searchArr[i].split("=");
            obj[temp[0]] = temp[1]
        }
        var htmls = template("editInformation", obj)
        $("#editIn").html(htmls)
        if (validata() == true ){
        $.ajax({
            async: false,
            type: "get",
            url: "/kinan/SafeSetInfo",
            dataType: "json",
            success: function(info) {
                var htmls = template("hiddenInfo", info.data)
                $(".hiddenIn").html(htmls)
                    // console.log(info.data)
                $("#submit").on("click", function() {
                    var flag_oldpassword = oldpassword_check(); //检查老密码

                    if (!flag_oldpassword) {

                        return false;
                    }
                    //检查第一次密码
                    var flag_firstpassword = newPassword_check();

                    if (!flag_firstpassword) {

                        return false;
                    }

                    var flag_repassword = rpass_check(); //重复密码

                    if (flag_firstpassword && flag_repassword) {
                        //原密码加密
                        var oldpassword = $("#old_password").val()

                        var key = $("#key").val();
                        var oResult = strEnc(oldpassword, key);

                        $("#old_password").prop("value", oResult);
                        var newPassword = $("#new_password").val();
                        var nResult = strEnc(newPassword, key);
                        $("#new_password").prop("value", nResult);
                        var password = $("#password").val();
                        var pResult = strEnc(password, key);
                        $("#password").prop("value", pResult);
                        var data = $("#editIn").serializeArray();
                        $.ajax({
                            type: "post",
                            url: "/kinan/EditUser?" + search,
                            //  dataType:"json",
                            data: data,
                            success: function(data) {
                                window.location.href = "/userlist.html";
                            }
                        })


                    }
                    return false;
                })

            }


        })
}
    })
    //密码的提示语    
var message = "";
var oldPassword = "";

function getMessage() {
    var errorInfo = document.getElementById("errorInfo");
    var strongPassword = document.getElementById("strongPassword").value;
    var minLength = document.getElementById("minLength").value;
    var maxLength_set = document.getElementById("maxLength_set").value;
    var lowerCase = document.getElementById("lowerCase").value;
    var upperCase = document.getElementById("upperCase").value;
    var symbol = document.getElementById("symbol").value;
    var figure = document.getElementById("figure").value;
    var historyDept = document.getElementById("historyDept").value;
    var rMinLength = document.getElementById("rMinLength").value;
    var rMaxLength = document.getElementById("rMaxLength").value;
    var head = "密码至少包含";

    if (strongPassword == 1) {

        if (lowerCase == 1) {
            message += "1个小写字母、";
        }
        if (upperCase == 1) {
            message += "1个大写字母、";
        }
        if (figure == 1) {
            message += "1个数字、";
        }
        if (symbol == 1) {
            message += "1个特殊字符((-@.$!_)、";
        }

        if (lowerCase == 0 && upperCase == 0 && figure == 0 && symbol == 0) {
            message = "密码只能由" + minLength + "-" + maxLength_set + "位的字母、数字或特殊符号(-@.$!_)组成";
        } else {
            message = message.substring(0, message.length - 1);
            message = head + message + ",且由" + minLength + "-" + maxLength_set + "位组成";
        }
        //      document.getElementById("first_password").maxLength=maxLength_set;//赋予最大长度
        //      document.getElementById("password").maxLength=maxLength_set;
    } else {
        message = "密码只能由" + rMinLength + "-" + rMaxLength + "位的字母、数字或特殊字符(-@.$!_)组成";
        //      document.getElementById("first_password").maxLength=rMaxLength;//赋予最大长度
        //      document.getElementById("password").maxLength=rMaxLength;
    }
    errorInfo.innerHTML = "<font color='gray'>" + message + "</font>";
}

//原密码判断
function oldpassword_check() {
    var oldpassword = $("#old_password").val()
    var errorInfo = $("#errorInfo");
    errorInfo.html("");
    if (oldpassword == "") {
        errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>请输入原密码</b></font><br/><br/>");
        return false;
    } else if (oldpassword.length < 8 || oldpassword.length > 16) {
        errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>原密码由8到16位组成</b></font><br/><br/>");
        return false;
    }
    return true;
}
//新密码判断
function newPassword_check() {
    // alert(0)
    var minLength = $("#minLength").val();
    var maxLength_set = $("#maxLength_set").val();
    var newPassword = $("#new_password").val();
    var strongPassword = $("#strongPassword").val();
    var lowerCase = $("#lowerCase").val();
    var upperCase = $("#upperCase").val();
    var symbol = $("#symbol").val();
    var figure = $("#figure").val();
    var head = "密码至少包含";
    //alert(firstValue);
    var errorInfo = $("#errorInfo");
    errorInfo.html("");
    if (newPassword == "") {
        errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>请输入新密码</b></font><br/><br/>");
        // $("#result").prop("value","false");
        // return;
        return false;
    } else if (strongPassword == 1) {
        if (lowerCase == 1) {
            //判断是否有个小写字母，正则匹配
            var reg = /[a-z]/
            if (!reg.test(newPassword)) {
                errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>" + message + "</b></font>");
                return false;
            }

        }
        if (upperCase == 1) {
            //判断是否有个大写字母，正则匹配
            var reg = /[A-Z]/
            if (!reg.test(newPassword)) {
                errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>" + message + "</b></font>");
                return false;
            }
        }
        if (figure == 1) {
            //判断是否有个数字，正则匹配
            var reg = /[0-9]/
            if (!reg.test(newPassword)) {
                errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>" + message + "</b></font>");
                return false;
            }
        }
        if (symbol == 1) {
            //判断是否有个特殊字符，正则匹配(-@.$!_)
            var reg = /[-@.$!_]/
            if (!reg.test(newPassword)) {
                errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>" + message + "</b></font>");
                return false;
            }
        }

        if (lowerCase == 0 && upperCase == 0 && figure == 0 && symbol == 0) {
            message = "密码只能由" + minLength + "-" + maxLength_set + "位的字母、数字或特殊符号(-@.$!_)组成";
        } else {
            message = message.substring(0, message.length - 1);
            message = head + message + ",且由" + minLength + "-" + maxLength_set + "位组成";
        }
        return true;
    } else if (newPassword.length < 8 || newPassword.length > 16) {
        errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>新密码由8到16位组成</b></font><br/><br/>");
        //  $("#result").prop("value","false");
        // return;
        return false;
    }
    return true;
}
//重复密码判断
function rpass_check() {
    var oldpassword = $("#old_password").val()
    var newPassword = $("#new_password").val();
    var password = $("#password").val();
    var errorInfo = $("#errorInfo");
    errorInfo.html("");
    if (password == "") {
        errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>请输入重复密码</b></font><br/><br/>");
        return false;
    } else if (password.length < 8 || password.length > 16) {
        errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>重复密码由8到16位组成</b></font><br/><br/>");
        return false;
    } else if (newPassword != password) {
        errorInfo.html("<font color='red'>提示：</font><font color='#005b96'><b>两次密码不一致</b></font><br/><br/>");
        return false;
    } else {
        //原密码写入历史密码
        $("#historyPassword").prop("value", oldpassword)
        return true;
    }

}
//验证密码是否输入空格
function banInputSapce(e) {
    var keynum;
    if (window.event) // IE
    {
        keynum = e.keyCode
    } else if (e.which) // Netscape/Firefox/Opera
    {
        keynum = e.which
    }
    if (keynum == 32) {
        document.getElementById("errorInfo").innerHTML = "<font color='red'>不能输入空格</font>";
        document.getElementById("result").value = "false";
        return false;
    }
    return true;
}
//页面加载
window.onload = function() {
    getMessage();
}

function goback() {
    window.location.href = "/userlist.html";
}
