#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "input"
#define NB_ROWS 128
#define NB_COLS 8
#define LOG2_ROWS 7 // log2(NB_ROWS)
#define LOG2_COLS 3 // log2(NB_COLS)

unsigned seat_ID(const char *s)
{
	unsigned ID = 0;
	for (size_t i = 0; i < LOG2_ROWS; ++i) {
		ID <<= 1;
		ID += s[i] == 'B' ? 1 : 0;
	}
	for (size_t i = 7; i < LOG2_ROWS + LOG2_COLS; ++i) {
		ID <<= 1;
		ID += s[i] == 'R' ? 1 : 0;
	}
	return ID;
}

int main(void)
{
        FILE *fp;

        if ((fp = fopen(FILENAME, "r")) == NULL) {
                fprintf(stderr, "Can't open " FILENAME " for read: %s\n",
                        strerror(errno));
                return EXIT_FAILURE;
        }

	char buff[11] = {0};
	bool taken_seats[NB_ROWS * NB_COLS] = {false};

	while (fscanf(fp, "%10s\n", buff) == 1)
		taken_seats[seat_ID(buff)] = true;

	fclose(fp);

	unsigned ID = NB_ROWS * NB_COLS - 1;
	while (!taken_seats[ID] && ID != 0)
		--ID;
	
	printf("Part one: %u\n", ID);

	ID = 1;
	while (!taken_seats[ID + 1] || taken_seats[ID] || !taken_seats[ID - 1])
		++ID;
	printf("Part two: %u\n", ID);

	return EXIT_SUCCESS;
}
	
