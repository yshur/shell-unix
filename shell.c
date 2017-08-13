#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

#define BUFFER 512
#define ARGS 32
#define SEPARATORS " \t\n"

int main (int argc, char** argv)
{
	char line[BUFFER];
	char* args[ARGS];
	char** arg;
	char* prompt = "shell>> ";
	char* cwd[256];
	DIR* directory;
	struct dirent* ent;

	while(1)
	{
		puts(prompt);
		fflush(stdout);
		
		if (fgets(line, BUFFER, stdin))
		{
			arg=args;
			*arg++ = strtok(line, SEPARATORS);
			while((*arg++ = strtok(NULL, SEPARATORS)));
			getcwd(cwd, 256);

			if (!args[1])
			{
				args[1]=(char*)malloc(256);
				strcpy(args[1], cwd);
			}
			if(strcmp(args[0], "ls")==0)
			{
				if ((directory=opendir(args[1]))==NULL)
				{
					perror("opendir");
					return 2;
				}		
				while((ent=readdir(directory))!=NULL)
				{
					if(0==strncmp(ent->d_name, ".", 1))
						continue;
					printf("%s ", ent->d_name);
				}
				printf("\n");
			}
			else if (strcmp(args[0], "cd")==0)
			{
				int ret;
				ret = chdir(args[1]);
				getcwd(cwd, 256);
				printf("%s\n", cwd);
			}
			else if (strcmp(args[0], "quit")==0)
			{
				printf("bye bye..\n");
				exit(0);
			}
			else
			{
				if(system(args[0])<0)
				{
					perror("system");
					exit(1);
				}
			}
		}
	}

	return 0;
}
