#include<stdio.h>
#include<pthread.h>
#define NTHREADS 10000
#define NITER 50
int counter=0;//Global variable...Shared by all functions
void *thread_1(void *p){
	for(int i=0;i<NITER;i++){
		counter++;
	}
	return NULL;
}
int main(){
	pthread_t t[NTHREADS];
	for(int i=0;i<NTHREADS;i++)

		pthread_create(&t[i],NULL,thread_1,NULL);

	for(int i=0;i<NTHREADS;i++)
		pthread_join(t[i],NULL);

	printf("\ncounter value=%d\n",counter);





	return 0;
}

