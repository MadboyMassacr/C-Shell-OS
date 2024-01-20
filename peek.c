#include "peek.h"


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
