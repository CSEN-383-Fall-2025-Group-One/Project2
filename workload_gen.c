#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main()
{
    FILE *fptr;
    char *filename = "workload_data.txt";

    fptr = fopen(filename, "w");
    if (fptr == NULL){
        return -1;                              //error creating file
    }               

    // int seed = time(NULL);                   //from preview doc, does not generate same values on each runtime.
    int seed = 0;
    srand(seed);                                //Seed the random, guarantees consistency when debugging.

    for(int i = 0; i < 10; i++){                //Generates 10 jobs & writes them to the data file
        //Generate random job data.
        int arrival_time = rand() % 100;        //Will return a number between 0 and 99
        int service_time = (rand() % 10) + 1;   //Returns num between 1 and 10
        int priority = (rand() % 4) + 1;        //Priority between 1 and 4, with 1 being the highest
        //Possibly add in a 'job name' field

        fprintf(fptr, "<%d, %d, %d>\n", arrival_time, service_time, priority); //Write job to file
    }
    fclose(fptr); //closes the file
}