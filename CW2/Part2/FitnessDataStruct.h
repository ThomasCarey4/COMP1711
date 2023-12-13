typedef struct {
    char date[11];
    char time[6];
    int steps;
} FITNESS_DATA;

void tokeniseRecord(const char *input, const char *delimiter, char *date, char *time, char *steps);

int readFile(const char *fileName, FITNESS_DATA **out, int *numRows);

void minSteps(FITNESS_DATA **data, int *minStepsRow, int *numRows);

void maxSteps(FITNESS_DATA **data, int *minStepsRow, int *numRows);

void avgSteps(FITNESS_DATA **data, int *avgSteps, int *numRows);

void longestPeriodAbove500(FITNESS_DATA **data, int *numRows, int *startRow, int *endRow);