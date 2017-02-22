/** @file
    @brief sample web module
*/

#ifndef WEB_H
#define WEB_H

typedef char * (*Web_requestHandler)(char * outputBuffer, const char * path);

void Web_runServer(Web_requestHandler handler);

#endif