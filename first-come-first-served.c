#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//Katie Carter, Group 1
//Writing First-come-first-served method.

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

    //** SETUP ************************************************************************
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

        /*
        printf("pID: %d, arrival time: %d, service time: %d, priority: %d, remaining time: %d\n", 
            process_queue[i].pID, 
            process_queue[i].arrival_time, 
            process_queue[i].service_time, 
            process_queue[i].priority,
            process_queue[i].remaining_time);
        */

        i = i + 1; //increment pID

    }
    fclose(fptr);

    printf("\nData has been read from file and added to the array. Now, sorting the array\n");

    //Sorting based off of Arrival time
    qsort(process_queue, n, sizeof(struct Process), comp); 
    
    /*
    for(int j = 0; j < n; j++){
        printf("pID: %d, arrival time: %d, service time: %d, priority: %d, remaining time: %d\n", 
            process_queue[j].pID, 
            process_queue[j].arrival_time, 
            process_queue[j].service_time, 
            process_queue[j].priority,
            process_queue[j].remaining_time);
    }
    */
    
    printf("\n Now, executing FCFS \n");

    //** EXECUTION: ******************************************************************************************
    // Simulating 100 time quantums by iterating 100 times
    //
    // Stipulations for running in a time quantum:
    // A process that starts before q = 100 must finish
    // A process that arrives after q = 100 cannot run
    // A process is removed from the process queue after it has completed 
    //  
    // Implementing FCFS 
    // */

    int proj = 0;                   //gets the first process in the process_queue, 
                                    // also number completed processes

    for(int q = 0; q < 100; q++){
        printf("q: %d\n", q);

        if(process_queue[proj].arrival_time > q){
            continue;               //No processes have arrived yet. move on.
        }
        else{                       //a process has arrived. Run that Process.
            // printf("else\n");

            process_queue[proj].start_time = q; //If this is start of running process
            for(int p = 0; p < process_queue[proj].service_time; p++){ //loop for as long as it takes to service
                // printf("\t in For Loop\n");
                process_queue[proj].remaining_time = (process_queue[proj].remaining_time - 1); //decrement remaining time by 1, becayse we are servicing one time quantum in this loop.
                
                /*
                printf("pID: %d, arr: %d, serv: %d, start: %d, remaining: %d\n", 
                    process_queue[proj].pID, 
                    process_queue[proj].arrival_time, 
                    process_queue[proj].service_time, 
                    process_queue[proj].start_time, 
                    process_queue[proj].remaining_time);
                printf("FL Q: %d\n", q);
                */

                q = q + 1; //take up a time quantum
            }
            process_queue[proj].end_time = q; //time finished
            // printf("end time: %d\n", q);
            // printf("Time remaining: %d (should be 0)\n", process_queue[proj].remaining_time);
            printf("Process number %d completed. Stats are as follows:\n", proj);
            printf("pID: %d, arr: %d, serv: %d, start: %d, end: %d,remaining: %d\n", 
                process_queue[proj].pID, 
                process_queue[proj].arrival_time, 
                process_queue[proj].service_time, 
                process_queue[proj].start_time, 
                process_queue[proj].end_time, 
                process_queue[proj].remaining_time);

            proj += 1; //move on from the first completed project, effectively "removing" it from the queue.
        }
    } //End of For Loop.

    //Time Chart will be from a spreadsheet, I guess?

    printf("\nQuantum has been simulated. Calculating Metrics \n");

    /** METRICS ***********************************************************************
    // Now that the quantums have been simulated, calculate the metrics.
    // Metrics: 
    //      Average Turnaround time = avg(time completed-time arrival)
    //      Average waiting time = avg(turnaround time - service time)
    //      Average response time = avg(time start - arrival time)
    */

    printf("proj: %d\n", proj); //Proj = 10
    float avgTurnaround;
    float avgWaiting;
    float avgResponse;

    for(int a = 0; a < proj; a++){
        float turnaround = process_queue[a].end_time - process_queue[a].arrival_time;
        float wait = turnaround - process_queue[a].service_time;
        float response = process_queue[a].start_time - process_queue[a].arrival_time;

        printf("Process %d (pID %d): Turnaround %f, wait: %f, response: %f\n", a, process_queue[a].pID, turnaround, wait, response);
        avgTurnaround += turnaround;
        avgWaiting += wait;
        avgResponse += response;
    }

    printf("Sum of: Turnaround: %f, Wait time: %f, response time: %f\n", avgTurnaround, avgWaiting, avgResponse);

    avgTurnaround = avgTurnaround / proj;
    avgWaiting = avgWaiting / proj;
    avgResponse = avgResponse / proj;

    printf("Metrics: Average Turnaround time: %f, Average Waiting time: %f, Average Response time: %f\n", 
        avgTurnaround, avgWaiting, avgResponse);

    //TODO: Calculate throughput.
}