#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "input"
#define MAX_PASSWORD_LENGTH 200

bool is_valid_password_silver(size_t low, size_t high, char c, const char * password)
{
        size_t count = 0;
        while (*password) {
                if (*password == c)
                        ++count;
                ++password;
        }
        return low <= count && count <= high;
}

bool is_valid_password_gold(size_t low, size_t high, char c, const char * password)
{
        return (password[low-1] == c) ^ (password[high-1] == c);
}

int main(void)
{
        FILE *fp;

        if ((fp = fopen(FILENAME, "r")) == NULL) {
                fprintf(stderr, "Can't open " FILENAME " for read: %s\n",
                        strerror(errno));
                exit(EXIT_FAILURE);
        }

        size_t nb_valid_passwords_silver = 0;
        size_t nb_valid_passwords_gold = 0;
        size_t low, high;
        char c;
        char password[MAX_PASSWORD_LENGTH + 1];
        
        while (fscanf(fp, "%zu-%zu %c: %s\n", &low, &high, &c, password) == 4) {
                if (is_valid_password_silver(low, high, c, password))
                        ++nb_valid_passwords_silver;
                if (is_valid_password_gold(low, high, c, password))
                        ++nb_valid_passwords_gold;
        }

        fclose(fp);
        
        printf("%zu\n", nb_valid_passwords_silver);
        printf("%zu\n", nb_valid_passwords_gold);

        return EXIT_SUCCESS;
}
