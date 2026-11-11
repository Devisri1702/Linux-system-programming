#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
int main()
{
	if(fork()==0)
	{
		printf("child pid=%d ppid=%d\n",getpid(),getppid());
		sleep(30);
		printf("After sleep child pid=%d ppid=%d\n",getpid(),getppid());

	}
	else{
		printf("parent pid=%d\n",getpid());
		printf("parent process terminated\n");
	}
}
