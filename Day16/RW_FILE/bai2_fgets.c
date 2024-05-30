#include <stdio.h>
#include <string.h>

int main() {
    FILE *f;
    f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("Cannot open file!\n");
    } else {
        char s[1000];
        if (fgets(s, 1000, f) != NULL) {
            // Remove newline character at the end, if present
            size_t len = strlen(s);
            if (len > 0 && s[len - 1] == '\n') {
                s[len - 1] = '\0';
            }
            printf("Data: %s\n", s);
        } else {
            printf("Error reading from file!\n");
        }
        fclose(f);
    }
    return 0;
}
