#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#define length 100

// GLOBAL VARIABLES
int tracker = 0; // keeps track of the last tasks index

// FUNCTION DECLARATIONS

void homeUI();
void addTaskUI();
void completeTaskUI();
void showTasksUI();
void removeTask();
void cleanInput();

char * tasks[length];

int main() {
    printf("\n\n");
    printf("WELCOME TO YOUR TASKS!\n");
    printf("Type 'exit()' to go back a menu\n");

    homeUI(tasks);
}

void homeUI(char * tasks[length]) {
    char instruction[length];

    do {
        showTasksUI(tasks);

        printf("\n\n");

        printf("1. Add Task\t");
        printf("2. Complete Task\t");
        printf("\n");

        printf("What would you like to do? ");
        fgets(instruction, length, stdin);

        if (strcmp(instruction, "1\n") == 0) addTaskUI(tasks);
        else if (strcmp(instruction, "2\n") == 0) completeTaskUI(tasks);
        else if (strcmp(instruction, "exit()\n") == 0) { showTasksUI(tasks); break; }
    } while(1);

}

void addTaskUI(char * tasks[length]) {
    printf("\n\n");

    char task[length];

    do {
        printf("What would you like to add? ");
        fgets(task, length, stdin);

        if (strcmp(task, "exit()\n") == 0) break;

        tasks[tracker] = strdup(task);
        cleanInput(tasks[tracker]);
        tracker++;
    } while(1);
}

void completeTaskUI(char * tasks[length]) {
    printf("\n\n");

    char completeTaskNum[length];
    char* endptr;

    do {
        showTasksUI();
        
        printf("What task did you complete? ");
        fgets(completeTaskNum, length, stdin);

        if (strcmp(completeTaskNum, "exit()\n") == 0) break;
        cleanInput(completeTaskNum);

        int elementToRemove = strtoimax(completeTaskNum, &endptr, 10);

        if (elementToRemove <= tracker) removeTask(tasks, elementToRemove);

    } while(1);
}

void showTasksUI() {
    if (tracker > 0) {
        printf("\n\n");
        printf("HERE ARE YOUR TASKS:\n\n");

        for (int i = 0; i < tracker; i++) {
            printf("%d. %s\n", (i + 1), tasks[i]);
        }
    }

    printf("\n\n");
}

// @param element : element number to remove
// to remove an array element, I need to move every task after element 1 index forward
void removeTask(char * tasks[length], int element) {
    // start at the index of element (element numbering starts at 1)
    for (int i = element - 1; i < length; i++) {

        // move the current element by 1 index
        /* example

        Original  :  0 1 2 3 4
        Remove 2 :   0 1 3 4

        moves all elements after 2 by 1 index
        */

        tasks[i] = tasks[i + 1];
    }

    tracker--;
}

// @param s[length] : String => a task a user input
// takes a task and removes the '\n' and replaces it with null terminator
void cleanInput(char s[length]) {
    for (int i = 0; i < length; i++) {
        if (s[i] == '\n') {
            s[i] = '\0';
            break;
        }
    }
}