#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

int main(){
	printf("Invoking 'helloworld' system call");
	long int sys = syscall(333); // 333 is the system call number
	if(sys == 0)
		printf("System call 'helloworld' executed correctly.\nUsing the command 'dmesg' to check 'helloworld' system call\n");
	else
		printf("System call 'helloworld' did not execute as expected\n");
	return 0;
}

