#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "restApi.h"
#include "../../../esp/network/http.h"
#include "../../../esp/network/json.h"


//Necessary to be send via http
void write_json_http_header(char *buffer)
{
    http_write_header_code(buffer, HTTP_OK);
    http_write_content_type(buffer, "application/json");
    http_write_header_end(buffer);
}

void rest_api_exec(const char *restUrl, HTTP_QUERRY_TYPE querry_type, char *buffer)
{
    int id = 0;
    char axes;

    uint16_t valAcceloration[3];

    char values[300]=" ",ressource[300]=" ",valeur[300]=" ",values1[300]="";
    char ret[300]=" ";
    int nbElement=0,taille=3,i=0;

    JsonBuffer json;
    write_json_http_header(buffer);
    json_init(&json, buffer+strlen(buffer)/*json text doesn t overwrite our header*/, 100, JSON_MONOBLOC);//The size is hard coded, this needs to be changed
    json_open_object(&json);

    //We first check the querry type
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
            sscanf(restUrl,"%*[a-z/]%d",&id);
            switch(id)
            {
                case 1 :
                   json_add_field_int(&json, "motors 1", 10);
                    break;


                case 2 :
                   json_add_field_int(&json, "motors 2",10);
                    break;
            }
        }
        //------------------------LASER------------------------------------
        else if (strcmp(restUrl, "laserrangefinders") == 0)
        {
            json_add_field_int(&json, "tof1", VL6180X_getDistance(board_i2c_tof(), TOF1_ADDR));
            json_add_field_int(&json, "tof2", VL6180X_getDistance(board_i2c_tof(), TOF2_ADDR));
            json_add_field_int(&json, "tof3", VL6180X_getDistance(board_i2c_tof(), TOF3_ADDR));
        }
        else if (strncmp(restUrl, "laserrangefinders/", 18) == 0)
        {
            //We retrieve the laser id
            sscanf(restUrl,"%*[a-z/]%d",&id);
            switch(id)
            {
                case 1 :
                   json_add_field_int(&json, "tof1", VL6180X_getDistance(board_i2c_tof(), TOF1_ADDR));
                    break;
                case 2 :
                   json_add_field_int(&json, "tof2", VL6180X_getDistance(board_i2c_tof(), TOF2_ADDR));
                    break;
                case 3 :
                   json_add_field_int(&json, "tof3", VL6180X_getDistance(board_i2c_tof(), TOF3_ADDR));
                break;
                default :
                    break;
            }
        }
        //---------------------TRAVEL_DISTANCE-----------------------------
        else if (strcmp(restUrl, "traveldistances") == 0)
        {
             json_add_field_int(&json,"travel",10);//TODO FIXME
        }
        else if (strncmp(restUrl, "traveldistances/", 16) == 0)
        {
            //We retrieve the traveldistances id
            sscanf(restUrl,"%*[a-z/]%d",&id);
        }
        //----------------------ACCELEROMETER---------------------------------
        else if (strcmp(restUrl, "accelerations") == 0)
        {
            // lsm6ds3_getAccel(board_i2c_tof(),i2c_getc(board_i2c_tof()),valAcceloration);
            // for(i=0;i<3;i++)
            // {
                // json_add_field_int(&json, "accelerations",valAcceloration[i]);
            // }
            // Wait for accelorometer focntions
        }
        else if (strncmp(restUrl, "accelerations/", 14) == 0)
        {
            sscanf(restUrl, "%*[a-z]/%c", &axes);
            switch(axes)
            {
                case 'x' :
                    json_add_field_int(&json,"acceleration x",10);
                    break;
                case 'y' :
                    json_add_field_int(&json,"acceleration y",10);
                    break;
                case 'z' :
                    json_add_field_int(&json,"acceleration z",10);
                    break;
            }
        }
        //-------------------ROTARY_ENCODER------------------------
        else if (strcmp(restUrl, "rotaryencoderpositions") == 0)
        {
            json_add_field_int(&json,"rotary encoder 0",getC1());
            json_add_field_int(&json,"rotary encoder 1",getC2());
        }
        else if (strncmp(restUrl, "rotaryencoderpositions/", 23) == 0)
        {
            sscanf(restUrl, "%*[a-z/]%d", &id);
            switch(id)
            {
                case 0 :
                    json_add_field_int(&json,"rotary encoder 0",getC1());
                    break;
                case 1 :
                    json_add_field_int(&json,"rotary encoder 1",getC2());
                    break;
                default :
                    http_write_header_code(buffer, HTTP_NOT_IMPLEMENTED);
                    http_write_header_end(buffer);
                    break;
            }
        }
        //--------------------STATUS------------------------------
        else if (strcmp(restUrl, "batterylevel") == 0)
        {
            json_add_field_int(&json,"battery",board_getPowerVoltage()*1000);
        }
        else //The resource wasn't found
        {
            http_write_header_code(buffer, HTTP_NOT_FOUND);
            http_write_header_end(buffer);
        }

        break;
    case HTTP_QUERRY_TYPE_POST:

        //ret = strrchr(restUrl, ch);
        //printf("REQUETE POST : %s\n", ret);

        nbElement = http_parse_value_post(ret,"%[^=]s",values);
        if(nbElement > 1)
        {

            if( http_parse_value_post(values,"%[^&]s",values1) > 0)
            {
                printf("%s\n\n",values1);

                for(i=1;i<nbElement;i=i+1)
                {
                    sscanf(values1+taille,"%s",ressource);
                    taille += strlen(ressource) + 1;
                    sscanf(values1+taille,"%s",valeur);
                    taille += strlen(valeur) + 1;

                    if (strcmp(ressource, "motors") == 0)
                    {
                        motors_setSpeed(atoi(valeur));
                    }
                    else if (strncmp(ressource, "motors/",7) == 0)
                    {
                        //We retrieve the motor id
                        sscanf(ressource,"%*[a-z/]%d",&id);
                        switch(id)
                        {
                            case 1 :
                               // json_add_field_int(&json, "motors 1", VL6180X_getDistance(board_i2c_tof(), TOF1_ADDR));
                                 motors_setSpeed(atoi(valeur));
                                break;


                            case 2 :
                                 motors_setSpeed(atoi(valeur));
                               // json_add_field_int(&json, "motors 2", VL6180X_getDistance(board_i2c_tof(), TOF1_ADDR));
                                break;
                        }
                    }
                    else //The resource wasn't found
                    {
                        http_write_header_code(buffer, HTTP_NOT_FOUND);
                        http_write_header_end(buffer);
                    }
                }
            }
        break;
        }
    default :
        //If we encounter an other querry type
        http_write_header_code(buffer, HTTP_NOT_IMPLEMENTED);
        http_write_header_end(buffer);
        break;
    }

    json_close_object(&json);

}
