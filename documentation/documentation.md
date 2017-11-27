# <center>Preparing the development environment</center>
***
[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](http://www.gnu.org/licenses/gpl-3.0)
***
## Software needed :
- Cygwin (to get a proper bash for windows)
- MPLab ipe (Integrated programming environment)
- MPLab x ide (Only if you want to do step by step debugging)
- QT (version 5.2.0 or greater)
- XC32 compiler (gcc for Microchip 32 bits devices)
- XC16 compiler (gcc for Microchip 16 bits devices)

***
## Cygwin installation :
### During the first install you will have to add the following components(*use the search bar*) by **selecting** them :
- make (gnu make utility in devels)
- nano (optional)
- completion (makes the life easier)
- git (optional)
Validate your install by clicking next

***	
## Change the Cygwin's home directory :
1. Edit the file 'nsswitch.conf' located in the folder 'etc' 
2. Uncomment the 'db_home' line and set your path (example with the windows home directory) : db_home:  /%H
3. Don't forget to restart Cygwin to take the new home folder into account

***	
## Add paths to the 'Path' environment variable (on windows) :
- For QT add 'DEFAULT_INSTALL_DIRECTORY\QT\5.9.2\mingw53_32\bin'
- Add 'DEFAULT_INSTALL_DIRECTORY\Microchip\MPLABX\v4.05\mplab_ipe'
(To add these paths, go to the **Start menu**,right click on **Computer**, on your left you'll see **Advanced settings**)

***
***
# <center>Testing the environment setup by compiling a test sample</center>
## Introduction:
Test samples are located in the **rtprog**\\**test** directory  
In each sample directory, you'll find a **Makefile** file with these fields :

|	Fields   			|&nbsp;&nbsp;&nbsp; 	Meaning                 |
|	:----				| 			:-----						|
|	**RTPROG**			|&nbsp;&nbsp;&nbsp;  	rtprog root directory path		|
|	**DEV_PROG**		|&nbsp;&nbsp;&nbsp;  	the programmer that is used to program the board(PICkit3 -> TPPK3; MPLAB REAL ICE -> TPRICE; MPLAB ICD 3 -> TPICD3;MPLAB PM3 -> TPPM3; PICkit On Board -> PKOB )		|
|	**PROJECT**			|&nbsp;&nbsp;&nbsp;  	the project directory		|
|	**BOARD**			|&nbsp;&nbsp;&nbsp;  	the board used for this project		|
|	**OUT_PWD**			|&nbsp;&nbsp;&nbsp;  	the directory where the compiled files are put into		|

Change them to suit your needs


To compile the sample, move into the sample's directory  
Then type **make** *to compile only* or **make prog** *to compile and then program the board with one command* 
```bash
cd my/super/path/to/rtprog/test/test32
make
#or
make prog
```
If you get the error **Programmer not found** check the programmer you specified to the **DEV_PROG** variable in the project Makefile.  
If everything works fine, then you're good to go :)

***  
###### This doc was generated with the help of pandoc using : *pandoc -s -f gfm -t html documentation.md -o documentation.html*
