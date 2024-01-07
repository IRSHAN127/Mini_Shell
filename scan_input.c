#include"main.h"

pid_t pid;

void scan_input(char *prompt, char *input_string)
{
	int command_type,ret_status,status;
	char *command;

	while(1)
	{

	    memset(input_string,'\0',25);

		//Display the prompt
		printf(ANSI_COLOR_RED"[%s]$"ANSI_COLOR_RESET,prompt);
		
		//clear the o/p buffer
		fflush(stdout);

		//Read the input from the user
		scanf("%[^\n]s",input_string);
		
		//clear the i/p buffer
		getchar();

		//customize the prompt: PS1=minishell$:
		if(!strncmp("PS1=",input_string,4))
		{
			if(input_string[4] != ' ')
			{
				strcpy(prompt,&input_string[4]);
				memset(input_string,'\0',25);
				continue;
			}
			printf("command  not found\n");
		}

		//To get the command untill space or new line is encountered
		//input_string[] = ls -l,pwd..
		command = get_command(input_string);
		printf("command = %s\n",command);

		command_type = check_command_type(command);
		printf("command_type = %d\n",command_type);
		
		if(command_type == EXTERNAL)
		{
			pid = fork();

			if(pid == 0)
			{
				//child process should execute the command
				ret_status = system(input_string);
				
				if(ret_status == 0)
					exit(0);
				else
					exit(1);
			}
			else if(pid > 0)
			{
				//parent 
				wait(&status);
				if(WIFEXITED(status))
					printf("child with pid %d terminated normallly\n",pid);
				else
					printf("child with pid %d terminated abnormallly\n",pid);
			}
			else
			{
				printf("Fork failed\n");
				exit(2);
			}
		}

		//execute family of echo family
		echo(input_string,status);

		//Execute internal commands
		execute_internal_commands(input_string);

	}
}
