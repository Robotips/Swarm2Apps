#ifndef RESTAPI_H
#define RESTAPI_H

#include "board.h"
#include "modules.h"
#include "motors.h"
#include "../../../esp/network/http.h"

//Function prototype
void rest_api_exec(const char *restUrl, HTTP_QUERRY_TYPE querry_type, char *buffer);
int parseData( const char * chaine , char * occurence,char *buffer);

#endif // RESTAPI_H
