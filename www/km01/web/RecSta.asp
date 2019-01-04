<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7">
<title>State Info</title>
<link href="css/laysta.css" rel="stylesheet" type="text/css" />
<script language="javascript" src="js/common.js"></script>
<script language="javascript" src="js/cookie.js"></script>
<script language="javascript" src="js/dvrStat.js"></script>
<script language="JavaScript" type="text/JavaScript">
<!--
MM_reloadPage(true);
function Click(){
	window.event.returnValue=false;
}
document.oncontextmenu=Click;
//-->
</script>
</head>

<body onload="initVideoTable('Channel ');setOperator();startGet();" onunload="stopGet();">
<iframe src="status.asp" name="status" style="display:none"></iframe> 
<form name="RecSta">
<input type="hidden" name="operator" value="" /><input type="hidden" name="lang" value="en" />
 <table width="840" cellpadding="0" cellspacing="0" class="table">
  <tr>
    <th width="164" height="30"></th>
    <th width="210">Video </th>
    <th width="232">Record </th>
    <th width="232">Alarm </th>
  </tr></table>
 <div id="tb1" style="display:">
 <table id="Page1" width="840" cellpadding="0" cellspacing="0" class="mtable">
 </table>
 </div>
  
  <div id="tb2" style="display:none">
  <table width="840" cellpadding="0" cellspacing="0" class="mtable">
  <tr>
    <td width="164" height="25"><strong>Channel 17</strong></td>
    <td width="210"><label id="v17"></label></td>
    <td width="232"><label id="r17"></label></td>
    <td width="232"><label id="a17"></label></td>
  </tr>
  <tr>
    <td height="25"><strong>Channel 18</strong></td>
    <td><label id="v18"></label></td>
    <td><label id="r18"></label></td>
    <td><label id="a18"></label></td>
    </tr>
  <tr>
    <td height="25"><strong>Channel 19</strong></td>
    <td><label id="v19"></label></td>
    <td><label id="r19"></label></td>
    <td><label id="a19"></label></td>
    </tr>
  <tr>
    <td height="25"><strong>Channel 20</strong></td>
    <td><label id="v20"></label></td>
    <td><label id="r20"></label></td>
    <td><label id="a20"></label></td>
    </tr>
  <tr>
    <td height="25"><strong>Channel 21</strong></td>
    <td><label id="v21"></label></td>
    <td><label id="r21"></label></td>
    <td><label id="a21"></label></td>
    </tr>
  <tr>
    <td height="25"><strong>Channel 22</strong></td>
    <td><label id="v22"></label></td>
    <td><label id="r22"></label></td>
    <td><label id="a22"></label></td>
    </tr>
  <tr>
    <td height="25"><strong>Channel 23</strong></td>
    <td><label id="v23"></label></td>
    <td><label id="r23"></label></td>
    <td><label id="a23"></label></td>
    </tr>
  <tr>
    <td height="25"><strong>Channel 24</strong></td>
    <td><label id="v24"></label></td>
    <td><label id="r24"></label></td>
    <td><label id="a24"></label></td>
    </tr>
  <tr>
    <td height="25"><strong>Channel 25</strong></td>
    <td><label id="v25"></label></td>
    <td><label id="r25"></label></td>
    <td><label id="a25"></label></td>
    </tr>
  <tr>
    <td height="25"><strong>Channel 26</strong></td>
    <td><label id="v26"></label></td>
    <td><label id="r26"></label></td>
    <td><label id="a26"></label></td>
    </tr>
  <tr>
    <td height="25"><strong>Channel 27</strong></td>
    <td><label id="v27"></label></td>
    <td><label id="r27"></label></td>
    <td><label id="a27"></label></td>
    </tr>
  <tr>
    <td height="25"><strong>Channel 28</strong></td>
    <td><label id="v28"></label></td>
    <td><label id="r28"></label></td>
    <td><label id="a28"></label></td>
    </tr>
  <tr>
    <td height="25"><strong>Channel 29</strong></td>
    <td><label id="v29"></label></td>
    <td><label id="r29"></label></td>
    <td><label id="a29"></label></td>
    </tr>
  <tr>
    <td height="25"><strong>Channel 30</strong></td>
    <td><label id="v30"></label></td>
    <td><label id="r30"></label></td>
    <td><label id="a30"></label></td>
    </tr>
  <tr>
    <td height="25"><strong>Channel 31</strong></td>
    <td><label id="v31"></label></td>
    <td><label id="r31"></label></td>
    <td><label id="a31"></label></td>
    </tr>
  <tr>
    <td height="25"><strong>Channel 32</strong></td>
    <td><label id="v32"></label></td>
    <td><label id="r32"></label></td>
    <td><label id="a32"></label></td>
    </tr></table>
  </div>
  <table width="840" cellpadding="0" cellspacing="0" class="bottom">
  <tr style="display:none;">
    <th width="164" height="30"></th>
    <th width="210"><input type="button" name="PageUp" value="PageUp" onclick="onPageUp()" /></th>
    <th width="232"><input type="button" name="PageDown" value="PageDown" onclick="onPageDown()" /></th>
    <th width="232"></th>
  </tr>
  </table>
  <input type="button" onClick="stopGet();" id="btnStop" style="display:none" />
  </form>
</body>
</html>
