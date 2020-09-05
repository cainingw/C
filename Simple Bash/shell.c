#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
	char *prompt = "308sh> ";//used to store prompt
	char command[100];//used to store command
	char path[100];//used to store new directory path
	char cwd[1024];//used to store current directory

    //implement prompt option
    if(argc == 3){
       if(strcmp(argv[1],"-p")==0){
	    prompt = argv[2];
       }else{
	printf("Invalid command line \n");
	}
     }
    else if(argc == 1){  

    }else{
      printf("Invalid command line \n");
    }


   while(1){
	//print out prompt
	printf(prompt);

	//get user input
	fgets(command,100,stdin);

	//Eliminate enter influence in command
	if (strlen(command)>0 && command[strlen (command) - 1] == '\n'){
        	command[strlen(command) - 1] = '\0';
	}

	
	//buildin command implementation
	//use strtok to separate the command into different results
	int i = 0;
       	char *token[100];
	token[0] = strtok(command,  " ");
	while(token[i] != NULL){
		i++;
		token[i]= strtok(NULL," ");
	}

	//set <var> <value>
	if(strcmp(token[0], "set") == 0){
		setenv(token[1],token[2],1);	
		}

	//get <var>	
	else if(strcmp(token[0],"get")==0){
	printf("%s: %s\n", token[1],getenv(token[1]));	
	}	

	//exit
	else if(strcmp(token[0], "exit") == 0){
		return 0; 
	}
	//pid
	else if(strcmp(token[0], "pid") == 0){
		printf("Current process ID is %d.\n", getpid());
	}	
	//ppid
	else if(strcmp(token[0], "ppid") == 0){
		printf("Current parent process ID is %d.\n", getppid());
	}  	
	//cd <dir>
	else if(strcmp(token[0], "cd") == 0){
		if(token[1] == NULL){
			chdir(getenv("HOME"));
		}else{
			if(chdir(token[1]) < 0){
				printf("cannot find directory\n");
			}
		}				
	}
	//pwd
	else if(strcmp(token[0], "pwd") == 0){
		if(getcwd(cwd, sizeof(cwd)) == -1){
			printf("failed to print current directory");
		}
		printf("%s\n", cwd);
	}



	// program commands implementation
  	else{
		int child1,child2;
		int status;
		int background = 0;

		if(command[strlen(command)-1]=='&'){
		background = 1;
		command[strlen(command)-1]= '\0';
		}
		
		// not background process
		if(background == 0){
			if ((child1 = fork())<0){
				printf("failed to fork a child process");
			}
			else if (child1 == 0){
				if(strcmp(token[0], "/bin/ls") == 0){
				printf("[%d] %s\n",getpid(),"ls");
				}else{
				printf("[%d] %s\n",getpid(),token[0]);
				}
				if(execvp(token[0], token)<0){
					printf("Cannot exec %s: No such file or directory\n",token[0]);	
				}
				usleep(1000);
				return 0;
			}
			else{
				status = -1;
                        	waitpid(child1, &status, 0);
				if(strcmp(token[0], "/bin/ls") == 0){
				printf("[%d] %s Exit %d\n", child1, "ls",WEXITSTATUS(status));
				}else{
				printf("[%d] %s Exit %d\n", child1, token[0], WEXITSTATUS(status));
				}
                 	
			}
		}
		// background process(currently not work)		
		else{
			background = 0;
			child2 = fork();
			if(child2 == 0){
				child1 = fork();
				if(child1 == 0){
					printf("[%d] %s\n", getpid(), token[0]);
					execvp(token[0], token);
					perror("\0");
					return 0;
				}else{
					status = -1;
					waitpid(-1,&status,0);
					if(1){
						printf("\n[%d] %s Exit %d\n", child1, token[0], WEXITSTATUS(status));
						printf(prompt);
					}else{
						printf("[%d] %s Exit %d\n", child1, token[0], WEXITSTATUS(status));
					}
					return 0;
				}
			}else{	
				usleep(1000);	
			}
		}
	}	
  }
  return 0;
}