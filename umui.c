/*
 * umui.c -- User Management GoForm Processing
 *
 * Copyright (c) GoAhead Software Inc., 1995-2010. All Rights Reserved.
 *
 * See the file "license.txt" for usage and redistribution license requirements
 *
 */

/******************************** Description *********************************/

/*
 *	This module provides GoForm functions for User management
 */

/********************************* Includes ***********************************/

#include	"wsIntrn.h"
#include	"um.h"
/********************************* Defines ************************************/

#define		NONE_OPTION		T("<NONE>")
#define		MSG_START		T("<body><h2>")
#define		MSG_END			T("</h2></body>")

/**************************** Forward Declarations ****************************/

//static void		formAddUser(webs_t wp, char_t *path, char_t *query);
//static void		formDeleteUser(webs_t wp, char_t *path, char_t *query);
static void		formDisplayUser(webs_t wp, char_t *path, char_t *query);
static int		aspGenerateUserList(int eid, webs_t wp, 
									int argc, char_t **argv);

static void		formAddGroup(webs_t wp, char_t *path, char_t *query);
static void		formDeleteGroup(webs_t wp, char_t *path, char_t *query);
static int		aspGenerateGroupList(int eid, webs_t wp, 
									 int argc, char_t **argv);

static void		formAddAccessLimit(webs_t wp, char_t *path, char_t *query);
static void		formDeleteAccessLimit(webs_t wp, char_t *path, char_t *query);
static int		aspGenerateAccessLimitList(int eid, webs_t wp, 
										   int argc, char_t **argv);

static int		aspGenerateAccessMethodList(int eid, webs_t wp, 
											int argc, char_t **argv);
static int		aspGeneratePrivilegeList(int eid, webs_t wp, 
										 int argc, char_t **argv);

static void		formSaveUserManagement(webs_t wp, char_t *path, char_t *query);
static void		formLoadUserManagement(webs_t wp, char_t *path, char_t *query);

static void		websMsgStart(webs_t wp);
static void		websMsgEnd(webs_t wp);
/*==================== my test===================*/
//static void 	formAddUserGroup(webs_t wp, char_t *path, char_t *query);
//static int 		aspShowGroupName(int eid, webs_t wp, int argc, char_t **argv);
/*********************************** Code *************************************/
/*
 *	Set up the User Management form handlers
 */

void formDefineUserMgmt(void)
{
//	websAspDefine(T("MakeGroupList"), aspGenerateGroupList);
	websAspDefine(T("MakeUserList"), aspGenerateUserList);
	websAspDefine(T("MakeAccessLimitList"), aspGenerateAccessLimitList);
	websAspDefine(T("MakeAccessMethodList"), aspGenerateAccessMethodList);
	websAspDefine(T("MakePrivilegeList"), aspGeneratePrivilegeList);

//	websFormDefine(T("AddUser"), formAddUser);
//	websFormDefine(T("DeleteUser"), formDeleteUser);
	websFormDefine(T("DisplayUser"), formDisplayUser);
//	websFormDefine(T("AddGroup"), formAddGroup);
	websFormDefine(T("DeleteGroup"), formDeleteGroup);
	websFormDefine(T("AddAccessLimit"), formAddAccessLimit);
	websFormDefine(T("DeleteAccessLimit"), formDeleteAccessLimit);

	websFormDefine(T("SaveUserManagement"), formSaveUserManagement);
	websFormDefine(T("LoadUserManagement"), formLoadUserManagement);
	/*=============== my test =================*/
//	websFormDefine(T("addUserGroup"),formAddUserGroup);

//	websAspDefine(T("showUserGroupName"),aspShowGroupName);
}

/******************************************************************************/
#if 0
/*
 *  Add a user
 */

static void formAddUser(webs_t wp, char_t *path, char_t *query)
{
	char_t	*userid, *pass1, *pass2, *group, *enabled, *ok;
	bool_t bDisable;
	int	nCheck;

	a_assert(wp);

	userid = websGetVar(wp, T("user"), T("")); 
	pass1 = websGetVar(wp, T("password"), T("")); 
	pass2 = websGetVar(wp, T("passconf"), T("")); 
	group = websGetVar(wp, T("group"), T("")); 
	enabled = websGetVar(wp, T("enabled"), T("")); 
	ok = websGetVar(wp, T("ok"), T("")); 

	websHeader(wp);
	websMsgStart(wp);

	if (gstricmp(ok, T("ok")) != 0) {
		websWrite(wp, T("Add User Cancelled"));
	} else if (gstrcmp(pass1, pass2) != 0) {
		websWrite(wp, T("Confirmation Password did not match."));
	} else {
		if (enabled && *enabled && (gstrcmp(enabled, T("on")) == 0)) {
			bDisable = FALSE;
		} else {
			bDisable = TRUE;
		}

		nCheck = umAddUser(userid, pass1, group, 0, bDisable);
		if (nCheck != 0) {
			char_t * strError;

			switch (nCheck) {
			case UM_ERR_DUPLICATE:
				strError = T("User already exists.");
				break;

			case UM_ERR_BAD_NAME:
				strError = T("Invalid user name.");
				break;

			case UM_ERR_BAD_PASSWORD:
				strError = T("Invalid password.");
				break;

			case UM_ERR_NOT_FOUND:
				strError = T("Invalid or unselected group.");
				break;

			default:
				strError = T("Error writing user record.");
				break;
			}

			websWrite(wp, T("Unable to add user, \"%s\".  %s"),
				userid, strError);
		} else {
			websWrite(wp, T("User, \"%s\" was successfully added."),
				userid);
		}
	}

	websMsgEnd(wp);
	websFooter(wp);
	websDone(wp, 200);
}
#endif
/******************************************************************************/
/*
 *  Delete a user
 */
#if 0
static void formDeleteUser(webs_t wp, char_t *path, char_t *query)
{
	char_t	*userid, *ok;

	a_assert(wp);

	userid = websGetVar(wp, T("user"), T("")); 
	ok = websGetVar(wp, T("ok"), T("")); 

	websHeader(wp);
	websMsgStart(wp);

	if (gstricmp(ok, T("ok")) != 0) {
		websWrite(wp, T("Delete User Cancelled"));
	} else if (umUserExists(userid) == FALSE) {
		websWrite(wp, T("ERROR: User \"%s\" not found"), userid);
	} else if (umGetUserProtected(userid)) {
		websWrite(wp, T("ERROR: User, \"%s\" is delete-protected."), userid);
	} else if (umDeleteUser(userid) != 0) {
		websWrite(wp, T("ERROR: Unable to delete user, \"%s\" "), userid);
	} else {
		websWrite(wp, T("User, \"%s\" was successfully deleted."), userid);
	}

	websMsgEnd(wp);
	websFooter(wp);
	websDone(wp, 200);
}
#endif
/******************************************************************************/
/*
 *  Display the user info
 */

static void formDisplayUser(webs_t wp, char_t *path, char_t *query)
{
	char_t	*userid, *ok, *temp;
	bool_t	enabled;

	a_assert(wp);

	userid = websGetVar(wp, T("user"), T("")); 
	ok = websGetVar(wp, T("ok"), T("")); 

	websHeader(wp);
	websWrite(wp, T("<body>"));

	if (gstricmp(ok, T("ok")) != 0) {
		websWrite(wp, T("Display User Cancelled"));
	} else if (umUserExists(userid) == FALSE) {
		websWrite(wp, T("ERROR: User <b>%s</b> not found.\n"), userid);
	} else {
		websWrite(wp, T("<h2>User ID: <b>%s</b></h2>\n"), userid);
		temp = umGetUserGroup(userid);
		websWrite(wp, T("<h3>User Group: <b>%s</b></h3>\n"), temp);
		enabled = umGetUserEnabled(userid);
		websWrite(wp, T("<h3>Enabled: <b>%d</b></h3>\n"), enabled);
	}

	websWrite(wp, T("</body>\n"));
	websFooter(wp);
	websDone(wp, 200);
}


/******************************************************************************/
/*
 *  Generate HTML to create a list box containing the users
 */

static int aspGenerateUserList(int eid, webs_t wp, int argc, char_t **argv)
{
	char_t	*userid;
	int		row, nBytesSent, nBytes;

	a_assert(wp);

	nBytes = websWrite(wp, 
		T("<SELECT NAME=\"user\" SIZE=\"3\" TITLE=\"Select a User\">"));
	row = 0;
	userid = umGetFirstUser();
	nBytesSent = 0;

	while (userid && (nBytes > 0)) {
		nBytes = websWrite(wp, T("<OPTION VALUE=\"%s\">%s\n"), 
			userid, userid);
		userid = umGetNextUser(userid);
		nBytesSent += nBytes;
	}

	nBytesSent += websWrite(wp, T("</SELECT>"));

	return nBytesSent;
}
#if 0
/*========================== Add userGroup ==============================*/
static void formAddUserGroup(webs_t wp, char_t *path, char_t *query)
{
	printf("====this is formAddGroup ========\n");
	char_t			*group, *userGroupName, *portAccess, *userManager, *diviceSetting, *securityManager, *systemMaintenance, *ok, *pChar;
	int				nCheck, nBytes, nBytesSent;
	short			priv;
	bool_t			bDisable, bportA, buserM, bdiviceS, bsecurityM, bsystemM;

	a_assert(wp);

	userGroupName = websGetVar(wp, T("userGroupName"), T("")); 
	portAccess = websGetVar(wp, T("portAccess"), T(""));
	userManager = websGetVar(wp, T("userManager"), T("")); 
	diviceSetting = websGetVar(wp, T("diviceSetting"), T("")); 
	securityManager = websGetVar(wp, T("securityManager"), T(""));
	systemMaintenance = websGetVar(wp, T("systemMaintenance"), T(""));
	ok = websGetVar(wp, T("ok"), T("")); 
	
	printf(" userGroupName:%s\n portAccess:%s\n userManager:%s\n diviceSetting:%s\n securityManager:%s\n systemMaintenance:%s\n",
			userGroupName,portAccess,userManager,diviceSetting,securityManager,systemMaintenance);

	if (gstricmp(ok, T("ok")) != 0) {
		websWrite(wp, T("Add Group Cancelled."));
	} else
	if ((userGroupName == NULL) || (*userGroupName == 0)) {
		printf("No Group Name was entered.\n");
	} else if (umGroupExists(userGroupName)) {
		websWrite(wp, T("HTTP/1.0 200 OK\n"));
		websWrite(wp, T("Pragma: no-cache\n"));
		websWrite(wp, T("Cache-control: no-cache\n"));
		websWrite(wp, T("Content-Type: text/html\n"));
		websWrite(wp, T("\n"));
		websWrite(wp, T("{\"ERROR\": \"%s is already exists\"}"), userGroupName);
		websDone(wp, 200);
	} else {

		if (portAccess && *portAccess && (gstrcmp(portAccess, T("1")) == 0)) {
			bportA = TRUE;
		} else {
			bportA = FALSE;
		}

		if (userManager && *userManager && (gstrcmp(userManager, T("1")) == 0)) {
			buserM = TRUE;
		} else {
			buserM = FALSE;
		}

		if (diviceSetting && *diviceSetting && (gstrcmp(diviceSetting, T("1")) == 0)) {
			bdiviceS = TRUE;
		} else {
			bdiviceS = FALSE;
		}

		if (securityManager && *securityManager && (gstrcmp(securityManager, T("1")) == 0)) {
			bsecurityM = TRUE;
		} else {
			bsecurityM = FALSE;
		}

		if (systemMaintenance && *systemMaintenance && (gstrcmp(systemMaintenance, T("1")) == 0)) {
			bsystemM = TRUE;
		} else {
			bsystemM = FALSE;
		}

		nCheck = umAddGroup(userGroupName, bportA, buserM, bdiviceS, bsecurityM, bsystemM);
		if (nCheck != 0) {
			printf("Unable to add group, \"%s\", code: %d \n",
					userGroupName, nCheck);
		} else {
			printf("Group, \"%s\" was successfully added.\n", 
					userGroupName);
		}
		if (umCommit(NULL) != 0) {
			printf("ERROR: Unable to save user configuration.\n");
		} else {
			printf("User configuration was saved successfully.\n");
			websWrite(wp, T("HTTP/1.0 200 OK\n"));
			websWrite(wp, T("Pragma: no-cache\n"));
			websWrite(wp, T("Cache-control: no-cache\n"));
			websWrite(wp, T("Content-Type: text/html\n"));
			websWrite(wp, T("\n"));
			websWrite(wp, T("{\"SUCCESS\": \"create user group successful\"}"), userGroupName);
			websDone(wp, 200);
		}
	}
/*	send the user group name to the browser*/

	group = umGetFirstGroup();
	while (group && (nBytes > 0)) {
		nBytes = websWrite(wp, T("%s "), group);
		group = umGetNextGroup(group);
		nBytesSent += nBytes;
	}
	printf("nBytesSent:%d\n",nBytesSent);

}
#endif

/******************************************************************************/
/*
 *  Delete a group
 */

static void formDeleteGroup(webs_t wp, char_t *path, char_t *query)
{
	char_t	*group, *ok;

	a_assert(wp);

	group = websGetVar(wp, T("group"), T("")); 
	ok = websGetVar(wp, T("ok"), T("")); 

	websHeader(wp);
	websMsgStart(wp);

	if (gstricmp(ok, T("ok")) != 0) {
		websWrite(wp, T("Delete Group Cancelled."));
	} else if ((group == NULL) || (*group == '\0')) {
		websWrite(wp, T("ERROR: No group was selected."));
	} else if (umGetGroupProtected(group)) {
		websWrite(wp, T("ERROR: Group, \"%s\" is delete-protected."), group);
	} else if (umGetGroupInUse(group)) {
		websWrite(wp, T("ERROR: Group, \"%s\" is being used."),	group);
	} else if (umDeleteGroup(group) != 0) {
		websWrite(wp, T("ERROR: Unable to delete group, \"%s\" "), group);
	} else {
		websWrite(wp, T("Group, \"%s\" was successfully deleted."), group);
	}

	websMsgEnd(wp);
	websFooter(wp);
	websDone(wp, 200);
}

/******************************************************************************/
#if 0
/*============================= show group name =============================*/
static int aspShowGroupName(int eid, webs_t wp, int argc, char_t ** argv)
{
	printf("======||aspShowGroupName||========\n");
	char_t *userGroupName;
	int portAccess, userManager, diviceSetting, securityManager, systemMaintenance;
	int nBytes, nBytesSent, row;
	nBytes = 1;
	nBytesSent = 0;
	a_assert(wp);

	userGroupName = umGetFirstGroup();
//	printf("firstname:%s\n",userGroupName);

	if(userGroupName && (nBytes > 0)){
		websWrite(wp, T("{list:["));
	}
	while (userGroupName && (nBytes > 0)){
		//find the userGroupName which stay in 
		row = umSearchStr(userGroupName);
		//according the row read the data
		portAccess = umReadInt("portAccess", row);
		userManager = umReadInt("userManager", row);
		diviceSetting = umReadInt("diviceSetting", row);
		securityManager = umReadInt("securityManager", row);
		systemMaintenance = umReadInt("systemMaintenance", row);

		nBytes = websWrite(wp, T("{\"userGroupName\":\"%s\",\"portAccess\":\"%d\",\"userManager\":\"%d\",\"diviceSetting\":\"%d\",\"securityManager\":\"%d\",\"systemMaintenance\":\"%d\"}"),userGroupName,portAccess,userManager,diviceSetting,securityManager,systemMaintenance);
		userGroupName = umGetNextGroup(userGroupName);
//		printf("nextname:%s\n",userGroupName);
		nBytesSent += nBytes;
		if(userGroupName && (nBytes > 0)){
			websWrite(wp, T(","));
		}
	}
	if(nBytesSent > 0){
		websWrite(wp, T("]}"));
	}

/*  change column value (int)
	row = umSearchStr(userGroupName);
	umWriteInt("systemMaintenance", row, 1);
	umCommit(NULL);
	systemMaintenance = umReadInt("systemMaintenance", row);
	printf("system:%d\n",systemMaintenance);
*/
/* 	change the table name
	row = umSearchStr(userGroupName);
	umWriteStr("name", row, "fffk");
	umCommit(NULL);
*/
/* 	delete the row
	row = umSearchStr(userGroupName);
	umDeleteRow(row);
	umCommit(NULL);
*/
	return 0;
}
#endif
/******************************************************************************/
/*
 *  Add an access limit
 */

static void formAddAccessLimit(webs_t wp, char_t *path, char_t *query)
{
	char_t			*url, *method, *group, *secure, *ok;
	int				nCheck;
	accessMeth_t	am;
	short			nSecure;

	a_assert(wp);

	url = websGetVar(wp, T("url"), T("")); 
	group = websGetVar(wp, T("group"), T("")); 
	method = websGetVar(wp, T("method"), T("")); 
	secure = websGetVar(wp, T("secure"), T("")); 
	ok = websGetVar(wp, T("ok"), T("")); 

	websHeader(wp);
	websMsgStart(wp);

	if (gstricmp(ok, T("ok")) != 0) {
		websWrite(wp, T("Add Access Limit Cancelled."));
	} else if ((url == NULL) || (*url == 0)) {
		websWrite(wp, T("ERROR:  No URL was entered."));
	} else if (umAccessLimitExists(url)) {
		websWrite(wp, T("ERROR:  An Access Limit for [%s] already exists."),
			url);
	} else {
		if (method && *method) {
			am = (accessMeth_t) gatoi(method);
		} else {
			am = AM_FULL;
		}

		if (secure && *secure) {
			nSecure = (short) gatoi(secure);
		} else {
			nSecure = 0;
		}

		nCheck = umAddAccessLimit(url, am, nSecure, group);
		if (nCheck != 0) {
			websWrite(wp, T("Unable to add Access Limit for [%s]"),	url);
		} else {
			websWrite(wp, T("Access limit for [%s], was successfully added."),
				url);
		}
	}

	websMsgEnd(wp);
	websFooter(wp);
	websDone(wp, 200);
}

/******************************************************************************/
/*
 *  Delete an Access Limit
 */

static void formDeleteAccessLimit(webs_t wp, char_t *path, char_t *query)
{
	char_t	*url, *ok;

	a_assert(wp);

	url = websGetVar(wp, T("url"), T("")); 
	ok = websGetVar(wp, T("ok"), T("")); 

	websHeader(wp);
	websMsgStart(wp);

	if (gstricmp(ok, T("ok")) != 0) {
		websWrite(wp, T("Delete Access Limit Cancelled"));
	} else if (umDeleteAccessLimit(url) != 0) {
		websWrite(wp, T("ERROR: Unable to delete Access Limit for [%s]"), 
			url);
	} else {
		websWrite(wp, T("Access Limit for [%s], was successfully deleted."), 
			url);
	}

	websMsgEnd(wp);
	websFooter(wp);
	websDone(wp, 200);
}

/******************************************************************************/
/*
 *  Generate HTML to create a list box containing the access limits
 */

static int aspGenerateAccessLimitList(int eid, webs_t wp, 
									  int argc, char_t **argv)
{
	char_t	*url;
	int		row, nBytesSent, nBytes;

	a_assert(wp);

	row = nBytesSent = 0;
	url = umGetFirstAccessLimit();
	nBytes = websWrite(wp, 
		T("<SELECT NAME=\"url\" SIZE=\"3\" TITLE=\"Select a URL\">"));

	while (url && (nBytes > 0)) {
		nBytes = websWrite(wp, T("<OPTION VALUE=\"%s\">%s\n"), url, url);
		url = umGetNextAccessLimit(url);
		nBytesSent += nBytes;
	}

	nBytesSent += websWrite(wp, T("</SELECT>"));

	return nBytesSent;
}

/******************************************************************************/
/*
 *  Generate HTML to create a list box containing the access methods
 */

static int aspGenerateAccessMethodList(int eid, webs_t wp, 
									   int argc, char_t **argv)
{
	int		nBytes;

	a_assert(wp);

	nBytes = websWrite(wp, 
		T("<SELECT NAME=\"method\" SIZE=\"3\" TITLE=\"Select a Method\">"));
	nBytes += websWrite(wp, T("<OPTION VALUE=\"%d\">FULL ACCESS\n"), 
		AM_FULL);
	nBytes += websWrite(wp, T("<OPTION VALUE=\"%d\">BASIC ACCESS\n"), 
		AM_BASIC);
	nBytes += websWrite(wp, T("<OPTION VALUE=\"%d\" SELECTED>DIGEST ACCESS\n"), 
		AM_DIGEST);
	nBytes += websWrite(wp, T("<OPTION VALUE=\"%d\">NO ACCESS\n"), 
		AM_NONE);
	nBytes += websWrite(wp, T("</SELECT>"));

	return nBytes;
}
/******************************************************************************/
/*
 *  Generate HTML to create a list box containing privileges
 */

static int aspGeneratePrivilegeList(int eid, webs_t wp, 
									int argc, char_t **argv)
{
	int		nBytes;

	a_assert(wp);

	nBytes = websWrite(wp, T("<SELECT NAME=\"privilege\" SIZE=\"3\" "));
	nBytes += websWrite(wp, T("MULTIPLE TITLE=\"Choose Privileges\">"));
	nBytes += websWrite(wp, T("<OPTION VALUE=\"%d\">READ\n"), PRIV_MANAGER);
	nBytes += websWrite(wp, T("<OPTION VALUE=\"%d\">EXECUTE\n"), PRIV_DIVICE);
	nBytes += websWrite(wp, T("<OPTION VALUE=\"%d\">ADMINISTRATE\n"), 
		PRIV_SYSTEM);
	nBytes += websWrite(wp, T("</SELECT>"));

	return nBytes;
}

/******************************************************************************/
/*
 *  Save the user management configuration to a file
 */

static void formSaveUserManagement(webs_t wp, char_t *path, char_t *query)
{
	char_t	*ok;

	a_assert(wp);

	ok = websGetVar(wp, T("ok"), T("")); 

	websHeader(wp);
	websMsgStart(wp);

	if (gstricmp(ok, T("ok")) != 0) {
		websWrite(wp, T("Save Cancelled."));
	} else if (umCommit(NULL) != 0) {
		websWrite(wp, T("ERROR: Unable to save user configuration."));
	} else {
		websWrite(wp, T("User configuration was saved successfully."));
	}

	websMsgEnd(wp);
	websFooter(wp);
	websDone(wp, 200);
}

/******************************************************************************/
/*
 *  Load the user management configuration from a file
 */

static void formLoadUserManagement(webs_t wp, char_t *path, char_t *query)
{
	char_t	*ok;

	a_assert(wp);

	ok = websGetVar(wp, T("ok"), T("")); 

	websHeader(wp);
	websMsgStart(wp);

	if (gstricmp(ok, T("ok")) != 0) {
		websWrite(wp, T("Load Cancelled."));
	} else if (umRestore(NULL) != 0) {
		websWrite(wp, T("ERROR: Unable to load user configuration."));
	} else {
		websWrite(wp, T("User configuration was re-loaded successfully."));
	}

	websMsgEnd(wp);
	websFooter(wp);
	websDone(wp, 200);
}

/******************************************************************************/
/*
 *  Message start and end convenience functions
 */

static void	websMsgStart(webs_t wp)
{
	websWrite(wp, MSG_START);
}

static void	websMsgEnd(webs_t wp)
{
	websWrite(wp, MSG_END);
}

/******************************************************************************/

