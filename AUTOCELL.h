#ifndef AUTOCELL_H
#define AUTOCELL_H


/*
Represents a grid of cells (automata),
and contains its own rule sets
*/
typedef struct AutomataTable
{
	int generation;
	
	int width;
	int height;
	
	int* rules;
	int* neighborhood;
	int num_neighbors;
	
	int* cells;
	int* buffer;
} AT;


/*
INPUT:	width (cells), height (cells), rule set pointer,
		relational neighborhood pointer, number of neighbors
RETURN:	an automata table pointer with randomized cells
*/
AT* init_random_table(int, int, int*, int*, int);


/*
INPUT:	width (cells), height (cells), rule set pointer,
		relational neighborhood pointer, number of neighbors,
		cell grid pointer
RETURN:	an automata table pointer with the preset cells
*/
AT* init_preset_table(int, int, int*, int*, int, int*);


/*
INPUT:	automata table pointer
OP:		destroys the automata table
*/
void delete_table(AT*);


/*
INPUT:	automata table pointer, cell x coordinate, cell y coordinate
RETURN:	the state of a single cell
*/
int get_cell(AT*, int, int);


/*
INPUT:	automata table pointer, neighbor number,
		cell x coordinate, cell y coordinate
RETURN:	the state of the nth neighbor for a single cell, and
		assumes the edge cell neighbors are across the table
*/
int get_neighbor_wrap(AT*, int, int, int);


/*
INPUT:	automata table pointer, neighbor number,
		cell x coordinate, cell y coordinate, wall default state
RETURN:	the state of the nth neighbor for a single cell, and
		assumes the edge cell neighbors are the same state
*/
int get_neighbor_wall(AT*, int, int, int, int);


/*
INPUT:	automata table pointer, cell x coordinate, cell y coordinate
OP:		calculates the next state for a single cell
*/
void calc_next_state(AT*, int, int);


/*
INPUT:	automata table pointer
OP:		calculates the next state for the whole table
*/
void update_table(AT*);


/*
INPUT:	automata table pointer
OP:		prints the state of the table to the console
*/
void print_table_states(AT*);

/*
INPUT:	automata table pointer
OP:		prints the state of the table to the console in
		a more clear manner
*/
void print_table_characters(AT*);


#endif //AUTOCELL_H
