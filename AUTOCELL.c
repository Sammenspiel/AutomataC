#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "AUTOCELL.h"


AT* init_random_table(int w, int h, int* r, int* n, int nn)
{
	printf("Creating table...\n");
	printf("Performing mallocs\n");
	
	AT* at = (AT*) malloc(sizeof(AT));
	
	int* new_cells = (int*) malloc(w * h * sizeof(int));
	int* new_buffer = (int*) malloc(w * h * sizeof(int));
	
	printf("Assigning variables\n");
	
	at->generation = 0;
	
	at->width = w;
	at->height = h;
	
	at->rules = r;
	at->neighborhood = n;
	at->num_neighbors = nn;
	
	at->cells = new_cells;
	at->buffer = new_buffer;
	
	srand(time(NULL));
	
	printf("Initializing cells\n");
	
	for(int i = 0; i < at->width; i++)
	{
		for(int j = 0; j < at->height; j++)
		{
			int index = i + (j * at->width);
			at->cells[index] = rand() % 2;
		}
	}
	
	printf("Initializing buffer\n");
	
	for(int k = 0; k < at->width; k++)
	{
		for(int l = 0; l < at->height; l++)
		{
			int index = k + (l * at->width);
			at->buffer[index] = 0;
		}
	}
	
	return at;
}


AT* init_preset_table(int w, int h, int* r, int* n, int nn, int* c)
{
	printf("Creating table...\n");
	printf("Performing mallocs\n");
	
	AT* at = (AT*) malloc(sizeof(AT));
	
	int* new_buffer = (int*) malloc(w * h * sizeof(int));
	
	printf("Assigning variables\n");
	
	at->generation = 0;
	
	at->width = w;
	at->height = h;
	
	at->rules = r;
	at->neighborhood = n;
	at->num_neighbors = nn;
	
	at->cells = c;
	at->buffer = new_buffer;
	
	srand(time(NULL));
	
	printf("Initializing buffer\n");
	
	for(int k = 0; k < at->width; k++)
	{
		for(int l = 0; l < at->height; l++)
		{
			int index = k + (l * at->width);
			at->buffer[index] = 0;
		}
	}
	
	return at;
}


void delete_table(AT* at)
{
	printf("Deleting table...\n");
	printf("Freeing cells\n");
	free(at->cells);
	printf("Freeing buffer\n");
	free(at->buffer);
	printf("Freeing automata table\n");
	free(at);
}

int get_cell(AT* at, int x, int y)
{
	int index = x + (y * at->width);
	return at->cells[index];
}


int get_neighbor_wrap(AT* at, int n, int x, int y)
{
	int nbr_x = x + at->neighborhood[2 * n];
	int nbr_y = y + at->neighborhood[2 * n + 1];
	
	if(nbr_x < 0)
	{
		nbr_x = nbr_x + at->width;
	}
	else if(nbr_x >= at->width)
	{
		nbr_x = nbr_x - at->width;
	}
	
	if(nbr_y < 0)
	{
		nbr_y = nbr_y + at->height;
	}
	else if(nbr_y >= at->height)
	{
		nbr_y = nbr_y - at->height;
	}
	
	int nbr_index = nbr_x + (nbr_y * at->width);
	return at->cells[nbr_index];
}


int get_neighbor_wall(AT* at, int n, int x, int y, int wall_state)
{
	int nbr_x = x + at->neighborhood[2 * n];
	int nbr_y = y + at->neighborhood[(2 * n) + 1];
	
	if((nbr_x < 0) || (nbr_x >= at->width) || (nbr_y < 0) || (nbr_y >= at->height))
	{
		return wall_state;
	}
	
	int nbr_index = nbr_x + (nbr_y * at->width);
	return at->cells[nbr_index];
}


void calc_next_state(AT* at, int x, int y)
{
	int nbr_sum = 0;
	
	for(int n = 0; n < at->num_neighbors; n++)
	{
		nbr_sum += get_neighbor_wrap(at, n, x, y);
	}
	
	int next_state = at->rules[nbr_sum];
	int index = x + (y * at->width);
	
	if(next_state >= 0)
	{
		at->buffer[index] = next_state;
	} else {
		at->buffer[index] = at->cells[index];
	}
}


void update_table(AT* at)
{
	for( int i = 0; i < at->width; i++ )
	{
		for( int j = 0; j < at->height; j++ )
		{
			calc_next_state(at, i, j);
		}
	}
	
	int* temp = at->cells;
	at->cells = at->buffer;
	at->buffer = temp;
	
	at->generation++;
}


void print_table_states(AT* at)
{
	printf("Printing automata table at generation %d\n\n", at->generation);
	
	for(int j = 0; j < at->height; j++)
	{
		for(int i = 0; i < at->width; i++)
		{
			printf(" %d", get_cell(at, i, j));
		}
		printf("\n");
	}
	printf("\n");
}


void print_table_characters(AT* at)
{
	printf("Printing automata table at generation %d\n\n", at->generation);
	
	for(int j = 0; j < at->height; j++)
	{
		for(int i = 0; i < at->width; i++)
		{
			if(get_cell(at, i, j) == 1)
				printf("O");
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("\n");
}
