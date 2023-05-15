#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
char cwd[1000];
char prevWorkingDirectory[1000];
int historyLines = 0;
void callExit() {
	printf("Exiting.\n");
	exit(0);
}
void callGetcwd() {
	getcwd(cwd, sizeof(cwd));
	if (cwd == NULL) {
		printf("getcwd() error\n");
	}
}
int checkInternalCommand(char* token) {
	if (strcmp(token, "cd") == 0 || strcmp(token, "echo") == 0 || strcmp(token, "history") == 0 || strcmp(token, "pwd") == 0 || strcmp(token, "exit") == 0) {
		return 1;
	}
	else {
		return 0;
	}
}
int checkExternalCommand(char* token) {
	if (strcmp(token, "ls") == 0 || strcmp(token, "cat") == 0 || strcmp(token, "date") == 0 || strcmp(token, "rm") == 0 || strcmp(token, "mkdir") == 0) {
		return 1;
	}
	else {
		return 0;
	}
}
void callChdir(char* add) {
	int x = chdir(add);
	if (x == -1) {
		printf("Error in changing directory to %s\n", add);
	}
	else {
		strcpy(prevWorkingDirectory, cwd);
		strcpy(cwd, add);
	}
}
void cd(char* argument) {
	if (argument == NULL || strcmp(argument, "-") == 0) {
		callChdir(prevWorkingDirectory);
	}
	else if (strcmp("..", argument) == 0) {
		callChdir("../");
	}
	else if (strcmp("~", argument) == 0) {
		callChdir(getenv("HOME"));
	}
	else {
		if (strcmp("-L", argument) == 0 || strcmp("-P", argument) == 0) {
			argument = strtok(NULL, " ");
			if (argument == NULL) {
				callChdir(getenv("HOME"));
			}
			else {
				callChdir(argument);
			}
		}
		else {
			callChdir(argument);
		}
	}
}
void pwd(char* argument) {
	if (argument != NULL) {
		if (strcmp(argument, "-L") == 0) {
			printf("%s\n", cwd);
		}
		else if (strcmp(argument, "--help") == 0) {
			FILE* help = fopen("/Users/nvgenomics/Desktop/projects/shell in c/pwdhelp.txt", "r");
			char out[1000];
			while (fgets(out, sizeof(out), help) != NULL) {
				fputs(out, stdout);
			}
			fclose(help);
		}
		else {
			printf("Command not found\n");
		}
	}
	else {
		printf("%s\n", cwd);
	}
}
void history(char* argument) {
	if (argument == NULL) {
		FILE* his = fopen("/Users/nvgenomics/Desktop/projects/shell in c/historystore.txt", "r");
		char out[1000];
		int line = 0;
		while (fgets(out, sizeof(out), his) != NULL) {
			line += 1;
			printf(" %d\t", line);
			fputs(out, stdout);
		}
		fclose(his);
	}
	else {
		if (strcmp(argument, "-c") == 0) {
			FILE* his = fopen("/Users/nvgenomics/Desktop/projects/shell in c/historystore.txt", "w");
			fclose(his);
			historyLines = 0;
		}
		else if (strcmp(argument, "-s") == 0) {
			argument = strtok(NULL, " ");
			FILE* his = fopen("/Users/nvgenomics/Desktop/projects/shell in c/historystore.txt", "a");
			while (argument != NULL) {
				fprintf(his, "%s ", argument);
				argument = strtok(NULL, " ");
			}
			fprintf(his, "%s\n", "");
			fclose(his);
			historyLines += 1;
		}
		else if (strcmp(argument, "--help") == 0) {
			FILE* help = fopen("/Users/nvgenomics/Desktop/projects/shell in c/historyhelp.txt", "r");
			char out[1000];
			while (fgets(out, sizeof(out), help) != NULL) {
				fputs(out, stdout);
			}
			fclose(help);
		}
		else {
			printf("Command not in history\n");
		}
	}
}
void exitt(char* token) {
	if (token == NULL) {
		exit(0);
	}
	else if (strcmp(token, "--help") == 0) {
		printf("Press 'exit' to exit\n");
	}
	else {
		printf("Invalid command\n");
	}
}

void maintainHistoryStore(char* argument) {
	FILE* his = fopen("/Users/nvgenomics/Desktop/projects/shell in c/historystore.txt", "a");
	fprintf(his, "%s\n", argument);
	fclose(his);
	historyLines += 1;
}

void echo(char* token) {
	if (token == NULL) {
		printf("\n");
	}
	else if (strcmp(token, "--help") == 0) {
		printf("Use 'echo' followed by an argument\n");
	}
	else {
		while (token != NULL) {
			printf("%s ", token);
			token = strtok(NULL, " ");
		}
		printf("\n");
	}
}

void callInternalCommand(char* token) {
	if (strcmp(token, "cd") == 0) {
		token = strtok(NULL, " ");
		cd(token);
	}
	else if (strcmp(token, "echo") == 0) {
		token = strtok(NULL, " ");
		echo(token);
	}
	else if (strcmp(token, "history") == 0) {
		token = strtok(NULL, " ");
		history(token);
	}
	else if (strcmp(token, "pwd") == 0) {
		token = strtok(NULL, " ");
		pwd(token);
	}
	else if (strcmp(token, "exit") == 0) {
		token = strtok(NULL, " ");
		exitt(token);
	}
}

void callExternalCommand(char* token, char input[]) {
	if (strcmp(token, "ls") == 0) {
		token = strtok(NULL, " ");
		execl("/Users/nvgenomics/Desktop/projects/shell in c/ls.c", token, NULL);
	}
	else if (strcmp(token, "cat") == 0) {
		token = strtok(NULL, " ");
		execl("/Users/nvgenomics/Desktop/projects/shell in c/cat.c", token, input, NULL);
	}
	else if (strcmp(token, "date") == 0) {
		token = strtok(NULL, " ");
		execl("/Users/nvgenomics/Desktop/projects/shell in c/date.c", token, NULL);
	}
	else if (strcmp(token, "rm") == 0) {
		token = strtok(NULL, " ");
		execl("/Users/nvgenomics/Desktop/projects/shell in c/rm.c", token, input, NULL);
	}
	else if (strcmp(token, "mkdir") == 0) {
		token = strtok(NULL, " ");
		execl("/Users/nvgenomics/Desktop/projects/shell in c/mkdir.c", token, input, NULL);
	}
}
void callHelp() {
	FILE* help = fopen("/Users/nvgenomics/Desktop/projects/shell in c/help.txt", "r");
	char out[1000];
	while (fgets(out, sizeof(out), help) != NULL) {
		fputs(out, stdout);
	}
	fclose(help);
}
int main(int arg, char const* argc[]) {
	printf("WELCOME TO YASH'S SHELL\n");
	callGetcwd();
	strcpy(prevWorkingDirectory, cwd);
	while (1) {
		callGetcwd();
		printf("%s ~$ ", cwd);
		char input[100];
		char nakli[105] = "";
		scanf("%[^\n]%*c", input);
		maintainHistoryStore(input);
		strcat(nakli, input);
		strcat(nakli, " ");
		char* token;
		token = strtok(input, " ");
		if (checkInternalCommand(token) == 1) {
			callInternalCommand(token);
		}
		else if (checkExternalCommand(token) == 1) {
			pid_t pid;
			pid = fork();
			if (pid == 0) {
				// Child process
				callExternalCommand(token, nakli);
				exit(0);
			}
			else if (pid > 0) {
				// Parent process
				waitpid(0, NULL, 0);
				// Wait for the child process to end
			}
			else {
				printf("Error in forking\n");
			}
		}
		else {
			if (strcmp(token, "help") == 0) {
				callHelp();
			}
			else {
				printf("Command not found\n");
				printf("Enter 'help' for supported commands\n");
			}
		}
	}
	return 0;
}
 
