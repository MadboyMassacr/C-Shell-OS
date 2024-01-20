#include "neonate.h"

void neonate(char* token) 
{
    int time_arg = atoi(token);
    struct termios oldt, newt;
    char ch;
    DIR *dir;
    struct dirent *entry;
    unsigned long long latest_start_time = 0;
    char latest_pid[20];

    
    // if (dir == NULL) {
    //     perror("opendir");
    //     exit(EXIT_FAILURE);
    // }

    // Initialize terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Set STDIN to non-blocking mode
    int flags = fcntl(STDIN_FILENO, F_GETFL);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    while (1) {
        dir = opendir("/proc");
        int i = -1;
        // while entry is not null and entry is integer if its greater than i, then set i to entry
        while ((entry = readdir(dir)) != NULL) {
            if (atoi(entry->d_name) > i) {
                i = atoi(entry->d_name);
            }
        }
        printf("%d\n", i);
        closedir(dir);

        // Check for 'x' keypress
        if (read(STDIN_FILENO, &ch, 1) == 1 && ch == 'x') {
            break;
        }

        // Sleep for the specified time_arg
        sleep(time_arg); // Convert seconds to microseconds
    }

    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, flags);
    return;
}
