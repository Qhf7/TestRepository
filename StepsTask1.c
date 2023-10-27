#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an appropriate struct
typedef struct
{
    char date[11];
    char time[6];
    int steps;
} FITNESS_DATA;

// Define any additional variables here

// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps)
{
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);

    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL)
    {
        strcpy(date, token);
    }

    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        strcpy(time, token);
    }

    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        strcpy(steps, token);
    }

    // Free the duplicated string
    free(inputCopy);
}

// Complete the main function

// Main function
int main()
{
    char line[50];
    FITNESS_DATA *data = NULL; // Pointer for dynamic allocation
    char date[11], time[6], steps[10];
    int index = 0;

    FILE *file = fopen("FitnessData_2023.csv", "r");

    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file) != NULL)
    {
        tokeniseRecord(line, ",", date, time, steps);

        // Dynamic allocation for new data record
        data = realloc(data, (index + 1) * sizeof(FITNESS_DATA));
        if (!data)
        {
            printf("Memory allocation failed.\n");
            fclose(file);
            return 1;
        }

        strcpy(data[index].date, date);
        strcpy(data[index].time, time);
        data[index].steps = atoi(steps);

        index++;
    }

    for (int i = 0; i < 3 && i < index; i++)
    {
        printf("%s/%s/%d\n", data[i].date, data[i].time, data[i].steps);
    }

    fclose(file);
    free(data); // Free dynamically allocated memory
    return 0;
}
