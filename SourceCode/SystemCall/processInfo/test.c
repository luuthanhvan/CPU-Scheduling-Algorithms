#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
int main(){
	printf("Invoking 'print_self' system call\n");
	long int sys = syscall(333); // 333 is the system call number
	if(sys == 0)
		printf("System call 'printf_self' executed correctly. Use dmesg to check processInfo\n");
	else
		printf("System call 'printf_self ' did not execute as expected\n");
	return 0;
}

