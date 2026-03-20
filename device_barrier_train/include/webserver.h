#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <global.h>

// global functions
void runWebServer(void *parameter);

// local functions
void sendbarrierstatus();
void sendalertstatus_SAFE();
void sendalertstatus_DANGER();

#endif // WEBSERVER_H