#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Function to tokenize a record
void tokeniseRecord(char *record, char delimiter, char *date, char *time, int *steps) {
    char *ptr = strtok(record, &delimiter);
    if (ptr != NULL) {
        strcpy(date, ptr);
        ptr = strtok(NULL, &delimiter);
        if (ptr != NULL) {
            strcpy(time, ptr);
            ptr = strtok(NULL, &delimiter);
            if (ptr != NULL) {
                *steps = atoi(ptr);
            }
        }
    }
}


int readFile(const char *fileName, FitnessData **out, int *numRows){
    FILE* openFile = fopen(fileName, "r");
    if (openFile == NULL){ // Check if file exists
        return 1;
    }

    // Start with an array of a small size
    int maxRows = 10;
    char delimiter = ',';
    *out = malloc(maxRows * sizeof(FitnessData));

    // Read the data
    int row = 0;
    char buffer[24];
    char date[11];
    char time[6];
    int steps;
    while(fgets(buffer, 24, openFile)){
        // If the array is full, increase its size
        if (row == maxRows) {
            maxRows *= 2;
            *out = realloc(*out, maxRows * sizeof(FitnessData));
        }
        if(buffer[0] != '\n' &&
         (buffer[10] != ',' || buffer[16] != ',' ||
          buffer[4] != '-' || buffer[7] != '-' ||
          buffer[13] != ':')){ // What the f*ck does bad data mean
            fclose(openFile);
            return 1;
        }
        // Tokenize the record and store it in the array
        tokeniseRecord(buffer, delimiter, date, time, &steps);
        if (date[0] == '\0' || time[0] == '\0' || steps == 0) {
            fclose(openFile);
            return 1;
        }
        strcpy((*out)[row].date, date);
        strcpy((*out)[row].time, time);
        (*out)[row].steps = steps;
        ++row;
    }
    fclose(openFile);

    // Update the number of rows
    *numRows = row;
    return 0;
}


void sortFile(FitnessData **data, int *numRows){ // Bubble sort
    int i, j;
    FitnessData temp;
    for (i = 0; i < *numRows; i++){
        for (j = 0; j < *numRows - 1; j++){
            if ((*data)[j].steps < (*data)[j + 1].steps){
                temp = (*data)[j];
                (*data)[j] = (*data)[j + 1];
                (*data)[j + 1] = temp;
            }
        }
    }
}


void saveFile(const char *fileName, FitnessData **data, int *numRows){
    FILE* openFile = fopen(fileName, "w");
    if (openFile == NULL){ // Check if file could be opened/created
        printf("Error: Could not find or open the file\n");
        return;
    }
    for (int i = 0; i < *numRows; i++){
        fprintf(openFile, "%s\t%s\t%d\n", (*data)[i].date, (*data)[i].time, (*data)[i].steps);
    }
    fclose(openFile);
}


int main() {
    char filename[64] = "FitnessData_2023.csv";
    char saveFilename[72];
    printf("Enter Filename: ");
    scanf("%s", filename);
    sprintf(saveFilename, "%s.tsv", filename);
    int numRows = -1;
    FitnessData *data = NULL;
    if(readFile(filename, &data, &numRows) == 1){
        printf("Error: Could not read the file\n");
        return 1;
    }
    sortFile(&data, &numRows);
    saveFile(saveFilename, &data, &numRows);
    printf("Data sorted and written to %s\n", saveFilename);
    return 0;
}
