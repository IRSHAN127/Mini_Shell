#include "main.h"

void echo(char *input_string, int status)
{
	//exit status
	if(strncmp("echo $?",input_string,7) == 0)
	{
		printf("%d\n",status);
	}
	
	//pid of the process
	if(strncmp("echo $$",input_string,7) == 0)
	{
		printf("%d\n",getpid());
	}

	//printf the executable path of project
	if(strncmp("echo $SHELL",input_string,11) == 0)
	{
		system("pwd");
	}

}

void execute_internal_commands(char *input_string)
{
	//exit status
	if(strncmp("exit",input_string,4) == 0)
	{
		exit(1);
	}
	
	//cd
	if(strncmp("cd",input_string,2) == 0)
	{
		//chdir()
		//intput_string[] = cd abc
		int i =3;
		while(input_string[i] == 32)
		{
		//	printf("i\n");
			i++;
		}
		chdir(&input_string[i]);
	}

	//printf the executable path of project
	if(strncmp("pwd",input_string,3) == 0)
	{
		system("pwd");
	}
}
