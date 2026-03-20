#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <global.h>

// global functions
void runWebServer(void *parameter);

// local functions
void onevent();
void sendbarrierstatus();
void sendtrespassingalert();
void sendalertstatus_SAFE();
void sendalertstatus_DANGER();

#endif // WEBSERVER_H