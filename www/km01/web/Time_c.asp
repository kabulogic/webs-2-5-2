<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7">
<meta http-equiv="pragma"   content="no-cache" />   
<title>Time</title>
<br />
<link href="css/public.css" rel="stylesheet" type="text/css" />
<link href="css/layout.css" rel="stylesheet" type="text/css" />
<script language="javascript" src="js/common.js"></script>
<script language="javascript" src="js/validate.js"></script>
<script language="javascript" src="js/time.js"></script>
<script>
</script>
</head>
<body onLoad="setOperator();timeIndex()">
<iframe id="hideframe" name="hideframe" style="display:none ;"></iframe>
  <table cellpadding="0" cellspacing="0" class="bttable" width="840">
  <tr class="menu1">
  <td height="25">&nbsp;时间设置</td>
  </tr>
  <tr>
	  <td style="border:1px solid #999" align="center">
	  	<br />
		<form name="timeSetCfg" action="/infinova/timeSetCfg" method="post" target="hideframe">
		<input type="hidden" name="operator" value="" />
			<input type="hidden" name="lang" value="cn" />
			<input type="hidden" name="flag" value="" />
		<table width="100%" cellspacing="0">
		  <tr>
			<td colspan="18" height="10">		</td>
		  </tr>
          <tr>
            <td width="119" height="20" align="left">&nbsp;时区： 
            <%timeGet("NTP");%></td>
            <td colspan="3" align="left"><select style="FONT-SIZE: 9pt; width:450px;" name="tzSelect">
              <option value="0">(GMT-12:00) 日界线西</option>
              <option value="1">(GMT-11:00) 中途岛，萨摩亚群岛</option>
              <option value="2">(GMT-10:00) 夏威夷</option>
              <option value="3">(GMT-09:00) 阿拉斯加</option>
              <option value="4">(GMT-08:00) 蒂华纳，下加利福尼亚州，太平洋时间（美国和加拿大）</option>
              <option value="5">(GMT-07:00) 奇瓦瓦，拉巴斯，马萨特兰，山地时间（美国和加拿大），亚利桑那</option>
              <option value="6">(GMT-06:00) 瓜达拉哈拉，墨西哥城，中美洲</option>
              <option value="7">(GMT-05:00) 波哥大，利马，里奥布郎库，东部时间（美国和加拿大），印地安那州（东部）</option>
              <option value="8">(GMT-04:00) 加拉加斯，拉巴斯，圣地亚哥，马瑙斯</option>
              <option value="9">(GMT-03:30) 纽芬兰</option>
              <option value="10">(GMT-03:00) 巴西利亚，布宜诺斯艾利斯，乔治敦，格陵兰，蒙得维的亚</option>
              <option value="11">(GMT-02:00) 中大西洋</option>
              <option value="12">(GMT-01:00) 佛得角群岛，亚速尔群岛</option>
              <option value="13">(GMT) 格林威治标准时间:都柏林，爱丁堡，伦敦，里斯本，卡萨布兰卡，罗维亚，雷克雅未克</option>
              <option value="14">(GMT+01:00) 阿姆斯特丹，柏林，伯尔尼，罗马，斯德哥尔摩，贝尔格莱德，布拉迪斯拉发，布达佩斯，布鲁塞尔，哥本哈根，马德里，巴黎，萨拉热窝，斯科普里，华沙，萨格勒布，中非西部</option>
              <option value="15">(GMT+02:00) 安曼，贝鲁特，哈拉雷，比勒陀利亚，赫尔辛基，基辅，里加，索非亚，塔林，开罗，明斯克，温得和克，雅典，布加勒斯特，伊斯坦布尔，耶路撒冷</option>
              <option value="16">(GMT+03:00) 巴格达，第比利斯，科威特，利雅得，莫斯科，圣彼得堡，伏尔加格勒，内罗毕</option>
              <option value="17">(GMT+03:30) 德黑兰</option>
              <option value="18">(GMT+04:00) 阿布扎比，埃里温，巴库</option>
              <option value="19">(GMT+04:30) 喀布尔</option>
              <option value="20">(GMT+05:00) 叶卡捷琳堡，伊斯兰堡，卡拉奇，塔什干</option>
              <option value="21">(GMT+05:30) 马德拉斯，加尔各答，孟买，新德里，斯里哈亚华登尼普拉</option>
              <option value="22">(GMT+05:45) 加德曼都</option>
              <option value="23">(GMT+06:00) 阿拉木图，新西伯利亚，阿斯塔纳，达卡</option>
              <option value="24">(GMT+06:30) 仰光</option>
              <option value="25">(GMT+07:00) 克拉斯诺亚尔斯克，曼谷，河内，雅加达</option>
              <option value="26" selected="selected">(GMT+08:00) 北京，重庆，香港特别行政区，乌鲁木齐，吉隆坡，新加坡，台北，伊尔库茨克，乌兰巴图</option>
              <option value="27">(GMT+09:00) 大坂，札幌，东京，汉城，雅库茨克</option>
              <option value="28">(GMT+09:30) 阿德莱德，达尔文</option>
              <option value="29">(GMT+10:00) 布里斯班，符拉迪沃斯托克，关岛，摩尔兹比港，霍巴特，詹培拉，摩尔本，悉尼</option>
              <option value="30">(GMT+11:00) 马加丹，所罗门群岛</option>
              <option value="31">(GMT+12:00) 奥克兰，惠灵顿，斐济，堪察加半岛，马绍尔群岛</option>
              <option value="32">(GMT+13:00) 努库阿洛法</option>
            </select></td>
            <td width="234">&nbsp;</td>
          </tr>
          <tr>
            <td height="30">&nbsp;</td>
            <td width="24" align="left" valign="bottom"><input name="cbDaylight" type="checkbox" id="cbDaylight" onclick="" value="0" /></td>
            <td width="261" align="left" valign="bottom">开启夏时制</td>
            <td width="186" align="left" valign="bottom"><input name="tzbutton" type="submit" class="myButton" value="设 置" onclick="setTimezone()"/></td>
            <td align="left">&nbsp;</td>
          </tr>
		  <tr>
			<td colspan="18" height="10">		</td>
		  </tr>
        </table>
		<br />
	  <table width="100%" cellspacing="0">
        <tr>
          <td colspan="18" height="10"></td>
        </tr>
        <tr>
          <td width="120" height="20" align="left">&nbsp;服务器时间：
            <iframe src="GetTime.asp" name="timeFrame" style="display:none"></iframe> </td>
          <td colspan="2" align="left"><input name="PC_Time" type="text" size="30" disabled="disabled" value="" />
          <input  name="localtime" type="hidden" value="0" size="18" maxlength="18"></td>
          <td width="98" align="left"><input name="CheckTime" type="button" class="myButton" onclick="setLocalTime();" value="校&nbsp;时" /></td>
          <td width="321" align="left">注：将服务器时间校对为本地电脑时间</td>
        </tr>
        
        
        <tr>
          <td colspan="18" height="10"></td>
        </tr>
      </table>
	  <br />
	  <table width="100%" cellspacing="0">
        <tr>
          <td colspan="16" height="10"></td>
        </tr>
        <tr>
          <td width="120" height="20" align="left"><input type="checkbox" name="chkntp" value="ntp" onclick="NTPChecked();" />
开启NTP 服务器</td>
          <td colspan="2">&nbsp;</td>
          </tr>
        <tr>
          <td height="20" align="left">&nbsp;服务器IP：</td>
          <td width="290" align="left"><input name="ntpIP" type="text" size="18" maxlength="15" onchange="checkIP(this);" /></td>
          <td width="418" align="left"><input name="CheckTime2" type="button" class="myButton" onclick="setNTP();" value="设 置" /></td>
        </tr>
        <tr>
          <td colspan="16" height="10"></td>
        </tr>
      </table>
	  <br />
	  </form>
	</td>
  </tr>
  </table>
</body>
</html>
