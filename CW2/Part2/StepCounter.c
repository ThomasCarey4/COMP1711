#include "FitnessDataStruct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps){
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

}

int readFile(const char *fileName, FITNESS_DATA **out, int *numRows){
    FILE* openFile = fopen(fileName, "r");
    if (openFile == NULL){ // Check if file exists
        printf("Error: Could not find or open the file\n");
        return 1;
    }

    // Start with an array of some size
    int maxRows = 10;
    char delimiter = ',';
    *out = malloc(maxRows * sizeof(FITNESS_DATA));

    // Read the data
    int row = 0;
    char buffer[24];
    char date[11];
    char time[6];
    char steps[22];
    while(fgets(buffer, 24, openFile)){
        // If the array is full, increase its size
        if (row == maxRows) {
            maxRows *= 2;
            *out = realloc(*out, maxRows * sizeof(FITNESS_DATA));
        }
        // Tokenize the record and store it in the array
        tokeniseRecord(buffer, &delimiter, date, time, steps);
        if (date[0] != '\0' && time[0] != '\0' && steps[0] != '\0') {
            strcpy((*out)[row].date, date);
            strcpy((*out)[row].time, time);
            (*out)[row].steps = atoi(steps);
            ++row;
        }
    }
    fclose(openFile);

    // Update the number of rows
    *numRows = row;
    return 0;
}

void minSteps(FITNESS_DATA **data, int *minStepsRow, int *numRows){
    int minSteps = __INT16_MAX__; // The row with the minimum steps
    for (int i = 0; i < *numRows; i++) {
        int steps = (*data)[i].steps;
        // If this row has fewer steps, update minSteps and minStepsRow
        if (steps < minSteps) {
            minSteps = steps;
            *minStepsRow = i;
        }
    }
}

void maxSteps(FITNESS_DATA **data, int *maxStepsRow, int *numRows){
    int maxSteps = -1; // The row with the minimum steps
    for (int i = 0; i < *numRows; i++) {
        int steps = (*data)[i].steps;
        // If this row has fewer steps, update minSteps and minStepsRow
        if (steps > maxSteps) {
            maxSteps = steps;
            *maxStepsRow = i;
        }
    }
}

void avgSteps(FITNESS_DATA **data, int *avgSteps, int *numRows){
    int totalSteps = 0;
    float average = 0;
    for (int i = 0; i < *numRows; i++) {
        totalSteps += (*data)[i].steps;
    }
    average = (float)totalSteps / *numRows;
    *avgSteps = average + 0.5;
}

void longestPeriodAbove500(FITNESS_DATA **data, int *startRow, int *endRow, int *numRows){
    int longestPeriod = 0; // Length of the longest period
    int currentPeriod = 0; // Length of the current period
    int currentStartRow = -1; // Start row of the current period

    for (int i = 0; i < *numRows; i++) {
        int steps = (*data)[i].steps;
        if (steps > 500) {
            if (currentStartRow == -1) {
                currentStartRow = i;
            }
            currentPeriod++;
        } else {
            if (currentPeriod > longestPeriod) {
                longestPeriod = currentPeriod;
                *startRow = currentStartRow;
                *endRow = i - 1;
            }
            currentPeriod = 0;
            currentStartRow = -1;
        }
    }

    if (currentPeriod > longestPeriod) {
        longestPeriod = currentPeriod;
        *startRow = currentStartRow;
        *endRow = *numRows - 1;
    }
}

// Complete the main function
int main() {
    int running = 1;
    FITNESS_DATA *data = NULL; // Declare a pointer to an array of FITNESS_DATA structs
    int numRows;
    int minStepsRow = -1;
    int maxStepsRow = -1;
    int averageSteps = -1;
    int periodStartRow = -1;
    int periodEndRow = -1;
    char fileName[64];
    char option;
    while (running) {
        printf("Menu Options:\n"
            "A: Specify the filename to be imported\n"
            "B: Display the total number of records in the file\n"
            "C: Find the date and time of the timeslot with the fewest steps\n"
            "D: Find the date and time of the timeslot with the largest number of steps\n"
            "E: Find the mean step count of all the records in the file\n"
            "F: Find the longest continuous period where the step count is above 500 steps\n"
            "Q: Quit\n"
            "Enter choice: ");
        scanf(" %c", &option);
        switch (option) {
        case 'A':
            printf("Input filename: ");
            scanf(" %s", fileName);
            if(readFile(fileName, &data, &numRows) == 1){
                return 1;
            }
            printf("File successfully loaded.\n");
            break;
        case 'B':
            printf("Total records: %d\n", numRows);
            break;
        case 'C':
            if (data != NULL) {
                minSteps(&data, &minStepsRow, &numRows);
                printf("Fewest steps: %s %s\n",  data[minStepsRow].date, data[minStepsRow].time);
            } else {
                printf("Error: no data\n");
            }
            break;
        case 'D':
            if (data != NULL) {
                maxSteps(&data, &maxStepsRow, &numRows);
                printf("Largest steps: %s %s\n",  data[maxStepsRow].date, data[maxStepsRow].time);
            } else {
                printf("Error: no data\n");
            }
            break;
        case 'E':
            if (data != NULL) {
                avgSteps(&data, &averageSteps, &numRows);
                printf("Mean step count: %d\n", averageSteps);
            } else {
                printf("Error: no data\n");
            }
            break;
        case 'F':
            if (data != NULL) {
                longestPeriodAbove500(&data, &periodStartRow, &periodEndRow, &numRows);
                printf("Longest period start: %s %s\n",  data[periodStartRow].date, data[periodStartRow].time);
                printf("Longest period end: %s %s\n",  data[periodEndRow].date, data[periodEndRow].time);
            } else {
                printf("Error: no data\n");
            }
            break;
        case 'Q':
        case 'q':
            running = 0;
            break;
        default:
            printf("Invalid choice. Try again.\n");
            break;
        }
    }
    free(data);
    return 0;
}
