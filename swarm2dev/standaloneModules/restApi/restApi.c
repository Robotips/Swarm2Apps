#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "restApi.h"
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
    char axes = ' ';

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
            json_add_field_int(&json,"motors",mrobot_motorGetP());
            json_carriage_return(&json);
        }
        else if (strncmp(restUrl, "motors/",7) == 0)
        {
            //We retrieve the motor id
            sscanf(restUrl,"%*[a-z/]%d",&id);
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
             json_carriage_return(&json);
        }
        else if (strncmp(restUrl, "traveldistances/", 16) == 0)
        {
            //We retrieve the traveldistances id
            sscanf(restUrl,"%*[a-z/]%d",&id);
        }
        //----------------------ACCELEROMETER---------------------------------
        else if (strcmp(restUrl, "accelerations") == 0)
        {
            // json_add_field_int(&json, "acc1", /*Fonctions accelero buffer*/);
            // Wait for accelorometer focntions
        }
        else if (strncmp(restUrl, "accelerations/", 14) == 0)
        {
            sscanf(restUrl, "%*[a-z]/%c", &axes);
        }
        //-------------------ROTARY_ENCODER------------------------
        else if (strcmp(restUrl, "rotaryencoderpositions") == 0)
        {
            json_add_field_int(&json,"rotary encoder",10);//TODO FIXME
            json_carriage_return(&json);
        }
        else if (strncmp(restUrl, "rotaryencoderpositions/", 23) == 0)
        {
            sscanf(restUrl, "%*[a-z/]%d", &id);
            switch(id)
            {
                case 0 :
                    json_add_field_int(&json,"rotary encoder 0",getC1());
                    json_carriage_return(&json);
                    break;
                case 1 :
                    json_add_field_int(&json,"rotary encoder 1",getC2());
                    json_carriage_return(&json);
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
            json_carriage_return(&json);
        }
        else //The resource wasn't found
        {
            http_write_header_code(buffer, HTTP_NOT_FOUND);
            http_write_header_end(buffer);
        }

        break;
    case HTTP_QUERRY_TYPE_POST:
        break;
    default :
        //If we encounter an other querry type
        http_write_header_code(buffer, HTTP_NOT_IMPLEMENTED);
        http_write_header_end(buffer);
        break;
    }
    
    json_close_object(&json);

}
