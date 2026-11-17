#include<stdio.h>
int main(){

FILE *f=fopen("/proc/self/maps","r");
if(!f){perror("fopen:");
return;}
char line[512];
while(fgets(line,sizeof(line),f))
	printf("%s\n",line);




}
