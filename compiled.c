#include<stdio.h>
#include <unistd.h>
#include<pwd.h>
#include<string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include<stdlib.h>
#include <grp.h>
#include <time.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/socket.h>
#include<arpa/inet.h>
#include <netdb.h>
#include<netdb.h>


void warp(char* token, char* pwd, char* hwd)
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    
    if(token == NULL)
    {
        if(strcmp(cwd, pwd) == 0)
        {
            chdir(getpwuid(1000)->pw_dir);
            printf("%s\n", getcwd(NULL, 0));
            getcwd(cwd, sizeof(cwd));
        }
        else
        {
            chdir(getpwuid(1000)->pw_dir);
            printf("%s\n", getcwd(NULL, 0));
            strcpy(pwd, cwd);
            getcwd(cwd, sizeof(cwd));
           
        }
    }
    else if(strcmp(token, ".") == 0)
    {
        printf("%s\n", getcwd(NULL, 0));
    }
    else if(strcmp(token, "..") == 0)
    {
        chdir("..");
        printf("%s\n", getcwd(NULL, 0));
        if(strcmp(cwd, pwd) == 0)
        {
            getcwd(cwd, sizeof(cwd));
        }
        else
        {
            strcpy(pwd, cwd);
            getcwd(cwd, sizeof(cwd));
           
        }
    }
    else if(strcmp(token, "~") == 0)
    {
        if(strcmp(cwd, pwd) == 0)
        {
            chdir(hwd);
            printf("%s\n", getcwd(NULL, 0));
            getcwd(cwd, sizeof(cwd));
        }
        else
        {
            chdir(hwd);
            printf("%s\n", getcwd(NULL, 0));
            strcpy(pwd, cwd);
            getcwd(cwd, sizeof(cwd));
           
        }
    }
    else if(strcmp(token, "-") == 0)
    {
        if(strcmp(cwd, pwd) == 0)
        {
            printf("No previous directory\n");
        }
        else
        {
            chdir(pwd);
            printf("%s\n", getcwd(NULL, 0));
            strcpy(pwd, cwd);
            getcwd(cwd, sizeof(cwd));
        }
       
    }
    else if (token[0] == '.' && token[1] == '/')
    {
        if(strcmp(cwd, pwd) == 0)
        {
            // make a copy of token from index 2 to end
            char *newtoken = (char*)malloc(strlen(token) - 1);
            for (int i = 2; i < strlen(token); i++)
            {
                newtoken[i - 2] = token[i];
            }
            chdir(newtoken);
            printf("%s\n", getcwd(NULL, 0));
            getcwd(cwd, sizeof(cwd));
        }
        else
        {
            char *newtoken = (char*)malloc(strlen(token) - 1);
            for (int i = 2; i < strlen(token); i++)
            {
                newtoken[i - 2] = token[i];
            }
            chdir(newtoken);
            printf("%s\n", getcwd(NULL, 0));
            strcpy(pwd, cwd);
            getcwd(cwd, sizeof(cwd));
           
        }
    }
    else if (&token[0] == "." && &token[1] == "." && &token[2] == "/")
    {
        if(strcmp(cwd, pwd) == 0)
        {
            chdir("..");
            char *newtoken = (char*)malloc(strlen(token) - 1);
            for (int i = 2; i < strlen(token); i++)
            {
                newtoken[i - 2] = token[i];
            }
            chdir(newtoken);
            printf("%s\n", getcwd(NULL, 0));
            getcwd(cwd, sizeof(cwd));
        }
        else
        {
            chdir("..");
            char *newtoken = (char*)malloc(strlen(token) - 1);
            for (int i = 2; i < strlen(token); i++)
            {
                newtoken[i - 2] = token[i];
            }
            chdir(newtoken);
            printf("%s\n", getcwd(NULL, 0));
            strcpy(pwd, cwd);
            getcwd(cwd, sizeof(cwd));
           
        }
    }
    else if (token[0] == '~' && token[1] == '/')
    {
        if(strcmp(cwd, pwd) == 0)
        {
            chdir(hwd);
            char *newtoken = (char*)malloc(strlen(token) - 1);
            for (int i = 2; i < strlen(token); i++)
            {
                newtoken[i - 2] = token[i];
            }
            chdir(newtoken);
            printf("%s\n", getcwd(NULL, 0));
            getcwd(cwd, sizeof(cwd));
        }
        else
        {
            chdir(hwd);
            char *newtoken = (char*)malloc(strlen(token) - 1);
            for (int i = 2; i < strlen(token); i++)
            {
                newtoken[i - 2] = token[i];
            }
            chdir(newtoken);
            printf("%s\n", getcwd(NULL, 0));
            strcpy(pwd, cwd);
            getcwd(cwd, sizeof(cwd));
           
        }
    }
    else if (token[0] == '-' && token[1] == '/')
    {
        if(strcmp(cwd, pwd) == 0)
        {
            printf("No previous directory\n");
        }
        else
        {
            chdir(pwd);
            char *newtoken = (char*)malloc(strlen(token) - 1);
            for (int i = 2; i < strlen(token); i++)
            {
                newtoken[i - 2] = token[i];
            }
            chdir(newtoken);
            printf("%s\n", getcwd(NULL, 0));
            strcpy(pwd, cwd);
            getcwd(cwd, sizeof(cwd));
        }
    }
    else
    {
        if(strcmp(cwd, pwd) == 0)
        {
            chdir(token);
            printf("%s\n", getcwd(NULL, 0));
            getcwd(cwd, sizeof(cwd));
        }
        else
        {
            chdir(token);
            printf("%s\n", getcwd(NULL, 0));
            strcpy(pwd, cwd);
            getcwd(cwd, sizeof(cwd));
           
        }

    }
    token = strtok(NULL, " ");
    if(token != NULL)
    {
        if(strcmp(cwd, pwd) == 0)
        {
            chdir(token);
            printf("%s\n", getcwd(NULL, 0));
            getcwd(cwd, sizeof(cwd));
        }
        else
        {
            chdir(token);
            printf("%s\n", getcwd(NULL, 0));
            strcpy(pwd, cwd);
            getcwd(cwd, sizeof(cwd));
           
        }
    }
    return;
}

int compare(const void *a, const void *b) 
{
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;

    // Ignore leading dots ('.') if they exist
    if (str1[0] == '.') str1++;
    if (str2[0] == '.') str2++;

    return strcmp(str1, str2);
}

void print_permissions(mode_t mode) 
{
    putchar((mode & S_IRUSR) ? 'r' : '-');
    putchar((mode & S_IWUSR) ? 'w' : '-');
    putchar((mode & S_IXUSR) ? 'x' : '-');
    putchar((mode & S_IRGRP) ? 'r' : '-');
    putchar((mode & S_IWGRP) ? 'w' : '-');
    putchar((mode & S_IXGRP) ? 'x' : '-');
    putchar((mode & S_IROTH) ? 'r' : '-');
    putchar((mode & S_IWOTH) ? 'w' : '-');
    putchar((mode & S_IXOTH) ? 'x' : '-');
}

void peek(char* input, char* token1, char* token2, char* token3, char* token4, char* pwd, char* hwd)
{

    if(token2 == NULL || strcmp(token2, ".") == 0)
    {
        const char *dir_path = ".";
        DIR *dir = opendir(dir_path);
        char *entries[1024]; 
        int count = 0;
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) 
        {
            if (entry->d_name[0] != '.') 
            {
                entries[count] = strdup(entry->d_name);
                count++;
            }
        }
        closedir(dir);

        qsort(entries, count, sizeof(char *), compare);
        for (int i = 0; i < count; i++) 
        {
            printf("%s\n", entries[i]);
            free(entries[i]); 
        }
    }
    else if(token2[0] == '.' && token2[1] == '/')
    {
        char *newtoken = (char*)malloc(strlen(token2) - 1);
            for (int i = 2; i < strlen(token2); i++)
            {
                newtoken[i - 2] = token2[i];
            }
        const char *dir_path = newtoken;
        DIR *dir = opendir(dir_path);
        char *entries[1024]; 
        int count = 0;
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) 
        {
            if (entry->d_name[0] != '.') 
            {
                entries[count] = strdup(entry->d_name);
                count++;
            }
        }
        closedir(dir);

        qsort(entries, count, sizeof(char *), compare);
        for (int i = 0; i < count; i++) 
        {
            printf("%s\n", entries[i]);
            free(entries[i]); 
        }
    }
    else if (token2[0] == '.' && token2[1] == '.' && token2[2] == '/') 
    {
        char *newtoken = (char*)malloc(strlen(token2) + 1); // Allocate enough memory
        if (newtoken == NULL) {
            // Handle memory allocation failure
            perror("Memory allocation failed");
            return;
        }
        strcpy(newtoken, token2 + 3); // Copy everything after "../" into newtoken

        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        if (chdir("..") != 0) {
            perror("chdir failed"); // Handle directory change failure
            free(newtoken); // Free allocated memory
            return;
        }
        
        const char *dir_path = newtoken;
        DIR *dir = opendir(dir_path);
        if (dir == NULL) {
            perror("opendir failed"); // Handle directory open failure
            free(newtoken); // Free allocated memory
            chdir(cwd); // Restore the original directory
            return;
        }

        char *entries[1024];
        int count = 0;
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_name[0] != '.') {
                entries[count] = strdup(entry->d_name);
                count++;
            }
        }
        closedir(dir);

        if (count >= 1024) {
            // Handle too many entries
        } else {
            qsort(entries, count, sizeof(char *), compare);
            for (int i = 0; i < count; i++) {
                printf("%s\n", entries[i]);
                free(entries[i]);
            }
        }

        chdir(cwd);
        free(newtoken); // Free allocated memory
    }

    else if(token2[0] == '~' && token2[1] == '/')
    {
        char *newtoken = (char*)malloc(strlen(token2) - 1);
            for (int i = 2; i < strlen(token2); i++)
            {
                newtoken[i - 2] = token2[i];
            }
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        chdir(hwd);
        const char *dir_path = newtoken;
        DIR *dir = opendir(dir_path);
        char *entries[1024]; 
        int count = 0;
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) 
        {
            if (entry->d_name[0] != '.') 
            {
                entries[count] = strdup(entry->d_name);
                count++;
            }
        }
        closedir(dir);

        qsort(entries, count, sizeof(char *), compare);
        for (int i = 0; i < count; i++) 
        {
            printf("%s\n", entries[i]);
            free(entries[i]); 
        }
        chdir(cwd);
    }
    else if (token2[0] == '-' && token2[1] == '/') 
    {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));

        if (strcmp(cwd, pwd) == 0) {
            printf("No previous directory\n");
            return; // No need to proceed further
        }

        chdir(pwd);

        char *newtoken = (char *)malloc(strlen(token2) - 1); // Allocate enough memory
        if (newtoken == NULL) {
            // Handle memory allocation failure
            perror("Memory allocation failed");
            chdir(cwd); // Restore the original directory
            return;
        }
        strcpy(newtoken, token2 + 2); // Copy everything after "-/" into newtoken

        const char *dir_path = newtoken;
        DIR *dir = opendir(dir_path);
        if (dir == NULL) {
            perror("opendir failed"); // Handle directory open failure
            free(newtoken); // Free allocated memory
            chdir(cwd); // Restore the original directory
            return;
        }

        char *entries[1024];
        int count = 0;
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_name[0] != '.') {
                entries[count] = strdup(entry->d_name);
                count++;
            }
        }
        closedir(dir);

        if (count >= 1024) {
            // Handle too many entries
        } else {
            qsort(entries, count, sizeof(char *), compare);
            for (int i = 0; i < count; i++) {
                printf("%s\n", entries[i]);
                free(entries[i]);
            }
        }

        chdir(cwd); // Restore the original directory
        free(newtoken); // Free allocated memory
    }

    else if(strcmp(token2, "..") == 0)
    {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        chdir("..");
        const char *dir_path = ".";
        DIR *dir = opendir(dir_path);
        char *entries[1024]; 
        int count = 0;
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) 
        {
            if (entry->d_name[0] != '.') 
            {
                entries[count] = strdup(entry->d_name);
                count++;
            }
        }
        closedir(dir);

        qsort(entries, count, sizeof(char *), compare);
        for (int i = 0; i < count; i++) 
        {
            printf("%s\n", entries[i]);
            free(entries[i]); 
        }
        chdir(cwd);
    }
    else if(strcmp(token2, "~") == 0)
    {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        chdir(hwd);
        const char *dir_path = ".";
        DIR *dir = opendir(dir_path);
        char *entries[1024]; 
        int count = 0;
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) 
        {
            if (entry->d_name[0] != '.') 
            {
                entries[count] = strdup(entry->d_name);
                count++;
            }
        }
        closedir(dir);

        qsort(entries, count, sizeof(char *), compare);
        for (int i = 0; i < count; i++) 
        {
            printf("%s\n", entries[i]);
            free(entries[i]); 
        }
        chdir(cwd);
    }
    else if(strcmp(token2, "-") == 0)
    {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        if(strcmp(cwd, pwd) == 0)
        {
            printf("No previous directory\n");
        }
        else
        {
            chdir(pwd);
            const char *dir_path = ".";
            DIR *dir = opendir(dir_path);
            char *entries[1024]; 
            int count = 0;
            struct dirent *entry;
            while ((entry = readdir(dir)) != NULL) 
            {
                if (entry->d_name[0] != '.') 
                {
                    entries[count] = strdup(entry->d_name);
                    count++;
                }
            }
            closedir(dir);

            qsort(entries, count, sizeof(char *), compare);
            for (int i = 0; i < count; i++) 
            {
                printf("%s\n", entries[i]);
                free(entries[i]); 
            }
            chdir(cwd);
        }
        
    }
    else if (strcmp(token2, "-a") == 0 && token3 == NULL)
    {
        const char *dir_path = ".";
        DIR *dir = opendir(dir_path);
        char *entries[1024]; 
        int count = 0;
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) 
        {
            entries[count] = strdup(entry->d_name);
            count++;
        }
        closedir(dir);

        qsort(entries, count, sizeof(char *), compare);
        for (int i = 0; i < count; i++) 
        {
            printf("%s\n", entries[i]);
            free(entries[i]); 
        }
    }
    else if(strcmp(token2, "-l") == 0 && token3 == NULL)
    {
        const char *dir_path = ".";
        DIR *dir = opendir(dir_path);
        char *entries[1024]; // Assuming a maximum of 1024 entries; you can adjust this if needed.
        int count = 0;

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) 
        {
            
            if (entry->d_name[0] != '.') 
                {
                    entries[count] = strdup(entry->d_name);
                    count++;
                }
        }

        closedir(dir);

        // Sort the array of names lexicographically
        qsort(entries, count, sizeof(char *), compare);

        // Print entries in -l format
        for (int i = 0; i < count; i++) {
            char file_path[1024]; // Assuming a maximum path length of 1024 characters
            snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, entries[i]);

            struct stat file_info;
            if (stat(file_path, &file_info) == -1) {
                perror("stat");
                continue;
            }

            print_permissions(file_info.st_mode);
            printf(" %ld ", (long)file_info.st_nlink);

            struct passwd *owner_info = getpwuid(file_info.st_uid);
            struct group *group_info = getgrgid(file_info.st_gid);

            if (owner_info != NULL) {
                printf("%s ", owner_info->pw_name);
            } else {
                printf("%d ", (int)file_info.st_uid);
            }

            if (group_info != NULL) {
                printf("%s ", group_info->gr_name);
            } else {
                printf("%d ", (int)file_info.st_gid);
            }

            printf("%ld ", (long)file_info.st_size);

            struct tm *time_info = localtime(&file_info.st_mtime);
            char time_buffer[80];
            strftime(time_buffer, sizeof(time_buffer), "%b %d %Y %H:%M", time_info);
            printf("%s ", time_buffer);

            printf("%s\n", entries[i]);

            free(entries[i]);
        }
        
    
    }
    else if (((strcmp(token2, "-la") == 0) && token3 == NULL) || ((strcmp(token2, "-al") == 0) && token3 == NULL) || ((strcmp(token2, "-l") == 0) && (strcmp(token3, "-a") == 0) && token4 == NULL) || ((strcmp(token2, "-a") == 0) && (strcmp(token3, "-l") == 0) && token4 == NULL))
    {
        const char *dir_path = ".";
        DIR *dir = opendir(dir_path);
        char *entries[1024]; // Assuming a maximum of 1024 entries; you can adjust this if needed.
        int count = 0;

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) 
        {
            entries[count] = strdup(entry->d_name);
            count++;
        }

        closedir(dir);

        // Sort the array of names lexicographically
        qsort(entries, count, sizeof(char *), compare);

        // Print entries in -l format
        for (int i = 0; i < count; i++) {
            char file_path[1024]; // Assuming a maximum path length of 1024 characters
            snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, entries[i]);

            struct stat file_info;
            if (stat(file_path, &file_info) == -1) {
                perror("stat");
                continue;
            }

            print_permissions(file_info.st_mode);
            printf(" %ld ", (long)file_info.st_nlink);

            struct passwd *owner_info = getpwuid(file_info.st_uid);
            struct group *group_info = getgrgid(file_info.st_gid);

            if (owner_info != NULL) {
                printf("%s ", owner_info->pw_name);
            } else {
                printf("%d ", (int)file_info.st_uid);
            }

            if (group_info != NULL) {
                printf("%s ", group_info->gr_name);
            } else {
                printf("%d ", (int)file_info.st_gid);
            }

            printf("%ld ", (long)file_info.st_size);

            struct tm *time_info = localtime(&file_info.st_mtime);
            char time_buffer[80];
            strftime(time_buffer, sizeof(time_buffer), "%b %d %Y %H:%M", time_info);
            printf("%s ", time_buffer);

            printf("%s\n", entries[i]);

            free(entries[i]);
        }

    }
    else if(token2 != NULL && strcmp(token2, "-l") != 0 && strcmp(token2, "-a") != 0 && strcmp(token2, "-la") != 0 && strcmp(token2, "-al") != 0)
    {
        const char *dir_path = strdup(token2);
        DIR *dir = opendir(dir_path);
        char *entries[1024]; 
        int count = 0;
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) 
        {
            if (entry->d_name[0] != '.') 
            {
                entries[count] = strdup(entry->d_name);
                count++;
            }
        }
        closedir(dir);

        qsort(entries, count, sizeof(char *), compare);
        for (int i = 0; i < count; i++) 
        {
            printf("%s\n", entries[i]);
            free(entries[i]); 
        }
    }
    else if (strcmp(token2, "-a") == 0 && token3 != NULL && strcmp(token3, "-l") != 0) 
    {
        const char *dir_path = strdup(token3);
        DIR *dir = opendir(dir_path);
        char *entries[1024]; 
        int count = 0;
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) 
        {
            entries[count] = strdup(entry->d_name);
            count++;
        }
        closedir(dir);

        qsort(entries, count, sizeof(char *), compare);
        for (int i = 0; i < count; i++) 
        {
            printf("%s\n", entries[i]);
            free(entries[i]); 
        }
    }
    else if(strcmp(token2, "-l") == 0 && token3 != NULL && strcmp(token3, "-a") != 0)
    {
        const char *dir_path = strdup(token3);
        DIR *dir = opendir(dir_path);
        char *entries[1024]; // Assuming a maximum of 1024 entries; you can adjust this if needed.
        int count = 0;

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) 
        {
            
            if (entry->d_name[0] != '.') 
                {
                    entries[count] = strdup(entry->d_name);
                    count++;
                }
        }

        closedir(dir);

        // Sort the array of names lexicographically
        qsort(entries, count, sizeof(char *), compare);

        // Print entries in -l format
        for (int i = 0; i < count; i++) {
            char file_path[1024]; // Assuming a maximum path length of 1024 characters
            snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, entries[i]);

            struct stat file_info;
            if (stat(file_path, &file_info) == -1) {
                perror("stat");
                continue;
            }

            print_permissions(file_info.st_mode);
            printf(" %ld ", (long)file_info.st_nlink);

            struct passwd *owner_info = getpwuid(file_info.st_uid);
            struct group *group_info = getgrgid(file_info.st_gid);

            if (owner_info != NULL) {
                printf("%s ", owner_info->pw_name);
            } else {
                printf("%d ", (int)file_info.st_uid);
            }

            if (group_info != NULL) {
                printf("%s ", group_info->gr_name);
            } else {
                printf("%d ", (int)file_info.st_gid);
            }

            printf("%ld ", (long)file_info.st_size);

            struct tm *time_info = localtime(&file_info.st_mtime);
            char time_buffer[80];
            strftime(time_buffer, sizeof(time_buffer), "%b %d %Y %H:%M", time_info);
            printf("%s ", time_buffer);

            printf("%s\n", entries[i]);

            free(entries[i]);
        }
        
    
    }
    else if (((strcmp(token2, "-la") == 0) && token3 != NULL) || ((strcmp(token2, "-al") == 0) && token3 != NULL))
    {
        const char *dir_path = strdup(token3);
        DIR *dir = opendir(dir_path);
        char *entries[1024]; // Assuming a maximum of 1024 entries; you can adjust this if needed.
        int count = 0;

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) 
        {
            entries[count] = strdup(entry->d_name);
            count++;
        }

        closedir(dir);

        // Sort the array of names lexicographically
        qsort(entries, count, sizeof(char *), compare);

        // Print entries in -l format
        for (int i = 0; i < count; i++) {
            char file_path[1024]; // Assuming a maximum path length of 1024 characters
            snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, entries[i]);

            struct stat file_info;
            if (stat(file_path, &file_info) == -1) {
                perror("stat");
                continue;
            }

            print_permissions(file_info.st_mode);
            printf(" %ld ", (long)file_info.st_nlink);

            struct passwd *owner_info = getpwuid(file_info.st_uid);
            struct group *group_info = getgrgid(file_info.st_gid);

            if (owner_info != NULL) {
                printf("%s ", owner_info->pw_name);
            } else {
                printf("%d ", (int)file_info.st_uid);
            }

            if (group_info != NULL) {
                printf("%s ", group_info->gr_name);
            } else {
                printf("%d ", (int)file_info.st_gid);
            }

            printf("%ld ", (long)file_info.st_size);

            struct tm *time_info = localtime(&file_info.st_mtime);
            char time_buffer[80];
            strftime(time_buffer, sizeof(time_buffer), "%b %d %Y %H:%M", time_info);
            printf("%s ", time_buffer);

            printf("%s\n", entries[i]);

            free(entries[i]);
        }

    }
    else if (((strcmp(token2, "-l") == 0) && (strcmp(token3, "-a") == 0) && token4 != NULL) || ((strcmp(token2, "-a") == 0) && (strcmp(token3, "-l") == 0) && token4 != NULL))
    {
        const char *dir_path = strdup(token4);
        DIR *dir = opendir(dir_path);
        char *entries[1024]; // Assuming a maximum of 1024 entries; you can adjust this if needed.
        int count = 0;

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) 
        {
            entries[count] = strdup(entry->d_name);
            count++;
        }

        closedir(dir);

        // Sort the array of names lexicographically
        qsort(entries, count, sizeof(char *), compare);

        // Print entries in -l format
        for (int i = 0; i < count; i++) {
            char file_path[1024]; // Assuming a maximum path length of 1024 characters
            snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, entries[i]);

            struct stat file_info;
            if (stat(file_path, &file_info) == -1) {
                perror("stat");
                continue;
            }

            print_permissions(file_info.st_mode);
            printf(" %ld ", (long)file_info.st_nlink);

            struct passwd *owner_info = getpwuid(file_info.st_uid);
            struct group *group_info = getgrgid(file_info.st_gid);

            if (owner_info != NULL) {
                printf("%s ", owner_info->pw_name);
            } else {
                printf("%d ", (int)file_info.st_uid);
            }

            if (group_info != NULL) {
                printf("%s ", group_info->gr_name);
            } else {
                printf("%d ", (int)file_info.st_gid);
            }

            printf("%ld ", (long)file_info.st_size);

            struct tm *time_info = localtime(&file_info.st_mtime);
            char time_buffer[80];
            strftime(time_buffer, sizeof(time_buffer), "%b %d %Y %H:%M", time_info);
            printf("%s ", time_buffer);

            printf("%s\n", entries[i]);

            free(entries[i]);
        }

    }
}

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

        // Get the executable path
        char exe_path[256];
        ssize_t len = readlink("/proc/%d/exe", exe_path, sizeof(exe_path)-1);
        if (len != -1) {
            exe_path[len] = '\0';
            printf("executable path : %s\n", exe_path);
        } else {
            printf("executable path : Not available\n");
        }

    }
    return;
    
}

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


struct CircularQueue {
    char data[15][255];
    int front;
    int rear;
    int size;
};

void initQueue(struct CircularQueue *queue) {
    queue->front = -1;
    queue->rear = -1;
    queue->size = 0;
}

int isFull(struct CircularQueue *queue) {
    return (queue->size == 15);
}

void enqueue(struct CircularQueue *queue, const char *item) {
    if (isFull(queue)) {
        for(int i = 0; i < 14; i++)
        {
            strcpy(queue->data[i], queue->data[i + 1]);
        }
        strcpy(queue->data[14], item);
        return;
    }

    // Move the rear pointer and add the item to the queue
    queue->rear = (queue->rear + 1) % 15;
    strcpy(queue->data[queue->rear], item);
    queue->size++;
}

void pastevents_append(char* input) {
    FILE *fp;
    char buff[255];
    char *test_token;
    struct CircularQueue queue;
    initQueue(&queue);

    fp = fopen("pastevents.txt", "r");

    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    // Read lines from the file into the circular queue
    while (fgets(buff, sizeof(buff), fp) != NULL) {
        // Remove the trailing newline character, if present
        size_t len = strlen(buff);
        if (len > 0 && buff[len - 1] == '\n') {
            buff[len - 1] = '\0';
        }

        enqueue(&queue, buff);
    }

    fclose(fp);
    //if the input starts with pastevents,return
    test_token = strdup(input);
    test_token = strtok(test_token, " ");
    if(strcmp(test_token, "pastevents") == 0)
    {
        return;
    }
    //enque if the last element of queue is not the same as input
    if(strcmp(queue.data[queue.rear], input) != 0)
    {
        enqueue(&queue, input);
    }
    else
    {
        return;
    }

    // Append the input to the queue
    // enqueue(&queue, input);

    // Open the file for writing, overwriting its contents
    fp = fopen("pastevents.txt", "w");

    if (fp == NULL) {
        perror("Error opening file for writing");
        return;
    }

    // Write the contents of the circular queue back to the file
    int i, count;
    count = queue.size;
    int front = queue.front;  // Store the current front index

    for (i = 0; i < count; i++) {
        char copy[225];
        strcpy(copy, queue.data[i]);
        fprintf(fp, "%s\n", copy); // Print the current front item
        // free(queue.data[front]);  // Free memory for the current front item
        // front = (front + 1) % 15; // Move to the next item
        // queue.size--;
    }

    fclose(fp);
}

void pastevents() {
    FILE *fp;
    char buff[255];

    fp = fopen("pastevents.txt", "r");

    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    while (fgets(buff, sizeof(buff), fp) != NULL) {
        // Remove the trailing newline character, if present
        size_t len = strlen(buff);
        if (len > 0 && buff[len - 1] == '\n') {
            buff[len - 1] = '\0';
        }

        printf("%s\n", buff);
    }

    fclose(fp);
    return;
}

void pastevents_execute(char* token, char* pwd, char* hwd) {
    FILE *fp;
    char buff[255];
    int max_lines = 0;


    fp = fopen("pastevents.txt", "r");

    if (fp == NULL) {
        perror("Error opening file");
        return;
    }
    while(fgets(buff, sizeof(buff), fp) != NULL)
    {
        max_lines++;
    }

    fclose(fp);
    fp = fopen("pastevents.txt", "r");
    char* lines[max_lines]; // Array to store lines
    int line_count = 0; // Number of lines read

    // Read lines from the end of the file and store them in the array
    while (fgets(buff, sizeof(buff), fp) != NULL) {
        // Remove the trailing newline character, if present
        size_t len = strlen(buff);
        if (len > 0 && buff[len - 1] == '\n') {
            buff[len - 1] = '\0';
        }

        // Allocate memory for the line and copy it
        lines[line_count] = strdup(buff);

        // Increase the line count
        line_count++;

        // Stop reading when we have enough lines
        if (line_count == max_lines) {
            break;
        }
    }

    fclose(fp);
    char input[255];
    char input_cpy[255];
    strcpy(input, lines[line_count - atoi(token)]);
    if(atoi(token) != 1)
    {
        pastevents_append(input);
    }
    if (input[strlen(input) - 1] == '\n') 
    {
        input[strlen(input) - 1] = '\0';
    }
    strcpy(input_cpy, input);
    token = strtok(input, " ");
    char cwdforwarp[1024];
    if(strcmp(token, "warp") == 0)
    {
        token = strtok(NULL, " ");
        warp(token, pwd, hwd);
    }
    else if(strcmp(token, "peek") == 0)
    {
        char *tokens[4];
        tokens[0] = token;
        token = strtok(NULL, " ");
        tokens[1] = token;
        token = strtok(NULL, " ");
        tokens[2] = token;
        token = strtok(NULL, " ");
        tokens[3] = token;


        peek(input, tokens[0], tokens[1], tokens[2], tokens[3], pwd, hwd);
    }
    else if(strcmp(token, "proclore") == 0)
    {
        token = strtok(NULL, " ");
        proclore(token);
    }
    else
    {
        int fun_len = strlen(input_cpy);
        sys_call(input_cpy, fun_len);
    }
    
    // Print the lines in reverse order
    for (int i = line_count - 1; i >= 0; i--) {


        // Free the allocated memory for each line
        free(lines[i]);
    }

    return;
}

void pastevents_purge()
{
    // open file and empty it
    FILE *fp;
    fp = fopen("pastevents.txt", "w");
    fclose(fp);
    return;
}

void iman(char* token) 
{

    // website name
    char* website = "man.he.net";

    // DNS resolution
    struct hostent *host_info;

    host_info = gethostbyname(website);

    char *ip_address;

    struct in_addr addr;
    
    memcpy(&addr, host_info->h_addr_list[0], sizeof(struct in_addr));
    ip_address = inet_ntoa(addr);

    const char* PORT = "80";
    // Create a socket
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;


    // Connect to the server
    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            continue;
        }
        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            continue;
        }
        break;
    }

    freeaddrinfo(servinfo);

    // Send an HTTP GET request for the man page
    char request[1024];
    snprintf(request, sizeof(request), "GET /?topic=%s&section=all HTTP/1.1\r\nHOST: man.he.net\r\n\r\n", token);


    // Receive and print the response
    char buffer[4096];
    ssize_t bytes_received;
    while ((bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        printf("%s", buffer);
    }


    // Close the socket
    close(sockfd);

    return;
}

void prompt(char* hwd) 
{
    int hwdlen = strlen(hwd);
    char input[256];
    char input_cpy[256]; // Assuming a maximum input length of 100 characters
    char *token;
    char hostname[256];
    char cwd[1024]; 
    char* home = getenv("HOME");
    gethostname(hostname, sizeof(hostname));
    getcwd(cwd, sizeof(cwd));
    if(strcmp(cwd, hwd) == 0)
        printf("<%s@%s:~>", getpwuid(1000)->pw_name, hostname);
    else
    {
        int count = 0;
        while (count < hwdlen && cwd[count] == hwd[count]) 
        {
            count++;
        }
        if(count == hwdlen)
        {
            int len = strlen(cwd);
            char *relative_path = (char*)malloc(len - count + 1);
            for (int i = count; i < len; i++)
            {
                relative_path[i - count] = cwd[i];
            }
            printf("<%s@%s:~%s>", getpwuid(1000)->pw_name, hostname, relative_path);
        }
        else 
        {
            printf("<%s@%s:%s>", getpwuid(1000)->pw_name, hostname, cwd);
        }

    }
}

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

int main()
{
    // make a copy of standard file input
    int std_in = dup(STDIN_FILENO);
    int std_out = dup(STDOUT_FILENO);
    char* pwd = getcwd(NULL, 0);
    char hwd[1024];
    getcwd(hwd, sizeof(hwd));
    int hwdlen = strlen(hwd);
    while(1)
    {
        char input[100];
        char input_main[100] ;// Assuming a maximum input length of 100 characters
        char *token;
        char input_cpy[256]; 
        prompt(hwd);
        fgets(input_main, sizeof(input_main), stdin);
        int count = 0;
        // Remove the newline character from the input
        if (input_main[strlen(input_main) - 1] == '\n') 
        {
            input_main[strlen(input_main) - 1] = '\0';
        }
        for(int i = 0; i < 100; i++)
        {
            if(input_main[i] == '&')
            {
                count++;
            }
        }
        // copy the input_main to a new variable named input_main_updated and replace all & with ;&
        char input_main_updated[100 + count];
        int j = 0;
        for(int i = 0; i < 100; i++)
        {
            if(input_main[i] == '&')
            {
                input_main_updated[j] = '&';
                j++;
                input_main_updated[j] = ';';
                j++;
            }
            else
            {
                input_main_updated[j] = input_main[i];
                j++;
            }
        }
        if (input_main_updated[strlen(input_main_updated) - 1] == '\n') 
        {
            input_main_updated[strlen(input_main_updated) - 1] = '\0';
        }
        char input_main_updated_cpy[100 + count];
        strcpy(input_main_updated_cpy, input_main_updated);

        // tokenise the input_main_updated and store it in input
        token = strtok(input_main_updated_cpy, ";");
        strcpy(input, token);
        int token_count = 0;

        while(input != NULL)
        {
            token_count++;
            strcpy(input_cpy, input);
            if(token[strlen(token) - 1] == '&')
            {
                pid_t child = fork();
                if(child < 0)
                {
                    printf("Error in forking\n");
                }
                else if(child == 0)
                {
                    // change the output from stdout to /dev/null
                    freopen("/dev/null", "w", stdout);
                    token = strtok(input, " ");
                    char cwdforwarp[1024];
                    

                    if(strcmp(token, "warp") == 0)
                    {
                        token = strtok(NULL, " ");
                        warp(token, pwd, hwd);
                    }
                    else if(strcmp(token, "peek") == 0)
                    {
                        char *tokens[4];
                        tokens[0] = token;
                        token = strtok(NULL, " ");
                        tokens[1] = token;
                        token = strtok(NULL, " ");
                        tokens[2] = token;
                        token = strtok(NULL, " ");
                        tokens[3] = token;


                        peek(input, tokens[0], tokens[1], tokens[2], tokens[3], pwd, hwd);
                    }
                    else if(strcmp(token, "proclore") == 0)
                    {
                        token = strtok(NULL, " ");
                        proclore(token);
                    }
                    else if(strcmp(token, "pastevents") == 0)
                    {
                        token = strtok(NULL, " ");
                        if(token == NULL)
                        {
                            pastevents();
                        }
                        else if(strcmp(token, "execute") == 0)
                        {
                            token = strtok(NULL, " ");
                            pastevents_execute(token, pwd, hwd);
                        }
                        else if(strcmp(token, "purge") == 0)
                        {
                            pastevents_purge();
                        }
                    }
                    else if(strcmp(token, "iMan") == 0)
                    {
                        token = strtok(NULL, " ");
                        if(token == NULL)
                        {
                            printf("No command specified\n");
                        }
                        else
                        {
                            iman(token);
                        }
                    }
                    else
                    {
                        int fun_len = strlen(input_cpy);
                        sys_call(input_cpy, fun_len);
                    }

                        exit(0);
                }
                else
                {
                    printf("%d\n", child);

                    int check = token_count;
                    check--;
                    strcpy(input_main_updated_cpy, input_main_updated);
                    token = strtok(input_main_updated_cpy, ";");
                    while(check > -1)
                    {
                        token = strtok(NULL, ";");
                        check--;
                    }
                    if(token != NULL)
                    {
                        strcpy(input, token);
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                int input_test = 0;
                int output_test = 0;
                for(int i = 0; i < strlen(input); i++)
                {
                    if(input[i] == '<')
                    {
                        input_test = 1;
                    }
                    if(input[i] == '>' && input[i + 1] == '>')
                    {
                        output_test = 2;
                        i++;
                    }
                    else if(input[i] == '>')
                    {
                        output_test = 1;
                    }
                }
                char* input_file;
                char* output_file;
                if(input_test == 0 && output_test == 0)
                {

                }
                else if(input_test == 1 && output_test == 0)
                {
                    // input redirection
                    token = strtok(input, "<");
                    token = strtok(NULL, "<");
                    input_file = strdup(token);
                    // open file descriptor
                    int fd = open(input_file, O_RDONLY);
                    dup2(fd, STDIN_FILENO);
                    close(fd);
                    token = strtok(input, "<");
                    strcpy(input_cpy, token);
                }
                else if(input_test == 0 && output_test == 1)
                {
                    // output redirection
                    token = strtok(input, ">");
                    token = strtok(NULL, ">");
                    output_file = strdup(token);
                    // open file descriptor
                    int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                    token = strtok(input, ">");
                    strcpy(input_cpy, token);
                }
                else if(input_test == 0 && output_test == 2)
                {
                    // output redirection but append mode
                    token = strtok(input, ">>");
                    token = strtok(NULL, ">>");
                    output_file = strdup(token);
                    // open file descriptor
                    int fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                    token = strtok(input, ">>");
                    strcpy(input_cpy, token);
                }
                else if(input_test == 1 && output_test == 1)
                {
                    // input and output redirection
                    token = strtok(input, "<");
                    token = strtok(NULL, "<");
                    char token_nibba[256];
                    strcpy(token_nibba, token);
                    token = strtok(token_nibba, ">");
                    input_file = strdup(token);
                    // make the last character \0
                    int len = strlen(input_file);
                    input_file[len - 1] = '\0';
                    // open file descriptor
                    int fd = open(input_file, O_RDONLY);
                    dup2(fd, STDIN_FILENO);
                    close(fd);
                    int nibba_len = strlen(token_nibba);
                    token_nibba[nibba_len] = '>';
                    token = strtok(token_nibba, ">");
                    token = strtok(NULL, ">");
                    output_file = strdup(token);
                    // open file descriptor
                    fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                    token = strtok(input, ">");
                    strcpy(input_cpy, token);
                }
                else if(input_test == 1 && output_test == 2)
                {
                    // input and output redirection
                    token = strtok(input, "<");
                    token = strtok(NULL, "<");
                    char token_nibba[256];
                    strcpy(token_nibba, token);
                    token = strtok(token_nibba, ">>");
                    input_file = strdup(token);
                    // make the last character \0
                    int len = strlen(input_file);
                    input_file[len - 1] = '\0';
                    // open file descriptor
                    int fd = open(input_file, O_RDONLY);
                    dup2(fd, STDIN_FILENO);
                    close(fd);
                    int nibba_len = strlen(token_nibba);
                    token_nibba[nibba_len] = '>';
                    token = NULL;
                    token = strtok(token_nibba, ">>");
                    token = strtok(NULL, ">>");
                    output_file = strdup(token);
                    // open file descriptor
                    fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                    token = strtok(input, ">>");
                    strcpy(input_cpy, token);
                }

                token = strtok(input, " ");
                char cwdforwarp[1024];
                

                if(strcmp(token, "warp") == 0)
                {
                    token = strtok(NULL, " ");
                    warp(token, pwd, hwd);
                }
                else if(strcmp(token, "peek") == 0)
                {
                    char *tokens[4];
                    tokens[0] = token;
                    token = strtok(NULL, " ");
                    tokens[1] = token;
                    token = strtok(NULL, " ");
                    tokens[2] = token;
                    token = strtok(NULL, " ");
                    tokens[3] = token;


                    peek(input, tokens[0], tokens[1], tokens[2], tokens[3], pwd, hwd);
                }
                else if(strcmp(token, "proclore") == 0)
                {
                    token = strtok(NULL, " ");
                    proclore(token);
                }
                else if(strcmp(token, "pastevents") == 0)
                {
                    token = strtok(NULL, " ");
                    if(token == NULL)
                    {
                        pastevents();
                    }
                    else if(strcmp(token, "execute") == 0)
                    {
                        token = strtok(NULL, " ");
                        pastevents_execute(token, pwd, hwd);
                    }
                    else if(strcmp(token, "purge") == 0)
                    {
                        pastevents_purge();
                    }
                }
                else if(strcmp(token, "iMan") == 0)
                {
                    token = strtok(NULL, " ");
                    if(token == NULL)
                    {
                        printf("No command specified\n");
                    }
                    else
                    {
                        iman(token);
                    }
                }
                else if(strcmp(token, "neonate") == 0)
                {
                    token = strtok(NULL, " ");
                    token = strtok(NULL, " ");
                    neonate(token);
                }
                else if(strcmp(token, "activities") == 0)
                {
                    activities();
                }
                else if(strcmp(token, "fg") == 0)
                {
                    token = strtok(NULL, " ");
                    // check if token exists in /proc
                    DIR *dir;
                    struct dirent *entry;
                    // open proc directory
                    dir = opendir("/proc");
                    int pid_exists = 0;
                    while ((entry = readdir(dir)) != NULL) {
                        if (atoi(entry->d_name) == atoi(token)) {
                            pid_exists = 1;
                            break;
                        }
                    }
                    closedir(dir);
                    // if pid does not exists then print so
                    if(pid_exists == 0)
                    {
                        printf("No such process exists\n");
                    }
                    else
                    {

                    }     
                }
                else if(strcmp(token, "bg") == 0)
                {
                    token = strtok(NULL, " ");
                    // check if token exists in /proc
                    DIR *dir;
                    struct dirent *entry;
                    // open proc directory
                    dir = opendir("/proc");
                    int pid_exists = 0;
                    while ((entry = readdir(dir)) != NULL) {
                        if (atoi(entry->d_name) == atoi(token)) {
                            pid_exists = 1;
                            break;
                        }
                    }
                    closedir(dir);
                    // if pid does not exists then print so
                    if(pid_exists == 0)
                    {
                        printf("No such process exists\n");
                    }
                    else
                    {
                        // run the process in background
                        pid_t child = fork();
                        if(child == 0)
                        {
                            // change the output from stdout to /dev/null
                            freopen("/dev/null", "w", stdout);
                            // run the process
                            token = strtok(input_cpy, " ");
                            char* args[100];
                            int i = 0;
                            char* token_cpy = strdup(token);
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
                        }

                    }

                }
                else
                {
                    int fun_len = strlen(input_cpy);
                    sys_call(input_cpy, fun_len);
                }

                int check = token_count;
                check--;
                strcpy(input_main_updated_cpy, input_main_updated);
                token = strtok(input_main_updated_cpy, ";");
                while(check > -1)
                {
                    token = strtok(NULL, ";");
                    check--;
                }
                if(token != NULL)
                {
                    strcpy(input, token);
                }
                else
                {
                    break;
                }
            }
        }
        // retyrn the input to stdin
        dup2(std_in, STDIN_FILENO);
        // change output back to stdout
        dup2(std_out, STDOUT_FILENO);
    
    }
}
