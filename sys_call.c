#include "header.h"

void sys_call(char* input_cpy, int fun_len) {
    if (input_cpy[fun_len - 1] != '&') {
        pid_t child = fork();
        if (child == 0) {
            // Parse the command
            char* args[256];
            int i = 0;
            char* token = strtok(input_cpy, " ");
            while (token != NULL) {
                args[i++] = token;
                token = strtok(NULL, " ");
            }
            args[i] = NULL;

            // Execute the command
            if (execvp(args[0], args) == -1) {
                // perror("execvp");
                exit(EXIT_FAILURE);
            }
        } else if (child < 0) {
            // perror("fork");
            printf("Error in forking\n");
        } else {
            // Wait for the child process to complete
            int status;
            waitpid(child, &status, 0);
            // printf("Child process %d exited with status %d\n", child, status);
        }
    } else {
        input_cpy[fun_len - 1] = '\0';
        pid_t child = fork();
        if (child == 0) {
            freopen("/dev/null", "w", stdout);
            // Parse the command (same as above)
            char* args[256];
            int i = 0;
            char* token = strtok(input_cpy, " ");
            while (token != NULL) {
                args[i++] = token;
                token = strtok(NULL, " ");
            }
            args[i] = NULL;

            // Execute the command
            if (execvp(args[0], args) == -1) {
                // perror("execvp");
                exit(EXIT_FAILURE);
            }
        } else if (child < 0) {
            // perror("fork");
            printf("Error in forking\n");
        } else {
            // printf("Child process %d running in the background\n", child);
        }
    }
}
