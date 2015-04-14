#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AUTOCELL.h"


int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		printf("Please enter exactly two integers to specify width and height.\n");
		return 0;
	}
	
	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	
	printf("Width:  %d\n", width);
	printf("Height: %d\n", height);
	
	int rules[] = { 0, 0, -1, 1, 0, 0, 0, 0, 0 };
	
	int neighborhood[] = { -1, -1,   0, -1,   1, -1,
						   -1,  0,            1,  0,
						   -1,  1,   0,  1,   1,  1 };
						   
	int num_neighbors = (sizeof(neighborhood) / sizeof(int)) / 2;				   
	
	AT* automata_table = init_random_table(width, height, rules, neighborhood, num_neighbors);
	
	print_table_characters(automata_table);
	
	printf("Press ENTER to go to next generation. Type 'e' to exit loop.\n");
	
	char c = 97;
	while(c != 101)
	{
		c = getchar();
		update_table(automata_table);
		print_table_characters(automata_table);
	}
	
	delete_table(automata_table);
	
	printf("End of program :( press ENTER to exit.\n");
	
	getchar();
	
	return 0;
}
