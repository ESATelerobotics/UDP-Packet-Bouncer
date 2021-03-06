 /** @file ASAP_Bouncer_Main.cpp
 *  @brief Main function for the bouncer
 *
 *  @author Thomas Krueger
 *  @bug No known bugs.
 */

#include "ASAP_Bouncer_Main.h"

void * bouncing_rt_function(void * Data)
{
	char	Data_Buffer[Max_Payload_Data_Size];
	int		Bytes_Received;
	
	while(true)
	{
		Bytes_Received = MyReceiver.receive_Blocking(Data_Buffer, Max_Payload_Data_Size);
		if(verbose)
		{
			printf("%d Bytes Received --> Bounce\n", Bytes_Received);
		}
		MySender.transmit(Data_Buffer, Bytes_Received);
	}
	return 0;
}

int main(int argc, char** argv)
{
    GError 		*	error = NULL;
    GOptionContext 	*	context;
	int 			result;
	char 			Dest_IP_Address[32];
	int			Dest_Port;
	char			Source_IP_Address[32];
	int			Source_Port;
	

	context = g_option_context_new (Argument_Order);
    g_option_context_add_main_entries(context, options, NULL);
	
	g_option_context_set_summary(context, Summary);
	g_option_context_set_description (context, Description);
	
    if (!g_option_context_parse(context, &argc, &argv, &error))
    {
		g_print ("option parsing failed: %s\n\n", error->message);
		printf(g_option_context_get_help (context, TRUE, NULL));
		exit(EXIT_FAILURE);
    }
	
	if (argc<4)
	{
		printf("Not enough arguments...\n\n");
		printf(g_option_context_get_help (context, TRUE, NULL));
		exit(EXIT_FAILURE);
	}
	if (argc>4)
	{
		printf("Not many arguments...\n\n");
		printf(g_option_context_get_help (context, TRUE, NULL));
		exit(EXIT_FAILURE);
	}
	
	sprintf(Source_IP_Address, "0.0.0.0");
	sprintf(Dest_IP_Address, "%s", argv[1]);
	Dest_Port = atoi(argv[2]);
	Source_Port = atoi(argv[3]);
	
	printf("The programm will be running with the following settings\n");
	printf("====================\n");
	printf("Destination ip address : %s\n", Dest_IP_Address);
	printf("Destination port       : %d\n", Dest_Port);
	printf("Source ip address      : %s\n", Source_IP_Address);
	printf("Source port            : %d\n", Source_Port);
	
	//init the sockets
	MySender.init(Dest_IP_Address, Dest_Port);
	MyReceiver.init(Source_IP_Address, Source_Port);
	
	//create the tasks
	
  fprintf(stdout, "Starting standard posix bouncing thread\n");
  //invoke the bouncer as posix task
  result = pthread_create(&Bouncing_Task, NULL, &bouncing_rt_function, NULL);
  if(result != 0)
  {
	  fprintf(stderr, "Posic task creation failed in %s at line %d\n", __FILE__, __LINE__);
	  return -1;
  }
  //wait before task returns
  result = pthread_join(Bouncing_Task, NULL);
  if (result != 0)
  {
	  fprintf(stderr, "Task does not rejoin properly\n");
	  return -1;
  }

  fprintf(stderr, "Program terminated nominally\n");
  return 0;
}