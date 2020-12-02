#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000
#define SUM 2020
#define FILENAME "input"

int comp(const void *px, const void *py)
{
	unsigned long x = *(unsigned long *)px;
	unsigned long y = *(unsigned long *)py;
	return (x >= y) - (x <= y);
}

int main(void)
{
	FILE *fp;

	if ((fp = fopen(FILENAME, "r")) == NULL) {
		fprintf(stderr, "Can't open " FILENAME " for read: %s\n",
			strerror(errno));
		exit(EXIT_FAILURE);
	}

	unsigned long numbers[MAX_LENGTH];
	size_t length = 0;

	while (length < MAX_LENGTH && fscanf(fp, "%lu\n", &numbers[length]) == 1)
		++length;

	if (fgetc(fp) != EOF) {
		fprintf(stderr, "Input too long, "
			"try recompiling with a bigger MAX_LENGTH value\n");
		fclose(fp);
		exit(EXIT_FAILURE);
	}

	fclose(fp);

	qsort(numbers, length, sizeof(unsigned long), comp);

	unsigned long *p;
	unsigned long to_search;

	/* Silver */
	for (size_t i = 0; i < length; ++i) {
		to_search = SUM - numbers[i];
		if (p = bsearch(&to_search, numbers, length, sizeof(unsigned long), comp)) {
			printf("Silver: %lu\n", numbers[i] * *p);
			break;
		}
	}

	/* Gold */
	for (size_t i = 0; i < length; ++i) {
		for (size_t j = i; j < length; ++j) {
			to_search = SUM - numbers[i] - numbers[j];
			if (p = bsearch(&to_search, numbers, length, sizeof(unsigned), comp)) {
				printf("Gold: %lu\n", numbers[i] * numbers[j] * *p);
				return EXIT_SUCCESS;
			}
		}
	}

	return EXIT_FAILURE;
}
