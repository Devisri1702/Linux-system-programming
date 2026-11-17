#include<stdio.h>
#include<stdlib.h>
int x=10;//DATA SEC
int y;//BSS
int main(){
	int l=1;
	int *p=malloc(100);
	//address per region
	printf("PID:%d\n",getpid());
	printf("data sec :%p\n",&x);
	printf("bss sec: %p\n",&y);
	printf("heap:%p\n",p);
	printf("Stack sec: %p\n",&l);
printf("\npaused. Run the tools in another terminal.\Press Enter to exit.\n");
getchar();
free(p);
return 0;
}

