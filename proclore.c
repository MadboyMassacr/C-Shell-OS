#include "proclore.h"

void proclore(char* token)
{
    if(token == NULL)
    {
        pid_t pid = getpid();
        printf("pid : %d\n", pid);

        // Get the process status
        char status_path[256];
        sprintf(status_path, "/proc/%d/status", pid);
        FILE *status_file = fopen(status_path, "r");
        if (status_file) {
            char line[256];
            while (fgets(line, sizeof(line), status_file)) {
                if (strncmp(line, "State:", 6) == 0) {
                    char status = line[7];
                    char status_plus = (status == 'R' || status == 'S' || status == 'Z') ? '+' : '-';
                    printf("process status : %c%c\n", status, status_plus);
                    break;
                }
            }
            fclose(status_file);
        }

        // Get the process group
        pid_t pgid = getpgid(pid);
        printf("Process Group : %d\n", pgid);

        // Get virtual memory information
        long pages = sysconf(_SC_PHYS_PAGES);
        long page_size = sysconf(_SC_PAGE_SIZE);
        printf("Virtual memory : %ld\n", pages * page_size);

        // Get the executable path
        char exe_path[256];
        ssize_t len = readlink("/proc/self/exe", exe_path, sizeof(exe_path)-1);
        if (len != -1) {
            exe_path[len] = '\0';
            printf("executable path : %s\n", exe_path);
        }

    }
    else
    {
        // token is the pid
        pid_t pid = atoi(token);
        printf("pid : %d\n", pid);

        // Get the process status
        char status_path[256];
        sprintf(status_path, "/proc/%d/status", pid);
        FILE *status_file = fopen(status_path, "r");
        if (status_file) {
            char line[256];
            while (fgets(line, sizeof(line), status_file)) {
                if (strncmp(line, "State:", 6) == 0) {
                    char status = line[7];
                    char status_plus = (status == 'R' || status == 'S' || status == 'Z') ? '+' : '-';
                    printf("process status : %c%c\n", status, status_plus);
                    break;
                }
            }
            fclose(status_file);
        }

        // Get the process group
        pid_t pgid = getpgid(pid);
        printf("Process Group : %d\n", pgid);

        // Get virtual memory information
        long pages = sysconf(_SC_PHYS_PAGES);
        long page_size = sysconf(_SC_PAGE_SIZE);
        printf("Virtual memory : %ld\n", pages * page_size);

        char procPath[128];
        snprintf(procPath, sizeof(procPath), "/proc/%d/exe", pid);

        // Read the symbolic link that points to the executable file
        char exePath[4096];
        ssize_t len = readlink(procPath, exePath, sizeof(exePath) - 1);

        if (len != -1) {
            exePath[len] = '\0';
            printf("Executable path of process %d: %s\n", pid, exePath);
        } else {
            perror("readlink");
        }

    }
    return;
    
}
