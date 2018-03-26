/**
 * @file http_formater.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date June 2, 2016, 11:45 AM
 *
 * @brief HTTP protocol formater
 */

#include "http.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void http_write_header_code(char *buffer, int result_code)
{
    strcpy(buffer, "HTTP/1.1 ");
    switch (result_code)
    {
    case HTTP_OK:
        strcat(buffer, "200 OK\r\n");
        break;
    case HTTP_BAD_REQUEST:
        strcat(buffer, "400 Bad Request\r\n");
        break;
    case HTTP_NOT_FOUND:
        strcat(buffer, "404 Not Found\r\n");
        break;
    default:
        break;
    }
}

void http_write_content_type(char *buffer, const char *content_type)
{
    strcat(buffer, "Content-Type: ");
    strcat(buffer, content_type);
    strcat(buffer, "\r\n");
}

void http_write_content_lenght(char *buffer, unsigned int content_lenght)
{
    strcat(buffer, "Content-Length: ");
    // strcat(buffer, content_lenght);
    strcat(buffer, "\r\n");
}

void http_write_header_end(char *buffer)
{
    strcat(buffer, "\r\n");
}

int http_parse_value_post(const char * chaine , char * occurence,char *buffer)
{
	int elements=0;
    int taille=0;
    char values[25] = " ";

    while(sscanf(chaine+taille,occurence,values)!=0)
    {
         taille += strlen(values);

       if(taille <= strlen(chaine))
        {
            strcat(buffer,strcat(values," "));
            taille+=1;
            elements++;
        }
        else
        {
            return elements ;
        }
    }
    return elements ;
}
