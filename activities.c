#include "activities.h"

void activities()
{
    int home_pid = getpid();
    DIR *dir;
    struct dirent *entry;
    int count = 0;
    // open the proc directory
    dir = opendir("/proc");
    // for pid in proc directory if the ppid of the pid is equal to home_pid then count++
    while ((entry = readdir(dir)) != NULL) {
        if (atoi(entry->d_name) == home_pid) {
            continue;
        }
        char status_path[256];
        sprintf(status_path, "/proc/%s/status", entry->d_name);
        FILE *status_file = fopen(status_path, "r");
        if (status_file) {
            char line[256];
            while (fgets(line, sizeof(line), status_file)) {
                if (strncmp(line, "PPid:", 5) == 0) {
                    int ppid = atoi(line + 6);
                    if (ppid == home_pid) {
                        count++;
                    }
                    break;
                }
            }
            fclose(status_file);
        }
    }
    closedir(dir);
    int child_pid[count];
    int i = 0;
    dir = opendir("/proc");
    while ((entry = readdir(dir)) != NULL) {
        if (atoi(entry->d_name) == home_pid) {
            continue;
        }
        char status_path[256];
        sprintf(status_path, "/proc/%s/status", entry->d_name);
        FILE *status_file = fopen(status_path, "r");
        if (status_file) {
            char line[256];
            while (fgets(line, sizeof(line), status_file)) {
                if (strncmp(line, "PPid:", 5) == 0) {
                    int ppid = atoi(line + 6);
                    if (ppid == home_pid) {
                        child_pid[i] = atoi(entry->d_name);
                        i++;
                    }
                    break;
                }
            }
            fclose(status_file);
        }
    }
    closedir(dir);
    dir = opendir("/proc");
    char* child_cmd[count];
    // also get the input command of the child pid
    for(int j = 0; j < count; j++)
    {
        char status_path[256];
        sprintf(status_path, "/proc/%d/status", child_pid[j]);
        FILE *status_file = fopen(status_path, "r");
        char cmd[256];
        if (status_file) {
            char line[256];
            
            while (fgets(line, sizeof(line), status_file)) {
                if (strncmp(line, "Name:", 5) == 0) {
                    sscanf(line, "Name: %s", cmd);
                    child_cmd[j] = strdup(cmd);
                    break;
                }
            }
            fclose(status_file);
        }
    }
    closedir(dir);

    // print the child pids, their status
    for(int j = 0; j < count; j++)
    {
        char status_path[256];
        sprintf(status_path, "/proc/%d/status", child_pid[j]);
        FILE *status_file = fopen(status_path, "r");
        char cmd[256];
        if (status_file) {
            char line[256];
            
            while (fgets(line, sizeof(line), status_file)) {
                if (strncmp(line, "State:", 6) == 0) {
                    sscanf(line, "Name: %s", cmd);
                    char status = line[7];
                    char status_plus = (status == 'R' || status == 'S' || status == 'Z') ? '+' : '-';
                    if(status == 'R')
                    {
                        printf("%d: %s Running\n", child_pid[j], child_cmd[j]);
                    }
                    else
                    {
                        printf("%d: %s Sleeping\n", child_pid[j], child_cmd[j]);
                    }
                    break;
                }
            }
            fclose(status_file);
        }
    }
    
}
