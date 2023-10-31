#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

// Define any additional variables here



// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
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

void readFile(const char *fileName, const int maxRows, char out[][22])
{
    FILE* openFile = fopen(fileName, "r");
    if (openFile == NULL){ // Check if file exists
        printf("File not found...\n");
        return;
    }
    int row = 0;
    char buffer[22];
    while(fgets(buffer, maxRows, openFile)){
        strcpy(out[row], buffer); // Copy each row into the array of strings (out)
        ++row;
    }
    fclose(openFile);
}

// Complete the main function
int main() {
    char arrRows[40] = "FitnessData_2023.csv"; // Store the file name
    const int maxRows = 512; // The number of rows the program will read
    char delimiter = ',';
    char out[maxRows][22]; // Initialise array of strings to store file data
    int rowNumber = 0;
    FITNESS_DATA data[maxRows];
    readFile(arrRows, maxRows, out);
    while (out[rowNumber][0] != '\0'){ // Loop through each row of the file, until the end of the file is reached
        char steps[22];
        tokeniseRecord(out[rowNumber], &delimiter, data[rowNumber].date, data[rowNumber].time, steps); // Tokenise each row
        data[rowNumber].steps = atoi(steps); // Convert steps to an integer
        ++rowNumber;
    }
    printf("Number of records in file: %d\n", rowNumber);
    for(int i = 0; i < 3; ++i){ // Runs 3 times
        printf("%s/%s/%d\n",  data[i].date, data[i].time, data[i].steps); // Returns line 'i' of data in format: yyyy-mm-dd/hh:mm/steps
    }
}
