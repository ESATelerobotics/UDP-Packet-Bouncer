#ifndef MEASUREMENT_SENDER_MAIN_H_B54FGS
#define MEASUREMENT_SENDER_MAIN_H_B54FGS

//includes 
#include "Meteron_Link_Test_Common.h"
#include "Sender_Class.h"
#include "Receiver_Class.h"
#include "posix_periodic.h" 

#include <glib.h>

//global variables
pthread_t				Send_Task;
pthread_t				Receive_Task;

Sender					MySender;
Receiver				MyReceiver;

//for time measurement
struct timespec				Start_Operation;
struct timespec				Data_Received;
int					Sample_Rate = 10000;
int					Payload_Size = Min_Payload_Data_Size;
gchar 				*	Log_File_Path;


//the help and description of the command line
char * Argument_Order = "Destination_IP Destination_Port Source_Port";

char * Description =
"The parameters have to be entered manner showed above\n\
Example 1:\n\
             Dest_IP       De_pt Sc_pt\n\
ASAP_Bouncer 192.168.1.232 25001 25002 --verbose\n\
\n\
This command will send periodically with the default rate of 10 ms (10000 us) a message with \ 
the default datapayload of 12 bytes.\n \n\
Example 2:\n\
                   Dest_IP       De_pt  Sc_pt\n\
Measurement_Sender 192.168.1.232 25001  25002 --sample_rate=2000 --payload_size=64 \n \n\
This command will send periodically every 2 ms (2000 us) with \ 
a datapayload of 64 bytes.\n\
The source IP address will be 0.0.0.0 (receiving from everybody) by default.\n";

char * Summary = 
"This programm sends a upd datagram containing a timestap and a counter\
 value to the destination address. It is expected that on this computer\ 
 the package will be reflected respective send back to the sender.\
 This program also receives the reflected upd packets and compares\
 the timestaps to calculate the latency and determines lost packages.\n \n\
The execution is in the Xenomai user-space real-time domain";

//for the command line parsing
//variables
static gboolean verbose = FALSE;

//the valid options
GOptionEntry options[] =
	{
		{"sample_rate", 's', 0, G_OPTION_ARG_INT, &Sample_Rate, "Rate in which the UDP packets are send in microseconds (Default = 10000)", NULL},
		{"payload_size", 'p', 0, G_OPTION_ARG_INT, &Payload_Size, "Size of of the payload in bytes (Default/Minimum = 32)", NULL},
		{"verbose", 'v', 0, G_OPTION_ARG_NONE, &verbose, "Be verbose", NULL },
		{"Log-File-Path", 'l', 0, G_OPTION_ARG_STRING, &Log_File_Path, "Location and name of the logfile e.g. /home/thomas/log.txt", NULL},
		{ NULL }
	};

#endif