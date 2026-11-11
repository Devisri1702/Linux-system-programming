#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main(){
	char *args[]={"ls",NULL};
	printf("In Main..\n");
	execve("/bin/ls",args,NULL);
	printf("After execev");
}
