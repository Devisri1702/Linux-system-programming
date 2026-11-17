#include<stdio.h>
#include<stdlib.h>
int x=10;//DATA SEC
int y;//BSS
void recurse(int depth)
{
	int l=depth;//lives in the stack
	printf("depth %d:&l=%p\n",depth,(void*)&l);
	if(depth<3)
		recurse(depth+1);


}
int main(){
	int l=1;
	//address per region
	printf("PART A:REGIONS--\n");
	printf("data sec :%p\n",&x);
	printf("bss sec: %p\n",&y);
	printf("Stack sec: %p\n",&l);

	//Heap growth
        printf("PART B:heap--\n");
	for(int i=0;i<4;i++)
	{
		void *p=malloc(100);
		printf("malloc %d: %p\n",i+1,p);

	}
	//Stack growth
	printf("\n---Part C: Stack\n");
	recurse(1);
	return 0;
}

