#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){
	pid_t c1,c2,c3;

	if((c1=fork())==0)//creating a child process
	{
		sleep(10);
		//child-1
	}
	else{
		if((c2=fork())==0)
		{
			//child-2
		}
		else
		{
			if((c3=fork())==0){
				// child-3
			}
			/*			else{
						int s;
						pid_t r;
						while((r=waitpid(-1,&s,WNOHANG))!=-1)//waiting for all childs to be done
						{
						if(r==c1){
						printf("Child 1 exn completed\n");}
						else if(r==c2){
						printf("Child 2 exn completed\n");}
						else if(r==c3){
						printf("Child 3 exn completed\n");
						}
						}
						printf("All childs exn done\n");
						printf("Parent process exng.\n");
						printf("parent process pid=%d\n",getpid());

						printf("Parents exn done\n");




						}*/
						else{
							int s;
							pid_t r;
							while(waitpid(c1,&s,WNOHANG)==0)
								printf("c1 still sleeping\n");
							if(WIFEXITED(s))
								printf("exit code:%d\n",WEXITSTATUS(s));
						}

		}
	}


}
