#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>


char namakomputer[50];
char direktori[50];
int counter=0;
void sigfunc(){
        fprintf(stderr, "\n%s@%s:~%s$ ", getenv("LOGNAME"), namakomputer, direktori);
}


int main()
{
	char perintah[200], *subperintah[20];
	int i=0;

	while(1){
		gethostname(namakomputer,50);
		getcwd(direktori,50);
		printf("%s@%s:~%s$ ", getenv("LOGNAME"), namakomputer, direktori);
		signal(SIGINT, sigfunc);
		signal(SIGTSTP, sigfunc);
		if(fgets(perintah,100,stdin) == NULL){
			printf("\n");
			break;
		}
		if(perintah[strlen(perintah)-1] == '\n')
			perintah[strlen(perintah)-1] = '\0';

		subperintah[i] = strtok(perintah, " ");
		for(i=1; i<20; i++){
			subperintah[i] = strtok(NULL, " ");
			if(subperintah[i] == NULL)	break;
		}
		if(execute(subperintah,i) == 0)	break;
	}
	return 0;
}


int execute(char** subperintah, int i){
        if(strcmp(subperintah[0], "cd") == 0){
                if(subperintah[1] == NULL)
                       fprintf(stderr, "cd: No argument\n");
                else if(chdir(subperintah[1]) != 0)
                        fprintf(stderr,"cd: No such file or directory\n");
		return 1;
        }
        else {
                int background = 0, j;
                if(strcmp(subperintah[i-1],"&") == 0){ 
		 	background = 1;
			counter=counter+1;
		}
                pid_t pid = fork();
                if(pid == 0){
                        if(background == 1){
				subperintah[i-1] = NULL;
				for (j=counter; j>=(counter-1); j--)
				{
					if (j==counter) printf("\n[%d] %d\n", j, getpid());
					else if (j!=0) printf("[%d] Done\n", j);
				}
			}
                        execvp(subperintah[0], subperintah);
		return 1;
                }
                else if(pid<0){
                        printf("ERROR\n");
                        return 0;
      		}
		else if(background != 1){
			int status;
			waitpid(pid,&status,0);
		return 1;
                }
        }
}
