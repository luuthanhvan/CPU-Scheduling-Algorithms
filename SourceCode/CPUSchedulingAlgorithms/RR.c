/*
- Describe: This is a program for implementation of Round Robin (RR) CPU Scheduling algorithm.
RR is a preemptive scheduling algorithm. It is designed especially for time sharing systems. In this algorithm, 
a small unit of time called time quantum or time slice is assigned to each process. When the time quantum expired, the 
CPU is switched to another process. Performance of Round Robin totally depends on the size of the time quantum.
- Idea:
	1. Sort all the processes according to the arrival time.
	2. Keep traversing the all processes while all processes are not done.
		- if burst time > 0
			+) t = t + quantum
			+) burst time = burstime - quantum
		- else
			+) t = t + burst time
			+) waiting time = t - burst time - arrival time
			+) burst time = 0
	3. Find turn around time = waiting time + burst time.
	4. Average waiting time = total waiting time/number of process
	5. Average turnaround time = total turnaround time/number of processs
	
- Initialization variables:
	nbProcess: number of processes
	processID[]: array which store process number
	burstTime[] <- 0: array which store burst time of n processes
	arrivalTime[] <- 0: array which store arrival time of all processes
	waitingTime[] <- 0: array which store waiting time of all processes
	turnaroundTime[] <- 0: array which store turnaround time of all processes
	quantum: quantum time
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
	t <- arrivalTime[0]
	while(!done)
		For i <- 0 to n
		Begin
			if(burstTime[i] > 0)
				if(burstTime[i] > quantum)
					Begin
						t += quantum
						burstTime[i] -= quantum
					End
				else
					Begin
						t += burstTime[i]
						waitingTime[i] = t - burstTime[i] - arrivalTime[i]
						turnaroundTime[i] = waitingTime[i] + burstTime[i]
						totalWT += waitingTime[i]
						totalTAT += turnaroundTime[i]
						burstTime[i] = 0
					End
			else
				continue
		End
		done++
		avgWT <- totalWT/nbProcess
		avgTAT <- totalTAT/nbProcess
*/
#include <stdio.h>
#define MAXPROCESS 10 // Define the maximum process

/* Declare some global variables */
int process[MAXPROCESS];
int burstTime[MAXPROCESS]; 
int arrivalTime[MAXPROCESS];
int nbProcess; 
int waitingTime[MAXPROCESS];
int turnaroundTime[MAXPROCESS]; 
int quantum;
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
		scanf("%d", &process[i]);
	}
	printf("Enter CPU burst time: ");
	for(i = 0; i < nbProcess; i++){
		scanf("%d", &burstTime[i]);
	}
	
	printf("Enter arrival time: ");
	for(i = 0; i < nbProcess; i++){
		scanf("%d", &arrivalTime[i]);
	}
	printf("Enter quantum: ");
	scanf("%d", &quantum);
}

/* 
Function to display processes, cpu time, arrival time, waiting time, average waiting time,
turnaround time and average turnaround time.
*/
void display(){
	int i;
	printf("\nProcess\tCPU Burst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
	for(i = 0; i < nbProcess; i++){
		printf("P%d\t%7d\t%15d\t%15d\t%15d\n", process[i], burstTime[i], arrivalTime[i], waitingTime[i], turnaroundTime[i]);
	}
	printf("Average waiting time: %.2f\n", avgWT);
	printf("Average turn around time: %.2f\n", avgTAT);
}

/* Function to swap two integer. */
void swap(int *num1, int *num2){
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}

/* Function to sort all processes according to the arrival time. */
void sort(){
	int i, j;
	for(i = 0; i < nbProcess-1; i++)
		for(j = i+1; j < nbProcess; j++){
			if(arrivalTime[j] < arrivalTime[i]){
				swap(&process[i], &process[j]);
				swap(&burstTime[i], &burstTime[j]);
				swap(&arrivalTime[i], &arrivalTime[j]);
			}
		}
}

/* Function to calculate waiting time and average waiting time. */
void calculatingWT(){
	int i, j, temp = 0, remain = nbProcess;
	float totalWT = 0.0;
	int rt[MAXPROCESS];
	/* make a copy the burst time of all processes into rt[] */
	for(i = 0; i < nbProcess; i++){
		rt[i] = burstTime[i];
	}
	int t = arrivalTime[0]; /* current time = the time of process which come CPU first */
	int done = 0;
	while(done != nbProcess){
		for(i = 0; i < nbProcess; i++){
			if(rt[i] > 0){
				if(rt[i] > quantum){
					rt[i] -= quantum; /* decrease the burst time by quantum time */
					t += quantum; /* increase the current time by quantum time */
				}
				else{
					t += rt[i]; /* increase the current time by burst time */
					waitingTime[i] = t - burstTime[i] - arrivalTime[i];
					totalWT += waitingTime[i];
					rt[i] = 0;
				}
			}
			else
				continue;
		}
		done++;
	}
	avgWT = totalWT/nbProcess;
}

/* Function to calculate turn around time and average turnaround time */
void calculatingTAT(){
	int i;
	float sumTAT = 0.0; // sum of turnaround time
	for(i = 0; i < nbProcess; i++){
		turnaroundTime[i] = waitingTime[i] + burstTime[i];
		sumTAT += turnaroundTime[i];
	}
	avgTAT = sumTAT/nbProcess;
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
