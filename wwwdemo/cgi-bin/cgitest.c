/*
 * cgitest.c -- CGI Test example for the GoAhead WebServer
 *
 * Copyright (c) GoAhead Software Inc., 1995-2009. All Rights Reserved.
 *
 * See the file "license.txt" for usage and redistribution license requirements
 *
 * Release $Name: WEBSERVER-2-5 $
 */

/******************************** Description *********************************/

/*
 *	Tests the CGI environment variables generated by the GoAhead Webserver
 */
 
/********************************* Includes ***********************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h> /*add by zeed 2017-9-15*/

/******************************************************************************/
/*
 * Compare strings, ignoring case:  normal strcmp return codes.
 *
 *	WARNING: It is not good form to increment or decrement pointers inside a
 *	"call" to tolower et al. These can be MACROS, and have undesired side
 *	effects.
 */

int strcmpci(char *s1, char *s2)
{
	int		rc;

	if (s1 == NULL || s2 == NULL) {
		return 0;
	}

	if (s1 == s2) {
		return 0;
	}

	do {
		rc = tolower(*s1) - tolower(*s2);
		if (*s1 == '\0') {
			break;
		}
		s1++;
		s2++;
	} while (rc == 0);

	return rc;
}

/*************************************************************************/
/*
 *	gogetenv wraps getenv so that (NULL) is returned if the string is
 *	NULL.
 */

char *gogetenv(char *varname)
{
	char *result;

	if ((result = getenv(varname)) == NULL) {
		result = "(NULL)";
	}
	return result;
}

/*************************************************************************/
/*
 *	Convert a two-char hex string into the char it represents
 */

char x2c(char *what) 
{
   register char digit;

   digit = (what[0] >= 'A' ? ((what[0] & 0xdf) - 'A') + 10 : (what[0] - '0'));
   digit *= 16;
   digit += (what[1] >= 'A' ? ((what[1] & 0xdf) - 'A') + 10 : (what[1] - '0'));

   return digit;
}

/*************************************************************************/
/*
 *	Reduce any %xx escape sequences to the characters they represent
 */

void unescape_url(char *url) 
{
    register int i,j;

    for(i = 0, j = 0; url[j]; ++i,++j) {
        if((url[i] = url[j]) == '%') {
            url[i] = x2c(&url[j + 1]) ;
            j += 2 ;
        }
    }

    url[i] = '\0' ;
}

/*************************************************************************/
/*                                                                     
 *	getCGIvars()	Routine to read CGI input variables into an     
 *					array of strings.
 *
 *	Written in 1996 by James Marshall, james@jmarshall.com, except
 *	that the x2c() and unescape_url() routines were lifted directly
 *	from NCSA's sample program util.c, packaged with their HTTPD.
 *
 *	For the latest, see http://www.jmarshall.com/easy/cgi/ .
 *
 *	Read the CGI input and place all name/val pairs into list.
 *	Returns list containing name1, value1, name2, value2, ... , NULL
 */

char **getCGIvars() 
{
	register int	i;
	char			*request_method, *cgiinput, *nvpair, *eqpos;
	int				content_length, paircount;
    char			**cgivars, **pairlist;

/*
 *	Depending on the request method, read all CGI input into cgiinput
 *	(really should produce HTML error messages, instead of exit()ing)
 */
    request_method = gogetenv("REQUEST_METHOD") ;

	if (!request_method) {
		request_method = "NOT-CGI";
	}

    if (!strcmp(request_method, "GET") || !strcmp(request_method, "HEAD")) {
        cgiinput= strdup(gogetenv("QUERY_STRING"));
    } else if (!strcmp(request_method, "POST")) {
        if (strcmpci(gogetenv("CONTENT_TYPE"), "application/x-www-form-urlencoded")) {
            printf("getcgivars(): Unsupported Content-Type.\n");
            return NULL;
        }

        if (!(content_length = atoi(gogetenv("CONTENT_LENGTH")))) {
            printf("getcgivars(): No Content-Length was sent with the POST request.\n");
            return NULL;
        }

        if (!(cgiinput = (char *) malloc(content_length + 1))) {
            printf("getcgivars(): Could not malloc for cgiinput.\n") ;
            return NULL;
        }

        if (!fread(cgiinput, content_length, 1, stdin)) {
            printf("Couldn't read CGI input from STDIN.\n");
            return NULL;
        }

        cgiinput[content_length] = '\0' ;
    } else {
        printf("getcgivars(): unsupported REQUEST_METHOD\n") ;
        return NULL;
    }

/*
 *	Change all plusses back to spaces
 */
    for (i = 0; cgiinput[i]; i++) {
		if (cgiinput[i] == '+') {
			cgiinput[i] = ' ';
		}
	}

/*
 *	First, split on "&" to extract the name-value pairs into pairlist
 */
    pairlist = (char **) malloc(256 * sizeof(char **));
    paircount = 0 ;
    nvpair = strtok(cgiinput, "&");

    while (nvpair) {
        pairlist[paircount++] = strdup(nvpair);
        if (!(paircount % 256)) {
            pairlist= (char **) realloc(pairlist, (paircount + 256)
				* sizeof(char **));
		}

        nvpair = strtok(NULL, "&") ;
    }

/*	
 *	Terminate the pair list with NULL
 */
    pairlist[paircount] = 0;

/*
 *	Then, from the list of pairs, extract the names and values
 */
    cgivars = (char **) malloc((paircount * 2 + 1) * sizeof(char **));
    for (i = 0; i < paircount; i++) {
        if (eqpos = strchr(pairlist[i], '=')) {
            *eqpos = '\0' ;
            unescape_url(cgivars[i * 2 + 1] = strdup(eqpos + 1));
        } else {
            unescape_url(cgivars[i * 2 + 1] = strdup(""));
        }
        unescape_url(cgivars[i * 2] = strdup(pairlist[i]));
    }

/* 
 *	Terminate the cgi var list with NULL
 */
    cgivars[paircount * 2] = 0;	
    
/*
 *	Free anything that needs to be freed
 */
    free(cgiinput);

    for (i = 0; pairlist[i]; i++) {
		free(pairlist[i]);
	}

    free(pairlist);

/*
 *	Return the list of name-value strings
 */
    return cgivars;
    
}

/*************************************************************************/
/*
 *	Test program entry point
 */

int main(int argc, char *argv[])
{
	char	**pVars;
	int		loopCount = 1000;
	time_t	second;

/*
 *	Print the CGI response header, required for all HTML output.
 *	Note the extra \n, to send the blank line.
 */
    printf("Content-type: text/html\n\n") ;
/*	
 *	Print the HTML header to STDOUT.
 */
    printf("<html>\n");
    printf("<head><title>CGI Output</title></head>\n");
    printf("<body>\n");

    printf("<H1>CGI Test Program</H1>\n");
    printf("<P>This program displays the CGI Enviroment</P>\n");

/*	
 *	Print the CGI environment variables
 */
    printf("<H2>Environment Variables<A NAME=\"env\"></A></H2>\n");
    printf("<P>REQUEST METHOD = %s</P>\n", gogetenv("REQUEST_METHOD"));
    printf("<P>QUERY STRING = %s</P>\n", gogetenv("QUERY_STRING"));
    printf("<P>GATEWAY INTERFACE = %s</P>\n", gogetenv("GATEWAY_INTERFACE"));
    printf("<P>SCRIPT NAME = %s</P>\n", gogetenv("SCRIPT_NAME"));

    printf("<P>PATH TRANSLATED = %s</P>\n", gogetenv("PATH_TRANSLATED"));
    printf("<P>PATH INFO = %s</P>\n", gogetenv("PATH_INFO"));

    printf("<P>HTTP HOST = %s</P>\n", gogetenv("HTTP_HOST"));
    printf("<P>HTTP ACCEPT = %s</P>\n", gogetenv("HTTP_ACCEPT"));
    printf("<P>HTTP CONNECTION = %s</P>\n", gogetenv("HTTP_CONNECTION"));

    printf("<P>REMOTE USER = %s</P>\n", gogetenv("REMOTE_USER"));
    printf("<P>REMOTE HOST = %s</P>\n", gogetenv("REMOTE_HOST"));
    printf("<P>REMOTE ADDR = %s</P>\n", gogetenv("REMOTE_ADDR"));

    printf("<P>SERVER NAME = %s</P>\n", gogetenv("SERVER_NAME"));
    printf("<P>SERVER PORT = %s</P>\n", gogetenv("SERVER_PORT"));
    printf("<P>SERVER HOST = %s</P>\n", gogetenv("SERVER_HOST"));
    printf("<P>SERVER PROTOCOL = %s</P>\n", gogetenv("SERVER_PROTOCOL"));
    printf("<P>SERVER ADDR = %s</P>\n", gogetenv("SERVER_ADDR"));
    printf("<P>SERVER URL = %s</P>\n", gogetenv("SERVER_URL"));
    printf("<P>SERVER SOFTWARE = %s</P>\n", gogetenv("SERVER_SOFTWARE"));

/*	
 *	Print the parsed query string variables
 */
    printf("<H2>Query String Variables<A NAME=\"query\"></A></H2>\n");
    pVars = getCGIvars();
	if (pVars) {
		while (*pVars && *(pVars + 1)) {
			printf("<p>%s = <b>%s</b></p>\n", *pVars, *(pVars + 1));
			pVars += 2;
		}
	} else {
	    printf("<P>No query variables found</P>\n");
	}

/*	
 *	Print 1000 lines of text, 100 lines at a time.
 *	Pause for 5 seconds every 100 line chunk
 */
#ifdef PRINT_BIG_CHUNK_SLOWLY
    printf("<H2>Large chunk of meaningless text<A NAME=\"chunk\"></A></H2>\n");
	while (loopCount) {
		printf("<p>Meaningless line of text number %d.</p>\n", loopCount);
		if ((loopCount % 100) == 0) {
			second = time(NULL);
			while ((time(NULL) - second) < 5) {
			}
		}
		loopCount--;
	}
#endif

    printf("</body>\n");
    printf("</html>\n");

    return 0;
}

/*************************************************************************/