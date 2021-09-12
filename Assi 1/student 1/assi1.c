#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main(){
	char* cmds[]={"firefox","ls","gedit","terminator","ifconfig"};	int cont=1;	char *a[]={"./EXEC",NULL}; 
	while(cont){
		printf("Please choose an option :\n1. firefox\n2. List files\n3. Text editor\n4. Terminator\n5. configure a network interface\n");
		int choice; 
		printf("Your choice :");
		scanf("%d",&choice);
		if(0<choice<6){
			int proc_id=fork(); 
			if(proc_id==0){ 
				execvp(cmds[choice-1],a);	}
			sleep(2);	}
		else{
			printf("Please enter valid option. \n");
		}
		printf("Do you want to continue? Press 1 for Yes and 0 for No\n");
		scanf("%d",&cont);
}}
