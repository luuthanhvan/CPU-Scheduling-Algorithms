/* 
- Describe: This is a program for implementation of SJF (Shortest Job First) CPU Scheduling algorithm.
This algorithm associates with each process the length of the process's next CPU burst. When the CPU is available, it is 
assigned to the process that has the smallest next CPU burst.

- Idea:
	1. Sort all the processes according to the arrival time.
	2. Traverse until all process gets completely executed:
		- Find process with minimum remaining time at every single time lap.
		- Reduce its time by 1.
		- Check if its remaining time time becomes 0.
		- Increment the counter of process completion.
		- Completion time of current process = current time + 1
		- Calculate waiting time for each completed process.
			waiting time = completion time - arrival time - burst time
		- Increment time lap by one
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
	
	while(!complete)
		minTime <- __INT_MAX__
		For i <- 0 to n
		Begin
			if(burstTime != 0 && burstTime < minTime && arrivalTime <= t)
			Begin
				minTime = burst time
				minIndex = i
			End
			burstTime[minIndex] <- burstTime[minIndex] - 1
			if(burstTime[minIndex] == 0)
			Begin
				complete++
				finish_time = t+1;
				waitingTime[minIndex] = finishTime - arrivalTime[minIndex] - burstTime[minIndex]
				turnaroundTime[minIndex] = waitingTime[minIndex] + burstTime[minIndex]
				totalWT = totalWT + waitingTime[minIndex]
				totalTAT = totalTAT + turnaroundTime[minIndex]
			End
		End
		avgWT <- totalWT/nbProcess
		avgTAT <- totalTAT/nbProcess
*/

#include <stdio.h>
#define MAXPROCESS 50 /* Define the maximum process */
#define INT_MAX 9999999

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
Function to allow user enter number of process, cpu time and arrival time 
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
turnaround time and average turnaround time
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

/* 
Function to swap two integer 
*/
void swap(int *num1, int *num2){
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}

/* 
Function to sort all processes according to the arrival time 
*/
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

/* 
Function to calculate waiting time and average waiting time 
*/
void calculatingWT(){
	float sumWT = 0.0; // sum of waiting time
	int rt[MAXPROCESS];
	int i, j;
	// make a copy the burst time of all processes into rt[]
	for(i = 0; i < nbProcess; i++)
		rt[i] = burstTime[i];
	int complete = 0, minIndex;
	int t = arrivalTime[0]; // current time = the time of process which come CPU first
	// traverse until all processes gets completed
	while(complete != nbProcess){
		int minTime = INT_MAX;
		for(i = 0; i < nbProcess; i++){
			// find process with minimum burst time
			if(arrivalTime[i] <= t && rt[i] < minTime && rt[i] > 0){
				minTime = rt[i];
				minIndex = i;
			}
		}
		rt[minIndex]--; // reduce remaining time by one
		t++; // increment time
		// if a process gets completely executed
		if(rt[minIndex] == 0){
			complete++;
			//int finishTime = t+1; // finish time of current process
			waitingTime[minIndex] = t - burstTime[minIndex] - arrivalTime[minIndex];
			sumWT += waitingTime[minIndex];
		}
		//t++; // increment time
	}
	avgWT = sumWT/nbProcess;
}

/* 
Function to calculate turn around time and average turnaround time 
*/
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
