#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#define INPUT_BUF 1024

char *get_input(int *num_chars, int *num_lines, int *num_words, bool is_lines, bool is_word) {
    char *buffer = malloc(INPUT_BUF * sizeof(char));
    if (!buffer) {
        perror("malloc");
        exit(1);
    }
    memset(buffer, 0, INPUT_BUF);

    while (fgets(buffer, INPUT_BUF, stdin) != NULL) {
        if (is_lines == true && is_word == false) {
            for (size_t i = 0; i < strlen(buffer); i++) {
                if (errno == EINTR) { // Check for Ctrl+C
                    break;
                }
                if (buffer[i] == '\n') {
                    *num_lines += 1;
                }
            }
        } else if (is_lines == false && is_word == false) {
            for (size_t i = 0; i < strlen(buffer); i++) {
                if (errno == EINTR) { // Check for Ctrl+C
                    break;
                }

                *num_chars += 1;
            }
        } else if (is_word == true && is_lines == false) {
            for (size_t i = 0; i < strlen(buffer); i++) {
                if (errno == EINTR) { // Check for Ctrl+C
                    break;
                }

                if (buffer[i] == ' ' || buffer[i] == '\n') {
                    *num_words += 1;
                }
            }
        }
    }
    return buffer;
}

int main(int argc, char *argv[]) {
    int chars = 0;
    int lines = 0;
    int words = 0;

    if (argc < 2) {
        puts("No text given");
        return 1;
    } else {
        if (strncmp(argv[1], "-c", strlen(argv[1])) == 0) {
            char *line = get_input(&chars, &lines, &words, false, false);
            printf("%d\n", chars);
            free(line);
        } else if (strncmp(argv[1], "-l", strlen(argv[1])) == 0) {
            char *line = get_input(&chars, &lines, &words, true, false);
            printf("%d\n", lines);
            free(line);
        } else if (strncmp(argv[1], "-w", strlen(argv[1])) == 0) {
            char *line = get_input(&chars, &lines, &words, false, true);
            printf("%d\n", words);
            free(line);
        } else {
            puts("Usage: wc [-c|-l|-w]");
            return 0;
        }
    }

    return 0;
}
