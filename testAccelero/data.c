#include <stdio.h>      // standard input / output functions
#include <stdlib.h>
#include <string.h>     // string function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions  

int main(void){
	FILE *file;
	file = fopen("data.txt","w");
	if (file == NULL)
	{
		printf("error");
		exit(1);
	}

	struct termios tty;
	memset (&tty, 0, sizeof tty);

	char buf, reponse[1024];
	int n, spot = 0, cpt = 0;

	int USB = open( "/dev/ttyUSB0",O_RDWR | O_NOCTTY);
	if ( USB < 0 )
	{
		printf("erreur opening USB\n");
		exit(1);
	}

	tcgetattr(USB, &tty);

	/* Set Baud Rate */
	cfsetospeed (&tty, B9600);
	cfsetispeed (&tty, B9600);


	/* Setting other Port Stuff */
	tty.c_cflag     &=  ~PARENB;            // Make 8n1
	tty.c_cflag     &=  ~CSTOPB;
	tty.c_cflag     &=  ~CSIZE;
	tty.c_cflag     |=  CS8;
	tty.c_cc[VMIN]   =  1;                  // read doesn't block
	tty.c_cc[VTIME]  =  5;                  // 0.5 seconds read timeout
	tty.c_cflag     &=  ~CRTSCTS;           // no flow control
	tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

	
	tcflush( USB, TCIFLUSH );

	if ( tcsetattr ( USB, TCSANOW, &tty ) != 0)
	{
		printf("erreur setattr\n");
		exit(1);
	}

	fprintf(file,"Acc[0] | Acc[1] | Acc[2] | Giro[0] | Giro[1] | Giro[2]\n\n");
	/* Get 200 datalines from the USB port */
	while(cpt <= 200)
	{
		n = read( USB, &buf ,1);
		if ( n < 0 )
		{
			printf("erreur reading\n");
			exit(1);
		}
		if(n > 0)
		{
			if (buf == '\n')
			{
				fprintf(file,"%s",reponse);
				//printf("%s",reponse);
				strcpy(reponse,"");
				cpt = cpt + 1;
				spot = 0;
			}
			sprintf(&reponse[spot], "%c", buf);
			spot += n;
		}	
	}
	
	close(USB);

	return 0;

}
