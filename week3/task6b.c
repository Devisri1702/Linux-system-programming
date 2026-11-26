#include<stdio.h>
#include<pthread.h>
#define NTHREADS 5
#define NITER 100000
pthread_mutex_t lock;
int counter=0;//Global variable...Shared by all functions
void *thread_1(void *p){
	for(int i=0;i<NITER;i++){
		pthread_mutex_lock(&lock);
		counter++;
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}
int main(){
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_ERRORCHECK);
       pthread_mutex_init(&lock,&attr);
	pthread_t t[NTHREADS];
	for(int i=0;i<NTHREADS;i++)

		pthread_create(&t[i],NULL,thread_1,NULL);

	for(int i=0;i<NTHREADS;i++)
		pthread_join(t[i],NULL);


     pthread_mutexattr_destroy(&attr);
     int r;
    r= pthread_mutex_lock(&lock);
    printf("First lock succeed,returns= %d\n",r);
    
    r= pthread_mutex_lock(&lock);
    printf("Second lock failed returned= %d\n",r);


   r= pthread_mutex_unlock(&lock);
   printf("First unlock success,return= %d\n",r);
   r= pthread_mutex_unlock(&lock);
   printf("Extra unlock fails,return= %d\n",r);

printf("Counter value=%d\n",counter);




	return 0;
}

