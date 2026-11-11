#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>
//clean up zombie process uisng waitpid in sighcld handler
void sigchld_handler(int n){
	int s;
	printf("sigchld handler running..\n");
	waitpid(-1,&s,0);
	printf("parent took the exit status of the child\n");

}
int main()
{
	if(fork()==0)
	{
		printf("Child pid=%d ,ppid=%d\n",getpid(),getppid());
		printf("child doen..\n");

	}
	else{
		signal(SIGCLD,sigchld_handler);
		sleep(60);
		printf("Parent pid=%d\n",getpid());
	}
}
