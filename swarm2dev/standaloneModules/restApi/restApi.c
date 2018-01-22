#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "restApi.h"

void rest_api_exec(const char *restUrl, HTTP_QUERRY_TYPE querry_type, char *buffer)
{
    int id = 0;
    char axes = ' ';
    //We first check the querry typedef
    switch(querry_type)
    {
    case HTTP_QUERRY_TYPE_GET:
        //We check which resource we want to access
        //------------------------MOTOR------------------------------------
        if (strcmp(restUrl, "motors") == 0)
        {
            //We construct our json response with the 2 motor's data
        }
        else if (strncmp(restUrl, "motors/",7) == 0)
        {
            //We retrieve the motor id
            sscanf(restUrl,"%d",&id);
        }
        //------------------------LASER------------------------------------
        else if (strcmp(restUrl, "laserrangefinders") == 0)
        {
            //We construct our json response with the 3 laser's data
        }
        else if (strncmp(restUrl, "laserrangefinders/", 18) == 0)
        {
            //We retrieve the laser id
            sscanf(restUrl,"%d",&id);
        }
        //---------------------TRAVEL-DISTANCE-----------------------------
        else if (strcmp(restUrl, "traveldistances") == 0)
        {

        }
        else if (strncmp(restUrl, "traveldistances/", 16) == 0)
        {
            //We retrieve the laser id
            sscanf(restUrl,"%d",&id);
        }
        //----------------------ACCELEROMETER---------------------------------
        else if (strcmp(restUrl, "accelerations") == 0)
        {

        }
        else if (strncmp(restUrl, "accelerations/", 14) == 0)
        {
            sscanf(restUrl, "/%c", &axes);
        }
        //-------------------ROTARYENCODER------------------------
        else if (strcmp(restUrl, "rotaryencoderpositions") == 0)
        {

        }
        else if (strncmp(restUrl, "rotaryencoderpositions/", 23) == 0)
        {
            sscanf(restUrl, "%d", &id);
        }

        break;
    case HTTP_QUERRY_TYPE_POST:
        break;
    default :
        //If we encounter an other querry type
        break;
    }

}
