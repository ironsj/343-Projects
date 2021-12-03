#include "life.h"

int main(int argc, char** argv) {
	// The program requires a file name to start.
	if (argc != 2) {
		printf("Wrong number of arguments to program. This program requires a filename as argument.\n");
		printf("Usage: ./driver filename\n");
		printf("Example: ./driver beacon.gol\n");
		exit(EXIT_FAILURE);
	}

    int rows, cols;
    char **grid, **mutatedGrid, *str;

    grid = loadGridFromFile(argv[1],&rows,&cols);
    str = toString(rows,cols,grid);
    printf("%s\n",str);
    free(str);

    while (true) {
		printf("Press q to quit, n to iterate, w to save to file, or any other key to move to next generation: ");
		char input[5];
		fgets(input,5,stdin);

        switch(input[0]) {
            case 'q':
			case 'Q':
				// free memory and exit the game.
				free(grid);
				return 0;

            case 'w':
			case 'W':
				printf("Enter a filename: ");
				char filename[254];
				fgets(filename,254,stdin);
				// replace newline character with string terminator character
				filename[strlen(filename)-1] = '\0';
                saveGridToFile(filename,rows,cols,grid);
                break;

            case 'n':
			case 'N':
				printf("How many iterations? ");
				char buf[5];
				fgets(buf,5,stdin);
                // replace newline character with string terminator character
				buf[strlen(buf)-1] = '\0';
				int num = atoi(buf);

				printf("Iterating %d times.\n\n",num);
				for(int i = 0; i < num; ++i) {
					mutatedGrid = mutateGrid(rows,cols,grid);
					str = toString(rows,cols,mutatedGrid);
                    printf("%s\n",str);
                    free(str);
                    free(grid);
                    grid = mutatedGrid;
				}	
				break;

            default:
				mutatedGrid = mutateGrid(rows,cols,grid);
				str = toString(rows,cols,mutatedGrid);
                printf("%s\n",str);
                free(str);
                free(grid);
                grid = mutatedGrid;               
        }
    }

    return EXIT_SUCCESS;
}
