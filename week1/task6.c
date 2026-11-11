#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
int main(int argc,char *argv[]){
	if(argc!=4)
	{
		printf("Usage:./a.out src destn buffersize");
		return 1;
	}
	int bufsize=atoi(argv[3]);
	char *buf=malloc(bufsize);
	int in=open(argv[1],O_RDONLY);
	if(in<0)
	{
		perror("Open src:");
		return 1;
	}
	int out=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0664);

	if(out<0){
		perror("Open destn");
		return 1;}
	int n;	
	//reading from input file using in filedescriptor into buffer based on bufsize bytes and writing to output file frm that buf. 
	while(n=read(in,buf,bufsize))
	{
		int w=write(out,buf,n);
		if(w!=n)
		{
			perror("written failed");
			return 1;
		}
	}
	close(in);
	close (out);
	free(buf);
	return 0;
}
