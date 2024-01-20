#include "pastevents.h"
#include "peek.h"
#include "warp.h"
#include "proclore.h"
#include "sys_call.h"




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
    // int front = queue.front;  // Store the current front index

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
