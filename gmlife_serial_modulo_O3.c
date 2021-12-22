/*
	Conway's Game of Life
	Author : Panagiotis Stefanos Aslanis
*/

/*👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️
The universe of the Game of Life is an infinite, two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, live or dead, (or populated and unpopulated, respectively). Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent. At each step in time, the following transitions occur:

	1.Any live cell with fewer than two live neighbours dies, as if by underpopulation.
	2.Any live cell with two or three live neighbours lives on to the next generation.
	3.Any live cell with more than three live neighbours dies, as if by overpopulation.
	4.Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
These rules, which compare the behavior of the automaton to real life, can be condensed into the following:

	1.Any live cell with two or three live neighbours survives.
	2.Any dead cell with three live neighbours becomes a live cell.
	3.All other live cells die in the next generation. Similarly, all other dead cells stay dead.

The initial pattern constitutes the seed of the system. The first generation is created by applying the above rules simultaneously to every cell in the seed; births and deaths occur simultaneously, and the discrete moment at which this happens is sometimes called a tick. Each generation is a pure function of the preceding one. The rules continue to be applied repeatedly to create further generations.
Source: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life 
👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>


//Control graphics
#define DISPLAY_STATE 0
#define DISPLAY_FINAL_STATE 0
//Integers to represent the state of the each cell
#define LIFE 1
#define DEATH 0
//Forward Declaration
static double get_wall_seconds();

int main(int argc, char *argv[])
{
	//Create input params for Board Size(number of rows/columns), Time Steps
	if (argc != 4){
		printf("Number of arguments is incorrect");
		exit(1); 
	}
const int board_rows = atoi(argv[1]);
const int board_cols = atoi(argv[2]);
const int generations = atoi(argv[3]);
int generation;
//Create the game board 
int (*gme_board)[board_cols] = malloc(sizeof(int[board_rows][board_cols]));
int (*gme_update)[board_cols] = malloc(sizeof(int[board_rows][board_cols]));
//Check if malloc was successful
if (gme_board == NULL || gme_update == NULL ){
	printf("Failed to allocate memory.");
	exit(1);
}
//populate the game board randomly -parallelizable
for (int i=0; i < board_rows; ++i){
	for (int j=0; j < board_cols; ++j)
	{
		gme_board[i][j] = rand() < RAND_MAX / 4? 1: 0; 
		
	}
}
double time_init = get_wall_seconds();
//For all the generations 
for(generation=0;generation<=generations-1;generation++){ //do{ 
#if DISPLAY_STATE
printf("\033[H");
for (int i=0; i < board_rows; ++i){
	for (int j=0; j < board_cols; ++j){ 
	//printf("%d ", gme_board[i][j]);
		printf(gme_board[i][j] ? "\033[07m  \033[m" : "  ");
	}
	printf("\033[E");
}
fflush(stdout);
#endif
//Iterate through each cell on the board // EPISODE STARTS
for (int i=0; i	< board_rows; ++i){
	for (int j =0; j< board_cols;  ++j){
		int neighbors = 0;
		//Check the 8 tile area around it
		for (int x = i-1 ; x <= (i+1); ++x){
			for (int y = j-1; y <= (j+1); ++y){
			//Treat the cartesian as a tortoidal utilizing modulo theory.
			if ((x != i || y !=j) && gme_board[(x+board_rows) % board_rows][(y+board_cols) % board_cols]){
				neighbors++;
			   }
			}
		}
		
		//Apply the rules of Game of life and save it to the updated
		//if (gme_board[i][j] && neighbors > 0) neighbors--; //cell is not neighbor to himself
		if (!gme_board[i][j] && neighbors == 3){
			gme_update[i][j] = LIFE;
		} else if ( gme_board[i][j] && (neighbors < 2 || neighbors > 3)){
			gme_update[i][j] = DEATH;
		} else {
			gme_update[i][j] = gme_board[i][j];
		}
		
	}
  }
  	
	//Update the gameboard with the remaining and new ALIVE cells

    for (int i=0; i	< board_rows; ++i){
	for (int j =0; j< board_cols; ++j){
		gme_board[i][j] = gme_update[i][j];		
	}
} //  EPISODE ENDS HERE  
	
#if DISPLAY_STATE	
	usleep(500000);
#endif
} //while(generation >= 0 );
#if DISPLAY_FINAL_STATE
printf("\033[H");
for (int i=0; i < board_rows; ++i){
	for (int j=0; j < board_cols; ++j){ 
	//printf("%d ",gme_board[i][j]);
		printf(gme_board[i][j] ? "\033[07m  \033[m" : "  ");
	}
	printf("\033[E");
}
fflush(stdout);
#endif
double time_fin = get_wall_seconds();
printf("Time:%f\n\n",time_fin-time_init);
//free memory
	free(gme_board);
	free(gme_update);
return 0;
}

static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}
