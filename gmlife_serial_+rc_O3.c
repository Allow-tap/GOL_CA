/*
	Conway's Game of Life
	Author : Panagiotis Stefanos Aslanis
*/

/*👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️👨‍💻️
The universe of the Game of Life is an infinite, two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, live or DEATH, (or populated and unpopulated, respectively). Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent. At each step in time, the following transitions occur:

	1.Any live cell with fewer than two live neighbours dies, as if by underpopulation.
	2.Any live cell with two or three live neighbours lives on to the next generation.
	3.Any live cell with more than three live neighbours dies, as if by overpopulation.
	4.Any DEATH cell with exactly three live neighbours becomes a live cell, as if by reproduction.
These rules, which compare the behavior of the automaton to real life, can be condensed into the following:

	1.Any live cell with two or three live neighbours survives.
	2.Any DEATH cell with three live neighbours becomes a live cell.
	3.All other live cells die in the next generation. Similarly, all other DEATH cells stay DEATH.

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
//Extra rows,cols to make the grid wrap around(i.e., toroidal)
#define TOROIDAL 2
//Integers to represent the state of the each organism
#define LIFE 1
#define DEATH 0
//Forward Declaration
static double get_wall_seconds();
void free_mem(int** arr, int n);

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
int **gme_board, **gme_update, generation, neighbors, x, y, i,j;
//Allocate memory for the game board(i.e., grid including extra rows)
gme_board = (int**)malloc((board_rows + TOROIDAL) * (board_cols + TOROIDAL) * sizeof(int));
gme_update = (int**)malloc((board_rows + TOROIDAL) * (board_cols + TOROIDAL) * sizeof(int));

for(i = 0; i <= board_rows + 1;i++){
    gme_board[i]= (int*)malloc((board_cols + TOROIDAL) * sizeof(int));
	gme_update[i]= (int*)malloc((board_cols + TOROIDAL) * sizeof(int));
}

//Spawn a random amount of organisms 
for(i = 1; i <= board_rows;i++){
    for(j = 1; j <= board_cols;j++){
        gme_board[i][j] = rand() < RAND_MAX / 4? 1: 0;
    }
} 
double time_init = get_wall_seconds();
 
for(generation=0;generation<=generations-1;generation++){ 
     // Assign values to exra row, cols
	 for(j = 0;j <= board_cols + 1; j++){
			gme_board[0][j] = gme_board[board_rows][j]; //extra row to the north is equal to the last row of the grid
		    gme_board[board_rows + 1][j] = gme_board[1][j]; //extra row to the south is equal to the first row of the grid
		}
	 for(i = 0; i <= board_rows + 1;i++){
		    gme_board[i][0] = gme_board[i][board_cols];//extra column to the west is equal to last column of the gird
		    gme_board[i][board_cols + 1] = gme_board[i][1];//extra column to the east is equal to 
		}
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
/*Compute the next generation */
	for(i = 1; i <= board_rows; i++) {
		for(j = 1; j <= board_cols; j++) {
			neighbors = 0;
			for(x = i - 1; x <= i + 1; x++){
				for(y = j - 1; y <= j + 1; y++){
					if((x != i || y != j) && (gme_board[x][y] == LIFE)){neighbors++;}
				   }
				}
		
		if (!gme_board[i][j] && neighbors == 3){
			gme_update[i][j] = LIFE;
		} else if ( gme_board[i][j] && (neighbors < 2 || neighbors > 3)){
			gme_update[i][j] = DEATH;
		} else {
			gme_update[i][j] = gme_board[i][j];
		}
		
		}
	}								
	for(i = 1; i <= board_rows; i++){
		for(j = 1; j <= board_cols; j++){
			gme_board[i][j] = gme_update[i][j];
			}
		}
#if DISPLAY_STATE	
usleep(500000);
#endif
}
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
	free_mem(gme_update, board_rows);
    free_mem(gme_board, board_rows);
}
    
static double get_wall_seconds() {
struct timeval tv;
gettimeofday(&tv, NULL);
double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
return seconds;
}

void free_mem(int** arr, int n)
{
  int i;
  for(i=n+1; i>=0; i--)
     free(arr[i]);
  free(arr);
}
