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
  <td height="25">&nbsp;Time Settings </td>
  </tr>
  <tr>
	  <td style="border:1px solid #999" align="center">
	  	<br />
		<form name="timeSetCfg" action="/infinova/timeSetCfg" method="post" target="hideframe">
		<input type="hidden" name="operator" value="" />
			<input type="hidden" name="lang" value="en" />
			<input type="hidden" name="flag" value="" />
		<table width="100%" cellspacing="0">
		  <tr>
			<td colspan="18" height="10">		</td>
		  </tr>
          <tr>
            <td width="119" height="20" align="left">Time Zone:
  <%timeGet("NTP");%></td><td colspan="3" align="left"><select style="FONT-SIZE: 9pt; width:450px;" name="tzSelect">
              <option value="0">(GMT-12:00) International Date Line West</option>
              <option value="1">(GMT-11:00) Midway Island, Samoa</option>
              <option value="2">(GMT-10:00) Hawaii</option>
              <option value="3">(GMT-09:00) Alaska</option>
              <option value="4">(GMT-08:00) Pacific Time(US &amp; Canada); Tijuana</option>
              <option value="5">(GMT-07:00) Arizona, Chihuahua, La Paz, Mazatlan, Mountain Time(US &amp; Canada)</option>
              <option value="6">(GMT-06:00) Central America, Central Time(US &amp; Canada), Guadalajara, Mexico City, Monterrey, Saskatchewan</option>
              <option value="7">(GMT-05:00) Bogota, Lima, Quito, Eastern Time(US &amp; Canada), Indiana(East)</option>
              <option value="8">(GMT-04:00) Atlantic Time(Canada), Caracas, La Paz, Santiago</option>
              <option value="9">(GMT-03:30) Newfoundland</option>
              <option value="10">(GMT-03:00) Brasilia, Buenos Aires, Georgetown, Greenland</option>
              <option value="11">(GMT-02:00) Mid-Atlantic</option>
              <option value="12">(GMT-01:00) Azores, Cape Verde Is.</option>
              <option value="13">(GMT) Casablanca, Monrovia, Greenwich Mean Time; Dublin, Edinburgh, Lisbon, London</option>
              <option value="14">(GMT+01:00) Amsterdam, Berlin, Bern, Rome, Stockholm, Vienna, Belgrade, Bratislava, Budapest, Ljubljana, Prague, Brussels, Copenhagen, Madrid, Paris, Sarajevo, Skopje, Warsaw, Zagreb, West Central Africa</option>
              <option value="15">(GMT+02:00) Athens, Beirut, Istanbul, Minsk, Bucharest, Cairo, Harare, Pretoria, Helsinki, Kyiv, Riga, Sofia, Tallinn, Vilnius, Jerusalem</option>
              <option value="16">(GMT+03:00) Baghdad, Kuwait, Riyadh, Moscow, St. Petersburg, Volgograd, Nairobi</option>
              <option value="17">(GMT+03:30) Tehran</option>
              <option value="18">(GMT+04:00) Abu Dhabi, Muscat, Baku, Tbilisi, Yerevan</option>
              <option value="19">(GMT+04:30) Kabul</option>
              <option value="20">(GMT+05:00) Ekaterinburg, Islamabad, Karachi, Tashkent</option>
              <option value="21">(GMT+05:30) Chennai, Kolkata, Mumbai, New Delhi</option>
              <option value="22">(GMT+05:45) Kathmandu</option>
              <option value="23">(GMT+06:00) Almaty, Novosibirsk, Astana, Dhaka, Sri Jayawardenepura</option>
              <option value="24">(GMT+06:30) Rangoon</option>
              <option value="25">(GMT+07:00) Bangkok, Hanoi, Jakarta, Krasnoyarsk</option>
              <option value="26" selected="selected">(GMT+08:00) Beijing, Chongqing, Hong Kong, Urumqi, Irkutsk, Ulaan Bataar, Kuala Lumpur, Singapore, Perth, Taipei</option>
              <option value="27">(GMT+09:00) Osaka, Sapporo, Tokyo, Seoul, Yakutsk</option>
              <option value="28">(GMT+09:30) Adelaide, Darwin</option>
              <option value="29">(GMT+10:00) Brisbane, Canberra, Melbourne, Sydney, Guam, Pot Moresby, Hobart, Vladivostok</option>
              <option value="30">(GMT+11:00) Magadan, Solomon Is., New Caledonia</option>
              <option value="31">(GMT+12:00) Auckland, Wellington, Fiji, Kamchatka, Marshall Is.</option>
              <option value="32">(GMT+13:00) Nuku’alofa</option>
            </select></td>
            <td width="234">&nbsp;</td>
          </tr>
          <tr>
            <td height="30">&nbsp;</td>
            <td width="24" align="left" valign="bottom"><input name="cbDaylight" type="checkbox" id="cbDaylight" onclick="" value="0" /></td>
            <td width="353" align="left" valign="bottom">Enable daylight saving time</td>
            <td width="94" align="left" valign="bottom"><input name="tzbutton" type="submit" class="myButton" value="Set" onclick="setTimezone()"/></td>
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
          <td width="119" height="20" align="left">&nbsp;Server Time ：
            <iframe src="GetTime.asp" name="timeFrame" style="display:none"></iframe> </td>
          <td colspan="2" align="left"><input name="PC_Time" type="text" size="30" disabled="disabled" value="" />
          <input  name="localtime" type="hidden" value="0" size="18" maxlength="18"></td>
          <td width="94" align="left"><input name="CheckTime" type="button" class="myButton" onclick="setLocalTime();" value="Set" /></td>
          <td width="234" align="left">Note:Adjust Server time to PC time </td>
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
NTP Enable</td>
          <td colspan="2">&nbsp;</td>
          </tr>
        <tr>
          <td height="20" align="left">&nbsp;Server IP: </td>
          <td width="380" align="left"><input name="ntpIP" type="text" size="18" maxlength="15" onchange="checkIP(this);" /></td>
          <td width="328" align="left"><input name="CheckTime2" type="button" class="myButton" onclick="setNTP();" value="Set" /></td>
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
