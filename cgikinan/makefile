all:../www/km01/cgi-bin/auditlog.cgi ../www/km01/cgi-bin/remoteupgrade.cgi \
	../www/km01/cgi-bin/login.cgi ../www/km01/cgi-bin/ping.cgi ../www/km01/cgi-bin/v3ping.cgi
.PHONY : clean 
../www/km01/cgi-bin/auditlog.cgi : cgiauditlog.o cgic.o ../kinan/websSession.o ../des/des.o authenBySessionid.o 
	cc -o ../www/km01/cgi-bin/auditlog.cgi cgiauditlog.o cgic.o ../kinan/websSession.o ../des/des.o authenBySessionid.o  
../www/km01/cgi-bin/remoteupgrade.cgi : cgiupload.o cgic.o ../kinan/websSession.o ../des/des.o authenBySessionid.o
	cc -o ../www/km01/cgi-bin/remoteupgrade.cgi cgiupload.o cgic.o ../kinan/websSession.o ../des/des.o authenBySessionid.o
../www/km01/cgi-bin/login.cgi : cgilogin.o cgic.o ../kinan/websSession.o ../des/des.o
	cc -o ../www/km01/cgi-bin/login.cgi cgilogin.o cgic.o ../kinan/websSession.o ../des/des.o 
../www/km01/cgi-bin/ping.cgi : cgiping.o cgic.o ../kinan/websSession.o ../des/des.o authenBySessionid.o
	cc -o ../www/km01/cgi-bin/ping.cgi cgiping.o cgic.o ../kinan/websSession.o ../des/des.o authenBySessionid.o
../www/km01/cgi-bin/v3ping.cgi : v3ping.o cgic.o ../kinan/websSession.o ../des/des.o authenBySessionid.o ping.o
	cc -o ../www/km01/cgi-bin/v3ping.cgi v3ping.o cgic.o ../kinan/websSession.o ../des/des.o authenBySessionid.o ping.o
ping.o : ping.h
cgiauditlog.o : cgic.h ../kinan/websSession.h ../kmain/kingAPI.h authenBySessionid.h
cgic.o : cgic.h 
../kinan/websSession.o : ../kinan/websSession.h 
../des/des.o : ../des/tables.h 
authenBySessionid.o : authenBySessionid.h

clean : 
	rm $(all) *.o
