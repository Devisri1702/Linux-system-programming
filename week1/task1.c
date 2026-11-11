#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<ctype.h>
struct proc{
	int pid;
	int ppid;
	char name[256];
	char state;
};

struct proc arr[1000];
int cnt =0;
//printing the heirarchy 
void print_tree(int idx,int level)
{
	for(int i=0;i<level;i++)//to print the space for every subtree(process heirarchy)
	printf(" ");

	printf("%d %d %c %s\n",arr[idx].pid,arr[idx].ppid,arr[idx].state,arr[idx].name);
	for(int j=0;j<cnt;j++)
	if(arr[j].ppid==arr[idx].pid)//checking if process j is a  children for this process(idx)
		print_tree(j,level+1);

}
int read_status(int pid,struct proc *p){
	char path[64];
	char line[256];
	FILE *fp;
	snprintf(path,sizeof(path),"/proc/%d/status",pid);
	fp=fopen(path,"r");
	if(fp==0)
		return 0;
	while(fgets(line,sizeof(line),fp)!=NULL)
	{
		if(strncmp(line,"Name:",5)==0)
			sscanf(line,"Name: %255s",p->name);
		else if(strncmp(line,"State:",6)==0)
			sscanf(line,"State: %c",&p->state);
		else if(strncmp(line,"Pid:",4)==0)
			sscanf(line,"Pid: %d",&p->pid);
		else if(strncmp(line,"PPid:",5)==0)
			sscanf(line,"PPid: %d",&p->ppid);
		
	}
	fclose(fp);
return 1;

}
int main()
{
	DIR *d;
	struct dirent *e;
	d=opendir("/proc");
	if(d==NULL)
	return 1;
	while((e=readdir(d))!=NULL)
	{
	if(isdigit(e->d_name[0]))
	{
		int pid=atoi(e->d_name);
		read_status(pid,&arr[cnt]);
		cnt++;
	}
	}
closedir(d);
for(int i=0;i<cnt;i++)
if(arr[i].ppid==0)
print_tree(i,0);




}
