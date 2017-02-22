#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <web.h>

char * webHandler(char * buf, const char * uri);

int main(void) {
	Web_runServer(webHandler);
	return 0;
}

char * webHandler(char * buf, const char * uri) {
	if (strcmp(uri, "/") == 0) {
		sprintf(buf, 
			"<h1>WebSite Main Page</h1>"
			"<p>Here is some description</p>"
			"<a href='/profle'>Profile link</a>"
			"<div><img src='https://i.ytimg.com/vi/tntOCGkgt98/maxresdefault.jpg' width=\"500\" /></div>");
	} else {
		sprintf(buf, 
			"<h1>WebSite</h1>"
			"<p>You are on page <b>%s</b></p>", 
			uri);
	}
	return buf;
}