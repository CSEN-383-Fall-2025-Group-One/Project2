#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct Process{
    //Data read from Generation
    int pID;
    int arrival_time;
    int service_time;
    int priority;

    int start_time; //Time starts running
    int end_time; //Time ends running
    int remaining_time; //Time left until completion (initially = service_time)
};

//Question: How do I tell when I need to have a Malloc in C?

int comp(const void* a, const void* b){ //Comparison fxn for sorting
    const struct Process *p1 = a;
    const struct Process *p2 = b;

    return (p1->arrival_time - p2->arrival_time);
}

int main(){

    //** 
    // SETUP:
    // Reading our process data from a text file
    // Putting the data into a sortable array/data type (Struct Process)
    // Sorting the array based on arrival time
    // */

    int n = 10; //number of processes we have = 10

    struct Process process_queue[n]; //only 10 processes

    FILE *fptr;
    char *filename = "workload_data.txt";

    printf("Filename is: %s\n", filename);

    fptr = fopen(filename, "r");        //opens in read mode
    if (fptr == NULL) {
        perror("Error");
        return 1;
    }
    else{
        printf("File successfully opened\n");
    }


    int arrival;
    int service;
    int pri;

    int i = 0; //pID
    while(fscanf(fptr, "<%d, %d, %d>\n", &arrival, &service, &pri) == 3){ //scans the file in the specified format, ensuring 3 arguments
        process_queue[i].pID = i;                           //process ID is the iteration we are on, first one is 0
        process_queue[i].arrival_time = arrival;
        process_queue[i].service_time = service;
        process_queue[i].priority = pri;
        process_queue[i].remaining_time = service;          //Possibly come back here to check pointers understanding, make sure remaining is value of service, not is service


        printf("pID: %d, arrival time: %d, service time: %d, priority: %d, remaining time: %d\n", 
            process_queue[i].pID, process_queue[i].arrival_time, process_queue[i].service_time, process_queue[i].priority,
            process_queue[i].remaining_time);
        i = i + 1; //increment pID

    }

    fclose(fptr); //closes the file

    printf("\nData has been read from file and added to the array. Now, sorting the array\n");

    //Sorting based off of Arrival time
    qsort(process_queue, n, sizeof(struct Process), comp); 
    for(int j = 0; j < n; j++){
        printf("pID: %d, arrival time: %d, service time: %d, priority: %d, remaining time: %d\n", 
            process_queue[j].pID, process_queue[j].arrival_time, process_queue[j].service_time, process_queue[j].priority,
            process_queue[j].remaining_time);
    }

    //**
    // Execution:
    // Simulating 100 time quantums by iterating 100 times
    // Applying FCFS scheduling 
    //  */

    //** Stipulations for running in a time quantum:
    // A process that starts before q = 100 must finish
    // A process that arrives after q = 100 cannot run
    // A process is removed from the process queue after it has completed */

    struct Process completed_processes[n]; //As long as the queue

    int curr_proc = 0; //gets the first process in the process_queue
    for(int q = 0; q < 100; q++){
        if(process_queue[curr_proc].arrival_time != q){
        }
    }
}