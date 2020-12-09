#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "input"
#define MAX_ROWS 1000
#define MAX_COLS 100

size_t nb_tree_slope(char grid[MAX_ROWS][MAX_COLS + 2], size_t rows, size_t cols, size_t right, size_t down)
{
	size_t i = 0;
	size_t j = 0;
	size_t t = 0;
	while (i < rows) {
		if (grid[i][j] == '#')
			++t;
		i = (i + down);
		j = (j + right) % cols;
	}
	return t;
}

int main(void)
{
        FILE *fp;

        if ((fp = fopen(FILENAME, "r")) == NULL) {
                fprintf(stderr, "Can't open " FILENAME " for read: %s\n",
                        strerror(errno));
                exit(EXIT_FAILURE);
        }

	char grid[MAX_ROWS][MAX_COLS + 2];

	size_t cols = 0;
	size_t rows = 0;

        while (rows < MAX_ROWS && fgets(grid[rows], MAX_COLS + 2, fp)) {
		++rows;
        }

	if (fgetc(fp) != EOF) {
		fprintf(stderr, "Input too long, try with a larger MAX_ROWS or MAX_COLS value\n");
		fclose(fp);
		return EXIT_FAILURE;
	}
	
	fclose(fp);
	
	if (rows == 0) {
		fprintf(stderr, "Wrong input file\n");
		return EXIT_FAILURE;
	}
	
	cols = strlen(grid[0]) - 1;

	if (grid[0][cols] != '\n') {
		fprintf(stderr, "Lines too long for input, try with a larger MAX_COLS value\n");
		return EXIT_FAILURE;
	}
        
        printf("Part one: %zu\n", nb_tree_slope(grid, rows, cols, 3, 1));
	printf("Part two: %zu\n",
	       nb_tree_slope(grid, rows, cols, 1, 1)
	       * nb_tree_slope(grid, rows, cols, 3, 1)
	       * nb_tree_slope(grid, rows, cols, 5, 1)
	       * nb_tree_slope(grid, rows, cols, 7, 1)
	       * nb_tree_slope(grid, rows, cols, 1, 2));
	
        return EXIT_SUCCESS;
}
