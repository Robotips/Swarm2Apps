#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../../esp/network/http.h"
#include "restApi.h"



int main(void)
{

   //Pointeur de fonction
    void (*restapi)(const char *, HTTP_QUERRY_TYPE , char *) = NULL;
    char buffer[1500]={"pt: text/html,application/xhtml+xml\r\nnAccept-Encoding: gzip,deflate\r\nAccept-Charset: ISO-8859-1\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: 40\r\nKeep-Alive: 300\r\nConnection: keep-alive\r\n\r\nmotors=15&laserrangefinders=15"},rep[400]=" ";
    restapi = rest_api_exec;

   // while(1)
        if(restapi == NULL)
        {
            puts("Rest api non defini !! \n");
            return 1;
        }
        else
        {
            printf("Faite une requette :\n");
            //fgets(buffer, sizeof buffer, stdin);
            (*restapi)(buffer, HTTP_QUERRY_TYPE_POST, rep);
            printf("%s \n", rep);
        }

    return 0;
}
