/*
	Individual Assignment: Conway's Game of Life
	Author : Panagiotis Stefanos Aslanis
*/

//Best attempt both optimised code and parallelization with OpenMP
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <omp.h>
//Control graphics
#define DISPLAY_STATE 0
#define DISPLAY_FINAL_STATE 1
//Extra rows,cols to make the grid wrap around(i.e., toroidal)
#define TOROIDAL 2

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
int neighbors, x, y, i,j, gen;
int **gme_board = NULL;
int **gme_update = NULL;
//Allocate memory for the game board(i.e., grid including extra rows)
gme_board = (int**)malloc((board_rows + TOROIDAL) * (board_cols + TOROIDAL) * sizeof(int));
gme_update = (int**)malloc((board_rows + TOROIDAL) * (board_cols + TOROIDAL) * sizeof(int));

if (gme_board == NULL || gme_update == NULL ){
	printf("Failed to allocate memory.");
	exit(1);
}
for(i = 0; i <= board_rows + 1;i++){
	gme_board[i]= (int*)malloc((board_cols + TOROIDAL) * sizeof(int));
	gme_update[i]= (int*)malloc((board_cols + TOROIDAL) * sizeof(int));
	if (gme_board[i] == NULL || gme_update[i] == NULL ){
	printf("Failed to allocate memory.");
	exit(1);
	}
}


//Spawn a random amount of organisms
#pragma omp parallel
{
#pragma omp for 		
	for(i = 1; i <= board_rows;i++){
		for(j = 1; j <= board_cols;j++){
		    gme_board[i][j] = rand() < RAND_MAX / 4? 1: 0;
		}
	}
}
double time_init = get_wall_seconds();
gen = generations + 1;
while(--gen){ 
//for(generation=0;generation<=generations-1;generation++){ 
     // Assign the correct values to the extra rows,cols
	 for(j = 0;j <= board_cols + 1; j++){
			gme_board[0][j] = gme_board[board_rows][j]; //extra row to the north is equal to the last row of the grid
		    gme_board[board_rows + 1][j] = gme_board[1][j]; //extra row to the south is equal to the first row of the grid
		}
	 for(i = 0; i <= board_rows + 1;i++){
		    gme_board[i][0] = gme_board[i][board_cols];//extra column to the west is equal to last column of the gird
		    gme_board[i][board_cols + 1] = gme_board[i][1];//extra column to the east is equal to first column of the grid
		}
#if DISPLAY_STATE
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
/*Compute the next generation */
#pragma omp parallel 
{
#pragma omp for
	for(i = 1; i <= board_rows; i++) {
		for(j = 1; j <= board_cols; j++) {
			neighbors = 0;
			for(x = i - 1; x <= i + 1; x++){
				for(y = j - 1; y <= j + 1; y++){
					if((x != i || y != j) && (gme_board[x][y] == 1)){					
					neighbors++;
				  }
			   }
			}
		/*gme_update[i][j] = (neighbors == 3 || (neighbors == 2 && gme_board[i][j]));*/
		
		if (!gme_board[i][j] && neighbors == 3){
			gme_update[i][j] = 1;
		} else if ( gme_board[i][j] && (neighbors < 2 || neighbors > 3)){
			gme_update[i][j] = 0;
		} else {
			gme_update[i][j] = gme_board[i][j];
		}
		
		}
	}	
}				
#pragma omp parallel
{
#pragma omp for			
		for(i = 1; i <= board_rows; i++){
			for(j = 1; j <= board_cols; j++){
				gme_board[i][j] = gme_update[i][j];
				}
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
//Free memory
//sometimes you might encounter segmantation, if you want to always avoid that comment lines 140,141 and uncommenct 142,143
//According to Valgrind memcheck tool there might or there might not be an actual memory leak, I could not pinpoint where it is tbh.. :) 
	free_mem(gme_update, board_rows); 
    free_mem(gme_board, board_rows);
    //free(gme_board);
    //free(gme_update);
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
  for(i=n+1; i>=0; i--){ 
     free(arr[i]);
    }
  free(arr);
}
