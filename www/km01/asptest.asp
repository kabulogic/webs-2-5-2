<html>
<!- Copyright (c) Go Ahead Software Inc., 1999-2010. All Rights Reserved. ->
<head>
<title>ASP Test Page</title>
<link rel="stylesheet" href="/style/normal_ws.css" type="text/css">
<% language=javascript %>
function uploadFileSubmit()
{
	//  alert(document.getElementById("document.softupdate"));  
	    return;  

}
</head>

<body>

<h1>ASP / JavaScript&#153; Test</h1>
<h2>Expanded ASP data: <% aspTest("Peter Smith", "112 Merry Way"); %></h2>

<P>
<% var z; \
   for (z=0; z<5; z=z+1) \
     { \
     if (z<=2) \
		write(z+" is less than 3<br>"); \
     else if (z==3) \
		write(z+" is equal to 3<br>"); \
     else \
		write(z+" is greater than 3<br>"); \
     } \
%>
</P>

<span style="color:#3333ff;"><!-- added start for test upload file by gyr 2011.10.15 -->  
<h1>GoForm upload file test</h1>  
 <form id="upload-form" action="/goform/formUploadFileTest" method="post" enctype="multipart/form-data" >
 　　　<input type="file" id="upload" name="file" /> <br />
 　　　<input type="submit" value="Upload" />
    </form>

<!-- added end for test upload file by gyr 2011.10.15 -->  
  
</span>  

</body>
</html>
