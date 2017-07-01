#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
static char line[1024];

int main()
{
	printf("SIMPLE SHELL: Type 'exit' to exit from shell.\n");
	while (1) {
		//input
		if (!fgets(line, 1024, stdin)) 
			return 0;
 
		char* cmd = line;
		printf("\nCommand is: %s", cmd);
		//checking for exit criteria
			pid_t pid = fork();
			if (pid == 0)
			{
				if(strcmp(cmd,"exit\n")==0)
				{
					printf("Exiting from shell\n");
					return 0;
				} else {
				FILE *fpread, *fpwrite;
				char *  tokens    = strtok (line, " ");
				char seps[]   = " ,\t\n";
				char ch;
				ssize_t read;
				int count = 0;
				while (tokens != NULL)
				{
					if (count == 0 && (strcmp(tokens, "read") == 0))
					{
						tokens = strtok(NULL, seps);
						if (strcmp(tokens, "<") == 0)
						{
							tokens = strtok(NULL, seps);
							fpread  = fopen(tokens, "r");
							fpwrite = fopen("temp.txt", "w");
							while ((ch = getc(fpread)) != -1)
							{
								putc(ch, fpwrite);
							}
							fclose(fpread);
							fclose(fpwrite);
						}
						count = 1;
					} else if (count== 0 && strcmp(tokens, "write") == 0) {
						tokens = strtok(NULL, seps);
						if (strcmp(tokens, ">") == 0)
						{
							tokens = strtok(NULL, seps);
							fpread  = fopen("temp.txt", "r");
							fpwrite = fopen(tokens, "w");
							while ((ch = getc(fpread)) != -1)
							{
								putc(ch, fpwrite);
							}
							fclose(fpread);
							fclose(fpwrite);
						}
						count = 1;
					} else if (count == 0 && strcmp(tokens, "append") == 0) {
						tokens = strtok(NULL, seps);
						if (strcmp(tokens, ">>") == 0)
						{
							tokens = strtok(NULL, seps);
							fpread  = fopen("temp.txt", "r");
							fpwrite = fopen(tokens, "a");
							while ((ch = getc(fpread)) != -1)
							{
								putc(ch, fpwrite);
							}
							fclose(fpread);
							fclose(fpwrite);
						}
						count = 1;
					} else if (count == 1 && (strcmp(tokens, "|") == 0)) {
						printf("\nIn pipe");
						count = 0;
					}
					tokens = strtok(NULL, seps);
				}
				}
			} else if (pid > 0) {

				wait(NULL);
				return(0);
			}
	}
}
