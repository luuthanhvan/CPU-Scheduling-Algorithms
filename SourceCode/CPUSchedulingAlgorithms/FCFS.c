/*
- Describe: This is a program for implementation of First-come First-served (FCFS) CPU Scheduling algorithm. 
With this scheme, the process that requests the CPU first is allocated the CPU first or which process enter
the ready queue first is served first.

- Idea:
	1. Arrange all processes according to ascending arrival time
	2. Find waiting time of all processes:
		waiting time = service time - arrival time
	(Service time means amount of time after which a process can start execution. It is
	summation of burst time of previous processes).
	3. Find turnaround time:
		turnaround time = waiting time + burst time
	4. Average waiting time = total waiting time/number of processes
	5. Average turnaround time = total turnaround time/number of processes
	
- Initialization variables:
	nbProcess: number of processes
	idProcess[]: array which store process number
	burstTime[] <- 0: array which store burst time of n processes
	arrivalTime[] <- 0: array which store arrival time of all processes
	waitingTime[] <- 0: array which store waiting time of all processes
	turnaroundTime[] <- 0: array which store turnaround time of all processes
	avgWT <- 0.0: average waiting time
	avgTAT <- 0.0: average turnaround time
	
- Pseudo code:
Arrange all processes according to ascending arrival time
	For i <- 0 to n-1
		For j <- i+1 to n
			If arrivalTime[j] < arrivalTime[i]
				temp <- burstTime[j]
				burstTime[j] <- burstTime[i]
				burstTime[i] <- temp
				temp <- arrivalTime[j]
				arrivalTime[j] <- arrivalTime[i]
				arrivalTime[i] <- temp
				temp <- idProcess[j]
				idProcess[j] <- idProcess[i]
				idProcess[i] <- temp
	End For
	
	totalWT = 0.0
	totalTAT = 0.0
	serviceTime[0] = arrivalTime[0]
	For i <- 0 to n
	Begin
		serviceTime[i+1] = serviceTime[i] + burstTime[i]
		waitingTime[i] = serviceTime[i] - arrivalTime[i]
		turnaroundTime[i] = waitingTime[i] + burstTime[i]
		totalWT = totalWT + waitingTime[i]
		totalTAT = totalTAT + turnaroundTime[i]
	End
	avgWT = totalWT/nbProcess
	avgTAT = totalTAT/nbProcess
*/

#include <stdio.h>
#define MAXPROCESS 10 /* Define the maximum process */

/* Declare some global variables */
int processID[MAXPROCESS];
int burstTime[MAXPROCESS]; 
int arrivalTime[MAXPROCESS]; 
int nbProcess;
int waitingTime[MAXPROCESS]; 
int turnaroundTime[MAXPROCESS]; 
float avgWT = 0.0; 
float avgTAT = 0.0; 

/* 
Function to allow user enter number of process, cpu time and arrival time.
*/
void enter(){
	int i;
	printf("Enter number of process: ");
	scanf("%d", &nbProcess);
	printf("Enter the process number: "); 
	for(i = 0; i < nbProcess; i++){
		scanf("%d", &processID[i]);
	}
	printf("Enter CPU burst time: ");
	for(i = 0; i < nbProcess; i++){
		scanf("%d", &burstTime[i]);
	}
	printf("Enter arrival time: ");
	for(i = 0; i < nbProcess; i++){
		scanf("%d", &arrivalTime[i]);
	}
}

/* 
Function to display processes, cpu time, arrival time, waiting time, average waiting time,
turnaround time and average turnaround time. 
*/
void display(){
	int i;
	printf("\nProcess\tCPU Burst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
	for(i = 0; i < nbProcess; i++){
		printf("P%d\t%7d\t%15d\t%15d\t%15d\n", processID[i], burstTime[i], arrivalTime[i], waitingTime[i], turnaroundTime[i]);
	}
	printf("Average waiting time: %.2f\n", avgWT);
	printf("Average turn around time: %.2f\n", avgTAT);
}

/* Function to swap two integer */
void swap(int *num1, int *num2){
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}

/* Function to arrange all processes according to the arrival time */
void sort(){
	int i, j;
	for(i = 0; i < nbProcess-1; i++)
		for(j = i+1; j < nbProcess; j++){
			if(arrivalTime[j] < arrivalTime[i]){
				swap(&processID[i], &processID[j]);
				swap(&burstTime[i], &burstTime[j]);
				swap(&arrivalTime[i], &arrivalTime[j]);
			}
		}
}

/* Function to calculate waiting time and average waiting time */
void calculatingWT(){
	int i;
	float totalWT = 0.0;
	int serviceTime[MAXPROCESS];
	/* Assign first element of serviceTime[] is arrival time of process which come CPU first */
	serviceTime[0] = arrivalTime[0];
	for(i = 0; i < nbProcess; i++){
		/* The next serviceTime is summation of burstTime and serviceTime of previous processes */
		serviceTime[i+1] = serviceTime[i] + burstTime[i];
		waitingTime[i] = serviceTime[i] - arrivalTime[i];
		totalWT += waitingTime[i];
	}
	avgWT = totalWT/nbProcess;
}

/* Function to calculate turn around time and average turnaround time */
void calculatingTAT(){
	int i;
	float totalTAT = 0.0;
	for(i = 0; i < nbProcess; i++){
		turnaroundTime[i] = waitingTime[i] + burstTime[i];
		totalTAT += turnaroundTime[i];
	}
	avgTAT = totalTAT/nbProcess;
}

int main(){
	enter();
	display();
	sort();
	calculatingWT();
	calculatingTAT();
	printf("\n------------------------------------------------------------------------\nRESULT");
	display();
	return 0;
}

