//***************************************************
// Filename: life.c
//
// Author(s): Jake Irons
//***************************************************

#include "life.h"

// Constructs and returns a string (printable) representation of the grid
char *toString(int rows, int cols, char **grid)
{
	char *str = (char *) calloc(4 * rows * cols, sizeof(char));
	char *ptr = str;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
		    if (grid[i][j] == '0') {
		        sprintf(ptr," . ");
		    } else {
		        sprintf(ptr," X ");
		    }
				ptr += 3;;
			}
			sprintf(ptr,"\n");
			ptr++;
		}

	return str;
}

// Creates a grid of rows x cols and initializes the grid with data from specified file
char **loadGridFromFile(char *filename, int *rows, int *cols)
{
	char **grid = NULL;
	char buf[1024]; // max length of line in input file
	FILE *file = fopen(filename,"r");
	
    	// read line from file
    	fgets(buf,1024,file);
    	fclose(file); 
    	
   	// get number of rows from the line read
    	*rows = atoi(strtok(buf," "));
    	
    	// get number of columns from the line read
    	*cols = atoi(strtok(NULL," "));
    	
	// COMPLETE THIS PART OF THIS FUNCTION
	grid = (char**)malloc(sizeof(char*)**rows);
	for (int i=0; i < *rows; i++){
		grid[i]= (char*)malloc(sizeof(char)**cols);
		for (int j=0; j < *cols; j++){
			grid[i][j] = *strtok(NULL, " ");
		}
	}
	
    	return grid;
}

// Saves the grid data to the specified file
void saveGridToFile(char *filename, int rows, int cols, char **grid)
{
	FILE *file = fopen(filename,"w");

	// COMPLETE THIS PART OF THIS FUNCTION
	fprintf(file, "%d ", rows);
	fprintf(file, "%d ", cols);
	
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			fprintf(file, "%d ", grid[i][j] - '0');
		}
	}

    	fclose(file);
}

// Creates and returns a new grid that is a duplicate of the given grid
char **copyGrid(int rows, int cols, char **grid)
{
    	char **dup = NULL;

	// COMPLETE THIS PART OF THIS FUNCTION
	dup = (char**)malloc(sizeof(char*)*rows);
	for (int i=0; i < rows; i++){
		dup[i]= (char*)malloc(sizeof(char)*cols);
		for (int j=0; j < cols; j++){
			dup[i][j] = grid[i][j];
		}
	}
    	return dup;
}

// Mutates the given grid one generation and return a new grid
char **mutateGrid(int rows, int cols, char **grid)
{
	char** newgrid = copyGrid(rows,cols,grid);
	// COMPLETE THIS PART OF THIS FUNCTION
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			if((nbrOfNeighbors(i, j , rows, cols, grid) < 2) && (grid[i][j] == '1')){
				newgrid[i][j] = '0';
			}
			else if(((nbrOfNeighbors(i, j , rows, cols, grid) == 3) || (nbrOfNeighbors(i, j , rows, cols, grid) == 2)) && (grid[i][j] == '1')){
				newgrid[i][j] = '1';
			}
			else if((nbrOfNeighbors(i, j , rows, cols, grid) > 3) && (grid[i][j] == '1')){
				newgrid[i][j] = '0';
			}
			if((nbrOfNeighbors(i, j , rows, cols, grid) == 3) && (grid[i][j] == '0')){
				newgrid[i][j] = '1';
			}
		}
	}

	return newgrid;
}

// Returns the number of neighbors at postion (i,j) in the grid
int nbrOfNeighbors(int i, int j, int rows, int cols, char **grid)
{
	int neighbors = 0;

	// COMPLETE THIS PART OF THIS FUNCTION
	int newRow;
	int newCol;
	for(int surrRow = -1; surrRow < 2; surrRow++){
		for(int surrCol = -1; surrCol < 2; surrCol++){
			if(surrRow != 0 || surrCol != 0){
				newRow = i + surrRow;
				newCol = j + surrCol;
				if((newRow >=0 && newRow < rows) && (newCol >= 0 && newCol < cols)){
					if(grid[newRow][newCol] == '1'){
						neighbors++;
					}
				} 
			}
		}
	}
	return neighbors;
}
