#ifndef FITNESS_DATA_STRUCT_H
#define FITNESS_DATA_STRUCT_H

#include <stdio.h>

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FitnessData;

// Helper function prototypes
void tokeniseRecord(char *record, char delimiter, char *date, char *time, int *steps);

int readFile(const char *fileName, FitnessData **out, int *numRows);

void sortFile(FitnessData **data, int *numRows);

void saveFile(const char *fileName, FitnessData **data, int *numRows);

#endif // FITNESS_DATA_STRUCT_H