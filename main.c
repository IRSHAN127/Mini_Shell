#include"main.h"

int main()
{
	//Clear the output screen
	system("clear");

	//Declare an array to store the input
	char input_string[25];

	//Declare an array to store the prompt
	char prompt[25]="msh";

	//scan input
	scan_input(prompt,input_string);

	return 0;
}

